#ifndef _EVENT_H_
#define _EVENT_H_

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

/* ����:���̻ص�������������,���� F1/ F2/ F3 �¼�
 * ����:��
 * ˵��:��
 */
void CaseF1Process();
void CaseF2Process();
void CaseF3Process();
void CaseF4Process();
void CaseF5Process();

#endif