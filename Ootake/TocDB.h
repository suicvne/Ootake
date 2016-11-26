/*-----------------------------------------------------------------------------
	[TocDB.h]

	Copyright (C) 2004 Ki

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
-----------------------------------------------------------------------------*/
#ifndef TOC_DB_H_INCLUDED
#define TOC_DB_H_INCLUDED

#include "TypeDefs.h"

typedef struct
{
	Uint8	trackNum;
	Uint8	isAudio;
	Uint8	min;
	Uint8	sec;
	Uint8	frame;
	Uint8	lbaH;
	Uint8	lbaM;
	Uint8	lbaL;
} TOCINFO;

typedef struct
{
	char*		pTitle;
	TOCINFO		TOC[100+1]; //Kitao�X�V�B�R�Y�~�b�N�t�@���^�W�[��100�g���b�N��(���[�h�A�E�g)�����݂���̂�101���K�v�Bv2.07
} DISCINFO;


const DISCINFO*
TOCDB_IsMatch(
	const DISCINFO*	pDisc);


//Kitao�ǉ�
void
TOCDB_ClearGameTitle();


//Kitao�ǉ�
char*
TOCDB_GetGameTitle();


#endif		/* TOC_DB_H_INCLUDED */
