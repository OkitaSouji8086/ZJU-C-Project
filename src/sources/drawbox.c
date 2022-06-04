#ifndef _DRAWBOX_C_
#define _DRAWBOX_C_

#include "definition.h"
#include "drawbox.h"

//=============================================================================================================================================//
/* ����ʵ�� */
//=============================================================================================================================================//

/*����ʼ��ֹ��*/
void DrawStartBox(void *StartBox)
{
	ptr_StartBox box = (ptr_StartBox)StartBox;
	double Width = box->Degree == HORIZ ? box->width : box->height;
	double Height = box->Degree == HORIZ ? box->height : box->width;
	double x_mid = box->x;
	double y_mid = box->y;
	double Chamfer = Height / 8;

	int pensize = GetPenSize();	  /*���浱ǰϵͳ�ʻ���ϸ*/
	string color = GetPenColor(); /*���浱ǰϵͳ��ɫ*/
	int pointsize = GetPointSize();

	SetPenSize(box->PenSize); /*���ô�ϸ*/
	SetPenColor(box->Color);  /*������ɫ*/

	/*��Բ�Ǿ�����ʼ��ֹ��*/
	MovePen(x_mid - Width / 2, y_mid - Height / 2 + Chamfer);
	DrawLine(0, Height - 2 * Chamfer);
	DrawArc(Chamfer, 180, -90);
	DrawLine(Width - 2 * Chamfer, 0);
	DrawArc(Chamfer, 90, -90);
	DrawLine(0, -(Height - 2 * Chamfer));
	DrawArc(Chamfer, 0, -90);
	DrawLine(-(Width - 2 * Chamfer), 0);
	DrawArc(Chamfer, -90, -90);

	if (Width * 20 > pointsize)
		SetPointSize(Width * 20);

	MovePen(x_mid - TextStringWidth(box->Text) / 2, y_mid - GetFontAscent() / 2);
	DrawTextString(box->Text);

	SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);	 /*�ָ���ɫ*/
	SetPointSize(pointsize);

	COUNT[0]++;
}

/*��ִ�п�*/
void DrawProcedureBox(void *ProcedureBox)
{
	ptr_ProcedureBox box = (ptr_ProcedureBox)ProcedureBox;
	double Width = box->Degree == HORIZ ? box->width : box->height;
	double Height = box->Degree == HORIZ ? box->height : box->width;
	double x_mid = box->x;
	double y_mid = box->y;

	int pensize = GetPenSize();	  /*���浱ǰϵͳ�ʻ���ϸ*/
	string color = GetPenColor(); /*���浱ǰϵͳ��ɫ*/
	int pointsize = GetPointSize();

	SetPenSize(box->PenSize); /*���ô�ϸ*/
	SetPenColor(box->Color);  /*������ɫ*/

	/*������ִ�п�*/
	drawRectangle(x_mid - Width / 2, y_mid - Height / 2, Width, Height, FALSE);

	if (Width * 20 > pointsize)
		SetPointSize(Width * 20);

	MovePen(x_mid - TextStringWidth(box->Text) / 2, y_mid - GetFontHeight() / 2);
	DrawTextString(box->Text);

	SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);	 /*�ָ���ɫ*/
	SetPointSize(pointsize);

	COUNT[1]++;
}

/*�������жϿ�*/
void DrawJudgeBox(void *JudgeBox)
{
	ptr_JudgeBox box = (ptr_JudgeBox)JudgeBox;
	double Width = box->Degree == HORIZ ? box->width : box->height;
	double Height = box->Degree == HORIZ ? box->height : box->width;
	double x_mid = box->x;
	double y_mid = box->y;

	int pensize = GetPenSize();	  /*���浱ǰϵͳ�ʻ���ϸ*/
	string color = GetPenColor(); /*���浱ǰϵͳ��ɫ*/
	int pointsize = GetPointSize();

	SetPenSize(box->PenSize); /*���ô�ϸ*/
	SetPenColor(box->Color);  /*������ɫ*/

	/*�����������жϿ�*/
	MovePen(x_mid - Width / 2, y_mid);
	DrawLine(Width / 2, Height / 2);
	DrawLine(Width / 2, -Height / 2);
	DrawLine(-Width / 2, -Height / 2);
	DrawLine(-Width / 2, Height / 2);

	if (Width * 20 > pointsize)
		SetPointSize(Width * 20);

	MovePen(x_mid - TextStringWidth(box->Text) / 2, y_mid - GetFontHeight() / 2);
	DrawTextString(box->Text);

	SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);	 /*�ָ���ɫ*/
	SetPointSize(pointsize);

	COUNT[2]++;
}

/*�����������*/
void DrawInputAndOutputBox(void *InputAndOutputBox)
{
	ptr_InputAndOutputBox box = (ptr_InputAndOutputBox)InputAndOutputBox;
	double Width = box->Degree == HORIZ ? box->width : box->height;
	double Height = box->Degree == HORIZ ? box->height : box->width;
	double x_mid = box->x;
	double y_mid = box->y;

	int pensize = GetPenSize();	  /*���浱ǰϵͳ�ʻ���ϸ*/
	string color = GetPenColor(); /*���浱ǰϵͳ��ɫ*/
	int pointsize = GetPointSize();

	SetPenSize(box->PenSize); /*���ô�ϸ*/
	SetPenColor(box->Color);  /*������ɫ*/

	/*��ƽ���ı��������жϿ�*/
	MovePen(x_mid - Width / 2 - Height / 8, y_mid - Height / 2);
	DrawLine(Height / 4, Height);
	DrawLine(Width, 0);
	DrawLine(-Height / 4, -Height);
	DrawLine(-Width, 0);

	if (Width * 20 > pointsize)
		SetPointSize(Width * 20);

	MovePen(x_mid - TextStringWidth(box->Text) / 2, y_mid - GetFontHeight() / 2);
	DrawTextString(box->Text);

	SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);	 /*�ָ���ɫ*/
	SetPointSize(pointsize);

	COUNT[3]++;
}

#endif
