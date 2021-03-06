#ifndef _DRAWBOX_H_
#define _DRAWBOX_H_

#include "definition.h"

//=============================================================================================================================================//
/* 函数实现 */
//=============================================================================================================================================//

/* 功能:画执行框
 * 参数1:对象指针
 * 返回值:无
 * 说明:生成一个执行框
 */
void DrawStartBox(void *StartBox);
void DrawProcedureBox(void *ProcedureBox);
void DrawJudgeBox(void *JudgeBox);
void DrawInputAndOutputBox(void *InputAndOutputBox);

/* 功能:遍历链表,找到给定 ID 对应的对象
 * 参数:对象ID
 * 返回值:找到的对象指针
 */
extern void *SearchObj(int ID);

#endif
