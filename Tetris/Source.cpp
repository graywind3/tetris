/*************************
* Tetris
*/

#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <iostream>
using namespace std;

#include "Board.h"
#include "Figure.h"

void setscr(int a);

void setscr(int a) { /* write the high score to a file */
	FILE *fl = fopen("data.bin", "wb");
	fwrite(&a, sizeof(a), 1, fl);
	fclose(fl);
}

int gethighscore() { /* read the high score from a file */
	int r = 0;
	FILE *fl = fopen("data.bin", "rb");
	if (!fl)
		setscr(0);
	else
		fread(&r, sizeof(r), 1, fl);
	fclose(fl);
	return r;
}

void setpos(int x, int y) { // set cursor position on the screen at x,y 
	COORD C = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), C);
}

void setcur(bool mode) { /* turn on/off cursor */
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = mode ? TRUE : FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

/* == Data == */
int  score = 0, lines = 0;



void Draw(void);

ConsoleBoard b;
Figure f;

int main() {
	system("chcp 1251"); system("cls");
	//srand(time(NULL));

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
	GetConsoleScreenBufferInfo(h, &ConsoleInfo);
	WORD OriginalColors = ConsoleInfo.wAttributes;

	int i, x, y, points;
	char key;
	bool quick = false;

	f.Generate();

start:
	score = lines = 0;
	char act = '\0';
	
	cout << "Вы хотите продолжить закрытую игру? (y, Y - да)" << endl;
	cin >> act;
	if ((act == 'y') || (act == 'Y')){
		//когда считывается состояние игры из файла:
		//для метода Load доски ничего не меняется - мы считываем те же 200
		//байтов что и ранее, есть в файле еще что-либо или нет - для метода
		//Load доски не важно
		b.Load("Save.bin");
		//для метода Load фигуры, мы не можем считывать данные с начала файла,
		//так как первые 200 байт - данные доски, необходио вначале сделать
		//отступ в 200 байт
	    f.Load("Save.bin");
    }
    
	printf("Press any key...");
	getch();


	for (;;) {
		setcur(false);
		key = 0;
		for (i = 0; i < (quick ? 1000 : 5000); i++)
			if (kbhit()) {
				key = getch();
			}
		quick = false;
		if (key == 27) {
			//сохраняем состояние игровой доски
			//если мы сохраняем состояние игры (состояние игры это состояние игровой доски и
			//состояние фигуры) в один файл, то  тогда...
			//сохраняя состояние доски в файл Save.bin, это файл должен переписываться 
			b.Save("Save.bin");
			//но когда в этот же файл мы помещает данные фигуры, то эти данные должны добавлятся
			//в конец Save.bin, а не затирать то, что в нем есть (затирание предыдущих данных - это
			//поведение файлового потока по умолчанию)
			f.Save("Save.bin");
			//выход из игры - выход из цикла игры
			break; //27 - Esc
		}
		else if (key == ' ') getch(); 
		else if (key == 'w') f.Rotate(b); 
		else if (key == 'a') f.ShiftLeft(b); 
		else if (key == 'd') f.ShiftRight(b);
		else if (key == 's') quick = true; 
		else if (key == '\r') while (f.ShiftDown(b)); 
		else
			switch (key) { /* arraw is 2 chars */
				case 72: f.Rotate(b);    break;   //72 - стрелка вверх
				case 75: f.ShiftLeft(b); break;   //75 - стрелка влево
				case 77: f.ShiftRight(b); break;  //77 - стрелка вправо
				case 80: quick = true;   
			}

		if (!f.ShiftDown(b)) {
			f.DrawFigOnMap(b);
			f.CurFigX = 3;
			f.CurFigY = -3;
			lines += (points = b.CheckLine());
			if (points)
				score += 2 << points;
			else score++;
			f.Generate();
		}

		Draw();
		if (b.IsLost()) {
			setpos(20, 10);
			printf("     Game over!     ");
			getchar();
			goto start;
		}
	}
	setcur(true);
	SetConsoleTextAttribute(h, OriginalColors);
	return 0;
}



void rect(int x, int y, int color) { /* put a 1x1 rectangle at x,y */
	if (x < 0 || y < 0) return;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD cWritten;
	const char fill_char = ' ';
	SetConsoleTextAttribute(h, color);
	setpos(x, y);
	WriteFile(h, &fill_char, 1, &cWritten, NULL);
	SetConsoleTextAttribute(h, 0);
}

void square(int x, int y, int color) { /* squre at x,y */
	rect(2 * x, y, color);
	rect(2 * x + 1, y, color);
}


void Draw() { /* draw map, figure, border, next figure, scores */
	int x, y;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
	static bool done = false;
	if (!done) {
		done = true;
		system("cls");
		printf("Score: 0\nHigh score: 0\nLines: 0");
		for (y = 0; y < 20; y++) {
			setpos(19, y); putchar('|');
			setpos(40, y); putchar('|');
		}
		setpos(19, 20);
		for (x = 0; x < 22; x++) putchar('-');
	}
	if (gethighscore() < score) setscr(score);

	setpos(7, 0);  printf("%d", score);
	setpos(12, 1); printf("%d", gethighscore());
	setpos(7, 2);  printf("%d", lines);
	SetConsoleTextAttribute(h, 0);

	//draw board
	b.Draw();

	//draw figure
	f.Draw();

	// next figure 
	f.NextFigure();

	SetConsoleTextAttribute(h, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
}

