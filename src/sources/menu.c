#ifndef _MENU_C_
#define _MENU_C_

#include "definition.h"
#include "menu.h"

void DrawMenu()
{
	double WindowW = WINDOW_X / GetXResolution(), WindowH = WINDOW_Y / GetYResolution();
	double ButtonW = 1.0, ButtonH = 0.4;

	if (IS_SELECTED)
		if (button(GenUIID(0), WindowW - ButtonW * 1.5, ButtonH / 2, ButtonW, ButtonH, "Rorate"))
			((ptr_StartBox)CURR_OBJ)->Degree = !((ptr_StartBox)CURR_OBJ)->Degree;

	static char *menuListFile[] = {
		"File",
		"New   | Ctrl-N",
		"Open | Ctrl-O",
		"Save | Ctrl-S",
		"Exit   | Ctrl-E"};

	static char *menuListDraw[] = {
		"Draw",
		"1 | F1",
		"2 | F2",
		"3 | F3",
		"4 | F4"};

	static char *menuListEdit[] = {
		"Edit",
		"Copy    | Ctrl-C",
		"Paste   | Ctrl-V",
		"Rorate  | Ctrl-R",
		"Delete  | Del"};

	static char *menuListHelp[] = {
		"Help",
		"About",
		"Help"};

	int selection; /* 菜单选中 */

	double MenuH = GetFontHeight() * 1.5;				   /* 菜单高度 */
	double MenuW = TextStringWidth(menuListFile[0]) * 2;   /* 菜单标题宽度 */
	double wlist = TextStringWidth(menuListEdit[1]) * 1.2; /* 菜单条目宽度 */

	drawMenuBar(0, WindowH - MenuH, WindowW, MenuH);

	selection = menuList(GenUIID(0), 0, WindowH - MenuH, MenuW, wlist, MenuH, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (CURR_MODE == EDIT)
		switch (selection)
		{
		case 1:
			printf("New clicked\n");
			break;
		case 2:
			printf("Open clicked\n");
			break;
		case 3:
			printf("Save clicked\n");
			SaveAllObj();
			break;
		case 4:
			printf("Exit clicked\n");
			break;
		default:
			break;
		}

	selection = menuList(GenUIID(0), MenuW, WindowH - MenuH, MenuW, wlist, MenuH, menuListDraw, sizeof(menuListDraw) / sizeof(menuListDraw[0]));
	if (CURR_MODE == EDIT)
		switch (selection)
		{
		case 1:
			CaseF1Process();
			break;
		case 2:
			CaseF2Process();
			break;
		case 3:
			CaseF3Process();
			break;
		case 4:
			CaseF4Process();
			break;
		default:
			break;
		}

	selection = menuList(GenUIID(0), MenuW * 2, WindowH - MenuH, MenuW, wlist, MenuH, menuListEdit, sizeof(menuListEdit) / sizeof(menuListEdit[0]));
	if (CURR_MODE == EDIT)
		switch (selection)
		{
		case 1:
			CopyObj();
			break;
		case 2:
			PasteObj();
			break;
		case 3:
			if (IS_SELECTED)
				((ptr_StartBox)CURR_OBJ)->Degree = !((ptr_StartBox)CURR_OBJ)->Degree;
			break;
		case 4:
			if (CURR_OBJ != NULL)
			{
				DeleteObj(CURR_OBJ);
				CURR_OCCUPY--;
				CURR_OBJ = NULL;
				CURR_OBJ_KIND = -1;
			}
			IS_SELECTED = FALSE;
			break;
		default:
			break;
		}

	selection = menuList(GenUIID(0), MenuW * 3, WindowH - MenuH, MenuW, wlist, MenuH, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	if (CURR_MODE == EDIT)
		switch (selection)
		{
		case 1:
			CURR_MODE = ABOUT;
			break;
		case 2:
			CURR_MODE = HELP;
			break;
		default:
			break;
		}

	double ControlInfoW = TextStringWidth(menuListFile[0]) * 4;
	static char InfoBuffer[256];

	drawMenuBar(0, 0, WindowW, MenuH);

	if (IS_SELECTED)
	{
		if (OUT_OF_TEXT)
			sprintf(InfoBuffer, "Out of max length of text!");
		else if (IS_IN_TEXT)
			sprintf(InfoBuffer, "Editing Text...");
		else
			sprintf(InfoBuffer, "Current Edited Object ID is: %d", ((ptr_StartBox)CURR_OBJ)->ID + 1);
	}
	else
		sprintf(InfoBuffer, "Not Selected.");

	drawLabel(MenuW, GetFontHeight() / 3, InfoBuffer);
}

void DrawHelp()
{
	string color = GetPenColor();
	SetPenColor("black");
	double WindowW = WINDOW_X / GetXResolution(), WindowH = WINDOW_Y / GetYResolution();
	double ButtonW = 1.0, ButtonH = 0.4;
	double LineSpace = GetFontAscent() * 1.5;

	static string HelpWords[20];
	static bool HaveRead = FALSE;
	static CntLine = 0;
	int line;

	FILE *fp = fopen("..\\data\\info\\help.txt", "r");

	if (HaveRead == FALSE)
	{
		for (line = 0; line < 20; line++)
			HelpWords[line] = (string)malloc(sizeof(char) * 200);
		line = 0;
		while (!feof(fp))
		{
			fgets(HelpWords[line], 200, fp);
			line++;
			CntLine++;
		}
	}

	HaveRead = TRUE;

	SetEraseMode(TRUE);
	drawRectangle(WindowW / 4, WindowH / 4, WindowW / 2, WindowH / 2, TRUE);
	SetEraseMode(FALSE);
	drawRectangle(WindowW / 100, WindowH / 6, WindowW *20 /21, WindowH *2 /3 , FALSE);
	drawRectangle(WindowW / 100 + ButtonW * 0.1, WindowH / 6 + ButtonW * 0.1, WindowW *20 / 21 - ButtonW * 0.2, WindowH *2 /3 - ButtonW * 0.2, FALSE);

	for (line = 0; line < CntLine; line++)
	{
		MovePen(WindowW / 3 - TextStringWidth(HelpWords[0]) / 2, WindowH * 5 / 6- LineSpace * (line + 3));
		DrawTextString(HelpWords[line]);
	}

	if (button(GenUIID(0), WindowW / 51 * 50 - ButtonW * 1.5, WindowH / 6 + ButtonH / 2, ButtonW, ButtonH, "OK"))
		CURR_MODE = EDIT;
	SetPenColor(color);
}

void DrawAbout()
{
	string color = GetPenColor();
	SetPenColor("black");
	double WindowW = WINDOW_X / GetXResolution(), WindowH = WINDOW_Y / GetYResolution();
	double ButtonW = 1.0, ButtonH = 0.4;
	double LineSpace = GetFontAscent() * 1.5;

	static string AboutWords[5];
	static bool HaveRead = FALSE;
	static CntLine = 0;
	int line;

	FILE *fp = fopen("..\\data\\info\\about.txt", "r");

	if (HaveRead == FALSE)
	{
		for (line = 0; line < 5; line++)
			AboutWords[line] = (string)malloc(sizeof(char) * 50);
		line = 0;
		while (!feof(fp))
		{
			fgets(AboutWords[line], 50, fp);
			line++;
			CntLine++;
		}
	}

	HaveRead = TRUE;

	SetEraseMode(TRUE);
	drawRectangle(WindowW / 8 * 3, WindowH / 8 * 3, WindowW / 4, WindowH / 4, TRUE);
	SetEraseMode(FALSE);
	drawRectangle(WindowW / 8 * 3, WindowH / 8 * 3, WindowW / 4, WindowH / 4, FALSE);

	for (line = 0; line < CntLine; line++)
	{
		MovePen(WindowW / 2 - TextStringWidth(AboutWords[0]) / 2, WindowH * 5 / 8 - LineSpace * (line + 4));
		DrawTextString(AboutWords[line]);
	}

	if (button(GenUIID(0), WindowW / 8 * 6 - ButtonW * 1.5, WindowH / 8 * 2 + ButtonH / 2, ButtonW/2, ButtonH/2, "OK"))
		CURR_MODE = EDIT;
	SetPenColor(color);
}

#endif
