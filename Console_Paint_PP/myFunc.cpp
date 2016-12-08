#include "myFunc.h"
#include "conio2.h"
#include <cstdio>


void drawBground(int drawXStart, int drawXEnd)
{
	textcolor(WHITE);
	for (int i = drawYStart; i <= drawYEnd; i++) {
		for (int j = drawXStart; j <= drawXEnd; j++) {
			gotoxy(j, i);
			if (j == drawXStart || i == drawYStart || j == drawXEnd || i == drawYEnd)
			{
				putch('*');
			}
		}
	}
}

void drawLine(int startX, int startY)
{
	char zn;
	int x = startX; int y = startY;
	zn = getch();
	if (zn == 0) {
		/*zero = 1;*/
		zn = getch();
		if (zn == arrowUp) y--;
		else if (zn == arrowDown) y++;
		else if (zn == arrowLeft) x--;
		else if (zn == arrowRight) x++;
	}
}


bool load(picture *pic) {
	int tmp_color;
	FILE *plik;
	plik = fopen("bground"/*loadText()*/, "rb");
	if (plik == NULL) {
		cputs("otwarcie nie powiodlo sie");
		return false;
	}
	fscanf(plik, "%d\n%d\n", &pic->dim.height, &pic->dim.width);
	pic->colors = new int*[pic->dim.height];
	for (int i = 0; i < pic->dim.height; i++)
	{
		pic->colors[i] = new int[pic->dim.width];
	}
	for (int i = 0; i < pic->dim.height; i++) {
		for (int j = 0; j < pic->dim.width; j++) {
			tmp_color = getc(plik);
			if (tmp_color >= '0' && tmp_color <= '9') tmp_color -= 48;
			else if (tmp_color >= 'A' && tmp_color <= 'F') tmp_color -= 55;
			pic->colors[i][j] = tmp_color;
		}
		fscanf(plik, "\n");
	}
	fclose(plik);
	return true;
}

char* loadText() {
	static char text[maxTextSize];
	int i = 0;
	char zn;
	do
	{
		zn = getche();
		if (zn != backSpace && zn != escape && zn != enterKey) {
			text[i] = zn;
			i++;
		}
		if (zn == backSpace && i > 0) {
			i--;
			text[i] = '\0';
			clreol();
		}
	} while (zn != enterKey);
	text[i] = 0;
	return text;
}

bool save(picture *pic, char *fileName) {
	int tmp_color = 0;
	FILE *plik;
	plik = fopen(fileName, "wb");
	if (plik == NULL) {
		cputs("otwarcie nie powiodlo sie");
		return false;
	}
	fprintf(plik, "%d\n%d\n", pic->dim.height, pic->dim.width);
	for (int i = 0; i < pic->dim.height; i++) {
		for (int j = 0; j < pic->dim.width; j++) {
			tmp_color = pic->colors[i][j];
			if (tmp_color >= 0 && tmp_color <= 9) {
				tmp_color += 48;
			}
			else {
				tmp_color += 55;
			}
			fprintf(plik, "%c", tmp_color);
		}
		fprintf(plik, "\n");
	}
	fclose(plik);
	return true;
}

void drawTab(picture *pic, int drawXStart, int drawXEnd, int maxY, picture *result)
{
	dimensions frame;
	frame.height = drawXEnd - drawXStart;
	frame.width = maxY - drawYStart;
	dimensions dest;
	dimensions asd;
	if (frame.height > pic->dim.height) dest.height = pic->dim.height;
	else
		dest.height = frame.height;
	if (frame.width > pic->dim.width) dest.width = pic->dim.width;
	else
		dest.width = frame.width;
	for (int i = drawYStart + 1; i <= dest.height + drawYStart; i++) {
		for (int j = drawXStart + 1; j <= dest.width + drawXStart; j++) {
			gotoxy(j, i);
			asd.height = i - (drawYStart)-1;
			asd.width = j - (drawXStart)-1;
			textbackground(pic->colors[asd.height][asd.width]);
			putch(' ');
			result->colors[asd.height][asd.width] = pic->colors[asd.height][asd.width];
		}
	}
}

void clearBuffer(char *buffer)
{
	for (int i = 0; i < tmpBufferSize; i++)
	{
		buffer[i] = '\0';
	}
}

int getTextSize(char *tab)
{
	int size = 0;
	for (int i = 0; i < tmpBufferSize; i++)
	{
		if (tab[i] != '\0') size++;
		else break;
	}
	return size;
}

void putBuffer(char *buffer, int bufferSize)
{
	for (int i = 0; i < bufferSize; i++)
	{
		cputs(&buffer[i]);
	}
}

void clearBufferLine(int startX, int startY, int bufferLength)
{
	gotoxy(startX, startY);
	for (int i = 0; i < bufferLength; i++)
	{
		gotoxy(startX + i, startY);
		putch('\0');
	}
}

void swap(int &a, int &b)
{
	int c;
	c = a;
	a = b;
	b = c;
}

void clrFrame(int startX, int startY, int endX, int endY)
{
	textbackground(BLACK);
	for (int i = startY; i <= endY; i++) {
		for (int j = startX; j <= endX; j++) {
			gotoxy(j, i);
			cputs(" ");
		}
	}
}

int changeColorForFile(int bgColor)
{

	if (bgColor < 9) {
		return (char)(bgColor + 48);
	}
	else
		return (char)((bgColor % 10) + 66);
}

void floodFill(int x, int y, int color, int drawXStart, int maxX, int maxY, picture *result)
{
	if (isMenuLeft) {
		if (x > maxX + 49) return;
	}
	else if (x > maxX) return;
	if (y<1 || y>=maxY || x < drawXStart) return; //sprawdzenie wyjscia poza granice


	if (result->colors[y-1][x-1-drawXStart] == BLACK) { //sprawdzenie koloru
		textbackground(color);
		gotoxy(x, y+1);
		cputs(" ");
		result->colors[y-1][x-1-drawXStart] = color;
	}
	else return;

	floodFill(x, y - 1, color, drawXStart, maxX, maxY, result);
	floodFill(x + 1, y, color, drawXStart, maxX, maxY, result);
	floodFill(x, y + 1, color, drawXStart, maxX, maxY, result);
	floodFill(x - 1, y, color, drawXStart, maxX, maxY, result);
}