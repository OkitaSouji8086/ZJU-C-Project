#ifndef _DRAW_H_
#define _DRAW_H_

#include "definition.h"

void display();

void DrawAllObj();

void DrawLinkLine(ptr_Line Line_Obj);

void DrawHArray(double x1, double y1, double x2, double y2, bool ExchangeX);
void DrawVArray(double x1, double y1, double x2, double y2, bool ExchangeY);

#endif
