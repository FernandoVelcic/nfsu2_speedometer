#include "stdafx.h"
#include "Game.h"

HWND FindGame()
{
	HWND hWnd;

	while(true)
	{
		hWnd = FindWindow(NULL, L"NFS Underground 2");

		if(hWnd) {
			printf("Game detected: Need for Speed: Underground 2\r\n");
			g_dwVelocity = 0x007F09E8;

			//Shift
			g_dwShiftBase = 0x0089CDA8;
			g_dwShiftP[0] = 0x00;
			g_dwShiftP[1] = 0x48;
			g_dwShiftP[2] = 0x20;
			g_dwShiftI = 0x38;

			//Dial
			g_dwDialBase = 0x0082AF34;
			g_dwDialP[0] = 0x00;
			g_dwDialP[1] = 0x1D4;
			g_dwDialP[2] = 0x80;
			g_dwDialI = 0x54;

			//NO2 0x008364B0
			break;
		}

		hWnd = FindWindow(NULL, L"Need for Speed™ Most Wanted");

		if(hWnd) {
			printf("Game detected: Need for Speed: Most Wanted\r\n");
			g_dwVelocity = 0x00914654;
			break;
		}

		hWnd = FindWindow(NULL, L"Need for Speed™ Carbono");

		if(hWnd) {
			printf("Game detected: Need for Speed: Carbono\r\n");
			g_dwVelocity = 0x00A8E59C;
			break;
		}

		hWnd = FindWindow(NULL, L"Need for Speed™ Undercover");

		if(hWnd) {
			printf("Game detected: Need for Speed: Undercover\r\n");
			g_dwVelocity = 0x00D83AE4;
			break;
		}

		Sleep(1000);
	}

	return hWnd;
}