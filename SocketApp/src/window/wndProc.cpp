#pragma once
#include "../../include/socketApp.h"

void AddTextToMessages(const std::string& buffer, bool newLine)
{
    HWND hEdit = GetDlgItem(_hwnd, MESSAGE_TEXTS);

    int length = GetWindowTextLengthA(hEdit);
    SendMessageA(hEdit, EM_SETSEL, length, length);

    SendMessageA(
        hEdit,
        EM_REPLACESEL,
        FALSE,
        (LPARAM)buffer.c_str()
    );

    if (newLine)
    {
        SendMessageA(
            hEdit,
            EM_REPLACESEL,
            FALSE,
            (LPARAM)"\r\n"
        );
    }

    SendMessageA(hEdit, EM_SCROLLCARET, 0, 0);
}

void UpdatePropertyText(DWORD propertyId, std::string newText)
{
	SendDlgItemMessageA(_hwnd, propertyId, WM_SETTEXT, newText.length(), (LPARAM)newText.c_str());
}

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_CREATE:
			return WMCREATE(hwnd, wParam, lParam);

		case WM_CTLCOLORSTATIC:
			return WMCOLORSTATIC(hwnd, wParam, lParam);

		case WM_COMMAND:
			return WMCOMMAND(hwnd, wParam, lParam);

	}

	return DefWindowProcA(hwnd, msg, wParam, lParam);
}