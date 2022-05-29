#ifndef _DRAWBOX_H_
#define _DRAWBOX_H_

#include "main.h"

/* ����:���������ؼ�
 * ����1:ID1
 * ����2:ID2
 * ����ֵ:��
 * ˵��:����һ��ֱ�ߣ����������ؼ�
 */
void LinkTwoObj(int ID1, int ID2);


/* ����:��ִ�п�
 * ����1:����ָ��
 * ����ֵ:��
 * ˵��:����һ��ִ�п򣬲���ÿ�����ɶ�������λ��������ƫ��һ��
 */
void DrawProcedureBox(void *ProcedureBox);


void DrawJudgeBox(void *JudgeBox);
void DrawJudgeBox(void *JudgeBox);
void DrawStartBox(void *StartBox);

/* ����:��������,�ҵ����� ID ��Ӧ�Ķ���
 * ����:����ID
 * ����ֵ:�ҵ��Ķ���ָ��
 */
extern void* SearchObj(int ID);

#endif
