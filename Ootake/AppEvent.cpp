/******************************************************************************
Ootake
Copyright(C)2006-2016 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[AppEvent.c]

	Copyright (C) 2004 Ki

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
#include <string.h>
#include <windows.h>
#include "AppEvent.h"

/*
	���������ɋN����C�x���g�ɂ��Ă͍��̂Ƃ���l�����Ȃ��B
	EXIT �C�x���g�͑��̑S�ẴC�x���g�����D�悷��B
*/

static char					_GameFileName[MAX_PATH+1];

static Sint32				_CurrentEvent = APPEVENT_NONE;
static BOOL					_bNoEvent;

static Uint32				_LongArg;

static BOOL					_bInit = FALSE;


BOOL
APPEVENT_Init()
{
	_CurrentEvent = APPEVENT_NONE;

	_bInit = TRUE;
	_bNoEvent = TRUE;

	return TRUE;
}


BOOL
APPEVENT_Deinit()
{
	_bInit = FALSE;
	_CurrentEvent = APPEVENT_NONE;

	return TRUE;
}


BOOL
APPEVENT_Set(
	const Sint32	event,
	const void*		pParam)
{
	if (!_bInit)
		return FALSE;

	// EXIT �C�x���g���󂯎�����ꍇ�͑��̃C�x���g���󂯕t���Ȃ��B 
	if (_CurrentEvent == APPEVENT_EXIT)
		return FALSE;

	if (!_bNoEvent)
		return FALSE;

	_CurrentEvent = event;

	// �p�����[�^���󂯎��K�v������C�x���g������������ 
	switch (_CurrentEvent)
	{
		case APPEVENT_OPENGAME:
			if (pParam == NULL) return FALSE;
			strcpy(_GameFileName, (char*)pParam);
			break;

		default:
			return FALSE;
	}

	_bNoEvent = FALSE;

	return TRUE;
}

const Sint32
APPEVENT_GetEventID()
{
	MSG		msg;

	if (!_bInit)
		return APPEVENT_NONE;

	// ���b�Z�[�W���[�v 
	if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		if (!GetMessage(&msg, NULL, 0, 0))
		{
			_CurrentEvent = APPEVENT_EXIT;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return _CurrentEvent;
}


const void*
APPEVENT_GetParam(
	const Sint32	event)
{
	if (!_bInit)
		return NULL;

	if (_bNoEvent)
		return NULL;

	switch (event)
	{
		case APPEVENT_OPENGAME:
			return (const void*)_GameFileName;

		case APPEVENT_SHOWMENU:
			return (const void*)_LongArg;

		default:
			return NULL;
	}

	return NULL;
}


void
APPEVENT_Ack()
{
	if (_bInit)
	{
		// EXIT �C�x���g�� Deinit ����܂ŏ����Ȃ� 
		if (_CurrentEvent != APPEVENT_EXIT)
		{
			_CurrentEvent = APPEVENT_NONE;
			_bNoEvent = TRUE;
		}
	}
}

