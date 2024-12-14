#pragma once

#include <monster/Monster.h>
#include <kint/Kint.h>

using namespace physx;

class Stuff
{
public:

	Ogre::SceneNode* sNode;
	Ogre::String name;

	void setSceneNode(Ogre::SceneNode* scnNode);
	void setName(Ogre::String nm);

	void showRenderer(bool value);

	virtual void setPxRigidDynamic(PxRigidDynamic* dynActor) {};
	virtual void setPxRigidStatic(PxRigidStatic* staActor) {};

	virtual bool update(float deltaTime) { return true; };

};

struct StuffType {
	enum typeEnum
	{
		eRIGID_DYNAMIC,
		eRIGID_STATIC
	};
};

// Util functions
Ogre::Vector3 ktmPositionVec3(PxVec3 position);
Ogre::Quaternion ktmOrientation(PxQuat quat);

