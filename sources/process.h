#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "main.h"

/* ����:ɾ������
 * ����:����ָ�룬��CURR_OBJ
 * ����ֵ:��
 */
void DeleteObj(void* ptr_Obj);


/* ����:��������,�ҵ����� ID ��Ӧ�Ķ���
 * ����:����ID
 * ����ֵ:�ҵ��Ķ���ָ��
 */
void* SearchObj(int ID);

/* ����:SearchObj��������
 * ����1:������dataָ��
 * ����2:����ID
 * ����ֵ:�Ƿ����,���ΪTRUE
 */
bool equalfunptr_PBox(void *obj1, void *obj2);
bool equalfunptr_JBox(void *obj1, void *obj2);
bool equalfunptr_SBox(void *obj1, void *obj2);


#endif