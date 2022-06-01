#ifndef _DRAWBOX_C_
#define _DRAWBOX_C_

#include "drawbox.h"
#include "imgui.h"
#include "extgraph.h"


//=============================================================================================================================================//
/* Ĭ��ֵ���� */
//=============================================================================================================================================//



//=============================================================================================================================================//
/* ȫ�ֱ������� */
//=============================================================================================================================================//



//=============================================================================================================================================//
/* ����ʵ�� */
//=============================================================================================================================================//


/*����ʼ��ֹ��*/
void DrawStartBox(void *StartBox)
{
    ptr_StartBox box = (ptr_StartBox)StartBox;
	double Width = box->width;
	double Height = box->height;
    double x_mid = box->x;
    double y_mid = box->y;
    double Chamfer = Height/8;
	double c=0;

    int pensize = GetPenSize();/*���浱ǰϵͳ�ʻ���ϸ*/
	string color = GetPenColor();/*���浱ǰϵͳ��ɫ*/
    
    SetPenSize(box->PenSize);/*���ô�ϸ*/
	SetPenColor(box->Color);/*������ɫ*/

    /*��Բ�Ǿ�����ʼ��ֹ��*/
    MovePen( x_mid - Width/2, y_mid - Height/2 + Chamfer);
	DrawLine(c, Height - 2*Chamfer);
	DrawArc(Chamfer, c+180, c-90);
	DrawLine(Width - 2*Chamfer, c);
	DrawArc(Chamfer, c+90, c-90);
	DrawLine(c, -(Height - 2*Chamfer));
	DrawArc(Chamfer, c, c-90);
	DrawLine(-(Width - 2*Chamfer), c);
	DrawArc(Chamfer, c-90, c-90);

    MovePen(x_mid - TextStringWidth(box->Text)/2, y_mid - GetFontHeight()/2);
    DrawTextString(box->Text);

    SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);/*�ָ���ɫ*/

    COUNT[0]++;
}

/*��ִ�п�*/
void DrawProcedureBox(void *ProcedureBox)
{
    ptr_ProcedureBox box = (ptr_ProcedureBox)ProcedureBox;
	double Height = box->height;
    double Width = box->width;
    double x_mid = box->x;
    double y_mid = box->y;

    int pensize = GetPenSize();/*���浱ǰϵͳ�ʻ���ϸ*/
	string color = GetPenColor();/*���浱ǰϵͳ��ɫ*/

    SetPenSize(box->PenSize);/*���ô�ϸ*/
	SetPenColor(box->Color);/*������ɫ*/
        
    /*������ִ�п�*/
	drawRectangle(x_mid - Width/2, y_mid - Height/2, Width, Height, FALSE);

    MovePen(x_mid - TextStringWidth(box->Text)/2, y_mid - GetFontHeight()/2);
    DrawTextString(box->Text);

    SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);/*�ָ���ɫ*/

    COUNT[1]++;
}


/*�������жϿ�*/
void DrawJudgeBox(void *JudgeBox)
{
    ptr_JudgeBox box = (ptr_JudgeBox)JudgeBox;
    double Width = box->width;
    double Height = box->height;
    double x_mid = box->x;
    double y_mid = box->y;

    int pensize = GetPenSize();/*���浱ǰϵͳ�ʻ���ϸ*/
	string color = GetPenColor();/*���浱ǰϵͳ��ɫ*/
    
    SetPenSize(box->PenSize);/*���ô�ϸ*/
	SetPenColor(box->Color);/*������ɫ*/
	

    /*�����������жϿ�*/
    MovePen( x_mid - Width/2, y_mid);
    DrawLine( Width/2 , Height/2 );
    DrawLine( Width/2 , -Height/2 );
    DrawLine( -Width/2 , -Height/2 );
    DrawLine( -Width/2 , Height/2 );

    MovePen(x_mid - TextStringWidth(box->Text)/2, y_mid - GetFontHeight()/2);
    DrawTextString(box->Text);

    SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);/*�ָ���ɫ*/

    COUNT[2]++;
}

/*�����������*/
void DrawInputAndOutputBox(void *InputAndOutputBox)
{
    ptr_InputAndOutputBox box = (ptr_InputAndOutputBox)InputAndOutputBox;
    double Width = box->width;
    double Height = box->height;
    double x_mid = box->x;
    double y_mid = box->y;

    int pensize = GetPenSize();/*���浱ǰϵͳ�ʻ���ϸ*/
	string color = GetPenColor();/*���浱ǰϵͳ��ɫ*/
    
    SetPenSize(box->PenSize);/*���ô�ϸ*/
	SetPenColor(box->Color);/*������ɫ*/
	

    /*��ƽ���ı��������жϿ�*/
    MovePen( x_mid - Width/2 - Height/8, y_mid - Height/2);
    DrawLine( Height/4, Height );
    DrawLine( Width , 0 );
    DrawLine( -Height/4 , -Height );
    DrawLine( -Width , 0 );

    MovePen(x_mid - TextStringWidth(box->Text)/2, y_mid - GetFontHeight()/2);
    DrawTextString(box->Text);

    SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);/*�ָ���ɫ*/

    COUNT[3]++;
}


#endif
