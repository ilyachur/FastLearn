/*
 * functions.c
 *
 *  Created on: Jun 19, 2014
 *      Author: ichuraev
 */
#include <inkview.h>
#include "functions.h"

ifont *arialb12;

int cindex= 0;

static imenu menu1[] = {
	{ ITEM_HEADER,  0, "Menu", NULL },
	{ ITEM_ACTIVE, 101, "Say 'Hi'", NULL },
	{ ITEM_ACTIVE, 102, "Exit", NULL },
	{  0,  0, NULL, NULL }
};

void menu1_handler(int index) {
	cindex = index;

	switch (index) {
	case 101:
		Message(ICON_INFORMATION, "Message", "Hello, World! This message will disappear after 5 seconds, or press any key", 5000);
		break;
	case 102:
		CloseApp();
		break;
	}
}

void msg(char *s) {
	FillArea(350, 770, 250, 20, WHITE);
	SetFont(arialb12, BLACK);
	DrawString(350, 770, s);
	PartialUpdate(350, 770, 250, 20);
}

void mainscreen_repaint() {
	ClearScreen();
	FullUpdate();
}

int main_handler(int type, int par1, int par2) {

	fprintf(stderr, "[%i %i %i]\n", type, par1, par2);

	if (type == EVT_INIT) {
	    arialb12 = OpenFont("DroidSans", 12, 1);
	}

	if (type == EVT_SHOW) {
		// occurs when this event handler becomes active
		mainscreen_repaint();
	}

	if (type == EVT_KEYPRESS) {
		switch (par1) {
		case KEY_OK:
			OpenMenu(menu1, cindex, 20, 20, menu1_handler);
			break;
		case KEY_BACK:
			CloseApp();
			break;
		case KEY_LEFT:
			msg("KEY_LEFT");
			break;
		case KEY_RIGHT:
			msg("KEY_RIGHT");
			break;
		case KEY_UP:
			msg("KEY_UP");
			break;
		case KEY_DOWN:
			msg("KEY_DOWN");
			break;
		case KEY_MUSIC:
			msg("KEY_MUSIC");
			break;
		case KEY_MENU:
			OpenMenu(menu1, cindex, 20, 20, menu1_handler);
			break;
		case KEY_DELETE:
			msg("KEY_DELETE");
			break;
		}
	}

	if (type == EVT_EXIT) {
		// occurs only in main handler when exiting or when SIGINT received.
		// save configuration here, if needed
	}

	return 0;
}
