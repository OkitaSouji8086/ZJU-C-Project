#ifndef _READ_INFO_C_
#define _READ_INFO_C_

#include "definition.h"
#include "readInfo.h"

extern double WINDOW_X;
extern double WINDOW_Y;
extern mode CURR_MODE;

void DrawHelp()
{
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
	drawRectangle(WindowW / 4, WindowH / 4, WindowW / 2, WindowH / 2, FALSE);
	drawRectangle(WindowW / 4 + ButtonW * 0.1, WindowH / 4 + ButtonW * 0.1, WindowW / 2 - ButtonW * 0.2, WindowH / 2 - ButtonW * 0.2, FALSE);

	for (line = 0; line < CntLine; line++)
	{
		MovePen(WindowW / 2 - TextStringWidth(HelpWords[0]) / 2, WindowH * 3 / 4 - LineSpace * (line + 3));
		DrawTextString(HelpWords[line]);
	}

	if (button(GenUIID(0), WindowW / 4 * 3 - ButtonW * 1.5, WindowH / 4 + ButtonH / 2, ButtonW, ButtonH, "OK"))
		CURR_MODE = EDIT;
}

void DrawAbout()
{
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

	if (button(GenUIID(0), WindowW / 8 * 5 - ButtonW * 1.5, WindowH / 8 * 3 + ButtonH / 2, ButtonW, ButtonH, "OK"))
		CURR_MODE = EDIT;
}

#endif
