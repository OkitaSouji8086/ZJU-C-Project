#ifndef _DRAW_H_
#define _DRAW_H_

#include "main.h"


/* 功能:缩放对象
 * 参数1:缩放倍数
 * 参数2:对象指针
 * 参数3:给定缩放函数
 * 返回值:无
 * 说明:调用 给定缩放函数，缩放 给定指针指向的任意类型对象
 */
void EnLargeObj(double Times, void* ptr_Obj, void (*fptr_EnLargeObj)(double Times, void* ptr_Obj));


/* 功能:EnLargeObj辅助函数
 * 参数1:缩放倍数
 * 参数2:对象指针
 * 返回值:无
 * 说明:缩放 给定指针指向的特定类型对象
 */
void EnLargeProcedureBox(double Times, void* ptr_Obj); /* 放大 */
void EnLargeJudgeBox(double Times, void* ptr_Obj);
void EnLargeStartBox(double Times, void* ptr_Obj);

#endif