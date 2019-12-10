#pragma once

uint score = 0;

uint addScore(uint s)
{
	static uint score = 0;
	score += s;
	screen.fillRect(SCALE*12+SCALE/4, SCALE*10+SCALE/4, SCALE*5, SCALE, BLACK);
	screen.setCursor(SCALE*12+SCALE/4, SCALE*10+SCALE/4);
	screen.print(score);
	return score;
}

void initScore()
{
	screen.setTextSize(2);
	screen.setCursor(SCALE*12+SCALE/4, SCALE*8+SCALE/4);
	screen.print("Score");
	setScore(0);
}
