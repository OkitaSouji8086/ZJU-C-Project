#ifndef _TEST_C_
#define _TEST_C_

#include "test.h"
#include "graphics.h"

void test()
{
	double WindowW = WindowX / GetXResolution(), WindowH = WindowY / GetYResolution();

	printf("test\n");
	MovePen(0, WindowH / 2);
	DrawLine(WindowW, 0);
	MovePen(0, WindowW / 2);
	DrawLine(0, WindowH);
}

#endif
