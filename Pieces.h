#pragma once
extern "C"{

#define BOARDX	10
#define BOARDY	20

u8 board[BOARDX][BOARDY];

#define BLOCKLEN	(SCREENY/BOARDY)
#define NUMPIECES	7

#define getBlock(x, y, p)	((p)&  (0x8000>>(4*(y)+(x))))
#define setBlock(x, y, p)	((p)|  (0x8000>>(4*(y)+(x))))
#define clearBlock(x, y, p)	((p)& ~(0x8000>>(4*(y)+(x))))
#define flipBlock(x, y, p)	((p)^  (0x8000>>(4*(y)+(x))))

typedef struct{
	u8 id;
	uint x;
	uint y;
	u16 blocks;
	union{
		Color arr[3];
		struct{
			Color color;
			Color light;
			Color dark;
		};
	};
}Piece;

const Piece pieceArr [NUMPIECES] = {
	{0,0,0,PIECE_0, {YELLOW,LIGHTYELLOW,DARKYELLOW	}},
	{1,0,0,PIECE_1, {CYAN,	LIGHTCYAN,	DARKCYAN	}},
	{2,0,0,PIECE_2, {PURPLE,LIGHTPURPLE,DARKPURPLE	}},
	{3,0,0,PIECE_3, {BLUE,	LIGHTBLUE,	DARKBLUE	}},
	{4,0,0,PIECE_4, {ORANGE,LIGHTORANGE,DARKORANGE	}},
	{5,0,0,PIECE_5, {RED,	LIGHTRED,	DARKRED	}},
	{6,0,0,PIECE_6, {GREEN,	LIGHTGREEN,	DARKGREEN	}}
};

uint randomPieceIndex(void)
{
	static uint prev = NUMPIECES;
	uint next = rand()%(NUMPIECES-1);
	next += next>=prev;
	prev = next;
	return next;
}

Piece randomPiece(void)
{
	return pieceArr[randomPieceIndex()];
}

void getOffsets(uint *xoff, uint *yoff, const u16 blocks)
{

	for(uint x = 0; x < 4; x++){
		for(uint y = 0; y < 4; y++){
			*xoff = x;
			if(getBlock(x,y,blocks))
				goto ESC;
		}
	}
	ESC:
	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			*yoff = y;
			if(getBlock(x,y,blocks))
				return;
		}
	}
}

void getLens(uint *xlen, uint *ylen, const u16 blocks)
{
	for(uint x = 0; x < 4; x++){
		for(uint y = 0; y < 4; y++){
			*xlen = 4-x;
			if(getBlock(3-x,3-y,blocks))
				goto ESC;
		}
	}
	ESC:
	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			*ylen = 4-y;
			if(getBlock(3-x,3-y,blocks))
				return;
		}
	}
}

u16 pieceBlocksAdjust(const u16 blocks)
{
	uint xoff = 0;
	uint yoff = 0;
	getOffsets(&xoff, &yoff, blocks);
	u16 xadjusted = 0;
	for(uint x = 0; x < 4-xoff; x++){
		for(uint y = 0; y < 4; y++){
			if(getBlock(x+xoff, y, blocks))
				xadjusted |= setBlock(x,y,xadjusted);
		}
	}
	u16 xyadjusted = 0;
	for(uint y = 0; y < 4-yoff; y++){
		for(uint x = 0; x < 4; x++){
			if(getBlock(x, y+yoff, xadjusted))
				xyadjusted |= setBlock(x,y,xyadjusted);
		}
	}
	return xyadjusted;
}

/*
0100	0010	0000	0000
11x0	0011	0000	0x00
0000	00x0	0x11	1100
0000	0000	0010	0100
2,1	2,2	1,2	1,1 */
u16 pieceBlocksRoR(const u16 blocks)
{
	u16 ret = 0;
	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			if(getBlock(x,y,blocks))
				ret |= setBlock(3-y,x,ret);
		}
	}
	return pieceBlocksAdjust(ret);
}

/*
0x00	0000	0000	0010
1110	0100	0000	001x
0000	x100	0111	0010
0000	0100	00x0	0000
1,0	0,2	2,3	3,1 */
u16 pieceBlocksRoL(const u16 blocks)
{
	u16 ret = 0;
	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			if(getBlock(x,y,blocks))
				ret |= setBlock(y,3-x,ret);
		}
	}
	return pieceBlocksAdjust(ret);
}

bool validPiecePos(const Piece p)
{
	uint xlen = 0;
	uint ylen = 0;
	getLens(&xlen, &ylen, p.blocks);
	if(p.x + xlen >= BOARDX || p.y + ylen >= BOARDY)
		return false;
	for(uint y = 0; y < ylen; y++){
		for(uint x = 0; x < xlen; x++){
			if(getBlock(x,y,p.blocks) && board[x][y] != NUMPIECES)
				return false;
		}
	}
	return true;
}

bool canMove(const Piece p, const Direction dir)
{
	uint xlen = 0;
	uint ylen = 0;
	getLens(&xlen, &ylen, p.blocks);
	Piece moved = p;
	switch(dir) {
		case DIR_U:
			if(moved.y <= 0)
				return false;
			moved.y--;
			break;
		case DIR_R:
			if(moved.x+xlen >= BOARDX)
				return false;
			moved.x--;
			break;
		case DIR_D:
			if(moved.y+ylen >= BOARDY)
				return false;
			moved.y++;
			break;
		case DIR_L:
			if(moved.x <= 0)
				return false;
			moved.x--;
			break;
	}
	return validPiecePos(moved);
}

bool tryMove(Piece *p, const Direction dir)
{
	if(!canMove(*p,dir))
		return false;
	switch(dir) {
		case DIR_U:
			p->y--;
			break;
		case DIR_R:
			p->x--;
			break;
		case DIR_D:
			p->y++;
			break;
		case DIR_L:
			p->x--;
			break;
	}
	return true;
}

void placePiece(const Piece p)
{
	uint xlen = 0;
	uint ylen = 0;
	getLens(&xlen, &ylen, p.blocks);
	for(uint y = 0; y < ylen; y++){
		for(uint x = 0; x < xlen; x++){
			if(getBlock(x,y,p.blocks))
				board[p.x+x][p.y+y]=p.id;
		}
	}
}

}
