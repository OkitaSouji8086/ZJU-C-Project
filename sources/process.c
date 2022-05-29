#ifndef _PROCESS_C_
#define _PROCESS_C_

#include "process.h"

void DeleteObj(void* ptr_Obj)
{
	return;
}

void* SearchObj(int ID)
{
	int i;
	linkedlistADT ptr_SearchObj = NULL;
	for (i = 0; i < 2; i++)
	{
		if(i == 0) ptr_SearchObj = SearchNode(List[PROCEDUREBOX], &ID, equalfunptr_PBox);
		else if(i == 1) ptr_SearchObj = SearchNode(List[JUDGEBOX], &ID, equalfunptr_JBox);
		else ptr_SearchObj = SearchNode(List[STARTBOX], &ID, equalfunptr_SBox);

		if(ptr_SearchObj != NULL) break;
	}
	
	return ptr_SearchObj->dataptr;
}

bool equalfunptr_PBox(void *obj1, void *obj2)
{
	ptr_ProcedureBox ptr_temp = (ptr_ProcedureBox)obj1;
	int* id_temp = (int*)obj2;

	if(ptr_temp->ID == *id_temp) return TRUE;
	else return FALSE;
}
bool equalfunptr_JBox(void *obj1, void *obj2)
{
	ptr_JudgeBox ptr_temp = (ptr_JudgeBox)obj1;
	int* id_temp = (int*)obj2;

	if(ptr_temp->ID == *id_temp) return TRUE;
	else return FALSE;
}
bool equalfunptr_SBox(void *obj1, void *obj2)
{
	ptr_StartBox ptr_temp = (ptr_StartBox)obj1;
	int* id_temp = (int*)obj2;

	if(ptr_temp->ID == *id_temp) return TRUE;
	else return FALSE;
}

#endif