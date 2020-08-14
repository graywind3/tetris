#include "BaseFigure.h"

BaseFigure::BaseFigure() {

	//for (int i=0; i)
	figure[4][4] = {};

	CurFigX = 3;
	CurFigY = -3; /* coord of up left corner of figure */
	CurFigType = 0;
	NextFigID = rand() % 7 + 1;

}

void BaseFigure::Rotate(const BaseBoard& b) { /* rotate current figure */
	if (CurFigType == (BACKGROUND_INTENSITY | BACKGROUND_RED)) return;
	int x, y, emptylines = 0;
	bool is3x3 = true, buffer[4][4] = {};
	/* = if figure isn`t 4x4 or 2x2 but 3x3 = */
	for (y = 0; y < 4; y++)
		if (figure[3][y])
			is3x3 = false;
	for (x = 0; x < 4; x++)
		if (figure[x][3])
			is3x3 = false;
	/* = ================================== = */
	if (is3x3) {
		for (x = 0; x < 3; x++)
			for (y = 0; y < 3; y++)
				buffer[x][y] = figure[y][2 - x];
	}
	else {
		for (x = 0; x < 4; x++)
			for (y = 0; y < 4; y++)
				buffer[x][y] = figure[y][3 - x];
	}
	/* = can we rotate?                     = */
	for (x = 0; x < 4; x++) {
		for (y = 0; y < 4; y++) {
			if (buffer[x][y] && b.map[CurFigX + x][CurFigY + y])
				return;
		}
	}
	/* = ================================== = */
	/* = corner? = */
	for (x = 0; x < 4; x++) {
		for (y = 0; y < 4; y++) {
			if (buffer[x][y] && (CurFigX + x > 9 || CurFigY + y > 19))
				return;
		}
	}
	/* = ======= = */
	for (x = 0; x < 4; x++)
		for (y = 0; y < 4; y++)
			figure[x][y] = buffer[x][y];
}

void BaseFigure::ShiftRight(const BaseBoard& b) { /* shift current figure right */
	int x, y, lastline = 3; /* last empty vertical */
	bool empty = true, possible = true;
	for (x = 3; x > -1; x--) {
		for (y = 0; y < 4; y++)
			if (figure[x][y])
				empty = false;
		if (empty) lastline--;
	}
	if (CurFigX + 3 != 9)
		for (x = 0; x < 4; x++)
			for (y = CurFigY; y < CurFigY + 4; y++)
				if (figure[x][y - CurFigY] && b.map[CurFigX + x + 1][y])
					possible = false;

	if (CurFigX < 9 - lastline && possible)
		CurFigX++;
}



void BaseFigure::ShiftLeft(const BaseBoard& b) { /* shift current figure left */
	int x, y, lastline = 0; /* first empty vertical */
	bool empty = true, possible = true;
	for (x = 0; x < 4; x++) {
		for (y = 0; y < 4; y++)
			if (figure[x][y])
				empty = false;
		if (empty) lastline++;
	}
	if (CurFigX > 0)
		for (x = 0; x < 4; x++)
			for (y = CurFigY; y < CurFigY + 4; y++)
				if (figure[x][y - CurFigY] && b.map[CurFigX - 1 + x][y])
					possible = false;

	if (CurFigX > 0 - lastline && possible)
		CurFigX--;
}


bool BaseFigure::ShiftDown(const BaseBoard& b) { /* return opportunity shifting down current figure, if possible shift */
	bool empty = true, possible = true;
	int x, y, emptylines = 0; /* so we should check last line of "figure" */
	for (y = 3; y > -1; y--) {
		for (x = 0; x < 4; x++) {
			if (figure[x][y]) {
				empty = false;
				break;
			}
		}
		if (!empty) break;
		emptylines++;
	}
	for (y = 0; y < 4; y++)
		for (x = CurFigX; x < CurFigX + 4; x++)
			if (CurFigY >= -1) /* else we will can compare with map[x][CurFigY+y+1] (map[x][y-2]) and y < 2 it will be last 19`th line */
				if (figure[x - CurFigX][y] && b.map[x][CurFigY + y + 1]) {
					possible = false;
					break;
				}
	if (CurFigY < 16 + emptylines && possible) /* 19 - emptylines */
		CurFigY++;
	else return false;
	return true;
}

void BaseFigure::FigCpy(bool a[4][4], const bool b[4][4]) {
	int x, y;
	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++)
			a[x][y] = b[x][y];
}

void BaseFigure::Generate() { /* generate next figure */
	switch (NextFigID) {
	case 1: FigCpy(figure, __Fig0); CurFigType = (BACKGROUND_INTENSITY | BACKGROUND_RED); break;
	case 2: FigCpy(figure, __Fig1); CurFigType = (BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN); break;
	case 3: FigCpy(figure, __Fig2); CurFigType = (BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_RED); break;
	case 4: FigCpy(figure, __Fig3); CurFigType = (BACKGROUND_INTENSITY | BACKGROUND_BLUE); break;
	case 5: FigCpy(figure, __Fig4); CurFigType = (BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN); break;
	case 6: FigCpy(figure, __Fig5); CurFigType = (BACKGROUND_INTENSITY | BACKGROUND_GREEN); break;
	case 7: FigCpy(figure, __Fig6); CurFigType = (BACKGROUND_RED | BACKGROUND_GREEN);
	}

	NextFigID = rand() % 7 + 1;
	switch (NextFigID) {
	case 1: FigCpy(_next_fig, __Fig0); NextFigType = (BACKGROUND_INTENSITY | BACKGROUND_RED); break;
	case 2: FigCpy(_next_fig, __Fig1); NextFigType = (BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN); break;
	case 3: FigCpy(_next_fig, __Fig2); NextFigType = (BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_RED); break;
	case 4: FigCpy(_next_fig, __Fig3); NextFigType = (BACKGROUND_INTENSITY | BACKGROUND_BLUE); break;
	case 5: FigCpy(_next_fig, __Fig4); NextFigType = (BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN); break;
	case 6: FigCpy(_next_fig, __Fig5); NextFigType = (BACKGROUND_INTENSITY | BACKGROUND_GREEN); break;
	case 7: FigCpy(_next_fig, __Fig6); NextFigType = (BACKGROUND_RED | BACKGROUND_GREEN);
	}
}

void BaseFigure::DrawFigOnMap(BaseBoard& b) { /* Draw figure on map before generating a new */
	int x, y;
	for (y = CurFigY; y < CurFigY + 4; y++) {
		for (x = CurFigX; x < CurFigX + 4; x++) {
			if (figure[x - CurFigX][y - CurFigY] && x < 10 && x >= 0 && y < 20 && y >= 0)
				b.map[x][y] = CurFigType * (int)figure[x - CurFigX][y - CurFigY];
		}
	}
}

void BaseFigure::Save(string filename) {
	//ios - перечисление, в котором собраны все флаги для управления работой с файловыми потоками 

	//указывая флаг ios::app мы меняем поведение потока по умолчанию: вместо того, чтобы затереть
	//те данные, которые в файле были, и начать заполнять файл заново, поток будет сразу помещать
	//данные в конец файла, не затирая то содержимое, которое в нем имеется
	ofstream out(filename.c_str(),
		ios::binary | ios::app); //ios::app - append (добавить) - флаг указывает, на то, что данные
								 //будут добавлятся в конец файла

	out.write((char*)&figure, 16 * sizeof(bool));

	out.write(
		(char*)&CurFigX, //передаем указатель на адрес поля в памяти (на первый байт переменной) 
		sizeof(CurFigX));//передаем сколько байт в переменной
	out.write((char*)&CurFigY, sizeof(CurFigY));
	out.write((char*)&CurFigType, sizeof(CurFigType));
	out.write((char*)&NextFigID, sizeof(NextFigID));

	out.close();
};

void BaseFigure::Load(string filename) {
	ifstream in(filename.c_str(),
		ios::binary);

	//проверка: если по какой-либо причине поток
	//для работы с файлом не смог создастся (самая распрастраненная причина -
	//отсутствие файла с именем filename)
	if (!in)
		return; //то просто выходим из метода


				//метод seekg позволяет сделать отступ (при работе с файловым потоком)
	in.seekg(200,            //число байт на которое необходимо сделать отступ
		std::ios::beg); //указывает место, от которого необходимо сделать отступ
						//варианты задания места, от которого делается отступ
						//std::ios::beg; beg - begin   (начало)  - отступ от начала файла (в направлении к концу файла)
						//std::ios::cur; cur - current (текущий) - отступ от текущей позиции (в направлении к концу файла)
						//std::ios::end; end - end     (конец)   - отступ от конца файла (в направлении к началу файла)
	in.read((char*)&figure, 16 * sizeof(bool));

	in.read(
		(char*)&CurFigX, //передаем указатель на адрес поля в памяти (на первый байт переменной) 
		sizeof(CurFigX));//передаем сколько байт в переменной
	in.read((char*)&CurFigY, sizeof(CurFigY));
	in.read((char*)&CurFigType, sizeof(CurFigType));
	in.read((char*)&NextFigID, sizeof(NextFigID));

	in.close();
};





