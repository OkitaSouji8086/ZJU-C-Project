#ifndef _DRAWBOX_H_
#define _DRAWBOX_H_

#include "main.h"

/* 功能:连接两个控件
 * 参数1:ID1
 * 参数2:ID2
 * 返回值:无
 * 说明:新增一条直线，连接两个控件
 */
void LinkTwoObj(int ID1, int ID2);


/* 功能:画执行框
 * 参数1:对象指针
 * 返回值:无
 * 说明:生成一个执行框，并且每次生成都从中心位置往右下偏移一点
 */
void DrawProcedureBox(void *ProcedureBox);


void DrawJudgeBox(void *JudgeBox);
void DrawJudgeBox(void *JudgeBox);
void DrawStartBox(void *StartBox);

/* 功能:遍历链表,找到给定 ID 对应的对象
 * 参数:对象ID
 * 返回值:找到的对象指针
 */
extern void* SearchObj(int ID);

#endif
