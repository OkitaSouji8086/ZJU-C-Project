#ifndef _SaveAndLoad_C_
#define _SaveAndLoad_C_
#include "SaveAndLoad.h"

static char r = 'r';
static char l = 'l';
static char g = 'g';
static char b = 'b';

void SaveAllObj();				  //�������е�ǰ����//
void DrawLineDSave(FILE *fp);	  /*����ֱ��*/
void DrawProcedureSave(FILE *fp); /*����ִ�п�*/
void DrawJudgeSave(FILE *fp);	  /*�����жϿ�*/
void DrawStartSave(FILE *fp);	  /*������ʼ��*/
void LoadAllObj();
void DrawLineDLoad(FILE *fp);
void DrawProcedureLoad(FILE *fp);
void DrawJudgeLoad(FILE *fp);
void DrawStartLoad(FILE *fp);
void DrawTextLoad(FILE *fp);
void DrawTextSave(FILE *fp);

void SaveAllObj() //����ĺ���?//
{
	FILE *fp = fopen("save.data", "wb");

	DrawLineDSave(fp);
	DrawProcedureSave(fp);
	DrawJudgeSave(fp);
	DrawStartSave(fp);
	fclose(fp);
}
void DrawLineDSave(FILE *fp) //��//
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

		if (!strcmp(data->Color, "Red"))
			fwrite(&r, sizeof(char), 1, fp);

		else if (strcmp(data->Color, "Blue"))
			fwrite(&l, sizeof(char), 1, fp);

		else if (!strcmp(data->Color, "Green"))
			fwrite(&g, sizeof(char), 1, fp);

		else if (!strcmp(data->Color, "Black"))
			fwrite(&b, sizeof(char), 1, fp);

		nodeptr = nodeptr->next;
	}
}

void DrawProcedureSave(FILE *fp) //����ִ�п�//
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
		fwrite(&data->PenSize, sizeof(int), 1, fp);
		if (!strcmp(data->Color, "Red"))
			fwrite(&r, sizeof(char), 1, fp);

		else if (strcmp(data->Color, "Blue"))
			fwrite(&l, sizeof(char), 1, fp);

		else if (!strcmp(data->Color, "Green"))
			fwrite(&g, sizeof(char), 1, fp);

		else if (!strcmp(data->Color, "Black"))
			fwrite(&b, sizeof(char), 1, fp);

		s_len = strlen(data->Text);
		fwrite(&s_len, sizeof(unsigned int), 1, fp);
		fwrite(data->Text, sizeof(char), s_len, fp);
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

		if (!strcmp(data->Color, "Red"))
			fwrite(&r, sizeof(char), 1, fp);

		else if (strcmp(data->Color, "Blue"))
			fwrite(&l, sizeof(char), 1, fp);

		else if (!strcmp(data->Color, "Green"))
			fwrite(&g, sizeof(char), 1, fp);

		else if (!strcmp(data->Color, "Black"))
			fwrite(&b, sizeof(char), 1, fp);

		s_len = strlen(data->Text);
		fwrite(&s_len, sizeof(unsigned int), 1, fp);
		fwrite(data->Text, sizeof(char), s_len, fp);
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

		if (!strcmp(data->Color, "Red"))
			fwrite(&r, sizeof(char), 1, fp);

		else if (strcmp(data->Color, "Blue"))
			fwrite(&l, sizeof(char), 1, fp);

		else if (!strcmp(data->Color, "Green"))
			fwrite(&g, sizeof(char), 1, fp);

		else if (!strcmp(data->Color, "Black"))
			fwrite(&b, sizeof(char), 1, fp);

		s_len = strlen(data->Text);
		fwrite(&s_len, sizeof(unsigned int), 1, fp);
		fwrite(data->Text, sizeof(char), s_len, fp);
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
			// DrawTextLoad(fp);//
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

	fread(&mid, sizeof(char), 1, fp);

	if (mid == 'r')
		data->Color = "Red";
	else if (mid == 'g')
		data->Color = "Green";
	else if (mid == 'l')
		data->Color = "Blue";
	else if (mid == 'b')
		data->Color = "Black";
	data->IsSelected = FALSE;

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
	fread(&data->PenSize, sizeof(int), 1, fp);

	fread(&mid, sizeof(char), 1, fp);

	if (mid == 'r')
		data->Color = "Red";
	else if (mid == 'g')
		data->Color = "Green";
	else if (mid == 'l')
		data->Color = "Blue";
	else if (mid == 'b')
		data->Color = "Black";
	fread(&s_len, sizeof(unsigned int), 1, fp);
	fread(buf, sizeof(unsigned char), s_len, fp);
	data->Text = buf;

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
	fread(&data->PenSize, sizeof(int), 1, fp);

	fread(&mid, sizeof(char), 1, fp);

	if (mid == 'r')
		data->Color = "Red";
	else if (mid == 'g')
		data->Color = "Green";
	else if (mid == 'l')
		data->Color = "Blue";
	else if (mid == 'b')
		data->Color = "Black";

	fread(&s_len, sizeof(unsigned int), 1, fp);
	fread(buf, sizeof(unsigned char), s_len, fp);
	data->Text = buf;
	data->IsSelected = FALSE;

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
	fread(&data->PenSize, sizeof(int), 1, fp);

	fread(&mid, sizeof(char), 1, fp);

	if (mid == 'r')
		data->Color = "Red";
	else if (mid == 'g')
		data->Color = "Green";
	else if (mid == 'l')
		data->Color = "Blue";
	else if (mid == 'b')
		data->Color = "Black";

	fread(&s_len, sizeof(unsigned int), 1, fp);
	fread(buf, sizeof(unsigned char), s_len, fp);
	data->Text = buf;
	data->IsSelected = FALSE;
	InsertNode(List[STARTBOX], NULL, data);
}

/*void DrawTextSave(FILE *fp)
{
   linkedlistADT nodeptr;
   ptr_Text data;
   unsigned int i = 4,s_len = 0;

   char mid;

   nodeptr = List[TEXT]->next;
   while(nodeptr!=NULL)
   {
	   data = nodeptr->dataptr;
	   fwrite(&i,sizeof(unsigned int),1,fp);
	   fwrite(&data->ID,sizeof(int),1,fp);
	   fwrite(&data->x,sizeof(double),1,fp);
	   fwrite(&data->y,sizeof(double),1,fp);
	   fwrite(&data->PenSize,sizeof(int),1,fp);

	   if(!strcmp(data->Color,"Red"))
	   fwrite(&r,sizeof(char),1,fp);

	   else if(strcmp(data->Color,"Blue"))
	   fwrite(&l,sizeof(char),1,fp);

	   else if(!strcmp(data->Color,"Green"))
	   fwrite(&g,sizeof(char),1,fp);

	   else if(!strcmp(data->Color,"Black"))
	   fwrite(&b,sizeof(char),1,fp);

	   fwrite(&data->curPos,sizeof(int),1,fp);
	   s_len = strlen(data->text);
	   fwrite(&s_len,sizeof(unsigned int),1,fp);
	   fwrite(data->text,sizeof(char),s_len,fp);
	   nodeptr = nodeptr->next;

   }
}  */

/* void DrawTextLoad(FILE *fp)
{
	ptr_Text data = (ptr_Text)malloc(sizeof(*data));
	unsigned int s_len;
	string buf;
	char mid;

	fread(&data->ID,sizeof(int),1,fp);
	fread(&data->x, sizeof(double), 1, fp);
	fread(&data->y, sizeof(double), 1, fp);
	fread(&mid, sizeof(char), 1, fp);

	if(mid == 'r') data->Color = "Red";
	else if(mid == 'g') data->Color = "Green";
	else if(mid == 'l') data->Color = "Blue";
	else if(mid == 'b') data->Color = "Black";

	fread(&data->curPos, sizeof(int), 1, fp);
	fread(&s_len, sizeof(unsigned int), 1, fp);
	buf = (string)malloc(sizeof(char)*s_len);
	fread(buf, sizeof(unsigned char), s_len, fp);

	data->text = buf;
	data->Color = SYSCOLOR;
	data->IsSelected = FALSE;
	data->isDisplayed = FALSE;

	InsertNode(List[TEXT], NULL, data);
} */

#endif
