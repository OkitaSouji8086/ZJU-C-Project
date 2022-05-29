#ifndef _DRAWBOX_C_
#define _DRAWBOX_C_

#include "drawbox.h"


//=============================================================================================================================================//
/* Ĭ��ֵ���� */
//=============================================================================================================================================//

/* �˵��ؼ��߶� */
double MenuH = 0.4;

/* �˵��ؼ���� */
double MenuW = 1.0;



//=============================================================================================================================================//
/* ȫ�ֱ������� */
//=============================================================================================================================================//

/*�ж����ɵĿ���Ҫ������ƫ�ƶ��ٸ���λ*/
int i = 0;



//=============================================================================================================================================//
/* ����ʵ�� */
//=============================================================================================================================================//


/*��ֱ��*/
void LinkTwoObj(int ID1, int ID2)
{
	// int IDlast=COUNT[0]+COUNT[1]+COUNT[2]-1;
	
    int pensize = GetPenSize();/*���浱ǰϵͳ�ʻ���ϸ*/
	string color = GetPenColor();/*���浱ǰϵͳ��ɫ*/

    // // SetPenSize(SYSPENSIZE);/*���ô�ϸ*/
	// // SetPenColor(SYSCOLOR);/*������ɫ*/

	// /*�жϿ������*/
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
		/*����������ʹ��x1��y1��λ������Ŀ���������*/
		t=x1;
		x1=x2;
		x2=t;

		t=y1;
		y1=y2;
		y2=t;
	}
	
	/*�Ȼ�������ٻ�������*/
	
	/*���һ�����*/
	if(x1<x2){
		MovePen(x1+curr1->width/2,y1);
		DrawLine(x2-x1-curr1->width/2,0);
		DrawLine(0,-(y1-y2-curr2->height/2));
	}
	/*���󻭺���*/
	else{
		MovePen(x1-curr1->width/2,y1);
		DrawLine(-(x1-x2-curr1->width/2),0);
		DrawLine(0,-(y1-y2-curr2->height/2));
	}
	
    SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);/*�ָ���ɫ*/
}


/*��ִ�п�*/
void DrawProcedureBox(void *ProcedureBox)
{
    ptr_ProcedureBox box = (ptr_ProcedureBox)ProcedureBox;
    int Height=(box->height);
    int Width=(box->width);
    int x_mid=WindowX/2;
    int y_mid=WindowY/2;

    int pensize = GetPenSize();/*���浱ǰϵͳ�ʻ���ϸ*/
	string color = GetPenColor();/*���浱ǰϵͳ��ɫ*/

    SetPenSize(box->PenSize);/*���ô�ϸ*/
	SetPenColor(box->Color);/*������ɫ*/
    
    /*����ƫ������ʹ���ظ����ʱ���ɵĿ��������ƫ��*/
    int x_offset=Width/10;
    int y_offset=Height/10;
    
        
    /*������ִ�п�*/
    MovePen( x_mid - Width/2 + i*x_offset , y_mid + Height/2 - i*y_offset );
    DrawLine( Width , 0 );
    DrawLine( 0 , -Height );
    DrawLine( -Width , 0 );
    DrawLine( 0 , Height );

    /*¼����Ϣ*/
    box->x = x_mid + i*x_offset;
    box->y = y_mid - i*y_offset;
    box->ID = i;

    SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);/*�ָ���ɫ*/
    box->TextID = i;

    i++;
}


/*�������жϿ�*/
void DrawJudgeBox(void *JudgeBox)
{
    ptr_JudgeBox box = (ptr_JudgeBox)JudgeBox;
    int Height=(box->height);
    int Width=(box->width);
    int x_mid=WindowX/2;
    int y_mid=WindowY/2;

    int pensize = GetPenSize();/*���浱ǰϵͳ�ʻ���ϸ*/
	string color = GetPenColor();/*���浱ǰϵͳ��ɫ*/
    
    /*����ƫ������ʹ���ظ����ʱ���ɵĿ��������ƫ��*/
    int x_offset=Width/10;
    int y_offset=Height/10;

    /*�����������жϿ�*/
    MovePen( x_mid - Width/2 + i*x_offset , y_mid - i*y_offset );
    DrawLine( Width/2 , Height/2 );
    DrawLine( Width/2 , -Height/2 );
    DrawLine( -Width/2 , -Height/2 );
    DrawLine( -Width/2 , Height/2 );

    /*¼����Ϣ*/
    box->x = x_mid + i*x_offset;
    box->y = y_mid - i*y_offset;
    box->ID = i;
    box->TextID = i;

    SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);/*�ָ���ɫ*/

    i++;
}


/*����ʼ��ֹ��*/
void DrawStartBox(void *StartBox)
{
    ptr_StartBox box = (ptr_StartBox)StartBox;
    int Height=(box->height);
    int Width=(box->width);
    int x_mid=WindowX/2;
    int y_mid=WindowY/2;

    int pensize = GetPenSize();/*���浱ǰϵͳ�ʻ���ϸ*/
	string color = GetPenColor();/*���浱ǰϵͳ��ɫ*/
    
    /*����ƫ������ʹ���ظ����ʱ���ɵĿ��������ƫ��*/
    int x_offset=Width/10;
    int y_offset=Height/10;

    /*����Բ��ʼ��ֹ��*/
    MovePen(x_mid + i*x_offset + box->width , y_mid - i*y_offset);
    DrawEllipticalArc(box->width , box->height, 0.0, 360.0);

    /*¼����Ϣ*/
    box->x = x_mid + i*x_offset;
    box->y = y_mid - i*y_offset;
    box->ID = i;
    box->TextID = i;

    SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);/*�ָ���ɫ*/

    i++;
}

#endif
