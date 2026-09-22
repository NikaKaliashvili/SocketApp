#pragma once
#include "../socketApp.h"

class Window {
public:
	// Constructor for initializing window
	Window(std::string windowTitle, int x, int y, int w, int h);
	
	// Handles window events
	void HandleEvents();
};