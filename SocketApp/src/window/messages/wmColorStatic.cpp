#include "../../../include/socketApp.h"

LRESULT WMCOLORSTATIC(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	HDC hdc = (HDC)wParam;

	SetBkColor(hdc, BG_COLOR);
	SetTextColor(hdc, RGB(255, 255, 255));
	return (LRESULT)_hStaticBg;
}