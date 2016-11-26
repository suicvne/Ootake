/******************************************************************************
Ootake
�E���荞�݋֎~�w�߂������ꍇ�A���荞�ݗv�����L�����Z�������ɁA���荞�ݔ�������
  ���荞�݂������Ȃ������ɂ��āA�X�e�[�^�X�̓Z�b�g���ꂽ�܂܂ɂ���悤�ɂ����B

Copyright(C)2006 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[IntCtrl.c]
		�����݃R���g���[�����������܂��D

	Implements the interrupt controller.

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
#include <stdio.h>
#include "IntCtrl.h"
#include "CPU.h"
#include "Printf.h"


static Uint8	_IntDisable;
static Uint8	_IntStatus;


/*
	[DEV NOTE]

	�b�o�t�� IntCtrl �� $1403 �ɏ������ݓ�����s�Ȃ����u�Ԃ�
	TIRQ �̃��N�G�X�g�͎�艺������B

	�b�o�t�� $FF:0000 (VDC) ����ǂݏo�����s�Ȃ����u�Ԃ�
	IRQ1 �̃��N�G�X�g�͎�艺������B

	��̂Q�̓�����b�o�t���s�Ȃ킸�A
	IntCtrl �� disable �t���O���[���ŁA
	���� �b�o�t �̂h�t���O���[���̏ꍇ��
	���荞�݂�������������B
	�i���������荞�݂���������Ƃh�t���O�͂P�ɃZ�b�g�����j

	�b�o�t�� $1402 (���荞�݋֎~���W�X�^) �ɏ������݂��s�Ȃ����Ƃ��A
	IntCtrl �͎��̂R�̓�����s�Ȃ�Ȃ���΂Ȃ�Ȃ��F

	�P�D�������܂ꂽ�f�[�^��ۑ�����(���ʂR�r�b�g)
	�Q�D���̏������݂ɂ���ĐV���ɋ֎~���ꂽ�r�b�g�𒲂ׁA IRQ ����艺����
	�R�D���̏������݂ɂ���ĐV���ɋ����ꂽ�r�b�g�𒲂ׁA
		���Ӌ@�킩��̊��荞�ݗv���󋵂ɉ����� CPU �� IRQ ��v������

	[Kitao�X�V]
	�EIRQ1�̃��N�G�X�g�́AVDC�̃X�e�[�^�X��ǂݏo�����Ƃ������ł͂Ȃ�
	  ���荞�݂��s��ꂽ�Ɠ����Ƀ��N�G�X�g����艺������i�܂胊�N�G�X�g
	  �͂����P�񂾂��L���j����ɂ����B�����CLI���ߒ���̊��荞�݂�������
	  �ꍇ���A�W���b�L�[�`�F���̋N�������܂������悤�ɂȂ����B
	�E���荞�݋֎~�w�߂������ꍇ�A���荞�ݗv�����L�����Z�������ɁA���荞�ݔ���
	  ���Ɋ��荞�݂������Ȃ������ɂ��āA�X�e�[�^�X�̓Z�b�g���ꂽ�܂܂ɂ���悤
	  �ɂ����B
*/


/*-----------------------------------------------------------------------------
** [INTCTRL_Request]
**   �����ݗv���X�e�[�^�X���Z�b�g���܂��D
**---------------------------------------------------------------------------*/
//Kitao�X�V�B���荞�݋֎~���ɂ��X�e�[�^�X���Z�b�g�����悤�ɂ����B
void
INTCTRL_Request(
	Uint8		request)
{
	if (request & INTCTRL_IRQ2)
	{
		_IntStatus |= INTCTRL_IRQ2;
		CPU_ActivateIRQ2();
	}

	if (request & INTCTRL_IRQ1)
	{
		_IntStatus |= INTCTRL_IRQ1;
		CPU_ActivateIRQ1();
	}

	if (request & INTCTRL_TIRQ)
	{
		_IntStatus |= INTCTRL_TIRQ;
		CPU_ActivateTIMER();
	}
}


/*-----------------------------------------------------------------------------
** [INTCTRL_Cancel]
**   �����ݗv���X�e�[�^�X�����Z�b�g���܂��D
**---------------------------------------------------------------------------*/
void
INTCTRL_Cancel(
	Uint8		request)
{
	if (request & INTCTRL_IRQ2)
	{
		_IntStatus &= ~INTCTRL_IRQ2;
		CPU_InactivateIRQ2();
	}

	if (request & INTCTRL_IRQ1)
	{
		_IntStatus &= ~INTCTRL_IRQ1;
		CPU_InactivateIRQ1();
	}

	if (request & INTCTRL_TIRQ)
	{
		_IntStatus &= ~INTCTRL_TIRQ;
		CPU_InactivateTIMER();
	}
}


/*-----------------------------------------------------------------------------
** [INTCTRL_Init]
**   �����݃R���g���[�������������܂��D
**---------------------------------------------------------------------------*/
Sint32
INTCTRL_Init()
{
	_IntDisable = 0;
	CPU_SetIntDisable(_IntDisable); //Kitao�ǉ�
	_IntStatus = 0;

	return 0;
}


/*-----------------------------------------------------------------------------
** [INTCTRL_Deinit]
**   �����݃R���g���[���̏I���������s�Ȃ��܂��D
**---------------------------------------------------------------------------*/
void
INTCTRL_Deinit()
{
	_IntDisable = 0;
	CPU_SetIntDisable(_IntDisable); //Kitao�ǉ�
	_IntStatus = 0;
}


/*-----------------------------------------------------------------------------
** [INTCTRL_Read]
**   �����݃R���g���[������̓ǂݏo������ł��D
**---------------------------------------------------------------------------*/
Uint8
INTCTRL_Read(Uint32 regNum)
{
	switch (regNum & 3) //Kitao�X�V
	{
		case 2:
			return _IntDisable;

		case 3:
			return _IntStatus;
	}
	//(regNum & 3)��0��1�̏ꍇ
	return 0; //MainBoard.c ����Ă΂ꂽ�ꍇ�A���ۂɂ�Buffer�̒l�ƃ~�b�N�X���ꂽ�l���ǂݏo�����Bv1.62�L
}


/*-----------------------------------------------------------------------------
** [INTCTRL_Write]
**   �����݃R���g���[���ւ̏������ݓ���ł��D
**---------------------------------------------------------------------------*/
//Kitao�X�V
void
INTCTRL_Write(
	Uint32		regNum,
	Uint8		data)
{
	//PRINTF("IntCtrl Write = %X,%X", regNum,data); //Test�p

	switch (regNum & 3) //Kitao�X�V
	{
		case 2:
			_IntDisable = data & 7; //Kitao�X�V
			CPU_SetIntDisable(_IntDisable); //Kitao�ǉ�
			return;

		case 3:
			//PRINTF("IntCtrl Write = %X,%X", regNum,data); //Test�p
			INTCTRL_Cancel(INTCTRL_TIRQ);
			return;
	}
}


// save variable
#define SAVE_V(V)	if (fwrite(&V, sizeof(V), 1, p) != 1)	return FALSE
#define LOAD_V(V)	if (fread(&V, sizeof(V), 1, p) != 1)	return FALSE
/*-----------------------------------------------------------------------------
	[SaveState]
		��Ԃ��t�@�C���ɕۑ����܂��B 
-----------------------------------------------------------------------------*/
BOOL
INTCTRL_SaveState(
	FILE*		p)
{
	if (p == NULL)
		return FALSE;

	SAVE_V(_IntDisable);
	SAVE_V(_IntStatus);

	return TRUE;
}


/*-----------------------------------------------------------------------------
	[LoadState]
		��Ԃ��t�@�C������ǂݍ��݂܂��B 
-----------------------------------------------------------------------------*/
BOOL
INTCTRL_LoadState(
	FILE*		p)
{
	if (p == NULL)
		return FALSE;

	LOAD_V(_IntDisable);
	CPU_SetIntDisable(_IntDisable); //Kitao�ǉ�
	LOAD_V(_IntStatus);

	return TRUE;
}

#undef SAVE_V
#undef LOAD_V
