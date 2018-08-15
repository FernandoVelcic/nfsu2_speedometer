#include "stdafx.h"
#include "Arduino.h"
#include "Game.h"

HWND hWnd;
HANDLE hProcess;
DWORD pId;
DWORD dwExitCode;

void _tmain(int argc, _TCHAR* argv[])
{
	printf("Digital Speedometer\r\n");
	printf("Author: Fernando Velcic\r\n\r\n");

	printf("Please start the game...\r\n");

	hWnd = FindGame();

	GetWindowThreadProcessId(hWnd, &pId);
	hProcess = OpenProcess(PROCESS_VM_READ|PROCESS_QUERY_INFORMATION, false, pId);
	
	if(hProcess) {
		printf("Game injected successfully.\r\n");
	}

	ArduinoSerialConnection();

	while(true)
	{
		GetExitCodeProcess(hProcess, &dwExitCode);

		if(dwExitCode != STILL_ACTIVE) {
			break;
		}

		ReadProcessMemory(hProcess, (LPCVOID)g_dwVelocity, &g_fpVelocity, sizeof(float), NULL);

		g_dwShift = g_dwShiftBase;
		for(int i = 0; i < _countof(g_dwShiftP); i++)
		{
			if( !ReadProcessMemory(hProcess, (LPCVOID)(g_dwShift+g_dwShiftP[i]), &g_dwShift, sizeof(DWORD), NULL) ) {
				break;
			}
		}
		ReadProcessMemory(hProcess, (LPCVOID)(g_dwShift+g_dwShiftI), &g_byShift, sizeof(BYTE), NULL);

		g_dwDial = g_dwDialBase;
		for(int i = 0; i < _countof(g_dwDialP); i++)
		{
			if( !ReadProcessMemory(hProcess, (LPCVOID)(g_dwDial+g_dwDialP[i]), &g_dwDial, sizeof(DWORD), NULL) ) {
				break;
			}
		}
		ReadProcessMemory(hProcess, (LPCVOID)(g_dwDial+g_dwDialI), &g_fpDial, sizeof(float), NULL);

		printf("[DEBUG] MPH: %f\t KM/H: %f\t Shift: %d\t Lights: %d\r\n", g_fpVelocity, MPH2KMH(g_fpVelocity), g_byShift, (unsigned char)(g_fpDial/1000)-1);

		SendSpeedometerInfo();

		Sleep(REFRESH_TIME);
	}

	printf("The game was closed by user.\r\n");

	system("pause");
}

//100*g_fpVelocity/(50+30*(g_byShift-2))