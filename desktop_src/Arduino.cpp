#include "stdafx.h"
#include "Arduino.h"
#include <math.h> 

HANDLE hPort;

#pragma pack(2)
struct sSpeedometerInfo
{
	/*<thisrel this+0x0>*/ /*|0x2|*/ unsigned short	Speed;
	/*<thisrel this+0x2>*/ /*|0x1|*/ unsigned char	Shift;
	/*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char	Leds;
} SpeedometerInfo;
#pragma pack()

void SendSpeedometerInfo()
{
	SpeedometerInfo.Speed = (unsigned short)(MPH2KMH(g_fpVelocity));
	SpeedometerInfo.Shift = g_byShift;
	
	//SpeedometerInfo.Leds = (unsigned char)pow((double)(g_fpDial-1000.0f), (double)1/4.5);
	SpeedometerInfo.Leds = (unsigned char)(g_fpDial/1000)-1;

	DWORD dwDst;
	WriteFile(hPort, (LPCVOID)&SpeedometerInfo, sizeof(SpeedometerInfo), &dwDst, NULL);
}

bool ArduinoSerialConnection()
{
	hPort = CreateFile(L"\\\\.\\COM13", GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	
	if(hPort == INVALID_HANDLE_VALUE) {
		printf("[DEBUG] Serial connection error: %d", GetLastError());
		return false;
	}
	
	DCB dcbSerialParams = {0};
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	
	if ( !GetCommState(hPort, &dcbSerialParams) ) {
		printf("[DEBUG] Cannot get serial communication status: %d", GetLastError());
		return false;
	}

	dcbSerialParams.BaudRate = CBR_19200;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;

	if( !SetCommState(hPort, &dcbSerialParams) )
	{
		printf("[DEBUG] Cannot set serial communication status: %d", GetLastError());
		return false;
	}

	return true;
}

/*
bitfield method
	SpeedometerInfo.Leds |= 0 << 0;
	SpeedometerInfo.Leds |= 0 << 1;
	SpeedometerInfo.Leds |= 1 << 2;
	SpeedometerInfo.Leds |= 1 << 3;
	SpeedometerInfo.Leds |= 1 << 4;
	SpeedometerInfo.Leds |= 1 << 5;
	SpeedometerInfo.Leds |= 1 << 6;
	SpeedometerInfo.Leds |= 0 << 7;
*/