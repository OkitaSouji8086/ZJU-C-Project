#ifndef _DRAW_C_
#define _DRAW_C_

#include "definition.h"
#include "draw.h"
#include "drawbox.h"

void display()
{
	DisplayClear();

	DrawMenu();

	DrawAllObj();

	if (CURR_MODE == HELP)
		DrawHelp();

	if (CURR_MODE == ABOUT)
		DrawAbout();
}

void DrawAllObj()
{
	TraverseLinkedList(List[LINE], DrawLinkLine);
	TraverseLinkedList(List[STARTBOX], DrawStartBox);
	TraverseLinkedList(List[PROCEDUREBOX], DrawProcedureBox);
	TraverseLinkedList(List[JUDGEBOX], DrawJudgeBox);
	TraverseLinkedList(List[INPUTANDOUTPUTBOX], DrawInputAndOutputBox);
}

void DrawLinkLine(ptr_Line Line_Obj)
{
	bool ExchangeX = FALSE;
	bool ExchangeY = FALSE;
	bool HorV = TRUE;

	double x1 = ((ptr_StartBox)Line_Obj->Obj1)->x;
	double x2 = ((ptr_StartBox)Line_Obj->Obj2)->x;
	double y1 = ((ptr_StartBox)Line_Obj->Obj1)->y;
	double y2 = ((ptr_StartBox)Line_Obj->Obj2)->y;
	double width1 = ((ptr_StartBox)Line_Obj->Obj1)->Degree == HORIZ ? ((ptr_StartBox)Line_Obj->Obj1)->width : ((ptr_StartBox)Line_Obj->Obj1)->height;
	double width2 = ((ptr_StartBox)Line_Obj->Obj2)->Degree == HORIZ ? ((ptr_StartBox)Line_Obj->Obj2)->width : ((ptr_StartBox)Line_Obj->Obj2)->height;
	double height1 = ((ptr_StartBox)Line_Obj->Obj1)->Degree == HORIZ ? ((ptr_StartBox)Line_Obj->Obj1)->height : ((ptr_StartBox)Line_Obj->Obj1)->width;
	double height2 = ((ptr_StartBox)Line_Obj->Obj2)->Degree == HORIZ ? ((ptr_StartBox)Line_Obj->Obj2)->height : ((ptr_StartBox)Line_Obj->Obj2)->width;

	int pensize = GetPenSize();	  /*保存当前系统笔画粗细*/
	string color = GetPenColor(); /*保存当前系统颜色*/

	SetPenSize(Line_Obj->PenSize); /*设置粗细*/
	SetPenColor(Line_Obj->Color);  /*设置颜色*/

	if (fabs(x1 - x2) < 2.0)
		HorV = FALSE;
	if (fabs(y1 - y2) < 0.8)
		HorV = TRUE;

	if (HorV)
	{
		if (x1 > x2)
			ExchangeX = TRUE;

		if (!ExchangeX)
			DrawHArray(x1 + width1 / 2, y1, x2 - width2 / 2, y2, ExchangeX);
		else
			DrawHArray(x1 - width1 / 2, y1, x2 + width2 / 2, y2, ExchangeX);
	}
	else
	{
		if (y1 < y2)
			ExchangeY = TRUE;

		if (!ExchangeY)
			DrawVArray(x1, y1 - height1 / 2, x2, y2 + height2 / 2, ExchangeY);
		else
			DrawVArray(x1, y1 + height1 / 2, x2, y2 - height2 / 2, ExchangeY);
	}

	SetPenSize(pensize);
	SetPenColor(color);
}

void DrawHArray(double x1, double y1, double x2, double y2, bool ExchangeX)
{
	double zero = 0;
	double MidX = (x1 + x2) / 2;

	MovePen(x1, y1);
	DrawLine(MidX - x1, zero);
	DrawLine(zero, y2 - y1);
	DrawLine(x2 - MidX, zero);
	if (!ExchangeX)
	{
		DrawLine(-0.15, 0.05);
		DrawLine(0.15, -0.05);
		DrawLine(-0.15, -0.05);
	}
	else
	{
		DrawLine(0.15, 0.05);
		DrawLine(-0.15, -0.05);
		DrawLine(0.15, -0.05);
	}
}

void DrawVArray(double x1, double y1, double x2, double y2, bool ExchangeY)
{
	double MidY = (y1 + y2) / 2;

	MovePen(x1, y1);
	DrawLine(0, MidY - y1);
	DrawLine(x2 - x1, 0);
	DrawLine(0, y2 - MidY);
	if (!ExchangeY)
	{
		DrawLine(-0.05, 0.15);
		DrawLine(0.05, -0.15);
		DrawLine(0.05, 0.15);
	}
	else
	{
		DrawLine(-0.05, -0.15);
		DrawLine(0.05, 0.15);
		DrawLine(0.05, -0.15);
	}
}

#endif
