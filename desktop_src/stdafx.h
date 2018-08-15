// stdafx.h: archivo de inclusión de los archivos de inclusión estándar del sistema
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

// TODO: mencionar aquí los encabezados adicionales que el programa necesita
#include <Windows.h>

#define MPH2KMH(speed) (speed*1.609344)
#define REFRESH_TIME 50

extern DWORD g_dwVelocity;
extern float g_fpVelocity;

//Shift
extern DWORD g_dwShiftBase;
extern DWORD g_dwShiftP[3];
extern DWORD g_dwShiftI;

extern DWORD g_dwShift;
extern BYTE g_byShift;

//Dial
extern DWORD g_dwDialBase;
extern DWORD g_dwDialP[3];
extern DWORD g_dwDialI;

extern DWORD g_dwDial;
extern float g_fpDial;


