/******************************************************************************
Ootake

 [Debug.h]
	�f�o�b�O�p�E�B���h�E�̕\���B�f�B�X�A�Z���u���Ȃǂ��s���B

Copyright(C)2006-2007 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

******************************************************************************/
#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include "TypeDefs.h"
#include <windows.h>


BOOL
DEBUG_Init(
	HINSTANCE	hInstance);

void
DEBUG_Deinit();

const HWND
DEBUG_GetHwnd();

void
DEBUG_SetPause(
	BOOL	pause);

BOOL
DEBUG_GetPause();

BOOL
DEBUG_GetPauseLong();


#endif /* DEBUG_H_INCLUDED */
