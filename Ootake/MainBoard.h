/*******************************************************************************
	[MainBoard.h]

	Copyright (C) 2004 Ki

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*******************************************************************************/
#ifndef MAIN_BOARD_H
#define MAIN_BOARD_H

#include <stdio.h>
#include "TypeDefs.h"
#include "CPU.h"
#include "VDC.h"
#include "APU.h"
#include "PSG.h"
#include "IntCtrl.h"
#include "Timer.h"
#include "Cartridge.h"
#include "JoyPad.h"
#include "Mouse.h"
#include "MB128.h"
#include "CDROM.h"
#include "ADPCM.h"

//Kitao�ǉ��B�X�e�[�g�Z�[�u�̃o�[�W�����B�Â����̂���ʂ��ēǂݍ��߂�悤�ɂ��邽�߂ɕK�v�B
//v0.50��1�Bv0.51����2�ɁBv0.57����3�ɁBv0.58����4�ɁBv0.60����5�ɁBv0.61����6�ɁB
//v0.62����7�ɁBv0.64����8�ɁBv0.65����9�ɁBv0.72����10�ɁBv0.74����11�ɁBv0.78����12�ɁB
//v0.79����13�ɁBv0.80����14�ɁBv0.82����15�ɁBv0.87����16�ɁBv0.89����17�ɁBv0.91����18�ɁB
//v0.92����19�ɁBv0.94����20�ɁBv0.95����21�ɁBv1.00����22�ɁBv1.02����23�ɁBv1.03����24�ɁB
//v1.08����25�ɁBv1.11����26�ɁBv1.15����27�ɁBv1.30����28�ɁBv1.31����29�ɁBv1.38����30�ɁB
//v1.40����31�ɁBv1.43����32�ɁB(33,34��v1.61beta)�Bv1.61����35�ɁBv1.63����36�ɁB
//v1.65����37�ɁBv2.00����40�ɁBv2.08����41�ɁBv2.27����42�ɁBv2.28����43�ɁBv2.47beta����44�ɁB
//v2.47����45�ɁB
#define SAVE_STATE_VERSION	45


enum RamType
{
	MAINBOARD_MAINRAM = 0,
	MAINBOARD_BUFFERRAM,
	MAINBOARD_ARCADERAM
};


BOOL
MAINBOARD_Init(
	const char*		pGameName);

void
MAINBOARD_Deinit();

void
MAINBOARD_Pause(
	BOOL	bPause);

//Kitao�ǉ�
void
MAINBOARD_PauseNoMessage(
	BOOL	bPause);

BOOL
MAINBOARD_SaveBRAM(
	const char*		pathName);

BOOL
MAINBOARD_LoadBRAM(
	const char*		pathName);


void
MAINBOARD_Reset();


void
MAINBOARD_AdvanceFrame();

Sint32
MAINBOARD_AdvanceInstruction();


//Kitao�ǉ�
void
MAINBOARD_ResetFastForwardingCount();


BOOL
MAINBOARD_ChangeScreenMode(
	Sint32		screenWidth,
	Sint32		screenHeight,
	Sint32		magnification,
	BOOL		bFullScreen,
	Uint32		bFullScreenColor); //Kitao�X�V�BbFullScreenColor�c�t���X�N���[������bitsPerPixel


BOOL
MAINBOARD_ChangeSoundMode(
	Uint32		bufferSize,
	Uint32		sampleRate,
	Uint32		masterVolume,
	BOOL		bReverb);

BOOL
MAINBOARD_SaveState(
	FILE*		p);

BOOL
MAINBOARD_LoadState(
	FILE*		p);

void
MAINBOARD_ChangeMemoryValue(
	Sint32		ramType,
	Uint32		addr,
	Uint8		data);

//Kitao�ǉ�
void
MAINBOARD_ScreenUpdate(
	BOOL	bVsync,
	BOOL	bFullScreenRefresh);

//Kitao�ǉ�
void
MAINBOARD_ScreenEncord();

//Kitao�ǉ�
void
MAINBOARD_ScreenUpdateFast();

//Kitao�ǉ��Bv2.77
void
MAINBOARD_ScreenUpdateClear();

//Kitao�ǉ�
void
MAINBOARD_DrawScreenshot();

//Kitao�ǉ�
void
MAINBOARD_ScreenClear();

//Kitao�ǉ�
BOOL
MAINBOARD_GetPause();

//Kitao�ǉ�
void
MAINBOARD_SetBigSoundBuffer(
	Sint32 n);

//Kitao�ǉ�
Sint32
MAINBOARD_GetMagnification();

//Kitao�ǉ�
Sint32
MAINBOARD_GetScanLine();

//Kitao�ǉ�
void
MAINBOARD_SetSuperGrafx(
	Sint32	superGrafx);

//Kitao�ǉ�
Sint32
MAINBOARD_GetSuperGrafx();

//Kitao�ǉ�
void
MAINBOARD_SetArcadeCard(
	BOOL	arcadeCard);

//Kitao�ǉ�
BOOL
MAINBOARD_GetArcadeCard();

//Kitao�ǉ�
void
MAINBOARD_SetBackupFull(
	BOOL	backupFull);

//Kitao�ǉ�
BOOL
MAINBOARD_GetBackupFull();

//Kitao�ǉ�
void
MAINBOARD_SetStretched(
	BOOL	bStretched,
	BOOL	bVStretched);

//Kitao�ǉ�
Uint32
MAINBOARD_GetStateVersion();

//Kitao�ǉ�
BOOL
MAINBOARD_LoadScreenBuf(
	Sint32	num,
	FILE*	p);

//Kitao�ǉ�
void
MAINBOARD_RestoreScreenBuf();

//Kitao�ǉ�
void
MAINBOARD_ResetFastForwardingCount();

//Kitao�ǉ�
void
MAINBOARD_SetFastForwarding(
	Sint32	fastForwarding,
	BOOL	bSoundAjust,
	BOOL	bReset);

//Kitao�ǉ�
Sint32
MAINBOARD_GetFastForwarding();

//Kitao�ǉ�
Sint32
MAINBOARD_GetFastForwardingR();

//Kitao�ǉ�
BOOL
MAINBOARD_GetSystemInit();

//Kitao�ǉ�
void
MAINBOARD_TG16BitConvert();

//Kitao�ǉ�
void
MAINBOARD_OverDumpedConvert();

//Kitao�ǉ�
void
MAINBOARD_IncSysTime();

//Kitao�ǉ�
void
MAINBOARD_SetGradiusII();

//Kitao�ǉ�
int
MAINBOARD_GetProcessingDelay();

//Kitao�ǉ�
int
MAINBOARD_GetDisplayedFrames();

//Kitao�ǉ�
void
MAINBOARD_ResetPrevTvW();

//Kitao�ǉ�
BOOL
MAINBOARD_GetResolutionChange();

//Kitao�ǉ�
void
MAINBOARD_SetResolutionChange(
	BOOL	bResolutionChange);

//Kitao�ǉ�
Sint32
MAINBOARD_GetShowOverscanTop();

//Kitao�ǉ�
Sint32
MAINBOARD_GetShowOverscanBottom();

//Kitao�ǉ�
Sint32
MAINBOARD_GetShowOverscanLeft();

//Kitao�ǉ�
Sint32
MAINBOARD_GetShowOverscanRight();

//Kitao�ǉ�
BOOL
MAINBOARD_GetShowOverscan();

//Kitao�ǉ�
void
MAINBOARD_SetShowOverscanTop(
	Sint32	showOverscanTop);

//Kitao�ǉ�
void
MAINBOARD_SetShowOverscanBottom(
	Sint32	showOverscanBottom);

//Kitao�ǉ�
void
MAINBOARD_SetShowOverscanLeft(
	Sint32	showOverscanLeft);

//Kitao�ǉ�
void
MAINBOARD_SetShowOverscanRight(
	Sint32	showOverscanRight);

//Kitao�ǉ�
BOOL
MAINBOARD_GetFourSplitScreen();

//Kitao�ǉ�
BOOL
MAINBOARD_GetMonoColor();

//Kitao�ǉ�
Sint32
MAINBOARD_GetForceMonoColor();

//Kitao�ǉ�
void
MAINBOARD_SetForceMonoColor(
	Sint32	forceMonoColor);

//Kitao�ǉ�
Uint8*
MAINBOARD_GetpMainRam();

//Kitao�ǉ�
void
MAINBOARD_WriteROM(
	Uint32		mpr,
	Uint32		addr,
	Uint8		data);

//Kitao�ǉ�
void
MAINBOARD_SetContinuousWriteValue(
	BOOL		bContinuous,
	Uint32		mpr,
	Uint32		addr,
	Uint8		data);

//Kitao�ǉ�
BOOL
MAINBOARD_GetSystemCard();

//Kitao�ǉ��Bv2.63
Uint32
MAINBOARD_GetSysTime();

//Kitao�ǉ��Bv2.63
void
MAINBOARD_ResetSysTime();

//Kitao�ǉ��Bv2.70
BOOL
MAINBOARD_GetWorldStadium91();

//Kitao�ǉ��Bv2.70
BOOL
MAINBOARD_GetWorldStadium();

//Kitao�ǉ��Bv2.70
BOOL
MAINBOARD_GetPowerLeague34593();

//Kitao�ǉ��Bv2.70
BOOL
MAINBOARD_GetPowerLeague2();

//Kitao�ǉ��Bv2.70
BOOL
MAINBOARD_GetNaxatStadium();

//Kitao�ǉ��Bv2.70
BOOL
MAINBOARD_GetKoregaPro();

//Kitao�ǉ��Bv2.77
BOOL
MAINBOARD_GetUpdateFullScreen();


#endif /* MAIN_BOARD_H */
