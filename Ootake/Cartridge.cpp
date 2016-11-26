/******************************************************************************
Ootake
�EROM�̗e�ʂ�Ԃ��悤�ɂ����B
�E�z�o���@�ɂ���Ă̓w�b�_���t���Ă��܂����̂�����悤�Ȃ̂ŁA�w�b�_�t���̃C��
  �[�W�t�@�C���ɂ��Ή������B

Copyright(C)2006 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[Cartridge.c]
		�J�[�g���b�W�̓ǂݍ��ݓ����s�Ȃ��܂��D

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
#include "Cartridge.h"


static BOOL
read_384k(
	FILE*		p,
	Uint8*		pRom,
	Sint32		headerSize)//Kitao�X�V
{
	/* mask �� 0xFFFFF �ɂȂ�̂ŁA$00000 - $FFFFF �����؂Ė��߂� */
	if (fread(pRom, sizeof(Uint8), 262144, p) != 262144)
		return FALSE;

	fseek(p, headerSize, SEEK_SET);//Kitao�X�V

	if (fread(pRom + 262144, sizeof(Uint8), 393216, p) != 393216)
		return FALSE;

	memcpy(pRom+262144+393216, pRom, 0x100000-(262144+393216));

	return TRUE;
}


/*-----------------------------------------------------------------------------
** [LoadCartridge]
**	 �J�[�g���b�W���t�@�C������ǂݍ��݂܂��D
** �J�[�g���b�W�ɕK�v�ȗ̈�̊m�ۂ��s�Ȃ��܂��D
** �ǂݍ��񂾃J�[�g���b�W�̃}�X�N�l��Ԃ��܂��D(�[���Ȃ玸�s)
**---------------------------------------------------------------------------*/
Uint32
CART_LoadCartridge(
	const char*		pGameName,
	Uint8**			ppRom,
	Uint32*			pRomSize) //Kitao�X�V�BROM�̗e�ʃT�C�Y���ݒ肳���悤�ɂ����B
{
	FILE*	pFile;
	Uint32	fileSize;
	Uint32	headerSize; //Kitao�ǉ�
	Uint32	mask;

	pFile = fopen(pGameName, "rb");
	
	if (pFile == NULL)
	{
		return 0;
	}

	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
	//Kitao�ǉ��B�z�o���@�ɂ���Ă̓w�b�_���t���Ă��܂����̂�����悤�Ȃ̂Ńw�b�_���������ꍇ�̓J�b�g�B
	headerSize = fileSize % 1024;
	if (headerSize != 0)
	{
		fseek(pFile, headerSize, SEEK_SET);
		fileSize -= headerSize;
	}
	else
		fseek(pFile, 0, SEEK_SET);
	*pRomSize = fileSize;

	// ROM MASK �̒l�����肷��B 
	// ROM �̃T�C�Y�� $6000 �Ȃǂ̏ꍇ
	// (�Q�ׂ̂���łȂ��ꍇ)���l������B 
	if (fileSize == 393216)
		mask = 1 << 20;
	else
	{
		mask = 0x2000;
		while (mask < fileSize)
			mask <<= 1;
	}

	// ���ۂɂ͂Q�ׂ̂���Ŋm�ۂ��� ($6000 �̏ꍇ�� $8000)
	*ppRom = (Uint8*)malloc(mask);
	if (*ppRom == NULL)
	{
		fclose(pFile);
		return 0;
	}
	memset(*ppRom, 0xFF, mask);
	--mask;	

	if (fileSize == 393216)
	{
		if (!read_384k(pFile, *ppRom, headerSize))
		{
			fclose(pFile);
			free(*ppRom);
			return 0;
		}
	}
	else if (fread(*ppRom, sizeof(Uint8), fileSize, pFile) != fileSize)
	{
		fclose(pFile);
		free(*ppRom);
		return 0;
	}

	fclose(pFile);

	return mask;
}


/*-----------------------------------------------------------------------------
** [FreeCartridge]
**	 �J�[�g���b�W��j�����܂��D
** �J�[�g���b�W�p�Ɋm�ۂ����̈��������܂��D
**---------------------------------------------------------------------------*/
void
CART_FreeCartridge(
	Uint8*		pRom)
{
	free(pRom);
}

