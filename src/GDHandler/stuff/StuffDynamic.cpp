#include "StuffDynamic.h"


void StuffDynamic::setPxRigidDynamic(PxRigidDynamic* dynActor) {
	sActor = dynActor;
}

bool StuffDynamic::update(float deltaTime) {
	sNode->setPosition(ktmPositionVec3(sActor->getGlobalPose().p));
	sNode->setOrientation(ktmOrientation(sActor->getGlobalPose().q));
	return true;
}


