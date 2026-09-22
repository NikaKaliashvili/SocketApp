#pragma once
#include "../../include/socketApp.h"

void AddTextToMessages(std::string buffer) {
	SendDlgItemMessageA(_hwnd, MESSAGE_TEXTS, EM_SETSEL, -1, 1);
	SendDlgItemMessageA(_hwnd, MESSAGE_TEXTS, EM_REPLACESEL, FALSE, (LPARAM)buffer.c_str());
	SendDlgItemMessageA(_hwnd, MESSAGE_TEXTS, EM_REPLACESEL, FALSE, (LPARAM)"\r\n");
}

void UpdatePropertyText(DWORD propertyId, std::string newText)
{
	SendDlgItemMessageA(_hwnd, propertyId, WM_SETTEXT, newText.length(), (LPARAM)newText.c_str());
}

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {

		case WM_CREATE:
			return WMCREATE(hwnd, wParam, lParam);

		case WM_CTLCOLORSTATIC:
			return WMCOLORSTATIC(hwnd, wParam, lParam);

		case WM_COMMAND:
			return WMCOMMAND(hwnd, wParam, lParam);

	}

	return DefWindowProcA(hwnd, msg, wParam, lParam);
}