#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "definition.h"

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

/* ����:���Ŷ���
 * ����1:���ű���
 * ����2:����ָ��
 * ����3:�������ź���
 * ����ֵ:��
 * ˵��:���� �������ź��������� ����ָ��ָ����������Ͷ���
 */
void EnLargeObj(double Times, void *ptr_Obj, void (*fptr_EnLargeObj)(double Times, void *ptr_Obj));

/* ����:EnLargeObj��������
 * ����1:���ű���
 * ����2:����ָ��
 * ����ֵ:��
 * ˵��:���� ����ָ��ָ����ض����Ͷ���
 */
void EnLargeProcedureBox(double Times, void *ptr_Obj);
void EnLargeJudgeBox(double Times, void *ptr_Obj);
void EnLargeStartBox(double Times, void *ptr_Obj);

/* ����:ɾ������
 * ����:����ָ�룬��CURR_OBJ
 * ����ֵ:��
 */
void DeleteObj(void *ptr_Obj);

/* ����:��������,�ҵ����� ID ��Ӧ�Ķ���
 * ����:����ID
 * ����ֵ:�ҵ��Ķ���ָ��
 */
void *SearchObj(int ID);

/* ����:SearchObj��������
 * ����1:������dataָ��
 * ����2:����ID
 * ����ֵ:�Ƿ����,���ΪTRUE
 */
bool equalfunptr_Line(void *obj1, void *obj2);
bool equalfunptr_PBox(void *obj1, void *obj2);
bool equalfunptr_JBox(void *obj1, void *obj2);
bool equalfunptr_SBox(void *obj1, void *obj2);
bool equalfunptr_IBox(void *obj1, void *obj2);

void PickNearestObj(double mx, double my);
double LtsDistance(void *ptr_Obj, double mx, double my);
bool IsInZone(double mx, double my, void *Obj);
#endif
