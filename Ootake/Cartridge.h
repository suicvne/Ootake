/*-----------------------------------------------------------------------------
	[Cartridge.h]
		�J�[�g���b�W�̓ǂݍ��ݓ��ɕK�v�Ȑ錾���s�Ȃ��܂��D

	Copyright (C) 2004 Ki

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
-----------------------------------------------------------------------------*/
#ifndef CARTRIDGE_H_INCLUDED
#define CARTRIDGE_H_INCLUDED

#include "TypeDefs.h"


/*-----------------------------------------------------------------------------
** �֐��̃v���g�^�C�v�錾���s�Ȃ��܂��D
**---------------------------------------------------------------------------*/
Uint32
CART_LoadCartridge(
	const char*		pGameName,
	Uint8**			ppRom,
	Uint32*			pRomSize); //Kitao�X�V�BROM�̗e�ʃT�C�Y���ݒ肳���悤�ɂ����B

void
CART_FreeCartridge(
	Uint8*		pRom);


#endif		/* CARTRIDGE_H_INCLUDED */
