/******************************************************************************
Ootake

 [WriteMemory.h]
	���������e���������̃R�}���h����͂��邽�߂̃t�H�[��

Copyright(C)2006-2010 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

******************************************************************************/
#ifndef WRITEMEM_H_INCLUDED
#define WRITEMEM_H_INCLUDED

#include "TypeDefs.h"
#include <windows.h>


BOOL
WRITEMEM_Init(
	HWND		hWnd,
	HINSTANCE	hInstance,
	Uint32*		mpr,
	Uint32*		addr,
	Uint8*		data,
	BOOL*		bContinuous,
	Sint32*		setOk);

void
WRITEMEM_Deinit();

char*
WRITEMEM_GetCode();

void
WRITEMEM_ClearCode();


#endif /* WRITEMEM_H_INCLUDED */
