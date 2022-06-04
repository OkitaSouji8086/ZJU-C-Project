#ifndef _MAIN_H_
#define _MAIN_H_

#include "definition.h"

//=============================================================================================================================================//
/* Ĭ��ֵ���� */
//=============================================================================================================================================//

/* Ĭ�ϻ�ͼ���� */
extern string SYS_COLOR;
extern int SYS_PENSIZE;
extern double WINDOW_X;
extern double WINDOW_Y;

/* Ĭ�϶��󳤿� */
extern double OBJ_WIDTH;
extern double OBJ_HEIGHT;

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

void TimerEventProcess(int timerID);

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
void EnlargeObj(void *ptr_Obj);

/* ����:����ѡ�еĶ���
 * ����:��
 * ����ֵ:��
 * ˵��:���ж���ѡ���Ұ��� Ctrl+C, ���� TEMP ָ��ö���
 */
void CopyObj();

/* ����:ճ��ѡ�еĶ���
 * ����:��
 * ����ֵ:��
 * ˵��:�ڵ�ǰ���λ������һ���¶���,��λ������������� TEMP ָ��Ķ�����ͬ
 */
void PasteObj();

/* ����:ɾ������
 * ����:����ָ�룬��CURR_OBJ
 * ����ֵ:��
 */
void DeleteObj(void *ptr_Obj);

/* ����:��������,�ҵ����� ID ��Ӧ�Ķ���
 * ����:����ID
 * ����ֵ:�ҵ��Ķ���ָ��
 */
void *SearchObj(int ID);

/* ����:SearchObj��������
 * ����1:������dataָ��
 * ����2:����ID
 * ����ֵ:�Ƿ����,���ΪTRUE
 */
bool equalfunptr_PBox(void *obj1, void *obj2);
bool equalfunptr_JBox(void *obj1, void *obj2);
bool equalfunptr_SBox(void *obj1, void *obj2);
bool equalfunptr_IBox(void *obj1, void *obj2);

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
extern void DrawInputAndOutputBox(void *InputAndOutputBox);

extern void PickNearestObj(double mx, double my);

extern void test();

#endif
