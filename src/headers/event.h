#ifndef _EVENT_H_
#define _EVENT_H_

void KeyboardEventProcess(int key, int event);
void CharEventProcess(char c);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);

void CaseF1Process();
void CaseF2Process();
void CaseF3Process();
void CaseF4Process();
void CaseF5Process();

#endif