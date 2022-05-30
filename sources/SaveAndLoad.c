#ifndef _SaveAndLoad_C_
#define _SaveAndLoad_C_
#include"SaveAndLoad.h"


void SaveAllObj();//保存所有当前对象// 
void DrawLineDSave(FILE *fp);  /*保存直线*/ 
void DrawProcedureSave(FILE *fp);   /*保存执行框*/ 
void DrawJudgeSave(FILE *fp);/*保存判断框*/ 
void DrawStartSave(FILE *fp);/*保存起始框*/
void LoadAllObj();
void DrawLineDLoad(FILE *fp);
void DrawProcedureLoad(FILE *fp);
void DrawJudgeLoad(FILE *fp);
void DrawStartLoad(FILE *fp);
void DrawTextLoad(FILE *fp) ;
void DrawTextSave(FILE *fp);





void SaveAllObj()                        //保存的函数// 
{
	FILE *fp = fopen("save.dat","wb");
	
	DrawLineDSave(fp);
	DrawProcedureSave(fp);
	DrawJudgeSave(fp);
	DrawStartSave(fp);
	DrawTextSave(fp);
	fclose(fp);
 } 
 void DrawLineDSave(FILE* fp) //线// 
 {
 	char r = r;
	char l = l;
	char g = g;
	char b = b;
	
 	linkedlistADT nodeptr;
 	unsigned int i = 0;
 	ptr_Line data;
 	
 	nodeptr = List[LINE]->next;
 	while(nodeptr != NULL)
	{
	    data = nodeptr->dataptr;

 		fwrite(&i,sizeof(unsigned int ),1,fp);
 		fwrite(&data->ID_1,sizeof(int),1,fp);
 		fwrite(&data->ID_2,sizeof(int),1,fp);
 		fwrite(&data->PenSize,sizeof(int),1,fp);

		if(!strcmp(data->Color,"Red"))
		fwrite(&r,sizeof(char),1,fp);
		
		else if(strcmp(data->Color,"Blue"))
		fwrite(&l,sizeof(char),1,fp);
		
		else if(!strcmp(data->Color,"Green"))
		fwrite(&g,sizeof(char),1,fp);
		
		else if(!strcmp(data->Color,"Black"))
		fwrite(&b,sizeof(char),1,fp); 	
				   
		nodeptr = nodeptr->next;
	}
 }
 
 void DrawProcedureSave(FILE *fp)          //保存执行框// 
 {
 		char r = r;
	char l = l;
	char g = g;
	char b = b;
	
 	linkedlistADT nodeptr;
 	unsigned int i = 1;
 	
 	ptr_ProcedureBox data;
 	nodeptr = List[PROCEDUREBOX] ->next;
 	while(nodeptr != NULL)
 	{
 		data = nodeptr->dataptr;
 		fwrite(&i,sizeof(unsigned int),1,fp);
 		fwrite(&data->ID,sizeof(int),1,fp);
 		fwrite(&data->x,sizeof(double),1,fp);
 		fwrite(&data->y,sizeof(double),1,fp);
 		fwrite(&data->width,sizeof(double),1,fp);
 		fwrite(&data->height,sizeof(double),1,fp);
 		fwrite(&data->PenSize,sizeof(int),1,fp);
 	    if(!strcmp(data->Color,"Red"))
		fwrite(&r,sizeof(char),1,fp);
		
		else if(strcmp(data->Color,"Blue"))
		fwrite(&l,sizeof(char),1,fp);
		
		else if(!strcmp(data->Color,"Green"))
		fwrite(&g,sizeof(char),1,fp);
		
		else if(!strcmp(data->Color,"Black"))
		fwrite(&b,sizeof(char),1,fp);
 		
 		fwrite(&data->TextID,sizeof(int),1,fp);
 		nodeptr = nodeptr->next;
	 }
 }
 
 void DrawJudgeSave(FILE *fp)
 {
 	char r = r;
	char l = l;
	char g = g;
	char b = b;
	
 	linkedlistADT nodeptr;
 	unsigned int i  = 2;
 	
 	ptr_JudgeBox data;
 	nodeptr = List[JUDGEBOX]->next;
 	while(nodeptr != NULL)
 	{
 		data = nodeptr->dataptr;
 		fwrite(&i,sizeof(unsigned int),1,fp);
 		fwrite(&data->ID,sizeof(int),1,fp);
 		fwrite(&data->x,sizeof(double),1,fp);
 		fwrite(&data->y,sizeof(double),1,fp);
 		fwrite(&data->width,sizeof(double),1,fp);
 		fwrite(&data->height,sizeof(double),1,fp);
 		
		if(!strcmp(data->Color,"Red"))
		fwrite(&r,sizeof(char),1,fp);
		
		else if(strcmp(data->Color,"Blue"))
		fwrite(&l,sizeof(char),1,fp);
		
		else if(!strcmp(data->Color,"Green"))
		fwrite(&g,sizeof(char),1,fp);
		
		else if(!strcmp(data->Color,"Black"))
		fwrite(&b,sizeof(char),1,fp);

 		fwrite(&data->TextID,sizeof(int),1,fp);
 		nodeptr = nodeptr->next;
	 }
 }
 
void DrawStartSave(FILE *fp)
{
		char r = r;
	char l = l;
	char g = g;
	char b = b;
	
	linkedlistADT nodeptr;
	unsigned int i = 3;
	
	ptr_StartBox data;
	nodeptr = List[STARTBOX]->next;
	while(nodeptr!=NULL){
 		data = nodeptr->dataptr;
 		fwrite(&i,sizeof(unsigned int),1,fp);
 		fwrite(&data->ID,sizeof(int),1,fp);
 		fwrite(&data->x,sizeof(double),1,fp);
 		fwrite(&data->y,sizeof(double),1,fp);
 		fwrite(&data->width,sizeof(double),1,fp);
 		fwrite(&data->height,sizeof(double),1,fp);
 		
		if(!strcmp(data->Color,"Red"))
		fwrite(&r,sizeof(char),1,fp);
		
		else if(strcmp(data->Color,"Blue"))
		fwrite(&l,sizeof(char),1,fp);
		
		else if(!strcmp(data->Color,"Green"))
		fwrite(&g,sizeof(char),1,fp);
		
		else if(!strcmp(data->Color,"Black"))
		fwrite(&b,sizeof(char),1,fp);
		
		fwrite(&data->TextID,sizeof(int),1,fp);
 		nodeptr = nodeptr->next;
}
}


void LoadAllObj( )
{
	FILE *fp = fopen("save.dat", "rb");
	unsigned int ObjKind;

	ptr_Line LineData;
	ptr_ProcedureBox ProcedureData;
	ptr_JudgeBox JudgeData;
	ptr_StartBox StartData;
	ptr_Text TextData;

	while(1){
		fread(&ObjKind, sizeof(unsigned int), 1, fp);
		if(feof(fp)) break;
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
			DrawTextLoad(fp);
			break;
		default:
			break;
		}
	}

	fclose(fp);
}


void DrawLineDLoad(FILE *fp)
{
	char r = r;
	char l = l;
	char g = g;
	char b = b;
	char mid;
	ptr_Line data = (ptr_Line)malloc(sizeof(*data));

    fread(&data->ID_1,sizeof(int),1,fp);
	fread(&data->ID_2,sizeof(int), 1, fp);
	fread(&data->PenSize, sizeof(int), 1, fp);
	
	fread(&mid, sizeof(char), 1, fp);
	
	if(mid == 'r') data->Color = "Red";
	else if(mid == 'g') data->Color = "Green";
	else if(mid == 'l') data->Color = "Blue";
	else if(mid == 'b') data->Color = "Black";
	data->IsSelected = FALSE;

	InsertNode(List[LINE], NULL, data);
}

void DrawProcedureLoad(FILE *fp)
{
	char mid;
	char r = r;
	char l = l;
	char g = g;
	char b = b;
	ptr_ProcedureBox data = (ptr_ProcedureBox)malloc(sizeof(*data));

	fread(&data->ID, sizeof(int), 1, fp);
	fread(&data->x, sizeof(double), 1, fp);
	fread(&data->y, sizeof(double), 1, fp);
	fread(&data->width, sizeof(double), 1, fp);
	fread(&data->height, sizeof(double), 1, fp);
	fread(&data->PenSize, sizeof(int), 1, fp);
	
	fread(&mid, sizeof(char), 1, fp);
	
	if(mid == 'r') data->Color = "Red";
	else if(mid == 'g') data->Color = "Green";
	else if(mid == 'l') data->Color = "Blue";
	else if(mid == 'b') data->Color = "Black";
	
    fread(&data->TextID,sizeof(int),1,fp);
	data->IsSelected = FALSE;

	InsertNode(List[PROCEDUREBOX], NULL, data);
	
}
void DrawJudgeLoad(FILE *fp)
{   char mid;
	char r = r;
	char l = l;
	char g = g;
	char b = b;
	ptr_JudgeBox data = (ptr_JudgeBox)malloc(sizeof(*data));

	fread(&data->ID, sizeof(int), 1, fp);
	fread(&data->x, sizeof(double), 1, fp);
	fread(&data->y, sizeof(double), 1, fp);
	fread(&data->width, sizeof(double), 1, fp);
	fread(&data->height, sizeof(double), 1, fp);
	fread(&data->PenSize, sizeof(int), 1, fp);
	
	fread(&mid, sizeof(char), 1, fp);
	
	if(mid == 'r') data->Color = "Red";
	else if(mid == 'g') data->Color = "Green";
	else if(mid == 'l') data->Color = "Blue";
	else if(mid == 'b') data->Color = "Black";    
	fread(&data->TextID,sizeof(int),1,fp);
	data->IsSelected = FALSE;

	InsertNode(List[JUDGEBOX], NULL, data);
	
}


void DrawStartLoad(FILE *fp)
{
	char r = r;
	char l = l;
	char g = g;
	char b = b;
	char mid;
	
	ptr_StartBox data = (ptr_StartBox)malloc(sizeof(*data));

	fread(&data->ID, sizeof(int), 1, fp);
	fread(&data->x, sizeof(double), 1, fp);
	fread(&data->y, sizeof(double), 1, fp);
	fread(&data->width, sizeof(double), 1, fp);
	fread(&data->height, sizeof(double), 1, fp);
	fread(&data->PenSize, sizeof(int), 1, fp);
	
	fread(&mid, sizeof(char), 1, fp);
	
	if(mid == 'r') data->Color = "Red";
	else if(mid == 'g') data->Color = "Green";
	else if(mid == 'l') data->Color = "Blue";
	else if(mid == 'b') data->Color = "Black";


	fread(&data->TextID,sizeof(int),1,fp);
	data->IsSelected = FALSE;
	InsertNode(List[STARTBOX], NULL, data);
	
}


void DrawTextSave(FILE *fp)
{
	linkedlistADT nodeptr;
	ptr_Text data;
	unsigned int i = 4,s_len = 0;
	char r = r;
	char l = l;
	char g = g;
	char b = b;
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
}

void DrawTextLoad(FILE *fp)
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
}

#endif