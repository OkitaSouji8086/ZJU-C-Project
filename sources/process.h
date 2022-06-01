#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "main.h"
#include "math.h"

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
bool equalfunptr_Text(void *obj1, void *obj2);

void PickNearestObj(double mx, double my);
double LtsDistance(void *ptr_Obj, double mx, double my);
bool IsInZone(double mx, double my, void *Obj);
#endif
