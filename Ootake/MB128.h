/*-----------------------------------------------------------------------------
	[MB128.h]
		Memory Base 128 �݊����f�B�A�̎����ɕK�v�Ȓ�`��錾���s�Ȃ��܂��B

	Copyright (C) 2004 Ki

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
**---------------------------------------------------------------------------*/
#ifndef MB128_H_INCLUDED
#define MB128_H_INCLUDED

#include <stdio.h>
#include "TypeDefs.h"


#define MB128_FILENAME		"MB128.dat"


void
MB128_Init();


//Kitao�ǉ�
BOOL
MB128_LoadFile();


//Kitao�X�V
BOOL
MB128_SaveFile();


void
MB128_Connect(
	BOOL		bConnect);

BOOL
MB128_IsConnected();


BOOL
MB128_IsActive();


Uint8
MB128_Read();


void
MB128_Write(
	Uint8		data);


/*-----------------------------------------------------------------------------
	[SaveState]
		��Ԃ��t�@�C���ɕۑ����܂��B 
-----------------------------------------------------------------------------*/
BOOL
MB128_SaveState(
	FILE*		p);


/*-----------------------------------------------------------------------------
	[LoadState]
		��Ԃ��t�@�C������ǂݍ��݂܂��B 
-----------------------------------------------------------------------------*/
BOOL
MB128_LoadState(
	FILE*		p);


#endif /* MB128_H_INCLUDED */
