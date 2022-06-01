#ifndef _DRAW_C_
#define _DRAW_C_

#include "draw.h"
#include "graphics.h"
#include "string.h"

static string textbuf;

void DrawAllObj()
{
	TraverseLinkedList(List[LINE], DrawLinkLine);
	TraverseLinkedList(List[STARTBOX], DrawStartBox);
	TraverseLinkedList(List[PROCEDUREBOX], DrawProcedureBox);
	TraverseLinkedList(List[JUDGEBOX], DrawJudgeBox);
	TraverseLinkedList(List[INPUTANDOUTPUTBOX], DrawInputAndOutputBox);
}

void DrawLinkLine(void *Line_Obj)
{
	ptr_Line line = (ptr_Line)Line_Obj;
	bool ExchangeX = FALSE;
	bool ExchangeY = FALSE;
	bool HorV = TRUE;

	double x1 = ((ptr_StartBox)line->Obj1)->x;
	double x2 = ((ptr_StartBox)line->Obj2)->x;

	double y1 = ((ptr_StartBox)line->Obj1)->y;
	double y2 = ((ptr_StartBox)line->Obj2)->y;
	double width1 = ((ptr_StartBox)line->Obj1)->width;
	double width2 = ((ptr_StartBox)line->Obj2)->width;
	double height1 = ((ptr_StartBox)line->Obj1)->height;
	double height2 = ((ptr_StartBox)line->Obj2)->height;

	int pensize = GetPenSize();	  /*保存当前系统笔画粗细*/
	string color = GetPenColor(); /*保存当前系统颜色*/

	SetPenSize(line->PenSize); /*设置粗细*/
	SetPenColor(line->Color);  /*设置颜色*/

	if (fabs(x1 - x2) < 2.0)
		HorV = FALSE;
	if (fabs(y1 - y2) < 0.8)
		HorV = TRUE;

	if (HorV)
	{
		if (x1 > x2)
			ExchangeX = TRUE;

		if (!ExchangeX)
		{
			DrawHArray(x1 + width1 / 2, y1, x2 - width2 / 2, y2, ExchangeX);
		}
		else
		{
			DrawHArray(x1 - width1 / 2, y1, x2 + width2 / 2, y2, ExchangeX);
		}
	}
	else
	{
		if (y1 < y2)
			ExchangeY = TRUE;

		if (!ExchangeY)
		{
			DrawVArray(x1, y1 - height1 / 2, x2, y2 + height2 / 2, ExchangeY);
		}
		else
		{
			DrawVArray(x1, y1 + height1 / 2, x2, y2 - height2 / 2, ExchangeY);
		}
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
	double zero = 0;
	double MidY = (y1 + y2) / 2;

	MovePen(x1, y1);
	DrawLine(zero, MidY - y1);
	DrawLine(x2 - x1, zero);
	DrawLine(zero, y2 - MidY);
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

void EnLargeObj(double Times, void *ptr_Obj, void (*fptr_EnLargeObj)(double Times, void *ptr_Obj))
{
	if (fptr_EnLargeObj == NULL)
		return;
	(*fptr_EnLargeObj)(Times, ptr_Obj);
}

void EnLargeProcedureBox(double Times, void *ptr_Obj)
{
	ptr_ProcedureBox ptr_temp = (ptr_ProcedureBox)ptr_Obj;
	ptr_temp->width *= Times;
	ptr_temp->height *= Times;
}

void EnLargeJudgeBox(double Times, void *ptr_Obj)
{
	ptr_JudgeBox ptr_temp = (ptr_JudgeBox)ptr_Obj;
	ptr_temp->width *= Times;
	ptr_temp->height *= Times;
}

void EnLargeStartBox(double Times, void *ptr_Obj)
{
	ptr_StartBox ptr_temp = (ptr_StartBox)ptr_Obj;
	ptr_temp->width *= Times;
	ptr_temp->height *= Times;
}
#endif
