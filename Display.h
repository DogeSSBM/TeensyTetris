#pragma once

#define SCREENX	240
#define HSCREENX	(SCREENX/2)
#define SCREENY	320
#define HSCREENY	(SCREENY/2)
#include "ILI9341_t3.h"
#include "Colors.h"

ILI9341_t3 screen = ILI9341_t3(10, 9);
Color drawColor = WHITE;
Color textColor = WHITE;

void setColor(const Color color)
{
	drawColor = color;
}

void drawPixel(const uint x, const uint y)
{
	screen.drawPixel(x, y, drawColor);
}

void drawLine(const uint x1, const uint y1, const uint x2, const uint y2)
{
	screen.drawLine(x1, y1, x2, y2, drawColor);
}

void drawRect(const uint x, const uint y, const uint xlen, const uint ylen)
{
	screen.drawRect(x, y, xlen, ylen, drawColor);
}

void drawCircle(const uint x, const uint y, const uint radius)
{
	screen.drawCircle(x, y, radius, drawColor);
}

void drawSquare(const uint x, const uint y, const uint size)
{
	screen.drawRect(x, y, size, size, drawColor);
}

void fillSquare(const uint x, const uint y, const uint size)
{
	screen.fillRect(x, y, size, size, drawColor);
}

void fillRect(const uint x, const uint y, const uint xlen, const uint ylen)
{
	screen.fillRect(x, y, xlen, ylen, drawColor);
}

void fillCircle(const uint x, const uint y, const uint radius)
{
	screen.fillCircle(x, y, radius, drawColor);
}

uint getCursorX(void)
{
	return screen.getCursorX();
}

uint getCursorY(void)
{
	return screen.getCursorY();
}

uint getTextSize(void)
{
	return screen.getTextSize();
}

void setTextSize(const uint s)
{
	screen.setTextSize(s);
}

void setTextColor(const Color c)
{
	screen.setTextColor(c);
	textColor = c;
}

uint screenToLine(const uint s)
{
	return s/(getTextSize()*8);
}

void setCursorX(const uint x)
{
	screen.setCursor(x, getCursorY());
}

void setCursorY(const uint y)
{
	screen.setCursor(getCursorY(), y);
}

void setCursor(const uint x, const uint y)
{
	screen.setCursor(x, y);
}

void setCharCursor(const uint x, const uint y)
{
	const uint s = getTextSize()*8;
	setCursor(x*s, x*y);
}

void setLine(const uint l)
{
	screen.setCursor(0, l*getTextSize()*8);
}

void setClearLine(const uint l)
{
	screen.setCursor(0, l*getTextSize()*8);
	setColor(BLACK);
	fillRect(getCursorX(), getCursorY(), SCREENX, getTextSize()*8);
}

uint numLines(void)
{
	return SCREENY/(getTextSize()*8);
}

void setClearLineBottom(const uint l)
{
	setClearLine(numLines()-(1+l));
}

void printText(const char* text)
{
	screen.print(text);
}

void fillPrintText(const char* text)
{
	const uint len = strlen(text);
	const u8 size = getTextSize();
	const Color temp = drawColor;
	setColor(BLACK);
	fillRect(screen.getCursorX(), screen.getCursorX(), size*8*len, size);
	drawColor = temp;
	printText(text);
}

void drawText(const uint x, const uint y, const char* text)
{
	i16 oldx = 0, oldy = 0;
	screen.getCursor(&oldx, &oldy);
	screen.setCursor(x, y);
	screen.print(text);
	screen.setCursor(oldx, oldy);
}

void fillText(const uint x, const uint y, const char* text)
{
	const uint len = strlen(text)-1;
	const u8 size = getTextSize();
	const Color temp = drawColor;
	setColor(BLACK);
	fillRect(x, y, size*8*len, size*8);
	drawColor = temp;
	drawText(x, y, text);
}

void screenBlank(void)
{
	screen.fillScreen(BLACK);
	screen.setCursor(0,0);
}

void screenInit(void)
{
	screen.begin();
	screenBlank();
	screen.setTextSize(3);
	screen.setTextColor(WHITE);
	setColor(WHITE);
}
