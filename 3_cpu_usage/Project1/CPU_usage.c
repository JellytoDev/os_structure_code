#include <stdio.h>

#include <Windows.h>

#include <time.h>



double CPU_Usage() // CPU 사용량 함수
{
	FILETIME idle, kernel, user; 

	int i = 0;
	double r = 0;

	GetSystemTimes(&idle, &kernel, &user); 

	DWORD kehigh1 = kernel.dwHighDateTime;
	DWORD kelow1 = kernel.dwLowDateTime;
	DWORD ushigh1 = user.dwHighDateTime;
	DWORD uslow1 = user.dwLowDateTime;
	DWORD idhigh1 = idle.dwHighDateTime;
	DWORD idlow1 = idle.dwLowDateTime;

	Sleep(1000); // 0.5초 동안 쉰 뒤에 idle, kernel, user cpu 시간을 가져온다.

	GetSystemTimes(&idle, &kernel, &user); 

	DWORD kehigh2 = kernel.dwHighDateTime;
	DWORD kelow2 = kernel.dwLowDateTime;
	DWORD ushigh2 = user.dwHighDateTime;
	DWORD uslow2 = user.dwLowDateTime;
	DWORD idhigh2 = idle.dwHighDateTime;
	DWORD idlow2 = idle.dwLowDateTime;

	double ke = (kehigh2 + kelow2) - (kehigh1 + kelow1);
	double us = (ushigh2 + uslow2) - (ushigh1 + uslow1);
	double id = (idhigh2 + idlow2) - (idhigh1 + idlow1);

	double cpu_usage = (us + ke - id) * 100 / (us + ke); // cpu 사용률

	return cpu_usage;

}



void main()
{
	int n = 0;
	double a[1000];

	SYSTEMTIME time; // GetLocalTIme 함수의 매개변수

	while (1)
	{
		GetLocalTime(&time);
		double cpu_usage = CPU_Usage(); // cpu 사용량 받아오기
		a[n] = cpu_usage;

		if (n == 0) 
			printf("   %d %d.%02d.%02d %02d:%02d:%02d :"
				, n, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);

		if (n >= 1) // CPU 사용량 출력
			printf("   %d %d.%02d.%02d %02d:%02d:%02d : [CPU Load: %0.2f%%]"
				, n, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, 
				cpu_usage);


		if (n < 5) // 5보다 작을시 평균 구하지 않음
			printf("\n");
		else if (n >= 5 && n < 10) // 5초 동안 평균
			printf(" [5sec avg: %0.2f%%]\n", (double)(a[n - 4] + a[n - 3] + a[n - 2] + a[n - 1] + a[n]) / 5);
		else if (n >= 10 && n < 15) // 10초 동안 평균
			printf(" [5sec avg: %0.2f%%] [10sec avg: %0.2f%%]\n", (double)(a[n - 4] + a[n - 3] +
				a[n - 2] + a[n - 1] + a[n]) / 5,
				(double)(a[n - 9] + a[n - 8] + a[n - 7] + a[n - 6] + a[n - 5] + a[n - 4] + a[n - 3] + 
					a[n - 2] + a[n - 1] + a[n]) / 10);
		else if (n >= 15) // 15초 동안 평균
			printf(" [5sec avg: %0.2f%%] [10sec avg: %0.2f%%] [15sec avg: %0.2f%%]\n",
				(double)(a[n - 4] + a[n - 3] + a[n - 2] + a[n - 1] + a[n]) / 5,
				(double)(a[n - 9] + a[n - 8] + a[n - 7] + a[n - 6] + a[n - 5] + a[n - 4] + a[n - 3] + 
					a[n - 2] + a[n - 1] + a[n]) / 10,
				(double)(a[n - 14] + a[n - 13] + a[n - 12] + a[n - 11] + a[n - 10] + a[n - 9] + a[n - 8] +
					a[n - 7] + a[n - 6] + a[n - 5] + a[n - 4] + a[n - 3] + a[n - 2] + a[n - 1] + a[n]) / 15);
		n++;

	}

}