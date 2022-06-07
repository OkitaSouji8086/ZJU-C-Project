#ifndef _SaveAndLoad_C_
#define _SaveAndLoad_C_

#include "definition.h"
#include "SaveAndLoad.h"

static char r = 'r';
static char l = 'l';
static char g = 'g';
static char b = 'b';

void SaveAllObj();				  //锟斤拷锟斤拷锟斤拷锟叫碉拷前锟斤拷锟斤拷//
void DrawLineDSave(FILE *fp);	  /*锟斤拷锟斤拷直锟斤拷*/
void DrawProcedureSave(FILE *fp); /*锟斤拷锟斤拷执锟叫匡拷*/
void DrawJudgeSave(FILE *fp);	  /*锟斤拷锟斤拷锟叫断匡拷*/
void DrawStartSave(FILE *fp);	  /*锟斤拷锟斤拷锟斤拷始锟斤拷*/
void LoadAllObj();
void DrawLineDLoad(FILE *fp);
void DrawProcedureLoad(FILE *fp);
void DrawJudgeLoad(FILE *fp);
void DrawStartLoad(FILE *fp);
void DrawTextLoad(FILE *fp);
void DrawTextSave(FILE *fp);
void DrawInputAndOutputBoxLoad(FILE *fp);
void DrawInputAndOutputBoxSave(FILE *fp);


void SaveAllObj() //锟斤拷锟斤拷暮锟斤拷锟�?//
{
	FILE *fp = fopen("save.dat", "wb");

	DrawProcedureSave(fp);
	DrawJudgeSave(fp);
	DrawStartSave(fp);
	DrawInputAndOutputBoxSave(fp);
	DrawLineDSave(fp);

	fclose(fp);
}
void DrawLineDSave(FILE *fp) //锟斤拷//
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

void DrawProcedureSave(FILE *fp) //锟斤拷锟斤拷执锟叫匡拷//
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
		fwrite(&data->Degree,sizeof(degree),1,fp);
		nodeptr = nodeptr->next;
	}
}

void DrawJudgeSave(FILE *fp)
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
		fwrite(&data->Degree,sizeof(degree),1,fp);
		nodeptr = nodeptr->next;
	}
}

void DrawStartSave(FILE *fp)
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
		fwrite(&data->Degree,sizeof(degree),1,fp);
		
		nodeptr = nodeptr->next;
	}
}

void LoadAllObj()
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
{
	char mid;
	ptr_Line data = (ptr_Line)malloc(sizeof(*data));

	fread(&data->ID_1, sizeof(int), 1, fp);
	fread(&data->ID_2, sizeof(int), 1, fp);
	fread(&data->PenSize, sizeof(int), 1, fp);

	
	data->Color = "Red";
    data->Obj1 = SearchObj(data->ID_1);
    data->Obj2 = SearchObj(data->ID_2);
    
	InsertNode(List[LINE], NULL, data);
}

void DrawProcedureLoad(FILE *fp)
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
	
	fread(&data->Degree,sizeof(degree),1,fp);
	
    
	data->IsSelected = FALSE;
	InsertNode(List[PROCEDUREBOX], NULL, data);
}

void DrawJudgeLoad(FILE *fp)
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

	fread(&data->Degree,sizeof(degree),1,fp);

	InsertNode(List[JUDGEBOX], NULL, data);
}

void DrawStartLoad(FILE *fp)
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
	
	
	fread(&data->Degree,sizeof(degree),1,fp);

	data->IsSelected = FALSE;
	InsertNode(List[STARTBOX], NULL, data);
}

DrawInputAndOutputBoxSave(FILE *fp)
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
		fwrite(&data->Degree,sizeof(degree),1,fp);
		nodeptr = nodeptr->next;
	}
}

DrawInputAndOutputBoxLoad(FILE *fp)
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
	
	
	fread(&data->Degree,sizeof(degree),1,fp);

	data->IsSelected = FALSE;
	InsertNode(List[INPUTANDOUTPUTBOX], NULL, data);
}

#endif
