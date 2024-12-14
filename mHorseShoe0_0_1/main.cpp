
#include <GDHandler/GDHandler.h>
#include <feel/Feel.h>

#include <cons.h>
#include <timer/glock.h>


// 16 millisec in each frame for 60FPS
const double MS_PER_FRAME = 16;

ResourceHandler* ResourceHandler::instancePtr = nullptr;

int main() {

	int fps = 1;

	OgreBites::ApplicationContext ctx(INSTANCE_NAME);
	ctx.initApp();

	// Ogre Overlay INIT
	Monster* monster = new Monster(ctx.getRoot(),ctx.getRenderWindow(), ctx.getOverlaySystem(),fps);

	Kint* kint = new Kint();
	IKEYS* inputKeys = nullptr;
	
	Ogre::Root* oRoot = monster->oRoot;

	monster->InitMonster(ctx.initialiseImGui());
	ctx.addInputListener(ctx.getImGuiInputListener());

	monster->setupTestTrack();

	//// Physics INIT
	kint = new Kint();
	kint->InitPhysics();

	//GDHANDLER
	GDHandler gdhandler = GDHandler( monster);
	inputKeys = gdhandler.keyHandler->inputKeys;

	gdhandler.addPlayerMovement(monster->addCamera("CAMERA_MAN", Ogre::Vector3(0, 10, 100)));

	// MAIN LOOP
	double startTime;
	double elapsed;
	double deltaTime;

	double lastTime = getCurrentTime();

	

	while (!inputKeys->Quit_KEY) {

		startTime = getCurrentTime();
		elapsed = startTime - lastTime;
		deltaTime = elapsed / 100;

		// Input Update
		gdhandler.updateGDHandler(deltaTime);

		// Physics Update
		kint->updatePhysics(deltaTime);

		// Renderer Update
		monster->update();
		oRoot->renderOneFrame();

		fps = 1000/(getCurrentTime() - startTime);

		lastTime = startTime;

		if (startTime + MS_PER_FRAME > getCurrentTime()) {
			Sleep(startTime + MS_PER_FRAME - getCurrentTime());
		}

		

	}

	// Shutdown
	kint->Shutdown();
	monster->Shutdown();

	std::cout << "HEllOS";

	
}

     

