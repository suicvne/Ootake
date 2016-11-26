/******************************************************************************
Ootake

 [Option.h]
	�X�^�[�g���ɐݒ��ύX���邽�߂̃t�H�[��

Copyright(C)2006-2016 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

******************************************************************************/
#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED

#include "TypeDefs.h"
#include <windows.h>


BOOL
OPTION_Init(
	HINSTANCE	hInstance,
	Sint32*		screenType,
	Sint32*		drawMode,
	Sint32*		soundBuffer);

void
OPTION_Deinit();

HWND
OPTION_GetHWnd();


#endif /* OPTION_H_INCLUDED */
