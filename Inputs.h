#pragma once

void inputs(void)
{
	if(btnPressed.btn2){
		resetWait(&btnState.btn2);
		btnPressed.btn2 = false;
	}
}
