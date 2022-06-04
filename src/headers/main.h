#ifndef _MAIN_H_
#define _MAIN_H_

#include "definition.h"

//=============================================================================================================================================//
/* 默认值定义 */
//=============================================================================================================================================//

/* 默认绘图属性 */
extern string SYS_COLOR;
extern int SYS_PENSIZE;
extern double WINDOW_X;
extern double WINDOW_Y;

/* 默认对象长宽 */
extern double OBJ_WIDTH;
extern double OBJ_HEIGHT;

//=============================================================================================================================================//
/* 函数声明 */
//=============================================================================================================================================//

/* 功能:主函数
 * 参数:无
 * 返回值:正常退出返回0
 * 说明:调用 DrawMenu() 来绘制菜单,仅初始化时调用一次;
 */
void Main();

/* 功能:重新绘制所有图形
 * 参数:无
 * 返回值:无
 */
void display();

/* 功能:绘制菜单
 * 参数:无
 * 返回值:无
 * 说明:控件列表: File -New -Open -Save -Exit
 *               Draw -1(F1) -2(F2) -3(F3)
 *               Edit -Copy -Paste -Delete
 *               Help -About -Help
 */
void DrawMenu();

/* 功能:绘制所有对象
 * 参数:无
 * 返回值:无
 */
void DrawAllObj();

/* 功能:响应键盘事件
 * 参数1:按键名
 * 参数2:事件
 * 说明:事件表:
 * |  按键  |         操作        |         调用函数         |
 * |   F1   |  绘制随机起始终止框  |      DrawStartBox()     |
 * |   F2   |    绘制随机判断框    |     DrawJudegeBox()     |
 * |   F3   |    绘制随机执行框    |    DrawProcedureBox()   |
 * |  F10   |       退出程序      |         exit(1)         |
 * | Ctrl+N |  删除所有链表,清屏， |      DeleteAllObj()     |
 *             重新绘制菜单        |     DisplayClear()      |
 *                                |       DrawMenu()        |
 * | Ctrl+S |   保存到save.data   |       SaveAllObj()      |
 * | Ctrl+O |   从save.data读取   |       LoadAllObj()      |
 * | Ctrl+C |    复制选中的对象    |        CopyObj()        |
 * | Ctrl+V |       粘贴对象      |        PasteObj()       |
 * | BackSP |       删除对象      |       DeleteObj()       |
 * | ESCAPE |   退出对象选中状态   |       DeleteObj()       |
 */
void KeyboardEventProcess(int key, int event);

/* 功能:键盘回调函数辅助函数,处理 F1/ F2/ F3 事件
 * 参数:无
 * 说明:无
 */
void CaseF1Process();
void CaseF2Process();
void CaseF3Process();

/* 功能:响应鼠标事件事件
 * 参数1:x坐标
 * 参数2:y坐标
 * 参数3:按键
 * 参数4:事件
 * 说明:事件表:暂缺
 */
void MouseEventProcess(int x, int y, int button, int event);

/* 功能:响应字符事件事件
 * 参数:字符
 * 说明:事件表:暂缺
 */
void CharEventProcess(char c);

void TimerEventProcess(int timerID);

/* 功能:新增一条直线，连接两个控件
 * 参数1:对象1 ID
 * 参数2:对象2 ID
 * 返回值:无
 */
void LinkTwoObj(int ID1, int ID2);

/* 功能:缩放对象
 * 参数:对象指针，即CURR_OBJ
 * 返回值:无
 */
void EnlargeObj(void *ptr_Obj);

/* 功能:复制选中的对象
 * 参数:无
 * 返回值:无
 * 说明:若有对象被选中且按下 Ctrl+C, 则令 TEMP 指向该对象
 */
void CopyObj();

/* 功能:粘贴选中的对象
 * 参数:无
 * 返回值:无
 * 说明:在当前鼠标位置生成一个新对象,除位置外其余参数与 TEMP 指向的对象相同
 */
void PasteObj();

/* 功能:删除对象
 * 参数:对象指针，即CURR_OBJ
 * 返回值:无
 */
void DeleteObj(void *ptr_Obj);

/* 功能:遍历链表,找到给定 ID 对应的对象
 * 参数:对象ID
 * 返回值:找到的对象指针
 */
void *SearchObj(int ID);

/* 功能:SearchObj辅助函数
 * 参数1:待查找data指针
 * 参数2:给定ID
 * 返回值:是否相等,相等为TRUE
 */
bool equalfunptr_PBox(void *obj1, void *obj2);
bool equalfunptr_JBox(void *obj1, void *obj2);
bool equalfunptr_SBox(void *obj1, void *obj2);
bool equalfunptr_IBox(void *obj1, void *obj2);

/* 功能:保存所有对象到save.data
 * 参数:无
 * 返回值:无
 */
void SaveAllObj();

/* 功能:从save.data读取
 * 参数:无
 * 返回值:无
 */
void LoadAllObj();

/* 功能:绘制起始框
 * 参数:起始框指针
 * 返回值:无
 */
extern void DrawStartBox(void *StartBox);
extern void DrawProcedureBox(void *ProcedureBox);
extern void DrawJudgeBox(void *JudgeBox);
extern void DrawInputAndOutputBox(void *InputAndOutputBox);

extern void PickNearestObj(double mx, double my);

extern void test();

#endif
