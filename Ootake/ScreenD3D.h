/******************************************************************************
	[ScreenD3D.h]

		Define Direct3D screen interface.

******************************************************************************/
#ifndef SCREEND3D_H_INCLUDED
#define SCREEND3D_H_INCLUDED

#include "TypeDefs.h"


BOOL
SCREEND3D_Init(
	Sint32		width,
	Sint32		height,
	Sint32		magnification, //Kitao�ǉ�
	Uint32		flags); //Kitao�ǉ�

BOOL
SCREEND3D_ChangeMode(
	Sint32		width,
	Sint32		height,
	Sint32		magnification, //Kitao�ǉ�
	Uint32		flags);

//Kitao�X�V
BOOL
SCREEND3D_WaitVBlank(
	BOOL	bDraw);

void
SCREEND3D_PutPixel(
	Sint32		x,
	Sint32		y,
	Uint32		pixel);

void*
SCREEND3D_GetBuffer();

const Sint32
SCREEND3D_GetBufferPitch();

//Kitao�ǉ�
void
SCREEND3D_Clear(
	byte	r,
	byte	g,
	byte	b);

//Kitao�X�V
void
SCREEND3D_Fill(
	Uint32	color);

//Kitao�X�V
void
SCREEND3D_Blt(
	Uint32*		pSrc,
	Sint32		srcX,
	Sint32		srcY,
	Uint16*		pTvW,
	Sint32		srcH,
	Sint32		executeCode);

void
SCREEND3D_Deinit();

//Kitao�ǉ�
void
SCREEND3D_SetSyncTo60HzScreen(
	BOOL	bSyncTo60HzScreen);

//Kitao�ǉ�
BOOL
SCREEND3D_GetSyncTo60HzScreen();

//Kitao�ǉ��Bv2.65
void
SCREEND3D_UpdateWindowsAutoVSync();

//Kitao�ǉ�
void
SCREEND3D_SetMessageText(
	char*	pText);

//Kitao�ǉ�
DWORD
SCREEND3D_GetLastTimeSyncTime();

//Kitao�ǉ�
void
SCREEND3D_WriteScreenshot(
	FILE*	fp);

//Kitao�ǉ�
void
SCREEND3D_SetMagnification(
	Sint32	magnification);

//Kitao�ǉ�
Sint32
SCREEND3D_GetMagnification();

//Kitao�ǉ�
BOOL
SCREEND3D_GetOldVideoChip();

//Kitao�ǉ�
void
SCREEND3D_SetWindowsAero(
	BOOL	bWindowsAero);

//Kitao�ǉ�
void
SCREEND3D_SetCenterText(
	char*	pText);

#endif // SCREEND3D_H_INCLUDED
