/******************************************************************************
Ootake
�E���s�[�g�Đ����ɒ�~���߂������ꍇ�́A�����ɒ�~�����ɂP��Ō�܂ōĐ������
  ���ɂ����B�i�X�`�[���n�[�c�Ŋm�F�BADPCM�̃��s�[�g�́A���s�[�g�Đ��ƌ������
  �́A�Đ������܂ŉ����~�߂Ȃ��悤�ɂ���t���O�Ƃ��ċ@�\���Ă���悤���j
�E�f�R�[�h�͍Đ������������s���悤�ɂ����B�v���f�R�[�h���s�v�ɂȂ�A���V���v
  ���Ȏ����ɂ����Bv0.60
�E����͍Đ��T���v�����O���[�g��44.1KHz�ɌŒ肵���B(���x�A�b�v)
�EADPCM�̔������I�������Ƃ��ɂ����Ȃ�g�`��0�ɂ����A�t�F�[�h�A�E�g������悤��
  ���A�m�C�Y���y�������Bv0.57
�E�A���Đ����ɋN����m�C�Y������邽��ad_ref_index�͊��S�ɏ��������܂ł̓��Z
  �b�g���Ȃ��悤�ɂ����Bv0.60
�Ev0.61�B���X�g�n���}�Q�h���A�V���[���b�N�z�[���Y��ADPCM�Đ��ɑΉ������B����X
  �[�p�[CD-ROM2�\�t�g�͊F���̌X��������̂��ǂ������m�F�B����ADPCM���g���m�[�}
  ��CD-ROM�\�t�g�ł��������K�v�B�Ƃ肠�������̂Q��(���X�}�Q�{�z�[���Y2��)���N
  �����ꂽ�Ƃ������A���ʓ���Ƃ��ď�������悤�ɂ����B
�Ev0.65�B�T���v�����g���̒l��dobule�^�ɂ��ĉ��������コ�����B
�Ev1.02&v1.40�B_PlayLength�̐ݒ莞�ɁA�T���v�����g����4kHz��菬�����ꍇ�́A
  _LengthCount�̒l��0x7FFF�Ń}�X�N����悤�ɂ����B�����O���b�T�[�̉��̗������
  ���B
�Ev1.07�B(_LengthCount+1)��0x8000�����̏ꍇ�A0x4000,0xC000������_�Ƃ���悤��
  �����B�u�g�b�v��_��Vol.1�v�ŕK�v�B
�Ev1.38�B�o�b�t�@�ւ̋󏑂����݂��Č������B�V�O����ZIRIA������C���[�h�X����L
  �P��OP���������C���̍��̃��W�F���h�̖��O�ǂݏグ�����삷��悤�ɂȂ����B
�Ev1.40�B_LengthCount���ő�l�������ꍇ�A�X�g���[�~���O�Đ��Ƃ݂Ȃ��A�r���Ŏ~
  �߂邱�ƂȂ��A�Ō�܂ōĐ�����悤�ɂ����B���X�g�n���}�Q�h���A�V���[���b�N�z
  �[���Y�A�G�t�F�����W���I����ADPCM�Đ��Ƀp�b�`�������g�킸�ɑΉ������B

Copyright(C)2006-2013 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[ADPCM.c]
		�`�c�o�b�l���������܂��B

		Implement ADPCM functions.

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

#include <stdio.h>		// debug
#include "ADPCM.h"
#include "App.h"
#include "MainBoard.h"
#include "PRINTF.h"
#include "WinMain.h"

//Kitao�ǉ�
#define ADPCM_OVERSAMPLRATE	4.0 //4.0�B���������̂ݗL���B�l�̐���������Ȃ����߂�4.0�ӂ肪�œK�B5.0���Ƃ��A�^�b�N�s���Bv2.70�X�V�B1.0���ƃI�[�o�[�T���v�����O�Ȃ��B�Ȃ����ƍ����̃{�C�X��������C���ɒ�������̂ōŏ����̃I�[�o�[�T���v�����O���s���B
#define ADPCM_INCLINE 3.990 //3.990 x ADPCM_OVERSAMPLRATE(4.0)�{��ADPCM���ʂ𑝕��B�v15.96�{�B�X�i�b�`���[�œK�B�v17�{���ƃC�[�XI�EII�ŉ�����B18�{���ƃO��II�́uOption�v�����ŉ�����m�F�B���@���݂̉��ʂɒ����Bv2.62�X�V�B��Ƀh���S���X���C���[�p�Y�`��,���㕨��Q,���㕨��R,�t�@�C�e�B���O�X�g���[�g,�O���f�B�E�XII,�E�B���Y�I�u�T���_�[,�h���L�����w���Œ��������B

static Uint8	_Ram[0x10000];
static Uint16	_Addr;
static Uint16	_ReadAddr;
static Uint16	_WriteAddr;
static Uint32	_LengthCount;
static Uint32	_PlayLength;
static Uint16	_PlayAddr; //Kitao�ǉ��BHalf�̈ʒu�֌W�Ȃǂ��킩��₷�����邽�߂ɁAPlayLength�͈��������̂܂܂ɂ��āAPlayAddr(���݂̍Đ��J�[�\���ʒu)�𑫂��Ă����`�ɂ����Bv1.08�X�V�BUint16�ɂ����B
static Uint16	_PlayHalfAddr; //Kitao�ǉ��Bv1.08
static BOOL		_bPlay;
static BOOL		_bRepeat;
static BOOL		_bStream; //Kitao�ǉ��Bv1.40
static Uint32	_OldSampleFreq; //Kitao�X�V�B�Â��X�e�[�g�Z�[�u��ǂݍ��ނ��߂Ɏc���Ă���B
static double	_SampleFreq; //Kitao�X�V�Bv0.65�Bdouble�Ōv�Z����̂Ō�����double�T�C�Y�ɂ����B���x�A�b�v�B
static Uint32	_DP; // delta phase in 16.16 fixed�B Kitao�X�V�B���x�A�b�v�̂��߁A_SampleFreq�ݒ莞�ɂ��炩���ߌv�Z���Ă����悤�ɂ����Bv1.08
static Sint16	_FadeOut; //Kitao�ǉ��B�m�C�Y�y���̂��߁A�������̓t�F�[�h�A�E�g�ŏ�������Bsample��16�r�b�g�Ȃ̂�Sint16�ŁB
static BOOL		_bPause = FALSE; //Kitao�ǉ��B���X�e�[�g�Z�[�u�̕K�v�Ȃ�
static Sint32	_CDDAAjustCount = 0; //CDDA�̍Đ��X�s�[�h�������p�̃J�E���^�BADPCM�ɂ��K�p�Bv2.32�B���X�e�[�g�Z�[�u�̕K�v�Ȃ�

/* volume, fadein/fadeout */
static Sint32	_CurrentVolume = 0;
static Sint32	_InitialVolume = 0;
static Sint32	_VolumeStep;
static BOOL		_bFadeIn  = FALSE;
static BOOL		_bFadeOut = FALSE;
static Sint32	_FadeClockCount;
static Sint32	_FadeCycle;
static Sint32	_AdpcmVolumeEffect = 0;//Kitao�ǉ�
static double	_VOL = 0.0;//Kitao�ǉ��Bv1.08


static Uint32	_Phase;
static Sint32	_OldDecodeBuffer[0x20000]; //Kitao�X�V�Bv0.60�����g�p
static Sint32	_DecodeBuffer; //Kitao�ǉ�
static BOOL		_bLowNibble;


static Sint32	_PlayedSampleCount;
static Sint32	_WrittenSampleCount; //Kitao�X�V�Bv0.60�����g�p
static Sint32	_PlayedSampleCountDecimal; //Kitao�X�V�Bv0.60�����g�p

static Uint8	_ReadBuffer;//Kitao�ǉ�
static Uint8	_WriteBuffer;//Kitao�ǉ�
static BOOL		_bDecReadBuffer;//Kitao�ǉ��Bv1.38�����g�p�ɁB���o�[�W�����̃X�e�[�g�Z�[�u��ǂݍ��ނ��߂Ɏc���Ă���B


static void		(*_pfnNotification)(Uint32 adpcmState);


// for adpcm play  ���ݔ�g�p�B0�ŃX�e�[�g�Z�[�u���Ă���̂ŁA�X�e�[�g�Z�[�u�̗\���̈�Ƃ��Ďg����B
static Sint32	_SrcIndex;
static Sint32	_DstIndex;
static Sint32	_Sample;
static Sint32	_Error;
static Sint32	_nDstSample;
static Sint32	_nSrcSample;


/*
	The original decoder is provided by Dave Shadoff,
	and further optimized by Ki.
*/
static Sint32		ad_sample;
static Sint32		ad_ref_index;

static const Uint32	_LUT[49*16] =
{
	0x0002ffff, 0x0006ffff, 0x000affff, 0x000effff, 0x00120002, 0x00160004, 0x001a0006, 0x001e0008,
	0xfffeffff, 0xfffaffff, 0xfff6ffff, 0xfff2ffff, 0xffee0002, 0xffea0004, 0xffe60006, 0xffe20008,
	0x0002ffff, 0x0006ffff, 0x000affff, 0x000effff, 0x00130002, 0x00170004, 0x001b0006, 0x001f0008,
	0xfffeffff, 0xfffaffff, 0xfff6ffff, 0xfff2ffff, 0xffed0002, 0xffe90004, 0xffe50006, 0xffe10008,
	0x0002ffff, 0x0006ffff, 0x000bffff, 0x000fffff, 0x00150002, 0x00190004, 0x001e0006, 0x00220008,
	0xfffeffff, 0xfffaffff, 0xfff5ffff, 0xfff1ffff, 0xffeb0002, 0xffe70004, 0xffe20006, 0xffde0008,
	0x0002ffff, 0x0007ffff, 0x000cffff, 0x0011ffff, 0x00170002, 0x001c0004, 0x00210006, 0x00260008,
	0xfffeffff, 0xfff9ffff, 0xfff4ffff, 0xffefffff, 0xffe90002, 0xffe40004, 0xffdf0006, 0xffda0008,
	0x0002ffff, 0x0007ffff, 0x000dffff, 0x0012ffff, 0x00190002, 0x001e0004, 0x00240006, 0x00290008,
	0xfffeffff, 0xfff9ffff, 0xfff3ffff, 0xffeeffff, 0xffe70002, 0xffe20004, 0xffdc0006, 0xffd70008,
	0x0003ffff, 0x0009ffff, 0x000fffff, 0x0015ffff, 0x001c0002, 0x00220004, 0x00280006, 0x002e0008,
	0xfffdffff, 0xfff7ffff, 0xfff1ffff, 0xffebffff, 0xffe40002, 0xffde0004, 0xffd80006, 0xffd20008,
	0x0003ffff, 0x000affff, 0x0011ffff, 0x0018ffff, 0x001f0002, 0x00260004, 0x002d0006, 0x00340008,
	0xfffdffff, 0xfff6ffff, 0xffefffff, 0xffe8ffff, 0xffe10002, 0xffda0004, 0xffd30006, 0xffcc0008,
	0x0003ffff, 0x000affff, 0x0012ffff, 0x0019ffff, 0x00220002, 0x00290004, 0x00310006, 0x00380008,
	0xfffdffff, 0xfff6ffff, 0xffeeffff, 0xffe7ffff, 0xffde0002, 0xffd70004, 0xffcf0006, 0xffc80008,
	0x0004ffff, 0x000cffff, 0x0015ffff, 0x001dffff, 0x00260002, 0x002e0004, 0x00370006, 0x003f0008,
	0xfffcffff, 0xfff4ffff, 0xffebffff, 0xffe3ffff, 0xffda0002, 0xffd20004, 0xffc90006, 0xffc10008,
	0x0004ffff, 0x000dffff, 0x0016ffff, 0x001fffff, 0x00290002, 0x00320004, 0x003b0006, 0x00440008,
	0xfffcffff, 0xfff3ffff, 0xffeaffff, 0xffe1ffff, 0xffd70002, 0xffce0004, 0xffc50006, 0xffbc0008,
	0x0005ffff, 0x000fffff, 0x0019ffff, 0x0023ffff, 0x002e0002, 0x00380004, 0x00420006, 0x004c0008,
	0xfffbffff, 0xfff1ffff, 0xffe7ffff, 0xffddffff, 0xffd20002, 0xffc80004, 0xffbe0006, 0xffb40008,
	0x0005ffff, 0x0010ffff, 0x001bffff, 0x0026ffff, 0x00320002, 0x003d0004, 0x00480006, 0x00530008,
	0xfffbffff, 0xfff0ffff, 0xffe5ffff, 0xffdaffff, 0xffce0002, 0xffc30004, 0xffb80006, 0xffad0008,
	0x0006ffff, 0x0012ffff, 0x001fffff, 0x002bffff, 0x00380002, 0x00440004, 0x00510006, 0x005d0008,
	0xfffaffff, 0xffeeffff, 0xffe1ffff, 0xffd5ffff, 0xffc80002, 0xffbc0004, 0xffaf0006, 0xffa30008,
	0x0006ffff, 0x0013ffff, 0x0021ffff, 0x002effff, 0x003d0002, 0x004a0004, 0x00580006, 0x00650008,
	0xfffaffff, 0xffedffff, 0xffdfffff, 0xffd2ffff, 0xffc30002, 0xffb60004, 0xffa80006, 0xff9b0008,
	0x0007ffff, 0x0016ffff, 0x0025ffff, 0x0034ffff, 0x00430002, 0x00520004, 0x00610006, 0x00700008,
	0xfff9ffff, 0xffeaffff, 0xffdbffff, 0xffccffff, 0xffbd0002, 0xffae0004, 0xff9f0006, 0xff900008,
	0x0008ffff, 0x0018ffff, 0x0029ffff, 0x0039ffff, 0x004a0002, 0x005a0004, 0x006b0006, 0x007b0008,
	0xfff8ffff, 0xffe8ffff, 0xffd7ffff, 0xffc7ffff, 0xffb60002, 0xffa60004, 0xff950006, 0xff850008,
	0x0009ffff, 0x001bffff, 0x002dffff, 0x003fffff, 0x00520002, 0x00640004, 0x00760006, 0x00880008,
	0xfff7ffff, 0xffe5ffff, 0xffd3ffff, 0xffc1ffff, 0xffae0002, 0xff9c0004, 0xff8a0006, 0xff780008,
	0x000affff, 0x001effff, 0x0032ffff, 0x0046ffff, 0x005a0002, 0x006e0004, 0x00820006, 0x00960008,
	0xfff6ffff, 0xffe2ffff, 0xffceffff, 0xffbaffff, 0xffa60002, 0xff920004, 0xff7e0006, 0xff6a0008,
	0x000bffff, 0x0021ffff, 0x0037ffff, 0x004dffff, 0x00630002, 0x00790004, 0x008f0006, 0x00a50008,
	0xfff5ffff, 0xffdfffff, 0xffc9ffff, 0xffb3ffff, 0xff9d0002, 0xff870004, 0xff710006, 0xff5b0008,
	0x000cffff, 0x0024ffff, 0x003cffff, 0x0054ffff, 0x006d0002, 0x00850004, 0x009d0006, 0x00b50008,
	0xfff4ffff, 0xffdcffff, 0xffc4ffff, 0xffacffff, 0xff930002, 0xff7b0004, 0xff630006, 0xff4b0008,
	0x000dffff, 0x0027ffff, 0x0042ffff, 0x005cffff, 0x00780002, 0x00920004, 0x00ad0006, 0x00c70008,
	0xfff3ffff, 0xffd9ffff, 0xffbeffff, 0xffa4ffff, 0xff880002, 0xff6e0004, 0xff530006, 0xff390008,
	0x000effff, 0x002bffff, 0x0049ffff, 0x0066ffff, 0x00840002, 0x00a10004, 0x00bf0006, 0x00dc0008,
	0xfff2ffff, 0xffd5ffff, 0xffb7ffff, 0xff9affff, 0xff7c0002, 0xff5f0004, 0xff410006, 0xff240008,
	0x0010ffff, 0x0030ffff, 0x0051ffff, 0x0071ffff, 0x00920002, 0x00b20004, 0x00d30006, 0x00f30008,
	0xfff0ffff, 0xffd0ffff, 0xffafffff, 0xff8fffff, 0xff6e0002, 0xff4e0004, 0xff2d0006, 0xff0d0008,
	0x0011ffff, 0x0034ffff, 0x0058ffff, 0x007bffff, 0x00a00002, 0x00c30004, 0x00e70006, 0x010a0008,
	0xffefffff, 0xffccffff, 0xffa8ffff, 0xff85ffff, 0xff600002, 0xff3d0004, 0xff190006, 0xfef60008,
	0x0013ffff, 0x003affff, 0x0061ffff, 0x0088ffff, 0x00b00002, 0x00d70004, 0x00fe0006, 0x01250008,
	0xffedffff, 0xffc6ffff, 0xff9fffff, 0xff78ffff, 0xff500002, 0xff290004, 0xff020006, 0xfedb0008,
	0x0015ffff, 0x0040ffff, 0x006bffff, 0x0096ffff, 0x00c20002, 0x00ed0004, 0x01180006, 0x01430008,
	0xffebffff, 0xffc0ffff, 0xff95ffff, 0xff6affff, 0xff3e0002, 0xff130004, 0xfee80006, 0xfebd0008,
	0x0017ffff, 0x0046ffff, 0x0076ffff, 0x00a5ffff, 0x00d50002, 0x01040004, 0x01340006, 0x01630008,
	0xffe9ffff, 0xffbaffff, 0xff8affff, 0xff5bffff, 0xff2b0002, 0xfefc0004, 0xfecc0006, 0xfe9d0008,
	0x001affff, 0x004effff, 0x0082ffff, 0x00b6ffff, 0x00eb0002, 0x011f0004, 0x01530006, 0x01870008,
	0xffe6ffff, 0xffb2ffff, 0xff7effff, 0xff4affff, 0xff150002, 0xfee10004, 0xfead0006, 0xfe790008,
	0x001cffff, 0x0055ffff, 0x008fffff, 0x00c8ffff, 0x01020002, 0x013b0004, 0x01750006, 0x01ae0008,
	0xffe4ffff, 0xffabffff, 0xff71ffff, 0xff38ffff, 0xfefe0002, 0xfec50004, 0xfe8b0006, 0xfe520008,
	0x001fffff, 0x005effff, 0x009dffff, 0x00dcffff, 0x011c0002, 0x015b0004, 0x019a0006, 0x01d90008,
	0xffe1ffff, 0xffa2ffff, 0xff63ffff, 0xff24ffff, 0xfee40002, 0xfea50004, 0xfe660006, 0xfe270008,
	0x0022ffff, 0x0067ffff, 0x00adffff, 0x00f2ffff, 0x01390002, 0x017e0004, 0x01c40006, 0x02090008,
	0xffdeffff, 0xff99ffff, 0xff53ffff, 0xff0effff, 0xfec70002, 0xfe820004, 0xfe3c0006, 0xfdf70008,
	0x0026ffff, 0x0072ffff, 0x00bfffff, 0x010bffff, 0x01590002, 0x01a50004, 0x01f20006, 0x023e0008,
	0xffdaffff, 0xff8effff, 0xff41ffff, 0xfef5ffff, 0xfea70002, 0xfe5b0004, 0xfe0e0006, 0xfdc20008,
	0x002affff, 0x007effff, 0x00d2ffff, 0x0126ffff, 0x017b0002, 0x01cf0004, 0x02230006, 0x02770008,
	0xffd6ffff, 0xff82ffff, 0xff2effff, 0xfedaffff, 0xfe850002, 0xfe310004, 0xfddd0006, 0xfd890008,
	0x002effff, 0x008affff, 0x00e7ffff, 0x0143ffff, 0x01a10002, 0x01fd0004, 0x025a0006, 0x02b60008,
	0xffd2ffff, 0xff76ffff, 0xff19ffff, 0xfebdffff, 0xfe5f0002, 0xfe030004, 0xfda60006, 0xfd4a0008,
	0x0033ffff, 0x0099ffff, 0x00ffffff, 0x0165ffff, 0x01cb0002, 0x02310004, 0x02970006, 0x02fd0008,
	0xffcdffff, 0xff67ffff, 0xff01ffff, 0xfe9bffff, 0xfe350002, 0xfdcf0004, 0xfd690006, 0xfd030008,
	0x0038ffff, 0x00a8ffff, 0x0118ffff, 0x0188ffff, 0x01f90002, 0x02690004, 0x02d90006, 0x03490008,
	0xffc8ffff, 0xff58ffff, 0xfee8ffff, 0xfe78ffff, 0xfe070002, 0xfd970004, 0xfd270006, 0xfcb70008,
	0x003dffff, 0x00b8ffff, 0x0134ffff, 0x01afffff, 0x022b0002, 0x02a60004, 0x03220006, 0x039d0008,
	0xffc3ffff, 0xff48ffff, 0xfeccffff, 0xfe51ffff, 0xfdd50002, 0xfd5a0004, 0xfcde0006, 0xfc630008,
	0x0044ffff, 0x00ccffff, 0x0154ffff, 0x01dcffff, 0x02640002, 0x02ec0004, 0x03740006, 0x03fc0008,
	0xffbcffff, 0xff34ffff, 0xfeacffff, 0xfe24ffff, 0xfd9c0002, 0xfd140004, 0xfc8c0006, 0xfc040008,
	0x004affff, 0x00dfffff, 0x0175ffff, 0x020affff, 0x02a00002, 0x03350004, 0x03cb0006, 0x04600008,
	0xffb6ffff, 0xff21ffff, 0xfe8bffff, 0xfdf6ffff, 0xfd600002, 0xfccb0004, 0xfc350006, 0xfba00008,
	0x0052ffff, 0x00f6ffff, 0x019bffff, 0x023fffff, 0x02e40002, 0x03880004, 0x042d0006, 0x04d10008,
	0xffaeffff, 0xff0affff, 0xfe65ffff, 0xfdc1ffff, 0xfd1c0002, 0xfc780004, 0xfbd30006, 0xfb2f0008,
	0x005affff, 0x010fffff, 0x01c4ffff, 0x0279ffff, 0x032e0002, 0x03e30004, 0x04980006, 0x054d0008,
	0xffa6ffff, 0xfef1ffff, 0xfe3cffff, 0xfd87ffff, 0xfcd20002, 0xfc1d0004, 0xfb680006, 0xfab30008,
	0x0063ffff, 0x012affff, 0x01f1ffff, 0x02b8ffff, 0x037f0002, 0x04460004, 0x050d0006, 0x05d40008,
	0xff9dffff, 0xfed6ffff, 0xfe0fffff, 0xfd48ffff, 0xfc810002, 0xfbba0004, 0xfaf30006, 0xfa2c0008,
	0x006dffff, 0x0148ffff, 0x0223ffff, 0x02feffff, 0x03d90002, 0x04b40004, 0x058f0006, 0x066a0008,
	0xff93ffff, 0xfeb8ffff, 0xfdddffff, 0xfd02ffff, 0xfc270002, 0xfb4c0004, 0xfa710006, 0xf9960008,
	0x0078ffff, 0x0168ffff, 0x0259ffff, 0x0349ffff, 0x043b0002, 0x052b0004, 0x061c0006, 0x070c0008,
	0xff88ffff, 0xfe98ffff, 0xfda7ffff, 0xfcb7ffff, 0xfbc50002, 0xfad50004, 0xf9e40006, 0xf8f40008,
	0x0084ffff, 0x018dffff, 0x0296ffff, 0x039fffff, 0x04a80002, 0x05b10004, 0x06ba0006, 0x07c30008,
	0xff7cffff, 0xfe73ffff, 0xfd6affff, 0xfc61ffff, 0xfb580002, 0xfa4f0004, 0xf9460006, 0xf83d0008,
	0x0091ffff, 0x01b4ffff, 0x02d8ffff, 0x03fbffff, 0x051f0002, 0x06420004, 0x07660006, 0x08890008,
	0xff6fffff, 0xfe4cffff, 0xfd28ffff, 0xfc05ffff, 0xfae10002, 0xf9be0004, 0xf89a0006, 0xf7770008,
	0x00a0ffff, 0x01e0ffff, 0x0321ffff, 0x0461ffff, 0x05a20002, 0x06e20004, 0x08230006, 0x09630008,
	0xff60ffff, 0xfe20ffff, 0xfcdfffff, 0xfb9fffff, 0xfa5e0002, 0xf91e0004, 0xf7dd0006, 0xf69d0008,
	0x00b0ffff, 0x0210ffff, 0x0371ffff, 0x04d1ffff, 0x06330002, 0x07930004, 0x08f40006, 0x0a540008,
	0xff50ffff, 0xfdf0ffff, 0xfc8fffff, 0xfb2fffff, 0xf9cd0002, 0xf86d0004, 0xf70c0006, 0xf5ac0008,
	0x00c2ffff, 0x0246ffff, 0x03caffff, 0x054effff, 0x06d20002, 0x08560004, 0x09da0006, 0x0b5e0008,
	0xff3effff, 0xfdbaffff, 0xfc36ffff, 0xfab2ffff, 0xf92e0002, 0xf7aa0004, 0xf6260006, 0xf4a20008
};

/*-----------------------------------------------------------------------------
	[decode]
		ADPCM�G���R�[�h���ꂽ�f�[�^�𕄍��t��16�r�b�g�I�[�f�B�I�f�[�^��
	�f�R�[�h���܂��B
-----------------------------------------------------------------------------*/
static inline Sint32 //Kitao�X�V�Bv2.00
decode(
	Uint8	code)
{
	Uint32 data = _LUT[(ad_ref_index << 4) + code];

	ad_sample += (Sint32)data >> 16;
	if (ad_sample < -2048)
		ad_sample = -2048;
	else if (ad_sample > 2047)
		ad_sample = 2047;

	ad_ref_index += (Sint16)(data & 0xFFFF);
	if (ad_ref_index < 0)
		ad_ref_index = 0;
	else if (ad_ref_index > 48)
		ad_ref_index = 48;

	return ad_sample;
}


//Kitao�ǉ�
static void
set_VOL()
{
	if (_AdpcmVolumeEffect == 0)
		_VOL = 0.0; //�~���[�g
	else if (_AdpcmVolumeEffect == 3)
		_VOL = ((double)_CurrentVolume / 65535.0) * 3.0/4.0; // 3/4�Bv1.29�ǉ�
	else
	 	_VOL = ((double)_CurrentVolume / 65535.0) / (double)_AdpcmVolumeEffect; //���ʗp�̊|������_AdpcmVolumeEffect(���ʒ��ߌ���)
	_VOL *= ADPCM_INCLINE; //���@���݂̉��ʂɒ���
}


/*-----------------------------------------------------------------------------
	[Init]
		
-----------------------------------------------------------------------------*/
BOOL
ADPCM_Init()
{
	ADPCM_SetVolume(APP_GetAdpcmVolume());//Kitao�ǉ�
	memset(_Ram, 0, sizeof(_Ram));
	_SampleFreq = 0.0;
	_DP = 0; //Kitao�ǉ�
	ADPCM_Reset(); //Kitao�X�V
	return TRUE;
}


/*-----------------------------------------------------------------------------
	[Deinit]
		
-----------------------------------------------------------------------------*/
void
ADPCM_Deinit()
{
	ADPCM_Reset(); //Kitao�X�V
}


/*-----------------------------------------------------------------------------
	[Reset]
		
-----------------------------------------------------------------------------*/
void
ADPCM_Reset()
{
	_bPlay = FALSE;
	_bRepeat = FALSE;
	_bStream = FALSE; //Kitao�ǉ��Bv1.40
	_Addr = 0;
	_ReadAddr = 0;
	_WriteAddr = 0;
	_LengthCount = 0;
	_SampleFreq = 0.0;
	_DP = 0; //Kitao�ǉ�
	_FadeOut = 0; //Kitao�ǉ�

	// for adpcm play  ���ݔ�g�p�B�X�e�[�g�Z�[�u�̗\���̈�Ƃ��Ďg���B
	//_SrcIndex = 0;
	_DstIndex = 0;
	_Sample = 0;
	_Error = 0;
	_nDstSample = 0;
	_nSrcSample = 0;

	_CurrentVolume = _InitialVolume;
	set_VOL(); //Kitao�ǉ�
	_VolumeStep = _InitialVolume / 10;
	_bFadeIn  = FALSE;
	_bFadeOut = FALSE;
	_FadeClockCount = 0;
	_FadeCycle = 0;

	ad_sample = 0;
	ad_ref_index = 0;

	_ReadBuffer = 0;//Kitao�ǉ�
	_WriteBuffer = 0;//Kitao�ǉ�
}


/*-----------------------------------------------------------------------------
	[SetNotificationFunction]
		
-----------------------------------------------------------------------------*/
void
ADPCM_SetNotificationFunction(
	void	(*pfnNotification)(Uint32))
{
	_pfnNotification = pfnNotification;
}


/*-----------------------------------------------------------------------------
	[SetAddrLo]
		
-----------------------------------------------------------------------------*/
void
ADPCM_SetAddrLo(
	Uint8	addrLo)
{
	_Addr &= 0xFF00;
	_Addr |= addrLo;
//_Addr = addrLo; //test
}


/*-----------------------------------------------------------------------------
	[SetAddrHi]
		
-----------------------------------------------------------------------------*/
void
ADPCM_SetAddrHi(
	Uint8	addrHi)
{
	_Addr &= 0xFF;
	_Addr |= addrHi << 8;
}


/*-----------------------------------------------------------------------------
	[SetReadAddr]
		
-----------------------------------------------------------------------------*/
void
ADPCM_SetReadAddr()
{
/*
{
	char s[100];
	sprintf(s,"Kekka=%x -> %x", _ReadAddr,_Addr);
	int ok;
	ok = MessageBox(WINMAIN_GetHwnd(),
			s,
			"Test",
			MB_YESNO); //Kitao Test
	if (ok != IDYES)
		WINMAIN_SetBreakTrap(FALSE);
}
*/
	// $180A �̋�ǂ݂��Q��s�Ȃ��邱�Ƃւ̑΍�������Ȃ�
	//Kitao�X�V�B��ǂ݂̑΍����@���V���v���ɂ����B
	_ReadAddr = _Addr;
	_ReadBuffer = 2; //��ǂ݂Q��
}


/*-----------------------------------------------------------------------------
	[SetWriteAddr]
		
-----------------------------------------------------------------------------*/
void
ADPCM_SetWriteAddr(
	Uint8	writeBuffer) //Kitao�X�V�B$180A�ւ̋󏑂����P��s���ꍇ1�ŌĂԁB�ʏ��0�B
{
/*
{
	char s[100];
	sprintf(s,"Kekka=%x", _WriteAddr);
	int ok;
	ok = MessageBox(WINMAIN_GetHwnd(),
			s,
			"Test",
			MB_YESNO); //Kitao Test
	if (ok != IDYES)
		WINMAIN_SetBreakTrap(FALSE);
}
*/
	_WriteAddr = _Addr;
	_WriteBuffer = writeBuffer; //v1.38�ǉ��B�V�O����ZIRIA�C���[�h�X����L�P�̃I�[�v�j���O�C���̍��̃��W�F���h�̖��O�ǂݏグ�B

	//PRINTF("WriteAddr=%X , WriteBuffer=%d , ReadAddr=%X , LengthCount=%X", (int)_WriteAddr, _WriteBuffer, _ReadAddr, _LengthCount);//test�p
	if (((_ReadAddr + _LengthCount) & 0x1FFF) == 0x1FFF) //�X�g���[���Đ��̏ꍇ�Bv2.24�X�V�BAYA�ŉ��̓r�؂����
		_bStream = TRUE; //AYA,���X�g�n���}�Q�h��,�G�t�F�����W���I��,�z�[���Y�P�Q�ŕK�v�B
}


/*-----------------------------------------------------------------------------
	[SetLength]
		
-----------------------------------------------------------------------------*/
void
ADPCM_SetLength()
{
	_LengthCount = _Addr;

	//Kitao�ǉ��B�X�g���[�~���O�ł͂Ȃ��ꍇ�A�l���}�X�N����B�����O���b�T�[�ŕK�v�Bv1.40�Bv2.15�X�V
	//PRINTF("SampleFreq=%d , Read=%X , Write=%X , Length=%X ,Repeat=%d", (int)_SampleFreq, (int)_ReadAddr, (int)_WriteAddr, (int)_LengthCount, (int)_bRepeat);//test�p
	if ((_SampleFreq < 16000)&& //�Đ����g�����Ⴂ(�b�Ԃ̃f�[�^�ʂ����Ȃ�)�Ƃ��̂݁B���ꂪ�Ȃ��Ɛ��T����R�ŉ��؂�B����m�`��,�C�[�X�R��16000�ł��̏����ɍ��v�B�����O���b�T�[�Ŏ��g��10666�̂Ƃ��̓}�X�N�K�v�Bv2.36�X�V
		(_ReadAddr >= 0x4000)&& //���ꂪ�Ȃ���"���_�J�u�L�`"��"�W���b�N�j�N���E�X�S���t"�̉����r�؂�B
	 	(_WriteAddr == 0x0000)&& //"�V�n����炤","���鐯���(�o�b�N�A�b�vRAM�����ς��̉���)"�ł��̏������Ȃ��Ɖ��؂�Bv1.49�X�V
		(_LengthCount != 0x8000)&& //����m�`���|����̋R�m�|�ł��̏������Ȃ��Ɖ��؂�Bv2.16�X�V
		(_LengthCount != 0xFFFF)) //�G�t�F�����W���I���ł��̏������Ȃ��Ɖ��؂�Bv1.50�X�V
			_LengthCount &= 0x7FFF;
}


/*-----------------------------------------------------------------------------
	[ReadBuffer]
		
-----------------------------------------------------------------------------*/
Uint8
ADPCM_ReadBuffer()
{
	//PRINTF("Read = %X , %X", _ReadAddr,_ReadBuffer);//test�p
	if (_ReadBuffer > 0) //Kitao�X�V�B��ǂ݂��ς�ł��Ȃ����
	{
		_ReadBuffer--;
		return 0;
	}
	else
		return _Ram[_ReadAddr++];
}


/*-----------------------------------------------------------------------------
	[WriteBuffer]
		
-----------------------------------------------------------------------------*/
void
ADPCM_WriteBuffer(
	Uint8	data)
{
	//PRINTF("Write = %X , %X", _WriteAddr,_PlayLength);//test�p
	if (_WriteBuffer > 0) //Kitao�ǉ��B�󏑂����ς�ł��Ȃ����
		_WriteBuffer--;
	else
	{
		_Ram[_WriteAddr++] = data;
		_PlayLength++; //Kitao�ǉ�
	}
}


static Sint32 _test=2;
/*-----------------------------------------------------------------------------
	[Play]
		
-----------------------------------------------------------------------------*/
void
ADPCM_Play(
	BOOL	bPlay)
{
	//PRINTF("PlayAddr=%X , PlayLength=%X , _PlayedSampleCount=%X", (int)_PlayAddr, (int)_PlayLength, (int)_PlayedSampleCount);//test�p
	//PRINTF("PlayLength=%X , PlayLength-_PlayedSampleCount=%X", (int)_PlayLength, (int)(_PlayLength-_PlayedSampleCount));//test�p
	if (bPlay)
	{
		//PRINTF("SampleFreq=%d Repeat=%d", _SampleFreq, _bRepeat);//test�p
		_PlayAddr = _ReadAddr; //Kitao�ǉ�
		_PlayLength = _LengthCount + 1; //Kitao�X�V�Bv2.29�Bv2.36
		_PlayHalfAddr = (Uint16)(_PlayLength >> 1); //Kitao�ǉ��Bv1.08�Bv2.29�Bv2.36
		_PlayedSampleCount = 0;
		ad_sample = 0;
		_DecodeBuffer = decode(_Ram[_PlayAddr] >> 4);
		_bLowNibble	= TRUE;
		_Phase = 0; //Kitao�X�V
		_CDDAAjustCount = 0; //v2.32�ǉ�
		_bPlay = TRUE;
	}
	else if ((!_bRepeat)&& //Kitao�ǉ��B���s�[�g��TRUE�Ȃ�Ō�܂ōĐ�����B�X�`�[���n�[�c
			 ((!_bStream)|| //���X�g���[���Đ�(((_ReadAddr + _LengthCount) & 0x1FFF) == 0x1FFF)�������ꍇ�́A�����̃X�g�b�v�͂����Ɋ����݈ʒu�܂ōĐ�����B���X�g�n���}�Q�h��,�G�t�F�����W���I��,�z�[���Y�P�Q�B
			  (_PlayLength - _PlayedSampleCount > 0x8000))) //�X�g���[���Đ��ł��c�肪0x8000�ȏ�̏��(�L�����Z����������)�̏ꍇ�͂����ɃX�g�b�v�B
	{
		_bPlay = FALSE;
		_bRepeat = FALSE;
		_bStream = FALSE; //Kitao�ǉ��Bv1.40
		ad_ref_index = 0; //Kitao�ǉ��B�������ɂ������Z�b�g�B�������Ă���Ƃ��Ƀ��Z�b�g����ƃv�`�v�`�m�C�Y���o�邽�߁B
		if (_pfnNotification != NULL)
			_pfnNotification(ADPCM_STATE_STOPPED);
		//PRINTF("ADPCM STOP"); //test
	}
}


/*-----------------------------------------------------------------------------
	[Repeat]
		�n�[�h�E�F�A�Ń��[�v�Đ����s�Ȃ��Ă��邩�ǂ����͕s���B
		��Kitao�X�V�B���s�[�g�Đ��ƌ������́A�Đ������܂ŉ����~�߂Ȃ��悤�ɂ���t���O�̂悤���BRepeat���Z�b�g�����Ɖ����I���܂ŃX�g�b�v���Ȃ��悤�ɂ���B�i�X�`�[���n�[�c�j
-----------------------------------------------------------------------------*/
void
ADPCM_Repeat(
	BOOL	bRepeat)
{
	//PRINTF("PlayAddr=%X , PlayLength=%X , _PlayedSampleCount=%X", (int)_PlayAddr, (int)_PlayLength, (int)_PlayedSampleCount);//test�p
	//Kitao�Q�l�B���s�[�g�̃I�t�������ł��Ȃ��悤�ɂ���Ɛ���m�`���Ń^�C�~���O�����@�ɋ߂��Ȃ邪�A���̃\�t�g�ő傫����肪����Bv2.24
	_bRepeat = bRepeat; //Kitao�X�V�B�Đ��J�n���Repeat���ݒ肳��邱�Ƃ�����i�X�`�[���n�[�c�j
}


//Kitao�ǉ��BADPCM�̍Đ��̓������ꎞ��~����BCDROM.c ����g�p�BADPCM�Đ�����ɐi�݁A���荞�݂������N�������Ă��܂�Ȃ����߂ɕK�v�B
void
ADPCM_Pause(
	BOOL	bPause)
{
	_bPause = bPause;
}


//sample�̍쐬�A����эĐ������E����_�ʉ߂̃`�F�b�N���s���Bv2.32�X�V
static inline Sint16
makeSample()
{
	Sint32	j;
	Sint16	sample; //Kitao�X�V�BSint16�ɁB

	sample = 0; //�I�[�o�[�T���v�����O�p
	for (j=1; j<=(Sint32)ADPCM_OVERSAMPLRATE; j++) //�I�[�o�[�T���v�����O������ƁA���̃A�^�b�N������ĉ����������Â炢�Q�[��������i���㕨��Q,�R���j�̂ŁA�ߏ�ȃI�[�o�[�T���v�����O���Ȃ��ق��������悤���Bv2.62�Cv2.70
	{
		_Phase += _DP;
		if (_Phase >= (1<<13))
		{
			if (_bLowNibble)
			{	//�o�C�g�㔼�̃f�[�^���f�R�[�h
				_PlayedSampleCount++; //�����ŃJ�E���^���v���X����悤�ɂ��āA���߂ɍĐ��I���̍��}��PCE���ɓ`����悤�ɂ����B�h���S���X���C���[�p�Y�`���̃h�����̃e���|���œK�Bv2.36�X�V
				if (_PlayedSampleCount == _PlayLength) //�S�Ă̍Đ������������ꍇ�B
				{
					_bPlay = FALSE;
					_bRepeat = FALSE;
					_bStream = FALSE; //Kitao�ǉ��Bv1.40
					ad_ref_index = 0; //Kitao�ǉ��B�������ɂ������Z�b�g�B�������Ă���Ƃ��Ƀ��Z�b�g����ƃv�`�v�`�m�C�Y���o�邽�߁B
					sample += (Sint16)(_DecodeBuffer * ((Sint32)ADPCM_OVERSAMPLRATE - j +1)); //�I�[�o�[�T���v�����O�p
					if (_pfnNotification != NULL)
						_pfnNotification(ADPCM_STATE_FULL_PLAYED); //Kitao�X�V�B�S�Ă̍Đ�������
					//PRINTF("ADPCM FULL : %X", _LengthCount); //test
					break; //�I�[�o�[�T���v�����O�p
				}
				else
				{
					_DecodeBuffer = decode(_Ram[_PlayAddr] & 0x0F);
					_PlayAddr++; //Uint16�Ȃ̂�0xFFFF�������ꍇ��0x0000�֖߂�
					//PRINTF("Kekka=%X, %X",(int)_PlayAddr, _PlayHalfAddr);//test�p
					if (_LengthCount < 0x7FFF) //Kitao�ǉ��B(_LengthCount+1)��0x8000�����̏ꍇ�A�n�[�t����_LengthCount���̒n�_�𕪊�_�Ƃ���B�u�g�b�v��_��Vol.1�v�ŕK�v�Bv1.07�B
					{
						if (_PlayAddr == _PlayHalfAddr) //Kitao�X�V�B�Đ���PC�G���W��ADPCM�p�o�b�t�@�������̕���_�܂ŒB�����Ƃ�
						{
							_PlayHalfAddr += ((Uint16)_LengthCount - 1024); //���̕���_���u�I����1KB��O�v�ɐݒ肷��B�g�b�v���˂炦Vol1�ŕK�v�B
							if (_pfnNotification != NULL)
								_pfnNotification(ADPCM_STATE_HALF_PLAYED); //Kitao�ǋL�B�Đ����o�b�t�@�������̕���_��ʉ߂������Ƃ�PC�G���W���ɒm�点��BPC�G���W�����͕K�v�ɉ����ĐV���Ƀo�b�t�@�O�������ɑ����̃f�[�^��ǂݍ��ނ��Ƃ��o����B
							//PRINTF("ADPCM HALF : %X,%X", _PlayAddr,_LengthCount); //test
						}
					}
					else
					{
						if ((_PlayAddr == 0x8000)||(_PlayAddr == 0x0000)) //Kitao�X�V�B�Đ���PC�G���W��ADPCM�p�o�b�t�@�������̕���_�i�������I�_�j�܂ŒB�����Ƃ�
						{
							if (_pfnNotification != NULL)
								_pfnNotification(ADPCM_STATE_HALF_PLAYED); //Kitao�ǋL�B�Đ����o�b�t�@�������̕���_��ʉ߂������Ƃ�PC�G���W���ɒm�点��BPC�G���W�����͕K�v�ɉ����ĐV���Ƀo�b�t�@�O�������ɑ����̃f�[�^��ǂݍ��ނ��Ƃ��o����B
							//PRINTF("ADPCM HALF : %X,%X", _PlayAddr,_LengthCount); //test
						}
					}
					_bLowNibble = FALSE;
				}
			}
			else
			{	//�o�C�g�O���̃f�[�^���f�R�[�h
				if (_PlayedSampleCount+1 != _PlayLength) //���ōĐ������̏ꍇ�̓f�R�[�h���Ȃ��B�h��������(CD��)�́u�^�P�R�v�^�`�v�ł��K�m�C�Y���ڂ�Ȃ����߂ɕK�v�Bv2.36�X�V
					_DecodeBuffer = decode(_Ram[_PlayAddr] >> 4);
				_bLowNibble = TRUE;
			}
			_Phase -= (1<<13);
		}
		sample += (Sint16)_DecodeBuffer; //�I�[�o�[�T���v�����O�p
	}

	return sample; //�I�[�o�[�T���v�����O�p
	//return (Sint16)_DecodeBuffer; //��I�[�o�[�T���v�����O���p
}

/*-----------------------------------------------------------------------------
	[Mix]

-----------------------------------------------------------------------------*/
void
ADPCM_Mix(
	Sint16*		pDst,				// �o�͐�o�b�t�@ //Kitao�X�V�BADPCM��p�o�b�t�@�ɂ�������Sint16�ɁB
	Sint32		nSample)			// �����o���T���v���� 
{
	Sint32		i;
	Sint16		sample; //Kitao�X�V�BSint16�ɁB
	Sint32		cddaAdjust; //v2.32�ǉ�

	if ((!_bPlay)&&(_FadeOut == 0)) //Kitao�X�V�BHu-Card�Ȃ�ADPCM���g��Ȃ��Q�[���̏������y�����邽�߂ɁA��Đ�����_FadeOut��0�Ȃ�f�R�[�h�����������Ȃ킸�Ƀ��^�[���B
		return;

	cddaAdjust = APP_GetCddaAdjust();
	for (i=0; i<nSample; i++)
	{
		if (!_bPlay) //�Đ����I�����Ă����Ȃ�
		{
			//Kitao�ǉ��B�m�C�Y�y���̂��߃t�F�[�h�A�E�g�ŏ�������B
			if (_FadeOut > 0)
			{
				--_FadeOut;
				if (_FadeOut < 0)
					_FadeOut = 0;
			}
			else if (_FadeOut < 0)
			{
				++_FadeOut;
				if (_FadeOut > 0)
					_FadeOut = 0;
			}
			*pDst++ = _FadeOut;
			*pDst++ = _FadeOut;
		}
		else if (_bPause) //Kitao�ǉ��B�|�[�Y���Ȃ�(CD���[�h�҂���CDROM.c ����|�[�Y�����)
		{
			//�O��̉������̂܂ܖ炵�ĊԂ�������
			*pDst++ = _FadeOut;
			*pDst++ = _FadeOut;
		}
		else //�Đ����Ȃ�
		{
			//ADPCM�Đ����x�̔�����(CD-DA�̐ݒ���g��)�B�x���菈���Bv2.32�ǉ�
			if (cddaAdjust < 0)
				if (--_CDDAAjustCount <= cddaAdjust) //cddaAdjust�̐�Βl=���t���[���ɂP�񑫓��݂��邩
				{	
					//�O���sample�ł�����x�Đ����đ����݂���B
					*pDst++ = _FadeOut;
					*pDst++ = _FadeOut;
					_CDDAAjustCount = 0;
					continue;
				}

			//�f�R�[�h���ăT���v�����쐬�B�Đ������̃`�F�b�N�ƕ���_�ʉ߂̃`�F�b�N���s����B
			sample = makeSample();

			//ADPCM�Đ����x�̔�����(CD-DA�̐ݒ���g��)�B�����菈���Bv2.32�ǉ�
			if (cddaAdjust > 0)
			{
				//�O�񑁑��肵���ꍇ�A����̔g�`�ɑO���΂����g�`����������B�m�C�Y�΍�Bv2.46
				if (_CDDAAjustCount == cddaAdjust) //cddaAdjust=���t���[���ɂP�񂾂������肵�Đi�߂邩
					sample = (Sint16)(((Sint32)_FadeOut + (Sint32)sample) / 2);
				//������`�F�b�N
				if (++_CDDAAjustCount >= cddaAdjust) //cddaAdjust=���t���[���ɂP�񂾂������肵�Đi�߂邩
					if (_PlayedSampleCount != _PlayLength) //�܂��Đ����I�����Ă��Ȃ��ꍇ�̂�
					{	
						sample = (Sint16)(((Sint32)sample + (Sint32)makeSample()) / 2); //���̔g�`�������Bv2.46�X�V�B�Đ������̃`�F�b�N�ƕ���_�ʉ߂̃`�F�b�N���s����B
						_CDDAAjustCount = 0;
					}
			}
			
			sample = (Sint16)((double)sample * _VOL); //Kitao�X�V�B*_VOL�͉��ʑ����p�̊|����
			*pDst++ = sample; //Kitao�X�V�BADPCM��p�̃o�b�t�@�ɂ����̂ŁA�v���X�������ڒl������������B
			*pDst++ = sample; //Kitao�X�V
			
			_FadeOut = sample; //Kitao�ǉ��B�Ō�̔g�`�l
		}
	}
}


//Kitao�ǉ�
static void
set_DP()
{
	// 16�{�I�[�o�[�T���v�����O�Ń~�b�N�X����̂� 
	// �ʏ�� dp ��ADPCM_OVERSAMPLRATE�Ŋ��� 
	_DP = (Uint32)((8192.0 / ADPCM_OVERSAMPLRATE / 44100.0) * _SampleFreq +0.5); //Kitao�X�V�B�덷�����Ȃ����邽��ADPCM_OVERSAMPLRATE�Ő�Ɋ���B+0.5�̓v�`�m�C�Y�y���̂��ߎl�̌ܓ��B
}

/*-----------------------------------------------------------------------------
	[SetFreq]
		
-----------------------------------------------------------------------------*/
//Kitao�X�V�BPCE�̃f�[�^���̂܂܂Ŏ󂯎���āA�����瑤��double�ϐ��Ɍv�Z����悤�ɂ����B
void
ADPCM_SetFreq(
	Uint8	data)
{
	_SampleFreq = 32000.0 / (double)(16 - (data & 15));
	set_DP();
}


/*-----------------------------------------------------------------------------
	[IsPlaying]
		
-----------------------------------------------------------------------------*/
BOOL
ADPCM_IsPlaying()
{
	return _bPlay;
}


void
ADPCM_SetVolume(
	Uint32	volume)		// 0 - 65535
{
	if (volume < 0)	volume = 0;
	if (volume > 65535)	volume = 65535;

	_InitialVolume = volume;
	if ((!_bFadeOut)&&(!_bFadeIn))
	{
		_CurrentVolume = volume;
		set_VOL(); //Kitao�ǉ�
	}
}


void
ADPCM_FadeOut(
	Sint32	ms)
{
	if (ms == 0)
	{
		_CurrentVolume = 0;
		_VOL = 0.0; //Kitao�ǉ�
		_bFadeOut = FALSE;
		_bFadeIn  = FALSE;
		_FadeCycle = 0;
	}
	else if (_CurrentVolume > 0)
	{
		_FadeCycle = (Sint32)(((7159090.0 / ((double)_CurrentVolume / (double)_VolumeStep)) * (double)ms) / 1000.0);
		_bFadeOut	= TRUE;
		_bFadeIn	= FALSE;
	}
	else
	{
		_bFadeOut = FALSE;
		_bFadeIn  = FALSE;
		_FadeCycle = 0;
	}
}


void
ADPCM_FadeIn(
	Sint32		ms)
{
	if (ms == 0)
	{
		_CurrentVolume = _InitialVolume;
		set_VOL(); //Kitao�ǉ�
		_bFadeOut = FALSE;
		_bFadeIn  = FALSE;
		_FadeCycle = 0;
	}
	else if (_InitialVolume - _CurrentVolume > 0)
	{
		_FadeCycle = (Sint32)(((7159090.0 / (((double)_InitialVolume - (double)_CurrentVolume) / (double)_VolumeStep)) * (double)ms) / 1000.0);
		_bFadeOut = FALSE;
		_bFadeIn  = TRUE;
	}
	else
	{
		_bFadeOut = FALSE;
		_bFadeIn  = FALSE;
		_FadeCycle = 0;
	}
}


//Kitao�X�V�B�t�F�[�h�A�E�g�E�t�F�[�h�C�������BAPU_AdvanceClock()����Ă΂��B
void
ADPCM_AdvanceFadeClock()
{
	if (_bFadeOut || _bFadeIn)
		if (++_FadeClockCount >= _FadeCycle)
		{
			_FadeClockCount = 0;
			if (_bFadeOut)
			{
				if (_CurrentVolume > 0)
				{
					_CurrentVolume -= _VolumeStep;
					set_VOL(); //Kitao�ǉ�
					if (_CurrentVolume <= 0)
					{
						_CurrentVolume = 0;
						_VOL = 0; //Kitao�ǉ�
						_bFadeOut = FALSE;
					}
				}
			}
			else if (_bFadeIn)
			{
				if (_CurrentVolume < _InitialVolume)
				{
					_CurrentVolume += _VolumeStep;
					set_VOL(); //Kitao�ǉ�
					if (_CurrentVolume >= _InitialVolume)
					{
						_CurrentVolume = _InitialVolume;
						set_VOL(); //Kitao�ǉ�
						_bFadeIn = FALSE;
					}
				}
			}
		}
}


//Kitao�ǉ��B�{�����[���~���[�g�A�n�[�t�Ȃǂ��ł���悤�ɂ����B
void
ADPCM_SetVolumeEffect(
	Uint32	volumeEffect)
{
	_AdpcmVolumeEffect = (Sint32)volumeEffect; //�����l���傫���قǃ{�����[���͏������Ȃ�
	set_VOL();
}


//Kitao�ǉ��B�e���|�������p�̃J�E���^���N���A����Bv2.32
void
ADPCM_ClearCDDAAjustCount()
{
	_CDDAAjustCount = 0;
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
ADPCM_SaveState(
	FILE*		p)
{
	if (p == NULL)
		return FALSE;

	SAVE_A(_Ram);
	SAVE_V(_DecodeBuffer); //Kitao�ǉ�
	SAVE_V(_bLowNibble);

	SAVE_V(_Addr);
	SAVE_V(_ReadAddr);
	SAVE_V(_WriteAddr);
	SAVE_V(_LengthCount);
	SAVE_V(_PlayLength);
	SAVE_V(_PlayAddr); //Kitao�X�V�Bv1.08����Uint16�ɁB
	SAVE_V(_PlayHalfAddr); //Kitao�ǉ��Bv1.08
	SAVE_V(_bPlay);
	SAVE_V(_bRepeat);
	SAVE_V(_bStream);// v1.40�ǉ�
	SAVE_V(_SampleFreq); //v0.65�B�^��double�ɕύX�B
	SAVE_V(_Phase);

	SAVE_V(_WrittenSampleCount);
	SAVE_V(_PlayedSampleCount);
	SAVE_V(_PlayedSampleCountDecimal);

	SAVE_V(_ReadBuffer);
	SAVE_V(_WriteBuffer); //v1.31�ǉ�

	//����6�͌��ݔ�g�p�B0�ŃZ�[�u����Ă���̂ŗ\���̈�Ƃ��Ďg�p�ł���B
	SAVE_V(_SrcIndex);
	SAVE_V(_DstIndex);
	SAVE_V(_Sample);
	SAVE_V(_Error);
	SAVE_V(_nDstSample);
	SAVE_V(_nSrcSample);

	SAVE_V(_CurrentVolume);
	SAVE_V(_VolumeStep);
	SAVE_V(_bFadeIn);
	SAVE_V(_bFadeOut);
	SAVE_V(_FadeClockCount);
	SAVE_V(_FadeCycle);

	SAVE_V(ad_sample);
	SAVE_V(ad_ref_index);

	return TRUE;
}


/*-----------------------------------------------------------------------------
	[LoadState]
		��Ԃ��t�@�C������ǂݍ��݂܂��B 
-----------------------------------------------------------------------------*/
BOOL
ADPCM_LoadState(
	FILE*		p)
{
	Sint32	playAddr32;
	BOOL	bInterruptHalf; //Kitao�X�V�Bv1.07�����g�p�ɁB�ߋ��o�[�W�����̃X�e�[�g�Z�[�u��ǂݍ��ݗp�B

	if (p == NULL)
		return FALSE;

	LOAD_A(_Ram);
	if (MAINBOARD_GetStateVersion() >= 5) //Kitao�ǉ��Bv0.60�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_DecodeBuffer);
		LOAD_V(_bLowNibble);
	}
	else //0.59�ȑO�̃Z�[�u�t�@�C���Ȃ�
		LOAD_A(_OldDecodeBuffer);

	LOAD_V(_Addr);
	LOAD_V(_ReadAddr);
	LOAD_V(_WriteAddr);
	LOAD_V(_LengthCount);
	LOAD_V(_PlayLength);
	if (MAINBOARD_GetStateVersion() >= 25) //Kitao�ǉ��Bv1.08�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_PlayAddr);
		LOAD_V(_PlayHalfAddr);
	}
	else //v1.07�ȑO
	{
		LOAD_V(playAddr32);
		_PlayAddr = (Uint16)playAddr32;
		_PlayHalfAddr = (Uint16)(_PlayAddr + (_LengthCount - 1024));
	}
	LOAD_V(_bPlay);
	LOAD_V(_bRepeat);
	if (MAINBOARD_GetStateVersion() >= 31) //Kitao�ǉ��Bv1.40�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_bStream);
	}
	else
		_bStream = FALSE;
	if (MAINBOARD_GetStateVersion() >= 9) //Kitao�ǉ��Bv0.65�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_SampleFreq);
	}
	else
	{
		LOAD_V(_OldSampleFreq);
		_SampleFreq = (double)_OldSampleFreq;
	}
	set_DP(); //Kitao�ǉ��B_SampleFreq����_DP���v�Z����Bv1.08
	LOAD_V(_Phase);
	if (MAINBOARD_GetStateVersion() < 26) //Kitao�ǉ��Bv1.11���O�̃Z�[�u�t�@�C���Ȃ�
		LOAD_V(bInterruptHalf); //���ݔ�g�p�B�_�~�[�ǂݍ��݁B

	LOAD_V(_WrittenSampleCount);
	LOAD_V(_PlayedSampleCount);
	LOAD_V(_PlayedSampleCountDecimal);

	_CDDAAjustCount = 0; //v2.32�ǉ��B���Ⴂ�Ō듮��(���A�W���X�g�̊��ő傫�Ȓl��ǂݍ��ނƌ듮��)���邱�Ƃ�h�����߁A�A�W���X�g�J�E���^�͏�Ƀ��Z�b�g�ŁB

	LOAD_V(_ReadBuffer);
	if (MAINBOARD_GetStateVersion() == 29) //Kitao�ǉ��Bv1.31�`1.37�̃Z�[�u�t�@�C���Ȃ�
		LOAD_V(_bDecReadBuffer); //���ݔ�g�p�B�_�~�[�ǂݍ��݁B
	if (MAINBOARD_GetStateVersion() >= 30) //Kitao�ǉ��Bv1.38�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_WriteBuffer);
	}
	else
		_WriteBuffer = 0;

	//����6�͌��ݔ�g�p�B0�ŃZ�[�u����Ă���̂ŗ\���̈�Ƃ��Ďg�p�ł���B
	LOAD_V(_SrcIndex);
	LOAD_V(_DstIndex);
	LOAD_V(_Sample);
	LOAD_V(_Error);
	LOAD_V(_nDstSample);
	LOAD_V(_nSrcSample);

	LOAD_V(_CurrentVolume);
	set_VOL(); //Kitao�ǉ��Bv1.08
	LOAD_V(_VolumeStep);
	LOAD_V(_bFadeIn);
	LOAD_V(_bFadeOut);
	LOAD_V(_FadeClockCount);
	LOAD_V(_FadeCycle);

	LOAD_V(ad_sample);
	LOAD_V(ad_ref_index);
	
	return TRUE;
}

#undef SAVE_V
#undef SAVE_A
#undef LOAD_V
#undef LOAD_A

