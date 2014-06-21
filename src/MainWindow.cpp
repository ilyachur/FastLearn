/*
 * MainWindow.c
 *
 *  Created on: Jun 19, 2014
 *      Author: ichuraev
 */
#include <inkview.h>
#include "MainWindow.h"

FastLearn::MainWindow * FastLearn::MainWindow::obj_mw = NULL;

imenu FastLearn::MainWindow::menu1[] = {
	{ ITEM_HEADER,  0, (char*)"Menu", NULL },
	{ ITEM_ACTIVE, 101, (char*)"Say 'Hi'", NULL },
	{ ITEM_ACTIVE, 102, (char*)"Run Calc'", NULL },
	{ ITEM_ACTIVE, 103, (char*)"Exit", NULL },
	{  0,  0, NULL, NULL }
};

FastLearn::MainWindow::MainWindow(): cindex(0) {
	m_main_handler = FastLearn::main_handler;
	m_menu_handler = FastLearn::menu_handler;
	arialb12 = OpenFont("DroidSans", 12, 1);
}

FastLearn::MainWindow * FastLearn::MainWindow::create_window() {
	if (obj_mw == NULL) {
		obj_mw = new MainWindow();
	}
	return obj_mw;
}

void FastLearn::MainWindow::screen_repaint() {
	ClearScreen();
	FullUpdate();
}

void FastLearn::MainWindow::msg(char *s) {
	FillArea(350, 770, 250, 20, WHITE);
	SetFont(arialb12, BLACK);
	DrawString(350, 770, s);
	PartialUpdate(350, 770, 250, 20);
}

void FastLearn::MainWindow::open_menu() {
	OpenMenu(menu1, cindex, 20, 20, m_menu_handler);
}

void FastLearn::MainWindow::set_cindex(int index) {
	cindex = index;
}

void FastLearn::menu_handler(int index) {
	MainWindow *mw = MainWindow::create_window();
	mw->set_cindex(index);
	int status;
	pid_t p;

	switch (index) {
	case 101:
		Message(ICON_INFORMATION, "Message", "Hello, World! This message will disappear after 5 seconds, or press any key", 5000);
		break;
	case 102:
		p = fork();
		if (!p) {
			execv("/mnt/ext1/applications/calc.app", NULL);
		} else {
			wait(&status);
			mw->screen_repaint();
			char str[256];
			sprintf(str," Process pid: %d Child process return: %d", getpid(), WEXITSTATUS(status));
			Message(ICON_INFORMATION, "ProcInfo", str, 5000);
		}
		break;
	case 103:
		CloseApp();
		break;
	}
}

int FastLearn::main_handler(int type, int par1, int par2) {
	fprintf(stderr, "[%i %i %i]\n", type, par1, par2);

	MainWindow *mw = MainWindow::create_window();

	if (type == EVT_INIT) {
		//arialb12 = OpenFont("DroidSans", 12, 1);
	}

	if (type == EVT_SHOW) {
		// occurs when this event handler becomes active
		mw->screen_repaint();
	}

	if (type == EVT_KEYPRESS) {
		switch (par1) {
		case KEY_OK:
			mw->open_menu();
			break;
		case KEY_BACK:
			CloseApp();
			break;
		case KEY_LEFT:
			mw->msg((char*)"KEY_LEFT");
			break;
		case KEY_RIGHT:
			mw->msg((char*)"KEY_RIGHT");
			break;
		case KEY_UP:
			mw->msg((char*)"KEY_UP");
			break;
		case KEY_DOWN:
			mw->msg((char*)"KEY_DOWN");
			break;
		case KEY_MUSIC:
			mw->msg((char*)"KEY_MUSIC");
			break;
		case KEY_MENU:
			mw->open_menu();
			break;
		case KEY_DELETE:
			mw->msg((char*)"KEY_DELETE");
			break;
		}
	}

	if (type == EVT_EXIT) {
		// occurs only in main handler when exiting or when SIGINT received.
		// save configuration here, if needed
	}

	return 0;
}
