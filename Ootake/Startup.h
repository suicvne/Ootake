/******************************************************************************
Ootake

 [Srartup.h]
	�X�^�[�g���̃��b�Z�[�W�\����CD-ROM�EHu�J�[�h�̑I��

Copyright(C)2006 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

******************************************************************************/
#ifndef STARTUP_H_INCLUDED
#define STARTUP_H_INCLUDED

#include "TypeDefs.h"
#include <windows.h>


BOOL
STARTUP_Init(
	HINSTANCE	hInstance,
	Sint32*		CDorHu);

void
STARTUP_Deinit();

HWND
STARTUP_GetHwnd();


#endif /* STARTUP_H_INCLUDED */
