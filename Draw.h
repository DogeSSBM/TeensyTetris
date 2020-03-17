#pragma once
extern "C"{

void drawBoxAbsolute(const uint x, const uint y,
const Color c, const Color cl, const Color cd)
{
	setColor(cd);
	fillSquare(x, y, BLOCKLEN);
	setColor(cl);
	fillSquare(x, y, BLOCKLEN-2);
	setColor(c);
	fillSquare(x+2, y+2, BLOCKLEN-4);
}

void drawBox(const uint x, const uint y,
const Color c, const Color cl, const Color cd)
{
	drawBoxAbsolute(x*BLOCKLEN, y*BLOCKLEN, c, cl, cd);
}

void drawBoxNext(const uint x, const uint y,
const Color c, const Color cl, const Color cd)
{
	drawBoxAbsolute((x+BOARDX+1)*BLOCKLEN, (y+1)*BLOCKLEN, c, cl, cd);
}

void drawWalls(void)
{
	// Board walls
	for(uint y = 0; y < BOARDY; y++){
		drawBox(BOARDX,	y, GREY, LIGHTGREY, DARKGREY);
	}

	// Smaller length vertical walls
	for(uint y = 12; y < BOARDY; y++){
		drawBox(BOARDX+1,	y, GREY, LIGHTGREY, DARKGREY);
		drawBox(BOARDX+2,	y, GREY, LIGHTGREY, DARKGREY);
		drawBox(BOARDX+3,	y, GREY, LIGHTGREY, DARKGREY);
		drawBox(BOARDX+4,	y, GREY, LIGHTGREY, DARKGREY);
	}

	// Horizontal dividers
	for(uint x = BOARDX; x < BOARDX+5; x++){
		drawBox(x, 0, GREY, LIGHTGREY, DARKGREY);
		drawBox(x, 6, GREY, LIGHTGREY, DARKGREY);
		drawBox(x, 9, GREY, LIGHTGREY, DARKGREY);
	}
}

void drawPiece(const Piece p)
{
	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			if(getBlock(x,y,p.blocks))
				drawBox(p.x+x, p.y+y, p.color, p.light, p.dark);
		}
	}
}

void blankPiece(const Piece p)
{
	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			if(getBlock(x,y,p.blocks))
				drawBox(p.x+x, p.y+y, BLACK, BLACK, BLACK);
		}
	}
}

void drawBoard(void)
{
	for(uint y = 0; y < BOARDY; y++){
		for(uint x = 0; x < BOARDX; x++){
			if(board[x][y] != NUMPIECES){
				drawBox(x,y,
					pieceArr[board[x][y]].color,
					pieceArr[board[x][y]].light,
					pieceArr[board[x][y]].dark
				);
			}
		}
	}
}

}
