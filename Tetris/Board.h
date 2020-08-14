#ifndef BoardH
#define BoardH

#include <stdio.h>
#include <Windows.h>

#include "BaseBoard.h"

class ConsoleBoard: public BaseBoard {
	void rect(int x, int y, int color);  /* put a 1x1 rectangle at x,y */
	void square(int x, int y, int color);  /* squre at x,y */
	void setpos(int x, int y);  /* set cursor position on the screen at x,y */

public:
	ConsoleBoard() : BaseBoard() {};
	void Draw();
	void DrawFullLine(int y);
};

#endif
