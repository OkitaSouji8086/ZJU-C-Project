#ifndef _SaveAndLoad_H_
#define _SaveAndLoad_H_

#include "definition.h"

/* 功能:保存所有对象到save.data
 * 参数:无
 * 返回值:无
 */
void SaveAllObj();

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

/* 功能:从save.data读取
 * 参数:无
 * 返回值:无
 */
void LoadAllObj();

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
void DrawInputAndOutputBoxLoad(FILE *fp);
/*
读取输入输出
*/
void DrawInputAndOutputBoxSave(FILE *fp);
/*
保存输入输出
*/
#endif
