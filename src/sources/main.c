#ifndef _MAIN_C_
#define _MAIN_C_

#include "definition.h"
#include "process.h"
#include "event.h"

//=============================================================================================================================================//
/* 函数实现 */
//=============================================================================================================================================//

/* 功能:主函数
 * 参数:无
 * 返回值:正常退出返回0
 * 说明:调用 DrawMenu() 来绘制菜单,仅初始化时调用一次;
 */
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
