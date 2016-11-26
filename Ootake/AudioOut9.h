/******************************************************************************
Ootake

	[AudioOut9.h]
		DirectSound9�ɂ��I�[�f�B�I�C���^�t�F�C�X���`���܂��D

Copyright(C)2006-2013 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

******************************************************************************/
#ifndef AUDIO_OUT9_H_INCLUDED
#define AUDIO_OUT9_H_INCLUDED

#include "TypeDefs.h"

#define AOUT9_BUFFERRATE 4	//�o�b�t�@��4�ɕ����Ď��B�������Ȃ��ق������̒x���͏��Ȃ��ςނ��A���������ق����������肵�������オ��Bv2.70�X�V


BOOL
AOUT9_Init(
	Sint32		soundType,
	Uint32		bufSize,
	Uint32		sampleRate,
	void		(*pCallBack)(int ch, Sint16* pBuf, Sint32 nSamples));

void
AOUT9_Play(
	BOOL		bPlay);

void
AOUT9_Deinit();

//Kitao�ǉ�
void
AOUT9_SetPlayStart();

//Kitao�ǉ�
BOOL
AOUT9_GetPlay();

//Kitao�ǉ�
BOOL
AOUT9_GetThreadStarted();


#endif // AUDIO_OUT9_H_INCLUDED
