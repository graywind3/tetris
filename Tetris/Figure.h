#ifndef FigureH
#define FigureH

#include <ctime>
#include "BaseFigure.h"


class Figure: public BaseFigure {
	HANDLE h;
	void setpos(int x, int y);
	void rect(int x, int y, int color);  /* put a 1x1 rectangle at x,y */
	void square(int x, int y, int color);  /* squre at x,y */

public:
	Figure() : BaseFigure() {
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	};

	void Draw();
	void NextFigure();
};

#endif
