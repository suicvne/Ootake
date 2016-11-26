/*-----------------------------------------------------------------------------
	[CDROM.h]
		CD-ROM�h���C�u���L�q����̂ɕK�v�Ȓ�`�����
	�֐��̃v���g�^�C�v�錾���s�Ȃ��܂��D

	Copyright (C) 2004 Ki

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
**---------------------------------------------------------------------------*/
#ifndef CD_ROM_H_INCLUDED
#define CD_ROM_H_INCLUDED

#include "TypeDefs.h"

#define	CDROM_IRQ2		1


/*-----------------------------------------------------------------------------
** �֐��̃v���g�^�C�v�錾���s�Ȃ��܂��D
**---------------------------------------------------------------------------*/
Sint32
CDROM_Init();

void
CDROM_Deinit();

BOOL
CDROM_Reset();

Uint8
CDROM_Read(
	Uint32 regNum);

void
CDROM_Write(
	Uint32	regNum,
	Uint8	data);

BOOL
CDROM_IsCDROMEnabled();

BOOL
CDROM_IsBRAMEnabled();

void
CDROM_AdvanceClock();

void
CDROM_AdvanceFadeClock();

BOOL
CDROM_SaveState(
	FILE*	p);

BOOL
CDROM_LoadState(
	FILE*	p);

//Kitao�ǉ�
void
CDROM_Stop(
	BOOL	bClearParameter);

//Kitao�ǉ�
BOOL
CDROM_CheckPaused();

//Kitao�ǉ�
BOOL
CDROM_CheckPlaying();

//Kitao�ǉ�
BOOL
CDROM_CheckInterrupt();

//Kitao�ǉ�
void
CDROM_Mix(
	Sint16*		pDst,
	Sint32		nSample);

//Kitao�ǉ�
void
CDROM_SetCdVolume(
	Sint32		volume);

//Kitao�ǉ�
void
CDROM_SetFastCD(
	BOOL fastCD);

//Kitao�ǉ�
BOOL
CDROM_GetFastCD();

//Kitao�ǉ�
void
CDROM_SetFastSeek(
	BOOL fastSeek);

//Kitao�ǉ�
BOOL
CDROM_GetFastSeek();

//Kitao�ǉ�
void
CDROM_SetVolumeEffect(
	Uint32 effectVolume);

//Kitao�ǉ�
void
CDROM_SetCDDAReadBufferSize();

//Kitao�ǉ�
void
CDROM_ResetCDAccessCount(
	BOOL	bReset);

//Kitao�ǉ�
void
CDROM_LoadPlayAudioTrack();

//Kitao�ǉ�
Sint32
CDROM_GetCDDAReadBufferSize();

//Kitao�ǉ�
Sint32
CDROM_GetReadByteCount();

//Kitao�ǉ�
Uint8
CDROM_Read1801();

//Kitao�ǉ�
void
CDROM_NoResetCDChange(
	int	dn);

//Kitao�ǉ�
void
CDROM_SetInstallFileName(
	int		track,
	char*	pFileName);

//Kitao�ǉ�
void
CDROM_SetInstallWavFileName(
	int		track,
	char*	pFileName);

//Kitao�ǉ�
void
CDROM_SetInstallCueFileName(
	char*	pFileName);

//Kitao�ǉ�
BOOL
CDROM_CDInstall(
	HWND	hWnd,
	BOOL	bFull);

//Kitao�ǉ�
void
CDROM_CDUninstall();

//Kitao�ǉ�
Sint32
CDROM_CheckCDInstall();

//Kitao�ǉ�
void
CDROM_SetInstallRequiredHDD(
	BOOL	bFull);

//Kitao�ǉ�
Sint32
CDROM_GetInstallRequiredHDD();

//Kitao�ǉ�
void
CDROM_SetPort(
	Uint32		n,
	Uint8		data);

//Kitao�ǉ�
Uint8
CDROM_GetPort(
	Uint32		n);

//Kitao�ǉ�
Sint32
CDROM_GetCDInstall();

//Kitao�ǉ�
void
CDROM_ClearCDDAAjustCount();

//Kitao�ǉ�
void
CDROM_UpdateCDInstall();

//Kitao�ǉ��Bv2.70
BOOL
CDROM_GetRomRomStadium();

//Kitao�ǉ��Bv2.70
BOOL
CDROM_GetBaseballer();


#endif		/* CD_ROM_H_INCLUDED */
