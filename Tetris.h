#pragma once

#define SCALE 12
#define GAP 2
#define XORIG 3
#define YORIG 0

typedef struct{
	uint levelNum;
	uint scoreRemaining;
	u32 falltime;
}level;

#include "Timing.h"
#include "PieceDefs.h"
#include "Board.h"
#include "Pieces.h"
#include "Score.h"
#include "Draw.h"
#include "Events.h"

level getLevel(uint l)
{
	level ret = {l, 5*l, levelFallMs(l)};
	return ret;
}

void tetris(void)
{
	initScore();
	uint x = XORIG, y = YORIG;
	piece p = pieces[rand()%NUMPIECES];
	piece n = pieces[rand()%NUMPIECES];
	level l = getLevel(1);
	u32 fallMs = 1000;
	drawAll(x,y,p,n);
	resetTime();
	while(1){

	}
}
