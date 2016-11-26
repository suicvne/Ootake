/*-----------------------------------------------------------------------------
	[PSG.h]
		�o�r�f���L�q����̂ɕK�v�Ȓ�`����ъ֐��̃v���g�^�C�v�錾���s�Ȃ��܂��D

	Copyright (C) 2004 Ki

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**---------------------------------------------------------------------------*/
#ifndef PSG_H_INCLUDED
#define PSG_H_INCLUDED

#include <stdio.h>
#include "TypeDefs.h"

#define PSG_FRQ		3579545.0


/*-----------------------------------------------------------------------------
** �֐��̃v���g�^�C�v�錾���s�Ȃ��܂��D
**---------------------------------------------------------------------------*/
Sint32
PSG_Init(
	Sint32		sampleRate);

void
PSG_Deinit();

void
PSG_Mix(
	Sint16*		pDst,				// �o�͐�o�b�t�@ 
	Sint32		nSample);			// �����o���T���v���� 

void
PSG_SetSampleRate(
	Uint32		sampleRate);

void
PSGDEBUG_ShowRegs();

Uint8
PSG_Read(Uint32 regNum);

void
PSG_Write(
	Uint32		regNum,
	Uint8		data);

Sint32
PSG_AdvanceClock(Sint32 clock);

BOOL
PSG_SaveState(
	FILE*		p);

BOOL
PSG_LoadState(
	FILE*		p);

//Kitao�ǉ��BPSG�̃{�����[�����ʂɐݒ�\�ɂ����B
void
PSG_SetVolume(
	Uint32		volume);		// 0 - 65535

//Kitao�ǉ��B�{�����[���~���[�g�A�n�[�t�Ȃǂ��ł���悤�ɂ����B
void
PSG_SetVolumeEffect(
	Uint32 volumeEffect);

//Kitao�ǉ�
void
PSG_ResetVolumeReg();

//Kitao�ǉ�
void
PSG_SetMutePsgChannel(
	Sint32	num,
	BOOL	bMute);

//Kitao�ǉ�
BOOL
PSG_GetMutePsgChannel(
	Sint32	num);

//Kitao�ǉ��Bv2.60
void
PSG_SetHoneyInTheSky(
	BOOL	bHoneyInTheSky);


#endif		/* PSG_H_INCLUDED */
