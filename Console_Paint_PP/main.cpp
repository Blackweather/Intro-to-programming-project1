#include<stdlib.h>
#include <stdio.h>
#include"conio2.h"
#include "myFunc.h"

/* Uwaga: w docelowym programie nalezy zadeklarowac odpowiednie
stale, na przyklad po to, aby wyeliminowac z programu
wartosci numeryczne umieszczajac w ich miejsce
dobrze dobrane identyfikatory */

int main() {
	int zn = 0, x = 2, y = 2, attr = 7, back = 0, zero = 0; bool draw = false;//draw while true not draw while false

	char tmpBuffer[tmpBufferSize]; //bufor wykorzystywany w itoa
	// je¿eli program jest kompilowany w czystym jêzyku C
	// proszê odkomentowaæ poni¿sz¹ liniê
	// Conio2_Init();
	settitle("Karol Szczepanski 165391");
	char *myFileName[maxTextSize];
	*myFileName = "Karol Szczepanski 165391";
	int startMenuX = 60;
	int drawXStart = 1;
	int drawXEnd = 52;
	if (isMenuLeft == 1) {
		startMenuX = 1;
		drawXStart = 50;
		drawXEnd = 52; //101
		x = 51;
	}
	int maxX = drawXEnd - 1; int maxY = drawYEnd - 1; //zmienne do okreslenia nowego pliku
	bool rectDrawing = false;
	bool programClose = false;
	picture anyPic; //wczytany obrazek

	picture result; //tablica przechowujaca wszystko co na obrazku
	result.dim.height = 20; //domyslne wymiary
	result.dim.width = 50;
	result.colors = new int*[result.dim.height];
	for (int i = 0; i < result.dim.height; i++)
	{
		result.colors[i] = new int[result.dim.width];
	}
	for (int i = 0; i < result.dim.height; i++)
	{
		for (int j = 0; j < result.dim.width; j++)
		{
			result.colors[i][j] = BLACK;
		}
	}
	rectangle rect;
	//wczytanie ramki
	if (isMenuLeft == 1) {
		drawBground(drawXStart, drawXEnd + 49);
	}
	else drawBground(drawXStart, drawXEnd);
	do {
		textbackground(BLACK);
		textcolor(7);
		for (int i = startMenuX; i <= startMenuX + maxTextSize; i++) {
			gotoxy(i, 1);
			cputs(" ");
		}
		gotoxy(startMenuX, 1);
		cputs(*myFileName);
		gotoxy(startMenuX, 2);
		if (rectDrawing) {
			cputs("esc - przerwanie rysowania prostokata");
		}
		else
		{
			cputs("esc = wyjscie");
			for (int i = 0; i < 24; i++) cputs(" ");
		}
		gotoxy(startMenuX, 3);
		cputs("strzalki = poruszanie");
		gotoxy(startMenuX, 4);
		cputs("spacja = ");
		if (draw) {
			cputs(" nierysowanie ");
		}
		else cputs(" rysowanie   ");
		gotoxy(startMenuX, 5);
		cputs("i - otwieranie pliku");
		gotoxy(startMenuX, 6);
		cputs("s - zapis do pliku o podanej nazwie");
		gotoxy(startMenuX, 7);
		cputs("0-9, q-y - zmiana koloru");
		gotoxy(startMenuX, 8);
		cputs("f = wypelnienie");
		gotoxy(startMenuX, 9);
		cputs("k = rysowanie prostokata ");
		if (rectDrawing) cputs("- w trakcie ");
		else cputs("- dostepne ");
		gotoxy(startMenuX, 10);
		cputs("n - nowy plik");
		for (int i = startMenuX; i < startMenuX + 15; i++)
		{
			gotoxy(i, 11);
			cputs(" ");
		} //wyczyszczenie linii
		gotoxy(startMenuX, 11);
		cputs("Pozycja kursora - x= ");
		clearBuffer(tmpBuffer);
		int xPosition = x - drawXStart;
		itoa(xPosition, tmpBuffer, 10);
		cputs(tmpBuffer);
		cputs(" ");
		//wypisanie bufora
		for (int i = startMenuX; i < startMenuX + 15; i++)
		{
			gotoxy(i, 12);
			cputs(" ");
		} //wyczyszczenie linii
		gotoxy(startMenuX, 12);
		cputs("Pozycja kursora - y= ");
		clearBuffer(tmpBuffer);
		int yPosition = y - drawYStart;
		itoa(yPosition, tmpBuffer, 10);
		cputs(tmpBuffer);
		cputs(" ");
		//wypisanie bufora

		gotoxy(x, y);
		textcolor(attr);
		textbackground(back);
		if (draw) {//sprawdzenie trybu rysowania
			cputs(" ");
			result.colors[yPosition - 1][xPosition - 1] = back;
		}
		zero = 0;
		zn = getch();
		if (zn == 0) {
			zero = 1;
			zn = getch();
			if (zn == arrowUp)
			{
				if (y > 2) y--;
			}
			else if (zn == arrowDown)
			{
				if (y < maxY) y++;
			}
			else if (zn == arrowLeft)
			{
				if (x > drawXStart + 1) x--;
			}
			else if (zn == arrowRight)
			{
				if (isMenuLeft) {
					if (x < maxX + 49) x++;
				}
				else if (x < maxX) x++;
			}

		}

		else if (zn == 'i' || zn == 'I')
		{
			gotoxy(drawXStart, drawYEnd + 10);
			load(&anyPic);
			if (isMenuLeft) {
				drawTab(&anyPic, drawXStart, maxX + 49, maxY, &result);
			}
			else drawTab(&anyPic, drawXStart, maxX, maxY, &result);
		}

		else if (zn == 's' || zn == 'S')
		{
			save(&result, *myFileName);
		}

		else if (zn == ' ' && rectDrawing == false) {
			if (draw) draw = false;
			else draw = true;
		}

		else if (zn >= '0' && zn <= '9') //klawisze od 1-9
		{
			back = (int)zn - 48;
		}
		else if (zn == 'q' || zn == 'Q') { back = LIGHTGREEN; }
		else if (zn == 'w' || zn == 'W') { back = LIGHTCYAN; }
		else if (zn == 'e' || zn == 'E') { back = LIGHTRED; }
		else if (zn == 'r' || zn == 'R') { back = LIGHTMAGENTA; }
		else if (zn == 't' || zn == 'T') { back = YELLOW; }
		else if (zn == 'y' || zn == 'Y') { back = WHITE; }

		else if (zn == 'n' || zn == 'N') {
			if (isMenuLeft) {
				clrFrame(drawXStart + 1, drawYStart + 1, maxX + 49, maxY);
			}
			else clrFrame(drawXStart + 1, drawYStart + 1, maxX, maxY);
			//usuniecie poprzedniej tablicy
			for (int i = 0; i < result.dim.height; i++)
			{
				delete[] result.colors[i];
			}
			delete[]result.colors;

			gotoxy(startMenuX, drawYEnd + 10);
			draw = false;
			textbackground(BLACK);
			attr = 7;
			clreol();
			cputs("Podaj wymiary: \n");
			clreol();
			cputs("Szerokosc: ");
			char *myWidth[maxTextSize];
			*myWidth = loadText();
			if (atoi(*myWidth) <= 50) { //sprawdzenie czy wymiar nie jest wiekszy od dostepnej przestrzeni
				maxX = atoi(*myWidth) + 1;
			}
			cputs("\n");
			result.dim.width = maxX - 1; //okreslenie wymiaru do alokacji
			clreol();
			cputs("Wysokosc: ");
			char *myHeight[maxTextSize];
			*myHeight = loadText();
			if (atoi(*myHeight) <= 20) { //sprawdzenie czy wymiar nie jest wiekszy od dostepnej przestrzeni
				maxY = atoi(*myHeight) + 1;
			}
			result.dim.height = maxY - 1; //okreslenie wymiaru do alokacji
			//alokacja i wypelnienie
			result.colors = new int*[result.dim.height];
			for (int i = 0; i < result.dim.height; i++)
			{
				result.colors[i] = new int[result.dim.width];
			}
			for (int i = 0; i < result.dim.height; i++)
			{
				for (int j = 0; j < result.dim.width; j++)
				{
					result.colors[i][j] = BLACK;
				}
			}
			//koniec alokacji
			cputs("\n");
			cputs("Podaj nazwe pliku: ");

			*myFileName = loadText();
			cputs("\r");
			clreol();

			x = drawXStart + 1;
			y = drawYStart + 1;
			textbackground(back);
		}
		else if (zn == 'k' || zn == 'K') {
			if (!rectDrawing) {
				rectDrawing = true;
				draw = false;
				rect.beginX = x;
				rect.beginY = y;
			}
			else {
				rectDrawing = false;
				rect.endX = x;
				rect.endY = y;

				if (rect.endX < rect.beginX) {
					swap(rect.beginX, rect.endX);
					if (rect.endY < rect.beginY) {
						swap(rect.beginY, rect.endY);
					}
				}
				else if (rect.endY < rect.beginY) {
					swap(rect.beginY, rect.endY);
				}

				for (int i = rect.beginY; i <= rect.endY; i++) {
					for (int j = rect.beginX; j <= rect.endX; j++) {
						if (i == rect.beginY || i == rect.endY || j == rect.beginX || j == rect.endX) {
							gotoxy(j, i);
							cputs(" ");
							result.colors[i-drawYStart-1][j-drawXStart-1] = back;
						}
					}
				}
			}
		}
		else if (zn == 'f' || zn == 'F')
		{
			floodFill(x, y, back, drawXStart, maxX, maxY, &result);
		}
		else if (zn == escape) {
			if (rectDrawing == true) {
				rectDrawing = false;
			}
			else
			{
				programClose = true;
			}
		}
	} while (!programClose);

	return 0;
}
