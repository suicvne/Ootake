/******************************************************************************
Ootake

	[AudioOutX.h]
		XAudio2�ɂ��I�[�f�B�I�C���^�t�F�C�X���`���܂��D

Copyright(C)2006-2013 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

******************************************************************************/
#ifndef AUDIO_OUTX_H_INCLUDED
#define AUDIO_OUTX_H_INCLUDED

#include "TypeDefs.h"

#define AOUTX_BUFFERRATE 2	//�Q�Ԃ�̃o�b�t�@��p�ӁBXAudio2�ɔC���镔���������̂�4�łȂ�2�ŉ�����OK�Bv2.70


BOOL
AOUTX_Init(
	Sint32		soundType,
	Uint32		bufSize,
	Uint32		sampleRate,
	void		(*pCallBack)(int ch, Sint16* pBuf, Sint32 nSamples));

void
AOUTX_Play(
	BOOL		bPlay);

void
AOUTX_Deinit();

void
AOUTX_SetPlayStart();

BOOL
AOUTX_GetPlay();

//Kitao�ǉ�
BOOL
AOUTX_GetThreadStarted();


#endif // AUDIO_OUTX_H_INCLUDED
