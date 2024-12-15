#include "GDHandler.h"

// Add newly made player Subject and observers
// Get this shit working

GDHandler::GDHandler(Monster* renderer) {
	
	monster = renderer;

	// PRE MESH LOADING
	// Load meshs in ogre3d
	monster->preLoadMeshData();


	// FEELS
	initFeel(monster->sdlWindow);

	_setupGround();

}

void GDHandler::addPlayerNode()
{
	if (this->playerSubject == nullptr) {
		this->playerSubject = new PlayerSubject(monster->getPlayerSceneNode());
	}
	
	PlayerObserver* playerObserver = new PlayerObserver(*this->playerSubject);
	// Show Gui Player info
	monster->setPlayerObserver(playerObserver);
	
}


// resize things not resizing themselves
void GDHandler::windowSizeChanged()
{
	// TODO
}

// FEEL -> GHANDLER -> MONSTER / GUI
void GDHandler::showGuiAddTab()
{
	monster->ShowADDTab(true);
}


//bool GDHandler::addObject()
//{
//	if (ap->type == phyType::DYNAMIC) {
//
//		PxTransform transform = PxTransform(PxVec3(ap->pos[0], ap->pos[1], ap->pos[2]));
//		PxGeometry* geo = new PxBoxGeometry(PxVec3(ap->c_size[0], ap->c_size[1], ap->c_size[2]));
//
//		createStuffRigidDynamic(*ap->add_name,*ap->msh_name,transform,*ap->mass,geo);
//
//		addVisualShape();
//		return true;
//		
//	}
//	else if (ap->type == phyType::STATIC)
//	{
//		PxTransform transform = PxTransform(PxVec3(ap->pos[0], ap->pos[1], ap->pos[2]));
//		PxGeometry* geo = new PxBoxGeometry(PxVec3(ap->c_size[0], ap->c_size[1], ap->c_size[2]));
//
//		createStuffRigidStatic(*ap->add_name, *ap->msh_name, transform, geo);
//
//		return true;
//
//	}
//	else {
//		// MESH INSTANCE 
//		// TODO
//	}
//
//	return false;
//}


// Transfer into Stuff
void GDHandler::createStuffRigidDynamic(std::string name, Ogre::String meshName, PxTransform position, PxReal mass, PxGeometry* geo)
{
	StuffDynamic* sDyn = new StuffDynamic();
	sDyn->setPxRigidDynamic(createRigidBody(name, position, mass, geo));
	sDyn->setSceneNode(monster->loadMeshScnNode(name, meshName));

	sDynColl.push_back(sDyn);
}
void GDHandler::createStuffRigidDynamic(std::string name, Ogre::SceneNode* sNode, PxTransform position, PxReal mass, PxGeometry* geo)
{
	StuffDynamic* sDyn = new StuffDynamic();
	sDyn->setPxRigidDynamic(createRigidBody(name, position, mass, geo));
	sDyn->setSceneNode(sNode);

	sDynColl.push_back(sDyn);
}


void GDHandler::createStuffRigidStatic(std::string name, Ogre::String meshName, PxTransform position, PxGeometry* geo)
{
	StuffStatic* sStatic = new StuffStatic();
	sStatic->setPxRigidStatic(createStaticBody(name, position, geo));
	sStatic->setSceneNode(monster->loadMeshScnNode(name, meshName));

	sStaticColl.push_back(sStatic);
}
void GDHandler::createStuffRigidStatic(std::string name, Ogre::SceneNode* sNode, PxTransform position, PxGeometry* geo)
{
	StuffStatic* sStatic = new StuffStatic();
	sStatic->setPxRigidStatic(createStaticBody(name, position, geo));
	sStatic->setSceneNode(sNode);

	sStaticColl.push_back(sStatic);
}


void GDHandler::updateGDHandler(float deltaTime)
{
	updateInput(deltaTime);

	_updatePlayerPrameters(deltaTime);

	_updateStuffs(deltaTime);

}


void GDHandler::_setupGround()
{
	// Ground
	PxTransform transform = PxTransform(PxVec3(0, 0, 0));
	PxGeometry* geo = new PxBoxGeometry(PxVec3(100, 10, 100));

	Ogre::SceneNode* groundNode = monster->loadMeshScnNode("Ground_S_Node", "Cube.001.mesh");
	groundNode->setScale(Ogre::Vector3(100, 1, 100));

	createStuffRigidStatic("Ground", groundNode, transform, geo);
}

void GDHandler::_updatePlayerPrameters(float deltaTime)
{
	// PLAYER MOVEMENT
	// Updates the player Scenen node set in the moster player Node
	// Updates the playerSubject which in turn updates all the assigned Observers
	if (playerSubject != nullptr && mouseHidden) {
		updateRotation(keyHandler->mInput, deltaTime, playerSubject);
		updatePosition(keyHandler->inputKeys, deltaTime, playerSubject);
	}

}

void GDHandler::_updateStuffs(float deltaTime)
{
	if (!sDynColl.empty()) {
		for (int i = 0; i < sDynColl.size(); i++) {
			sDynColl[i]->update(deltaTime);
		}
	}
}
















