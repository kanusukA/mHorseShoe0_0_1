#pragma once

#include "stuff/Stuff.h"
#include <iostream>

class Creator
{
	virtual void createStuffRigidDynamic(std::string name, Ogre::String meshName, RigidDynamicInfo* info);
	virtual void createStuffRigidDynamic(std::string name, Ogre::SceneNode* sNode, RigidDynamicInfo* info);

	virtual void createStuffRigidStatic(std::string name, Ogre::String meshName, PxTransform* trans, PxShape* shape);
};

