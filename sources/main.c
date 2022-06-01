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
/* ������ */
//=============================================================================================================================================//

/* ÿ��Ԫ�ض���һ��ָ�� ֱ��/������ ��ָ�� */
linkedlistADT List[5] = {NULL, NULL, NULL, NULL, NULL};

//=============================================================================================================================================//
/* ȫ�ֱ������� */
//=============================================================================================================================================//

/* ÿ�ֶ���ĸ��� */
int COUNT[4] = {0, 0, 0, 0};

/* ��ǰѡ�е�Ԫ��,û��ѡ��ʱΪNULL */
void *CURR_OBJ = NULL;
/* ��ǰѡ�е�Ԫ������,û��ѡ��ʱΪ-1 */
int CURR_OBJ_KIND = -1;

/* ���а�,ָ����һ�������ƵĶ���,û����ΪNULL */
void *TEMP = NULL;
/* ���а��еĶ�������,û����Ϊ-1 */
int TEMP_KIND = -1;

/* ��ǰ��ŵ��ڼ� */
int CURR_ID = 0;

/* ��ǰ���ĵ㱻ռ�ݵĸ��� */
int CURR_OCCUPY = 0;

/* �޸�CURR_OCCUPYʹ���ź� */
static bool CURR_OCCUPY_EN = FALSE;

/* ͼ��Ԫ��ѡ��״̬ */
static bool isSelected = FALSE;

static bool isInText = FALSE;

static bool IsPaste = FALSE;

char _EMPTY_CHAR_[TEXTLEN + 1];

//=============================================================================================================================================//
/* Ĭ��ֵ���� */
//=============================================================================================================================================//

/* Ĭ�ϻ�ͼ���� */
string SYSCOLOR = "Red";
int SYSPENSIZE = 2;
double WindowX = 1280;
double WindowY = 720;

/* Ĭ�϶��󳤿� */
double OBJWIDTH = 1.0;
double OBJHEIGHT = 0.4;

//=============================================================================================================================================//
/* ����ʵ�� */
//=============================================================================================================================================//

void Main()
{
	int i;

	_EMPTY_CHAR_[0] = '\0';

	SetWindowTitle("Program Creater");
	SetWindowSize(ScaleXInches(WindowX), ScaleXInches(WindowY));
	InitGraphics();

#if _DEBUG_ == 1
	InitConsole();
#endif

	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
	registerMouseEvent(MouseEventProcess);
	registerTimerEvent(TimerEventProcess);

	startTimer(TIMER, 16);

	for (i = 0; i < NLIST; i++)
		List[i] = NewLinkedList();

#if _DEBUG_
	test();
#endif

	display();
}

void display()
{
	DisplayClear();

	DrawMenu();

	DrawAllObj();
}

void DrawMenu()
{
	double WindowW = WindowX / GetXResolution(), WindowH = WindowY / GetYResolution();
	double ButtonW = 1.0, ButtonH = 0.4;

	if (button(GenUIID(0), WindowW - ButtonW * 1.5, ButtonH / 2, ButtonW, ButtonH, "OK"))
	{
		printf("OK button clicked\n");
	}

	static char *menuListFile[] = {
		"File",
		"New   | Ctrl-N",
		"Open | Ctrl-O",
		"Save | Ctrl-S",
		"Exit   | Ctrl-E"};

	static char *menuListDraw[] = {
		"Draw",
		"1 | F1",
		"2 | F2",
		"3 | F3",
		"4 | F4"};

	static char *menuListEdit[] = {
		"Edit",
		"Copy    | Ctrl-C",
		"Paste   | Ctrl-V",
		"Delete  | Del"};

	static char *menuListHelp[] = {
		"Help",
		"About",
		"Help"};

	int selection; /* �˵�ѡ�� */
	static char *selectedLabel = NULL;

	double MenuH = GetFontHeight() * 1.5;				   /* �˵��߶� */
	double MenuW = TextStringWidth(menuListFile[0]) * 2;   /* �˵������� */
	double wlist = TextStringWidth(menuListEdit[1]) * 1.2; /* �˵���Ŀ��� */

	drawMenuBar(0, WindowH - MenuH, WindowW, MenuH);

	selection = menuList(GenUIID(0), 0, WindowH - MenuH, MenuW, wlist, MenuH, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection > 0)
		selectedLabel = menuListFile[selection];
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
		SaveAllObj();
		break;
	case 4:
		printf("Exit clicked\n");
		break;
	default:
		break;
	}

	selection = menuList(GenUIID(0), MenuW, WindowH - MenuH, MenuW, wlist, MenuH, menuListDraw, sizeof(menuListDraw) / sizeof(menuListDraw[0]));
	if (selection > 0)
		selectedLabel = menuListFile[selection];
	switch (selection)
	{
	case 1:
		CaseF1Process();
		break;
	case 2:
		CaseF2Process();
		break;
	case 3:
		CaseF3Process();
		break;
	case 4:
		CaseF4Process();
		break;
	default:
		break;
	}

	selection = menuList(GenUIID(0), MenuW * 2, WindowH - MenuH, MenuW, wlist, MenuH, menuListEdit, sizeof(menuListEdit) / sizeof(menuListEdit[0]));
	if (selection > 0)
		selectedLabel = menuListFile[selection];
	switch (selection)
	{
	case 1:
		CopyObj();
		break;
	case 2:
		PasteObj();
		break;
	case 3:
		if (CURR_OBJ != NULL)
		{
			DeleteObj(CURR_OBJ);
			CURR_OCCUPY--;
			CURR_OBJ = NULL;
			CURR_OBJ_KIND = -1;
			IsPaste = FALSE;
		}
		isSelected = FALSE;
		break;
	default:
		break;
	}

	selection = menuList(GenUIID(0), MenuW * 3, WindowH - MenuH, MenuW, wlist, MenuH, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	if (selection > 0)
		selectedLabel = menuListFile[selection];
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

	double ControlInfoW = TextStringWidth(menuListFile[0]) * 4;
	static char InfoBuffer[256];

	drawMenuBar(0, 0, WindowW, MenuH);

	if (isSelected)
	{
		if (isInText)
			sprintf(InfoBuffer, "Editing Text...");
		else
			sprintf(InfoBuffer, "Current Edited Object ID is: %d", ((ptr_StartBox)CURR_OBJ)->ID + 1);
	}
	else
		sprintf(InfoBuffer, "Not Selected.");

	drawLabel(MenuW, GetFontHeight() / 3, InfoBuffer);
}

void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event);
	display();

	switch (event)
	{
	case KEY_DOWN:
		switch (key)
		{
		case VK_F1: /*F1: ������ʼ��ֹ��*/
			CaseF1Process();
			break;

		case VK_F2: /*F2: �����жϿ�*/
			CaseF2Process();
			break;

		case VK_F3: /*F3: ����ִ�п�*/
			CaseF3Process();
			break;

		case VK_F4: /*F4���������������*/
			CaseF4Process();
			break;

		case VK_F5: /*F5���༭��ǰѡ�еĶ�����ı��� */
			CaseF5Process();
			break;

		case VK_F10: /*F10: �˳�����*/
			exit(1);
			break;

		case VK_BACK: /*BACKSP: �˸�*/
			break;

		case VK_ESCAPE: /*ESCAPE: �˳�����ѡ��״̬*/
			if (!isSelected)
				break;
			((ptr_StartBox)CURR_OBJ)->IsSelected = FALSE;
			((ptr_StartBox)CURR_OBJ)->Color = SYSCOLOR;
			isSelected = FALSE;
			IsPaste = FALSE;
			CURR_OBJ = NULL;
			CURR_OBJ_KIND = -1;

			break;

		case VK_CONTROL:

			break;

		case VK_DELETE:
			if (CURR_OBJ != NULL)
			{
				DeleteObj(CURR_OBJ);
				CURR_OCCUPY--;
				CURR_OBJ = NULL;
				CURR_OBJ_KIND = -1;
			}
			isSelected = FALSE;
			break;

		case 'O': /*Ctrl+O����save.data��ȡ*/
			if (flag == 1)
			{
				LoadAllObj();
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

	if (!isSelected)
		return;

	string curr_textbuf = ((ptr_StartBox)CURR_OBJ)->Text;
	int len = strlen(curr_textbuf);

	if (!isInText)
		return;
	switch (c)
	{
	case 27:   /*ESC*/
	case '\r': /* ע�⣺�س������ﷵ�ص��ַ���'\r'������'\n'*/
		isSelected = FALSE;
		isInText = FALSE;
		IsPaste = FALSE;
		((ptr_StartBox)CURR_OBJ)->IsSelected = FALSE;
		((ptr_StartBox)CURR_OBJ)->Color = SYSCOLOR;
		CURR_OBJ = NULL;
		CURR_OBJ_KIND = -1;
		break;
	case '\b': /*BACKSPACE*/
		if (len == 0)
			break;
		curr_textbuf[len - 1] = '\0';
		len--;
		break;
	default:
		curr_textbuf[len] = c;
		curr_textbuf[len + 1] = '\0';
		len++;
		break;
	}

	display();
}

void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event);

	static bool isChangeSize = FALSE;	/*���ű�־*/
	static bool isMove = FALSE;			/*�ƶ���־*/
	static double omx = 0.0, omy = 0.0; /*ǰһ�������*/
	double mx, my;						/*��ǰ�������*/
	double x1, y1, x2, y2, dx, dy;
	ptr_Line Line_Obj = NULL;
	int PreObjID = -1;
	void *PreObj = NULL;

	mx = ScaleXInches(x); /*pixels --> inches*/
	my = ScaleYInches(y); /*pixels --> inches*/

	switch (event)
	{
	case BUTTON_DOWN:
		if (isSelected)
		{ /*����ѡ��״̬*/
			omx = mx;
			omy = my;
			if (button == LEFT_BUTTON)
			{ /*������£������ƶ�״̬*/
				isMove = TRUE;
			}
			else if (button == RIGHT_BUTTON)
			{ /*�Ҽ������£���������״̬*/
				isChangeSize = TRUE;
			}
			break;
		}

		PickNearestObj(mx, my); /*ѡ�����*/
		if (CURR_OBJ_KIND == -1)
			break;
		((ptr_StartBox)CURR_OBJ)->Color = "GREEN";
		((ptr_StartBox)CURR_OBJ)->IsSelected = TRUE;

		isSelected = TRUE;
		CURR_OCCUPY_EN = TRUE;
		DrawAllObj();
		break;
	case BUTTON_DOUBLECLICK:
		if (isSelected)
		{
			PreObj = CURR_OBJ;
			PreObjID = ((ptr_StartBox)CURR_OBJ)->ID;

			PickNearestObj(mx, my);
			if (CURR_OBJ_KIND == -1)
				break;

			if (((ptr_StartBox)CURR_OBJ)->ID != PreObjID || IsPaste)
			{
				((ptr_StartBox)PreObj)->IsSelected = FALSE;
				((ptr_StartBox)PreObj)->Color = SYSCOLOR;
				((ptr_StartBox)CURR_OBJ)->IsSelected = TRUE;
				((ptr_StartBox)CURR_OBJ)->Color = "GREEN";
				Line_Obj = (ptr_Line)GetBlock(sizeof(*Line_Obj));
				Line_Obj->Obj1 = PreObj;
				Line_Obj->ID_1 = PreObjID;
				Line_Obj->Obj2 = CURR_OBJ;
				Line_Obj->ID_2 = ((ptr_StartBox)CURR_OBJ)->ID;
				Line_Obj->PenSize = SYSPENSIZE;
				Line_Obj->Color = SYSCOLOR;
				Line_Obj->IsSelected = FALSE;
				DrawLinkLine(Line_Obj);
				InsertNode(List[LINE], NULL, Line_Obj);
				if (PreObj == (ptr_StartBox)TEMP)
				{
					IsPaste = FALSE;
					((ptr_StartBox)TEMP)->IsSelected = FALSE;
					((ptr_StartBox)TEMP)->Color = SYSCOLOR;
					TEMP = NULL;
					TEMP_KIND = -1;
				}
			}
			else
			{
				CaseF5Process();
			}
		}
		break;
	case BUTTON_UP:
		isMove = FALSE;		  /*�˳��ƶ�״̬*/
		isChangeSize = FALSE; /*�˳�����״̬*/
		break;
	case MOUSEMOVE:
		if (isSelected && (isMove || isChangeSize))
		{ /*ѡ��״̬�£��ƶ�������*/
			SetEraseMode(TRUE);
			DrawAllObj();
			dx = mx - omx;
			dy = my - omy;
			if (isMove)
			{ /*�ƶ�*/
				((ptr_StartBox)CURR_OBJ)->x += dx;
				((ptr_StartBox)CURR_OBJ)->y += dy;
			}

			else if (isChangeSize)
			{ /*����*/
				((ptr_StartBox)CURR_OBJ)->width += dx;
				((ptr_StartBox)CURR_OBJ)->height = ((ptr_StartBox)CURR_OBJ)->width * OBJHEIGHT / OBJWIDTH;
			}
			omx = mx;
			omy = my;
			if (CURR_OCCUPY_EN)
			{
				CURR_OCCUPY--;
				CURR_OCCUPY_EN = FALSE;
			}
			SetEraseMode(FALSE);
			DrawAllObj();
		}
		break;
	}
	display();
}

void TimerEventProcess(int timerID)
{
	display();
	printf("TimerCallback.\n");
}

void CaseF1Process()
{
	/* ��Ļ���ĵ����� */
	double MidX = GetWindowWidth() / 2;
	double MidY = GetWindowHeight() / 2;

	ptr_StartBox PastedObj;
	string textbuf = CopyString(_EMPTY_CHAR_);

	PastedObj = (ptr_StartBox)GetBlock(sizeof(*PastedObj));

	PastedObj->ID = CURR_ID;
	CURR_ID++;

	PastedObj->x = MidX + CURR_OCCUPY * OBJWIDTH / 2;
	PastedObj->y = MidY - CURR_OCCUPY * OBJHEIGHT / 2;
	PastedObj->width = OBJWIDTH;
	PastedObj->height = OBJHEIGHT;
	PastedObj->PenSize = SYSPENSIZE;
	PastedObj->Color = SYSCOLOR;
	PastedObj->Text = textbuf;
	PastedObj->IsSelected = FALSE;

	CURR_OCCUPY++;

	InsertNode(List[STARTBOX], NULL, PastedObj);
}

void CaseF2Process()
{
	/* ��Ļ���ĵ����� */
	double MidX = GetWindowWidth() / 2;
	double MidY = GetWindowHeight() / 2;

	ptr_ProcedureBox ProcedureBox_Obj;
	string textbuf = CopyString(_EMPTY_CHAR_);

	ProcedureBox_Obj = (ptr_ProcedureBox)GetBlock(sizeof(*ProcedureBox_Obj));

	ProcedureBox_Obj->ID = CURR_ID;
	CURR_ID++;

	ProcedureBox_Obj->x = MidX + CURR_OCCUPY * OBJWIDTH / 2;
	ProcedureBox_Obj->y = MidY - CURR_OCCUPY * OBJHEIGHT / 2;
	ProcedureBox_Obj->width = OBJWIDTH;
	ProcedureBox_Obj->height = OBJHEIGHT;
	ProcedureBox_Obj->PenSize = SYSPENSIZE;
	ProcedureBox_Obj->Color = SYSCOLOR;
	ProcedureBox_Obj->Text = textbuf;
	ProcedureBox_Obj->IsSelected = FALSE;

	CURR_OCCUPY++;

	InsertNode(List[PROCEDUREBOX], NULL, ProcedureBox_Obj);
}

void CaseF3Process()
{
	/* ��Ļ���ĵ����� */
	double MidX = GetWindowWidth() / 2;
	double MidY = GetWindowHeight() / 2;

	ptr_JudgeBox JudgeBox_Obj;
	string textbuf = CopyString(_EMPTY_CHAR_);

	JudgeBox_Obj = (ptr_JudgeBox)GetBlock(sizeof(*JudgeBox_Obj));

	JudgeBox_Obj->ID = CURR_ID;
	CURR_ID++;

	JudgeBox_Obj->x = MidX + CURR_OCCUPY * OBJWIDTH / 2;
	JudgeBox_Obj->y = MidY - CURR_OCCUPY * OBJHEIGHT / 2;
	JudgeBox_Obj->width = OBJWIDTH;
	JudgeBox_Obj->height = OBJHEIGHT;
	JudgeBox_Obj->PenSize = SYSPENSIZE;
	JudgeBox_Obj->Color = SYSCOLOR;
	JudgeBox_Obj->Text = textbuf;
	JudgeBox_Obj->IsSelected = FALSE;

	CURR_OCCUPY++;

	InsertNode(List[JUDGEBOX], NULL, JudgeBox_Obj);
}

void CaseF4Process()
{
	/* ��Ļ���ĵ����� */
	double MidX = GetWindowWidth() / 2;
	double MidY = GetWindowHeight() / 2;

	ptr_InputAndOutputBox InputAndOutputBox_Obj;
	string textbuf = CopyString(_EMPTY_CHAR_);

	InputAndOutputBox_Obj = (ptr_InputAndOutputBox)GetBlock(sizeof(*InputAndOutputBox_Obj));

	InputAndOutputBox_Obj->ID = CURR_ID;
	CURR_ID++;

	InputAndOutputBox_Obj->x = MidX + CURR_OCCUPY * OBJWIDTH / 2;
	InputAndOutputBox_Obj->y = MidY - CURR_OCCUPY * OBJHEIGHT / 2;
	InputAndOutputBox_Obj->width = OBJWIDTH;
	InputAndOutputBox_Obj->height = OBJHEIGHT;
	InputAndOutputBox_Obj->PenSize = SYSPENSIZE;
	InputAndOutputBox_Obj->Color = SYSCOLOR;
	InputAndOutputBox_Obj->Text = textbuf;
	InputAndOutputBox_Obj->IsSelected = FALSE;

	CURR_OCCUPY++;

	InsertNode(List[INPUTANDOUTPUTBOX], NULL, InputAndOutputBox_Obj);
}

void CaseF5Process()
{
	if (!isSelected)
		return;

	isInText = TRUE;
	((ptr_StartBox)CURR_OBJ)->Color = "BLACK";
}

void CopyObj()
{
	if (CURR_OBJ == NULL)
		return;

	TEMP = GetBlock(sizeof(*(ptr_StartBox)CURR_OBJ));

	((ptr_StartBox)TEMP)->x = ((ptr_StartBox)CURR_OBJ)->x + ((ptr_StartBox)CURR_OBJ)->width / 3;
	((ptr_StartBox)TEMP)->y = ((ptr_StartBox)CURR_OBJ)->y - ((ptr_StartBox)CURR_OBJ)->height / 3;
	((ptr_StartBox)TEMP)->width = ((ptr_StartBox)CURR_OBJ)->width;
	((ptr_StartBox)TEMP)->height = ((ptr_StartBox)CURR_OBJ)->height;
	((ptr_StartBox)TEMP)->PenSize = ((ptr_StartBox)CURR_OBJ)->PenSize;
	((ptr_StartBox)TEMP)->Color = ((ptr_StartBox)CURR_OBJ)->Color;
	((ptr_StartBox)TEMP)->Text = CopyString(((ptr_StartBox)CURR_OBJ)->Text);

	TEMP_KIND = CURR_OBJ_KIND;
}

void PasteObj()
{
	if (TEMP == NULL)
		return;

	void *PastedObj = GetBlock(sizeof(*(ptr_StartBox)TEMP));

	if (CURR_OBJ_KIND != -1)
	{
		((ptr_StartBox)CURR_OBJ)->IsSelected = FALSE;
		((ptr_StartBox)CURR_OBJ)->Color = SYSCOLOR;
	}

	((ptr_StartBox)PastedObj)->ID = ++CURR_ID;
	((ptr_StartBox)PastedObj)->x = ((ptr_StartBox)TEMP)->x;
	((ptr_StartBox)PastedObj)->y = ((ptr_StartBox)TEMP)->y;
	((ptr_StartBox)PastedObj)->width = ((ptr_StartBox)TEMP)->width;
	((ptr_StartBox)PastedObj)->height = ((ptr_StartBox)TEMP)->height;
	((ptr_StartBox)PastedObj)->PenSize = ((ptr_StartBox)TEMP)->PenSize;
	((ptr_StartBox)PastedObj)->Color = "GREEN";
	((ptr_StartBox)PastedObj)->Text = CopyString(((ptr_StartBox)TEMP)->Text);
	((ptr_StartBox)PastedObj)->IsSelected = TRUE;

	((ptr_StartBox)TEMP)->x = ((ptr_StartBox)TEMP)->x + ((ptr_StartBox)TEMP)->width / 3;
	((ptr_StartBox)TEMP)->y = ((ptr_StartBox)TEMP)->y - ((ptr_StartBox)TEMP)->height / 3;
	CURR_OBJ = PastedObj;

	switch (TEMP_KIND)
	{
	case STARTBOX:
		InsertNode(List[STARTBOX], NULL, PastedObj);
		CURR_OBJ_KIND = STARTBOX;
		break;
	case PROCEDUREBOX:
		InsertNode(List[PROCEDUREBOX], NULL, PastedObj);
		CURR_OBJ_KIND = PROCEDUREBOX;
		break;
	case JUDGEBOX:
		InsertNode(List[JUDGEBOX], NULL, PastedObj);
		CURR_OBJ_KIND = JUDGEBOX;
		break;
	case INPUTANDOUTPUTBOX:
		InsertNode(List[INPUTANDOUTPUTBOX], NULL, PastedObj);
		CURR_OBJ_KIND = INPUTANDOUTPUTBOX;
		break;
	default:
		break;
	}

	isSelected = TRUE;
	IsPaste = TRUE;
}

#endif
