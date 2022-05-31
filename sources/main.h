#ifndef _MAIN_H_
#define _MAIN_H_

#include "linkedlist.h"
#include "genlib.h"
#include "boolean.h"

//=============================================================================================================================================//
/* �궨�� */
//=============================================================================================================================================//

/* ����ģʽ */
#define _DEBUG_ 1

/* �������� */
#define NLIST 4
#define LINE 0
#define STARTBOX 1
#define PROCEDUREBOX 2
#define JUDGEBOX 3
#define TEXT 4

#define TEXTLEN  100
#define CURSOR "_"          /*������*/
#define CURSOR_BLINK  1     /*�����˸��ʱ���¼���־��*/

//=============================================================================================================================================//
/* ������ */
//=============================================================================================================================================//


/* ÿ��Ԫ�ض���һ��ָ�� ֱ��/������ ��ָ�� */
extern linkedlistADT List[NLIST];



//=============================================================================================================================================//
/* ȫ�ֱ������� */
//=============================================================================================================================================//

/* ÿ�ֶ���ĸ��� */
extern int COUNT[3];


/* ��ǰѡ�е�Ԫ��,û��ѡ��ʱΪNULL */
extern void* CURR_OBJ;
/* ��ǰѡ�е�Ԫ������,û��ѡ��ʱΪ-1 */
extern int CURR_OBJ_KIND;


/* ���а�,ָ����һ�������ƵĶ���,û����ΪNULL */
extern void* TEMP;
/* ���а��еĶ�������,û����Ϊ-1 */
extern int TEMP_KIND;

/* ID����,ÿ������Ψһ */
extern int ID[1000000];

/* ��ǰ��ŵ��ڼ� */
extern int CURR_ID;

/* ��ǰ���ĵ㱻ռ�ݵĸ��� */
extern int CURR_OCCUPY;

/* ���״̬�� */
extern int MOUSE_FSM;

//=============================================================================================================================================//
/* Ĭ��ֵ���� */
//=============================================================================================================================================//

/* Ĭ�ϻ�ͼ���� */
extern string SYSCOLOR;
extern int SYSPENSIZE;
extern double WindowX;
extern double WindowY;

/* Ĭ�϶��󳤿� */
extern double OBJWIDTH;
extern double OBJHEIGHT;



//=============================================================================================================================================//
/* �ṹ���� */
//=============================================================================================================================================//

/* ֱ�� */
typedef struct Line
{
	int ID_1; /* ��ʼ������ */
	int ID_2; /* ��ֹ������ */
	void* Obj1;
	void* Obj2;
	int PenSize; /* ��ϸ */
	string Color; /* ��ɫ */
	bool IsSelected; /* �Ƿ�ѡ�� */
} *ptr_Line;


/* ��ʼ��ֹ�� */
typedef struct StartBox
{
	int ID; /* Ψһ������ */
	double x, y; /* �������� */
	double width, height; /* ���� */
	int PenSize; /* ��ϸ */
	string Color; /* ��ɫ */
	string Text; /* �ı���ָ�� */
	bool IsSelected; /* �Ƿ�ѡ�� */
} *ptr_StartBox;


/* ִ�п� */
typedef struct ProcedureBox
{
	int ID; /* Ψһ������ */
	double x, y; /* �������� */
	double width, height; /* ���� */
	int PenSize; /* ��ϸ */
	string Color; /* ��ɫ */
	string Text; /* �ı���ָ�� */
	bool IsSelected; /* �Ƿ�ѡ�� */
} *ptr_ProcedureBox;


/* �жϿ� */
typedef struct JudgeBox
{
	int ID; /* Ψһ������ */
	double x, y; /* �������� */
	double width, height; /* ���� */
	int PenSize; /* ��ϸ */
	string Color; /* ��ɫ */
	string Text; /* �ı���ָ�� */
	bool IsSelected; /* �Ƿ�ѡ�� */
} *ptr_JudgeBox;



//=============================================================================================================================================//
/* �������� */
//=============================================================================================================================================//

/* ����:������
 * ����:��
 * ����ֵ:�����˳�����0
 * ˵��:���� DrawMenu() �����Ʋ˵�,����ʼ��ʱ����һ��;
 */
void Main();


/* ����:���»�������ͼ��
 * ����:��
 * ����ֵ:��
 */
void display();


/* ����:���Ʋ˵�
 * ����:��
 * ����ֵ:��
 * ˵��:�ؼ��б�: File -New -Open -Save -Exit
 *               Draw -1(F1) -2(F2) -3(F3)
 *               Edit -Copy -Paste -Delete
 *               Help -About -Help
 */
void DrawMenu();

/* ����:�������ж���
 * ����:��
 * ����ֵ:��
 */
void DrawAllObj();


/* ����:��Ӧ�����¼�
 * ����1:������
 * ����2:�¼�
 * ˵��:�¼���:
 * |  ����  |         ����        |         ���ú���         |
 * |   F1   |  ���������ʼ��ֹ��  |      DrawStartBox()     |
 * |   F2   |    ��������жϿ�    |     DrawJudegeBox()     |
 * |   F3   |    �������ִ�п�    |    DrawProcedureBox()   |
 * |  F10   |       �˳�����      |         exit(1)         | 
 * | Ctrl+N |  ɾ����������,������ |      DeleteAllObj()     |
 *             ���»��Ʋ˵�        |     DisplayClear()      |
 *                                |       DrawMenu()        |
 * | Ctrl+S |   ���浽save.data   |       SaveAllObj()      |
 * | Ctrl+O |   ��save.data��ȡ   |       LoadAllObj()      |
 * | Ctrl+C |    ����ѡ�еĶ���    |        CopyObj()        |
 * | Ctrl+V |       ճ������      |        PasteObj()       |
 * | BackSP |       ɾ������      |       DeleteObj()       |
 * | ESCAPE |   �˳�����ѡ��״̬   |       DeleteObj()       |
 */
void KeyboardEventProcess(int key, int event);

/* ����:���̻ص�������������,���� F1/ F2/ F3 �¼�
 * ����:��
 * ˵��:��
 */
void CaseF1Process();
void CaseF2Process();
void CaseF3Process();

/* ����:��Ӧ����¼��¼�
 * ����1:x����
 * ����2:y����
 * ����3:����
 * ����4:�¼�
 * ˵��:�¼���:��ȱ
 */
void MouseEventProcess(int x, int y, int button, int event);


/* ����:��Ӧ�ַ��¼��¼�
 * ����:�ַ�
 * ˵��:�¼���:��ȱ
 */
void CharEventProcess(char c);


/* ����:����һ��ֱ�ߣ����������ؼ�
 * ����1:����1 ID
 * ����2:����2 ID
 * ����ֵ:��
 */
void LinkTwoObj(int ID1, int ID2);


/* ����:���Ŷ���
 * ����:����ָ�룬��CURR_OBJ
 * ����ֵ:��
 */
void EnlargeObj(void* ptr_Obj); 


/* ����:����ѡ�еĶ���
 * ����:��
 * ����ֵ:��
 * ˵��:���ж���ѡ���Ұ��� Ctrl+C, ���� TEMP ָ��ö���
 */
void CopyObj();


/* ����:ճ��ѡ�еĶ���
 * ����:���а��еĶ���ָ�룬��TEMP
 * ����ֵ:��
 * ˵��:�ڵ�ǰ���λ������һ���¶���,��λ������������� TEMP ָ��Ķ�����ͬ
 */
void PasteObj();


/* ����:ɾ������
 * ����:����ָ�룬��CURR_OBJ
 * ����ֵ:��
 */
void DeleteObj(void* ptr_Obj);


/* ����:��������,�ҵ����� ID ��Ӧ�Ķ���
 * ����:����ID
 * ����ֵ:�ҵ��Ķ���ָ��
 */
void* SearchObj(int ID);

/* ����:SearchObj��������
 * ����1:������dataָ��
 * ����2:����ID
 * ����ֵ:�Ƿ����,���ΪTRUE
 */
bool equalfunptr_PBox(void *obj1, void *obj2);
bool equalfunptr_JBox(void *obj1, void *obj2);
bool equalfunptr_SBox(void *obj1, void *obj2);


/* ����:�������ж���save.data
 * ����:��
 * ����ֵ:��
 */
void SaveAllObj();


/* ����:��save.data��ȡ
 * ����:��
 * ����ֵ:��
 */
void LoadAllObj();



/* ����:������ʼ��
 * ����:��ʼ��ָ��
 * ����ֵ:��
 */
extern void DrawStartBox(void *StartBox);
extern void DrawProcedureBox(void *ProcedureBox);
extern void DrawJudgeBox(void *JudgeBox);

extern void PickNearestObj(double mx, double my);

#endif
