#ifndef _DRAWBOX_C_
#define _DRAWBOX_C_

#include "drawbox.h"


//=============================================================================================================================================//
/* 默认值定义 */
//=============================================================================================================================================//



//=============================================================================================================================================//
/* 全局变量定义 */
//=============================================================================================================================================//

/*判断生成的框需要往右下偏移多少个单位*/
int i = 0;



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


/*画执行框*/
void DrawProcedureBox(void *ProcedureBox)
{
    ptr_ProcedureBox box = (ptr_ProcedureBox)ProcedureBox;
    //int Height=(box->height);
    //int Width=(box->width);
    int x_mid = box->x;
    int y_mid = box->y;

    int pensize = GetPenSize();/*保存当前系统笔画粗细*/
	string color = GetPenColor();/*保存当前系统颜色*/

    
    /*定义偏移量，使得重复点击时生成的框会往右下偏移*/
    //int x_offset=box->width/10;
    //int y_offset=box->height/10;
    
        
    /*画矩形执行框*/
    MovePen( x_mid - box->width , y_mid + box->height );
    DrawLine( box->width , 0 );
    DrawLine( 0 , -box->height );
    DrawLine( -box->width , 0 );
    DrawLine( 0 , box->height );

    /*录入信息*/
    //box->x = x_mid + i*x_offset;
    //box->y = y_mid - i*y_offset;
    //box->ID = i;
    //box->TextID = i;

    SetPenSize(pensize); /*恢复粗细*/
	SetPenColor(color);/*恢复颜色*/

    i++;
}


/*画条件判断框*/
void DrawJudgeBox(void *JudgeBox)
{
    ptr_JudgeBox box = (ptr_JudgeBox)JudgeBox;
    //int Height=(box->height);
    //int Width=(box->width);
    int x_mid = box->x;
    int y_mid= box->y;

    int pensize = GetPenSize();/*保存当前系统笔画粗细*/
	string color = GetPenColor();/*保存当前系统颜色*/
    
    /*定义偏移量，使得重复点击时生成的框会往右下偏移*/
    //int x_offset=box->width/10;
    //int y_offset=box->height/10;

    /*画菱形条件判断框*/
    MovePen( x_mid - box->width , y_mid );
    DrawLine( box->width , box->height );
    DrawLine( box->width , -box->height );
    DrawLine( -box->width , -box->height );
    DrawLine( -box->width , box->height );

    /*录入信息*/
    //box->x = x_mid + i*x_offset;
    //box->y = y_mid - i*y_offset;
    //box->ID = i;
    //box->TextID = i;

    SetPenSize(pensize); /*恢复粗细*/
	SetPenColor(color);/*恢复颜色*/

    i++;
}


/*画起始终止框*/
void DrawStartBox(void *StartBox)
{
    ptr_StartBox box = (ptr_StartBox)StartBox;
    int x_mid = box->x;
    int y_mid = box->y;

    int pensize = GetPenSize();/*保存当前系统笔画粗细*/
	string color = GetPenColor();/*保存当前系统颜色*/
    

    /*画椭圆起始终止框*/
    MovePen(x_mid + box->width , y_mid);
    DrawEllipticalArc(box->width , box->height, 0.0, 360.0);

    /*录入信息*/
    // box->x = x_mid + i*x_offset;
    // box->y = y_mid - i*y_offset;
    // box->ID = i;
    // box->TextID = i;

    SetPenSize(pensize); /*恢复粗细*/
	SetPenColor(color);/*恢复颜色*/

    i++;
}

#endif
