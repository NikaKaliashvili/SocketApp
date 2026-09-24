#pragma once
#include "../socketApp.h"


LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Add new text to messages
void AddTextToMessages(const std::string& buffer, bool newLine = TRUE);

// Update's button text
void UpdatePropertyText(DWORD propertyId, std::string newText);