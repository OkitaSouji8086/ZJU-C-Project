#ifndef _DRAWBOX_H_
#define _DRAWBOX_H_

#include "main.h"

//=============================================================================================================================================//
/* ����ʵ�� */
//=============================================================================================================================================//

/* ����:��ִ�п�
 * ����1:����ָ��
 * ����ֵ:��
 * ˵��:����һ��ִ�п�
 */
void DrawStartBox(void *StartBox);
void DrawProcedureBox(void *ProcedureBox);
void DrawJudgeBox(void *JudgeBox);
void DrawInputAndOutputBox(void *InputAndOutputBox);

/* ����:��������,�ҵ����� ID ��Ӧ�Ķ���
 * ����:����ID
 * ����ֵ:�ҵ��Ķ���ָ��
 */
extern void *SearchObj(int ID);

#endif
