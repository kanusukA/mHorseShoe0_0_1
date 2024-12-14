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

	std::string obj_name = "Object_Name";
	std::string msh_name = "Mesh_Path_Name";
	// type : 
	// 0 - DYNAMIC
	// 1 - STATIC
	// 2 - MESH
	phyType type = phyType::DYNAMIC;
	int mass = 0;
	int pos[3] = { 0,0,0 };
	int c_size[3] = { 0,0,0 };
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
		addParam->msh_name = name;
	}

	void setObjectName(std::string name) {
		addParam->obj_name = name;
	}
	

	// Gui Param functions
	void showStatusBar(bool show) {
		guiParam->showStatus = show;
	}
	void showAdd(bool show) {
		guiParam->showAdd = show;
	}

};



