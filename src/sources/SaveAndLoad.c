#ifndef _SaveAndLoad_C_
#define _SaveAndLoad_C_

#include "definition.h"
#include "SaveAndLoad.h"

static char r = 'r';
static char l = 'l';
static char g = 'g';
static char b = 'b';

void SaveAllObj();				  //保存所有对象，链表，到“save.data"，fp是相应的文件指针//
void DrawLineDSave(FILE *fp);	  /*保存直线*/
void DrawProcedureSave(FILE *fp); /*保存执行框*/
void DrawJudgeSave(FILE *fp);	  /*保存判断框*/
void DrawStartSave(FILE *fp);	  /*保存起始框*/
void LoadAllObj();
void DrawLineDLoad(FILE *fp);			  /*读取线*/
void DrawProcedureLoad(FILE *fp);		  /*读取执行框*/
void DrawJudgeLoad(FILE *fp);			  /*读取判断框*/
void DrawStartLoad(FILE *fp);			  /*读取起始框*/
void DrawInputAndOutputBoxLoad(FILE *fp); /*读取输入输出框*/
void DrawInputAndOutputBoxSave(FILE *fp); /*保存输入输出框*/

void SaveAllObj()
//保存所有对象//
{
	FILE *fp = fopen("save.dat", "wb");

	DrawProcedureSave(fp);
	DrawJudgeSave(fp);
	DrawStartSave(fp);
	DrawInputAndOutputBoxSave(fp);
	DrawLineDSave(fp);

	fclose(fp);
}
void DrawLineDSave(FILE *fp)
//保存直线//
{

	linkedlistADT nodeptr;
	unsigned int i = LINE;
	ptr_Line data;

	nodeptr = List[LINE]->next;

	while (nodeptr != NULL)
	{
		data = nodeptr->dataptr;

		fwrite(&i, sizeof(unsigned int), 1, fp);
		fwrite(&data->ID_1, sizeof(int), 1, fp);
		fwrite(&data->ID_2, sizeof(int), 1, fp);
		fwrite(&data->PenSize, sizeof(int), 1, fp);

		nodeptr = nodeptr->next;
	}
}

void DrawProcedureSave(FILE *fp)
//保存执行框//
{
	linkedlistADT nodeptr;
	unsigned int i = 1, s_len = 0;

	ptr_ProcedureBox data;
	nodeptr = List[PROCEDUREBOX]->next;
	while (nodeptr != NULL)
	{
		data = nodeptr->dataptr;
		fwrite(&i, sizeof(unsigned int), 1, fp);
		fwrite(&data->ID, sizeof(int), 1, fp);
		fwrite(&data->x, sizeof(double), 1, fp);
		fwrite(&data->y, sizeof(double), 1, fp);
		fwrite(&data->width, sizeof(double), 1, fp);
		fwrite(&data->height, sizeof(double), 1, fp);

		s_len = strlen(data->Text);
		fwrite(&s_len, sizeof(unsigned int), 1, fp);
		fwrite(data->Text, sizeof(char), s_len, fp);
		fwrite(&data->Degree, sizeof(degree), 1, fp);
		nodeptr = nodeptr->next;
	}
}

void DrawJudgeSave(FILE *fp)
//保存判断框//
{
	linkedlistADT nodeptr;
	unsigned int i = 2, s_len = 0;

	ptr_JudgeBox data;
	nodeptr = List[JUDGEBOX]->next;
	while (nodeptr != NULL)
	{
		data = nodeptr->dataptr;
		fwrite(&i, sizeof(unsigned int), 1, fp);
		fwrite(&data->ID, sizeof(int), 1, fp);
		fwrite(&data->x, sizeof(double), 1, fp);
		fwrite(&data->y, sizeof(double), 1, fp);
		fwrite(&data->width, sizeof(double), 1, fp);
		fwrite(&data->height, sizeof(double), 1, fp);

		s_len = strlen(data->Text);
		fwrite(&s_len, sizeof(unsigned int), 1, fp);
		fwrite(data->Text, sizeof(char), s_len, fp);
		fwrite(&data->Degree, sizeof(degree), 1, fp);
		nodeptr = nodeptr->next;
	}
}

void DrawStartSave(FILE *fp)
//保存起始框//
{
	linkedlistADT nodeptr;
	unsigned int i = 3, s_len = 0;

	ptr_StartBox data;
	nodeptr = List[STARTBOX]->next;
	while (nodeptr != NULL)
	{
		data = nodeptr->dataptr;
		fwrite(&i, sizeof(unsigned int), 1, fp);
		fwrite(&data->ID, sizeof(int), 1, fp);
		fwrite(&data->x, sizeof(double), 1, fp);
		fwrite(&data->y, sizeof(double), 1, fp);
		fwrite(&data->width, sizeof(double), 1, fp);
		fwrite(&data->height, sizeof(double), 1, fp);

		s_len = strlen(data->Text);
		fwrite(&s_len, sizeof(unsigned int), 1, fp);
		fwrite(data->Text, sizeof(char), s_len, fp);
		fwrite(&data->Degree, sizeof(degree), 1, fp);

		nodeptr = nodeptr->next;
	}
}

void LoadAllObj()
//读取所有对象，因为保存的时候按照对象，在第一个元素设置了一个“标识符”ObjKind，所以可以通过循环和条件语句进行读取//
{
	FILE *fp = fopen("save.dat", "rb");
	unsigned int ObjKind;

	ptr_Line LineData;
	ptr_ProcedureBox ProcedureData;
	ptr_JudgeBox JudgeData;
	ptr_StartBox StartData;

	while (1)
	{
		fread(&ObjKind, sizeof(unsigned int), 1, fp);
		if (feof(fp))
			break;
		switch (ObjKind)
		{
		case 0:
			DrawLineDLoad(fp);
			break;
		case 1:
			DrawProcedureLoad(fp);
			break;
		case 2:
			DrawJudgeLoad(fp);
			break;
		case 3:
			DrawStartLoad(fp);
			break;
		case 4:
			DrawInputAndOutputBoxLoad(fp);
			break;
		default:
			break;
		}
	}

	fclose(fp);
}

void DrawLineDLoad(FILE *fp)
//读取直线//

{
	char mid;
	ptr_Line data = (ptr_Line)malloc(sizeof(*data));

	fread(&data->ID_1, sizeof(int), 1, fp);
	fread(&data->ID_2, sizeof(int), 1, fp);
	fread(&data->PenSize, sizeof(int), 1, fp);

	data->Color = "Red";

	data->Obj1 = SearchObj(data->ID_1);

	//特色区域，保存用ID，读取出来用函数SearchObj将ID转换为指针//

	data->Obj2 = SearchObj(data->ID_2);

	InsertNode(List[LINE], NULL, data);
}

void DrawProcedureLoad(FILE *fp)
//读取执行框//
{
	unsigned int s_len;
	string buf;
	char mid;

	ptr_ProcedureBox data = (ptr_ProcedureBox)malloc(sizeof(*data));

	fread(&data->ID, sizeof(int), 1, fp);
	fread(&data->x, sizeof(double), 1, fp);
	fread(&data->y, sizeof(double), 1, fp);
	fread(&data->width, sizeof(double), 1, fp);
	fread(&data->height, sizeof(double), 1, fp);
	data->PenSize = SYS_PENSIZE;

	data->Color = "Red";
	fread(&s_len, sizeof(unsigned int), 1, fp);
	buf = CopyString("\0");
	fread(buf, sizeof(unsigned char), s_len, fp);
	data->Text = buf;

	fread(&data->Degree, sizeof(degree), 1, fp);

	data->IsSelected = FALSE;
	InsertNode(List[PROCEDUREBOX], NULL, data);
}

void DrawJudgeLoad(FILE *fp)
//读取判断框//
{
	unsigned int s_len;
	string buf;
	char mid;

	ptr_JudgeBox data = (ptr_JudgeBox)malloc(sizeof(*data));

	fread(&data->ID, sizeof(int), 1, fp);
	fread(&data->x, sizeof(double), 1, fp);
	fread(&data->y, sizeof(double), 1, fp);
	fread(&data->width, sizeof(double), 1, fp);
	fread(&data->height, sizeof(double), 1, fp);
	data->PenSize = SYS_PENSIZE;

	data->Color = "Red";
	fread(&s_len, sizeof(unsigned int), 1, fp);
	buf = CopyString("\0");
	fread(buf, sizeof(unsigned char), s_len, fp);
	data->Text = buf;
	data->IsSelected = FALSE;

	fread(&data->Degree, sizeof(degree), 1, fp);

	InsertNode(List[JUDGEBOX], NULL, data);
}

void DrawStartLoad(FILE *fp)
//读取起始框//
{
	unsigned int s_len;
	string buf;
	char mid;

	ptr_StartBox data = (ptr_StartBox)malloc(sizeof(*data));

	fread(&data->ID, sizeof(int), 1, fp);
	fread(&data->x, sizeof(double), 1, fp);
	fread(&data->y, sizeof(double), 1, fp);
	fread(&data->width, sizeof(double), 1, fp);
	fread(&data->height, sizeof(double), 1, fp);
	data->PenSize = SYS_PENSIZE;

	data->Color = "Red";
	fread(&s_len, sizeof(unsigned int), 1, fp);
	buf = CopyString("\0");
	fread(buf, sizeof(unsigned char), s_len, fp);
	data->Text = buf;

	fread(&data->Degree, sizeof(degree), 1, fp);

	data->IsSelected = FALSE;
	InsertNode(List[STARTBOX], NULL, data);
}

void DrawInputAndOutputBoxSave(FILE *fp)
//保存输入输出框//
{
	linkedlistADT nodeptr;
	unsigned int i = 4, s_len = 0;

	ptr_InputAndOutputBox data;
	nodeptr = List[INPUTANDOUTPUTBOX]->next;
	while (nodeptr != NULL)
	{
		data = nodeptr->dataptr;
		fwrite(&i, sizeof(unsigned int), 1, fp);
		fwrite(&data->ID, sizeof(int), 1, fp);
		fwrite(&data->x, sizeof(double), 1, fp);
		fwrite(&data->y, sizeof(double), 1, fp);
		fwrite(&data->width, sizeof(double), 1, fp);
		fwrite(&data->height, sizeof(double), 1, fp);

		s_len = strlen(data->Text);
		fwrite(&s_len, sizeof(unsigned int), 1, fp);
		fwrite(data->Text, sizeof(char), s_len, fp);
		fwrite(&data->Degree, sizeof(degree), 1, fp);
		nodeptr = nodeptr->next;
	}
}

void DrawInputAndOutputBoxLoad(FILE *fp)
//读取输入输出框//
{
	unsigned int s_len;
	string buf;
	char mid;

	ptr_InputAndOutputBox data = (ptr_InputAndOutputBox)malloc(sizeof(*data));

	fread(&data->ID, sizeof(int), 1, fp);
	fread(&data->x, sizeof(double), 1, fp);
	fread(&data->y, sizeof(double), 1, fp);
	fread(&data->width, sizeof(double), 1, fp);
	fread(&data->height, sizeof(double), 1, fp);
	data->PenSize = SYS_PENSIZE;

	data->Color = "Red";
	fread(&s_len, sizeof(unsigned int), 1, fp);
	buf = CopyString("\0");
	fread(buf, sizeof(unsigned char), s_len, fp);
	data->Text = buf;

	fread(&data->Degree, sizeof(degree), 1, fp);

	data->IsSelected = FALSE;
	InsertNode(List[INPUTANDOUTPUTBOX], NULL, data);
}

#endif
