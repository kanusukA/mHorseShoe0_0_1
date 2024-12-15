#pragma once

#include <Gui/mediator/GuiMediator.h>

#include <GDHandler/ResourceHandler.h>

#include <feel/playerMovement.h>




struct GUI_WINDOW_POS {
	ImVec2 TOP_LEFT;
	ImVec2 TOP_RIGHT;
	ImVec2 TOP_CENTER;

	ImVec2 RIGHT;
	ImVec2 LEFT;
	ImVec2 CENTER;

	ImVec2 BOTTOM_LEFT;
	ImVec2 BOTTOM_RIGHT;
	ImVec2 BOTTOM_CENTER;
	
};


// Initalize from the Ogre::ApplicationContext -> initImGuiOverlay()
// Add imGui input listner to context input listner.
class Gui
{
private:

	Ogre::ImGuiOverlay* imOverlay = nullptr;

	GUI_WINDOW_POS* guiWPos = new GUI_WINDOW_POS();

	GuiComponent* guiComponent;

	int renderMeshesPosition = 0;
	int colliderMeshesPosition = 0;
	std::vector<std::string>* renderMeshes;
	std::vector<std::string>* colliderMeshes;

	PlayerObserver* playerObserver = nullptr;

	// Add Variable
	int pos[3] = { 0,0,0 };
	int c_size[3] = { 0,0,0 };

	// Gui Variables
	bool showStatusTab = false;
	bool showAddTab = false;

	ImVec2 StatusWindowPos;
	int* fps;

public:

	// EXTERNAL
	void StatusTab(ImVec2 pos, int* fps);
	void ShowADDTab(bool b);

	void setPlayerObserver(PlayerObserver* pObserver);

	// INIT
	void initGui(Ogre::ImGuiOverlay* overlay, GuiComponent* component);
	void setWindowGrabPoints(int WIDTH, int HEIGHT);
	void updateGui();
	void shutdown();

	// INTERNAL
	void _statusTab();
	void _addTab();
	void _debugTab();


};




