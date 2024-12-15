#pragma once

#include<GDHandler/ResourceHandler.h>

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreTrays.h>

#include <Gui/Gui.h>

#include <PxPhysicsAPI.h>

#include <iostream>

#include <SDL3/SDL.h>
#include <Windows.h>

#include <cons.h>

const Ogre::String TRAY_SYSTEM_NAME = "Default_Tray_Man";

#define MAIN_CAMERA_NAME "main_camera_name"


class Monster : public Gui
{

private:
	Ogre::SceneNode* CameraNode;

public:

	// INITIALIZE OGRE3D AND CREATE A RENDERWINDOW
	// name  -  NAME OF THE RENDERWINDOW
	Monster(Ogre::Root* root, Ogre::RenderWindow* rWin , Ogre::OverlaySystem* overlay, int &FPS);

	// INITIALISES SDL3 WINDOW / ADDS DEFAULT CAMERAMAN / GUI SYSTEM
	void InitMonster(Ogre::ImGuiOverlay* imguiOverlay, Mediator* mediator);

	// Use this function to add input listner to the application context
	int* FPS;

	Ogre::Root* oRoot;
	Ogre::RenderWindow* renderWindow;
	Ogre::SceneManager* oScnManager;


	Ogre::ManualObject* visualManualObj;
	Ogre::SceneNode* debugLineScnNode;

	Ogre::ManualObject* debugTriangleObj;
	Ogre::SceneNode* debugTriangleScnNode;

	// Add Subject and observer for render meshes available in Monster
	std::vector<Ogre::MeshPtr> preLoadRenderMeshes = std::vector<Ogre::MeshPtr>();

	SDL_Window* sdlWindow;

	Ogre::SceneNode* addCamera(Ogre::String camName, Ogre::Vector3 startPos);
	void addGuiPlayerInfo();
	Ogre::SceneNode* loadMeshScnNode(Ogre::String scnNodeName, Ogre::String meshName);

	void update();

	// PRE-LOAD MESHES

	// saves meshes to a vector to be accessed by gui
	void preLoadMeshData();
	// addes a resource location 
	// loc - location fron current worinking directory
	void addResourceLocation(const char* loc);

	Ogre::SceneNode* getPlayerSceneNode();
	
	
	void getMeshInformation(
		const Ogre::Mesh* const mesh,
		size_t& vertex_count,
		Ogre::Vector3*& vertices,
		size_t& index_count,
		unsigned long*& indices,
		const Ogre::Vector3& position,
		const Ogre::Quaternion& orient,
		const Ogre::Vector3& scale
	);

	void setupTestTrack();

	HWND* getHWND();
	
	void _setupSDL3(INT64 windowWidth, INT64 windowHeight, Ogre::String windowName, HWND* window);
	void _setupRTShader();
	void _loadResource();

	void Shutdown();

};

