/*
 * MainWindow.h
 *
 *  Created on: Jun 19, 2014
 *      Author: ichuraev
 */

#ifndef MAINWINDOWS_H_
#define MAINWINDOWS_H_

#include <inkview.h>

namespace FastLearn {
	int main_handler(int type, int par1, int par2);
	void menu_handler(int index);

	class MainWindow {
	// It is a Singleton
	private:
		static MainWindow *obj_mw;
		// Menu
		static imenu menu1[];

		// Font
		ifont *arialb12;

		iv_menuhandler m_menu_handler;
		iv_handler m_main_handler;

		int cindex;

		MainWindow();
	public:
		static MainWindow * create_window();

		void screen_repaint();
		void msg(char *s);
		void open_menu();
		void set_cindex(int index);
	};

}

#endif /* FUNCTIONS_H_ */
