/*
 * main.c
 *
 *  Created on: Jun 19, 2014
 *      Author: ichuraev
 */
#include <inkview.h>
#include "MainWindow.h"
#include <fstream>
#include <cstdio>

using namespace FastLearn;

int MonitorProc() {
	static bool was_dictionary = false;
	for (;;) {
		system("ps | grep Dictionary.app | grep -v grep > /mnt/ext1/my_tmp_file.txt");
		std::ifstream ps_file("/mnt/ext1/my_tmp_file.txt",  std::ios_base::binary);
		long nFileLen = 0;
		if (ps_file)
		{
			ps_file.seekg(0, std::ios_base::end);
			nFileLen = ps_file.tellg();
			ps_file.close();
			remove("/mnt/ext1/my_tmp_file.txt");
		}

		fprintf(stderr, "Size: %lu\n", nFileLen);

		if (nFileLen && !was_dictionary) {
			was_dictionary = true;
			InkViewMain(main_handler);
		} else if (!nFileLen && was_dictionary) {
			was_dictionary = false;
		}
	}
	return 0;
}

// TODO: Try to make daemon
int main() {
	pid_t pid = fork();
	if (!pid) {
		umask(0);
		setsid();

		chdir("/");

		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);

		int status = MonitorProc();
		return status;
	} else if (pid == -1) {
		return -1;
	} else {
		return 0;
	}
	//InkViewMain(main_handler);
	//return 0;
}
