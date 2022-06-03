#ifndef _PROCESS_C_
#define _PROCESS_C_

#include "process.h"

void DeleteObj(void *ptr_Obj)
{
	linkedlistADT deletednode = NULL;
	do
	{
		deletednode = DeleteNode(List[LINE], &(((ptr_StartBox)ptr_Obj)->ID), equalfunptr_Line);
	} while (deletednode != NULL);

	switch (CURR_OBJ_KIND)
	{
	case STARTBOX:
		DeleteNode(List[STARTBOX], &(((ptr_StartBox)ptr_Obj)->ID), equalfunptr_SBox);
		COUNT[0]--;
		break;
	case PROCEDUREBOX:
		DeleteNode(List[PROCEDUREBOX], &(((ptr_ProcedureBox)ptr_Obj)->ID), equalfunptr_PBox);
		COUNT[1]--;
		break;
	case JUDGEBOX:
		DeleteNode(List[JUDGEBOX], &(((ptr_JudgeBox)ptr_Obj)->ID), equalfunptr_JBox);
		COUNT[2]--;
		break;
	case INPUTANDOUTPUTBOX:
		DeleteNode(List[INPUTANDOUTPUTBOX], &(((ptr_InputAndOutputBox)ptr_Obj)->ID), equalfunptr_IBox);
		COUNT[3]--;
		break;
	default:
		break;
	}
}

void *SearchObj(int ID)
{
	int i;
	linkedlistADT ptr_SearchObj = NULL;
	for (i = 0; i < NLIST; i++)
	{
		if (i == 0)
			ptr_SearchObj = SearchNode(List[STARTBOX], &ID, equalfunptr_PBox);
		else if (i == 1)
			ptr_SearchObj = SearchNode(List[PROCEDUREBOX], &ID, equalfunptr_JBox);
		else if (i == 2)
			ptr_SearchObj = SearchNode(List[JUDGEBOX], &ID, equalfunptr_SBox);
		else if (i == 3)
			ptr_SearchObj = SearchNode(List[INPUTANDOUTPUTBOX], &ID, equalfunptr_IBox);
		if (ptr_SearchObj != NULL)
			break;
	}

	return ptr_SearchObj->dataptr;
}

bool equalfunptr_Line(void *obj1, void *obj2)
{
	ptr_Line ptr_temp = (ptr_Line)obj1;
	int *id_temp = (int *)obj2;

	if (ptr_temp->ID_1 == *id_temp || ptr_temp->ID_2 == *id_temp)
		return TRUE;
	else
		return FALSE;
}
bool equalfunptr_PBox(void *obj1, void *obj2)
{
	ptr_ProcedureBox ptr_temp = (ptr_ProcedureBox)obj1;
	int *id_temp = (int *)obj2;

	if (ptr_temp->ID == *id_temp)
		return TRUE;
	else
		return FALSE;
}
bool equalfunptr_JBox(void *obj1, void *obj2)
{
	ptr_JudgeBox ptr_temp = (ptr_JudgeBox)obj1;
	int *id_temp = (int *)obj2;

	if (ptr_temp->ID == *id_temp)
		return TRUE;
	else
		return FALSE;
}
bool equalfunptr_SBox(void *obj1, void *obj2)
{
	ptr_StartBox ptr_temp = (ptr_StartBox)obj1;
	int *id_temp = (int *)obj2;

	if (ptr_temp->ID == *id_temp)
		return TRUE;
	else
		return FALSE;
}
bool equalfunptr_IBox(void *obj1, void *obj2)
{
	ptr_InputAndOutputBox ptr_temp = (ptr_InputAndOutputBox)obj1;
	int *id_temp = (int *)obj2;

	if (ptr_temp->ID == *id_temp)
		return TRUE;
	else
		return FALSE;
}

void PickNearestObj(double mx, double my)
{
	double MinDistance = 100000000;
	double ObjDistance = -1;
	void *MinObj = NULL;
	int i;
	bool Found = FALSE;

	linkedlistADT nodeptr = NULL;

	for (i = STARTBOX; i < NLIST; i++)
	{
		nodeptr = List[i]->next;
		while (nodeptr != NULL)
		{
			ObjDistance = LtsDistance(nodeptr->dataptr, mx, my);
			if (IsInZone(mx, my, nodeptr->dataptr) && ObjDistance < MinDistance)
			{
				Found = TRUE;
				MinDistance = ObjDistance;
				CURR_OBJ = nodeptr->dataptr;
				CURR_OBJ_KIND = i;
			}
			nodeptr = nodeptr->next;
		}
	}

	if (!Found)
	{
		CURR_OBJ = NULL;
		CURR_OBJ_KIND = -1;
	}
}

double LtsDistance(void *ptr_Obj, double mx, double my)
{
	double x0, y0;
	x0 = ((ptr_StartBox)ptr_Obj)->x;
	y0 = ((ptr_StartBox)ptr_Obj)->y;

	return (fabs(x0 - mx) + fabs(y0 - my));
}

bool IsInZone(double mx, double my, void *Obj)
{
	double ObjX = ((ptr_StartBox)Obj)->x;
	double ObjY = ((ptr_StartBox)Obj)->y;
	double ObjW = ((ptr_StartBox)Obj)->width;
	double ObjH = ((ptr_StartBox)Obj)->height;

	if (mx < ObjX + ObjW && mx > ObjX - ObjW && my < ObjY + ObjH && my > ObjY - ObjH)
		return TRUE;
	else
		return FALSE;
}

#endif
