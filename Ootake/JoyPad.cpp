/******************************************************************************
Ootake
�E���͂̓ǂݍ��ݏ������s���邻�̂ǁAWindows�p�b�h�̏�Ԃ��ŐV��Ԃɂ��ēǂ�
  ���悤�ɂ����B�A�N�V�����Q�[���ł̔������ǂ��Ȃ�A���@�̑��슴�ɋ߂Â����B
�E�}���`�^�b�v��t���Ă��Ȃ����́A���@���l�ɁA�P�o�Ɠ������͂��Q�o�`�T�o�ɂ��o
  �͂����悤�ɂ����B(���Z�M�ŃI�v�V�������e�������Ȃ���������)
�E�J�E���^�[�̐i�ߕ����Z�J���h�o�C�g�t���O�̍X�V�̎d����ύX���A�����_�L���[�u
  ��TSP�Ȃǂ������̂U�{�^���p�b�h�Ō듮�삷��������������B
�E_bClearFlg�������Ă���Ƃ��́A����_bHighNibble���N���A����悤�ɂ����B�^�E��
  �_�]���Ő���ɃZ�[�u��(MB128�ƒʏ�BRAM����)�ł���悤�ɂȂ����Bv1.53
�E�Z���N�g�{�^���ƃ����{�^�������ւ���@�\��t�����B�i�o�����o���Ńv���C����
  �������邽�߁j
�E�A�ˋ@�\�������B
�E�A�x�j���[�p�b�h�R�̂悤�ɁA�R�{�^���p�̐ݒ���ł���悤�ɂ����Bv0.79

Copyright(C)2006-2013 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[JoyPad.c]
		�p�b�h���L�q���܂��B

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
#define _CRT_SECURE_NO_DEPRECATE //sprintf�֐��ŃR���p�C���x�����o���Ȃ�����

#define DIRECTINPUT_VERSION	0x0500	//Kitao�ǉ��B���ɂ���邩������Ȃ����ADirectInput5���y���B7���Ƃ��x������B�X�y�[�X�n���A�[���킩��₷���B

#include "JoyPad.h"
#include "Input.h"
#include "MB128.h"
#include "Mouse.h"
#include "WinMain.h"
#include "MainBoard.h"
#include "App.h"
#include "Printf.h"

extern Sint32 gCPU_ClockCount; //v2.00�ǉ��B�������̂��߃J�E���^���O���[�o�����B

//Kitao�ǉ��B�A�˃X�s�[�h�B���o�[�W�����ł͑S�p�b�h���p�̃X�s�[�h�B
#define RENSHA_HIGH		2
#define RENSHA_MIDDLE	4 //�h���S���X�s���b�g�C�d�������L�C���W�F���h�I�u�q�[���[�g���}OK
#define RENSHA_LOW		7 //v0.87�X�V�B��ɂ��邱�ƂŃC�[�X�S�̃t�@�C���[�A��OK

static BOOL		_bMultiTap;
static BOOL		_bSixButtonPad;
static BOOL		_bThreeButtonPad; //Kitao�ǉ�
static BOOL		_bSwapSelRun; //Kitao�ǉ�
static BOOL		_bSwapIandII; //Kitao�ǉ��Bv0.80

static Uint32	_Counter;
static BOOL		_bClearFlg;
static BOOL		_bHighNibble;
static BOOL		_bSecondByte;

static Sint32	_PrevUpdateStateLine = -1; //Kitao�ǉ�
static BOOL		_bMakeHesNoSound = FALSE; //Kitao�ǉ�
static BOOL		_bMakeHesNoSoundExecute = FALSE; //Kitao�ǉ�

static PCEPAD	_RenshaCount[6]; //�ePCE�p�b�h[1]�`[5]�̘A�ːݒ�([0]�͔�g�p)�B0�Ȃ�A�˃I�t�B1�ȏ�Ȃ�A�˃I���B�J�E���^�Ƃ��Ă��g���B
static PCEPAD	_RenshaSpeed[6]; //�ePCE�p�b�h[1]�`[5]�̘A�ˑ��x�ݒ�([0]�͔�g�p)
static Sint32	_RenshaSpeedSel; //�A�ːݒ�̑I��l�B
static Sint16	_RenshaSpeedMax; //�A�˃X�s�[�h����������ƒe���o�Ȃ��\�t�g�̏ꍇ�A���e�͈͒l�������ɐݒ肷��B

static Uint8	_PrevCursorKeyLR[6]; //v2.59�ǉ�
static Uint8	_PrevCursorKeyUD[6]; //v2.59�ǉ�

static BOOL		_bEmeraldDragon; //v2.68�ǉ�
//static Sint32	_PrevWrite = -1; //v2.68�ǉ��Btest


//Kitao�X�V
static
Uint8
read_two_button_pad()
{
	Uint8	ret = 0x0F; //TG16����(bit6=0)
	Uint8	b1, b2;
	Uint32	padNumber;
	BOOL	bThreeButtonPushed = FALSE; //Kitao�ǉ�

	if (_Counter == 0)
		return 0x00; //v1.10�X�V�B�G�������h�h���S����MB128���[�e�B���e�B������B�K���w�b�h�̖ʃZ���N�g���Z��OK�B

	if (_bMultiTap)
	{
		if (_Counter > 5)
			return 0x0F; //v1.10�X�V�B������0x00��Ԃ��Ɛ^�����L�œ��͕s��B
		padNumber = _Counter;
	}
	else
		padNumber = 1; //Kitao�ǉ��B�}���`�^�b�v��t���Ă��Ȃ��Ƃ���2P�`5P�̐M����1P�̑���ŏo�͂����B

	if (_bHighNibble)
	{
		if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_UP))		ret &= ~0x1;
		if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_RIGHT))	ret &= ~0x2;
		if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_DOWN))		ret &= ~0x4;
		if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_LEFT))		ret &= ~0x8;

		//���E���������A�㉺���������̓��͂�}���B�C���[�W�t�@�C�g�Q�ŕK�v�Bv2.59	
		if (APP_GetCheckSimultaneouslyPush())
		{
			if ((ret & 0xA) == 0) //���E��������
				ret |= _PrevCursorKeyLR[padNumber]; //��ԍŌ�ɉ������L�[�݂̂�L���ɂ���
			else
				_PrevCursorKeyLR[padNumber] = ~ret & 0xA;
			if ((ret & 0x5) == 0) //�㉺��������
				ret |= _PrevCursorKeyUD[padNumber]; //��ԍŌ�ɉ������L�[�݂̂�L���ɂ���
			else
				_PrevCursorKeyUD[padNumber] = ~ret & 0x5;
		}
	}
	else
	{
		if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_I))
		{
			if ((_RenshaCount[padNumber].button1 > 0)&&
				(_RenshaSpeed[1].button1 > 0)) //�A�˃X�s�[�h���I�t�ł͂Ȃ��ꍇ
			{
				if (_RenshaCount[padNumber].button1 <= (_RenshaSpeed[1].button1 >> 1)) //�J�E���^�̒l�������ȉ��̂Ƃ��͉����ꂽ���Ƃɂ���B��������̂Ƃ��͉�����Ă��Ȃ����Ƃɂ���B
					ret &= ~0x1; //�����ꂽ
				if (--_RenshaCount[padNumber].button1 == 0)
					_RenshaCount[padNumber].button1 = _RenshaSpeed[1].button1; //�A�˃X�s�[�h�́A���o�[�W�����ł̓p�b�h�P�̐ݒ��S�p�b�h�ŋ��p����B
			}
			else
				ret &= ~0x1; //�����ꂽ
		}
		else if ((_RenshaCount[padNumber].button1 > 0)&&
				 (_RenshaSpeed[1].button1 > 0)) //�A�˃X�s�[�h���I�t�ł͂Ȃ��ꍇ
					_RenshaCount[padNumber].button1 = (_RenshaSpeed[1].button1 >> 1); //�{�^���������Ă��Ȃ������ꍇ�A�A�˃J�E���^�����Z�b�g����B���ɂ��̃{�^�����������Ƃ��Ɂu�����������Ɣ��肳���v���߂ɕK�v�B

		if (_RenshaSpeed[1].button5 > 0) //�A�˃X�s�[�h���I�t�ł͂Ȃ��ꍇ
		{
			if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_V)) //JOYPAD_BUTTON_V�c2�{�^��,3�{�^���p�b�h�̂Ƃ��́A�A�ː�p�{�^���Ƃ��ċ@�\�B
			{
				if (_RenshaCount[padNumber].button5 > 0)
				{
					if (_RenshaCount[padNumber].button5 <= (_RenshaSpeed[1].button5 >> 1)) //�J�E���^�̒l�������ȉ��̂Ƃ��͉����ꂽ���Ƃɂ���B��������̂Ƃ��͉�����Ă��Ȃ����Ƃɂ���B
						ret &= ~0x1; //�����ꂽ
					if (--_RenshaCount[padNumber].button5 == 0)
						_RenshaCount[padNumber].button5 = _RenshaSpeed[1].button5; //�A�˃X�s�[�h�́A���o�[�W�����ł̓p�b�h�P�̐ݒ��S�p�b�h�ŋ��p����B
				}
				else
					ret &= ~0x1; //�����ꂽ
			}
			else if (_RenshaCount[padNumber].button5 > 0)
					_RenshaCount[padNumber].button5 = (_RenshaSpeed[1].button5 >> 1); //�{�^���������Ă��Ȃ������ꍇ�A�A�˃J�E���^�����Z�b�g����B���ɂ��̃{�^�����������Ƃ��Ɂu�����������Ɣ��肳���v���߂ɕK�v�B
		}

		if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_II))
		{
			if ((_RenshaCount[padNumber].button2 > 0)&&
				(_RenshaSpeed[1].button2 > 0)) //�A�˃X�s�[�h���I�t�ł͂Ȃ��ꍇ
			{
				if (_RenshaCount[padNumber].button2 <= (_RenshaSpeed[1].button2 >> 1)) //�J�E���^�̒l�������ȉ��̂Ƃ��͉����ꂽ���Ƃɂ���B��������̂Ƃ��͉�����Ă��Ȃ����Ƃɂ���B
					ret &= ~0x2; //�����ꂽ
				if (--_RenshaCount[padNumber].button2 == 0)
					_RenshaCount[padNumber].button2 = _RenshaSpeed[1].button2; //�A�˃X�s�[�h�́A���o�[�W�����ł̓p�b�h�P�̐ݒ��S�p�b�h�ŋ��p����B
			}
			else
				ret &= ~0x2; //�����ꂽ
		}
		else if ((_RenshaCount[padNumber].button2 > 0)&&
				 (_RenshaSpeed[1].button2 > 0)) //�A�˃X�s�[�h���I�t�ł͂Ȃ��ꍇ
					_RenshaCount[padNumber].button2 = (_RenshaSpeed[1].button2 >> 1); //�{�^���������Ă��Ȃ������ꍇ�A�A�˃J�E���^��1�Ƀ��Z�b�g����B���ɂ��̃{�^�����������Ƃ��Ɂu�����������Ɣ��肳���v���߂ɕK�v�B

		if (_RenshaSpeed[1].button6 > 0) //�A�˃X�s�[�h���I�t�ł͂Ȃ��ꍇ
		{
			if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_VI)) //JOYPAD_BUTTON_VI�c2�{�^��,3�{�^���p�b�h�̂Ƃ��́A�A�ː�p�{�^���Ƃ��ċ@�\�B
			{
				if (_RenshaCount[padNumber].button6 > 0)
				{
					if (_RenshaCount[padNumber].button6 <= (_RenshaSpeed[1].button6 >> 1)) //�J�E���^�̒l�������ȉ��̂Ƃ��͉����ꂽ���Ƃɂ���B��������̂Ƃ��͉�����Ă��Ȃ����Ƃɂ���B
						ret &= ~0x2; //�����ꂽ
					if (--_RenshaCount[padNumber].button6 == 0)
						_RenshaCount[padNumber].button6 = _RenshaSpeed[1].button6; //�A�˃X�s�[�h�́A���o�[�W�����ł̓p�b�h�P�̐ݒ��S�p�b�h�ŋ��p����B
				}
				else
					ret &= ~0x2; //�����ꂽ
			}
			else if (_RenshaCount[padNumber].button6 > 0)
					_RenshaCount[padNumber].button6 = (_RenshaSpeed[1].button6 >> 1); //�{�^���������Ă��Ȃ������ꍇ�A�A�˃J�E���^��1�Ƀ��Z�b�g����B���ɂ��̃{�^�����������Ƃ��Ɂu�����������Ɣ��肳���v���߂ɕK�v�B
		}

		if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_SELECT))
			ret &= ~0x4;
		if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_IV)) //�R�{�^���p�b�h�ݒ�̎��p
		{
			ret &= ~0x4;
			bThreeButtonPushed = TRUE;
		}
		if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_RUN))
			ret &= ~0x8;
		if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_III)) //�R�{�^���p�b�h�ݒ�̎��p
		{
			ret &= ~0x8;
			bThreeButtonPushed = TRUE;
		}
		if ((ret & 0x8)==0) //RUN�{�^���������ꂽ�Ȃ�
		{
			//RUN�{�^���̘A�ˏ���
			if ((_RenshaCount[padNumber].buttonRun > 0)&&
				(_RenshaSpeed[1].buttonRun > 0)) //�A�˃X�s�[�h���I�t�ł͂Ȃ��ꍇ
			{
				if (_RenshaCount[padNumber].buttonRun > (_RenshaSpeed[1].buttonRun >> 1)) //�J�E���^�̒l����������̂Ƃ��͉�����Ă��Ȃ����Ƃɂ���B�����ȉ��̂Ƃ��͉����ꂽ���Ƃɂ���B
					ret |= 0x8; //������Ă��Ȃ����Ƃɂ���
				if (--_RenshaCount[padNumber].buttonRun == 0)
					_RenshaCount[padNumber].buttonRun = _RenshaSpeed[1].buttonRun; //�A�˃X�s�[�h�́A���o�[�W�����ł̓p�b�h�P�̐ݒ��S�p�b�h�ŋ��p����B
			}
		}
		else if ((_RenshaCount[padNumber].buttonRun > 0)&&
				 (_RenshaSpeed[1].buttonRun > 0)) //�A�˃X�s�[�h���I�t�ł͂Ȃ��ꍇ
					_RenshaCount[padNumber].buttonRun = (_RenshaSpeed[1].buttonRun >> 1); //�{�^���������Ă��Ȃ������ꍇ�A�A�˃J�E���^��1�Ƀ��Z�b�g����B���ɂ��̃{�^�����������Ƃ��Ɂu�����������Ɣ��肳���v���߂ɕK�v�B

		if (_bSwapSelRun)
			if ((!_bThreeButtonPad)||(bThreeButtonPushed)) //�R�{�^���p�b�h�̏ꍇ�AIII��IV�{�^���������ꂽ�Ƃ��̂ݓ���ւ����s��(�ʏ��SELECT,RUN�{�^���������ꂽ�Ƃ��͓��ꊷ���Ȃ�)�B
			{	//RUN�{�^����SELECT�{�^�������ւ�
				b1 = (ret & 0x8) >> 1;
				b2 = (ret & 0x4) << 1;
				ret &= ~0xC;
				ret |= b1 | b2;
			}
		if (_bSwapIandII)
		{	//I�{�^����II�{�^�������ւ�
			b1 = (ret & 0x2) >> 1;
			b2 = (ret & 0x1) << 1;
			ret &= ~0x3;
			ret |= b1 | b2;
		}
	}

	//�t�@���N�V�����{�^���������Ă���Ԃ�PCE���ւ̓��͂��󂯕t���Ȃ��悤�ɂ���Bv2.38
	if ((padNumber == 1)&&(INPUT_CheckButtonState(APP_GetFunctionButton())))
		if (APP_CheckShortcutKey(APP_GetFunctionButton())) //�t�@���N�V�����{�^����PCE�̃{�^���Ɣ���Ă����ꍇ(FALSE���Ԃ�)�́A�t�@���N�V�����{�^���������Ȃ̂œ��͂��󂯕t����Bv2.77
			return 0x0F; //���͂��󂯕t���Ȃ�

	return ret;
}


//Kitao�X�V�B�������V���v���ɂ����B�Z�J���h�o�C�g�t���O�̍X�V�̎d����ύX���A��TSP�Ȃǂł̕s��𒼂����B
static
Uint8
read_six_button_pad()
{
	Uint8	ret = 0x0F; //TG16����(bit6=0)
	Uint8	b1, b2;
	Uint32	padNumber;

	if (_Counter == 0)
		return 0x00;

	if (_bMultiTap)
	{
		if (_Counter > 5)
			return 0x0F; //v1.10�X�V
		padNumber = _Counter;
	}
	else
		padNumber = 1; //Kitao�ǉ��B�}���`�^�b�v��t���Ă��Ȃ��Ƃ���2P�`5P�̐M����1P�̑���ŏo�͂����B

	if (_bSecondByte)
	{
		if (_bHighNibble)
		{
			if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_UP))		ret &= ~0x1;
			if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_RIGHT))	ret &= ~0x2;
			if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_DOWN))		ret &= ~0x4;
			if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_LEFT))		ret &= ~0x8;

			//���E���������A�㉺���������̓��͂�}���B�C���[�W�t�@�C�g�Q�ŕK�v�Bv2.59	
			if (APP_GetCheckSimultaneouslyPush())
			{
				if ((ret & 0xA) == 0) //���E��������
					ret |= _PrevCursorKeyLR[padNumber]; //��ԍŌ�ɉ������L�[�݂̂�L���ɂ���
				else
					_PrevCursorKeyLR[padNumber] = ~ret & 0xA;
				if ((ret & 0x5) == 0) //�㉺��������
					ret |= _PrevCursorKeyUD[padNumber]; //��ԍŌ�ɉ������L�[�݂̂�L���ɂ���
				else
					_PrevCursorKeyUD[padNumber] = ~ret & 0x5;
			}
		}
		else
		{
			if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_I))
			{
				if ((_RenshaCount[padNumber].button1 > 0)&&
					(_RenshaSpeed[1].button1 > 0)) //�A�˃X�s�[�h���I�t�ł͂Ȃ��ꍇ
				{
					if (_RenshaCount[padNumber].button1 <= (_RenshaSpeed[1].button1 >> 1)) //�J�E���^�̒l�������ȉ��̂Ƃ��͉����ꂽ���Ƃɂ���B��������̂Ƃ��͉�����Ă��Ȃ����Ƃɂ���B
						ret &= ~0x1; //�����ꂽ
					if (--_RenshaCount[padNumber].button1 == 0)
						_RenshaCount[padNumber].button1 = _RenshaSpeed[1].button1; //�A�˃X�s�[�h�́A���o�[�W�����ł̓p�b�h�P�̐ݒ��S�p�b�h�ŋ��p����B
				}
				else
					ret &= ~0x1; //�����ꂽ
			}
			else if ((_RenshaCount[padNumber].button1 > 0)&&
					 (_RenshaSpeed[1].button1 > 0)) //�A�˃X�s�[�h���I�t�ł͂Ȃ��ꍇ
						_RenshaCount[padNumber].button1 = (_RenshaSpeed[1].button1 >> 1); //�{�^���������Ă��Ȃ������ꍇ�A�A�˃J�E���^�����Z�b�g����B���ɂ��̃{�^�����������Ƃ��Ɂu�����������Ɣ��肳���v���߂ɕK�v�B

			if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_II))
			{
				if ((_RenshaCount[padNumber].button2 > 0)&&
					(_RenshaSpeed[1].button2 > 0)) //�A�˃X�s�[�h���I�t�ł͂Ȃ��ꍇ
				{
					if (_RenshaCount[padNumber].button2 <= (_RenshaSpeed[1].button2 >> 1)) //�J�E���^�̒l�������ȉ��̂Ƃ��͉����ꂽ���Ƃɂ���B��������̂Ƃ��͉�����Ă��Ȃ����Ƃɂ���B
						ret &= ~0x2; //�����ꂽ
					if (--_RenshaCount[padNumber].button2 == 0)
						_RenshaCount[padNumber].button2 = _RenshaSpeed[1].button2; //�A�˃X�s�[�h�́A���o�[�W�����ł̓p�b�h�P�̐ݒ��S�p�b�h�ŋ��p����B
				}
				else
					ret &= ~0x2; //�����ꂽ
			}
			else if ((_RenshaCount[padNumber].button2 > 0)&&
					 (_RenshaSpeed[1].button2 > 0)) //�A�˃X�s�[�h���I�t�ł͂Ȃ��ꍇ
						_RenshaCount[padNumber].button2 = (_RenshaSpeed[1].button2 >> 1); //�{�^���������Ă��Ȃ������ꍇ�A�A�˃J�E���^��1�Ƀ��Z�b�g����B���ɂ��̃{�^�����������Ƃ��Ɂu�����������Ɣ��肳���v���߂ɕK�v�B

			if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_SELECT))
				ret &= ~0x4;
			if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_RUN))
				ret &= ~0x8;
			if ((ret & 0x8)==0) //RUN�{�^���������ꂽ�Ȃ�
			{
				//RUN�{�^���̘A�ˏ���
				if ((_RenshaCount[padNumber].buttonRun > 0)&&
					(_RenshaSpeed[1].buttonRun > 0)) //�A�˃X�s�[�h���I�t�ł͂Ȃ��ꍇ
				{
					if (_RenshaCount[padNumber].buttonRun > (_RenshaSpeed[1].buttonRun >> 1)) //�J�E���^�̒l����������̂Ƃ��͉�����Ă��Ȃ����Ƃɂ���B�����ȉ��̂Ƃ��͉����ꂽ���Ƃɂ���B
						ret |= 0x8; //������Ă��Ȃ����Ƃɂ���
					if (--_RenshaCount[padNumber].buttonRun == 0)
						_RenshaCount[padNumber].buttonRun = _RenshaSpeed[1].buttonRun; //�A�˃X�s�[�h�́A���o�[�W�����ł̓p�b�h�P�̐ݒ��S�p�b�h�ŋ��p����B
				}
			}
			else if ((_RenshaCount[padNumber].buttonRun > 0)&&
					 (_RenshaSpeed[1].buttonRun > 0)) //�A�˃X�s�[�h���I�t�ł͂Ȃ��ꍇ
						_RenshaCount[padNumber].buttonRun = (_RenshaSpeed[1].buttonRun >> 1); //�{�^���������Ă��Ȃ������ꍇ�A�A�˃J�E���^��1�Ƀ��Z�b�g����B���ɂ��̃{�^�����������Ƃ��Ɂu�����������Ɣ��肳���v���߂ɕK�v�B

			if (_bSwapSelRun)
			{	//RUN�{�^����SELECT�{�^�������ւ�
				b1 = (ret & 0x8) >> 1;
				b2 = (ret & 0x4) << 1;
				ret &= ~0xC;
				ret |= b1 | b2;
			}
			if (_bSwapIandII)
			{	//I�{�^����II�{�^�������ւ�
				b1 = (ret & 0x2) >> 1;
				b2 = (ret & 0x1) << 1;
				ret &= ~0x3;
				ret |= b1 | b2;
			}
		}
	}
	else
	{
		if (_bHighNibble)
			ret = 0x00; //������0x00�i�㉺���E����������ԁj���Ԃ���邱�ƂŁA�Q�[���\�t�g���͂U�{�^���p�b�h���Ȃ����Ă���ƔF�������i�U�{�^�������ȑO�̃Q�[���ł͌듮�삷��j�Bv2.68�L
		else
		{
			if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_III))	ret &= ~0x1;
			if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_IV))	ret &= ~0x2;
			if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_V))	ret &= ~0x4;
			if (INPUT_IsPressed(padNumber, JOYPAD_BUTTON_VI))	ret &= ~0x8;
		}
	}

	//Kitao�ǉ��B�}���`�^�b�v��g�p���́u�p�b�h�T�Ԃ��ǂݏo���I�����v�ꍇ�A�Z�J���h�o�C�g�t���O���N���A���A�Q�{�^���̐��ɂ���B�����_�L���[�u�̃^�C�g����ʂŕK�v�B�G�������h�h���S����MB128���[�e�B���e�B(�㉟���Ȃ���X�^�[�g�j�ł��K�v�B
	if (!_bMultiTap)
		if (_Counter == 5)
			if (!_bHighNibble)
			{
				if (_bEmeraldDragon) //�G�������h�h���S���p�b�`�����B�G�������h�h���S���N������_bSecondByte���N���A�������III�`VI�{�^���������Ȃ��Ȃ��Ă��܂����Ƃւ̑Ώ��B����C���\��Bv2.68
				{
					if ((VDC_GetMWR() == 0x00)||(VDC_GetMWR() == 0x50)) //CD�N����ʁiMWR=0x00�BMB128�c�[���N���̂��߁j���J�W�m�̃V�[���iMWR=0x50�j�̏ꍇ�B�t�B�[���h��MWR=0x10�Ȃ̂Ńp�b�`�����ł���B��������������ăp�b�`����Ȃ������łł���΁B�j
						_bSecondByte = FALSE; //�Q�{�^���̐���
				}	
				else
					_bSecondByte = FALSE; //�Q�{�^���̐���
			}

	//�t�@���N�V�����{�^���������Ă���Ԃ�PCE���ւ̓��͂��󂯕t���Ȃ��悤�ɂ���Bv2.38
	if ((padNumber == 1)&&(INPUT_CheckButtonState(APP_GetFunctionButton())))
		if (APP_CheckShortcutKey(APP_GetFunctionButton())) //�t�@���N�V�����{�^����PCE�̃{�^���Ɣ���Ă����ꍇ(FALSE���Ԃ�)�́A�t�@���N�V�����{�^���������Ȃ̂œ��͂��󂯕t����Bv2.77
			return 0x0F; //���͂��󂯕t���Ȃ�

	return ret;
}


//Kitao�ǉ��BMainBoard.c������g�p�B
void
JOYPAD_Reset()
{
	_Counter = 0;
	_bClearFlg = FALSE;
	_bHighNibble = FALSE;
	_bSecondByte = FALSE;
}


/*-----------------------------------------------------------------------------
	������ 
-----------------------------------------------------------------------------*/
Sint32
JOYPAD_Init()
{
	int	i;

	INPUT_Init();

	_bSixButtonPad = FALSE;
	_bMultiTap = TRUE;
	_bSwapSelRun = FALSE; //Kitao�ǉ�
	_bSwapIandII = FALSE; //Kitao�ǉ�
	JOYPAD_ConnectMouse(FALSE); //Kitao�ǉ�
	JOYPAD_ConnectMB128(TRUE);

	//Kitao�ǉ��B�\���L�[���������}���p�ϐ���������
	for (i=1; i<=5; i++)
	{
		_PrevCursorKeyLR[i] = 0;
		_PrevCursorKeyUD[i] = 0;
	}

	//Kitao�ǉ��B�A�˗p�ϐ���������
	ZeroMemory(_RenshaCount, sizeof(_RenshaCount));
	JOYPAD_SetRenshaButton5(TRUE);
	JOYPAD_SetRenshaButton6(TRUE);
	_RenshaSpeedSel = APP_GetRenshaSpeedSel();
	_RenshaSpeedMax = 0;
	JOYPAD_SetRenshaSpeedButton1(_RenshaSpeedSel);
	JOYPAD_SetRenshaSpeedButton2(_RenshaSpeedSel);
	JOYPAD_SetRenshaSpeedButtonRun(_RenshaSpeedSel);
	JOYPAD_SetRenshaSpeedButton5(_RenshaSpeedSel);
	JOYPAD_SetRenshaSpeedButton6(_RenshaSpeedSel);

	JOYPAD_Reset();//Kitao�ǉ�

	return 0;
}


void
JOYPAD_Deinit()
{
	INPUT_Deinit();
}


//Kitao�X�V�B�߂�l���Ȃ����ݒ��p�ɂ����B
void
JOYPAD_ConnectMultiTap(
	BOOL	bConnect)
{
	_bMultiTap = bConnect;
}

//Kitao�X�V�B�߂�l���Ȃ����ݒ��p�ɂ����B
void
JOYPAD_UseSixButton(
	BOOL	bSixButton)
{
	_bSixButtonPad = bSixButton;
	//Kitao�ǉ�
	if (bSixButton)
	{	//�{�^���T,�U(�Q,�R�{�^���p�b�h�g�p���̘A�˗p�{�^��)�̘A�ːݒ����������B
		JOYPAD_SetRenshaButton5(FALSE);
		JOYPAD_SetRenshaButton6(FALSE);
	}
	else
	{	//�{�^���T,�U(�Q,�R�{�^���p�b�h�g�p���̘A�˗p�{�^��)�̘A�ːݒ�𕜋A����B
		if (JOYPAD_GetRenshaButton1())
			JOYPAD_SetRenshaButton5(FALSE);
		else
			JOYPAD_SetRenshaButton5(TRUE);
		if (JOYPAD_GetRenshaButton2())
			JOYPAD_SetRenshaButton6(FALSE);
		else
			JOYPAD_SetRenshaButton6(TRUE);
	}
}

//Kitao�ǉ�
void
JOYPAD_UseThreeButton(
	BOOL	bThreeButton)
{
	_bThreeButtonPad = bThreeButton;
}

//Kitao�X�V�B�߂�l���Ȃ����ݒ��p�ɂ����B
void
JOYPAD_ConnectMouse(
	BOOL	bConnect)
{
	MOUSE_Connect(bConnect);
	WINMAIN_ShowCursor(~bConnect); //Kitao�ǉ�
}

//Kitao�X�V�B�߂�l���Ȃ����ݒ��p�ɂ����B
void
JOYPAD_ConnectMB128(
	BOOL	bConnect)
{
	MB128_Connect(bConnect);
}


//Kitao�ǉ�
BOOL
JOYPAD_GetConnectMultiTap()
{
	return _bMultiTap;
}

//Kitao�ǉ�
BOOL
JOYPAD_GetConnectSixButton()
{
	return _bSixButtonPad;
}

//Kitao�ǉ�
BOOL
JOYPAD_GetConnectThreeButton()
{
	return _bThreeButtonPad;
}


//Kitao�ǉ�
void
JOYPAD_SetSwapSelRun(
	BOOL	bSwapSelRun)
{
	_bSwapSelRun = bSwapSelRun;
}

//Kitao�ǉ�
void
JOYPAD_SetSwapIandII(
	BOOL	bSwapIandII)
{
	_bSwapIandII = bSwapIandII;
}

//Kitao�ǉ��BApp.c��Mouse.c����g�p�B
BOOL
JOYPAD_GetSwapSelRun()
{
	return _bSwapSelRun;
}

//Kitao�ǉ��BApp.c��Mouse.c����g�p�B
BOOL
JOYPAD_GetSwapIandII()
{
	return _bSwapIandII;
}


/*	$1000 (R) status */
Uint8
JOYPAD_Read(
	Uint32	regNum)
{
	Uint8	ret;

	//if (regNum != 0x1000)
	//	PRINTF("JOYPAD_Read = %X",regNum); //test
/*
if (WINMAIN_GetBreakTrap())
{
	char s[100];
	sprintf(s,"JOYPAD_Read = %X",regNum);
	int ok;
	ok = MessageBox(WINMAIN_GetHwnd(), s, "Test", MB_YESNO); //Kitao Test
	if (ok != IDYES)
		WINMAIN_SetBreakTrap(FALSE);
}
*/
	//_PrevWrite = -1; //test

	if (MB128_IsActive())
		return MB128_Read();

	//Kitao�ǉ��B�J�E���^�[��Read���ɐi�߂�悤�ɂ����B��TSP�Ȃǂ������̂U�{�^���p�b�h�Ή��\�t�g�ł̖��������B
	if (_bHighNibble)
	{
		if (++_Counter == 16) //4bit�Ɖ���B16�Ȃ�0�ɖ߂��B3bit���Ƃe�P�T�[�J�X�ŎԂ��X�^�[�g�ł����Bv1.53
			_Counter = 0;
	}

	//Kitao�ǉ��B������Windows�W���C�X�e�B�b�N�̏�Ԃ��A�b�v�f�[�g���邱�ƂŒx�����Ȃ�����ł���B�X�y�[�X�n���A�[(�ŏ��̉~��`���Ȃ���A��)�ňႢ���킩��
 	if (MAINBOARD_GetScanLine() != _PrevUpdateStateLine) //�O��A�b�v�f�[�g���Ă���P���C���`��ȏ�̎��Ԃ������Ă�����A�b�v�f�[�g�B�A�b�v�f�[�g�̂��߂��ŏd���Ȃ邱�Ƃ�����B
	{
		INPUT_UpdateState(TRUE);
		_PrevUpdateStateLine = MAINBOARD_GetScanLine();
	}

	if (MOUSE_IsConnected())
	{
		if (_Counter == 1)
		{
			if (_bHighNibble)
				return MOUSE_ReadDelta();
			else
				return MOUSE_ReadButtons();
		}
		else if (_bMultiTap) //�}���`�^�b�v�Ή��ɁBv2.66
		{
			if (_Counter == 2) //2P�ɃW���C�p�b�h����������Ԃ��Č��B�Ƃ��߂��������A���̃~�j�Q�[���ŁA�p�b�h�̂Ȃ��Ȃ������s��Ȃ��Ă�OK�ɁB
			{
				_Counter = 1; //�R���g���[���P�̃W���C�p�b�h�{�^�����Q�Ƃ���B
				ret = read_two_button_pad();
				_Counter = 2; //�J�E���^�[�����ɖ߂��B
				return ret;
			}
			else if (_Counter == 3) //3P�ɃW���C�p�b�h����������Ԃ��Č��B�Ƃ��߂��������A����3P�p�b�h���g�����Z���Č��B�����Z�̏ڍׂ��܂��킩��Ȃ��̂Ŗ��e�X�g�Bv2.66
				return read_two_button_pad(); //�R���g���[���R�̃W���C�p�b�h�{�^�����Q�Ƃ���B
		}
	}

	if (_bSixButtonPad)
		return read_six_button_pad();

	//Kitao�ǉ��Bhes�t�@�C���̋ȊԂɖ���������Bv1.29
	if (_bMakeHesNoSound)
	{
		ret = read_two_button_pad();
		if (_bMakeHesNoSoundExecute)
		{
			if ((_Counter == 1)&&(!_bHighNibble)&&((ret & 0x3) == 3)) //I�{�^����II�{�^���𗣂��Ă�����
				_bMakeHesNoSoundExecute = FALSE;
		}
		else
		{
			if ((_Counter == 1)&&(!_bHighNibble)&&((ret & 0x3) != 3)) //I�{�^����II�{�^���������Ă�����
			{
				PSG_ResetVolumeReg(); //PSG�̃{�����[�����W�X�^��0�ɁB
				gCPU_ClockCount -= (Sint32)(7159090*0.5); //0.5�b�ԁB�������Ԃ����B
				_bMakeHesNoSoundExecute = TRUE; //�Q��A�����ē��삳���Ȃ����߂̍�
			}
		}
		return ret;
	}

	return read_two_button_pad();
}


/*	$1000 (W) select */
//Kitao�X�V�B�������V���v���ɂ����B�������̂U�{�^���p�b�h�Ή��\�t�g�̕s����Ȃ������B
void
JOYPAD_Write(
	Uint32	regNum,
	Uint8	data)
{
	//if (data == 3)
	//	PRINTF("JOYPAD_Write = %X, %X",regNum, data); //test
/*
if (WINMAIN_GetBreakTrap())
{
	char s[100];
	sprintf(s,"JOYPAD_Write = %X, %X",regNum, data);
	int ok;
	ok = MessageBox(WINMAIN_GetHwnd(), s, "Test", MB_YESNO); //Kitao Test
	if (ok != IDYES)
		WINMAIN_SetBreakTrap(FALSE);
}
*/
	MB128_Write(data);

	_bClearFlg = data & 0x2;
	_bHighNibble = data & 0x1;

	if (_bClearFlg)
	{
		_Counter = 0;
		_bHighNibble = FALSE; //Kitao�ǉ��B�^�E���_�]���̃Z�[�u���ɕK�v�Bv1.53
		_bSecondByte ^= TRUE; //Kitao�ǉ��B�Z�J���h�o�C�g�����]����悤���B��TSP�Ȃǂł̕s����Ȃ������B
		MOUSE_Reset();
	}
/*
if (data == 1)
if (_PrevWrite == 0)
{
	_bSecondByte = FALSE; //test
{
	char s[100];
	sprintf(s,"STOP JOYPAD_Write = %X, %X",regNum, data);
	int ok;
	ok = MessageBox(WINMAIN_GetHwnd(), s, "Test", MB_YESNO); //Kitao Test
	if (ok != IDYES)
		WINMAIN_SetBreakTrap(FALSE);
}
}
*/
	//_PrevWrite = data; //test
}


//Kitao�ǉ�
void
JOYPAD_ClearPrevUpdateStateLine()
{
	_PrevUpdateStateLine = -1;
}


//Kitao�ǉ��B�A�˃X�s�[�h���Z�b�g����B���o�[�W�����ł͑S�p�b�h���p�̃X�s�[�h�B
void
JOYPAD_SetRenshaSpeedButton1(
	Sint32	n)
{
	_RenshaSpeedSel = n;

	switch (n)
	{
		case 0: //Off
			_RenshaSpeed[1].button1 = 0;
			break;
		case 1: //High
			_RenshaSpeed[1].button1 = RENSHA_HIGH;
			break;
		case 2: //Middle
			_RenshaSpeed[1].button1 = RENSHA_MIDDLE;
			break;
		case 3: //Low
			_RenshaSpeed[1].button1 = RENSHA_LOW;
			break;
	}

	//�A�˃X�s�[�h����������ƒe���o�Ȃ��\�t�g�̏ꍇ�A�����I�ɑ��x�������Ē�������Bv1.43�ǉ�
	if ((_RenshaSpeed[1].button1 != 0)&&(_RenshaSpeed[1].button1 < _RenshaSpeedMax))
		_RenshaSpeed[1].button1 = _RenshaSpeedMax;
}
//Kitao�ǉ��B�A�˃X�s�[�h���Z�b�g����B���o�[�W�����ł͑S�p�b�h���p�̃X�s�[�h�B
void
JOYPAD_SetRenshaSpeedButton2(
	Sint32	n)
{
	_RenshaSpeedSel = n;

	switch (n)
	{
		case 0: //Off
			_RenshaSpeed[1].button2 = 0;
			break;
		case 1: //High
			_RenshaSpeed[1].button2 = RENSHA_HIGH;
			break;
		case 2: //Middle
			_RenshaSpeed[1].button2 = RENSHA_MIDDLE;
			break;
		case 3: //Low
			_RenshaSpeed[1].button2 = RENSHA_LOW;
			break;
	}

	//�A�˃X�s�[�h����������ƒe���o�Ȃ��\�t�g�̏ꍇ�A�����I�ɑ��x�������Ē�������Bv1.43�ǉ�
	if ((_RenshaSpeed[1].button2 != 0)&&(_RenshaSpeed[1].button2 < _RenshaSpeedMax))
		_RenshaSpeed[1].button2 = _RenshaSpeedMax;
}
//Kitao�ǉ��B�A�˃X�s�[�h���Z�b�g����B���o�[�W�����ł͑S�p�b�h���p�̃X�s�[�h�B
void
JOYPAD_SetRenshaSpeedButtonRun(
	Sint32	n)
{
	_RenshaSpeedSel = n;

	switch (n)
	{
		case 0: //Off
			_RenshaSpeed[1].buttonRun = 0;
			break;
		case 1: //High
			_RenshaSpeed[1].buttonRun = RENSHA_HIGH;
			break;
		case 2: //Middle
			_RenshaSpeed[1].buttonRun = RENSHA_MIDDLE;
			break;
		case 3: //Low
			_RenshaSpeed[1].buttonRun = RENSHA_LOW;
			break;
	}

	//�A�˃X�s�[�h����������ƒe���o�Ȃ��\�t�g�̏ꍇ�A�����I�ɑ��x�������Ē�������Bv1.43�ǉ�
	if ((_RenshaSpeed[1].buttonRun != 0)&&(_RenshaSpeed[1].buttonRun < _RenshaSpeedMax))
		_RenshaSpeed[1].buttonRun = _RenshaSpeedMax;
}
//Kitao�ǉ��B�A�˃X�s�[�h���Z�b�g����B���o�[�W�����ł͑S�p�b�h���p�̃X�s�[�h�B
void
JOYPAD_SetRenshaSpeedButton5(
	Sint32	n)
{
	_RenshaSpeedSel = n;

	switch (n)
	{
		case 0: //Off
			_RenshaSpeed[1].button5 = 0;
			break;
		case 1: //High
			_RenshaSpeed[1].button5 = RENSHA_HIGH;
			break;
		case 2: //Middle
			_RenshaSpeed[1].button5 = RENSHA_MIDDLE;
			break;
		case 3: //Low
			_RenshaSpeed[1].button5 = RENSHA_LOW;
			break;
	}

	//�A�˃X�s�[�h����������ƒe���o�Ȃ��\�t�g�̏ꍇ�A�����I�ɑ��x�������Ē�������Bv1.43�ǉ�
	if ((_RenshaSpeed[1].button5 != 0)&&(_RenshaSpeed[1].button5 < _RenshaSpeedMax))
		_RenshaSpeed[1].button5 = _RenshaSpeedMax;
}
//Kitao�ǉ��B�A�˃X�s�[�h���Z�b�g����B���o�[�W�����ł͑S�p�b�h���p�̃X�s�[�h�B
void
JOYPAD_SetRenshaSpeedButton6(
	Sint32	n)
{
	_RenshaSpeedSel = n;

	switch (n)
	{
		case 0: //Off
			_RenshaSpeed[1].button6 = 0;
			break;
		case 1: //High
			_RenshaSpeed[1].button6 = RENSHA_HIGH;
			break;
		case 2: //Middle
			_RenshaSpeed[1].button6 = RENSHA_MIDDLE;
			break;
		case 3: //Low
			_RenshaSpeed[1].button6 = RENSHA_LOW;
			break;
	}

	//�A�˃X�s�[�h����������ƒe���o�Ȃ��\�t�g�̏ꍇ�A�����I�ɑ��x�������Ē�������Bv1.43�ǉ�
	if ((_RenshaSpeed[1].button6 != 0)&&(_RenshaSpeed[1].button6 < _RenshaSpeedMax))
		_RenshaSpeed[1].button6 = _RenshaSpeedMax;
}


//Kitao�ǉ��B�A�˂̃I���I�t���Z�b�g����B
void
JOYPAD_SetRenshaButton1(
	BOOL	bSet)
{
	int	i;

	if (bSet)
		for (i=1; i<=5; i++)
			_RenshaCount[i].button1 = 1;
	else
		for (i=1; i<=5; i++)
			_RenshaCount[i].button1 = 0;
}
//Kitao�ǉ��B�A�˂̃I���I�t���Z�b�g����B
void
JOYPAD_SetRenshaButton2(
	BOOL	set)
{
	int	i;

	if (set)
		for (i=1; i<=5; i++)
			_RenshaCount[i].button2 = 1;
	else
		for (i=1; i<=5; i++)
			_RenshaCount[i].button2 = 0;
}
//Kitao�ǉ��B�A�˂̃I���I�t���Z�b�g����B
void
JOYPAD_SetRenshaButtonRun(
	BOOL	set)
{
	int	i;

	if (set)
		for (i=1; i<=5; i++)
			_RenshaCount[i].buttonRun = 1;
	else
		for (i=1; i<=5; i++)
			_RenshaCount[i].buttonRun = 0;
}
//Kitao�ǉ��B�A�˂̃I���I�t���Z�b�g����B
void
JOYPAD_SetRenshaButton5(
	BOOL	bSet)
{
	int	i;

	if (bSet)
		for (i=1; i<=5; i++)
			_RenshaCount[i].button5 = 1;
	else
		for (i=1; i<=5; i++)
			_RenshaCount[i].button5 = 0;
}
//Kitao�ǉ��B�A�˂̃I���I�t���Z�b�g����B
void
JOYPAD_SetRenshaButton6(
	BOOL	set)
{
	int	i;

	if (set)
		for (i=1; i<=5; i++)
			_RenshaCount[i].button6 = 1;
	else
		for (i=1; i<=5; i++)
			_RenshaCount[i].button6 = 0;
}


//Kitao�ǉ��B�A�˃X�s�[�h����������ƒe���o�Ȃ��\�t�g�̏ꍇ�A���e�͈͒l��ݒ肷��B
void
JOYPAD_SetRenshaSpeedMax(
	Sint32	n)	//n=1�cHigh�C2=Middle�C3=Low�B
{
	switch (n)
	{
		case 0: //Off
			_RenshaSpeedMax = 0;
			break;
		case 1: //High
			_RenshaSpeedMax = RENSHA_HIGH;
			break;
		case 2: //Middle
			_RenshaSpeedMax = RENSHA_MIDDLE;
			break;
		case 3: //Low
			_RenshaSpeedMax = RENSHA_LOW;
			break;
	}
	JOYPAD_SetRenshaSpeedButton1(_RenshaSpeedSel);
	JOYPAD_SetRenshaSpeedButton2(_RenshaSpeedSel);
	JOYPAD_SetRenshaSpeedButtonRun(_RenshaSpeedSel);
	JOYPAD_SetRenshaSpeedButton5(_RenshaSpeedSel);
	JOYPAD_SetRenshaSpeedButton6(_RenshaSpeedSel);
}


//Kitao�ǉ��B���ݘA�˃��[�h�Ȃ̂���Ԃ��B
BOOL
JOYPAD_GetRenshaButton1()
{
	return (_RenshaCount[1].button1 != 0);
}
//Kitao�ǉ��B���ݘA�˃��[�h�Ȃ̂���Ԃ��B
BOOL
JOYPAD_GetRenshaButton2()
{
	return (_RenshaCount[1].button2 != 0);
}
//Kitao�ǉ��B���ݘA�˃��[�h�Ȃ̂���Ԃ��B
BOOL
JOYPAD_GetRenshaButtonRun()
{
	return (_RenshaCount[1].buttonRun != 0);
}


//Kitao�ǉ��B�ȊԖ����쐬�@�\��L���ɂ��邩�ǂ�����ݒ肷��Bv1.29
void
JOYPAD_SetMakeHesNoSound(
	BOOL	bMakeHesNoSound)
{
	_bMakeHesNoSound = bMakeHesNoSound;
	_bMakeHesNoSoundExecute = FALSE;
}

//Kitao�ǉ�
BOOL
JOYPAD_GetMakeHesNoSound()
{
	return _bMakeHesNoSound;
}


//v2.68�ǉ�
void
JOYPAD_SetEmeraldDragon(
	BOOL	bEmeraldDragon)
{
	_bEmeraldDragon = bEmeraldDragon;
}


// save variable
#define SAVE_V(V)	if (fwrite(&V, sizeof(V), 1, p) != 1)	return FALSE
#define LOAD_V(V)	if (fread(&V, sizeof(V), 1, p) != 1)	return FALSE
// save array
#define SAVE_A(A)	if (fwrite(A, sizeof(A), 1, p) != 1)	return FALSE
#define LOAD_A(A)	if (fread(A, sizeof(A), 1, p) != 1)		return FALSE
/*-----------------------------------------------------------------------------
	[SaveState]
		��Ԃ��t�@�C���ɕۑ����܂��B 
-----------------------------------------------------------------------------*/
BOOL
JOYPAD_SaveState(
	FILE*		p)
{
	if (p == NULL)
		return FALSE;

	SAVE_V(_bSixButtonPad);
	SAVE_V(_bThreeButtonPad); //Kitao�ǉ��Bv0.79

	SAVE_V(_bMultiTap);
	SAVE_V(_bSwapSelRun); //Kitao�ǉ�
	SAVE_V(_bSwapIandII); //Kitao�ǉ�
	SAVE_V(_Counter);
	SAVE_V(_bClearFlg);
	SAVE_V(_bHighNibble);
	SAVE_V(_bSecondByte);

	MOUSE_SaveState(p);
	MB128_SaveState(p);

	SAVE_A(_RenshaCount);
	SAVE_A(_RenshaSpeed);
	SAVE_V(_RenshaSpeedSel); //v1.43

	return TRUE;
}


/*-----------------------------------------------------------------------------
	[LoadState]
		��Ԃ��t�@�C������ǂݍ��݂܂��B 
-----------------------------------------------------------------------------*/
BOOL
JOYPAD_LoadState(
	FILE*		p)
{
	if (p == NULL)
		return FALSE;

	LOAD_V(_bSixButtonPad);
	if (MAINBOARD_GetStateVersion() >= 13) //Kitao�ǉ��Bv0.79�ȍ~�̃Z�[�u�t�@�C���Ȃ�
		LOAD_V(_bThreeButtonPad);
	APP_SetInputConfiguration(); //Kitao�ǉ�

	LOAD_V(_bMultiTap);
	LOAD_V(_bSwapSelRun); //Kitao�ǉ�
	if (MAINBOARD_GetStateVersion() >= 14) //Kitao�ǉ��Bv0.80�ȍ~�̃Z�[�u�t�@�C���Ȃ�
		LOAD_V(_bSwapIandII);
	LOAD_V(_Counter);
	LOAD_V(_bClearFlg);
	LOAD_V(_bHighNibble);
	LOAD_V(_bSecondByte);

	MOUSE_LoadState(p);
	MB128_LoadState(p);

	if (MAINBOARD_GetStateVersion() >= 4) //Kitao�ǉ��Bv0.58�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_A(_RenshaCount);
		LOAD_A(_RenshaSpeed);
	}
	else
		ZeroMemory(_RenshaCount, sizeof(_RenshaCount));
	if (MAINBOARD_GetStateVersion() >= 32) //Kitao�ǉ��Bv1.43�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_RenshaSpeedSel);
	}
	else
	{
		switch (_RenshaSpeed[1].button1)
		{
			case RENSHA_HIGH:
				_RenshaSpeedSel = 1;
				break;
			case RENSHA_MIDDLE:
				_RenshaSpeedSel = 2;
				break;
			case RENSHA_LOW:
				_RenshaSpeedSel = 3;
				break;
			default:
				_RenshaSpeedSel = 0;
				break;
		}
	}
	APP_SetRenshaSpeedSel(_RenshaSpeedSel);
	JOYPAD_SetRenshaSpeedButton1(_RenshaSpeedSel);
	JOYPAD_SetRenshaSpeedButton2(_RenshaSpeedSel);
	JOYPAD_SetRenshaSpeedButtonRun(_RenshaSpeedSel);
	JOYPAD_SetRenshaSpeedButton5(_RenshaSpeedSel);
	JOYPAD_SetRenshaSpeedButton6(_RenshaSpeedSel);
	JOYPAD_UseSixButton(_bSixButtonPad); //v0.91�ǉ��Bv0.91���O�̃Z�[�u�t�@�C���̂��߂ɁA�A�ː�p�{�^���̐ݒ���X�V����B

	return TRUE;
}

#undef SAVE_V
#undef LOAD_V
#undef SAVE_A
#undef LOAD_A
