#ifndef _DRAWBOX_C_
#define _DRAWBOX_C_

#include "drawbox.h"
#include "imgui.h"
#include "extgraph.h"


//=============================================================================================================================================//
/* 默认值定义 */
//=============================================================================================================================================//



//=============================================================================================================================================//
/* 全局变量定义 */
//=============================================================================================================================================//



//=============================================================================================================================================//
/* 函数实现 */
//=============================================================================================================================================//


/*画起始终止框*/
void DrawStartBox(void *StartBox)
{
    ptr_StartBox box = (ptr_StartBox)StartBox;
	double Width = box->width;
	double Height = box->height;
    double x_mid = box->x;
    double y_mid = box->y;
	double c=0;

    int pensize = GetPenSize();/*保存当前系统笔画粗细*/
	string color = GetPenColor();/*保存当前系统颜色*/
    
    SetPenSize(box->PenSize);/*设置粗细*/
	SetPenColor(box->Color);/*设置颜色*/

    /*画圆角矩形起始终止框*/
    MovePen( x_mid - Width/2, y_mid - Height/2);
	DrawLine(c, Height-0.2);
	DrawArc(0.1, c+180, c-90);
	DrawLine(Width-0.2, c);
	DrawArc(0.1, c+90, c-90);
	DrawLine(c, -(Height-0.2));
	DrawArc(0.1, c, c-90);
	DrawLine(-(Width-0.2), c);
	DrawArc(0.1, c-90, c-90);

    MovePen(x_mid - TextStringWidth(box->Text)/2, y_mid - GetFontHeight());
    DrawTextString(box->Text);

    SetPenSize(pensize); /*恢复粗细*/
	SetPenColor(color);/*恢复颜色*/
}

/*画执行框*/
void DrawProcedureBox(void *ProcedureBox)
{
    ptr_ProcedureBox box = (ptr_ProcedureBox)ProcedureBox;
	double Height = box->height;
    double Width = box->width;
    double x_mid = box->x;
    double y_mid = box->y;

    int pensize = GetPenSize();/*保存当前系统笔画粗细*/
	string color = GetPenColor();/*保存当前系统颜色*/

    SetPenSize(box->PenSize);/*设置粗细*/
	SetPenColor(box->Color);/*设置颜色*/
        
    /*画矩形执行框*/
	drawRectangle(x_mid - Width/2, y_mid - Height/2, Width, Height, FALSE);

    MovePen(x_mid - TextStringWidth(box->Text)/2, y_mid - GetFontHeight());
    DrawTextString(box->Text);

    SetPenSize(pensize); /*恢复粗细*/
	SetPenColor(color);/*恢复颜色*/
}


/*画条件判断框*/
void DrawJudgeBox(void *JudgeBox)
{
    ptr_JudgeBox box = (ptr_JudgeBox)JudgeBox;
    double Width = box->width;
    double Height = box->height;
    double x_mid = box->x;
    double y_mid = box->y;

    int pensize = GetPenSize();/*保存当前系统笔画粗细*/
	string color = GetPenColor();/*保存当前系统颜色*/
    
    SetPenSize(box->PenSize);/*设置粗细*/
	SetPenColor(box->Color);/*设置颜色*/
	

    /*画菱形条件判断框*/
    MovePen( x_mid - Width/2, y_mid);
    DrawLine( Width/2 , Height/2 );
    DrawLine( Width/2 , -Height/2 );
    DrawLine( -Width/2 , -Height/2 );
    DrawLine( -Width/2 , Height/2 );

    MovePen(x_mid - TextStringWidth(box->Text)/2, y_mid - GetFontHeight());
    DrawTextString(box->Text);

    SetPenSize(pensize); /*恢复粗细*/
	SetPenColor(color);/*恢复颜色*/
}


#endif
