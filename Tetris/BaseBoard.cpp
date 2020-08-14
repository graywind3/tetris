#include "BaseBoard.h"

BaseBoard::BaseBoard() {
	srand(time(NULL));
	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 20; y++)
			map[x][y] = 0;
}

bool BaseBoard::IsLost() { /* check is game possible */
	int x, y;
	for (x = 3; x < 7; x++)
		if (map[x][0])
			return true;
	return false;
}

void BaseBoard::DelLine(int Y) { /* delete line at Y position */
	int x, y;
	for (x = 0; x < 10; x++) {
		for (y = Y; y > 0; y--) {
			map[x][y] = map[x][y - 1];
		}
	}
	for (x = 0; x < 10; x++)
		map[x][0] = 0;
}

int BaseBoard::CheckLine() {  /* returns amount of deleted lines */
	int x, y, lines = 0;
	bool full;
	for (y = 0; y < 20; y++) {
		full = true;
		for (x = 0; x < 10; x++)
			if (!map[x][y]) {
				full = false;
				break;
			}
		if (full) {
			lines++;

			DrawFullLine(y);
			DelLine(y);
		}
	}
	return lines;
}

//сохранить состояние доски в файл
void BaseBoard::Save(string filename) {
	ofstream out(filename.c_str(),
		ios::binary);
	//unsigned char map[10][20];
    //...
	int sz = sizeof(unsigned char);
	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 20; y++)
	        out.write((char*)&map[x][y], sz);
	out.close();
};

//считать состояние доски из файла
void BaseBoard::Load(string filename) {
	ifstream in(filename.c_str(),
		ios::binary);

	//проверка: если по какой-либо причине поток
	//для работы с файлом не смог создастся (самая распрастраненная причина -
	//отсутствие файла с именем filename)
	if (!in)
		return; //то просто выходим из метода

	int sz = sizeof(unsigned char);
	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 20; y++)
			in.read((char*)&map[x][y], sz);

	in.close();
};


