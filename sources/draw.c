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

void DrawLinkLine(void* Line_Obj)
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

	int pensize = GetPenSize();/*保存当前系统笔画粗细*/
	string color = GetPenColor();/*保存当前系统颜色*/
	
	SetPenSize(line->PenSize);/*设置粗细*/
	SetPenColor(line->Color);/*设置颜色*/

	if(fabs(x1 - x2) < 2.0) HorV = FALSE;
	if(fabs(y1 - y2) < 0.8) HorV = TRUE;

	if(HorV){
		if(x1 > x2)
			ExchangeX = TRUE;

		if(!ExchangeX){
			DrawHArray(x1 + width1/2, y1, x2 - width2/2, y2, ExchangeX);
		}else{
			DrawHArray(x1 - width1/2, y1, x2 + width2/2, y2, ExchangeX);
		}
	}else{
		if(y1 < y2)
			ExchangeY = TRUE;
		
		if(!ExchangeY){
			DrawVArray(x1, y1 - height1/2, x2, y2 + height2/2, ExchangeY);
		}else{
			DrawVArray(x1, y1 + height1/2, x2, y2 - height2/2, ExchangeY);
		}
	}
	

	SetPenSize(pensize);
	SetPenColor(color);
}

void DrawHArray(double x1, double y1, double x2, double y2, bool ExchangeX)
{
	double zero = 0;
	double MidX = (x1 + x2)/2;

	MovePen(x1, y1);
	DrawLine(MidX - x1, zero);
	DrawLine(zero, y2 - y1);
	DrawLine(x2 - MidX, zero);
	if(!ExchangeX){
		DrawLine(-0.15, 0.05);
		DrawLine(0.15, -0.05);
		DrawLine(-0.15, -0.05);
	}else{
		DrawLine(0.15, 0.05);
		DrawLine(-0.15, -0.05);
		DrawLine(0.15, -0.05);
	}
}

void DrawVArray(double x1, double y1, double x2, double y2, bool ExchangeY)
{
	double zero = 0;
	double MidY = (y1 + y2)/2;

	MovePen(x1, y1);
	DrawLine(zero, MidY - y1);
	DrawLine(x2 - x1, zero);
	DrawLine(zero, y2 - MidY);
	if(!ExchangeY){
		DrawLine(-0.05, 0.15);
		DrawLine(0.05, -0.15);
		DrawLine(0.05, 0.15);
	}else{
		DrawLine(-0.05, -0.15);
		DrawLine(0.05, 0.15);
		DrawLine(0.05, -0.15);
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
	ptr_ProcedureBox ProcedureBox_Obj;
	ptr_JudgeBox JudgeBox_Obj;
	ptr_InputAndOutputBox InputAndOutputBox_Obj;
	string textbuf = CopyString(((ptr_StartBox)TEMP)->Text);

	((ptr_StartBox)CURR_OBJ)->IsSelected = FALSE;
	((ptr_StartBox)CURR_OBJ)->Color = SYSCOLOR;

	switch (TEMP_KIND)
	{
	case STARTBOX:
		StartBox_Obj = (ptr_StartBox)GetBlock(sizeof(*StartBox_Obj));

		StartBox_Obj->x = ((ptr_StartBox)CURR_OBJ)->x + ((ptr_StartBox)CURR_OBJ)->width/3;
		StartBox_Obj->y = ((ptr_StartBox)CURR_OBJ)->y - ((ptr_StartBox)CURR_OBJ)->height/3;
		StartBox_Obj->width = ((ptr_StartBox)CURR_OBJ)->width;
		StartBox_Obj->height = ((ptr_StartBox)CURR_OBJ)->height;
		StartBox_Obj->PenSize = SYSPENSIZE;
		StartBox_Obj->Color = "GREEN";
		StartBox_Obj->Text = textbuf;
		StartBox_Obj->IsSelected = TRUE;

		DrawStartBox(StartBox_Obj);

		InsertNode(List[STARTBOX], NULL, StartBox_Obj);

		CURR_OBJ = StartBox_Obj;
		CURR_OBJ_KIND = STARTBOX;
		
		break;
	case PROCEDUREBOX:
		ProcedureBox_Obj = (ptr_ProcedureBox)GetBlock(sizeof(*ProcedureBox_Obj));

		ProcedureBox_Obj->ID = CURR_ID;
		CURR_ID ++;

		ProcedureBox_Obj->x = ((ptr_ProcedureBox)CURR_OBJ)->x + ((ptr_ProcedureBox)CURR_OBJ)->width/3;
		ProcedureBox_Obj->y = ((ptr_ProcedureBox)CURR_OBJ)->y - ((ptr_ProcedureBox)CURR_OBJ)->height/3;
		ProcedureBox_Obj->width = ((ptr_ProcedureBox)CURR_OBJ)->width;
		ProcedureBox_Obj->height = ((ptr_ProcedureBox)CURR_OBJ)->height;
		ProcedureBox_Obj->PenSize = SYSPENSIZE;
		ProcedureBox_Obj->Color = "GREEN";
		ProcedureBox_Obj->Text = textbuf;
		ProcedureBox_Obj->IsSelected = TRUE;

		DrawProcedureBox(ProcedureBox_Obj);
		InsertNode(List[PROCEDUREBOX], NULL, ProcedureBox_Obj);

		CURR_OBJ = ProcedureBox_Obj;
		CURR_OBJ_KIND = PROCEDUREBOX;

		break;
	case JUDGEBOX:
		JudgeBox_Obj = (ptr_JudgeBox)GetBlock(sizeof(*JudgeBox_Obj));

		JudgeBox_Obj->ID = CURR_ID;
		CURR_ID ++;

		JudgeBox_Obj->x = ((ptr_JudgeBox)CURR_OBJ)->x + ((ptr_JudgeBox)CURR_OBJ)->width/3;
		JudgeBox_Obj->y = ((ptr_JudgeBox)CURR_OBJ)->y - ((ptr_JudgeBox)CURR_OBJ)->height/3;
		JudgeBox_Obj->width = ((ptr_JudgeBox)CURR_OBJ)->width;
		JudgeBox_Obj->height = ((ptr_JudgeBox)CURR_OBJ)->height;
		JudgeBox_Obj->PenSize = SYSPENSIZE;
		JudgeBox_Obj->Color = "GREEN";
		JudgeBox_Obj->Text = textbuf;
		JudgeBox_Obj->IsSelected = TRUE;

		DrawJudgeBox(JudgeBox_Obj);
		InsertNode(List[JUDGEBOX], NULL, JudgeBox_Obj);

		CURR_OBJ = JudgeBox_Obj;
		CURR_OBJ_KIND = JUDGEBOX;

		break;
	case INPUTANDOUTPUTBOX:
		InputAndOutputBox_Obj = (ptr_InputAndOutputBox)GetBlock(sizeof(*InputAndOutputBox_Obj));

		InputAndOutputBox_Obj->ID = CURR_ID;
		CURR_ID ++;

		InputAndOutputBox_Obj->x = ((ptr_InputAndOutputBox)CURR_OBJ)->x + ((ptr_InputAndOutputBox)CURR_OBJ)->width/3;
		InputAndOutputBox_Obj->y = ((ptr_InputAndOutputBox)CURR_OBJ)->y - ((ptr_InputAndOutputBox)CURR_OBJ)->height/3;
		InputAndOutputBox_Obj->width = ((ptr_InputAndOutputBox)CURR_OBJ)->width;
		InputAndOutputBox_Obj->height = ((ptr_InputAndOutputBox)CURR_OBJ)->height;
		InputAndOutputBox_Obj->PenSize = SYSPENSIZE;
		InputAndOutputBox_Obj->Color = "GREEN";
		InputAndOutputBox_Obj->Text = textbuf;
		InputAndOutputBox_Obj->IsSelected = TRUE;

		DrawInputAndOutputBox(InputAndOutputBox_Obj);
		InsertNode(List[INPUTANDOUTPUTBOX], NULL, InputAndOutputBox_Obj);

		CURR_OBJ = InputAndOutputBox_Obj;
		CURR_OBJ_KIND = INPUTANDOUTPUTBOX;

		break;
	default:
		break;
	}
}

#endif
