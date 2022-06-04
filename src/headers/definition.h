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
/* 宏定义 */
//=============================================================================================================================================//

/* 调试模式 */
#define _DEBUG_ 0

/* 对象种类 */
#define NLIST 5
#define LINE 0
#define STARTBOX 1
#define PROCEDUREBOX 2
#define JUDGEBOX 3
#define INPUTANDOUTPUTBOX 4

#define TEXTLEN 100

#define TIMER 1
/* 当前所处状态 */
typedef enum
{
	EDIT, /* 编辑 */
	HELP, /* 显示帮助 */
	ABOUT /* 显示关于 */
} mode;

typedef enum
{
	HORIZ,	 /* 水平 */
	VERTICAL /* 垂直 */
} degree;

//=============================================================================================================================================//
/* 结构声明 */
//=============================================================================================================================================//

/* 直线 */
typedef struct Line
{
	int ID_1; /* 起始对象编号 */
	int ID_2; /* 终止对象编号 */
	void *Obj1;
	void *Obj2;
	int PenSize;  /* 粗细 */
	string Color; /* 颜色 */
} * ptr_Line;

/* 起始终止框 */
typedef struct StartBox
{
	int ID;				  /* 唯一对象编号 */
	double x, y;		  /* 中心坐标 */
	double width, height; /* 长宽 */
	degree Degree;		  /* 角度 */
	int PenSize;		  /* 粗细 */
	string Color;		  /* 颜色 */
	string Text;		  /* 文本框指针 */
	bool IsSelected;	  /* 是否选中 */
} * ptr_StartBox;

/* 执行框 */
typedef struct ProcedureBox
{
	int ID;				  /* 唯一对象编号 */
	double x, y;		  /* 中心坐标 */
	double width, height; /* 长宽 */
	degree Degree;		  /* 角度 */
	int PenSize;		  /* 粗细 */
	string Color;		  /* 颜色 */
	string Text;		  /* 文本框指针 */
	bool IsSelected;	  /* 是否选中 */
} * ptr_ProcedureBox;

/* 判断框 */
typedef struct JudgeBox
{
	int ID;				  /* 唯一对象编号 */
	double x, y;		  /* 中心坐标 */
	double width, height; /* 长宽 */
	degree Degree;		  /* 角度 */
	int PenSize;		  /* 粗细 */
	string Color;		  /* 颜色 */
	string Text;		  /* 文本框指针 */
	bool IsSelected;	  /* 是否选中 */
} * ptr_JudgeBox;

/* 输入输出框 */
typedef struct InputAndOutputBox
{
	int ID;				  /* 唯一对象编号 */
	double x, y;		  /* 中心坐标 */
	double width, height; /* 长宽 */
	degree Degree;		  /* 角度 */
	int PenSize;		  /* 粗细 */
	string Color;		  /* 颜色 */
	string Text;		  /* 文本框指针 */
	bool IsSelected;	  /* 是否选中 */
} * ptr_InputAndOutputBox;

//=============================================================================================================================================//
/* 链表定义 */
//=============================================================================================================================================//

/* 每个元素都是一个指向 直线/框链表 的指针 */
extern linkedlistADT List[5];

//=============================================================================================================================================//
/* 全局变量定义 */
//=============================================================================================================================================//

/* 每种对象的个数 */
extern int COUNT[4];

/* 当前选中的元素,没有选中时为NULL */
extern void *CURR_OBJ;
/* 当前选中的元素种类,没有选中时为-1 */
extern int CURR_OBJ_KIND;

/* 剪切板,指向上一个被复制的对象,没有则为NULL */
extern void *TEMP;
/* 剪切板中的对象种类,没有则为-1 */
extern int TEMP_KIND;

/* 当前编号到第几 */
extern int CURR_ID;

/* 当前中心点被占据的个数 */
extern int CURR_OCCUPY;

/* 修改CURR_OCCUPY使能信号 */
extern bool CURR_OCCUPY_EN;

/* 图形元素选中状态 */
extern bool IS_SELECTED;

extern bool IS_IN_TEXT;

extern bool OUT_OF_TEXT;

extern mode CURR_MODE;

//=============================================================================================================================================//
/* 默认值定义 */
//=============================================================================================================================================//

/* 默认绘图属性 */
extern string SYS_COLOR;
extern string SEL_COLOR;
extern string EDIT_COLOR;
extern int SYS_PENSIZE;
extern double WINDOW_X;
extern double WINDOW_Y;

/* 默认对象长宽 */
extern double OBJ_WIDTH;
extern double OBJ_HEIGHT;

#endif
