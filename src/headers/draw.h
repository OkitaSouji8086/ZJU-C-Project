#ifndef _DRAW_H_
#define _DRAW_H_

#include "definition.h"

/* 功能:重新绘制所有图形
 * 参数:无
 * 返回值:无
 */
void display();

/* 功能:绘制所有对象
 * 参数:无
 * 返回值:无
 */
void DrawAllObj();

void DrawLinkLine(ptr_Line Line_Obj);

void DrawHArray(double x1, double y1, double x2, double y2, bool ExchangeX);
void DrawVArray(double x1, double y1, double x2, double y2, bool ExchangeY);

#endif
