#pragma once
#define isMenuLeft 1

#define arrowLeft 0x4b
#define arrowRight 0x4d
#define arrowUp 0x48
#define arrowDown 0x50
#define enterKey 13
#define escape 27
#define backSpace 8

#define drawYStart 1
#define drawYEnd 22
#define tmpBufferSize 25
#define maxTextSize 40


struct dimensions
{
	int height;
	int width;
};

struct picture
{
	dimensions dim;
	int **colors;
};

struct rectangle
{
	int beginX;
	int beginY;
	int endX;
	int endY;
};


void drawBground(int drawXStart, int drawXEnd);
void drawTab(picture *pic,int drawXStart,int drawXEnd,int maxY, picture *result);
char *loadText();
bool load(picture *pic);
bool save(picture *pic,char *fileName);
void clearBufferLine(int startX, int startY, int bufferLength);
void clearBuffer(char* buffer);
void putBuffer(char* buffer, int bufferSize);
int getTextSize(char* tab); //pokazuje ilosc znakow bufora
void swap(int &a, int &b);
void clrFrame(int startX, int startY, int endX, int endY);
int changeColorForFile(int bgColor);
void floodFill(int x, int y, int color, int drawXStart,int maxX,int maxY,picture *result);