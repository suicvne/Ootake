/******************************************************************************
Ootake
Copyright(C)2006-2009 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[Config.c]

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
#include <malloc.h>
#include "Config.h"

#define		CONFIG_MAXITEM		128 //Kitao�X�V
#define		CONFIG_MAXLEN		256

typedef struct
{
	char		name[CONFIG_MAXLEN];
	char		value[CONFIG_MAXLEN];
} ConfigItem;

static ConfigItem		_Item[CONFIG_MAXITEM];
static Sint32			_nItem = 0;


/*-----------------------------------------------------------------------------
	[Init]
		�R���t�B�O�����������܂��B
-----------------------------------------------------------------------------*/
BOOL
CONFIG_Init()
{
	// �������A���P�[�g�^�ɂ���Ƃ��͂����Ń��������m�ۂ��� 
	return TRUE;
}


/*-----------------------------------------------------------------------------
	[Load]
		�t�@�C������ݒ荀�ڂ�ǂݍ��݂܂��B
-----------------------------------------------------------------------------*/
BOOL
CONFIG_Load(
	const char*		pPathName)
{
	FILE*		in;
	Sint32		nItem;

	if ((in = fopen(pPathName, "rb")) == NULL)	return FALSE;

	if (fread(&nItem, sizeof(nItem), 1, in) != 1)
	{
		fclose(in);
		return TRUE;
	}

	fread(_Item, sizeof(ConfigItem), CONFIG_MAXITEM, in);
	fclose(in);

	_nItem = nItem;

	return TRUE;
}


/*-----------------------------------------------------------------------------
	[Save]
		�t�@�C���ɐݒ荀�ڂ��������݂܂��B
-----------------------------------------------------------------------------*/
BOOL
CONFIG_Save(
	const char*		pPathName)
{
	FILE*		out;
	if ((out = fopen(pPathName, "wb")) == NULL)	return FALSE;

	if (fwrite(&_nItem, sizeof(_nItem), 1, out) != 1)
	{
		fclose(out);
		return FALSE;
	}

	if (fwrite(_Item, sizeof(ConfigItem), _nItem, out) != _nItem)
	{
		fclose(out);
		return FALSE;
	}

	fclose(out);

	return TRUE;
}


/*-----------------------------------------------------------------------------
	[Deinit]
		�R���t�B�O���I�����܂��B
-----------------------------------------------------------------------------*/
BOOL
CONFIG_Deinit()
{
	_nItem = 0;

	// �������A���P�[�g�^�ɂ���Ƃ��͂����Ń�������������� 
	return TRUE;
}


/*-----------------------------------------------------------------------------
	[Set]
	  pName �Ŏw�肳���R���t�B�O��ݒ肵�܂��B
	�ݒ荀�ڂ̓��j�[�N�Ȗ��O�ƒl�ƒl�̃T�C�Y(�o�C�g��)�œo�^���܂��B
	���ږ� pName �����ɑ��݂����ꍇ�́A�l���㏑������܂��B
	�������o�^����ꍇ�� strlen(������)+1 �� valueSize �Ɏw�肵�܂��B
-----------------------------------------------------------------------------*/
BOOL
CONFIG_Set(
	const char*		pName,
	const void*		pValue,
	const Sint32	valueSize)
{
	int				i;

	// pName ���������ǂ����𒲂ׂ�B 
	for (i = 0; i < _nItem; i++)
	{
		if (strcmp(_Item[i].name, pName) == 0)
		{
			// �����Ȃ炻�̒l��ύX����B 
			if (valueSize > CONFIG_MAXLEN)
				return FALSE;

			memcpy(_Item[i].value, pValue, valueSize);
			return TRUE;
		}
	}

	// �܂��Ȃ��ݒ荀�ڂȂ�V�K�ɒǉ�����B 
	if (_nItem >= CONFIG_MAXITEM)
		return FALSE;

	if (strlen(pName) + 1 > CONFIG_MAXLEN)
		return FALSE;

	if (valueSize > CONFIG_MAXLEN)
		return FALSE;

	strcpy(_Item[_nItem].name, pName);
	memcpy(_Item[_nItem].value, pValue, valueSize);
	++_nItem;

	return TRUE;
}


/*-----------------------------------------------------------------------------
	[Get]
	  pName �Ŏw�肳�ꂽ�ݒ荀�ڂ̒l��Ԃ��܂��B
-----------------------------------------------------------------------------*/
BOOL
CONFIG_Get(
	const char*		pName,
	      void*		pValue,
	const Sint32	valueSize)
{
	int				i;

	for (i = 0; i < _nItem; i++)
	{
		if (strcmp(_Item[i].name, pName) == 0)
		{
			// �ݒ荀�ڂ��݂������炻�̒l���R�s�[����B 
			memcpy(pValue, _Item[i].value, valueSize);
			return TRUE;
		}
	}

	return FALSE;
}

