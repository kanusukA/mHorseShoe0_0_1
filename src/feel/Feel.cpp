#include "Feel.h"


void Feel::initFeel(SDL_Window* sdlWindow)
{
	window = sdlWindow;
	SDL_SetWindowMouseGrab(window, true);

	keyHandler = new KeyHandler();
}

void Feel::hideMouse() {
	ShowCursor(false);
	SDL_SetWindowRelativeMouseMode(window,true);
	mouseHidden = true;
}

void Feel::showMouse() {
	ShowCursor(true);
	SDL_SetWindowRelativeMouseMode(window, false);
	mouseHidden = false;
	
}

void Feel::consoleMode(bool state)
{
	SDL_SetWindowMouseGrab(window,!state);
	ShowCursor(state);
	keyHandler->inputKeys->consolMode = false;
}


void Feel::updateInput(float deltaTime) {

	SDL_Event event;

	keyHandler->mInput->MouseXrel = 0;
	keyHandler->mInput->MouseYrel = 0;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_EVENT_WINDOW_RESIZED) {
			SDL_GetWindowSize(window, &keyHandler->winUtils->WINDOW_WIDTH, &keyHandler->winUtils->WINDOW_HEIGHT);
		}
		
		// Quit Check
		if (event.type == SDL_EVENT_QUIT || event.key.key == SDLK_ESCAPE) {
			keyHandler->inputKeys->Quit_KEY = true;
		}
		
		// Mouse
		if (event.type == SDL_EVENT_MOUSE_MOTION) {

			keyHandler->mInput->MouseXPer = event.motion.x;
			keyHandler->mInput->MouseYPer = event.motion.y;

			keyHandler->mInput->MouseXrel = event.motion.xrel;
			keyHandler->mInput->MouseYrel = event.motion.yrel;

		}

		// Key Down
		if (event.type == SDL_EVENT_KEY_DOWN)
		{
			if (event.key.key == keyHandler->keyBinds->UP_KEY || event.key.key == keyHandler->keyBinds->S_UP_KEY)
			{
				keyHandler->inputKeys->Up_KEY = true;
			}
			if (event.key.key == keyHandler->keyBinds->DOWN_KEY || event.key.key == keyHandler->keyBinds->S_DOWN_KEY)
			{
				keyHandler->inputKeys->Down_KEY = true;
			}
			if (event.key.key == keyHandler->keyBinds->LEFT_KEY || event.key.key == keyHandler->keyBinds->S_LEFT_KEY)
			{
				keyHandler->inputKeys->Left_KEY = true;
			}
			if (event.key.key == keyHandler->keyBinds->RIGHT_KEY || event.key.key == keyHandler->keyBinds->S_RIGHT_KEY)
			{
				keyHandler->inputKeys->Right_KEY = true;
			}

			if (event.key.key == keyHandler->keyBinds->ACTION_KEY)
			{
				keyHandler->inputKeys->Action_KEY = true;
			}
			if (event.key.key == keyHandler->keyBinds->SPRINT_KEY)
			{
				keyHandler->inputKeys->Sprint_KEY = true;
			}

			// HELD CTRL
			if (event.key.key == SDLK_LCTRL) {
				keyHandler->inputKeys->Ctrl_KEY = true;
			}
			

		}
		
		// Key Up
		if (event.type == SDL_EVENT_KEY_UP)
		{
			
			if (event.key.key == keyHandler->keyBinds->CONSOL_KEY) {
				keyHandler->inputKeys->consolMode = true;
			}

			if (event.key.key == keyHandler->keyBinds->UP_KEY || event.key.key == keyHandler->keyBinds->S_UP_KEY)
			{
				
				keyHandler->inputKeys->Up_KEY = false;
			}
			if (event.key.key == keyHandler->keyBinds->DOWN_KEY || event.key.key == keyHandler->keyBinds->S_DOWN_KEY)
			{
				keyHandler->inputKeys->Down_KEY = false;
			}
			if (event.key.key == keyHandler->keyBinds->LEFT_KEY || event.key.key == keyHandler->keyBinds->S_LEFT_KEY)
			{
				keyHandler->inputKeys->Left_KEY = false;
			}
			if (event.key.key == keyHandler->keyBinds->RIGHT_KEY || event.key.key == keyHandler->keyBinds->S_RIGHT_KEY)
			{
				keyHandler->inputKeys->Right_KEY = false;
			}

			if (event.key.key == keyHandler->keyBinds->ACTION_KEY)
			{
				showGuiAddTab();
				keyHandler->inputKeys->Action_KEY = false;
			}
			if (event.key.key == keyHandler->keyBinds->SPRINT_KEY)
			{
				keyHandler->inputKeys->Sprint_KEY = false;
			}

			// CTRL
			if (event.key.key == SDLK_LCTRL) {
				keyHandler->inputKeys->Ctrl_KEY = false;
			}
			
			
			if (event.key.key == keyHandler->keyBinds->HIDE_MOUSE_KEY && keyHandler->inputKeys->Ctrl_KEY) {
				
				if (mouseHidden) {
					showMouse();
				}
				else
				{
					hideMouse();
				}
			}
			if (event.key.key == keyHandler->keyBinds->GRAB_MOUSE_KEY && keyHandler->inputKeys->Ctrl_KEY) {
				SDL_SetWindowMouseGrab(window, !SDL_GetWindowMouseGrab(window));
			}

		}




	}

}