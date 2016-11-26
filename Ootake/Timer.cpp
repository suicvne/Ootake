/******************************************************************************
Ootake
�ECPU.c����Ăяo���ăN���b�N��i�߂�̂ł͂Ȃ��AVDC.c����APU�Ȃǂƕ��񂵂�1�N
  ���b�N���i�߂�悤�ɂ����B(�����̌���ƃI�[�o�[�N���b�N�@�\���ڂ̂���)
�E���񂵃��[�h��t�����B���̍ۂɉ��܂ő��񂵂ɂȂ��Ă��܂�Ȃ��悤�ɁA�^�C�}�[
  ���荞�݂�x�点�邱�Ƃ��ł���悤�ɂ����Bv0.92�B
�EKi���񂩂�������A�������������@�ɂ��߂�����������B�v���X�P�[���̓�����
  ����(�J�E���^��0����������Ƃ��ł͂Ȃ�512����������u�ԂɊ��荞�݂��N����)��
  ��A����̊��荞�݂�512�N���b�N�Ԃ񑁂���������悤�ɂ����B�����N���b�N�X��
  �T���v�����O�����������ɂȂ��Ă��܂����̂ŁA���ɖ߂����iv0.56�j�B���̎�����
  �d�������������̂��A���ۂ̎��@�ł́u512�N���b�N�̗V�т����ɂ���v�\�����B
  �Ƃ肠�����u�V���v���Ɏ��Ԓʂ�v�ŗǂ������B
�EReloadRegister�����ݒ�̏ꍇ�A�^�C�}�[���荞�݂̓J�E���g�_�E�����Ȃ��悤�ɂ�
  ���B(�Í��`���|�[�Y�������Ƀ��b�T�������������)
�EDownCounter�̃��Z�b�g�́A�R���g���[�����W�X�^��0���������܂ꂽ�Ƃ��ɂ����Ȃ�
  �悤�ɂ����Bv0.69�B
�ETimerRunning���I�t�ł�ReloadRegister���ݒ肳��Ă���΁A�J�E���g�_�E��������
  �Ȃ��悤�ɂ����Bv0.69�B�����̎����ŃN���b�N�X�̃T���v�����O�������@�ɋ߂���
  �����B�ȑO��Ki���񂩂�������A�������������u����̊��荞�݂͑��߂ɋN����v
  ���ۂɂ���v�����B
�EReloadRegister��-1���Ȃ��ق������@�ɋ߂����荞�݊Ԋu�ɂȂ�悤���B�N���b�N�X
  ��_���W�����G�N�X�v���[���[�Ȃǂ̉��F�����@�ɋ߂Â����Ǝv���Bv1.62
�E�^�C�}�[���荞�ݔ����̉񐔂����@��菭�Ȃ������悤�Ȃ̂ŁATimerRunning��FALSE
  �̂Ƃ��̏��������ǂ����B�^���_�]���̃I�[�g�}�b�s���O�\�����̗��ꂪ�قډ����B
  v2.20

Copyright(C)2006-2012 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[Timer.c]
		�^�C�}�[���������܂��D

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
#include "Timer.h"
#include "IntCtrl.h"
#include "MAINBOARD.h"
#include "APP.h"
#include "Printf.h"

/*
	�^�C�}�[�̊��荞�ݎ����F
	21.47727 / 3 / 1024 = 6991.298828125 [Hz] --> 1.430349e-4 [s]
	21.47727 / 3 / 1024 / 128 = 54.6195220947265625 [Hz] --> 0.01830847 [s]

	�^�C�}�͂b�o�t�̓���N���b�N 21.47727 / 3 [MHz] ��
	1024�������ē��삷��D�Ƃ������Ƃ́CCPU��1024�T�C�N��
	���_�E���J�E���^��1�T�C�N���Ɠ������D����āC�_�E���J�E���^��
	�����Ŗ{���̒l��1024�{(<<10)���ĕێ����邱�Ƃɂ���D
*/
static Sint32	_ReloadRegister;
static Sint32	_DownCounter;
static BOOL		_bTimerRunning;


/*-----------------------------------------------------------------------------
** [TIMER_Init]
**   �^�C�}�[�����������܂��D
**---------------------------------------------------------------------------*/
Sint32
TIMER_Init()
{
	_ReloadRegister = 1024; //Kitao�ǉ��Bv2.20
	_DownCounter = 1; //Kitao�ǉ��Bv1.61
	_bTimerRunning = FALSE;
	return 0;
}


/*-----------------------------------------------------------------------------
** [TIMER_Destroy]
**   �^�C�}�[�̏I���������s�Ȃ��܂��D
**---------------------------------------------------------------------------*/
void
TIMER_Deinit()
{
	INTCTRL_Cancel(INTCTRL_TIRQ);
}


/*-----------------------------------------------------------------------------
** [TIMER_Read]
**   �^�C�}�[����̓ǂݏo������ł��D
**---------------------------------------------------------------------------*/
Uint8
TIMER_Read() //Kitao�X�V
{
	return (Uint8)((_DownCounter >> 10) & 0x7F);
}


/*-----------------------------------------------------------------------------
** [TIMER_Write]
**   �^�C�}�[�ւ̏������ݓ���ł��D
**---------------------------------------------------------------------------*/
void
TIMER_Write(
	Uint32		regNum,
	Uint8		data)
{
	switch (regNum & 1)
	{
		case 0:
			//PRINTF("TimerTest %X, %X",regNum,data);//test�p
			//Kitao�X�V�B�V���v����0���Z�b�g������1024�J�E���^�҂��Bv1.62
			//�N���b�N�X�ȂǑ����̃\�t�g�ŉ��F�����@�ɋ߂Â����Ǝv���B�C�[�X�S�̃r�W���A���V�[���̌��p�N�Ɖ����s�b�^���ɁB
			_ReloadRegister = ((data & 0x7F) + 1) * 1024;
			//���̃^�C�~���O�ŃJ�E���^������������悤�ɂ����B�^���_�]���̃I�[�g�}�b�s���O��ʂ̗��ꂪ�قډ����B�H�ɗ��ꂽ�ꍇ�ł��������ŏ����B�����@�ł��H�ɗ����Bv2.20�X�V
			if (!_bTimerRunning) //�^�C�}�[�������Ă��Ȃ������ꍇ
				_DownCounter = _ReloadRegister + 1; //TV�X�|�[�c�o�X�P�Ńt���[�Y�A�}�W�J���`�F�C�X�̖ʃX�^�[�g���Ȃǂł́A�������̂��߃V���v���ɁBv2.65�X�V
			return;

		case 1:
			//PRINTF("TimerTest %X, %X",regNum,data);//test�p
			//�_�E���J�E���^��ݒ�
			//�J�E���g�J�n���́A���̒����TIMER_AdvanceClock�ł���-1������Ă��܂��̂ŁA+1���Ă����B
			//��������Ƃ����炭���@�Ɠ����^�C�~���O�B+1���Ȃ���ROCK-ON�ŉ�����Ȃ��Bv1.62�X�V
			if (!_bTimerRunning) //Kitao�X�V�B�^�C�}�[�������Ă��Ȃ������ꍇ�B�����Ă���Ƃ���DownCounter�����Z�b�g�����"���M�I��"��BGM�̃e���|���x���Ȃ��Ă��܂��Bv2.26�X�V
			{
				if (_DownCounter == 1)
					_DownCounter = _ReloadRegister + 1; //�N���b�N�X�Ń��Z�b�g���K�v�B
			}
			//�^�C�}�[���荞�݃I���I�t�ݒ�
			_bTimerRunning = (data & 1);
			//�^�C�}�[���荞�݂��I�t�ɂ���ꍇ�̏���
			if (!_bTimerRunning)
				_DownCounter = 1; //�N���b�N�X�ŕK�v�Bv2.20
			return;
	}
}


/*-----------------------------------------------------------------------------
	[TIMER_AdvanceClock]
		�w��̂b�o�t�N���b�N���������^�C�}�[������i�߂܂��D
-----------------------------------------------------------------------------*/
//Kitao�X�V�B�i�߂�N���b�N����1�N���b�N�Œ�ɂ����B
void
TIMER_AdvanceClock()
{
	//Kitao�X�V�Bv2.20
	if (--_DownCounter == 0)  //v1.62�X�V�B_ReloadRegister��1024�W���X�g�ɂ����̂ł������W���X�g1024�T�C�N���ɁB1�T�C�N���̈Ⴂ�ŉ��F�ɑ傫�ȈႢ���o��B
	{
		if (_bTimerRunning) //Kitao�ǉ�
		{
			INTCTRL_Request(INTCTRL_TIRQ); //�^�C�}���荞�ݔ���
			_DownCounter = _ReloadRegister;
		}
		else //�^�C�}�[�����j���O���I�t�̂Ƃ��̓J�E���^���ŒZ�l�ɐݒ肵�đ҂悤�ɂ����Bv2.20
			_DownCounter = 1;
	}
}


#define SAVE_V(V)	if (fwrite(&V, sizeof(V), 1, p) != 1)	return FALSE
#define LOAD_V(V)	if (fread(&V, sizeof(V), 1, p) != 1)	return FALSE
/*-----------------------------------------------------------------------------
	[SaveState]
		��Ԃ��t�@�C���ɕۑ����܂��B 
-----------------------------------------------------------------------------*/
BOOL
TIMER_SaveState(
	FILE*		p)
{
	if (p == NULL)
		return FALSE;

	SAVE_V(_DownCounter);
	SAVE_V(_ReloadRegister);
	SAVE_V(_bTimerRunning);

	return TRUE;
}


/*-----------------------------------------------------------------------------
	[LoadState]
		��Ԃ��t�@�C������ǂݍ��݂܂��B 
-----------------------------------------------------------------------------*/
BOOL
TIMER_LoadState(
	FILE*		p)
{
	Sint32	fastForwardingR; //v0.95����p�~�B�_�~�[
	BOOL	bSoundAjust; //v0.95����p�~�B�_�~�[
	BOOL	bUseVideoSpeedUpButton; //v0.95����p�~�B�_�~�[

	if (p == NULL)
		return FALSE;

	LOAD_V(_DownCounter);
	LOAD_V(_ReloadRegister);
	LOAD_V(_bTimerRunning);

	if ((MAINBOARD_GetStateVersion() >= 19)&&
		(MAINBOARD_GetStateVersion() <= 20)) //Kitao�ǉ��Bv0.92�`v0.94�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(fastForwardingR); //�_�~�[
		LOAD_V(bSoundAjust); //�_�~�[
		LOAD_V(bUseVideoSpeedUpButton); //�_�~�[
	}

	return TRUE;
}

#undef SAVE_V
#undef LOAD_V
