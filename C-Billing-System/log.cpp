#include <iostream>
#include <ctime>
#include <string>
#include "log.h"
using namespace std;

constexpr auto logFile = "log/logFile.txt";

void log_save(string loginfo)
{
	time_t tt = time(0);
	char l_ls_t[25];
	struct tm* ttime;
	ttime = localtime(&tt);
	strftime(l_ls_t, sizeof(l_ls_t), "%YƒÍ%m‘¬%d»’ %H:%M:%S", ttime);
	string s = l_ls_t;
	s = s + "  -  " + loginfo + "\n";
	FILE* fp;
	if ((fp = fopen(logFile, "a")) == NULL) {
		return;
	}
	fprintf(fp, "%s", s.c_str());
	fclose(fp);
}