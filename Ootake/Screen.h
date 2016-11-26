/******************************************************************************
	[Screen.h]
		��ʏo�͌n�̃C���^�t�F�C�X���`���܂��B

		Define screen interface.

	Copyright (C) 2004 Ki

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
******************************************************************************/
#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include "TypeDefs.h"

#define SCREEN_FDEFAULT					0
#define SCREEN_FFULLSCREEN				1
#define SCREEN_FHARDWAREACCELERATION	2

//Kitao�ǉ�
void
SCREEN_SaveWindowPosition();

//Kitao�ǉ�
void
SCREEN_LoadWindowPosition();

//Kitao�X�V�BSCREEN_ChangeMode()���疼�O��ύX�����Bv2.28
BOOL
SCREEN_Init(
	Sint32		width,
	Sint32		height,
	Sint32		magnification, //Kitao�ǉ�
	Uint32		bitsPerPixel,
	Uint32		flags);

void
SCREEN_Deinit();

BOOL
SCREEN_ToggleFullScreen();

//Kitao�X�V
BOOL
SCREEN_WaitVBlank(
	BOOL	bDraw);

void*
SCREEN_GetBuffer();

const Sint32
SCREEN_GetBufferPitch();

//Kitao�ǉ�
void
SCREEN_Clear(
	byte	r,
	byte	g,
	byte	b);

//Kitao�X�V
void
SCREEN_Fill(
	Uint32	color);

//Kitao�X�V
void
SCREEN_Blt(
	Uint32*		pSrc,
	Sint32		srcX,
	Sint32		srcY,
	Uint16*		pSrcW,
	Sint32		srcH,
	Sint32		executeCode);

//Kitao�ǉ�
void
SCREEN_SetSyncTo60HzScreen(
	BOOL	bSyncTo60HzScreen);

//Kitao�ǉ�
BOOL
SCREEN_GetSyncTo60HzScreen();

//Kitao�ǉ�
void
SCREEN_SetMessageText(
	char*	pText);

//Kitao�ǉ�
void
SCREEN_SetGamma(
	Sint32	scanLineType,
	Sint32	scanLineDensity);

//Kitao�ǉ�
DWORD
SCREEN_GetLastTimeSyncTime();

//Kitao�ǉ�
void
SCREEN_WriteScreenshot(
	FILE*	fp);

//Kitao�ǉ�
void
SCREEN_SetMagnification(
	Sint32	magnification);

//Kitao�ǉ�
Sint32
SCREEN_GetMagnification();

//Kitao�ǉ�
void
SCREEN_SetPixelMagnification(
	Sint32*	wMag,
	Sint32*	hMag);

//Kitao�ǉ�
Sint32
SCREEN_GetVerticalScanFrequency();

#endif // SCREEN_H_INCLUDED
