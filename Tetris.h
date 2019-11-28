#pragma once

#define TETRISX	10
#define TETRISY	20
#define BLOCKLEN	15

bool blockInPiece(uint x, uint y, u16 piece)
{
	return piece &((0b1 << 15) >> (x+(4*b)));
}

// empty, static, red, green, cyan, pink, orange, blue
typedef enum{B_E = 0, B_S, B_R, B_G, B_C, B_P, B_O, B_B}Block;

Block gameboard[TETRISX][TETRISY] = {B_E};

void blockDraw(int x, int y, Block block)
{
	u16 c = WHITE;
	switch (block) {
		case B_E:
			c = WHITE;
			break;
		case B_S:
			c = LIGHTGREY;
			break;
		case B_R:
			c = RED;
			break;
		case B_G:
			c = GREEN;
			break;
		case B_C:
			c = CYAN;
			break;
		case B_P:
			c = PINK;
			break;
		case B_O:
			c = ORANGE;
			break;
		case B_B:
			c = BLUE;
			break;
	}
	screen.fillRect((x*BLOCKLEN+2)+BLOCKLEN,y*BLOCKLEN+2,BLOCKLEN-2,BLOCKLEN-2,c);
}

void pieceDraw(int x, int y, u16 piece, Block block)
{
	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			if(blockInPiece())

		}
	}
}

void gameboardDraw(void)
{
	for(uint y = 0; y < TETRISY; y++){
		for(uint x = 0; x < TETRISX; x++){
			blockDraw(x,y,gameboard[x][y]);
		}
	}
}

void tetris(void)
{
	while(1){
		for(uint y = 0; y < TETRISY-1; y++){
			for(uint x = 1; x < TETRISX-1; x++){
				gameboard[x][y] = (Block)random(0,8);
			}
		}
		screenBlank();
		gameboardDraw();
		delay(2000);
	}
}
