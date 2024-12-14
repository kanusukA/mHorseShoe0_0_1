#pragma once

#include <Gui/mediator/GuiMediator.h>

#include <GDHandler/ResourceHandler.h>




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

	std::vector<std::string>* renderMeshes;
	std::vector<std::string>* colliderMeshes;

public:

	// EXTERNAL
	void StatusTab(ImVec2 pos, int* fps, const Ogre::Vector3* position, Ogre::Vector3* rotation);
	void ShowADDTab(bool b);

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




