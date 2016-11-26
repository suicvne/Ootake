/******************************************************************************
Ootake
�E�Q�[�����Ƃɕʂ̃t�@�C�����ŕۑ�����悤�ɂ����B
�E�X�e�[�g�Z�[�u���Ƀ������x�[�X128�̓��e���Z�[�u����悤�ɂ����B
�E����������V���v���������B�M���̖�]�S���łŃZ�[�u���񏉊�������Ƀp�b�h����
  ���Ȃ��Ȃ��������B
�E�A�h���X�̃u���b�N�P�ʂ�128�o�C�g�ɁBtori���񂩂�������������܂����B��
  �ɐM���̖�]�S���łŃZ�[�u�\�ɂȂ����B���̑��̑Ή��\�t�g��OK�Bv1.53

Copyright(C)2006-2009 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[MB128.c]
		Memory Base 128 �݊����f�B�A���������܂��B

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
#include "MB128.h"
#include "App.h"
#include "Printf.h"

static Uint8	_MB128[0x20000];		/* 128KB */
static Uint8	_FirstMB128[0x20000];	//Kitao�ǉ��B�ύX�����������ǂ����𒲂ׂ邽�߂̑ޔ�p�B

static BOOL		_bMB128Connected = FALSE;

static Uint8	_PrevData   = 0;
static Uint32	_Addr       = 0;
static Uint8	_Data       = 0;
static Uint32	_Length     = 0;
static Uint32	_Mode       = 0;
static BOOL		_bActivated = FALSE;
static BOOL		_bReadMode  = FALSE;
static Uint32	_ReadCount = 0;
static Uint32	_WriteCount= 0;


//Kitao�X�V�B�������ɐ�O�B
void
MB128_Init()
{
	_PrevData  = 0;
	_Addr      = 0;
	_Data      = 0;
	_Length    = 0;
	_Mode      = 0;
	_bActivated = FALSE;
	_bReadMode = FALSE;
	_ReadCount = 0;
	_WriteCount= 0;

	memset(_MB128, 0, 0x2000);
	//Kitao�ǉ��B�������x�[�X128�̋N�����ŏ��̏�Ԃ�ޔ����Ă����B�I�����ɍX�V���ꂽ�`�Ղ��������Ƃ������A�������x�[�X128��ۑ�����悤�ɂ����B
	//           �������邱�ƂŁA�ԈႦ�ăX�e�[�g���[�h���Ă��܂������ł��A�����I������Ό��̃������x�[�X128�t�@�C���͎c���Ă����B
	memcpy(&_FirstMB128, &_MB128, 0x20000);
}


//Kitao�ǉ�
BOOL
MB128_LoadFile()
{
	FILE*	pMB128;
	char	filePathName[MAX_PATH+1];

	strcpy(filePathName, APP_GetAppPath());
	strcat(filePathName, "mb128\\");//mb128�t�H���_�ɕۑ�����悤�ɂ���
	strcat(filePathName, APP_GetGameFileNameBuf());
	strcat(filePathName, "_mb128.dat");

	pMB128 = fopen(filePathName, "rb");

	if (pMB128)
	{
		if (fread(_MB128, sizeof(_MB128), 1, pMB128) != 1)
			puts("MB128_Init: Can't read file - creating a blank media.");
		fclose(pMB128);
	}
	else
	{
		memset(_MB128, 0, 0x20000);
		puts("MB128_Init: Can't open file - creating a blank media.");
	}

	//Kitao�ǉ��B�������x�[�X128�̋N�����ŏ��̏�Ԃ�ޔ����Ă����B�I�����ɍX�V���ꂽ�`�Ղ��������Ƃ������A�������x�[�X128��ۑ�����悤�ɂ����B
	//           �������邱�ƂŁA�ԈႦ�ăX�e�[�g���[�h���Ă��܂������ł��A�����I������Ό��̃������x�[�X128�t�@�C���͎c���Ă����B
	memcpy(&_FirstMB128, &_MB128, 0x20000);

	return TRUE;
}


//Kitao�X�V�BDeinit��SaveFile�ɕύX�B�Q�[�����ƂɕʁX�̃t�@�C�����ŕۑ�����悤�ɂ����B
BOOL
MB128_SaveFile()
{
	FILE*	pMB128;
	char	filePathName[MAX_PATH+1];

	strcpy(filePathName, APP_GetAppPath());
	strcat(filePathName, "mb128");//mb128�t�H���_�ɕۑ�����悤�ɂ���
	CreateDirectory(filePathName, NULL);//mb128�f�B���N�g�����Ȃ��ꍇ���
	strcat(filePathName, "\\");
	strcat(filePathName, APP_GetGameFileNameBuf());
	strcat(filePathName, "_mb128.dat");

	//Kitao�ǉ��B�o�b�N�A�b�v�������X�V���ꂽ�`�Ղ��������Ƃ������A�o�b�N�A�b�v������ۑ�����悤�ɂ����B
	//           �������邱�ƂŁA�ԈႦ�ăX�e�[�g���[�h���Ă��܂������ł��A�����I������Ό��̃o�b�N�A�b�v�����t�@�C���͎c���Ă����B���o�b�N�A�b�v�̕K�v�̂Ȃ��Q�[���̓t�@�C�����s�v�ɂȂ�B
	if (memcmp(&_MB128, &_FirstMB128, 0x20000) != 0) //�X�V����Ă����
	{
		pMB128 = fopen(filePathName, "wb");

		if (pMB128)
		{
			if (fwrite(_MB128, sizeof(_MB128), 1, pMB128) != 1)
				puts("MB128_Deinit: Can't write file - contents discarded.");
			fclose(pMB128);
			
			//Kitao�ǉ��B�������x�[�X128�̍X�V����̏�Ԃ�ޔ����Ă����B����X�V���ꂽ�`�Ղ��������Ƃ������A�������x�[�X128��ۑ��B
			memcpy(&_FirstMB128, &_MB128, 0x20000);
		}
		else
			puts("MB128_Deinit: Can't open file - contents discarded.");
	}

	return TRUE;
}


void
MB128_Connect(
	BOOL		bConnect)
{
	_bMB128Connected = bConnect;
}


BOOL
MB128_IsConnected()
{
	return _bMB128Connected;
}


BOOL
MB128_IsActive()
{
	return _bActivated;
}


Uint8
MB128_Read()
{
	Uint8	ret;

	if (!_bMB128Connected)
		return 0;

	switch (_Mode)
	{
		case 2:
			return 0;
		case 3:
			return 4;
		case 6: /* data read mode */
			if ((_PrevData & 2) && _bReadMode)
			{
				ret = ((_MB128[(_Addr*128+_ReadCount/8) & 0x1FFFF]) >> (_ReadCount&7)) & 1; //v1.53�X�V�Btori���񂩂�������������܂����B���肪�Ƃ��������܂��B
				if (++_ReadCount == _Length)
				{
					_bReadMode = FALSE;
					_ReadCount = 0;
					_WriteCount = 0;
					_Mode = 0;
					_Length = 0;
					_bActivated = FALSE;
				}
				return ret;
			}
		case 7: //Kitao�ǉ��B�M���̖�]�S���łőS�̏���������Ƀp�b�h�������Ȃ��Ȃ��������B
			_bReadMode = FALSE; //_bReadMode���N���A�ɁB
			_Mode = 0;
			_bActivated = FALSE;
			return 0;
	}

	return 0;
}


void
MB128_Write(
	Uint8		data)
{
	static Uint32	addrCount = 10;
	static Uint32	lenCount  = 20;
	static Uint8	writeBuffer = 0;

	if (!_bMB128Connected)
		return;

	if (!(_PrevData & 2) && (data & 2))
	{
		switch (_Mode)
		{
			case 0:
				_Data >>= 1;
				_Data |= (data & 1) << 7;
				if (_Data == 0xA8)
				{
					_bActivated = TRUE;
					++_Mode;
				}
				break;

			case 1:
				if ((data & 1) == 0)
					++_Mode;
				break;

			case 2:
				if ((data & 1) == 1)
					++_Mode;
				break;

			case 3:
				_bReadMode = data & 1;
				++_Mode;
				_Addr = 0;
				break;

			case 4: /* addr set mode */
				_Addr >>= 1;
				_Addr |= (data & 1) << 9;
				if (--addrCount == 0)
				{
					++_Mode;
					addrCount = 10;
					_Length = 0;
				}
				break;

			case 5:	/* length set mode */
				_Length >>= 1;
				_Length |= (data & 1) << 19;
				if (--lenCount == 0)
				{
					++_Mode;
					_WriteCount = 0;
					_ReadCount = 0;
					lenCount = 20;
				}
				break;

			case 6: /* data write mode */
				if (_bReadMode)	break;
				
				writeBuffer >>= 1;
				writeBuffer |= (data & 1) << 7;
				if ((_WriteCount & 7) == 7)
					_MB128[(_Addr*128+_WriteCount/8) & 0x1FFFF] = writeBuffer; //v1.53�X�V�Btori���񂩂�������������܂����B���肪�Ƃ��������܂��B
				if (++_WriteCount == _Length)
				{
					++_Mode;
					_WriteCount = 0;
					_ReadCount = 0;
					writeBuffer = 0;
					_Length = 0;
				}
				break;

			//case 7: //v1.53�J�b�g�B�Q�l�F������_Mode��0�ɂ���Ɛ^���_�]���ŃZ�[�u�⏉������Ƀp�b�h�������Ȃ��Ȃ�B
			//	break;
		}
	}

	_PrevData = data;
}


// save variable
#define SAVE_V(V)	if (fwrite(&V, sizeof(V), 1, p) != 1)	return FALSE
#define LOAD_V(V)	if (fread(&V, sizeof(V), 1, p) != 1)	return FALSE
// save array
#define SAVE_P(P, N)	if (fwrite(P, N, 1, p) != 1)	return FALSE
#define LOAD_P(P, N)	if (fread(P, N, 1, p) != 1)		return FALSE
/*-----------------------------------------------------------------------------
	[SaveState]
		��Ԃ��t�@�C���ɕۑ����܂��B 
-----------------------------------------------------------------------------*/
BOOL
MB128_SaveState(
	FILE*		p)
{
	if (p == NULL)
		return FALSE;

	SAVE_P((Uint8*)_MB128, 0x20000); //Kitao�ǉ��B�������x�[�X�̓��e���X�e�[�g�Z�[�u����悤�ɂ����B

	SAVE_V(_bMB128Connected);
	SAVE_V(_PrevData);
	SAVE_V(_Addr);
	SAVE_V(_Data);
	SAVE_V(_Length);
	SAVE_V(_Mode);
	SAVE_V(_bActivated);
	SAVE_V(_bReadMode);

	SAVE_V(_ReadCount);
	SAVE_V(_WriteCount);

	return TRUE;
}


/*-----------------------------------------------------------------------------
	[LoadState]
		��Ԃ��t�@�C������ǂݍ��݂܂��B 
-----------------------------------------------------------------------------*/
BOOL
MB128_LoadState(
	FILE*		p)
{
	if (p == NULL)
		return FALSE;

	LOAD_P((Uint8*)_MB128, 0x20000); //Kitao�ǉ��B�������x�[�X�̓��e���X�e�[�g�Z�[�u����悤�ɂ����B
	//Kitao�ǉ��B�������x�[�X128�̋N�����ŏ��̏�Ԃ�ޔ����Ă����B�I�����ɍX�V���ꂽ�`�Ղ��������Ƃ������A�������x�[�X128��ۑ�����悤�ɂ����B
	//           �������邱�ƂŁA�ԈႦ�ăX�e�[�g���[�h���Ă��܂������ł��A�����I������Ό��̃������x�[�X128�t�@�C���͎c���Ă����B
	memcpy(&_FirstMB128, &_MB128, 0x20000);

	LOAD_V(_bMB128Connected);
	LOAD_V(_PrevData);
	LOAD_V(_Addr);
	LOAD_V(_Data);
	LOAD_V(_Length);
	LOAD_V(_Mode);
	LOAD_V(_bActivated);
	LOAD_V(_bReadMode);

	LOAD_V(_ReadCount);
	LOAD_V(_WriteCount);

	return TRUE;
}

#undef SAVE_V
#undef LOAD_V
#undef SAVE_P
#undef LOAD_P
