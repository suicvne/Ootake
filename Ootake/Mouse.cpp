/******************************************************************************
Ootake
�E�}�E�X��傫�����������Ƃ��͉�������悤�ɂ����B
�E�}�E�X�̃��Z�b�g�p�x�𑝂₵�āA����̒x�����ł�����茸�炵���B
�E�}�E�X�g�p���̂Ƃ��́A�uWindows�̃}�E�X�J�[�\���v����ɃG�~�����[�^�E�B���h�E
  �̐^�񒆂Ɉʒu�����ĉB���悤�ɂ����B
�E��ʂ̕\���{���ɂ���ă}�E�X�̊��x���œK�������B
�E���̓����̌��E��-128�ł͂Ȃ�-127�i���̌��E�Ɠ����l�j�ɂ����B
�E�}�E�X�z�C�[���̉�]����ŃZ���N�g�{�^��(���])�E�����{�^��(������])���@�\
  ������悤�ɂ����B�z�C�[��(�^�񒆃{�^��)���N���b�N���邱�Ƃł��A�����{�^����
  �@�\������悤�ɂ����B

Copyright(C)2006-2010 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[Mouse.c]
		�}�E�X���������܂��B

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
#define DIRECTINPUT_VERSION	0x0500	//Kitao�ǉ��B���ɂ���邩������Ȃ����ADirectInput5���y���B7���Ƃ��x������B�X�y�[�X�n���A�[���킩��₷���B

#include "Mouse.h"
#include "WinMain.h"
#include "Input.h"
#include "JoyPad.h"
#include "MainBoard.h" //Kitao�ǉ�


static Uint32	_ReadCount;
static Sint8	_DeltaX;
static Sint8	_DeltaY;
static Sint32	_PrevX;
static Sint32	_PrevY;
static BOOL		_bMoveX = TRUE; //Kitao�ǉ��Bv1.23
static BOOL		_bMsConnected = FALSE;
static Uint8	_ButtonState;
static Sint32	_ClockCounter;
static Uint32	_MouseWheelFlg = 0; //Kitao�ǉ��B�}�E�X�z�C�[���̉�]�ŃZ���N�g�E�����{�^���������ꂽ�ꍇ�A�Z���N�g�E�����{�^���𗣂������̂��߂ɕK�v�B


void
MOUSE_RButtonDown(
	BOOL		bDown)
{
	_ButtonState &= ~1;
	_ButtonState |= bDown;
}

void
MOUSE_LButtonDown(
	BOOL		bDown)
{
	_ButtonState &= ~2;
	_ButtonState |= bDown << 1;
}

void
MOUSE_SelButtonDown(
	BOOL		bDown)
{
	_ButtonState &= ~4;
	_ButtonState |= bDown << 2;
}

void
MOUSE_RunButtonDown(
	BOOL		bDown)
{
	_ButtonState &= ~8;
	_ButtonState |= bDown << 3;
}


void
MOUSE_Reset()
{
	if (_ClockCounter >= 7159090.0/60.0/16.0) //Kitao�X�V�B�x�������炷���߁A���Z�b�g�p�x�͌듮�삵�Ȃ��͈͂łł��邾�����������B
	{
		_ReadCount = 0;
		_ClockCounter = 0;
	}
}


//Kitao�ǉ��BVBlank���Ԃɍ��W���A�b�v�f�[�g����悤�ɂ����Bv1.23
void
MOUSE_UpdateDelta()
{
	int		mag; //Kitao�ǉ�
	RECT	rc; //Kitao�ǉ�
	POINT	p; //Kitao�ǉ�
	Sint32	dx;
	Sint32	dy;

	if (!_bMsConnected) return; //�������̂��߃}�E�X���Ȃ��ł��Ȃ��Ƃ��͏������Ȃ�

	//Kitao�ǉ��B��ʂ̕\���{���ɂ���Ċ��x���œK�������B
	mag = MAINBOARD_GetMagnification();
	GetCursorPos(&p);
	dx = _PrevX - p.x;
	dy = _PrevY - p.y;
	if ((dx % mag) != 0) //�}�E�X�������ł��������Ă����Ƃ��́A0�ɂ����Œ�Ԃ�̃J�[�\���𓮂����B
	{ 
		if (dx > 0)
			dx = (dx / mag) + 1; //�ړ��ʂ͏����_�ȉ���؂�グ��悤�ɂ����B"��������"�Ń}�E�X�J�[�\���̓�����������肪�����Bv2.39
		else
			dx = (dx / mag) - 1;
	}
	else
		dx = dx / mag;
	if ((dy % mag) != 0) //�}�E�X�������ł��������Ă����Ƃ��́A0�ɂ����Œ�Ԃ�̃J�[�\���𓮂����B
	{ 
		if (dy > 0)
			dy = (dy / mag) + 1; //�ړ��ʂ͏����_�ȉ���؂�グ��悤�ɂ����B"��������"�Ń}�E�X�J�[�\���̓�����������肪�����Bv2.39
		else
			dy = (dy / mag) - 1;
	}
	else
		dy = dy / mag;

	//Kitao�ǉ��B�傫�����������Ƃ��͉�������悤�ɂ����B
	if (dx >=  64)
	{
		dx += dx/2;
		if (dx >  127)	dx =  127;
	}
	if (dy >=  64)
	{
		dy += dy/2;
		if (dy >  127)	dy =  127;
	}
	if (dx <= -64)
	{
		dx -= dx/2;
		if (dx < -127)	dx = -127; //Kitao�X�V�B-128�܂ŋ����ƃ}�E�X��傫���񂵂��Ƃ��ɂ��񂾂񍶂Ɋ���Ă��銴������̂�-127�~�܂�ŁB
	}
	if (dy <= -64)
	{
		dy -= dy/2;
		if (dy < -127)	dy = -127; //Kitao�X�V
	}

	//Kitao�ǉ��B�΂߈ړ��̎��Ɉړ���1��Ԃ��ƁA"������"(7MHz)�ŉ�ʂ������̂ŁA���̏ꍇ�͏c���Q��ɕ����Ĉړ�������悤�ɂ����Bv1.23
	//			 ��������Ǝ΂߂̈ړ��X�s�[�h�������āA�ׂ����}�E�X�𓮂������Ƃ��ɔ����������₷���Ȃ��������ŁA��Γ񒹁B"�Ƃ��߂��������A��"�̃Q�[���V�[��(7MHz)�ł��A���������ق������삵�₷���B
	if (VDC_GetTvWidth() >= 336) //VDC�����N���b�N(7MHz�ȏ�)�œ����Ă���Ƃ������A���̃^�C�~���O��������������悤�ɂ����B���̏������Ȃ��ƁA"��������"(5MHz)�Ń}�E�X�J�[�\���̓����������B�����Ă��̃Q�[���ł͏������Ȃ��ق����������X���[�Y�Bv2.39�X�V
		if (((dx == -1)||(dx ==  1))&&((dy == -1)||(dy ==  1)))
		{
			if (_bMoveX)
			{
				dy = 0;
				_bMoveX = FALSE;
			}
			else
			{
				dx = 0;
				_bMoveX = TRUE;
			}
		}

	//Kitao�X�V�B�}�E�X�g�p���̂Ƃ��́A�uWindows�̃}�E�X�J�[�\���v����ɃG�~�����[�^�E�B���h�E�̐^�񒆂Ɉʒu������悤�ɂ����B
	GetWindowRect(WINMAIN_GetHwnd(), &rc);
	_PrevX = rc.left + (rc.right-rc.left)/2;
	_PrevY = rc.top + (rc.bottom-rc.top)/2;
	SetCursorPos(_PrevX, _PrevY);

	_DeltaX = (Sint8)dx;
	_DeltaY = (Sint8)dy;
}


Uint8
MOUSE_ReadDelta()
{
	switch (_ReadCount++)
	{
		case 0: /* read delta x hi */
			//PRINTF("dx hi = %d\n", ((Uint8)_DeltaX) >> 4);
			return ((Uint8)_DeltaX) >> 4;

		case 1: /* read delta x lo */
			//PRINTF("dx lo = %d\n", ((Uint8)_DeltaX) & 0xF);
			return ((Uint8)_DeltaX) & 0xF;

		case 2: /* read delta y hi */
			//PRINTF("dy hi = %d\n", ((Uint8)_DeltaY) >> 4);
			return ((Uint8)_DeltaY) >> 4;

		case 3: /* read delta y lo */
			//PRINTF("dy lo = %d\n", ((Uint8)_DeltaY) & 0xF);
			return ((Uint8)_DeltaY) & 0xF;

		case 4: //Kitao�ǉ��B���̏�ԂŃ��Z�b�g�����܂ő҂B��������ƈ��̃��Y���ŃJ�[�\���������B���@�ł����l���͖��m�F�Bv1.23
			_DeltaX = 0;
			_DeltaY = 0;
			_ReadCount = 4;
			return 0;
	}

	return 0;
}


Uint8
MOUSE_ReadButtons()
{
	Uint8	ret = _ButtonState;

	if ((ret & 0xC) == 0xC) //RUN+SELECT���������ɂȂ��Ă��܂��Ă���ꍇ
		ret &= ~0xC; //�둀��ɂ��\�t�g���Z�b�g�������B�W���C�p�b�h����̓��Z�b�gOK�Bv1.43

	//�W���C�p�b�h�P��Select�{�^��,Run�{�^��,I�{�^��,II�{�^�����󂯕t����
	if (INPUT_IsPressed(1, JOYPAD_BUTTON_SELECT))	ret |= 4;
	if (INPUT_IsPressed(1, JOYPAD_BUTTON_RUN))		ret |= 8;
	if (INPUT_IsPressed(1, JOYPAD_BUTTON_I))		ret |= 1;
	if (INPUT_IsPressed(1, JOYPAD_BUTTON_II))		ret |= 2;

	//Kitao�ǉ��BSelect�{�^����Run�{�^�����X���b�v����ݒ�i�o�����o���̂��߂̋@�\�j�Ȃ�B
	if (JOYPAD_GetSwapSelRun())
	{
		Uint8	a = ret;
		ret &= ~12;
		ret |= (a & 4)<<1;
		ret |= (a & 8)>>1;
	}

	//Kitao�ǉ��BI�{�^����II�{�^�����X���b�v����ݒ�i���~���O�X���̂��߂̋@�\�j�Ȃ�B
	if (JOYPAD_GetSwapIandII())
	{
		Uint8	a = ret;
		ret &= ~3;
		ret |= (a & 1)<<1;
		ret |= (a & 2)>>1;
	}

	return ret ^0xF;
}


void
MOUSE_Connect(
	BOOL		bConnect)
{
	_bMsConnected = bConnect;
}


BOOL
MOUSE_IsConnected()
{
	return _bMsConnected;
}


//Kitao�X�V�B�i�߂�N���b�N����1�N���b�N�Œ�ɂ����B
void
MOUSE_AdvanceClock()
{
	_ClockCounter++;

	if (_MouseWheelFlg > 0) //Kitao�ǉ��B�}�E�X�z�C�[���̉�]�ŃZ���N�g�{�^���ƃ����{�^���������ꂽ�ꍇ�́A�{�^���X�e�[�g���N���A����B
		if (VDC_GetOverClockNow() == FALSE) //�I�[�o�[�N���b�N�Ԃ�̏����ł͂Ȃ��ʏ��CPU�����p���[���̓���Ȃ�
			if (--_MouseWheelFlg == 0) //��0.33�b�o�߂�����A�Z���N�g�{�^���E�����{�^���������ꂽ���Ƃɂ���B
				_ButtonState &= ~12;
}


//Kitao�ǉ��B�z�C�[����]�ŃZ���N�g�E�����{�^�������������ƂɁA�Z���N�g�E�����{�^���𗣂������̂��߂ɕK�v�B
void
MOUSE_SetMouseWheelFlg()
{
	_MouseWheelFlg = 7159090/3; //��0.33�b�o�߂�����A�����I�ɃZ���N�g�{�^���E�����{�^�����������悤�ɂɂ���B
}

//Kitao�ǉ�
Uint32
MOUSE_GetMouseWheelFlg()
{
	return _MouseWheelFlg;
}


// save variable
#define SAVE_V(V)	if (fwrite(&V, sizeof(V), 1, p) != 1)	return FALSE
#define LOAD_V(V)	if (fread(&V, sizeof(V), 1, p) != 1)	return FALSE
/*-----------------------------------------------------------------------------
	[SaveState]
		��Ԃ��t�@�C���ɕۑ����܂��B 
-----------------------------------------------------------------------------*/
BOOL
MOUSE_SaveState(
	FILE*		p)
{
	Sint32	currY; //Kitao�X�V�B_CurrX��_CurrY�͔�g�p�ɂ������ߋ��o�[�W�����̃X�e�[�g�ƌ݊�������邽�߂Ɏc���Ă���

	if (p == NULL)
		return FALSE;

	SAVE_V(_ReadCount);
	SAVE_V(_DeltaX);
	SAVE_V(_DeltaY);
	SAVE_V(_bMoveX); //Kitao�ǉ��Bv1.23�B����currX���ۑ�����Ă�������g�p�ɂȂ����̂ŁA������bMoveX�ۑ��B
	SAVE_V(currY);
	SAVE_V(_PrevX);
	SAVE_V(_PrevY);
	SAVE_V(_bMsConnected);
	SAVE_V(_ButtonState);
	SAVE_V(_MouseWheelFlg); //Kitao�ǉ�

	return TRUE;
}


/*-----------------------------------------------------------------------------
	[LoadState]
		��Ԃ��t�@�C������ǂݍ��݂܂��B 
-----------------------------------------------------------------------------*/
BOOL
MOUSE_LoadState(
	FILE*		p)
{
	Sint32	currY; //Kitao�X�V�B_CurrX��_CurrY�͔�g�p�ɂ������ߋ��o�[�W�����̃X�e�[�g�ƌ݊�������邽�߂Ɏc���Ă���

	if (p == NULL)
		return FALSE;

	LOAD_V(_ReadCount);
	LOAD_V(_DeltaX);
	LOAD_V(_DeltaY);
	LOAD_V(_bMoveX); //Kitao�ǉ��Bv1.23�B����currX���ۑ�����Ă�������g�p�ɂȂ����̂ŁA������bMoveX�ۑ��B�Â��X�e�[�g��currX��bMoveX�Ƃ��ēǂݍ���ł��܂����AbMoveX�͂ǂ�Ȓl�ł��s�s���͖����̂Ŗ��Ȃ��B
	LOAD_V(currY); //Kitao�X�V�B���ݔ�g�p
	LOAD_V(_PrevX);
	LOAD_V(_PrevY);
	LOAD_V(_bMsConnected);
	LOAD_V(_ButtonState);
	LOAD_V(_MouseWheelFlg); //Kitao�ǉ�

	return TRUE;
}

#undef SAVE_V
#undef LOAD_V
