#include "Types.h"
#include "Display.h"
#include "Buttons.h"
#include "Tetris.h"

void setup()
{
	randomSeed(analogRead(0));
	screenInit();
	btnInit();
	tetris();
}

void loop()
{
	delay(5);
	btnUpdate();
}
