/******************************************************************************
Ootake

 [RecentRom.h]
	�ŋߋN�������Q�[���̈ꗗ��\�����邽�߂̃t�H�[��

Copyright(C)2006-2011 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

******************************************************************************/
#ifndef RECENT_H_INCLUDED
#define RECENT_H_INCLUDED

#include "TypeDefs.h"
#include <windows.h>


BOOL
RECENT_Init(
	HINSTANCE	hInstance,
	Sint32*		selectedrom);

void
RECENT_Deinit();


#endif /* RECENT_H_INCLUDED */
