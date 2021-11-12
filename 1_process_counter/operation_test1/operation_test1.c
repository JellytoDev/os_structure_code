#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<tlHelp32.h>

void WINAPI GetLocalTime(_Out_ LPSYSTEMTIME lpSystemTime);

void main() {
	SYSTEMTIME time;

	printf("Process Counter Start\n");

	while (1) {
		int n = 0;
		HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		BOOL procount;
		PROCESSENTRY32 proentry;
		proentry.dwSize = sizeof(PROCESSENTRY32);
		procount = Process32First(snap, &proentry);

		while(procount) {
			procount = Process32Next(snap, &proentry);
			n++;
		}
		CloseHandle(snap);

		GetLocalTime(&time);
		printf("%d. %02d. %02d  %02d:%02d:%02d : %d \n", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond,n);
		Sleep(1000);
	}
}

	