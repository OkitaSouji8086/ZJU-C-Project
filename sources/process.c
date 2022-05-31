#ifndef _PROCESS_C_
#define _PROCESS_C_

#include "process.h"

void DeleteObj(void* ptr_Obj)
{
	linkedlistADT deletednode = NULL;
	do{
		deletednode = DeleteNode(List[LINE], &(((ptr_StartBox)ptr_Obj)->ID), equalfunptr_Line);
	} while (deletednode != NULL);

	switch (CURR_OBJ_KIND)
	{
	case STARTBOX:
		DeleteNode(List[STARTBOX], &(((ptr_StartBox)ptr_Obj)->ID), equalfunptr_SBox);
		break;
	case PROCEDUREBOX:
		DeleteNode(List[PROCEDUREBOX], &(((ptr_ProcedureBox)ptr_Obj)->ID), equalfunptr_PBox);
		break;
	case JUDGEBOX:
		DeleteNode(List[JUDGEBOX], &(((ptr_JudgeBox)ptr_Obj)->ID), equalfunptr_JBox);
		break;
	default:
		break;
	}
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

bool equalfunptr_Line(void *obj1, void *obj2)
{
	ptr_Line ptr_temp = (ptr_Line)obj1;
	int* id_temp = (int*)obj2;

	if(ptr_temp->ID_1 == *id_temp || ptr_temp->ID_2 == *id_temp) return TRUE;
	else return FALSE;
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

void PickNearestObj(double mx, double my)
{
	double MinDistance = 100000000;
	double ObjDistance = -1;
	void* MinObj = NULL;
	int i;

	linkedlistADT nodeptr = NULL;

	for (i = STARTBOX; i < NLIST; i++)
	{
		nodeptr = List[i]->next;
		while (nodeptr != NULL)
		{
			ObjDistance = LtsDistance(nodeptr->dataptr, mx, my);
			if(ObjDistance < MinDistance){
				MinDistance = ObjDistance;
				CURR_OBJ = nodeptr->dataptr;
				CURR_OBJ_KIND = i;
			}
			nodeptr = nodeptr->next;
		}	
	}
}

double LtsDistance(void* ptr_Obj, double mx, double my)
{
	double x0, y0;
	x0 = ((ptr_StartBox)ptr_Obj)->x;
	y0 = ((ptr_StartBox)ptr_Obj)->y;

	return (fabs(x0-mx) + fabs(y0-my));
}

#endif