#ifndef _DRAWBOX_C_
#define _DRAWBOX_C_

#include "drawbox.h"


//=============================================================================================================================================//
/* 默认值定义 */
//=============================================================================================================================================//



//=============================================================================================================================================//
/* 全局变量定义 */
//=============================================================================================================================================//



//=============================================================================================================================================//
/* 函数实现 */
//=============================================================================================================================================//


/*画直线*/
void LinkTwoObj(int ID1, int ID2)
{
	// int IDlast=COUNT[0]+COUNT[1]+COUNT[2]-1;
	
    int pensize = GetPenSize();/*保存当前系统笔画粗细*/
	string color = GetPenColor();/*保存当前系统颜色*/

    // // SetPenSize(SYSPENSIZE);/*设置粗细*/
	// // SetPenColor(SYSCOLOR);/*设置颜色*/

	// /*判断框的类型*/
	// if(ID1!=0&&ID2!=0&&ID1!=IDlast&&ID2!=IDlast){
	// 	ptr_ProcedureBox curr1;
	// 	ptr_ProcedureBox curr2;
	// }else if(ID1==0&&ID2==IDlast||ID1==IDlast&&ID2==0){
	// 	ptr_StartBox curr1;
	// 	ptr_StartBox curr2;
	// }else if((ID1==0||ID1==IDlast)&&(ID2!=IDlast&&ID2!=0)){
	// 	ptr_StartBox curr1;
	// 	ptr_ProcedureBox curr2;
	// }else if((ID1!=0&&ID1!=IDlast)&&(ID2==0||ID2==IDlast)){
	// 	ptr_ProcedureBox curr1;
	// 	ptr_StartBox curr2;
	// }

    ptr_ProcedureBox curr1 = NULL, curr2 = NULL;

	curr1 = (ptr_ProcedureBox)SearchObj(ID1);
	curr2 = (ptr_ProcedureBox)SearchObj(ID2);
	int x1=curr1->x;
	int x2=curr2->x;
	int y1=curr1->y;
	int y2=curr2->y;
	int t;

	if(y2>y1){
		/*交换参数，使得x1和y1是位于上面的框的坐标参数*/
		t=x1;
		x1=x2;
		x2=t;

		t=y1;
		y1=y2;
		y2=t;
	}
	
	/*先画横的线再画竖的线*/
	
	/*往右画横线*/
	if(x1<x2){
		MovePen(x1+curr1->width/2,y1);
		DrawLine(x2-x1-curr1->width/2,0);
		DrawLine(0,-(y1-y2-curr2->height/2));
	}
	/*往左画横线*/
	else{
		MovePen(x1-curr1->width/2,y1);
		DrawLine(-(x1-x2-curr1->width/2),0);
		DrawLine(0,-(y1-y2-curr2->height/2));
	}
	
    SetPenSize(pensize); /*恢复粗细*/
	SetPenColor(color);/*恢复颜色*/
}


/*画起始终止框*/
void DrawStartBox(void *StartBox)
{
    ptr_StartBox box = (ptr_StartBox)StartBox;
	double Width = box->width;
	double Height = box->height;
    double x_mid = box->x;
    double y_mid = box->y;

    int pensize = GetPenSize();/*保存当前系统笔画粗细*/
	string color = GetPenColor();/*保存当前系统颜色*/
    
    SetPenSize(box->PenSize);/*设置粗细*/
	SetPenColor(box->Color);/*设置颜色*/

    /*画椭圆起始终止框*/
    MovePen(x_mid + Width/2, y_mid);
    DrawEllipticalArc(Width , Height, 0.0, 360.0);

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
	drawRectangle(x_mid - Width/2, y_mid + Height/2, Width, Height, FALSE);

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

    SetPenSize(pensize); /*恢复粗细*/
	SetPenColor(color);/*恢复颜色*/
}


#endif
