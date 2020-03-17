#pragma once
extern "C"{

struct{
	uint level;
	uint togo;
}score;

void drawLabels(void)
{
	const uint allX = (BOARDX+1)*BLOCKLEN;
	const uint nextY = BLOCKLEN;
	const uint levelY = BLOCKLEN*7;
	const uint togoY = BLOCKLEN*10;
	fillText(allX, nextY, "Next:");
	fillText(allX, levelY, "Lvl:");
	fillText(allX, togoY, "ToGo:");
}

void drawScore(void)
{
	setTextSize(2);
	static char levelStr[5]	= {"0000"};
	intToStr(score.level, levelStr);
	static char togoStr[5]	= {"0000"};
	intToStr(score.togo, togoStr);
	const uint allX = (BOARDX+1)*BLOCKLEN;
	const uint levelY = BLOCKLEN*8;
	const uint togoY = BLOCKLEN*11;
	fillText(allX, levelY, levelStr);
	fillText(allX, togoY, togoStr);
}

}
