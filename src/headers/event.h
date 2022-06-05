#ifndef _EVENT_H_
#define _EVENT_H_

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

/* 功能:键盘回调函数辅助函数,处理 F1/ F2/ F3 事件
 * 参数:无
 * 说明:无
 */
void CaseF1Process();
void CaseF2Process();
void CaseF3Process();
void CaseF4Process();
void CaseF5Process();

#endif