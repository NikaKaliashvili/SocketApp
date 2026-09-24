#include "../../../include/socketApp.h"

void DrawConnectHostSection(HWND hwnd, HFONT& codeFont) {
	CreateWindowExA(0, "button", "Connection", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 340, 20, 310, 135, hwnd, (HMENU)CONNECT_HOST_FRAME, 0, 0); // FRAME

	CreateWindowExA(0, "static", "IP: ", WS_VISIBLE | WS_CHILD, 350, 50, 30, 23, hwnd, (HMENU)CONNECT_HOST_IP_LABEL, 0, 0); // IP LABEL
	CreateWindowExA(0, "edit", "127.0.0.1", WS_VISIBLE | WS_CHILD, 410, 54, 150, 20, hwnd, (HMENU)CONNECT_HOST_IP_FIELD, 0, 0); // IP FIELD

	CreateWindowExA(0, "static", "PORT: ", WS_VISIBLE | WS_CHILD, 350, 85, 50, 20, hwnd, (HMENU)CONNECT_HOST_PORT_LABEL, 0, 0); // PORT LABEL
	CreateWindowExA(0, "edit", "5631", WS_VISIBLE | WS_CHILD, 410, 88, 150, 20, hwnd, (HMENU)CONNECT_HOST_PORT_FIELD, 0, 0); // PORT FIELD

	CreateWindowExA(0, "button", "Connect", WS_VISIBLE | WS_CHILD | BS_FLAT, 409, 120, 151, 25, hwnd, (HMENU)CONNECT_HOST_BUTTON, 0, 0); // Connect/Host

	// server/client
	CreateWindowExA(0, "button", 0, WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 565, 40, 75, 80, hwnd, (HMENU)CLIENT_SERVER_FRAME, 0, 0); // CLIENT/SERVER FRAME
	CreateWindowExA(0, "button", "Client", WS_VISIBLE | WS_CHILD | WS_GROUP | BS_AUTORADIOBUTTON, 572, 55, 60, 20, hwnd, (HMENU)CLIENT_SERVER_CLIENT, 0, 0); // Client radio
	CreateWindowExA(0, "button", "Server", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 572, 90, 62, 20, hwnd, (HMENU)CLIENT_SERVER_SERVER, 0, 0); // Server radio


	// set fonts
	SendDlgItemMessageA(hwnd, CONNECT_HOST_FRAME, WM_SETFONT, WPARAM(codeFont), 0); // frame
	SendDlgItemMessageA(hwnd, CONNECT_HOST_IP_LABEL, WM_SETFONT, WPARAM(codeFont), 0); // ip label
	SendDlgItemMessageA(hwnd, CONNECT_HOST_PORT_LABEL, WM_SETFONT, WPARAM(codeFont), 0); // port label
	SendDlgItemMessageA(hwnd, CONNECT_HOST_BUTTON, WM_SETFONT, WPARAM(codeFont), 0); // connect button
}

void DrawMessageSection(HWND hwnd, HFONT& codeFont) {
	CreateWindowExA(0, "button", "Message", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 20, 20, 305, 250, hwnd, (HMENU)MESSAGE_FRAME, 0, 0); // FRAME
	CreateWindowExA(0, "edit", 0, WS_VISIBLE | WS_CHILD | ES_READONLY | ES_MULTILINE | ES_AUTOVSCROLL, 30, 50, 245, 200, hwnd, (HMENU)MESSAGE_TEXTS, 0, 0); // TEXTS
	CreateWindowExA(0, "edit", "Type something", WS_VISIBLE | WS_CHILD, 21, 245, 214, 25, hwnd, (HMENU)MESSAGE_FIELD, 0, 0); // MESSAGE FIELD
	CreateWindowExA(0, "button", "Send", WS_VISIBLE | WS_CHILD | BS_FLAT, 275, 244, 50, 27, hwnd, (HMENU)MESSAGE_SEND, 0, 0); // SEND BUTTON
	CreateWindowExA(0, "button", "...", WS_VISIBLE | WS_CHILD | BS_FLAT, 235, 244, 40, 27, hwnd, (HMENU)MESSAGE_FILE_SEND, 0, 0); // SEND FILE BUTTON

	// set fonts
	SendDlgItemMessageA(hwnd, MESSAGE_FRAME, WM_SETFONT, WPARAM(codeFont), 0); // frame
	SendDlgItemMessageA(hwnd, MESSAGE_FIELD, WM_SETFONT, WPARAM(codeFont), 0); // field
	SendDlgItemMessageA(hwnd, MESSAGE_SEND, WM_SETFONT, WPARAM(codeFont), 0); // send
	SendDlgItemMessageA(hwnd, MESSAGE_FILE_SEND, WM_SETFONT, WPARAM(codeFont), 0); // send file
}

static void CreateChildren(HWND hwnd) {
	HFONT codeFont = CreateFontA(23, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Cascadia Code");
	DrawConnectHostSection(hwnd, codeFont);
	DrawMessageSection(hwnd, codeFont);
}

LRESULT WMCREATE(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	_hwnd = hwnd;
	_hStaticBg = CreateSolidBrush(BG_COLOR);

	CreateChildren(hwnd);
	return 0;
}