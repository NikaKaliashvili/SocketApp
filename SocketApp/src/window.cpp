#include <iostream>
#include "../include/window/window.h"
#include "../include/window/wndProc.h"

static bool RegisterMainClass() {
	WNDCLASSEXA wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.lpszClassName = "NIKA_MAIN";
	wc.lpfnWndProc = WndProc;
	return RegisterClassExA(&wc);
}

Window::Window(std::string windowTitle, int x, int y, int w, int h) {
	// register class
	if (!RegisterMainClass) {
		std::cout << "Class registration failed!";
		return;
	}

	// create window
	if (!CreateWindowExA(0, "NIKA_MAIN", windowTitle.c_str(), WS_VISIBLE | WS_OVERLAPPEDWINDOW, x, y, w, h, 0, 0, 0, 0)) {
		std::cout << "Window creation failed!";
		return;
	}
	
}