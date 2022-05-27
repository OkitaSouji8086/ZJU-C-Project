#ifndef _MAIN_C_
#define _MAIN_C_

#include "main.h"

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "linkedlist.h"
#include "imgui.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

//=============================================================================================================================================//
/* 默认值定义 */
//=============================================================================================================================================//



//=============================================================================================================================================//
/* 函数实现 */
//=============================================================================================================================================//

void Main()
{
	SetWindowTitle("Program Creater");
	SetWindowSize(WindowX/GetXResolution(), WindowY/GetYResolution()); 
	InitGraphics();
	InitConsole();

	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
	registerMouseEvent(MouseEventProcess);

	display();
}

void display()
{
	DisplayClear();

	DrawMenu();
}

void DrawMenu()
{
	double WindowW = WindowX/GetXResolution(), WindowH = WindowY/GetYResolution();
	double ButtonW = 1.0, ButtonH = 0.4;
	
	if(button(GenUIID(0), WindowW/2, WindowH/2, ButtonW, ButtonH, "OK")){
		printf("OK button clicked\n");
	}

	static char * menuListFile[] = {
		"File",  
		"Open  | Ctrl-O",
		"Close",
		"Exit   | Ctrl-E"};

	int selection; /* 菜单选择条目 */

	double MenuH = GetFontHeight() * 1.5; /* 菜单控件高度 */
	double MenuW = TextStringWidth(menuListFile[0])*2; /* 菜单控件宽度 */
	double wlist = TextStringWidth(menuListFile[3])*1.2;
	static char * selectedLabel = NULL;

	drawMenuBar(0, WindowH-MenuH, WindowW, MenuH);

	selection = menuList(GenUIID(0), 0, WindowH-MenuH, MenuW, wlist, MenuH, menuListFile, sizeof(menuListFile)/sizeof(menuListFile[0]));
	if(selection > 0) selectedLabel = menuListFile[selection];
	if(selection == 3)
		printf("exit\n");
}

void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event);
	display();
}

void CharEventProcess(char c)
{
	uiGetChar(c);
	display();
}

void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event);
	display();
}

#endif
