#ifndef _TEST_C_
#define _TEST_C_

#include "test.h"
#include "graphics.h"

void test()
{
    double WindowW = WindowX/GetXResolution(), WindowH = WindowY/GetYResolution();
    double zero = 0;

    printf("test\n");
    MovePen(zero, WindowH/2);
    DrawLine(WindowW, zero);
    MovePen(zero, WindowW/2);
    DrawLine(zero, WindowH);
}

#endif
