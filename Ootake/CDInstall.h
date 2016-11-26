/******************************************************************************
Ootake

 [CDInstall.h]
	CD�̃f�[�^���C���X�g�[�����邱�ƂŃA�N�Z�X�̍�������}��

Copyright(C)2006-2007 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

******************************************************************************/
#ifndef CDINSTALL_H_INCLUDED
#define CDINSTALL_H_INCLUDED

#include "TypeDefs.h"
#include <windows.h>


BOOL
CDINSTALL_Init(
	HINSTANCE		hInstance,
	BOOL			bFullInstall);

void
CDINSTALL_Deinit();

Sint32
CDINSTALL_GetResult();


#endif /* CDINSTALL_H_INCLUDED */
