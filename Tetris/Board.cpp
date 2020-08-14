#include "Board.h"


void ConsoleBoard::rect(int x, int y, int color) { /* put a 1x1 rectangle at x,y */
	if (x < 0 || y < 0) return;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD cWritten;
	const char fill_char = ' ';
	SetConsoleTextAttribute(h, color);
	setpos(x, y);
	WriteFile(h, &fill_char, 1, &cWritten, NULL);
	SetConsoleTextAttribute(h, 0);
}

void ConsoleBoard::square(int x, int y, int color) { /* squre at x,y */
	rect(2 * x, y, color);
	rect(2 * x + 1, y, color);
}

void ConsoleBoard::setpos(int x, int y) { /* set cursor position on the screen at x,y */
	COORD C = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), C);
}

void ConsoleBoard::Draw() {
	/* = draw map = */
	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 10; x++) {
			square(10 + x, y, map[x][y]);
		}
	}
};



void ConsoleBoard::DrawFullLine(int y) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	setpos(20, y);
	printf("                    ");
	Sleep(50);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
};
