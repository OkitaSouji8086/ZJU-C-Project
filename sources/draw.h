#ifndef _DRAW_H_
#define _DRAW_H_

#include "main.h"


/* ����:���Ŷ���
 * ����1:���ű���
 * ����2:����ָ��
 * ����3:�������ź���
 * ����ֵ:��
 * ˵��:���� �������ź��������� ����ָ��ָ����������Ͷ���
 */
void EnLargeObj(double Times, void* ptr_Obj, void (*fptr_EnLargeObj)(double Times, void* ptr_Obj));


/* ����:EnLargeObj��������
 * ����1:���ű���
 * ����2:����ָ��
 * ����ֵ:��
 * ˵��:���� ����ָ��ָ����ض����Ͷ���
 */
void EnLargeProcedureBox(double Times, void* ptr_Obj); /* �Ŵ� */
void EnLargeJudgeBox(double Times, void* ptr_Obj);
void EnLargeStartBox(double Times, void* ptr_Obj);

#endif