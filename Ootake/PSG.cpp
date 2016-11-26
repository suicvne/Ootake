/******************************************************************************
Ootake
�E�L���[�̎Q�Ə������V���v���ɂ����B�e���|�̈��萫����щ����̌���B
�E�I�[�o�[�T���v�����O���Ȃ��悤�ɂ����B�i�M�҂̎�ς����邪�APSG�̏ꍇ�A������
  �����������Ȃ��Ă��܂��P�[�X���������߁B���x�I�ɂ��A�b�v�j
�E�m�C�Y�̉����E���ʂ����@���݂ɒ��������Bv0.72
�E�m�C�Y�̎��g����0x1F���������܂ꂽ�Ƃ��́A0x1E�Ɠ������g���ŉ��ʂ𔼕��ɂ���
  �炷�悤�ɂ����Bv0.68
�E����͍Đ��T���v�����[�g��44.1KHz�Œ�Ƃ����B(CD-DA�Đ����̑��x�A�b�v�̂���)
�EDDA���̔������I�������Ƃ��ɂ����Ȃ�g�`��0�ɂ����A�t�F�[�h�A�E�g������悤��
  ���A�m�C�Y���y�������Bv0.57
�EDDA���[�h(�T���v�����O����)�̂Ƃ��̔g�`�f�[�^�̃m�C�Y�������܂܂�Ă��镔��
  ���J�b�g�����āA�������グ���B���ʂ����߂����Bv0.59
�E�m�C�Y���̉����E���ʂ𒲐����āA���@�̕��͋C�ɋ߂Â����Bv0.68
�EwaveIndex�̏�������DDA���[�h���̓�����������Ď��@�̓���ɋ߂Â����Bv0.63
�EwaveIndex�̏���������wave�e�[�u��������������悤�ɂ����B�t�@�C���[�v�����X
  �����O�A�e�P�g���v���o�g���Ȃǂ̉������@�ɋ߂Â����Bv0.65
�Ewave�̔g�`�̐��������@���l�ɂ����Bv0.74
�Ewave�̍ŏ��l��-14�ɂȂ�悤�ɂ������𐮂����Bv0.74
�E�N���e�B�J���Z�N�V�����͕K�v�Ȃ�(�������݂������ɍs����킯�ł͂Ȃ�)�悤��
  �̂ŁA�ȗ��������������Bv1.09
�E�L���[����(ApuQueue.c)�������ɓ������č����������Bv1.10
�E�ቹ�̈�̃{�����[�����グ�Ď��@���݂̕������₷���ɋ߂Â����Bv1.46
�ELFO�����̂̎����B"�͂ɂ����񂴂�����"��OP��A�t���b�V���n�C�_�[�X�̌��ʉ���
  ���@�̉��ɋ߂Â����Bv1.59

Copyright(C)2006-2013 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[PSG.c]
		�o�r�f���������܂��B

	Implements the PSG.

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
#include <malloc.h>
#include <math.h>
#include "PSG.h"
#include "MainBoard.h" //Kitao�ǉ�
#include "App.h" //Kitao�ǉ�
#include "PRINTF.h" //Kitao�ǉ�


#define N_CHANNEL			6

#define SAMPLE_RATE			44100.0 //Kitao�X�V�B����͑��x�D��ŃT���v�����[�g��44100�Œ�Ƃ����B
#define OVERSAMPLE_RATE		1.0 //Kitao�X�V�BPSG�̓I�[�o�[�T���v�����O����Ƌ����̔����������Ȃ��Ă��܂��̂ŃI�[�o�[�T���v�����O���Ȃ��悤�ɂ����B���x�I�ɂ��A�b�v�B
#define PSG_DECLINE			(20.3149*6.0) //20.3149�BKitao�ǉ��BPSG���ʂ̌����l�B*6.0�͊e�`�����l���������Ԃ������Ӗ��B�傫���قǉ��͌���BCDDA��100%�̂Ƃ��ɂ��傤�Ǘǂ����炢�̉��ʂɍ��킹�悤�Bv2.19,v2.37,v2.39,v2.62�X�V
#define VOL_TABLE_DECLINE	-1.08689999991 //-1.08689999991�Ő��T����QOK�BKitao�ǉ��B���ʃe�[�u���̌����l�B�}�C�i�X���傫���قǏ����������������Â炭�Ȃ�B�}�C�i�X������������ƕ��ʓI�ȉ��ɂȂ�Bv2.19,v2.37,v2.39,v2.40,v2.62,v2.65�X�V
									       //  ��PSG_DECLINE�̒l��ύX�����ꍇ�A���ޗ��̃x�X�g�l���ύX����K�v������B���T����Q(�}�C�i�X����������PSG���ڗ���������ADPCM�������Â炢)�C�喂�E��(�}�C�i�X���������ƃp���`�����肷����),�\���W���[�u���C�h�ŁAPSG_DECLINE=(14.4701*6.0)�Ō��ޗ�-1.0498779900db�O�オ��є����Ă�������(�����̊��Ŏ��)�B
										   //																		  ���g���[�_�[(�}�C�i�X���傫�ڂ�����),�P�X�S�P(�}�C�i�X�����߂�����)�Ȃǂ������Ȓl�ύX�ő傫���ς��B
#define NOISE_TABLE_VALUE	-18 : -1 //�L���ƒ����₷����-18:-1���x�X�g�Ƃ����B�ő�l���傫��(+�ɋ߂�)�Əd�����ɁB�Q�̒l������Ă���Əd�����ɁB�t�H�[���[�V�����T�b�J�[�C�喂�E���̃G���f�B���O�̃h�����ȂǂŒ����Bv1.46,v2.40,v2.62�X�V
									 //  ��VOL_TABLE_DECLINE�ɂ���Ă��̒l�̍œK�l���ω�����B
#define SAMPLE_FADE_DECLINE	 0.305998999951 //0.30599899951�BKitao�ǉ��B�T���v�����O���̏������̉��̌��ޗʁB�\���W���[�u���C�h,�������S�Җ��p�̉����Œ����B��{�I�ɂ��̒l���������ق����m�C�Y������(�t�̃P�[�X������)�Bv2.40
											//							�T���v�����O�h�����̉��F�����܂�̂ő厖�Ȓl�B�l���傫������ƃt�@�C�i���\���W���[��\���W���[�u���C�h,���g���[�_�[�ȂǂŃh����������ڂ��Ȃ�B


/*-----------------------------------------------------------------------------
	[DEV NOTE]

	MAL			--- 0 - 15 (15 �� -0[dB], �P���邲�Ƃ� -3.0 [dB])
	AL			--- 0 - 31 (31 �� -0[dB], �P���邲�Ƃ� -1.5 [dB])
	LAL/RAL		--- 0 - 15 (15 �� -0[dB], �P���邲�Ƃ� -3.0 [dB])

	���̂悤�ɉ��߂��Ȃ����B

	MAL*2		--- 0 - 30 (30 �� -0[dB], �P���邲�Ƃ� -1.5 [dB])
	AL			--- 0 - 31 (31 �� -0[dB], �P���邲�Ƃ� -1.5 [dB])
	LAL/RAL*2	--- 0 - 30 (30 �� -0[dB], �P���邲�Ƃ� -1.5 [dB])


	dB = 20 * log10(OUT/IN)

	dB / 20 = log10(OUT/IN)

	OUT/IN = 10^(dB/20)

	IN(�ő�o��) �� 1.0 �Ƃ���ƁA

	OUT = 10^(dB/20)

					-91 <= -(MAL*2 + AL + LAL(RAL)*2) <= 0

	������A�ł����������́A

		-91 * 1.5 [dB] = -136.5 [dB] = 10^(-136.5/20) ~= 1.496236e-7 [�{]

	�ƂȂ�B

	  1e-7 �I�[�_�[�̒l�́A�Œ菬���_�ŕ\�����悤�Ƃ���ƁA������������
	24 �r�b�g�ȏ�K�v�ŁA�Ȃ����P�U�r�b�g�̉������������߂ɂ� +16�r�b�g
	������ 24+16 = 40�r�b�g�ȏ�K�v�ɂȂ�B����āA32 �r�b�g�̏����n��
	�o�b�d�̉������Œ菬���_�ŕ\������̂͂炢�B�����ŁA�g�`�̌v�Z��
	float �ōs�Ȃ����Ƃɂ���B

	  float ����o�͌`���ɕϊ�����̂͂`�o�t�̎d���Ƃ���B

	[2004.4.28] ����ς� Sint32 �Ŏ������邱�Ƃɂ���(�����Ȓl�͖�������)�B

	  �b�o�t�Ƃo�r�f�͓����h�b�Ƀp�b�P�[�W���Ă���̂����A
	���ۂɂ͂o�r�f�͂b�o�t�̂P�^�Q�̃N���b�N�œ��삷��ƍl���ėǂ��悤���B
	����āA�o�r�f�̓�����g�� Fpsg �́A

		Fpsg = 21.47727 [MHz] / 3 / 2 = 3.579545 [MHz]

	�ƂȂ�B

	���Ƃ��΂R�Q�T���v�����P�����Ƃ���g�`���Đ������Ƃ��A
	���̎��g���̎����ŃT���v�����P���E���o���ƁA

		M = 3579545 / 32 = 111860.78125 [Hz]

	�Ƃ����}�W�b�N�i���o�[��������i�t�@�~�R���Ɠ����j�B
	�������A�Đ����g�����Œ�ł͋Ȃ̉��t���ł��Ȃ��̂ŁA
	FRQ �Ȃ���g���p�����[�^��p���čĐ����g����ω�������B
	FRQ �͂o�r�f�̃��W�X�^�ɏ������܂��P�Q�r�b�g���̃p�����[�^�ŁA
	���œ���ꂽ�}�W�b�N�i���o�[�́u���鐔�v�ɂȂ��Ă���B

	��̂R�Q�T���v�����P�����Ƃ���g�`���Đ������Ƃ��A
	���̔g�`�̎��g�� F �́AFRQ ��p���āA
	
		F = M / FRQ [Hz]  (FRQ != 0)
	
	�ƂȂ�B

	  �o�b�̍Đ��T���v�����O���g���� Fpc [Hz] ���Ƃ���ƁA
	�P�����R�Q�T���v���̔g�`�̍Đ����g�� F2 ��  F2 = Fpc / 32 [Hz]�B
	����āA�o�b�̂P�T���v���ɑ΂��āA�o�b�d�̂P�T���v�����E���o��
	�J�E���^�̐i�ݕ� I ��

		I = F / F2 = 32 * F / Fpc = Fpsg / FRQ / Fpc [�P�ʂȂ�]

	�ƂȂ�B

	[NOISE CHANNEL]

	  �[���m�C�Y�̐����ɂ͂l�n��(maximum length sequence)���p������B
	�l�n��̃r�b�g���͖������ɂ��s���B
	�����ł͉��ɂP�T�r�b�g�Ƃ��Ď������s�Ȃ��B
	�o�͂͂P�r�b�g�ŁAD0 ���[���̂Ƃ��͕��̒l�A�P�̂Ƃ��͐��̒l�Ƃ���B

	�o�b�̂P�T���v���ɑ΂��āA�o�b�d�̂P�T���v�����E���o��
	�J�E���^�̐i�ݕ� I �́A

		I = Fpsg / 64 / FRQ / Fpc  (FRQ != 0)

	�ƂȂ�B

	[�Đ��N�I���e�B����ɂ���] 2004.6.22

	  �G�~�����[�^�ł́A�o�r�f�̃��W�X�^�Ƀf�[�^���������܂��܂ŁA
	���ɔ������ׂ������킩��Ȃ��B���W�X�^�Ƀf�[�^���������܂ꂽ�Ƃ��ɁA
	�T�E���h�o�b�t�@���X�V�������̂����ǁA�����ɂ����݂̎����ł́A
	�T�E���h�o�b�t�@�̍X�V�͕ʃX���b�h�ōs�Ȃ��Ă��āA
	�G�~�����[�V�����X���b�h����C�ӂ̎��ԂɍX�V���邱�Ƃ��ł��Ȃ��B

	  ����܂ł̍Đ��ł́A�T�E���h�o�b�t�@�̍X�V���̃��W�X�^�ݒ�݂̂�
	�L�����������A���ꂾ�ƗႦ�΃T�E���h�o�b�t�@�X�V�̍��ԂɈ�u����
	�o�͂��ꂽ���Ȃǂ���������Ă��܂��B����͓��ɂc�c�`���[�h��m�C�Y��
	���Y���p�[�g�Ƃ��Ďg�p������Ŗ��ɂȂ�B

	  ���W�X�^�ɏ������܂ꂽ�l��������Ɖ����o�͂ɔ��f������ɂ́A
	�ߋ��ɏ������܂ꂽ���W�X�^�̒l(���A�ǂ̃��W�X�^�ɁA�����������܂ꂽ��)
	��ۑ����Ă����āA�T�E���h�o�b�t�@�X�V���ɂ�����Q�Ƃ�����@��
	�l������B�ǂ̂��炢�ߋ��܂Ń��W�X�^�̒l��ۑ����Ă������́A
	�T�E���h�o�b�t�@�̒����ɂ����Ǝv���邪�A�Ƃ肠�����͎��s�����
	���߂邱�Ƃɂ���B

	  �o�r�f���W�X�^�ւ̏������ݓ���̓G�~�����[�V�����X���b�h��
	�s�Ȃ��A�T�E���h�o�b�t�@�X�V�͂��̐�p�X���b�h�ōs�Ȃ���B
	���ꂾ�ƁA�G�~�����[�V�����X���b�h�����W�X�^�̃L���[�ɏ������݂�
	�s�Ȃ��Ă���Œ��ɁA�T�E���h�o�b�t�@�X�V�X���b�h���L���[����
	�ǂݏo�����s�Ȃ��Ă��܂��A�A�N�Z�X���Փ˂���B���̖�����������ɂ́A

		�P�D�T�E���h�o�b�t�@�̍X�V��ʃX���b�h�ōs�Ȃ�Ȃ�
		�Q�D�L���[�̃A�N�Z�X������r�������ɂ���

	�̂Q�Ƃ��肪�l������B�Ƃ肠�����Q�̕��@���Ƃ邱�Ƃɂ���B
---------------------------------------------------------------------------*/


typedef struct
{
	Uint32		frq;
	BOOL		bOn;
	BOOL		bDDA;
	Uint32		volume;
	Uint32		volumeL;
	Uint32		volumeR;
	Sint32		outVolumeL;
	Sint32		outVolumeR;
	Sint32		wave[32];
	Uint32		waveIndex;
	Sint32		ddaSample;
	Uint32		phase;
	Uint32		deltaPhase;
	BOOL		bNoiseOn;
	Uint32		noiseFrq;
	Uint32		deltaNoisePhase;
} PSG;


static PSG			_Psg[8];				// 6, 7 is unused
static Sint32		_DdaFadeOutL[8]; //Kitao�ǉ�
static Sint32		_DdaFadeOutR[8]; //Kitao�ǉ�
static Uint32		_Channel;				// 0 - 5;
static Uint32		_MainVolumeL;			// 0 - 15
static Uint32		_MainVolumeR;			// 0 - 15
static Uint32		_LfoFrq;
static BOOL			_bLfoOn; //v1.59�����g�p�B�ߋ�ver�̃X�e�[�g���[�h�̂��߂Ɏc���Ă���B
static Uint32		_LfoCtrl;
static Uint32		_LfoShift; //v1.59�����g�p�B�ߋ�ver�̃X�e�[�g���[�h�̂��߂Ɏc���Ă���B
static Sint32		_PsgVolumeEffect = 0;//Kitao�ǉ�
static double		_Volume = 0;//Kitao�ǉ�
static double		_VOL = 0.0;//Kitao�ǉ��Bv1.08
static BOOL			_bPsgMute[8] = {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE};//Kitao�ǉ��Bv1.29

static Uint8		_Port[15];				// for debug purpose 

static Sint32		_VolumeTable[92];
static Sint32		_NoiseTable[32768];

static BOOL			_bPsgInit;
static BOOL			_bWaveCrash; //Kitao�ǉ��BDDA�Đ�����Wave�f�[�^������������ꂽ��TRUE
static BOOL			_bHoneyInTheSky; //�͂ɂ����񂴂������p�b�`�p�Bv2.60

//Kitao�X�V�Bv1.10�B�L���[�����������ɓ������č������B
/*
	�`�o�t��p�L���[�̎d�l

	���W�X�^�ɏ������݂��s�Ȃ��邲�ƂɁA
	�L���[�ɂ��̓��e��ǉ�����B

	�T�E���h�o�b�t�@�X�V���Ɍo�ߎ��Ԃ��݂āA
	�ߋ��ɏ������܂ꂽ���W�X�^���e��
	�������܂ꂽ���ɃL���[������o���A
	�o�r�f���W�X�^���X�V����B
	�i�Ȃ��o�r�f���W�X�^�͑S�� write only �Ƃ݂Ȃ�)
	  ���v�m�F

	�L���[�ɒǉ�����Ƃ��ɂ� write index ��p���A
	���o���Ƃ��ɂ� read index ��p����B

	// �ǉ�
	queue[write index++] = written data

	// ���o��
	data = queue[read index++]

	�L���[����l�����o�����Ƃ��� read index ��
	write index �ƈ�v�����Ƃ��� queue underflow�B
	���Ƃ肠�����Ȃɂ����Ȃ��B

	�L���[�ɒl��ǉ������Ƃ��� write index ��
	read index �ƈ�v�����Ƃ��� queue overflow�B
	���Ƃ肠�������Z�b�g���邱�Ƃɂ���B
*/

#define APUQUEUE_SIZE	65536*2				// must be power of 2  v1.61�X�V�B65536���Ƃ`��ԂR���I�[�o�[�N���b�N���ăv���C�����Ƃ��ɑ���Ȃ������B

typedef struct		//Kitao�X�V�Bclock�͔�g�p�Ƃ����Bv1.61����X�e�[�g�Z�[�u�̃T�C�Y�����炷���߂ɕϐ��ォ����J�b�g�B
{
	Uint8			reg;					// 0-15
	Uint8			data;					// written data
} ApuQueue;
typedef struct		//v1.60�ȑO�̃X�e�[�g���[�h�̂��ߎc���Ă���B
{
	Uint32			clock;					// cpu cycles elapsed since previous write  Kitao�X�V�Bclock�͌��ݔ�g�p�B
	Uint8			reg;					// 0-15
	Uint8			data;					// written data
} OldApuQueue;

static ApuQueue				_Queue[APUQUEUE_SIZE];
static Uint32				_QueueWriteIndex;
static Uint32				_QueueReadIndex;


//�{�����[���e�[�u���̍쐬
//Kitao�X�V�B�ቹ�ʂ̉������@��蕷�����Â炢�̂ŁA���ޗ���VOL_TABLE_DECLINE[db](���s���낵���x�X�g�l)�Ƃ��A�m�[�}���C�Y����������悤�ɂ����Bv1.46
//			 �����炭�A���@���A���v��ʂ��ďo�͂����ۂɃm�[�}���C�Y��������Ă���B
static void
create_volume_table()
{
	int		i;
	double	v;

	_VolumeTable[0] = 0; //Kitao�ǉ�
	for (i = 1; i <= 91; i++)
	{
		v = 91 - i;
		_VolumeTable[i] = (Sint32)(32768.0 * pow(10.0, v * VOL_TABLE_DECLINE / 20.0)); //VOL_TABLE_DECLINE�B��������������Ɖ������ʓI�ȌX���ɁB�\���W���[�u���C�h�Œ����Bv1.46�B
	}
}


//�m�C�Y�e�[�u���̍쐬
static void
create_noise_table()
{
	Sint32	i;
	Uint32	bit0;
	Uint32	bit1;
	Uint32	bit14;
	Uint32	reg = 0x100;

	for (i = 0; i < 32768; i++)
	{
		bit0 = reg & 1;
		bit1 = (reg & 2) >> 1;
		bit14 = (bit0 ^ bit1);
		reg >>= 1;
		reg |= (bit14 << 14);
		_NoiseTable[i] = (bit0) ? NOISE_TABLE_VALUE; //Kitao�X�V�B�m�C�Y�̃{�����[���Ɖ����𒲐������B
	}
}


/*-----------------------------------------------------------------------------
	[write_reg]
		�o�r�f�|�[�g�̏������݂ɑ΂��铮����L�q���܂��B
-----------------------------------------------------------------------------*/
static inline void
write_reg(
	Uint8		reg,
	Uint8		data)
{
	Uint32	i;
	Uint32 	frq;//Kitao�ǉ�

	_Port[reg & 15] = data;

	switch (reg & 15)
	{
		case 0:	// register select
			_Channel = data & 7;
			break;

		case 1:	// main volume
			_MainVolumeL = (data >> 4) & 0x0F;
			_MainVolumeR = data & 0x0F;

			/* LMAL, RMAL �͑S�`���l���̉��ʂɉe������ */
			for (i = 0; i < N_CHANNEL; i++)
			{
				_Psg[i].outVolumeL = _VolumeTable[_Psg[i].volume + (_MainVolumeL + _Psg[i].volumeL) * 2];
				_Psg[i].outVolumeR = _VolumeTable[_Psg[i].volume + (_MainVolumeR + _Psg[i].volumeR) * 2];
			}
			break;

		case 2:	// frequency low
			_Psg[_Channel].frq &= ~0xFF;
			_Psg[_Channel].frq |= data;
			//Kitao�X�V�Bupdate_frequency�́A���x�A�b�v�̂��߃T�u���[�`���ɂ������ڎ��s����悤�ɂ����B
			frq = (_Psg[_Channel].frq - 1) & 0xFFF;
			if (frq)
				_Psg[_Channel].deltaPhase = (Uint32)((double)(65536.0 * 256.0 * 8.0 * PSG_FRQ / OVERSAMPLE_RATE / SAMPLE_RATE) / (double)frq +0.5); //Kitao�X�V�B���x�A�b�v�̂���frq�ȊO�͒萔�v�Z�ɂ����B���x����̂��߁A��ɒl�̏�����OVERSAMPLE_RATE�̂ق��Ŋ���悤�ɂ����B+0.5�͎l�̌ܓ��Ő��x�A�b�v�B�v�`�m�C�Y�y���̂��߁B
			else
				_Psg[_Channel].deltaPhase = 0;
			break;

		case 3:	// frequency high
			_Psg[_Channel].frq &= ~0xF00;
			_Psg[_Channel].frq |= (data & 0x0F) << 8;
			//Kitao�X�V�Bupdate_frequency�́A���x�A�b�v�̂��߃T�u���[�`���ɂ������ڎ��s����悤�ɂ����B
			frq = (_Psg[_Channel].frq - 1) & 0xFFF;
			if (frq)
				_Psg[_Channel].deltaPhase = (Uint32)((double)(65536.0 * 256.0 * 8.0 * PSG_FRQ / OVERSAMPLE_RATE / SAMPLE_RATE) / (double)frq +0.5); //Kitao�X�V�B���x�A�b�v�̂���frq�ȊO�͒萔�v�Z�ɂ����B���x����̂��߁A��ɒl�̏�����OVERSAMPLE_RATE�̂ق��Ŋ���悤�ɂ����B+0.5�͎l�̌ܓ��Ő��x�A�b�v�B�v�`�m�C�Y�y���̂��߁B
			else
				_Psg[_Channel].deltaPhase = 0;
			break;

		case 4:	// ON, DDA, AL
			if (_bHoneyInTheSky) //�͂ɂ����񂴂������̃|�[�Y���ɁA�����ȃ{�����[�������^�C�~���O�̖��Ńv�`�m�C�Y���ڂ��Ă��܂��̂ŁA����̓p�b�`�����őΉ��Bv2.60�X�V
			{
				if ((_Psg[_Channel].bOn)&&(data == 0)) //��������data��0�̏ꍇ�ALR�{�����[����0�Ƀ��Z�b�g�B�͂ɂ����񂴂������̃|�[�Y���̃m�C�Y�������B(data & 0x1F)������0�̂Ƃ��Ƀ��Z�b�g����ƁA�T�C�����g�f�o�b�K�[�Y����NG�B�������ĂȂ����Ƀ��Z�b�g����ƃA�g�~�b�N���{��NG�B��2.55
				{
					//PRINTF("test %X %X %X %X",_Channel,_Psg[_Channel].bOn,_MainVolumeL,_MainVolumeR);
					if ((_MainVolumeL & 1) == 0) //���C���{�����[����bit0��0�̂Ƃ���������(�͂ɂ����񂴂������ŃC���M�����[��0xE�B���̃Q�[����0xF�B���w�r�[���j�b�g��0xE������)�B���ꂪ�Ȃ��ƃ~�Y�o�N��`���ŉ����o�Ȃ��B���@�̎d�g�݂Ɠ������ǂ����͖��m�F�Bv2.53�ǉ�
						_Psg[_Channel].volumeL = 0;
					if ((_MainVolumeR & 1) == 0) //�E�`�����l�������l�Ƃ���
						_Psg[_Channel].volumeR = 0;
				}
			}

			_Psg[_Channel].bOn = ((data & 0x80) != 0);
			if ((_Psg[_Channel].bDDA)&&((data & 0x40)==0)) //DDA����WAVE�֐؂�ւ��Ƃ� or DDA�����������Ƃ�
			{
				//Kitao�ǉ��BDDA�͂����Ȃ��������Ɩڗ��m�C�Y���ڂ�̂Ńt�F�[�h�A�E�g����B
				_DdaFadeOutL[_Channel] = (Sint32)((double)(_Psg[_Channel].ddaSample * _Psg[_Channel].outVolumeL) *
												  ((1 + (1 >> 3) + (1 >> 4) + (1 >> 5) + (1 >> 7) + (1 >> 12) + (1 >> 14) + (1 >> 15)) * SAMPLE_FADE_DECLINE)); //���̉��ʁBv2.65�X�V
				_DdaFadeOutR[_Channel] = (Sint32)((double)(_Psg[_Channel].ddaSample * _Psg[_Channel].outVolumeR) *
												  ((1 + (1 >> 3) + (1 >> 4) + (1 >> 5) + (1 >> 7) + (1 >> 12) + (1 >> 14) + (1 >> 15)) * SAMPLE_FADE_DECLINE));

			}
			_Psg[_Channel].bDDA = ((data & 0x40) != 0);
			
			//Kitao�ǉ��Bdata��bit7,6��01�̂Ƃ���Wave�C���f�b�N�X�����Z�b�g����B
			//DDA���[�h����Wave�f�[�^����������ł����ꍇ�͂�����Wave�f�[�^���C���i�������j����B�t�@�C���[�v�����X�����O�B
			if ((data & 0xC0) == 0x40)
			{
				_Psg[_Channel].waveIndex = 0;
				if (_bWaveCrash)
				{
					for (i=0; i<32; i++)
						_Psg[_Channel].wave[i] = -14; //Wave�f�[�^���ŏ��l�ŏ�����
					_bWaveCrash = FALSE;
				}
			}

			_Psg[_Channel].volume = data & 0x1F;
			_Psg[_Channel].outVolumeL = _VolumeTable[_Psg[_Channel].volume + (_MainVolumeL + _Psg[_Channel].volumeL) * 2];
			_Psg[_Channel].outVolumeR = _VolumeTable[_Psg[_Channel].volume + (_MainVolumeR + _Psg[_Channel].volumeR) * 2];
			break;

		case 5:	// LAL, RAL
			_Psg[_Channel].volumeL = (data >> 4) & 0xF;
			_Psg[_Channel].volumeR = data & 0xF;
			_Psg[_Channel].outVolumeL = _VolumeTable[_Psg[_Channel].volume + (_MainVolumeL + _Psg[_Channel].volumeL) * 2];
			_Psg[_Channel].outVolumeR = _VolumeTable[_Psg[_Channel].volume + (_MainVolumeR + _Psg[_Channel].volumeR) * 2];
			break;

		case 6:	// wave data  //Kitao�X�V�BDDA���[�h�̂Ƃ���Wave�f�[�^���X�V����悤�ɂ����Bv0.63�B�t�@�C���[�v�����X�����O
			data &= 0x1F;
			_bWaveCrash = FALSE; //Kitao�ǉ�
			if (!_Psg[_Channel].bOn) //Kitao�ǉ��B����炵�Ă��Ȃ��Ƃ�����Wave�f�[�^���X�V����Bv0.65�BF1�g���v���o�g���̃G���W�����B
			{
				_Psg[_Channel].wave[_Psg[_Channel].waveIndex++] = 17 - data; //17�BKitao�X�V�B��ԐS�n�悭�����l�ɁB�~�Y�o�N��`���C���g���[�_�[�C�h���S���X�s���b�g���Œ����B
				_Psg[_Channel].waveIndex &= 0x1F;
			}
			if (_Psg[_Channel].bDDA)
			{
				//Kitao�X�V�B�m�C�Y�y���̂���6��艺���̒l�̓J�b�g����悤�ɂ����Bv0.59
				if (data < 6) //�T�C�o�[�i�C�g��6�Ɍ���
					data = 6; //�m�C�Y�������̂ŏ����Ȓl�̓J�b�g
				_Psg[_Channel].ddaSample = 11 - data; //�T�C�o�[�i�C�g��11�Ɍ���B�h�����̉��F���œK�Bv0.74
			
				if (!_Psg[_Channel].bOn) //DDA���[�h����Wave�f�[�^�������������ꍇ
					_bWaveCrash = TRUE;
			}
			break;

		case 7:	// noise on, noise frq
			if (_Channel >= 4)
			{
				_Psg[_Channel].bNoiseOn = ((data & 0x80) != 0);
				_Psg[_Channel].noiseFrq = 0x1F - (data & 0x1F);
				if (_Psg[_Channel].noiseFrq == 0)
					_Psg[_Channel].deltaNoisePhase = (Uint32)((double)(2048.0 * PSG_FRQ / OVERSAMPLE_RATE / SAMPLE_RATE) +0.5); //Kitao�X�V
				else
					_Psg[_Channel].deltaNoisePhase = (Uint32)((double)(2048.0 * PSG_FRQ / OVERSAMPLE_RATE / SAMPLE_RATE) / (double)_Psg[_Channel].noiseFrq +0.5); //Kitao�X�V
			}
			break;

		case 8:	// LFO frequency
			_LfoFrq = data;
			//Kitao�e�X�g�p
			//PRINTF("LFO Frq = %X",_LfoFrq);
			break;

		case 9:	// LFO control  Kitao�X�V�B�V���v���Ɏ������Ă݂��B���@�œ������삩�͖��m�F�B�͂ɂ����񂴂������̉�������悤�Ɏ����Bv1.59
			if (data & 0x80) //bit7�𗧂ĂČĂԂƋ��炭���Z�b�g
			{
				_Psg[1].phase = 0; //LfoFrq�͏��������Ȃ��B�͂ɂ����񂴂������B
				//Kitao�e�X�g�p
				//PRINTF("LFO control = %X",data);
			}
			_LfoCtrl = data & 7; //�h���b�v���b�N�ق�z����5���g����Bv1.61�X�V
			if (_LfoCtrl & 4)
				_LfoCtrl = 0; //�h���b�v���b�N�ق�z���B���@�Œ�����������LFO�I�t�Ɠ������̂悤�Ȃ̂�bit2�������Ă���(���̐������H)��0�Ɠ������ƂƂ���B
			//Kitao�e�X�g�p
			//PRINTF("LFO control = %X,  Frq =%X",data,_LfoFrq);
			break;

		default:	// invalid write
			break;
	}

	return;
}


//Kitao�ǉ�
static void
set_VOL()
{
	Sint32	v;

	if (_PsgVolumeEffect == 0)
		_VOL = 0.0; //�~���[�g
	else if (_PsgVolumeEffect == 3)
		_VOL = _Volume / (double)(OVERSAMPLE_RATE * 4.0/3.0); // 3/4�Bv1.29�ǉ�
	else
		_VOL = _Volume / (double)(OVERSAMPLE_RATE * _PsgVolumeEffect); //Kitao�ǉ��B_PsgVolumeEffect=�{�����[�����ߌ��ʁB

	if (!APP_GetCDGame()) //Hu�J�[�h�Q�[���̂Ƃ������A�{�����[��101�`120��L�����Bv2.62
	{
		v = APP_GetWindowsVolume();
		if (v > 100)
			_VOL *= ((double)(v-100) * 3.0 + 100.0) / 100.0; //101�`120�͒ʏ��3.0�{�̉��ʕω��B3.0�{��Vol120�Ń\���W���[�u���C�h�œK�B�r�b�N���}�����[���hOK�B3.1�{�ȏゾ�Ɖ��������Ȃ違������̐S�z������B
	}
}

//v2.73�X�V
static inline void
inc_phase(
	Sint32		i)
{
	Sint32		lfo;

	if ((i==0)&&(_LfoCtrl>0))
	{
		//_LfoCtrl��1�̂Ƃ���0��V�t�g(���̂܂�)�ŁA�͂ɂ����񂴂����������@�̉��ɋ߂��B
		//_LfoCtrl��3�̂Ƃ���4��V�t�g�ŁA�t���b�V���n�C�_�[�X�����@�̉��ɋ߂��B
		lfo = _Psg[1].wave[_Psg[1].phase >> 27] << ((_LfoCtrl-1) << 1); //v1.60�X�V
		_Psg[0].phase += (Uint32)((double)(65536.0 * 256.0 * 8.0 * PSG_FRQ / OVERSAMPLE_RATE / SAMPLE_RATE) / (double)(_Psg[0].frq + lfo) +0.5);
		_Psg[1].phase += (Uint32)((double)(65536.0 * 256.0 * 8.0 * PSG_FRQ / OVERSAMPLE_RATE / SAMPLE_RATE) / (double)(_Psg[1].frq * _LfoFrq) +0.5); //v1.60�X�V
	}
	else
		_Psg[i].phase += _Psg[i].deltaPhase;
}

/*-----------------------------------------------------------------------------
	[Mix]
		�o�r�f�̏o�͂��~�b�N�X���܂��B
-----------------------------------------------------------------------------*/
void
PSG_Mix(
	Sint16*		pDst,		// �o�͐�o�b�t�@ //Kitao�X�V�BPSG��p�o�b�t�@�ɂ�������Sint16�ɁB
	Sint32		nSample)	// �����o���T���v���� 
{
	Sint32		i;
	Sint32		j;
	//Sint32		k; //Kitao�ǉ�
	Sint32		sample; //Kitao�ǉ�
	Sint32		sampleAllL; //Kitao�ǉ��B6ch�Ԃ�̃T���v���𑫂��Ă������߂̃o�b�t�@�B���x���ێ����邽�߂ɕK�v�B6ch�Ԃ񍇌v���I�������ɁA�����Sint16�ɕϊ����ď������ނ悤�ɂ����B
	Sint32		sampleAllR; //Kitao�ǉ��B��̂q�`�����l���p
	Sint32		smp; //Kitao�ǉ��BDDA����,�m�C�Y���ʌv�Z�p

	if (!_bPsgInit)
		return;

	for (j=0; j<nSample; j++)
	{
		sampleAllL = 0;
		sampleAllR = 0;
		for (i=0; i<N_CHANNEL; i++)
		{
			if ((_Psg[i].bOn)&&((i != 1)||(_LfoCtrl == 0))&&(!_bPsgMute[i])) //Kitao�X�V
			{
				if (_Psg[i].bDDA)
				{
					smp = _Psg[i].ddaSample * _Psg[i].outVolumeL;
					//smp = _Psg[i].ddaSample * _Psg[i].outVolumeL * (Sint32)OVERSAMPLE_RATE; //�I�[�o�[�T���v�����O�p
					sampleAllL += smp + (smp >> 3) + (smp >> 4) + (smp >> 5) + (smp >> 7) + (smp >> 12) + (smp >> 14) + (smp >> 15); //Kitao�X�V�B�T���v�����O���̉��ʂ����@���݂ɒ����Bv2.39,v2.40,v2.62,v2.65�Ē��������B
					smp = _Psg[i].ddaSample * _Psg[i].outVolumeR;
					//smp = _Psg[i].ddaSample * _Psg[i].outVolumeR * (Sint32)OVERSAMPLE_RATE; //�I�[�o�[�T���v�����O�p
					sampleAllR += smp + (smp >> 3) + (smp >> 4) + (smp >> 5) + (smp >> 7) + (smp >> 12) + (smp >> 14) + (smp >> 15); //Kitao�X�V�B�T���v�����O���̉��ʂ����@���݂ɒ����Bv2.39,v2.40,v2.62,v2.65�Ē��������B
				}
				else if (_Psg[i].bNoiseOn)
				{
					sample = _NoiseTable[_Psg[i].phase >> 17];
					_Psg[i].phase += _Psg[i].deltaNoisePhase; //Kitao�X�V
					/*
					for (k = 2; k<=OVERSAMPLE_RATE; k++) //�I�[�o�[�T���v�����O�p
					{
						sample += _NoiseTable[_Psg[i].phase>>17];
						_Psg[i].phase += _Psg[i].deltaNoisePhase;
					}
					*/
					
					if (_Psg[i].noiseFrq == 0) //Kitao�ǉ��BnoiseFrq=0(data��0x1F���������܂ꂽ)�̂Ƃ��͉��ʂ��ʏ�̔����Ƃ����B�i�t�@�C���[�v�����X�����O�R�A�p�b�N�����h�A�����Y�����A����΂�S���t�{�[�C�Y�Ȃǁj
					{
						smp = sample * _Psg[i].outVolumeL;
						sampleAllL += (smp >> 1) + (smp >> 12) + (smp >> 14); //(1/2 + 1/4096 + (1/32768 + 1/32768))
						smp = sample * _Psg[i].outVolumeR;
						sampleAllR += (smp >> 1) + (smp >> 12) + (smp >> 14);
					}
					else //�ʏ�
					{
						smp = sample * _Psg[i].outVolumeL;
						sampleAllL += smp + (smp >> 11) + (smp >> 14) + (smp >> 15); //Kitao�X�V�B�m�C�Y�̉��ʂ����@���݂ɒ���(1 + 1/2048 + 1/16384 + 1/32768)�B����"+1/32768"�Ő▭(��ρB�喂�E��,�\���W���[�u���C�h�Ȃ�)�ɂȂ�Bv2.62�X�V
						smp = sample * _Psg[i].outVolumeR;
						sampleAllR += smp + (smp >> 11) + (smp >> 14) + (smp >> 15); //Kitao�X�V�B�m�C�Y�̉��ʂ����@���݂ɒ���
					}
				}
				else if (_Psg[i].deltaPhase)
				{
					//Kitao�X�V�B�I�[�o�[�T���v�����O���Ȃ��悤�ɂ����B
					sample = _Psg[i].wave[_Psg[i].phase >> 27];
					inc_phase(i); //v2.73�X�V
					/*
					for (k = 2; k<=OVERSAMPLE_RATE; k++) //�I�[�o�[�T���v�����O�p
					{
						sample += _Psg[i].wave[_Psg[i].phase >> 27];
						inc_phase(i); //v2.73�X�V
					}
					*/
					if (_Psg[i].frq < 128)
						sample -= sample >> 2; //����g��̉��ʂ𐧌��B�u���b�h�M�A�̃X�^�[�g���ȂǂŎ��@�Ɠ��l�̉��ɁB�\���W���[�u���C�h�Ȃǂ����@�ɋ߂��Ȃ����Bv2.03

					sampleAllL += sample * _Psg[i].outVolumeL; //Kitao�X�V
					sampleAllR += sample * _Psg[i].outVolumeR; //Kitao�X�V
				}
			}
			//Kitao�ǉ��BDDA�������̓m�C�Y�y���̂��߃t�F�[�h�A�E�g�ŏ�������B
			//			 �x���{�[�}��(�u�킵���΂����͂�������v���琔�b��)��p���[�e�j�X(�^�C�g���ȏI�����琔�b��B�_���R�[��)�C�������S�Җ��p(����)���Ō��ʂ���B
			if (_DdaFadeOutL[i] > 0)
				--_DdaFadeOutL[i];
			else if (_DdaFadeOutL[i] < 0)
				++_DdaFadeOutL[i];
			if (_DdaFadeOutR[i] > 0)
				--_DdaFadeOutR[i];
			else if (_DdaFadeOutR[i] < 0)
				++_DdaFadeOutR[i];
			sampleAllL += _DdaFadeOutL[i];
			//sampleAllL += _DdaFadeOutL[i] * OVERSAMPLE_RATE; //�I�[�o�[�T���v�����O�p
			sampleAllR += _DdaFadeOutR[i];
			//sampleAllR += _DdaFadeOutR[i] * OVERSAMPLE_RATE; //�I�[�o�[�T���v�����O�p
		}
		//Kitao�X�V�B6ch���킳�����Ƃ���ŁA�{�����[���������ăo�b�t�@�ɏ������ށB�I�[�o�[�T���v�����O(�����ݔ�g�p)�����Ԃ��_VOL�ɂ���Ă����Ŋ����Ē��������B
		sampleAllL = (Sint32)((double)sampleAllL * _VOL);
		//if ((sampleAllL>32767)||(sampleAllL<-32768)) PRINTF("PSG Sachitta!");//test�p
		if (sampleAllL> 32767) sampleAllL= 32767; //Vol���A�b�v�����̂ŃT�`���[�V�����`�F�b�N���K�v�Bv2.39
		if (sampleAllL<-32768) sampleAllL=-32768; //  �p�b�N�����h��UFO���ɂ��ꂽ�Ƃ����炢�ŁA�ʏ�̃Q�[���ł͋N����Ȃ��B���ʂ̑傫�ȃr�b�N���}�����[���h��OK�B�p�b�N�����h���ʏ��OK�ŃT�`���[�V���������Ƃ��ł��킸���Ȃ̂ŉ����I�ɑ��v�B
												  //  �Ȃ̂ŉ����I�ɂ́APSG���Q��DirectX�`�����l���ɕ����Ė炷�ׂ�(�����͏d���Ȃ�)�����A����̓p�b�N�����h�ł��T�`���[�V�������������ŉ����I�ɖ��Ȃ�(���x�D��)�Ƃ���B
		sampleAllR = (Sint32)((double)sampleAllR * _VOL);
		//if ((sampleAllR>32767)||(sampleAllR<-32768)) PRINTF("PSG Satitta!");//test�p
		if (sampleAllR> 32767) sampleAllR= 32767; //Vol���A�b�v�����̂ŃT�`���[�V�����`�F�b�N���K�v�Bv2.39
		if (sampleAllR<-32768) sampleAllR=-32768; //
		*pDst++ = (Sint16)(sampleAllL);
		*pDst++ = (Sint16)(sampleAllR);
		
		//�L���[���Q�Ƃ�PSG���W�X�^���X�V����BKitao�X�V�B�������̂��߃T�u���[�`���ɂ��������ŏ����B�L���[�̎Q�Ƃ̓V���v���ɂ���(�e���|�̈��萫����)�B
		while (_QueueReadIndex != _QueueWriteIndex) //v1.10�X�V�B�L���[�����������֓������������B
		{
			write_reg(_Queue[_QueueReadIndex].reg, _Queue[_QueueReadIndex].data);
			_QueueReadIndex++; //Kitao�X�V
			_QueueReadIndex &= APUQUEUE_SIZE-1; //Kitao�X�V
		}
	}
}


//Kitao�X�V
static void
psg_reset()
{
	int		i,j;

	memset(_Psg, 0, sizeof(_Psg));
	memset(_DdaFadeOutL, 0, sizeof(_DdaFadeOutL)); //Kitao�ǉ�
	memset(_DdaFadeOutR, 0, sizeof(_DdaFadeOutR)); //Kitao�ǉ�
	_MainVolumeL = 0;
	_MainVolumeR = 0;
	_LfoFrq = 0;
	_LfoCtrl = 0;
	_Channel = 0; //Kitao�ǉ��Bv2.65
	_bWaveCrash = FALSE; //Kitao�ǉ�

	//Kitao�X�V�Bv0.65�Dwave�f�[�^���������B
	for (i=0; i<N_CHANNEL; i++)
		for (j=0; j<32; j++)
			_Psg[i].wave[j] = -14; //�ŏ��l�ŏ������B�t�@�C�v���C�t�H�[���[�V�����T�b�J�['90�CF1�g���v���o�g���ŕK�v�B
	for (j=0; j<32; j++)
		_Psg[3].wave[j] = 17; //ch3�͍ő�l�ŏ������BF1�g���v���o�g���Bv2.65

	//Kitao�X�V�Bv1.10�B�L���[�����������ɓ���
	_QueueWriteIndex = 0;
	_QueueReadIndex  = 0;
}


/*-----------------------------------------------------------------------------
	[Init]
		�o�r�f�����������܂��B
-----------------------------------------------------------------------------*/
Sint32
PSG_Init(
	Sint32		sampleRate)
{
	PSG_SetVolume(APP_GetPsgVolume());//Kitao�ǉ�

	psg_reset();

	create_volume_table();
	create_noise_table();

	PSG_SetSampleRate(sampleRate);

	_bPsgInit = TRUE;

	return 0;
}


/*-----------------------------------------------------------------------------
	[SetSampleRate]
-----------------------------------------------------------------------------*/
void
PSG_SetSampleRate(
	Uint32		sampleRate)
{
	//_SampleRate = sampleRate;
}


/*-----------------------------------------------------------------------------
	[Deinit]
		�o�r�f��j�����܂��B
-----------------------------------------------------------------------------*/
void
PSG_Deinit()
{
	memset(_Psg, 0, sizeof(_Psg));
	memset(_DdaFadeOutL, 0, sizeof(_DdaFadeOutL)); //Kitao�ǉ�
	memset(_DdaFadeOutR, 0, sizeof(_DdaFadeOutR)); //Kitao�ǉ�
	_MainVolumeL = 0;
	_MainVolumeR = 0;
	_LfoFrq = 0;
	_LfoCtrl = 0;
	_bWaveCrash = FALSE; //Kitao�ǉ�
	_bPsgInit = FALSE;
}


/*-----------------------------------------------------------------------------
	[Read]
		�o�r�f�|�[�g�̓ǂݏo���ɑ΂��铮����L�q���܂��B
-----------------------------------------------------------------------------*/
Uint8
PSG_Read(
	Uint32	regNum)
{
	if (regNum == 0)
		return (Uint8)_Channel;

	return _Port[regNum & 15];
}


/*-----------------------------------------------------------------------------
	[Write]
		�o�r�f�|�[�g�̏������݂ɑ΂��铮����L�q���܂��B
-----------------------------------------------------------------------------*/
void
PSG_Write(
	Uint32		regNum,
	Uint8		data)
{
	//v1.10�X�V�B�L���[�����������ɓ������č������B
	//Kitao�X�V�Bclock�͍l�������ɃV���v���ɂ��č����������B
	if (((_QueueWriteIndex + 1) & (APUQUEUE_SIZE-1)) == _QueueReadIndex)
	{
		PRINTF("PSG Queue Over!"); // �L���[�����^��
		return;
	}
	_Queue[_QueueWriteIndex].reg   = (Uint8)(regNum & 15);
	_Queue[_QueueWriteIndex].data  = data;
	_QueueWriteIndex++; //Kitao�X�V
	_QueueWriteIndex &= APUQUEUE_SIZE-1; //Kitao�X�V
}


Sint32
PSG_AdvanceClock(
	Sint32		clock)
{
	return 0;
}


//Kitao�ǉ��BPSG�̃{�����[�����ʂɐݒ�\�ɂ����B
void
PSG_SetVolume(
	Uint32	volume)		// 0 - 65535
{
	if (volume < 0)	volume = 0;
	if (volume > 65535)	volume = 65535;

	_Volume = (double)volume / 65535.0 / PSG_DECLINE;
	set_VOL();
}

//Kitao�ǉ��B�{�����[���~���[�g�A�n�[�t�Ȃǂ��ł���悤�ɂ����B
void
PSG_SetVolumeEffect(
	Uint32	volumeEffect)
{
	_PsgVolumeEffect = (Sint32)volumeEffect; //�����l���傫���قǃ{�����[���͏������Ȃ�
	set_VOL();
}


//Kitao�ǉ�
void
PSG_ResetVolumeReg()
{
	int	i;

	_MainVolumeL = 0;
	_MainVolumeR = 0;
	for (i = 0; i < N_CHANNEL; i++)
	{
		_Psg[i].volume = 0;
		_Psg[i].outVolumeL = 0;
		_Psg[i].outVolumeR = 0;
		_DdaFadeOutL[i] = 0;
		_DdaFadeOutR[i] = 0;
	}
}


//Kitao�ǉ�
void
PSG_SetMutePsgChannel(
	Sint32	num,
	BOOL	bMute)
{
	_bPsgMute[num] = bMute;
	if (bMute)
	{
		_DdaFadeOutL[num] = 0;
		_DdaFadeOutR[num] = 0;
	}
}

//Kitao�ǉ�
BOOL
PSG_GetMutePsgChannel(
	Sint32	num)
{
	return _bPsgMute[num];
}

//Kitao�ǉ��Bv2.60
void
PSG_SetHoneyInTheSky(
	BOOL	bHoneyInTheSky)
{
	_bHoneyInTheSky = bHoneyInTheSky;
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
PSG_SaveState(
	FILE*		p)
{
	BOOL	bFlashHiders = FALSE; //Kitao�X�V�B���ݔ�g�p�B���o�[�W�����̃X�e�[�g�Z�[�u�Ƃ̌݊��̂���

	if (p == NULL)
		return FALSE;

	SAVE_A(_Psg);

	SAVE_V(_Channel);
	SAVE_V(_MainVolumeL);
	SAVE_V(_MainVolumeR);
	SAVE_V(_LfoFrq);
	SAVE_V(_bLfoOn); //v1.59�����g�p�ɁB
	SAVE_V(_LfoCtrl);
	SAVE_V(_LfoShift); //v1.59�����g�p�ɁB
	SAVE_V(_bWaveCrash); //Kitao�ǉ��Bv0.65

	SAVE_V(bFlashHiders); //Kitao�ǉ��Bv0.62

	//v1.10�ǉ��B�L���[�����������֓����B
	SAVE_A(_Queue); //v1.61����T�C�Y���Q�{�ɂȂ����B
	SAVE_V(_QueueWriteIndex);
	SAVE_V(_QueueReadIndex);

	return TRUE;
}


/*-----------------------------------------------------------------------------
	[LoadState]
		��Ԃ��t�@�C������ǂݍ��݂܂��B 
-----------------------------------------------------------------------------*/
BOOL
PSG_LoadState(
	FILE*		p)
{
	Uint32			i;
	double			clockCounter; //Kitao�X�V�B���ݔ�g�p�B���o�[�W�����̃X�e�[�g�Z�[�u�Ƃ̌݊��̂���
	BOOL			bInit; //Kitao�X�V�B���ݔ�g�p�B���o�[�W�����̃X�e�[�g�Z�[�u�Ƃ̌݊��̂���
	Sint32			totalClockAdvanced; //Kitao�X�V�B���ݔ�g�p�B���o�[�W�����̃X�e�[�g�Z�[�u�Ƃ̌݊��̂���
	BOOL			bFlashHiders; //Kitao�X�V�B���ݔ�g�p�B���o�[�W�����̃X�e�[�g�Z�[�u�Ƃ̌݊��̂���
	OldApuQueue		oldQueue[65536]; //v1.60�ȑO�̃X�e�[�g��ǂݍ��ݗp�B
	

	if (p == NULL)
		return FALSE;

	LOAD_A(_Psg);

	LOAD_V(_Channel);
	LOAD_V(_MainVolumeL);
	LOAD_V(_MainVolumeR);
	LOAD_V(_LfoFrq);
	LOAD_V(_bLfoOn); //v1.59�����g�p�ɁB
	LOAD_V(_LfoCtrl);
	if (MAINBOARD_GetStateVersion() >= 3) //Kitao�ǉ��Bv0.57�ȍ~�̃Z�[�u�t�@�C���Ȃ�
		LOAD_V(_LfoShift); //v1.59�����g�p�ɁB
	if (MAINBOARD_GetStateVersion() >= 9) //Kitao�ǉ��Bv0.65�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_bWaveCrash);
	}
	else
		_bWaveCrash = FALSE;

	if (MAINBOARD_GetStateVersion() >= 7) //Kitao�ǉ��Bv0.62�ȍ~�̃Z�[�u�t�@�C���Ȃ�
		LOAD_V(bFlashHiders);

	//v1.10�ǉ��B�L���[�����������֓����Bv1.61�X�V
	if (MAINBOARD_GetStateVersion() >= 34) //v1.61beta�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_A(_Queue); //v1.61����T�C�Y���Q�{��clock�������폜�����B
		LOAD_V(_QueueWriteIndex);
		LOAD_V(_QueueReadIndex);
	}
	else //v1.60�ȑO�̃L���[(��)�o�[�W�����̃X�e�[�g�̏ꍇ�A�V�o�[�W�����̕��ɍ����悤�ɕϊ��B
	{
		LOAD_A(oldQueue);
		LOAD_V(_QueueWriteIndex);
		LOAD_V(_QueueReadIndex);
		if (_QueueWriteIndex >= _QueueReadIndex)
		{
			for (i=_QueueReadIndex; i<=_QueueWriteIndex; i++)
			{
				_Queue[i].reg  = oldQueue[i].reg;
				_Queue[i].data = oldQueue[i].data;
			}
		}
		else //Write�̈ʒu��Read�̈ʒu�����O�i65536�n�_���܂����Ńf�[�^�����݂��Ă���Ƃ��j�̏ꍇ
		{
			for (i=_QueueReadIndex; i<=65535; i++)
			{
				_Queue[i].reg  = oldQueue[i].reg;
				_Queue[i].data = oldQueue[i].data;
			}
			for (i=0; i<=_QueueWriteIndex; i++)
			{
				_Queue[65536+i].reg  = oldQueue[i].reg;
				_Queue[65536+i].data = oldQueue[i].data;
			}
			_QueueWriteIndex += 65536;
		}
	}
	if (MAINBOARD_GetStateVersion() < 26) //Kitao�ǉ��Bv1.11���O�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(clockCounter); //���ݔ�g�p�Bv0.95
		LOAD_V(bInit); //���ݔ�g�p�Bv1.10
		LOAD_V(totalClockAdvanced); //���ݔ�g�p�Bv0.95
	}

	return TRUE;
}

#undef SAVE_V
#undef SAVE_A
#undef LOAD_V
#undef LOAD_A

