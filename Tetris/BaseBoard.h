#ifndef BaseBoardH
#define BaseBoardH

#include <string>
#include <fstream>
#include <ctime>
using namespace std;

class BaseBoard {
protected:
public:
	BaseBoard();
	unsigned char map[10][20]; /* lines [0-9][20-22] are buffer */
	virtual bool IsLost(); /* check is game possible */
	virtual void DelLine(int Y);  /* delete line at Y position */
	virtual void Draw() = 0;
	virtual void DrawFullLine(int y) = 0;
	int CheckLine();   /* returns amount of deleted lines */
	void Save(string filename); //сохранить состояние доски в файл
	void Load(string filename); //считать состояние доски из файла
};

#endif
