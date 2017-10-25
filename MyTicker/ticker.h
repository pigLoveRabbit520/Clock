#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <windows.h>

using namespace std;

class Ticker {
    public:
    static string GetCurrentTimeStr()
    {
        time_t timep;
        struct tm *p;
        time(&timep);
        p = localtime(&timep); // 取得当地时间
        char buff[25];
        sprintf(buff, "%d-%02d-%02d %02d:%02d:%02d", (1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
		string res(buff);
        return res;
    }
};
