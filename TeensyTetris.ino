#include "Includes.h"

ul menu(void)
{
	Epoch ret;
	setTextSize(2);
	setCursor((BOARDX/2-2)*BLOCKLEN, 2*BLOCKLEN);
	const char title[] = "Tetris!";
	char buffer[] = " ";
	for(uint i = 0; i < strlen(title); i++){
		buffer[0] = title[i];
		setTextColor(pieceArr[i].color);
		printText((char*)buffer);
	}
	setTextColor(WHITE);
	for(uint y = 0; y < BOARDY; y++){
		for(uint x = 0; x < BOARDX; x++){
			if(y < BOARDY/3){
				board[x][y] = (u8)(NUMPIECES);
			}else if(y < BOARDY - BOARDY/3){
				board[x][y] = rand()&1?rand()%(NUMPIECES+1):NUMPIECES;
			}else{
				board[x][y] = rand()%(NUMPIECES+1);
			}
		}
	}
	drawWalls();
	drawLabels();
	drawScore();
	drawBoard();
	while(!(btnState.btnA && btnState.btnB));
	while(btnState.btnA || btnState.btnB);
	clearPressed();
	screenBlank();
	return ret;
}

void setup()
{
	Serial.begin(9600);
	while(!Serial.availableForWrite());
	delay(100);
	Serial.println("Hello, world!");
	init();
	randomSeed(menu());
	for(uint y = 0; y < BOARDY; y++){
		for(uint x = 0; x < BOARDX; x++){
			board[x][y] = NUMPIECES;
		}
	}
	drawWalls();
	drawBoard();
	drawLabels();
	drawScore();
	Piece piece = randomPiece();
	Piece next = randomPiece();
	drawPiece(next);
	uint waitTime = 1100;
	while(1){
		Epoch elapsed;

		Piece move = piece;
		if(btnpbtnState.btnL && !btnState.btnR && tryMove(&move,DIR_L)){
			blankPiece(piece);
			piece = move;
		}
		if(btnState.btnR && !btnState.btnL && tryMove(&move,DIR_R)){
			blankPiece(piece);
			piece = move;
		}
		if(btnState.btnU && !btnState.btnD && tryMove(&move,DIR_U)){
			blankPiece(piece);
			piece = move;
		}
		if(btnState.btnD && !btnState.btnU && tryMove(&move,DIR_D)){
			blankPiece(piece);
			piece = move;
		}
		drawPiece(piece);
		if(btnState.btnA && btnState.btnB && btnState.btnL && btnState.btnR)
			_softRestart();
		if(btnPressed.btnA && !btnState.btnA){
			btnPressed.btnA = false;
			placePiece(piece);
			piece = next;
			piece.x = BOARDX/2-2;
			piece.y = 0;
			blankPiece(next);
			next = randomPiece();
			next.x = BOARDX+1;
			next.y = 2;
			drawPiece(next);
			if(score.level < 10)
				waitTime -= 100;
			score.level++;
			drawScore();
		}
		//while(elapsed < waitTime);
	}
}

void loop()
{
	delay(500);
}
