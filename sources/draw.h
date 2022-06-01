#ifndef _DRAW_H_
#define _DRAW_H_

#include "main.h"

extern bool inText;

void DrawAllObj();

void DrawLinkLine(void* Line_Obj);

void DrawAllText();

void DrawHArray(double x1, double y1, double x2, double y2, bool ExchangeX);
void DrawVArray(double x1, double y1, double x2, double y2, bool ExchangeY);


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
void EnLargeStartBox(double Times, void* ptr_Obj);
void EnLargeProcedureBox(double Times, void* ptr_Obj);
void EnLargeJudgeBox(double Times, void* ptr_Obj);


/* ����:����ѡ�еĶ���
 * ����:��
 * ����ֵ:��
 * ˵��:���ж���ѡ���Ұ��� Ctrl+C, ���� TEMP ָ��ö���
 */
void CopyObj();

/* ����:ճ��ѡ�еĶ���
 * ����:��
 * ����ֵ:��
 * ˵��:�ڵ�ǰ���λ������һ���¶���,��λ������������� TEMP ָ��Ķ�����ͬ
 */
void PasteObj();

#endif