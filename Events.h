#pragma once

typedef enum{MOVE_U = 16, MOVE_D, MOVE_L, MOVE_R, ROTATE_L = 6, ROTATE_R, NOTHING = 0, PLACE}event;

event btnPress(void)
{
	btnRead();
	for(uint i = 0; i < BTNNUM; i++){
		if(btn.arr.pressed[i] && !btn.arr.prevPressed[i])
			return (event)btn.arr.pin;
	}
}
