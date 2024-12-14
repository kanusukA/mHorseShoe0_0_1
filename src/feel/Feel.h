#pragma once


#include "KeyHandler.h"
#include <Windows.h>
#include <iostream>


// Feel class handles all the userInput obtained from SDL.
// MUST HAVE INITALIZED AND RUNNING SDL3.
class Feel
{
public:
	// INITIALIZES INPUT HANDLER. CREATES NEW BINDINGS.
	void initFeel(SDL_Window* sdlWindow);
	

	KeyHandler* keyHandler;
	SDL_Window* window = NULL;

	void updateInput(float deltaTime);

	void hideMouse();
	void showMouse();

	bool mouseHidden = false;

	// GDHANDLER
	virtual void windowSizeChanged() {};
	virtual void showGuiAddTab() {};
	
	void consoleMode(bool state);

};

