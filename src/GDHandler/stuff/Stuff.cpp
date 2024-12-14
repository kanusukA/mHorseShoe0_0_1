#include "Stuff.h"


void Stuff::setSceneNode(Ogre::SceneNode* scnNode) {
	sNode = scnNode;
}

void Stuff::setName(Ogre::String nm) {
	name = nm;
}

void Stuff::showRenderer(bool value)
{
	sNode->setVisible(value);
}


Ogre::Vector3 ktmPositionVec3(PxVec3 position) {
	return Ogre::Vector3(position.x, position.y, position.z);
}

Ogre::Quaternion ktmOrientation(PxQuat quat) {
	return Ogre::Quaternion(quat.w, quat.x, quat.y, quat.z);
}
