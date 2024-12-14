#pragma once

#include <SDL3/SDL.h>


struct MOUSEIN {

	int MouseXPer = 0;
	int MouseYPer = 0;

	double MouseXrel = 0.0f;
	double MouseYrel = 0.0f;

};

struct IKEYS {

	

	bool MouseLeft_KEY = false;
	bool MouseRight_KEY = false;
	bool MouseMiddle_KEY = false;

	bool Up_KEY = false;
	bool Down_KEY = false;
	bool Left_KEY = false;
	bool Right_KEY = false;

	bool Sprint_KEY = false;
	bool Action_KEY = false;

	bool Quit_KEY = false;

	bool Ctrl_KEY = false;
	bool Alt_Key = false;

	bool consolMode = false;


};

struct KEYBINDS {

	int UP_KEY = SDLK_UP;
	int DOWN_KEY = SDLK_DOWN;
	int LEFT_KEY = SDLK_LEFT;
	int RIGHT_KEY = SDLK_RIGHT;

	int S_UP_KEY = SDLK_W;
	int S_DOWN_KEY = SDLK_S;
	int S_LEFT_KEY = SDLK_D;
	int S_RIGHT_KEY = SDLK_A;

	int SPRINT_KEY = SDLK_LSHIFT;
	int QUIT_KEY = SDLK_ESCAPE;
	int ACTION_KEY = SDLK_E;

	int CONSOL_KEY = SDLK_C;

	// HELD CTRL
	int HIDE_MOUSE_KEY = SDLK_G;

	//DEBUG
	int GRAB_MOUSE_KEY = SDLK_M;

};

struct WINDOW_UTILS {
	int WINDOW_WIDTH = 0;
	int WINDOW_HEIGHT = 0;
};



class KeyHandler {
public:

	IKEYS* inputKeys = new IKEYS();
	MOUSEIN* mInput = new MOUSEIN();
	KEYBINDS* keyBinds = new KEYBINDS();
	WINDOW_UTILS* winUtils = new WINDOW_UTILS();

	void setInputKeys(IKEYS* inKeys);

	// IMPLEMENT IN FUTURE

	/*void setKeyBinds(KEYBINDS* kBinds);
	void setKeyBinds(int key, int SDLK);

	void saveBinds();
	void loadBinds();*/
	

};