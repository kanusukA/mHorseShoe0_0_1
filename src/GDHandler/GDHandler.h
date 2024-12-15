#pragma once


#include "stuff/StuffDynamic.h"
#include "stuff/StuffStatic.h"

#include <feel/Feel.h>
#include <feel/playerMovement.h>

#include <Gui/Gui.h>

class GDHandler : public Feel , public Kint
{
public:

	GDHandler( Monster* renderer);

	Monster* monster;

	PlayerSubject* playerSubject = nullptr;

	std::vector<StuffDynamic*> sDynColl;
	std::vector<StuffStatic*> sStaticColl;

	void addPlayerNode();

	// FEEL
	void windowSizeChanged() override;
	void showGuiAddTab() override;


	// Creates SceneNode Based on the name and Mesh.
	// If PhysicsType : eRIGID_DYNAMIC the same mesh is used for collision.
	// NOTE : SHAPE IS NOT CONSIDERED IN THE INFO.
	void createStuffRigidDynamic(std::string name, Ogre::String meshName, PxTransform position, PxReal mass, PxGeometry* geo);
	void createStuffRigidDynamic(std::string name, Ogre::SceneNode* sNode, PxTransform position, PxReal mass, PxGeometry* geo);

	void createStuffRigidStatic(std::string name, Ogre::String meshName, PxTransform position, PxGeometry* geo);
	void createStuffRigidStatic(std::string name, Ogre::SceneNode* sNode, PxTransform position, PxGeometry* geo);

	void updateGDHandler(float deltaTime);

	// GDHANDLER (KINT) -> MONSTER STORAGE OF DATA
	//void addVisualShape();

	void _setupGround();
	void _updatePlayerPrameters(float deltaTime);
	void _updateStuffs(float deltaTime);

};

