#ifndef BaseFigureH
#define BaseFigureH

#include "BaseBoard.h"
#include <Windows.h>

class BaseFigure {
protected:
	/* list of figyres */
	bool __Fig0[4][4] = {
		{ 0, 0, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 }
	};

	bool __Fig1[4][4] = {
		{ 0, 1, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 }
	};

	bool __Fig2[4][4] = {
		{ 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 }
	};


	bool __Fig3[4][4] = {
		{ 0, 1, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 0 }
	};


	bool __Fig4[4][4] = {
		{ 0, 0, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 }
	};

	bool __Fig5[4][4] = {
		{ 0, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 0 }
	};

	bool __Fig6[4][4] = {
		{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 }
	};

	bool figure[4][4];
	int  CurFigType;

	bool  _next_fig[4][4];
	int  NextFigType, NextFigID;

public:

	int  CurFigX, CurFigY; /* coord of up left corner of figure */
	BaseFigure();

	void Rotate(const BaseBoard& b);
	void ShiftRight(const BaseBoard& b);
	void ShiftLeft(const BaseBoard& b);   /* shift current figure left */
	bool ShiftDown(const BaseBoard& b);  /* return opportunity shifting down current figure, if possible shift */
	void FigCpy(bool a[4][4], const bool b[4][4]);
	void Generate(void);
	void DrawFigOnMap(BaseBoard& b);
	virtual void Draw() = 0;
	virtual void NextFigure() = 0;
	void Save(string filename);
	void Load(string filename);
};

#endif // !BaseFig

