#include "../../include/socketApp.h"

static bool RegisterMainClass() {
	WNDCLASSEXA wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.lpszClassName = "NIKA_MAIN";
	wc.lpfnWndProc = WndProc;
	wc.hbrBackground = CreateSolidBrush(BG_COLOR);
	return RegisterClassExA(&wc);
}

Window::Window(std::string windowTitle, int x, int y, int w, int h) {
	// register class
	if (!RegisterMainClass()) {
		std::cout << "Class registration failed!" << std::endl;;
		return;
	}

	// create window
	if (CreateWindowExA(0, "NIKA_MAIN", windowTitle.c_str(), WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, x, y, w, h, 0, 0, 0, 0) == 0) {
		std::cout << "Window creation failed!" << std::endl;;
		return;
	}

	std::cout << "Initialized Window!" << std::endl;
	
}

void Window::HandleEvents()
{
	MSG msg;
	while (GetMessageA(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}
