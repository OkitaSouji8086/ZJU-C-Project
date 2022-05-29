#ifndef _DRAW_C_
#define _DRAW_C_

#include "draw.h"

void EnLargeObj(double Times, void* ptr_Obj, void (*fptr_EnLargeObj)(double Times, void* ptr_Obj))
{
    if(fptr_EnLargeObj == NULL) return;
    (*fptr_EnLargeObj)(Times, ptr_Obj);
}

void EnLargeProcedureBox(double Times, void* ptr_Obj)
{
    ptr_ProcedureBox ptr_temp = (ptr_ProcedureBox)ptr_Obj;
    ptr_temp->width *= Times;
    ptr_temp->height *= Times;
}

void EnLargeJudgeBox(double Times,void* ptr_Obj)
{
    ptr_JudgeBox ptr_temp = (ptr_JudgeBox)ptr_Obj;
    ptr_temp->width *= Times;
    ptr_temp->height *= Times;
}

void EnLargeStartBox(double Times,void* ptr_Obj)
{
    ptr_StartBox ptr_temp = (ptr_StartBox)ptr_Obj;
    ptr_temp->width *= Times;
    ptr_temp->height *= Times;
}

void CopyObj()
{
    if(CURR_OBJ == NULL) return;
    TEMP = CURR_OBJ;
    TEMP_KIND = CURR_OBJ_KIND;
}

void PasteObj()
{
    if(TEMP == NULL) return;
    switch (TEMP_KIND)
    {
    case PROCEDUREBOX:
        /* code */
        break;
    case JUDGEBOX:
        //
        break;
    case STARTBOX:
        //
        break;
    default:
        break;
    }
}

#endif