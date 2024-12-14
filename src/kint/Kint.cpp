#include "Kint.h"

PxReal pAccumulator = 0.0f;
PxReal pStepSize = 1.0f / 60.0f;

void Kint::InitPhysics() {

	pFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, pAllocator, pErrorCallback);

	pPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *pFoundation, PxTolerancesScale(), true);

	PxSceneDesc sceneDesc(pPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	pDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = pDispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;

	pScene = pPhysics->createScene(sceneDesc);

	pMaterial = pPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	setGlobalVisualization(true);

}

void Kint::Shutdown() {
	pPhysics->release();
	pFoundation->release();
}

bool Kint::updatePhysics(float deltaTime) {

	pAccumulator += deltaTime;

	if (pAccumulator < pStepSize) {
		return false;
	}
		
	pAccumulator -= pStepSize;

	pScene->simulate(pStepSize);
	pScene->fetchResults(true);

}

PxRigidDynamic* Kint::createRigidBody(std::string name,PxTransform transfrom, PxReal mass, PxGeometry* geo) {
	PxMaterial* mat = pPhysics->createMaterial(0.5f, 0.5f, 0.5f);
	PxShape* shape = pPhysics->createShape(*geo, *mat);

	shape->setFlag(PxShapeFlag::eVISUALIZATION, true);

	PxRigidDynamic* dyn = PxCreateDynamic(*pPhysics, transfrom, *shape, mass);
	dyn->setName(name.c_str());
	pScene->addActor(*dyn);

	return dyn;

}



PxRigidStatic* Kint::createStaticBody(std::string name,PxTransform transfrom, PxGeometry* geo ) {
	PxMaterial* mat = pPhysics->createMaterial(0.5f, 0.5f, 0.5f);
	PxShape* shape = pPhysics->createShape(*geo, *mat);
	
	shape->setFlag(PxShapeFlag::eVISUALIZATION, true);

	PxRigidStatic* sta = PxCreateStatic(*pPhysics, transfrom, *shape);
	sta->setName(name.c_str());
	pScene->addActor(*sta);

	return sta;
}

PxTriangleMesh* Kint::createTriangleCollisionMesh(int nbVert, PxVec3* vertices, int nbIndices, long* indices)
{
	// Triangle Data

	PxTriangleMeshDesc meshDesc;
	meshDesc.points.count = nbVert;
	meshDesc.points.stride = sizeof(PxVec3);
	meshDesc.points.data = vertices;

	meshDesc.triangles.count = nbIndices / 3;
	meshDesc.triangles.stride = 3 * sizeof(PxU32);
	meshDesc.triangles.data = indices;

	PxTolerancesScale scale;
	PxCookingParams params(scale);

	return PxCreateTriangleMesh(params, meshDesc);

}

const PxDebugLine* Kint::getDebugLines()
{
	return pScene->getRenderBuffer().getLines();
}

PxU32 Kint::getNbDebugLine()
{
	std::cout << "\nLines : " << pScene->getRenderBuffer().getNbLines();
	return pScene->getRenderBuffer().getNbLines();
	
}

const PxDebugTriangle* Kint::getDebugTriangles()
{
	return pScene->getRenderBuffer().getTriangles();
}

PxU32 Kint::getNbDebugTriangles()
{
	std::cout << "\nTriangles : " << pScene->getRenderBuffer().getNbTriangles();
	return pScene->getRenderBuffer().getNbTriangles();
}

void Kint::setGlobalVisualization(bool value)
{
	if (value)
	{
		// SETS VISUALIZATION OF GLOBAL OBJECTS
		// USE CULLING_BOX TO SET A SMALLER RADIUS OF VISUALIZATION
		pScene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
		// GET COLLISION EDGES OF ACTIVE OBJECTS
		pScene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_DYNAMIC, 1.0f);
	}
	else {
		// POSITIVE VALUE - TURE , NEGATIVE VALUE - FALSE
		pScene->setVisualizationParameter(PxVisualizationParameter::eSCALE, -1.0f);
	}
	

}

