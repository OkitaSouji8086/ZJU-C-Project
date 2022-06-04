#ifndef _EVENT_C_
#define _EVENT_C_

#include "definition.h"
#include "event.h"

void KeyboardEventProcess(int key, int event)
{
    uiGetKeyboard(key, event);

    if (CURR_MODE != EDIT)
        return;

    switch (event)
    {
    case KEY_DOWN:
        switch (key)
        {
        case VK_F1: /*F1: ������ʼ��ֹ��*/
            CaseF1Process();
            break;

        case VK_F2: /*F2: �����жϿ�*/
            CaseF2Process();
            break;

        case VK_F3: /*F3: ����ִ�п�*/
            CaseF3Process();
            break;

        case VK_F4: /*F4���������������*/
            CaseF4Process();
            break;

        case VK_F5: /*F5���༭��ǰѡ�еĶ�����ı��� */
            CaseF5Process();
            break;

        case VK_F10: /*F10: �˳�����*/
            exit(1);
            break;

        case VK_BACK: /*BACKSP: �˸�*/
            break;

        case VK_ESCAPE: /*ESCAPE: �˳�����ѡ��״̬*/
            if (!IS_SELECTED)
                break;
            ((ptr_StartBox)CURR_OBJ)->IsSelected = FALSE;
            ((ptr_StartBox)CURR_OBJ)->Color = SYS_COLOR;
            IS_SELECTED = FALSE;
            CURR_OBJ = NULL;
            CURR_OBJ_KIND = -1;
            break;

        case VK_DELETE:
            if (CURR_OBJ != NULL)
            {
                DeleteObj(CURR_OBJ);
                CURR_OCCUPY--;
                CURR_OBJ = NULL;
                CURR_OBJ_KIND = -1;
            }
            IS_SELECTED = FALSE;
            break;
        }
    case KEY_UP:
        break;
    }
}

void CharEventProcess(char c)
{
    uiGetChar(c);

    if (CURR_MODE != EDIT || !IS_SELECTED || c == 3 || c == 22)
        return;

    string curr_textbuf = ((ptr_StartBox)CURR_OBJ)->Text;
    int len = strlen(curr_textbuf);

    switch (c)
    {
    case 27:   /*ESC*/
    case '\r': /* ע�⣺�س������ﷵ�ص��ַ���'\r'������'\n'*/
        OUT_OF_TEXT = FALSE;
        IS_SELECTED = FALSE;
        IS_IN_TEXT = FALSE;
        ((ptr_StartBox)CURR_OBJ)->IsSelected = FALSE;
        ((ptr_StartBox)CURR_OBJ)->Color = SYS_COLOR;
        CURR_OBJ = NULL;
        CURR_OBJ_KIND = -1;
        break;
    case '\b': /*BACKSPACE*/
        if (len == 0)
            break;
        curr_textbuf[len - 1] = '\0';
        len--;
        OUT_OF_TEXT = FALSE;
        break;
    default:
        if (len > TEXTLEN + 1)
        {
            OUT_OF_TEXT = TRUE;
            break;
        }
        curr_textbuf[len] = c;
        curr_textbuf[len + 1] = '\0';
        len++;
        break;
    }
}

void MouseEventProcess(int x, int y, int button, int event)
{
    uiGetMouse(x, y, button, event);

    if (CURR_MODE != EDIT)
        return;

    static bool isChangeSize = FALSE;   /*���ű�־*/
    static bool isMove = FALSE;         /*�ƶ���־*/
    static double omx = 0.0, omy = 0.0; /*ǰһ�������*/
    double mx, my;                      /*��ǰ�������*/
    double x1, y1, x2, y2, dx, dy;
    ptr_Line Line_Obj = NULL;
    int PreObjID = -1;
    void *PreObj = NULL;

    mx = ScaleXInches(x); /*pixels --> inches*/
    my = ScaleYInches(y); /*pixels --> inches*/

    switch (event)
    {
    case BUTTON_DOWN:
        if (IS_SELECTED)
        { /*����ѡ��״̬*/
            omx = mx;
            omy = my;
            if (button == LEFT_BUTTON)
            { /*������£������ƶ�״̬*/
                isMove = TRUE;
            }
            else if (button == RIGHT_BUTTON)
            { /*�Ҽ������£���������״̬*/
                isChangeSize = TRUE;
            }
            break;
        }

        PickNearestObj(mx, my); /*ѡ�����*/
        if (CURR_OBJ_KIND == -1)
            break;
        ((ptr_StartBox)CURR_OBJ)->Color = SEL_COLOR;
        ((ptr_StartBox)CURR_OBJ)->IsSelected = TRUE;

        IS_SELECTED = TRUE;
        CURR_OCCUPY_EN = TRUE;
        DrawAllObj();
        break;
    case BUTTON_DOUBLECLICK:
        if (IS_SELECTED)
        {
            PreObj = CURR_OBJ;
            PreObjID = ((ptr_StartBox)CURR_OBJ)->ID;

            PickNearestObj(mx, my);
            if (CURR_OBJ_KIND == -1)
                break;

            if (((ptr_StartBox)CURR_OBJ)->ID != PreObjID)
            {
                ((ptr_StartBox)PreObj)->IsSelected = FALSE;
                ((ptr_StartBox)PreObj)->Color = SYS_COLOR;
                ((ptr_StartBox)CURR_OBJ)->IsSelected = TRUE;
                ((ptr_StartBox)CURR_OBJ)->Color = SEL_COLOR;
                Line_Obj = (ptr_Line)GetBlock(sizeof(*Line_Obj));
                Line_Obj->Obj1 = PreObj;
                Line_Obj->ID_1 = PreObjID;
                Line_Obj->Obj2 = CURR_OBJ;
                Line_Obj->ID_2 = ((ptr_StartBox)CURR_OBJ)->ID;
                Line_Obj->PenSize = SYS_PENSIZE;
                Line_Obj->Color = SYS_COLOR;
                DrawLinkLine(Line_Obj);
                InsertNode(List[LINE], NULL, Line_Obj);
                IS_IN_TEXT = FALSE;
            }
            else
                CaseF5Process();
        }
        break;
    case BUTTON_UP:
        isMove = FALSE;       /*�˳��ƶ�״̬*/
        isChangeSize = FALSE; /*�˳�����״̬*/
        break;
    case MOUSEMOVE:
        if (IS_SELECTED && (isMove || isChangeSize))
        { /*ѡ��״̬�£��ƶ�������*/
            dx = mx - omx;
            dy = my - omy;
            if (isMove)
            { /*�ƶ�*/
                ((ptr_StartBox)CURR_OBJ)->x += dx;
                ((ptr_StartBox)CURR_OBJ)->y += dy;
            }
            else if (isChangeSize)
            { /*����*/
                ((ptr_StartBox)CURR_OBJ)->width += dx;
                ((ptr_StartBox)CURR_OBJ)->height = ((ptr_StartBox)CURR_OBJ)->width * OBJ_HEIGHT / OBJ_WIDTH;
            }
            omx = mx;
            omy = my;
            if (CURR_OCCUPY_EN)
            {
                CURR_OCCUPY--;
                CURR_OCCUPY_EN = FALSE;
            }
        }
        break;
    }
}

void TimerEventProcess(int timerID)
{
    display();
}

void CaseF1Process()
{
    /* ��Ļ���ĵ����� */
    double MidX = GetWindowWidth() / 2;
    double MidY = GetWindowHeight() / 2;

    ptr_StartBox StartBox_Obj;
    string textbuf = CopyString("\0");

    StartBox_Obj = (ptr_StartBox)GetBlock(sizeof(*StartBox_Obj));

    StartBox_Obj->ID = CURR_ID;
    CURR_ID++;

    StartBox_Obj->x = MidX + CURR_OCCUPY * OBJ_WIDTH / 2;
    StartBox_Obj->y = MidY - CURR_OCCUPY * OBJ_HEIGHT / 2;
    StartBox_Obj->width = OBJ_WIDTH;
    StartBox_Obj->height = OBJ_HEIGHT;
    StartBox_Obj->Degree = HORIZ;
    StartBox_Obj->PenSize = SYS_PENSIZE;
    StartBox_Obj->Color = SYS_COLOR;
    StartBox_Obj->Text = textbuf;
    StartBox_Obj->IsSelected = FALSE;

    CURR_OCCUPY++;

    InsertNode(List[STARTBOX], NULL, StartBox_Obj);
}

void CaseF2Process()
{
    /* ��Ļ���ĵ����� */
    double MidX = GetWindowWidth() / 2;
    double MidY = GetWindowHeight() / 2;

    ptr_ProcedureBox ProcedureBox_Obj;
    string textbuf = CopyString("\0");

    ProcedureBox_Obj = (ptr_ProcedureBox)GetBlock(sizeof(*ProcedureBox_Obj));

    ProcedureBox_Obj->ID = CURR_ID;
    CURR_ID++;

    ProcedureBox_Obj->x = MidX + CURR_OCCUPY * OBJ_WIDTH / 2;
    ProcedureBox_Obj->y = MidY - CURR_OCCUPY * OBJ_HEIGHT / 2;
    ProcedureBox_Obj->width = OBJ_WIDTH;
    ProcedureBox_Obj->height = OBJ_HEIGHT;
    ProcedureBox_Obj->Degree = HORIZ;
    ProcedureBox_Obj->PenSize = SYS_PENSIZE;
    ProcedureBox_Obj->Color = SYS_COLOR;
    ProcedureBox_Obj->Text = textbuf;
    ProcedureBox_Obj->IsSelected = FALSE;

    CURR_OCCUPY++;

    InsertNode(List[PROCEDUREBOX], NULL, ProcedureBox_Obj);
}

void CaseF3Process()
{
    /* ��Ļ���ĵ����� */
    double MidX = GetWindowWidth() / 2;
    double MidY = GetWindowHeight() / 2;

    ptr_JudgeBox JudgeBox_Obj;
    string textbuf = CopyString("\0");

    JudgeBox_Obj = (ptr_JudgeBox)GetBlock(sizeof(*JudgeBox_Obj));

    JudgeBox_Obj->ID = CURR_ID;
    CURR_ID++;

    JudgeBox_Obj->x = MidX + CURR_OCCUPY * OBJ_WIDTH / 2;
    JudgeBox_Obj->y = MidY - CURR_OCCUPY * OBJ_HEIGHT / 2;
    JudgeBox_Obj->width = OBJ_WIDTH;
    JudgeBox_Obj->height = OBJ_HEIGHT;
    JudgeBox_Obj->Degree = HORIZ;
    JudgeBox_Obj->PenSize = SYS_PENSIZE;
    JudgeBox_Obj->Color = SYS_COLOR;
    JudgeBox_Obj->Text = textbuf;
    JudgeBox_Obj->IsSelected = FALSE;

    CURR_OCCUPY++;

    InsertNode(List[JUDGEBOX], NULL, JudgeBox_Obj);
}

void CaseF4Process()
{
    /* ��Ļ���ĵ����� */
    double MidX = GetWindowWidth() / 2;
    double MidY = GetWindowHeight() / 2;

    ptr_InputAndOutputBox InputAndOutputBox_Obj;
    string textbuf = CopyString("\0");

    InputAndOutputBox_Obj = (ptr_InputAndOutputBox)GetBlock(sizeof(*InputAndOutputBox_Obj));

    InputAndOutputBox_Obj->ID = CURR_ID;
    CURR_ID++;

    InputAndOutputBox_Obj->x = MidX + CURR_OCCUPY * OBJ_WIDTH / 2;
    InputAndOutputBox_Obj->y = MidY - CURR_OCCUPY * OBJ_HEIGHT / 2;
    InputAndOutputBox_Obj->width = OBJ_WIDTH;
    InputAndOutputBox_Obj->height = OBJ_HEIGHT;
    InputAndOutputBox_Obj->Degree = HORIZ;
    InputAndOutputBox_Obj->PenSize = SYS_PENSIZE;
    InputAndOutputBox_Obj->Color = SYS_COLOR;
    InputAndOutputBox_Obj->Text = textbuf;
    InputAndOutputBox_Obj->IsSelected = FALSE;

    CURR_OCCUPY++;

    InsertNode(List[INPUTANDOUTPUTBOX], NULL, InputAndOutputBox_Obj);
}

void CaseF5Process()
{
    if (!IS_SELECTED)
        return;

    IS_IN_TEXT = TRUE;
    ((ptr_StartBox)CURR_OBJ)->Color = EDIT_COLOR;
}

#endif
