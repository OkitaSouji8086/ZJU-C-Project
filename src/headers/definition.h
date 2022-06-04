#ifndef _DEFINATION_H_
#define _DEFINATION_H_

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
/* �궨�� */
//=============================================================================================================================================//

/* ����ģʽ */
#define _DEBUG_ 0

/* �������� */
#define NLIST 5
#define LINE 0
#define STARTBOX 1
#define PROCEDUREBOX 2
#define JUDGEBOX 3
#define INPUTANDOUTPUTBOX 4

#define TEXTLEN 100

#define TIMER 1
/* ��ǰ����״̬ */
typedef enum
{
	EDIT, /* �༭ */
	HELP, /* ��ʾ���� */
	ABOUT /* ��ʾ���� */
} mode;

typedef enum
{
	HORIZ,	 /* ˮƽ */
	VERTICAL /* ��ֱ */
} degree;

//=============================================================================================================================================//
/* �ṹ���� */
//=============================================================================================================================================//

/* ֱ�� */
typedef struct Line
{
	int ID_1; /* ��ʼ������ */
	int ID_2; /* ��ֹ������ */
	void *Obj1;
	void *Obj2;
	int PenSize;  /* ��ϸ */
	string Color; /* ��ɫ */
} * ptr_Line;

/* ��ʼ��ֹ�� */
typedef struct StartBox
{
	int ID;				  /* Ψһ������ */
	double x, y;		  /* �������� */
	double width, height; /* ���� */
	degree Degree;		  /* �Ƕ� */
	int PenSize;		  /* ��ϸ */
	string Color;		  /* ��ɫ */
	string Text;		  /* �ı���ָ�� */
	bool IsSelected;	  /* �Ƿ�ѡ�� */
} * ptr_StartBox;

/* ִ�п� */
typedef struct ProcedureBox
{
	int ID;				  /* Ψһ������ */
	double x, y;		  /* �������� */
	double width, height; /* ���� */
	degree Degree;		  /* �Ƕ� */
	int PenSize;		  /* ��ϸ */
	string Color;		  /* ��ɫ */
	string Text;		  /* �ı���ָ�� */
	bool IsSelected;	  /* �Ƿ�ѡ�� */
} * ptr_ProcedureBox;

/* �жϿ� */
typedef struct JudgeBox
{
	int ID;				  /* Ψһ������ */
	double x, y;		  /* �������� */
	double width, height; /* ���� */
	degree Degree;		  /* �Ƕ� */
	int PenSize;		  /* ��ϸ */
	string Color;		  /* ��ɫ */
	string Text;		  /* �ı���ָ�� */
	bool IsSelected;	  /* �Ƿ�ѡ�� */
} * ptr_JudgeBox;

/* ��������� */
typedef struct InputAndOutputBox
{
	int ID;				  /* Ψһ������ */
	double x, y;		  /* �������� */
	double width, height; /* ���� */
	degree Degree;		  /* �Ƕ� */
	int PenSize;		  /* ��ϸ */
	string Color;		  /* ��ɫ */
	string Text;		  /* �ı���ָ�� */
	bool IsSelected;	  /* �Ƿ�ѡ�� */
} * ptr_InputAndOutputBox;

//=============================================================================================================================================//
/* ������ */
//=============================================================================================================================================//

/* ÿ��Ԫ�ض���һ��ָ�� ֱ��/������ ��ָ�� */
extern linkedlistADT List[5];

//=============================================================================================================================================//
/* ȫ�ֱ������� */
//=============================================================================================================================================//

/* ÿ�ֶ���ĸ��� */
extern int COUNT[4];

/* ��ǰѡ�е�Ԫ��,û��ѡ��ʱΪNULL */
extern void *CURR_OBJ;
/* ��ǰѡ�е�Ԫ������,û��ѡ��ʱΪ-1 */
extern int CURR_OBJ_KIND;

/* ���а�,ָ����һ�������ƵĶ���,û����ΪNULL */
extern void *TEMP;
/* ���а��еĶ�������,û����Ϊ-1 */
extern int TEMP_KIND;

/* ��ǰ��ŵ��ڼ� */
extern int CURR_ID;

/* ��ǰ���ĵ㱻ռ�ݵĸ��� */
extern int CURR_OCCUPY;

/* �޸�CURR_OCCUPYʹ���ź� */
extern bool CURR_OCCUPY_EN;

/* ͼ��Ԫ��ѡ��״̬ */
extern bool IS_SELECTED;

extern bool IS_IN_TEXT;

extern bool OUT_OF_TEXT;

extern mode CURR_MODE;

//=============================================================================================================================================//
/* Ĭ��ֵ���� */
//=============================================================================================================================================//

/* Ĭ�ϻ�ͼ���� */
extern string SYS_COLOR;
extern string SEL_COLOR;
extern string EDIT_COLOR;
extern int SYS_PENSIZE;
extern double WINDOW_X;
extern double WINDOW_Y;

/* Ĭ�϶��󳤿� */
extern double OBJ_WIDTH;
extern double OBJ_HEIGHT;

#endif
