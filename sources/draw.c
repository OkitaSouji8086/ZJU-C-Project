#ifndef _DRAW_C_
#define _DRAW_C_

#include "draw.h"
#include "graphics.h"

void DrawAllObj()
{
	TraverseLinkedList(List[LINE], DrawLinkLine);
	TraverseLinkedList(List[STARTBOX], DrawStartBox);
	TraverseLinkedList(List[PROCEDUREBOX], DrawProcedureBox);
	TraverseLinkedList(List[JUDGEBOX], DrawJudgeBox);
}

void DrawLinkLine(void* Line_Obj)
{
	ptr_Line line = (ptr_Line)Line_Obj;
	bool ExchangeX = FALSE;

	double x1 = ((ptr_StartBox)line->Obj1)->x;
	double x2 = ((ptr_StartBox)line->Obj2)->x;

	double y1 = ((ptr_StartBox)line->Obj1)->y;
	double y2 = ((ptr_StartBox)line->Obj2)->y;
	double width1 = ((ptr_StartBox)line->Obj1)->width;
	double width2 = ((ptr_StartBox)line->Obj2)->width;

    int pensize = GetPenSize();/*保存当前系统笔画粗细*/
	string color = GetPenColor();/*保存当前系统颜色*/
	
	SetPenSize(line->PenSize);/*设置粗细*/
	SetPenColor(line->Color);/*设置颜色*/

	if(x1 > x2)
		ExchangeX = TRUE;
	
	if(!ExchangeX){
		DrawArray(x1 + width1/2, y1, x2 - width2/2, y2, ExchangeX);
	}else{
		DrawArray(x1 - width1/2, y1, x2 + width2/2, y2, ExchangeX);
	}

	SetPenSize(pensize);
	SetPenColor(color);
}

void DrawArray(double x1, double y1, double x2, double y2, bool ExchangeX)
{
	double zero = 0;
	double MidX = (x1 + x2)/2;

	MovePen(x1, y1);
	DrawLine(MidX - x1, zero);
	DrawLine(zero, y2 - y1);
	DrawLine(x2 - MidX, zero);
	if(!ExchangeX){
		DrawLine(-0.2, 0.1);
		DrawLine(0.2, -0.1);
		DrawLine(-0.2, -0.1);
	}else{
		DrawLine(0.2, 0.1);
		DrawLine(-0.2, -0.1);
		DrawLine(0.2, -0.1);
	}

}

void EnLargeObj(double Times, void* ptr_Obj, void (*fptr_EnLargeObj)(double Times, void* ptr_Obj))
{
	if(fptr_EnLargeObj == NULL) return;
	(*fptr_EnLargeObj)(Times, ptr_Obj);
}

void EnLargeProcedureBox(double Times, void* ptr_Obj)
{
	ptr_ProcedureBox ptr_temp = (ptr_ProcedureBox)ptr_Obj;
	ptr_temp->width *= Times;
	ptr_temp->height *= Times;
}

void EnLargeJudgeBox(double Times,void* ptr_Obj)
{
	ptr_JudgeBox ptr_temp = (ptr_JudgeBox)ptr_Obj;
	ptr_temp->width *= Times;
	ptr_temp->height *= Times;
}

void EnLargeStartBox(double Times,void* ptr_Obj)
{
	ptr_StartBox ptr_temp = (ptr_StartBox)ptr_Obj;
	ptr_temp->width *= Times;
	ptr_temp->height *= Times;
}

void CopyObj()
{
	if(CURR_OBJ == NULL) return;
	TEMP = CURR_OBJ;
	TEMP_KIND = CURR_OBJ_KIND;
}

void PasteObj()
{
	if(TEMP == NULL) return;

	ptr_StartBox StartBox_Obj;
	ptr_JudgeBox JudgeBox_Obj;
	ptr_ProcedureBox ProcedureBox_Obj;

	switch (TEMP_KIND)
	{
	case STARTBOX:
		StartBox_Obj = (ptr_StartBox)GetBlock(sizeof(*StartBox_Obj));

		StartBox_Obj->ID = CURR_ID;
		CURR_ID ++;

		StartBox_Obj->x = GetMouseX();
		StartBox_Obj->y = GetMouseY();
		StartBox_Obj->width = OBJWIDTH;
		StartBox_Obj->height = OBJHEIGHT;
		StartBox_Obj->PenSize = SYSPENSIZE;
		StartBox_Obj->Color = SYSCOLOR;
		StartBox_Obj->TextID = -1;
		StartBox_Obj->IsSelected = FALSE;

		DrawStartBox(StartBox_Obj);
		InsertNode(List[STARTBOX], NULL, StartBox_Obj);
		
		break;
	case JUDGEBOX:
		//
		break;
	case PROCEDUREBOX:
		//
		break;
	default:
		break;
	}
}

#endif
