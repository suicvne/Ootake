/******************************************************************************
Ootake
�E�X�N���[����ɂ����b�Z�[�W�̕\�����ł���悤�ɂ����Bv0.64

Copyright(C)2006-2009 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[Printf.c]

		Implements a printf function which displays a text on the
	main window's title bar.

	Copyright (C) 2005 Ki

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
******************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdarg.h>
#include "Printf.h"
#include "WinMain.h"
#include "Screen.h"
#include "App.h"
#include "MainBoard.h"


static char						_MessageBuffer[2048];
static Uint32					_MessageTime = 60*8; //�\������(�P�ʂ̓t���[��)�BKitao�ǉ��Bv1.58
static Uint32					_MessageTimeSaveLoad = 60*6; //�X�e�[�g�Z�[�u�ƃ��[�h���̕\�����ԁB���̃��b�Z�[�W��菭���Z�߂ɂ���Bv1.58
static BOOL						_bSaveLoadMessage = FALSE; //��"PRINTF��������"�ɁA�X�e�[�g�Z�[�u�ƃ��[�h���̏ꍇTRUE�ɐݒ肷��Bv1.58
static Uint32					_FrameCount = 0; //���b�Z�[�W�\������1�ȏ�ɂȂ�B��\������0�Œ�Ƃ���Bv2.54�X�V


/*----------------------------------------------------------------------------
	[PRINTF]
		Displays a text message for several seconds.
----------------------------------------------------------------------------*/
void
PRINTF(
	const char*		pMessage, ...)
{
	va_list			ap;

	va_start(ap, pMessage);
	vsprintf(_MessageBuffer, pMessage, ap);
	va_end(ap);

	while (strchr(_MessageBuffer, '\n'))
		*strchr(_MessageBuffer, '\n') = '\0';

	//puts(_MessageBuffer);
	//Kitao�ǉ��B�X�N���[����ւ̃��b�Z�[�W�\�����\�ɁB
	if (APP_GetFullScreen())
	{
		if (!APP_GetFullHideMessage())
			SCREEN_SetMessageText(_MessageBuffer);
	}
	else
	{
		if (APP_GetHideMessage())
			WINMAIN_SetCaption(_MessageBuffer);
		else
			SCREEN_SetMessageText(_MessageBuffer);
	}
	_FrameCount = 1;
	_bSaveLoadMessage = FALSE; //v1.58�ǉ�
}


void
PRINTF_Update()
{
	Uint32	mt;

	if (_FrameCount > 0) //���b�Z�[�W�\�����Ȃ�Bv2.54�ǉ�
	{
		if (_bSaveLoadMessage) //v1.58�ǉ�
			mt = _MessageTimeSaveLoad;
		else
			mt = _MessageTime;
		switch (MAINBOARD_GetFastForwarding()) //���񂵂��s���Ă���ꍇ�A����ɍ��킹�ăt���[�����𑝂₷�Bv2.38
		{
			case   10: mt = (Uint32)((double)mt * 1.10); break;
			case    5: mt = (Uint32)((double)mt * 1.20); break;
			case    3: mt = (Uint32)((double)mt * 1.33); break;
			case    2: mt = (Uint32)((double)mt * 1.50); break;
			case 1001: mt = (Uint32)((double)mt * 1.67); break;
			case 1000: mt = (Uint32)((double)mt * 1.83); break;
			case 2010: mt = (Uint32)((double)mt * 0.90); break;
			case 2004: mt = (Uint32)((double)mt * 0.75); break;
			case 2002: mt = (Uint32)((double)mt * 0.50); break;
		}
		if (++_FrameCount > mt) //v1.58�ǉ��B���b�Z�[�W�\�����Ԃ�ύX�\�ɁB
		{
			if (MAINBOARD_GetPause())  //Kitao�ǉ��BPAUSE���̓��b�Z�[�W�������Ȃ��B
				--_FrameCount;
			else
			{	//���b�Z�[�W����
				WINMAIN_SetCaption(NULL);
				SCREEN_SetMessageText(""); //Kitao�ǉ�
				_FrameCount = 0;
			}
		}
	}
}


BOOL
PRINTF_Init()
{
	SCREEN_SetMessageText(""); //Kitao�ǉ�
	_FrameCount = 0;
	return TRUE;
}


void
PRINTF_Deinit()
{
	SCREEN_SetMessageText(""); //Kitao�ǉ�
	_FrameCount = 0;
}


//Kitao�ǉ��B"PRINTF��������"�ɂ������ĂԂƁA���b�Z�[�W�̕\�����Ԃ�ʏ���Z���ł���Bv1.58
void
PRINTF_SetSaveLoadMessage()
{
	_bSaveLoadMessage = TRUE;
}

