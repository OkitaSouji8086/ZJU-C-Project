#ifndef _SaveAndLoad_H_
#define _SaveAndLoad_H_

#include "main.h"



void SaveAllObj();//�������е�ǰ����// 


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
void LoadAllObj();
/*
�� save.dat �е����ݵ�����
*/
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
#endif
