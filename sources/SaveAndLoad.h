#ifndef _SaveAndLoad_H_
#define _SaveAndLoad_H_

#include "main.h"



void SaveAllObj();//保存所有当前对象// 


void DrawLineDSave(FILE *fp);
  /*
  保存直线
  fp是在SaveAllObj中创建的文件指针
  */ 
  
  
  void DrawProcedureSave(FILE *fp);   
  /*
  保存执行框
  */ 

void DrawJudgeSave(FILE *fp);
/*
保存判断框
*/ 

void DrawStartSave(FILE *fp);
/*
保存起始框
*/
void LoadAllObj();
/*
读 save.dat 中的数据到表中
*/
void DrawLineDLoad(FILE *fp);
/*
读取直线
*/
void DrawProcedureLoad(FILE *fp);
/*
读取执行框
*/
 void DrawJudgeLoad(FILE *fp);
/*
读取判断框
*/
void DrawStartLoad(FILE *fp);
/*
读取开始框 
*/
#endif
