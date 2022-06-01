#ifndef _DRAW_H_
#define _DRAW_H_

#include "main.h"

extern bool inText;

void DrawAllObj();

void DrawLinkLine(void* Line_Obj);

void DrawAllText();

void DrawHArray(double x1, double y1, double x2, double y2, bool ExchangeX);
void DrawVArray(double x1, double y1, double x2, double y2, bool ExchangeY);


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
void EnLargeStartBox(double Times, void* ptr_Obj);
void EnLargeProcedureBox(double Times, void* ptr_Obj);
void EnLargeJudgeBox(double Times, void* ptr_Obj);


/* 功能:复制选中的对象
 * 参数:无
 * 返回值:无
 * 说明:若有对象被选中且按下 Ctrl+C, 则令 TEMP 指向该对象
 */
void CopyObj();

/* 功能:粘贴选中的对象
 * 参数:无
 * 返回值:无
 * 说明:在当前鼠标位置生成一个新对象,除位置外其余参数与 TEMP 指向的对象相同
 */
void PasteObj();

#endif