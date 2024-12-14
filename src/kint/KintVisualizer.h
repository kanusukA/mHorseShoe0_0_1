#pragma once

#include <PxPhysicsAPI.h>

#include <iostream>

class KintVisualizer
{
public:

	void visualizeRenderBufferPoints(const physx::PxDebugPoint* dbgPoints, physx::PxU32 nbPoints);
	void visualizeRenderBufferLines(const physx::PxDebugLine* dbgLines, physx::PxU32 nbLines);

};

