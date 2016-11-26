/******************************************************************************
Ootake

 [Resolution.h]
	�X�^�[�g���ɐݒ��ύX���邽�߂̃t�H�[���B���݂̓T�E���h�ݒ�̂�

Copyright(C)2006-2016 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

******************************************************************************/
#ifndef RESOLUTION_H_INCLUDED
#define RESOLUTION_H_INCLUDED

#include "TypeDefs.h"
#include <windows.h>


BOOL
RESOLUTION_Init(
	HINSTANCE	hInstance,
	Sint32		setNum,
	Sint32*		resolutionWidth,
	Sint32*		resolutionHeight);

void
RESOLUTION_Deinit();


#endif /* RESOLUTION_H_INCLUDED */
