#pragma once

#include <base/Mediator.h>

#include <Ogre.h>
#include <OgreImGuiOverlay.h>
#include <imgui_stdlib.h>
#include <cons.h>


enum phyType {
	DYNAMIC,
	STATIC,
	MESH
};

struct GuiParam {
	// VISUAL PARAM
	bool showRenderShapes = true;
	bool showDebugLines = false;

	// STATUS TAB
	bool showStatus = false;
	ImVec2 statusPosition;

	// ADD TAB
	bool showAdd = false;

};

struct AddParam{

	int positionRenderMesh = 0;
	int positionColliderMesh = 0;

	// Strings are set in a pointer because IMGUI takes string pointers for Input Text. It's more simpler
	std::string* obj_name = new std::string("Object Name");
	std::string* msh_name = new std::string("Mesh File Name");

	// type : 
	// 0 - DYNAMIC
	// 1 - STATIC
	// 2 - MESH
	phyType type = phyType::DYNAMIC;
	int* mass = new int(0);
	
};



class GuiComponent : public MediatorComponent {
private:
	AddParam* addParam = new AddParam();
	GuiParam* guiParam = new GuiParam();

public:

	void addObject() {
		// Add Events
		this->_mediator->Notify(this, "Add_object");
	}

	void showRenderMeshes() {
		this->_mediator->Notify(this, "show_render_meshes");
	}

	void showDebugLines() {
		this->_mediator->Notify(this, "show_debug_lines");
	}

	// Add Mesh functions

	void setRenderMeshName(std::string name) {
		*addParam->msh_name = name;
	}

	void setObjectName(std::string name) {
		*addParam->obj_name = name;
	}

	std::string* getRenderMeshName() {
		return addParam->msh_name;
	}
	std::string* getObjectName() {
		return addParam->obj_name;
	}

	phyType& getPhysicsType() {
		return this->addParam->type;
	}
	void setPhysicsType(phyType type) {
		this->addParam->type = type;
	}

	int* getMass() {
		return this->addParam->mass;
	}
	

	// Gui Param functions
	void showStatusBar(bool show) {
		guiParam->showStatus = show;
	}
	void showAdd(bool show) {
		guiParam->showAdd = show;
	}

};


class GuiMediator : public Mediator {
public:

	void Notify(MediatorComponent* component, std::string event) const override {

	}

};



