#pragma once

void drawBlock(uint x, uint y)
{
	screen.fillRect(SCALE*x+GAP, SCALE*y+GAP, SCALE-GAP*2, SCALE-GAP*2, WHITE);
}

void drawBlackBlock(uint x, uint y)
{
	screen.fillRect(SCALE*x+GAP, SCALE*y+GAP, SCALE-GAP*2, SCALE-GAP*2, BLACK);
}

void drawWalls(void)
{
	for(uint i = 0; i < 21; i++){
		// board walls
		drawBlock(0, i);
		drawBlock(11, i);
		// rightmost wall
		drawBlock(17, i);
	}

	for(uint i = 0; i < 12+6; i++){
		// floor
		drawBlock(i, 20);
	}

	for(uint i = 12; i < 12+5; i++){
		// next piece box
		drawBlock(i, 0);
		drawBlock(i, 7);
		// score bottom
		drawBlock(i, 12);
	}
}

void drawPiece(uint xpos, uint ypos, piece p)
{
	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			if(getBlock(x,y,p))
				drawBlock(xpos+x, ypos+y);
		}
	}
}

void drawNext(piece n)
{

	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			if(getBlock(x,y,n))
				drawBlock(13+x, 2+y);
			else
				drawBlackBlock(13+x, 2+y);
		}
	}
}

void drawBoard(void)
{
	for(uint y = 0; y < 20; y++){
		for(uint x = 0; x < 10; x++){
			if(board[x][y])
				drawBlock(x+1, y);
			else
				drawBlackBlock(x+1, y);
		}
	}
}

void drawDbg(level l)
{
	screen.setCursor(0, SCALE*21);
	screen.print("Lvl: ");
	screen.print(l.levelNum);

	screen.setCursor(SCREENX/2, SCALE*21);
	screen.print("Goal: ");
	screen.print(l.levelNum*5 - l.scoreRemaining);
	screen.print(" of ");
	screen.print(l.levelNum*5);

	screen.setCursor(0, SCALE*22);
	screen.print("fallMs: ");
	screen.print(elapsedTime());
	screen.print(" of ");
	screen.print(l.falltime);
}

void drawAll(uint pieceX, uint pieceY, piece p, piece n)
{
	drawWalls();
	drawBoard();
	drawPiece(pieceX + 1, pieceY, p);
	drawNext(n);
}
