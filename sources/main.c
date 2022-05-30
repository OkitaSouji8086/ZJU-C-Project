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
#include "boolean.h"
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
/* 链表定义 */
//=============================================================================================================================================//


/* 每个元素都是一个指向 直线/框链表 的指针 */
linkedlistADT List[4] = {NULL, NULL, NULL, NULL};



//=============================================================================================================================================//
/* 全局变量定义 */
//=============================================================================================================================================//

/* 每种对象的个数 */
int COUNT[3] = {0, 0, 0};


/* 当前选中的元素,没有选中时为NULL */
void* CURR_OBJ = NULL;
/* 当前选中的元素种类,没有选中时为-1 */
int CURR_OBJ_KIND = -1;


/* 剪切板,指向上一个被复制的对象,没有则为NULL */
void* TEMP = NULL;
/* 剪切板中的对象种类,没有则为-1 */
int TEMP_KIND = -1;

/* ID数组,每个对象唯一 */
int ID[1000000];
/* TEXT数组 */
string TextID[1000000];

/* 当前编号到第几 */
int CURR_ID = 0;

/* 当前中心点被占据的个数 */
int CURR_OCCUPY = 0;

/* 鼠标状态机 */
int MOUSE_FSM;



//=============================================================================================================================================//
/* 默认值定义 */
//=============================================================================================================================================//

/* 默认绘图属性 */
string SYSCOLOR = "Red";
int SYSPENSIZE = 1;



//=============================================================================================================================================//
/* 函数实现 */
//=============================================================================================================================================//

void Main()
{
	int i;

	SetWindowTitle("Program Creater");
	SetWindowSize(WindowX/GetXResolution(), WindowY/GetYResolution()); 
	InitGraphics();
	InitConsole();

	Randomize(); /* 随机函数初始化 */
	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
	registerMouseEvent(MouseEventProcess);

	for (i = 0; i < NLIST; i++)
	{
		List[i] = NewLinkedList();
	}
	

	display();

	#if _DEBUG_
		test();
	#endif
}

void display()
{
	DisplayClear();

	DrawMenu();

	DrawAllObj();
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
		CaseF1Proccess();
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

	/* 屏幕中心点坐标 */
	double MidX = WindowX/GetXResolution()/2;
	double MidY = WindowY/GetYResolution()/2; 

    switch (event) {
        case KEY_DOWN:
            switch (key) {
                case VK_F1:/*F1: 绘制起始终止框*/
					CaseF1Proccess();
					break;

                case VK_F2:/*F2: 绘制判断框*/
                    
					CaseF2Proccess();
				 	//JudgeBox = (ptr_JudgeBox)GetBlock(sizeof(*JudgeBox));
				 	//JudgeBox->PenSize = GetPenSize();
				 	//JudgeBox->Color = GetPenColor();
				 	//JudgeBox->IsSelected = FALSE;
				 	//DrawJudgeBox(JudgeBox);
				 	//InsertNode(List[JUDGEBOX],NULL,JudgeBox);
					
					
                  break;

                 case VK_F3:/*F3: 绘制执行框*/
                    
					CaseF3Proccess();
				 	//ProcedureBox = (ptr_ProcedureBox)GetBlock(sizeof(*ProcedureBox));
				 	//ProcedureBox->PenSize = GetPenSize();
					//ProcedureBox->Color = GetPenColor();
				 	//ProcedureBox->IsSelected = FALSE;
				 	//DrawProcedureBox(ProcedureBox);
				 	//InsertNode(List[PROCEDUREBOX],NULL,ProcedureBox);
					
					break;

                case VK_F10:/*F4: 退出程序*/
                    exit(1);
                    break;
        
				case VK_BACK:/*BACKSP: 删除对象*/
					DeleteObj(CURR_OBJ);
					break;

				case VK_ESCAPE:/*ESCAPE: 退出对象选中状态*/
					CURR_OBJ=NULL;

					break;

                case VK_CONTROL:  
									
					
					break;

				case 'S':/*Ctrl+S：保存到save.data*/
					if(flag==1){
						SaveAllObj();
					}

					break;

				case 'O':/*Ctrl+O：从save.data读取*/
					if(flag==1){
						LoadAllObj();
					}

					break;

				case 'C':/*Ctrl+C：复制选中对象*/
					if(flag==1){
						CopyObj();
					}

					break;

				case 'V':/*Ctrl+V：粘贴对象*/
					if(flag==1){
						PasteObj(TEMP);
					}

					break;

			}	
		case KEY_UP:
            break;

	}
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


void CaseF1Proccess()
{
	/* 屏幕中心点坐标 */
	double MidX = WindowX/GetXResolution()/2;
	double MidY = WindowY/GetYResolution()/2; 

    ptr_Line Line_Obj;
    ptr_ProcedureBox ProcedureBox_Obj;
    ptr_StartBox StartBox_Obj;
	ptr_JudgeBox JudgeBox_Obj;

	StartBox_Obj = (ptr_StartBox)GetBlock(sizeof(*StartBox_Obj));

	StartBox_Obj->ID = CURR_ID;
	CURR_ID ++;

	StartBox_Obj->x = MidX + CURR_OCCUPY + OBJWIDTH/10;
	StartBox_Obj->y = MidY + CURR_OCCUPY + OBJHEIGHT/10;
	StartBox_Obj->width = OBJWIDTH;
	StartBox_Obj->height = OBJHEIGHT;
	StartBox_Obj->PenSize = SYSPENSIZE;
	StartBox_Obj->Color = SYSCOLOR;
	StartBox_Obj->TextID = -1;
	StartBox_Obj->IsSelected = FALSE;

	CURR_OCCUPY ++;

	DrawStartBox(StartBox_Obj);
	InsertNode(List[STARTBOX], NULL, StartBox_Obj);
}


void CaseF2Proccess()
{
	/* 屏幕中心点坐标 */
	double MidX = WindowX/GetXResolution()/2;
	double MidY = WindowY/GetYResolution()/2; 

    ptr_Line Line_Obj;
    ptr_ProcedureBox ProcedureBox_Obj;
    ptr_StartBox StartBox_Obj;
	ptr_JudgeBox JudgeBox_Obj;

	JudgeBox_Obj = (ptr_JudgeBox)GetBlock(sizeof(*JudgeBox_Obj));

	JudgeBox_Obj->ID = CURR_ID;
	CURR_ID ++;

	JudgeBox_Obj->x = MidX + CURR_OCCUPY + OBJWIDTH/10;
	JudgeBox_Obj->y = MidY + CURR_OCCUPY + OBJHEIGHT/10;
	JudgeBox_Obj->width = OBJWIDTH;
	JudgeBox_Obj->height = OBJHEIGHT;
	JudgeBox_Obj->PenSize = SYSPENSIZE;
	JudgeBox_Obj->Color = SYSCOLOR;
	JudgeBox_Obj->TextID = -1;
	JudgeBox_Obj->IsSelected = FALSE;

	CURR_OCCUPY ++;

	DrawJudgeBox(JudgeBox_Obj);
	InsertNode(List[JUDGEBOX], NULL, JudgeBox_Obj);
}

void CaseF3Proccess()
{
	/* 屏幕中心点坐标 */
	double MidX = WindowX/GetXResolution()/2;
	double MidY = WindowY/GetYResolution()/2; 

    ptr_Line Line_Obj;
    ptr_ProcedureBox ProcedureBox_Obj;
    ptr_StartBox StartBox_Obj;
	ptr_JudgeBox JudgeBox_Obj;

	ProcedureBox_Obj = (ptr_ProcedureBox)GetBlock(sizeof(*ProcedureBox_Obj));

	ProcedureBox_Obj->ID = CURR_ID;
	CURR_ID ++;

	ProcedureBox_Obj->x = MidX + CURR_OCCUPY + OBJWIDTH/10;
	ProcedureBox_Obj->y = MidY + CURR_OCCUPY + OBJHEIGHT/10;
	ProcedureBox_Obj->width = OBJWIDTH;
	ProcedureBox_Obj->height = OBJHEIGHT;
	ProcedureBox_Obj->PenSize = SYSPENSIZE;
	ProcedureBox_Obj->Color = SYSCOLOR;
	ProcedureBox_Obj->TextID = -1;
	ProcedureBox_Obj->IsSelected = FALSE;

	CURR_OCCUPY ++;

	DrawProcedureBox(ProcedureBox_Obj);
	InsertNode(List[PROCEDUREBOX], NULL, ProcedureBox_Obj);
}
#endif
