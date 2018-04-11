#pragma once
#if defined(CONSOLE_VIEW_BUILD)
#include <windows.h>

inline void gotoxy(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
inline void HideCursor() {
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO hCCI;
	GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	SetConsoleCursorInfo(hConsoleOut, &hCCI);
}
#endif