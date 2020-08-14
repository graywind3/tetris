#include "Figure.h"

/* == Data == */




void Figure::setpos(int x, int y) { /* set cursor position on the screen at x,y */
	COORD C = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), C);
}

void Figure::rect(int x, int y, int color) { /* put a 1x1 rectangle at x,y */
	if (x < 0 || y < 0) return;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD cWritten;
	const char fill_char = ' ';
	SetConsoleTextAttribute(h, color);
	setpos(x, y);
	WriteFile(h, &fill_char, 1, &cWritten, NULL);
	SetConsoleTextAttribute(h, 0);
}
/* squre at x,y */
void Figure::square(int x, int y, int color) { 
	rect(2 * x, y, color);
	rect(2 * x + 1, y, color);
}



void Figure::Draw() {
	for (int y = CurFigY; y < CurFigY + 4; y++) {
		for (int x = CurFigX; x < CurFigX + 4; x++) {
			if (figure[x - CurFigX][y - CurFigY])
				/* if ceil in figure is black that means that it is clear ceil */
				square(10 + x, y, CurFigType);
		}
	}
};

void Figure::NextFigure() {
	SetConsoleTextAttribute(h, 0);
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			square(x + 1, y + 4, NextFigType * (int)_next_fig[x][y]);
		}
	}
};









