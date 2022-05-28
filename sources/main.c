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
		"New   | Ctrl-N",
		"Open | Ctrl-O",
		"Save | Ctrl-S",
		"Exit   | Ctrl-E"};

	static char * menuListDraw[] = {
		"Draw",
		"1 | F1",
		"2 | F2",
		"3 | F3",
		"4 | F4"};

	static char * menuListEdit[] = {
		"Edit",
		"Copy    | Ctrl-C",
		"Paste   | Ctrl-V",
		"Delete  | Del"};

	static char * menuListHelp[] = {
		"Help",
		"About",
		"Help"};

	int selection; /* 菜单选中 */
	static char * selectedLabel = NULL;

	double MenuH = GetFontHeight() * 1.5; /* 菜单高度 */
	double MenuW = TextStringWidth(menuListFile[0])*2; /* 菜单标题宽度 */
	double wlist = TextStringWidth(menuListEdit[1])*1.2; /* 菜单条目宽度 */

	drawMenuBar(0, WindowH-MenuH, WindowW, MenuH);

	selection = menuList(GenUIID(0), 0, WindowH-MenuH, MenuW, wlist, MenuH, menuListFile, sizeof(menuListFile)/sizeof(menuListFile[0]));
	if(selection > 0) selectedLabel = menuListFile[selection];
	switch (selection)
	{
	case 1:
		printf("New clicked\n");
		break;
	case 2:
		printf("Open clicked\n");
		break;
	case 3:
		printf("Save clicked\n");
		break;
	case 4:
		printf("Exit clicked\n");
		break;
	default:
		break;
	}

	selection = menuList(GenUIID(0), MenuW, WindowH-MenuH, MenuW, wlist, MenuH, menuListDraw, sizeof(menuListDraw)/sizeof(menuListDraw[0]));
	if(selection > 0) selectedLabel = menuListFile[selection];
	switch (selection)
	{
	case 1:
		printf("1 clicked\n");
		break;
	case 2:
		printf("2 clicked\n");
		break;
	case 3:
		printf("3 clicked\n");
		break;
	case 4:
		printf("4 clicked\n");
		break;
	default:
		break;
	}

	selection = menuList(GenUIID(0), MenuW*2, WindowH-MenuH, MenuW, wlist, MenuH, menuListEdit, sizeof(menuListEdit)/sizeof(menuListEdit[0]));
	if(selection > 0) selectedLabel = menuListFile[selection];
	switch (selection)
	{
	case 1:
		printf("Copy clicked\n");
		break;
	case 2:
		printf("Paste clicked\n");
		break;
	case 3:
		printf("Delete clicked\n");
		break;
	default:
		break;
	}

	selection = menuList(GenUIID(0), MenuW*3, WindowH-MenuH, MenuW, wlist, MenuH, menuListHelp, sizeof(menuListHelp)/sizeof(menuListHelp[0]));
	if(selection > 0) selectedLabel = menuListFile[selection];
	switch (selection)
	{
	case 1:
		printf("About clicked\n");
		break;
	case 2:
		printf("Help clicked\n");
		break;
	default:
		break;
	}
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
