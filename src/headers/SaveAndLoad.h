#ifndef _SaveAndLoad_H_
#define _SaveAndLoad_H_

#include "definition.h"

/* ����:�������ж���save.data
 * ����:��
 * ����ֵ:��
 */
void SaveAllObj();

void DrawLineDSave(FILE *fp);
/*
����ֱ��
fp����SaveAllObj�д������ļ�ָ��
*/

void DrawProcedureSave(FILE *fp);
/*
����ִ�п�
*/

void DrawJudgeSave(FILE *fp);
/*
�����жϿ�
*/

void DrawStartSave(FILE *fp);
/*
������ʼ��
*/

/* ����:��save.data��ȡ
 * ����:��
 * ����ֵ:��
 */
void LoadAllObj();

void DrawLineDLoad(FILE *fp);
/*
��ȡֱ��
*/
void DrawProcedureLoad(FILE *fp);
/*
��ȡִ�п�
*/
void DrawJudgeLoad(FILE *fp);
/*
��ȡ�жϿ�
*/
void DrawStartLoad(FILE *fp);
/*
��ȡ��ʼ��
*/
void DrawInputAndOutputBoxLoad(FILE *fp);
/*
��ȡ�������
*/
void DrawInputAndOutputBoxSave(FILE *fp);
/*
�����������
*/
#endif
