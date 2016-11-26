/******************************************************************************
	[AudioOut.h]
		�I�[�f�B�I�C���^�t�F�C�X���`���܂��D

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
******************************************************************************/
#ifndef AUDIO_OUT_H_INCLUDED
#define AUDIO_OUT_H_INCLUDED

#include "TypeDefs.h"

#define AOUT_BUFFERRATE 4	//Kitao�ǉ��B�o�b�t�@��4�ɕ����Ď��B�������Ȃ��ق������̒x���͏��Ȃ��ςނ��A���������ق����������肵�������オ��Bv2.70�X�V


BOOL
AOUT_Init(
	Sint32		soundType,	//Kitao�ǉ�
	Uint32		bufSize,	// in samples 
	Uint32		sampleRate,
	void		(*pCallBack)(int ch, Sint16* pBuf, Sint32 nSamples)); //Kitao�X�V�Bch(�`�����l���i���o�[)��ǉ�

void
AOUT_Play(
	BOOL		bPlay);

void
AOUT_Deinit();

//Kitao�ǉ�
void
AOUT_SetPlayStart();

//Kitao�ǉ�
BOOL
AOUT_GetPlay();

//Kitao�ǉ�
BOOL
AOUT_GetThreadStarted();

//Kitao�ǉ�
void
AOUT_SetFpOutputWAV(
	FILE*	fp,
	Sint32	mode);

//Kitao�ǉ�
FILE*
AOUT_GetFpOutputWAV();

//Kitao�ǉ�
void
AOUT_SetOutputWavFileSize(
	DWORD	size);

//Kitao�ǉ�
DWORD
AOUT_GetOutputWavFileSize();

//Kitao�ǉ�
Sint32
AOUT_GetOutputWavWaitFinish();

//Kitao�ǉ�
FILE*
AOUT_GetfpOutputWAV();

//WAV�o�͎��s�����BAudioOutX,AudioOut9������g�p�Bv2.70
void
AOUT_OutputWavExecute(
	DWORD		dwBufSize,						
	Sint16*		pAudioBuf1,
	Sint16*		pAudioBuf2,
	Sint16*		pAudioBuf3);

//Kitao�ǉ��Bv2.70
void
AOUT_InitWavMixBuf(
	DWORD		dwBufSize);

//Kitao�ǉ��Bv2.70
void
AOUT_DeinitWavMixBuf();


#endif // AUDIO_OUT_H_INCLUDED
