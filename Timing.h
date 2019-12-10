#pragma once

u32 refTime;

void resetTime()
{
	refTime = millis();
}

u32 elapsedTime()
{
	return millis()-refTime;
}

u32 levelFallMs(uint level)
{
	float flevel = level;
	float fms = pow(0.8f-((Level-1.0f)*0.007f), flevel-1.0f);
	return (u32)(fms*1000.0f);
}
