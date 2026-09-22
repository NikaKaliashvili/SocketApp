#pragma once
#include "../socketApp.h"


LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Add new text to messages
void AddTextToMessages(std::string buffer);

// Update's button text
void UpdatePropertyText(DWORD propertyId, std::string newText);