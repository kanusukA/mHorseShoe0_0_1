#include "Monster.h"

//Monster::Monster(Ogre::String name)
//{
//	// Basic Ogre setup
//	OgreBites::ApplicationContext ctx("mOgreCtx");
//	ctx.initApp();
//
//	renderWindow = ctx.getRenderWindow();
//	oRoot = ctx.getRoot();
//	oScnManager = oRoot->createSceneManager();
//
//	// RTShader System
//	_setupRTShader();
//
//	// Overlay | TraySystem Setup
//	Ogre::OverlaySystem* overSys = ctx.getOverlaySystem();
//	oScnManager->addRenderQueueListener(overSys);
//
//	oTrayMan = new OgreBites::TrayManager(TRAY_SYSTEM_NAME, ctx.getRenderWindow());
//	ctx.addInputListener(oTrayMan);
//
//}


Monster::Monster(Ogre::Root* root, Ogre::RenderWindow* rWin, Ogre::OverlaySystem* overlay, int& _FPS)
{
	oRoot = root;
	renderWindow = rWin;

	oScnManager = root->createSceneManager();

	_setupRTShader();

	oScnManager->addRenderQueueListener(overlay);
	
	FPS = &_FPS;
}

void Monster::InitMonster(Ogre::ImGuiOverlay* imguiOverlay) {

	// FIX DEFAULT VALUES !!
	_setupSDL3(WINDOW_WIDTH,WINDOW_HEIGHT,"Psycho",getHWND());

	// Gui
	initGui(imguiOverlay);

}


Ogre::SceneNode* Monster::addCamera(Ogre::String camName, Ogre::Vector3 startPos)
{
	Ogre::SceneNode* camNode = oScnManager->getRootSceneNode()->createChildSceneNode("CAM_NODE");

	Ogre::Camera* cam = oScnManager->createCamera(camName);
	cam->setAutoAspectRatio(true);
	cam->setNearClipDistance(2);

	camNode->attachObject(cam);
	camNode->setPosition(startPos);

	renderWindow->addViewport(cam);

	

	return camNode;
}

void Monster::addGuiPlayerInfo(Ogre::Vector3* position, Ogre::Vector3* rotation)
{
	// ADD and SHOW Gui Status tab
	StatusTab(ImVec2(0, 0), FPS, position,rotation);
}

Ogre::SceneNode* Monster::loadMeshScnNode(Ogre::String scnNodeName, Ogre::String meshName)
{
	// if mesh exists

	Ogre::MeshPtr msh = Ogre::MeshManager::getSingleton().load(meshName, "Assets");
	
	Ogre::SceneNode* scnNode = oScnManager->getRootSceneNode()->createChildSceneNode(scnNodeName);
	scnNode->attachObject(oScnManager->createEntity(msh));

	// get mesh info test
	size_t vertex_count, index_count;
	Ogre::Vector3* vertices;
	unsigned long* indices;
	getMeshInformation(msh.get(), vertex_count, vertices, index_count, indices,scnNode->getPosition(),scnNode->getOrientation(),scnNode->getScale());

	std::cout << "\n Vertices : " << vertex_count;
	std::cout << "\n triangles : " << index_count / 3;

	return scnNode;
}

void Monster::update()
{
	updateGui();
}

//void Monster::showDebugLines(bool value)
//{
//	if (debugLineScnNode)
//	{
//		debugLineScnNode->setVisible(value);
//	}
//}

//void Monster::initDebugLines()
//{
//	debugLineScnNode = oScnManager->getRootSceneNode()->createChildSceneNode("Gizmoz");
//
//	visualManualObj = new Ogre::ManualObject("This_Object");
//	visualManualObj->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
//	visualManualObj->position(0, 0, 0);
//	visualManualObj->position(0, 1, 0);
//	visualManualObj->end();
//
//	debugLineScnNode->attachObject(visualManualObj);
//
//}
//
//void Monster::updateDebugLines(const physx::PxDebugLine* dbgLines, int nbLines)
//{
//	visualManualObj->beginUpdate(0);
//
//	for (int i = 0; i < nbLines; i++) {
//		//First Vertex
//		visualManualObj->position(dbgLines[i].pos0.x, dbgLines[i].pos0.y, dbgLines[i].pos0.z);
//		// Second Vertex
//		visualManualObj->position(dbgLines[i].pos1.x, dbgLines[i].pos1.y, dbgLines[i].pos1.z);
//	}
//	
//	visualManualObj->end();
//}
//
//void Monster::initDebugTriangles()
//{
//	debugTriangleScnNode = oScnManager->getRootSceneNode()->createChildSceneNode();
//	
//	debugTriangleObj = new Ogre::ManualObject("Triangle_Object");
//	debugTriangleObj->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);
//	debugTriangleObj->position(0, 0, 0);
//	debugTriangleObj->position(1, 2, 0);
//	debugTriangleObj->position(2, 0, 0);
//	debugTriangleObj->end();
//
//	debugTriangleScnNode->attachObject(debugTriangleObj);
//}
//
//void Monster::showDebugTriangles()
//{
//}
//
//void Monster::updateDebugTriangles(const physx::PxDebugTriangle* dbgTriangle, int nbTriangles)
//{
//	debugTriangleObj->beginUpdate(0);
//	for (int i = 0; i < nbTriangles; i++) {
//		debugTriangleObj->position(dbgTriangle[i].pos0.x, dbgTriangle[i].pos0.y, dbgTriangle[i].pos0.z);
//		debugTriangleObj->position(dbgTriangle[i].pos1.x, dbgTriangle[i].pos1.y, dbgTriangle[i].pos1.z);
//		debugTriangleObj->position(dbgTriangle[i].pos2.x, dbgTriangle[i].pos2.y, dbgTriangle[i].pos2.z);
//	}
//	debugTriangleObj->end();
//}

void Monster::addResourceLocation(const char* loc)
{
	try
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(loc, "FileSystem");
	}
	catch (const std::exception& exception)
	{
		std::cout << "Failed to load Monster ResourceLocation : " << exception.what();
	}
	
}

void Monster::preLoadMeshData()
{
	// Get Resource Data
	ResourceHandler::getSingleton()->initResourceCheck();

	// Add location to ResourceGroupManager
	
	addResourceLocation(ResourceHandler::getSingleton()->getRenderMeshLocation());
	addResourceLocation(ResourceHandler::getSingleton()->getColliderMeshLocation());
	

	// Get names of meshes
	std::vector<HorseMeshResource> hmr = ResourceHandler::getSingleton()->getMeshResources();
	preLoadRenderMeshes.resize(hmr.size());

	// FIx Error Here
	for (int i = 0; i < hmr.size(); i++) {
		// The File system followed by Resource Handler is not the same as followed by Ogre.
		// NOW FIX IT.
		/*preLoadRenderMeshes[i] = Ogre::MeshManager::getSingleton().load(hmr[i].Name,
			Ogre::ResourceGroupManager::getSingleton().DEFAULT_RESOURCE_GROUP_NAME);*/
	}
	
	
}

void Monster::getMeshInformation(
	const Ogre::Mesh* const mesh, 
	size_t& vertex_count, 
	Ogre::Vector3*& vertices, 
	size_t& index_count, 
	unsigned long*& indices, 
	const Ogre::Vector3& position, 
	const Ogre::Quaternion& orient, 
	const Ogre::Vector3& scale)
{
	bool added_shared = false;
	size_t current_offset = 0;
	size_t shared_offset = 0;
	size_t next_offset = 0;
	size_t index_offset = 0;

	vertex_count = index_count = 0;

	// Calculates How many vertices and indices are required
	for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i) {

		Ogre::SubMesh* subMesh = mesh->getSubMesh(i);

		if (subMesh->useSharedVertices) {
			if (!added_shared)
			{
				vertex_count += mesh->sharedVertexData->vertexCount;
				added_shared = true;
			}
		}
		else {
			vertex_count += subMesh->vertexData->vertexCount;
		}
		// Add indices
		index_count += subMesh->indexData->indexCount;
	}

	// Allocate space for vertices and indices
	vertices = new Ogre::Vector3[vertex_count];
	indices = new unsigned long[index_count];

	added_shared = false;

	// adding data to array
	for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i) {
		Ogre::SubMesh* subMesh = mesh->getSubMesh(i);

		Ogre::VertexData* vertex_data = subMesh->useSharedVertices ? mesh->sharedVertexData : subMesh->vertexData;

		if ((!subMesh->useSharedVertices) || (subMesh->useSharedVertices && !added_shared))
		{
			if (subMesh->useSharedVertices) {
				added_shared = true;
				shared_offset = current_offset;
			}

			const Ogre::VertexElement* posElem = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);

			Ogre::HardwareVertexBufferSharedPtr vbuf = vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());

			unsigned char* vertex = static_cast<unsigned char*>(vbuf.get()->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

			float* pReal;

			for (size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf.get()->getVertexSize()) {
				posElem->baseVertexPointerToElement(vertex, &pReal);
				Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);
				vertices[current_offset + j] = (orient * (pt * scale)) + position;
			}

			vbuf.get()->unlock();
			next_offset += vertex_data->vertexCount;
		}

		Ogre::IndexData* index_data = subMesh->indexData;
		size_t numTris = index_data->indexCount / 3;
		Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;

		bool use32bitindexes = (ibuf.get()->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

		unsigned long* pLong = static_cast<unsigned long*>(ibuf.get()->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);

		size_t offset = (subMesh->useSharedVertices) ? shared_offset : current_offset;

		if (use32bitindexes) {
			for (size_t k = 0; k < numTris * 3; ++k) {
				indices[index_offset++] = pLong[k] + static_cast<unsigned long>(offset);
			}
		}
		else {
			for (size_t k = 0; k < numTris * 3; ++k) {
				indices[index_offset++] = static_cast<unsigned long>(pShort[k]) +
					static_cast<unsigned long>(offset);
			}
		}

		ibuf.get()->unlock();
		current_offset = next_offset;

	}
}


void Monster::setupTestTrack()
{
	Ogre::Light* pLight = oScnManager->createLight("pLight", Ogre::Light::LT_POINT);
	pLight->setPowerScale(15);
	Ogre::SceneNode* pLightNode = oScnManager->getRootSceneNode()->createChildSceneNode("pLightNodeScn");
	pLightNode->attachObject(pLight);
	pLightNode->setPosition(50, 150, 50);

	//Ogre::ResourceGroupManager::getSingleton().setWorldResourceGroupName("Assets");
	//Ogre::SceneNode* scn = oScnManager->getRootSceneNode()->createChildSceneNode("test_track");
	//scn->loadChildren("test_track.scene");

}

HWND* Monster::getHWND()
{
	HWND* hwnd;
	renderWindow->getCustomAttribute("WINDOW", &hwnd);
	return hwnd;
}



void Monster::_setupSDL3(INT64 windowWidth, INT64 windowHeight, Ogre::String windowName,HWND* window) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_PropertiesID props = SDL_CreateProperties();
	SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, window);
	//DEPRICATED
	//SDL_SetProperty(props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, getHWND());
	SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, windowName.c_str());
	//NOTWORKING
	//SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, windowWidth);
	//SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, windowHeight);

	// SDL WINDOW
	sdlWindow = SDL_CreateWindowWithProperties(props);
	SDL_SetWindowSize(sdlWindow, windowWidth, windowHeight);

}

void Monster::_setupRTShader() {
	Ogre::RTShader::ShaderGenerator* rtGen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	rtGen->addSceneManager(oScnManager);
}


void Monster::_loadResource()
{

}

void Monster::Shutdown()
{
	
}
