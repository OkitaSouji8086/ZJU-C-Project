#ifndef _MAIN_C_
#define _MAIN_C_

#include "definition.h"
#include "main.h"

//=============================================================================================================================================//
/* º¯ÊýÊµÏÖ */
//=============================================================================================================================================//

void Main()
{
	int i;

	CURR_MODE = EDIT;

	SetWindowTitle("Program Creater");
	SetWindowSize(ScaleXInches(WINDOW_X), ScaleXInches(WINDOW_Y));
	InitGraphics();

#if _DEBUG_ == 1
	InitConsole();
#endif

	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
	registerMouseEvent(MouseEventProcess);
	registerTimerEvent(TimerEventProcess);

	startTimer(TIMER, 8);

	for (i = 0; i < NLIST; i++)
		List[i] = NewLinkedList();

	display();
}

#endif
