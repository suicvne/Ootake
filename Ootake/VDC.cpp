/******************************************************************************
Ootake
�E�X�[�p�[�O���t�B�b�N�X�ɑΉ������Bv0.89
�EVblank�O��̎��Ԃ����@��菭�Ȃ��悤�Ȃ̂ŁA�P�t���[����263���C���Ƒz�肵�A
  Vblank�O���CPU�p���[�𑽂��g����悤�ɂ����B(���@�ɋ߂��������x�ɂȂ����͂�)
�E���X�^���荞�݂̃^�C�~���O�����@�ɋ߂Â����B�܂��AGUI��CPU���j���[����蓮��
  �̒������ł���悤�ɂ����B
�ERCR�̒l���X�V���ꂽ�Ƃ��ɂ܂����荞�ݗv�����s���Ă��Ȃ������ꍇ�A���荞�݃��C
  ���ォ�ǂ������`�F�b�N���Ă����Ƀ��X�^���荞�ݗv�����s���悤�ɂ����B�i�P���C
  �����ɍׂ������X�^���荞�݂���\�t�g�ł��A��ʂ�����邱�ƂȂ��m���Ƀ��X�^��
  �荞�݂𔭐������邽�߁j
�E�ł��邾������ɋ߂�����������邽�߂ɁA������CPU,CD-ROM,APU,�^�C�}�[,�}�E�X
  �̃N���b�N��i�߂�悤�ɂ����B
�ETV�ւ̐����\���J�n�ʒu�����j�[�N�ȃ\�t�g�ɂ��Ή������B
�ETV�ւ̐����\���J�n�ʒu�����j�[�N�ȃ\�t�g�ɂ��Ή������Bv0.57�B
�EVblank���荞�݂����郉�C����"DISPLAY_STARTLINE + _ScreenH + 2"(�����Ă��̃\
  �t�g��262)�Ƃ����B���ꂪ263���C�����z���Ă���ꍇ�́A263���C���ڂ�Vblank���N
  �����悤�ɂ����Bv1.40
�EVCR��4��菬�����ꍇ�A���̂Ԃ񑁂߂�Vblank���荞�݂��N�����悤�ɂ����Bv0.81
�EVRAM-SATB�Ԃ�DMA�]������CPU�N���b�N�����256�T�C�N��(DMA�]���Ȃ̂łقƂ�Ǐ�
  ��Ȃ��Ɛ���)�Ƃ����Bv1.14�B
�EVBlank���荞�݂����肵�ē`���邽�߁AVRAM-SATB�Ԃ�DMA�]������CPU�N���b�N�����
  VBlank�J�n�����P���C���ォ�炨���Ȃ��悤�ɂ����Bv0.82�B
�EVRAM-SATB�Ԃ�DMA�]������VRAM���C�g���N�������ꍇ�́ACPU���X�g�[��������悤��
  �����Bv0.87�B��񌳁FKi����
�EVRAM-VRAM�Ԃ�DMA�]���J�n�����ɂ����鎞�Ԃ�CPU���Z��32�N���b�N(�S���̐���B��
  �̒l���ƃl�N�^���X���X���[�Y�ɓ���)�Ƃ��A���m�Ȏ���(���@�Ɠ������͖��m�F)�o��
  ��Ɋ����̊��荞�݂𔭐�������悤�ɂ����Bv0.82�B
�EVRAM���C�g���ɃE�F�C�g������悤�ɂ����Bv0.82�B
�EMWR���W�X�^(��������)��ύX�����Ƃ��ɁA�������}�b�v�������ɂ͍X�V�����AVblank
  ���ԂōX�V����悤�ɂ����B�i�����_�L���[�u�̃v�����[�O�ASUPER���S�̗D���Ҕ��\
  ���ɉ�ʂ��������A���̑���ʐ؂�ւ����Ɉ�u��ʂ��������������j
�E�X�v���C�g�������Č��i�X�v���C�g�I�[�o�[���������ꍇ�I�[�o�[�Ԃ�̃X�v���C�g
  �͕\�����Ȃ��j����ݒ��t�����B�i�p���[���[�O�R�̑ŐȌ��ʕ\�������@���l�ɂ�
  �邽�߂ɕK�v�j
�EVRAM���[�h���ɁA�A�h���X���W�X�^(AR)��VDC_VRR�ł͂Ȃ��Ƃ���VRAM�̓��e��Ԃ�
  �悤�ɂ����B(21�G�����ł̕�������������)�Bv0.72�B
�ESAT(�X�v���C�g���)�̃p�^�[���A�h���X�̎w���bit0�`10�܂ŗL���Ƃ����B(�ۂ���
  �郁�C���̃I�[�v�j���O��A�V�X�l���̃G���h��ʓ��ŃX�v���C�g�̂��݂��o�Ă���
  ���Ă����̂�����)�Bv0.70
�ECPU�ɃI�[�o�[�N���b�N�@�\��t�����B
�EVDC�X�e�[�^�X�́ARead�����ƕK���N���A�����悤�ɂ����B
�EBYR���W�X�^�ւ̏������݂��s��ꂽ�ۂɁA�܂����̃��C���̕`����I���Ă��Ȃ���
  ���ꍇ��LineCounter�����������C���N�������g����悤�ɂ����B�_���W�����G�N�X
  �v���[���[�A�p�b�N�����h�A�G�^�[�i���V�e�B���ŕK�v�Bv0.62�X�V
�E�ǂ����Ă����x�^�C�~���O�����킸��肪�N����Q�[���ɂ́A�p�b�`�Ƃ���SATB�]��
  ���ɃE�F�C�g�����ē��삳����悤�ɂ����B�i���o�[�W�����ł͎g�p�̕K�v�Ȃ��j
�E���X�^���荞�݂̗v�����`����Ă��Ȃ������ꍇ�A�I�[�o�[�N���b�N���Ăł����̃�
  �C���`�撆�ɓ`����悤�ɂ����B�i�V���r�r���}���Q�ŋH�ɂP�t���[�����ꂽ��ʂ�
  �o���������jv0.57�B�����@�Ŋm�F�����Ƃ���A���@�ł��P�t���[�������̂�
  �f�t�H���g������(^^; ���V�g�̎��ŕ`�悪���ꂽ�̂ŃV���r�r���}���Q�ȊO�ł͂�
  �̏������J�b�g�����Bv0.61
�EVBlank���N�����ۂ�VCR�̒l���傫���ꍇ�AVBlank���N�������C����x�点��悤��
  �����Bv1.00�B"���_�`��"�̃X�e�[�^�X�\��
�EVRAM-VRAM�Ԃ�DMA�]���̍ہADCR��bit4�������Ă�����A�`����Ԓ��ɂ͓]�������A
  VBlank���Ԃ�҂��ē]������悤�ɂ����B�����O���b�T�[�ŕK�v�Bv1.03
�E�X�v���C�g����������BG�����������A�\�[�X�̈Ӗ����킩��Â炭�Ȃ�Ȃ��͈͂ō�
  ���������Bv1.08
�E�������̂���VCE.c �������֓��������Bv1.11�B
�E�X�v���C�g�\�������ŁA((MWR & 0xC) == 0x4)�̂Ƃ��̓p�^�[���C���f�b�N�X��2bit
  �p�^�[�����[�h�ɂȂ邱�Ƃ����������BKi�����莑���������������܂����B"�t
  �@�C�e�B���O����"�̃X�v���C�g�\��������ɂȂ����Bv1.13�B
�EVCE��Read���ɖ����ȃ|�[�g���w�肳��Ă����ꍇ�A0�łȂ�0xFF��Ԃ��悤�ɂ����B
  "�~�Y�o�N��`��"�S�ʂ̊�N���̕s��������B"�X�^�[�g�����O�I�f�b�Z�C�Q"����
  �삷��悤�ɂȂ����Bv1.62
�EVDC�|�[�g�̃A�N�Z�X�E�F�C�g�́A�o�[�X�g���[�h���̓m���E�F�C�g�Ƃ����B������
  �Q�[���̑��x,�^�C�~���O�����@�ɋ߂Â����B(���@�ł��̎��������������͖�����
  )�BVCE�|�[�g�̃A�N�Z�X�E�F�C�g�����l��������Ȃ����A����͖��m��̂��߁A�G
  �~�����[�g���x��D�悵�āA�o�[�X�g���[�h���ł��E�F�C�g�����Ă��܂��Bv2.07
�E�����\���J�n�ʒu������ȃP�[�X�ɑΉ������B�t�@�C�i���u���X�^�[�̃X�^�[�g�f��
  �����@���l�ɂȂ����Bv2.14

Copyright(C)2006-2013 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[VDC.c]
		�u�c�b�̎������s�Ȃ��܂��B

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
#include <string.h>
#include <malloc.h>
#include "VDC.h"
#include "MainBoard.h"
#include "App.h"
#include "Printf.h"

extern Sint32 gCPU_ClockCount;	//v2.00�ǉ��B�������̂��߃J�E���^���O���[�o�����B
extern Sint32 gCPU_Transfer;	//v2.31�ǉ��BCPU���]�����߂����s�����ǂ���

/*
	Kitao�X�V�Bv0.81�B�P�t���[�������X�^���荞�݉\�ő�͈͂�263���C���Ƃ����B�\�t�g�̓��쁕�^�C�~���O�����@�ɋ߂��Ȃ����B

	�P���C�����̂b�o�t�T�C�N�����́A
		7159090 / 60 / 263 ~= 453.68124207858048162230671736375
		(119318.16666666666666666666666667 / 263)
*/
//define VDC_CYCLESPERLINE ��MAX_SCANLINE ��VDC.h �ɒ�`�B

#define NUM_SPRITES			64

#define MAWR	_Regs[_VN][VDC_MAWR]
#define MARR	_Regs[_VN][VDC_MARR]
#define VWR		_Regs[_VN][VDC_VWR]
#define VRR		_Regs[_VN][VDC_VRR]
#define CR		_Regs[_VN][VDC_CR]
#define RCR		_Regs[_VN][VDC_RCR]
#define BXR		_Regs[_VN][VDC_BXR]
#define BYR		_Regs[_VN][VDC_BYR]
#define MWR		_Regs[_VN][VDC_MWR]
#define HSR		_Regs[_VN][VDC_HSR]
#define HDR		_Regs[_VN][VDC_HDR]
#define VPR		_Regs[_VN][VDC_VPR]
#define VDW		_Regs[_VN][VDC_VDW]
#define VCR		_Regs[_VN][VDC_VCR]
#define DCR		_Regs[_VN][VDC_DCR]
#define SOUR	_Regs[_VN][VDC_SOUR]
#define DESR	_Regs[_VN][VDC_DESR]
#define LENR	_Regs[_VN][VDC_LENR]
#define SATB	_Regs[_VN][VDC_SATB]

#define HSW		(HSR & 0xFF) //Kitao�X�V
#define VSW		(VPR & 0xFF) //Kitao�X�V
#define HDS		((HSR & 0x7F00) >> 8)
#define HDE		((HDR & 0x7F00) >> 8)
#define HDW		(HDR & 0x7F) //Kitao�ǉ�
#define VDS		(VPR >> 8)

#define DISPLAY_STARTLINE	((VPR & 0x1F)+1+VDS+2) //Kitao�X�V
#define DISPLAY_ENDLINE		(DISPLAY_STARTLINE+VDW+1)

//Kitao�ǉ��Bv2.06
static BOOL		_bSpriteLayer;
static BOOL		_bSprite2Layer;
static BOOL		_bBGLayer;
static BOOL		_bBG2Layer;

//Kitao�X�V�B�e�[�u�����ŏ��ɐ錾���X�[�p�[�O���t�B�b�N�X�p��VDC�Q�Ԃ�̕ϐ����g�p�B
static const Uint8		_IncSizeTable[4] = {1, 32, 64, 128};
static const Uint32		_HeightTable[4] = {16, 32, 64, 64};
static const Uint8		_BGWidthTable[4] = {32, 64, 128, 128};
static Uint32 			_PatternLUT[256][2];

static Sint32		_SuperGrafx; //Kitao�ǉ��B1�Ȃ�X�[�p�[�O���t�B�b�N�X���[�h�B�ʏ��0�B
static Sint32		_VN; //Kitao�ǉ��B�A�N�Z�X����VDC�i���o�[(0or1)�B�X�p�O���p�B�ʏ��PC�G���W���̏ꍇ���0�B
static Sint32		_VPC[8]; //Kitao�ǉ��BVPC�̒l�ۊǗp

static Uint16		_Regs[2][32];
static Uint32		_AR[2];

static Uint8		_VideoRam[2][65536]; //VRAM 64KB
static Uint16*		_pwVideoRam[2];
static Uint16		_ReadData[2]; //Kitao�ǉ��B���ۂ�VRAM���[�h�A�N�Z�X��VDC�|�[�g��"MARR���C�g��"�ɂ����Ȃ���(����)�B

static Sint32		_ScreenW[2];
static Sint32		_ScreenH[2];
static Uint32		_BGH[2];
static Uint32		_BGW[2];

static Uint16		_VdcAddrInc[2] = {1,1};
static Uint8		_VdcStatus[2] = {0,0};

static Uint32*		_pScreenBuf; //Kitao�ǉ�v1.11�B���C���o�b�t�@���g�킸��ScreenBuf�ɒ��ڏ������ނ悤�ɂ����B�������B
static Uint32		_LineBufVDC2[512]; //Kitao�ǉ��B�X�[�p�[�O���t�B�b�N�X�����Ŏg�p�B
static Uint8		_BgPutBuf[2][512]; //Kitao�ǉ�v1.11�B0�ȊO�Ȃ�BG�\���ς�(�����ȊO)�̃h�b�g�B
static Uint8		_SpPutBuf[2][512]; //Kitao�ǉ�v1.11�B1�Ȃ�X�v���C�g�\���ς�(�����ȊO)�̃h�b�g�B2�Ȃ�BG�ɉB�ꂽ�X�v���C�g�h�b�g������(�X�p�O���p)�B�ŏ�ʃr�b�g��1�Ȃ�X�v���C�g�i���o�[0�̃h�b�g���\���ς�(�Փ˔���Ŏg�p)�B

static Sint32		_RasterCounter[2];
static BOOL			_bRasterRequested[2]; //Kitao�ǉ��B���̃��C���̃��X�^���荞�ݗv�����I���Ă�����TRUE
static Sint32		_LineCounter[2];
static Sint32		_LineCountMask[2];
static Sint32		_LineOffset[2]; //Kitao�ǉ��B�`�撆�Ɂu�`��J�n���C���v���ύX���ꂽ�ꍇ�A���̃I�t�Z�b�g�𗘗p���Ď��@���l�̕`����Č�����Bv1.30�B�����݂͂P�t���[�����ƂɃ��Z�b�g�����̂ŃX�e�[�g�Z�[�u�̕K�v�͖������A�݊��̂��߂ɃZ�[�u���Ă���B
static Uint16		_PrevVSW[2]; //v2.09�ǉ��B�X�L�������C���擪����VSW�B���P�t���[�����ƂɍX�V�����̂ŃX�e�[�g�Z�[�u�̕K�v�͖���

static BOOL			_bUpdateSATB[2];
static Uint32		_SpDmaCount[2];
static Sint32		_SpDmaStole[2];
static Uint32		_VramDmaCount[2]; //Kitao�ǉ��Bv0.82
static BOOL			_bVramDmaExecute[2]; //Kitao�ǉ��Bv1.02

static Uint32		_MaxSpPerLine[2]; //Kitao�ǉ��Bv2.63
static BOOL			_bSpOver[2];
static BOOL			_bOverlap[2]; //Kitao�ǉ�
static BOOL			_bBurstMode[2] = {FALSE, FALSE};
static BOOL			_bVDCAccessWait[2] = {TRUE, TRUE}; //Kitao�ǉ��Bv2.08
static BOOL			_bMWRchange[2]; //Kitao�ǉ�

static Uint8		_BgTileCache[2][2048][8*8];
static Uint8		_SpTileCache[2][512][16*16];

static Uint16		_SpRam[2][64*4];

static Sint32		_TvStartLine[2]; //Kitao�ǉ�
static Sint32		_TvStartLineAdjust[2]; //Kitao�ǉ��B�Q�[�����Ɏ蓮�ŃA�W���X�g�p�B���ݖ��g�p�ŏ����p�Bv2.47
static Sint32		_VblankLine[2]; //Kitao�ǉ�
static Sint32		_VblankLineTop[2]; //Kitao�ǉ��B�`��J�n���C������VblankLine�̒l�Bv1.19�ǉ��B���P�t���[�����ƂɍX�V�����̂ŃX�e�[�g�Z�[�u�̕K�v�͖���
static BOOL			_bVDCleared[2]; //Kitao�ǉ��BVBlank���荞�ݗv����CPU�����X���[�����܂܎��t���[���̕`��J�n�ɗ����ꍇTRUE�ɂ��A������VBlank�v���X�e�[�^�X���N���A���A���̃t���[�����Œx��VBlank�𔭐�������Bv1.63
static Uint16		_prevCR[2]; //Kitao�ǉ��B�P���C���O��CR�̒l�Bv1.21�B���P�t���[�����ƂɍX�V�����̂ŃX�e�[�g�Z�[�u�̕K�v�͖���

static Sint32		_ScanLine;
static Sint32		_DisplayCounter;
static BOOL			_bRasterLate; //Kitao�ǉ�
static Sint32		_bForceRaster; //Kitao�ǉ��B���X�^���荞�݂�CPU�ŏ��������܂ő҂�(CPU���I�[�o�[�N���b�N����)�Ȃ�TRUE�B�V���r�r���}���Q�Ŏg�p�B
static Sint32		_bForceVBlank; //Kitao�ǉ��BVBlank���荞�݂�CPU�ŏ��������܂ő҂�(CPU���I�[�o�[�N���b�N����)�Ȃ�TRUE�B���f�B�\�[�h�Ŏg�p�B
static Sint32		_RasterTimingType = 2;//Kitao�ǉ��B���X�^�[���荞�݂�����^�C�~���O�𒲐����邽�߂̕ϐ��B1=���߂�CPU�Ƀ��X�^�^�C�~���O��`����\�t�g�B2=�ʏ�B3=�x�߂�CPU�Ƀ��X�^�^�C�~���O��`����\�t�g�B
static Sint32		_RasterTimingCount; //Kitao�ǉ�
static Sint32		_AutoRasterTimingType; //Kitao�ǉ��B�����Ń��X�^�[�^�C�~���O��ݒ肵�Ă���Q�[���̏ꍇ����_RasterTimingType������B�����łȂ��ꍇ�̓m�[�}��(2)������B
static Sint32		_OverClockType = 0; //Kitao�ǉ�
static Sint32		_OverClockCycle = 0; //Kitao�ǉ�
static Sint32		_AutoOverClock = -1; //Kitao�ǉ�
static BOOL			_bOverClockNow = FALSE; //v1.61�ǉ�
static Sint32		_WaitPatch; //Kitao�ǉ�
static Sint32		_bPerformSpriteLimit; //Kitao�ǉ��BTRUE�Ȃ�X�v���C�g�������Č��i�X�v���C�g�I�[�o�[���������ꍇ�I�[�o�[�Ԃ�̃X�v���C�g�͕\�����Ȃ��j�B�p���[���[�O�R�̑ŐȌ��ʕ\�������@���l�ɂ��邽�߂ɕK�v�B
static Sint32		_bAutoPerformSpriteLimit; //Kitao�ǉ��B�����ŃX�v���C�g������ݒ肵�Ă���Q�[���̏ꍇTRUE�B
static Uint32		_CpuPastCount;//Kitao�ǉ��Bv1.00�B�P���C�����̂ǂ��܂�CPU������i�߂����B(�P���C���ŏ����������̂ŃX�e�[�g�Z�[�u�̕K�v�͂Ȃ�)
static BOOL			_bIRQ1CancelExecute;//Kitao�ǉ��Bv1.03�B���ݔ�g�p�B�X�e�[�g���[�h�̌݊��̂��߂Ɏc���Ă���B

static Sint32		_DrawFrame; //Kitao�ǉ��B�����̕ϐ��͖��񏉊��������̂ŃX�e�[�g�Z�[�u�̕K�v�͂Ȃ��B

static Uint32		_ClockCounter; //���ݔ�g�p

static BOOL			_bShinMegamiTensei; //v2.20�ǉ�
static BOOL			_bWorldStadium91; //v2.64�ǉ�
static BOOL			_bEikanKimi; //v2.70�ǉ�
static BOOL			_bPowerLeague; //v2.70�ǉ�
static BOOL			_bTheProYakyuu; //v2.70�ǉ�

/*
	Kitao�X�V�Bv1.11�B�������̂���VCE.c �̏����������֓��������B
	[DEV NOTE]
	Kitao�X�V�B32�r�b�g�J���[�ɂ��Ή����邽�߁AVCE.c�ł�RGB�̕ϊ������������ɁARGB333�̂܂܃f�[�^�𑗂�o���悤�ɂ����B
	���ݔ������[�h�͖������iDDSCREEN�̂ق��Ɏ�������j�B
*/
static Uint8		_DCC;
static Uint16		_ColorTableAddr;
static Sint32		_TvStartPos; //Kitao�ǉ��B�e���r��̐����\���J�n�ʒu
static Sint32		_TvWidth; //Kitao�ǉ��B�e���r��̐����\����(�𑜓x)
static Sint32		_TvMax; //Kitao�ǉ��B�e���r��̐����\���ŏI�ʒu�Bv1.11�ǉ�

static Uint16		_Palette333[512]; //Kitao�ǋL�B0�`255��BG�p�B256�`511���X�v���C�g�p
static Uint32		_PaletteBG[256]; //Kitao�X�V�B�`�掞�Ɉ����₷���悤��Uint32�Łu0RGB�v��32�r�b�g�ŕێ��B
static Uint32		_PaletteSP[256]; //Kitao�ǉ��B�R�[�h�̍������̂��߁A�X�v���C�g�p��BG�p�ŕ������B
static Uint16		_ColorLatch;

static Sint32		_VpcPriority[4]; //Kitao�ǉ��B�X�[�p�[�O���t�B�b�N�X�p�B�`��̗D�揇�ʁB�S�̈�Ԃ�(�����炭[2][3]�͂ǂ��炩�P�����g��ꂸ�R�̈�ƂȂ�)
static Sint32		_VpcBorder1; //Kitao�ǉ��B�X�[�p�[�O���t�B�b�N�X�p�B�̈�����R�ɕ����邽�߂̋��E�c���P
static Sint32		_VpcBorder2; //Kitao�ǉ��B�X�[�p�[�O���t�B�b�N�X�p�B�̈�����R�ɕ����邽�߂̋��E�c���Q


/*-----------------------------------------------------------------------------
	[update_bg_tile_cache]
		�a�f�p�^�[�����G���R�[�h���ێ����܂��B
-----------------------------------------------------------------------------*/
//Kitao�X�V�Bfill_tile_cache()�Ɠ������č����������Bv1.08
//			 �^�C���L���b�V�����X�V����Ă��邩�ǂ����̔��f��drawBgLine�̂ق��ōs���悤�ɂ��č������Bv1.65
static inline void
update_bg_tile_cache(
	Uint32	cg_addr) //Kitao�X�V�Bfill_tile_cache()�Ɠ������č����������Bv1.08
{
	Uint32		D0, D1, D2, D3;
	Uint8*		pVRAM1;		// for D0 and D1
	Uint8*		pVRAM2;		// for D2 and D3
	Uint32*		pPixel;		// pixel 0-3 & 4-7

	//Kitao�X�V�B�g���ϐ������Ȃ����V���v�������č������Bv2.00
	pPixel = (Uint32*)&_BgTileCache[_VN][cg_addr][0];
	pVRAM1 = &_VideoRam[_VN][(cg_addr << 5) +  0];
	pVRAM2 = &_VideoRam[_VN][(cg_addr << 5) + 16];
	//��8�s�N�Z�����c8��Ԃ�G���R�[�h����B
	D0 = *pVRAM1++; D1 = *pVRAM1++; D2 = *pVRAM2++; D3 = *pVRAM2++;
	*pPixel++ = _PatternLUT[D0][0] | (_PatternLUT[D1][0] << 1) | (_PatternLUT[D2][0] << 2) | (_PatternLUT[D3][0] << 3); //�܂�pixel0-3�������Bv2.00�X�V
	*pPixel++ = _PatternLUT[D0][1] | (_PatternLUT[D1][1] << 1) | (_PatternLUT[D2][1] << 2) | (_PatternLUT[D3][1] << 3); //������pixel4-7�������B
	D0 = *pVRAM1++; D1 = *pVRAM1++; D2 = *pVRAM2++; D3 = *pVRAM2++;
	*pPixel++ = _PatternLUT[D0][0] | (_PatternLUT[D1][0] << 1) | (_PatternLUT[D2][0] << 2) | (_PatternLUT[D3][0] << 3);
	*pPixel++ = _PatternLUT[D0][1] | (_PatternLUT[D1][1] << 1) | (_PatternLUT[D2][1] << 2) | (_PatternLUT[D3][1] << 3);
	D0 = *pVRAM1++; D1 = *pVRAM1++; D2 = *pVRAM2++; D3 = *pVRAM2++;
	*pPixel++ = _PatternLUT[D0][0] | (_PatternLUT[D1][0] << 1) | (_PatternLUT[D2][0] << 2) | (_PatternLUT[D3][0] << 3);
	*pPixel++ = _PatternLUT[D0][1] | (_PatternLUT[D1][1] << 1) | (_PatternLUT[D2][1] << 2) | (_PatternLUT[D3][1] << 3);
	D0 = *pVRAM1++; D1 = *pVRAM1++; D2 = *pVRAM2++; D3 = *pVRAM2++;
	*pPixel++ = _PatternLUT[D0][0] | (_PatternLUT[D1][0] << 1) | (_PatternLUT[D2][0] << 2) | (_PatternLUT[D3][0] << 3);
	*pPixel++ = _PatternLUT[D0][1] | (_PatternLUT[D1][1] << 1) | (_PatternLUT[D2][1] << 2) | (_PatternLUT[D3][1] << 3);
	D0 = *pVRAM1++; D1 = *pVRAM1++; D2 = *pVRAM2++; D3 = *pVRAM2++;
	*pPixel++ = _PatternLUT[D0][0] | (_PatternLUT[D1][0] << 1) | (_PatternLUT[D2][0] << 2) | (_PatternLUT[D3][0] << 3);
	*pPixel++ = _PatternLUT[D0][1] | (_PatternLUT[D1][1] << 1) | (_PatternLUT[D2][1] << 2) | (_PatternLUT[D3][1] << 3);
	D0 = *pVRAM1++; D1 = *pVRAM1++; D2 = *pVRAM2++; D3 = *pVRAM2++;
	*pPixel++ = _PatternLUT[D0][0] | (_PatternLUT[D1][0] << 1) | (_PatternLUT[D2][0] << 2) | (_PatternLUT[D3][0] << 3);
	*pPixel++ = _PatternLUT[D0][1] | (_PatternLUT[D1][1] << 1) | (_PatternLUT[D2][1] << 2) | (_PatternLUT[D3][1] << 3);
	D0 = *pVRAM1++; D1 = *pVRAM1++; D2 = *pVRAM2++; D3 = *pVRAM2++;
	*pPixel++ = _PatternLUT[D0][0] | (_PatternLUT[D1][0] << 1) | (_PatternLUT[D2][0] << 2) | (_PatternLUT[D3][0] << 3);
	*pPixel++ = _PatternLUT[D0][1] | (_PatternLUT[D1][1] << 1) | (_PatternLUT[D2][1] << 2) | (_PatternLUT[D3][1] << 3);
	D0 = *pVRAM1++; D1 = *pVRAM1++; D2 = *pVRAM2++; D3 = *pVRAM2++;
	*pPixel++ = _PatternLUT[D0][0] | (_PatternLUT[D1][0] << 1) | (_PatternLUT[D2][0] << 2) | (_PatternLUT[D3][0] << 3);
	*pPixel   = _PatternLUT[D0][1] | (_PatternLUT[D1][1] << 1) | (_PatternLUT[D2][1] << 2) | (_PatternLUT[D3][1] << 3);
}


/*-----------------------------------------------------------------------------
	[update_sp_tile_cache]
		�r�o�p�^�[�����G���R�[�h���ێ����܂��B
-----------------------------------------------------------------------------*/
//Kitao�X�V�Bfill_tile_cache()�Ɠ������č����������Bv1.08
//			 �^�C���L���b�V�����X�V����Ă��邩�ǂ����̔��f��draw_sp_line�̂ق��ōs���悤�ɂ��č������Bv1.65
static inline void
update_sp_tile_cache(
	Uint32	pc) //Kitao�X�V�Bfill_tile_cache()�Ɠ������č����������Bv1.08
{
	int			i;
	Uint8*		pVRAM;
	Uint32*		pPixel; //pixel 0-3 & 4-7�Bv2.03�X�V�B

	//Kitao�X�V�B�g���ϐ������Ȃ����V���v�������č������Bv2.03
	pPixel = (Uint32*)&_SpTileCache[_VN][pc][0];
	pVRAM = &_VideoRam[_VN][pc << 7];

	//��16�s�N�Z�����c16��Ԃ�G���R�[�h����B
	for (i=0; i<16; i++)
	{
		*pPixel++ =  _PatternLUT[pVRAM[1]][0] | (_PatternLUT[pVRAM[33]][0] << 1) | (_PatternLUT[pVRAM[65]][0] << 2) | (_PatternLUT[pVRAM[97]][0] << 3); //�܂�pixel0-3�������Bv2.03�X�V
		*pPixel++ =  _PatternLUT[pVRAM[1]][1] | (_PatternLUT[pVRAM[33]][1] << 1) | (_PatternLUT[pVRAM[65]][1] << 2) | (_PatternLUT[pVRAM[97]][1] << 3); //������pixel4-7�������B
		*pPixel++ =  _PatternLUT[pVRAM[0]][0] | (_PatternLUT[pVRAM[32]][0] << 1) | (_PatternLUT[pVRAM[64]][0] << 2) | (_PatternLUT[pVRAM[96]][0] << 3); //�܂�pixel0-3�������Bv2.03�X�V
		*pPixel++ =  _PatternLUT[pVRAM[0]][1] | (_PatternLUT[pVRAM[32]][1] << 1) | (_PatternLUT[pVRAM[64]][1] << 2) | (_PatternLUT[pVRAM[96]][1] << 3); //������pixel4-7�������B
		pVRAM++; pVRAM++;
	}
}


static inline void
invalidate_tile_cache()
{
	int		i;

	for (i = 0; i < 2048; i++)
		_BgTileCache[_VN][i][0] = 0x20;

	for (i = 0; i < 512; i++)
		_SpTileCache[_VN][i][0] = 0x20;
}


/*-----------------------------------------------------------------------------
	[write_vram]
		�r�f�I�������Ƀf�[�^���������݂܂��B
		(�^�C���L���b�V���Ή�) 
-----------------------------------------------------------------------------*/
static inline void
write_vram(
	Uint16	addr,
	Uint16	data)
{
	//PRINTF("addr, data = %X , %X", (int)addr, data); //Test�p

	if ((addr < 0x8000)&&(_pwVideoRam[_VN][addr] != data))
	{
		// �uCG �p�^�[�����ύX���ꂽ�v�t���O�����
		// �uSG �p�^�[�����ύX���ꂽ�v�t���O�𗧂Ă�B
		// �Ȃ��������܂ꂽ�f�[�^�� CG/SG �p�^�[���Ƃ͌���Ȃ����A
		// ����͂��܂�Ȃ��B 
		_BgTileCache[_VN][addr >> 4][0] |= 0x20;
		_SpTileCache[_VN][addr >> 6][0] |= 0x20;
		
		_pwVideoRam[_VN][addr] = data;
	}
}


/*-----------------------------------------------------------------------------
	[update_satb]
		�r�`�s�a���X�V���܂��B
-----------------------------------------------------------------------------*/
//v1.61�X�V�Bmemcpy�ō������B
static inline void
update_satb(
	Uint16	addr)
{
	Uint32	i = sizeof(Uint16) * 256;

	if (addr > 0x7F00)
	{
		if (addr < 0x8000)
			i = sizeof(Uint16) * (0x8000 - addr);
		else
			return;
	}
	memcpy(_SpRam[_VN], &_pwVideoRam[_VN][addr], i);
}


/*-----------------------------------------------------------------------------
	[do_vram_vram_dma]
		VRAM-VRAM �Ԃ�DMA�]�����s�Ȃ��܂��B

	[NOTE]
		�P�o�C�g�]������̂ɉ��b�o�t�T�C�N��������̂��͕s���B
		VDC_STAT_DV �� (DCR & 2) == 0 �ł��Z�b�g�����̂��ǂ����͖��m�F�B��Kitao�X�V�B�Z�b�g����Ȃ��B�O���f�B�E�X�Ŋm�F�B
-----------------------------------------------------------------------------*/
static void
do_vram_vram_dma()
{
	Uint16	srcInc;
	Uint16	dstInc;

	//PRINTF("LENR, DCR , CR = %d , %X , %X", (int)LENR,DCR,CR); //Test�p

	//Kitao�ǉ��BDCR��bit4�������Ă��āA�`����Ԓ��ɓ]�����悤�Ƃ����ꍇ�A�]����VBlank���Ԃɍs���悤�ɂ����B
	if ((DCR & 0x10)&& //�Q�l�FDCR��bit4��1�c�����O���b�T�[�C��̃}�X�J���[�h�C���H���t�B�[�h�CBURAI�B�����炭�A�`����Ԓ��̓]����h���t���O�H
		(CR & 0xC0)&& //��ʕ\���I���̏ꍇ�̂݁B���ꂪ�Ȃ��Ɠ�̃}�X�J���[�h�ŉ�ʉ����B��ʕ\���I�t�̂Ƃ��͂����]���B
		(_DisplayCounter >= DISPLAY_STARTLINE)&&(_DisplayCounter < _VblankLineTop[_VN])) //�`����Ԓ��ɓ]�����悤�Ƃ���
	{
		//�����O���b�T�[�ŃX�N���[�����ɃX�e�[�^�X��ʂ�����Ȃ����߂ɕK�v�B
		_bVramDmaExecute[_VN] = TRUE;
	}
	else //�ʏ�
	{
		//Kitao�ǉ��B�����Ɋ��荞�ݗv�������s����ƃl�N�^���X�̂S�ʈȍ~�̃X�N���[���ł������肷��̂Ő��N���b�N�o�ߌ�Ɋ��荞�ݗv���B
		_VramDmaCount[_VN] = 24; //24�N���b�N(�S���̐���)��ɁA"DMA�]���J�n����"�̊��荞�ݗv�������邱�Ƃɂ����B�l�N�^���X�ōœK�B�傫������Ɖ��Ƀm�C�Y���ڂ違���c�M���Ŗ��B
		
		//�Q�[�����͂����ɓ]������Ă��邱�Ƃ����҂��Ă���̂ŁA������VRAM������������B
		srcInc = (DCR & 4) ? -1 : 1;
		dstInc = (DCR & 8) ? -1 : 1;
		do
		{
			write_vram(DESR, _pwVideoRam[_VN][SOUR]);
			SOUR += srcInc;
			DESR += dstInc;
		} while (LENR--);
	}
}


//Kitao�ǉ��B�e���r��ʂ̐����\���J�n�ʒu��ݒ肷��B�\�����ϐ�(_TvMax)���ݒ肷��B
static void
setTvStartPos()
{
	Sint32	tvWidth =_TvWidth;

	if (_VN != 0) return; //�X�[�p�[�O���t�B�b�N�X�̏ꍇ�AVDC0�̂Ƃ������ݒ肷��悤�ɂ����B

	if (_TvWidth == 256)
	{
		_TvStartPos = (2 - HDS) * 8; //��256�̏ꍇ�قƂ�ǂ�HDS=2
		if (MAINBOARD_GetShowOverscanLeft() > 0) //���E�̃I�[�o�[�X�L�����G���A��\������ꍇ�Bv1.43�ǉ�
			tvWidth = 268;
	}
	else if (_TvWidth == 336)
	{
		_TvStartPos = (4 - HDS) * 8; //��352�̏ꍇ�A�قƂ�ǂ�HDS=3�ō��E8�h�b�g�����J�b�g�B�N�C�Y�a�l�̖�],�V�g�̎��Q�̃t�B�[���h���퓬(HDS=2)�͍�16�h�b�g���J�b�g�B�V�n����炤(HDS=3)�͉�368�ō�8�h�b�g�E24�h�b�g���J�b�g����336�h�b�g�Ƃ��ďo�́B
		if (MAINBOARD_GetShowOverscanLeft() > 0) //���E�̃I�[�o�[�X�L�����G���A��\������ꍇ�Bv1.43�ǉ�
			tvWidth = 352;
	}
	else //(_TvWidth == 512)
		_TvStartPos = (11 - HDS) * 8; //��512(�V���[���b�N�z�[���Y)�̏ꍇHDS=11�B��544���[�h�̏ꍇHDS=8(TV�X�|�[�c�o�X�P�̑I��I�����)�B

	if ((MAINBOARD_GetShowOverscanLeft() > 0)&&(_TvWidth != 512)) //���E�̃I�[�o�[�X�L�����G���A��\������ꍇ�Bv1.43�ǉ�
	{
		if (_TvWidth == 256)
		{
			if (_ScreenW[0] > 256)
			{
				if ((HDS > 4)||(_ScreenW[0] >= 256+16)) //HDS��4�ȉ��Ń\�[�X����272��菬�����ꍇ(264�BF1�p�C���b�g�Ȃ�)�́A�E�������̃\�[�X���ɂȂ�̂Ń|�W�V�����͂��炳�����̂܂܁B
					_TvStartPos -= 8;
			}
		}
		else if (_TvWidth == 336)
		{
			if (_ScreenW[0] > 336)
			{
				if ((HDS > 4)||(_ScreenW[0] >= 336+16)) //HDS��4�ȉ��Ń\�[�X����352��菬�����ꍇ(344�Ȃ�)�́A�E�������̃\�[�X���ɂȂ�̂Ń|�W�V�����͂��炳�����̂܂܁B
					_TvStartPos -= 8;
			}
		}
	}
	else //���E�̃I�[�o�[�X�L�����G���A��\�����Ȃ��ꍇ���A��512�̏ꍇ�Bv2.10�X�V
	{
		if (_ScreenW[0] < tvWidth)
			_TvStartPos -= (tvWidth - _ScreenW[0]) * 2;
	}

	if (_TvStartPos < 0) //VCE�̃h�b�g�N���b�N�����ScreenWidth���ύX���ꂽ�ꍇ�ɋN���蓾��BTV�X�|�[�c�o�X�P�Ŋm�F�B
		_TvStartPos = 0;

	if (_ScreenW[0] > tvWidth) //V1.11�ǉ�
		_TvMax = tvWidth;
	else
		_TvMax = _ScreenW[0];

//Kitao�e�X�g�p
//PRINTF("ScanLine=%d, HDS=%X, ScreenW=%d, StartPos=%d , Max=%d", _ScanLine,HDS,_ScreenW[0],_TvStartPos,_TvMax);
/*
if (WINMAIN_GetBreakTrap())
{
	char s[100];
	sprintf(s,"ScanLine=%d, HDS=%X, ScreenW=%d, StartPos=%d , Max=%d", _ScanLine,HDS,_ScreenW[0],_TvStartPos,_TvMax);
	int ok;
	ok = MessageBox(WINMAIN_GetHwnd(),
			s,
			"Test",
			MB_YESNO);
	if (ok != IDYES)
		WINMAIN_SetBreakTrap(FALSE);
}
*/
}


//Kitao�ǉ��B�e���r��ʂ̐����\���J�n�ʒu��ݒ肷��B�\�����ϐ�(_TvMax)���ݒ肷��BApp.c, MainBoard.c ����I�[�o�[�X�L�����\���ؑ֎��ɗ��p�B
void
VDC_SetTvStartPos()
{
	_VN = 0;
	setTvStartPos();
}


//Kitao�ǉ��B�����\���J�n���C����VBlank�𔭐������郉�C�������߂�B�\���J�n���C�������j�[�N�ȃ\�t�g�ɂ��Ή������B
void
VDC_SetTvStartLine()
{
	Sint32	vdw0;
	Sint32	prevStartLine = _TvStartLine[_VN];

	if (VPR & 0x80) //VSW(VPR&0xFF)�����̐��Ȃ�
	{
		_TvStartLine[_VN] = VDS + (256 - VSW) + 18; //�V���[���b�N�z�[���Y�A�w�r�[���j�b�g�ɍ��킹��
		
		if (VCR > VDS)
			if ((VCR & 0x80) == 0)
				_TvStartLine[_VN] += 10 - (256 - VSW); //�V���[���b�N�z�[���Y�Q�A�w�r�[���j�b�g
	}
	else
	{
		_TvStartLine[_VN] = VDS + VSW + 10;
		
		if (VCR > VDS)
			if ((VCR & 0x80) == 0)
				_TvStartLine[_VN] += 10 - VSW; //�����֎�
		
		if ((VCR == 0x03)&&(VDW == 0xEF)&&(MWR == 0x00)) //�X�^�[���r�[���ŃI�[�o�[�X�L�����I�t�̂Ƃ��Ɉ�ԉ��̃��C�����؂��̂�����B
			_TvStartLine[_VN]++;						 //  ��K�Ōv���Ċm���߂ĂȂ������@�ł��؂�Ă��C������(���Ԃ���Ƃ��Ɋm�F)�B�ǂ���ɂ��Ă����₷���Ȃ�̂ł��̎����ɂ���Bv1.61
		if ((VCR == 0xF6)&&(VDW == 0xE0)&&(MWR == 0x50))
			_TvStartLine[_VN]++; //������h���L�����w�̍ŏI�Ό���Q�ʂŏ�ӂP���C��������Ȃ��悤�ɁB���@�ł��s�u�ɂ���ĂP���C���͗���Ă�����������Ȃ��Bv1.63
		if ((VCR == 0x04)&&(VDW == 0xE0)&&(MWR == 0x40))
			_TvStartLine[_VN]++; //�T�[�NIII�̃t�B�[���h��ʂŏ�ӂP���C��������Ȃ��悤�ɁB���@�ł��s�u�ɂ���ĂP���C���͗���Ă�����������Ȃ��Bv2.35

		if (VDS+VDW < 255)
		{
			vdw0 = (VDW & 511) + 1;
			if (vdw0 < 240)
			{
				if (VCR & 0x80)
					_TvStartLine[_VN] -= (240 - vdw0) / 2; //������h���L�����w�ŏ����_�ȉ��؂�̂Ă��x�X�g
				else
					_TvStartLine[_VN] -= (240 - vdw0 +1) / 2; //�u+1�v�̓_���C�A�X�v���X�̂��߂Ɏl�̌ܓ�(�f�B�X�v���C�ɂ���Ă͎��@�ōŏ�Ӑ؂�Ă�)
				if (VSW & 4)
					_TvStartLine[_VN]++; //�o�U�[���ł����[��ŏ�ӂP���C��������Ȃ��悤�ɁB�ۂ��Ղ郁�C���œ����Ƃ����̂ł��̈ʒu�ŏ����Bv2.11�X�V
			}
			else
				_TvStartLine[_VN] += (vdw0 - 240) / 2; //�ۂ��Ղ郁�C���̂��߂Ɏl�̌ܓ����Ȃ��Ő؂�̂�
		}
		else
			if (VDS+VDW < 511)
			{
				if ((VCR & 0x80) == 0)
					_TvStartLine[_VN] += (256 - VDS - (VSW + 1)) - 239; //�t���b�V���n�C�_�[�X�A���X�^���T�[�K�Q�A�g�C�V���b�v�{�[�C�Y�A���C���{�[�A�C�����h�ATV�X�|�[�c�t�b�g�{�[���A�X�g���C�_�[��
				else
					_TvStartLine[_VN] += (256 - VDS) - 239; //������120%�A�V�g�̎��̃J�W�m�Q�[��
			}
			else
				_TvStartLine[_VN]--; //�p�Y���{�[�C�BVDS=13,VDW=511�œ���B�R�[�X�N���A���̃X�^�b�t���[�����҂�����ɁB
	}
	if (_TvStartLine[_VN] < 0)
		_TvStartLine[_VN] = (-_TvStartLine[_VN] +1) / 2; //�t�@�C�i���u���X�^�[�̃X�^�[�g�f����ʂŕK�v�Bv2.14�ǉ�

	//�`��̃I�t�Z�b�g�l��ݒ肷��B�~�Y�o�N��`���̗��A�C�e����ʗh��A�X�v���b�V�����C�N�ŕK�v�Bv1.30�X�V
	_LineOffset[_VN] -= _TvStartLine[_VN] - prevStartLine;
	//PRINTF("%d , %d , %d, %d", _LineOffset[_VN],_TvStartLine[_VN],prevStartLine,_RasterCounter[_VN]); //test�p

	//Vblank���荞�݂𔭐������郉�C�������߂�B
	VDC_SetVblankLine();
}


//Kitao�ǉ��BVblank���荞�݂𔭐������郉�C�������߂�B
void
VDC_SetVblankLine()
{
	//Vblank���荞�݂𔭐������郉�C�������߂�B
	//�N���X���C�o�[��OP�f�����[�v��261�ȏオ�K�v�B���C���{�[�A�C�����h��263���K�v�B
	//�C���[�W�t�@�C�g�Q��260�ȏオ�K�v�B�\���W���[�u���C�h�R�ʂ̋�������261�ȏオ�K�v�B
	//�}�W�J���`�F�C�X�̃^�C�g����ʂ�254-256�ӂ肩263(VBlankTop)���K�v�B�R�Y�~�b�N�t�@���^�W�[�Q��260���K�v(����ȏ�ł��ȉ��ł��A���������Ɏ��@�ƈႤ�h��ɂȂ�)�B
	//���̓`���U�i�h�D�Q�̃v�����[�O�u���̓`���U�i�h�DII�v�̕������o�鏊��205-208(VBlankTop)�ӂ肪�K�v�B
	//�p���[�S���t�Q�̃N���u�I������261�ȏオ�K�v�B������120%�̎����O�f����257��256���K�v�B
	//�v���C�x�[�g�A�C�h���̃X�^�[�g�f���ŏ�ӂ�����Ȃ����߂�259�ӂ肪�K�v�BF1�T�[�J�X'92��262�ȏオ�K�v�B
	//�t�@�[�W�A�X�̎׍c��̐퓬�V�[����259�ȏオ�K�v�B���_�`���̃X�e�[�^�X�\����261�����肪�K�v�B
	//�t���CCD��251�ȏオ�K�v�B����ʖ�̏����Ȃ��b��252�ȉ����K�v�B���㕨��R�̃f��(���Ճs�A�m�̃V�[���̎�O)��243���K�v(244,242NG)�B
	//BURAI��OP��255�ȏオ�K�v(�傫���Ă��ʖ�)�B�����r�b�g��OP��260�ȏオ�K�v�B�`�F�C�XHQ�̃^�C�g����ʂ�260�ȉ����K�v�B
	//�X�v���K��mk2�̃X�e�[�W�W�f���I�Ղ�263���K�v�B�T�[�J�X���C�h�ŉ��ُ���N�����Ȃ����߂�262�ȉ����K�v�B
	_VblankLine[_VN] = DISPLAY_STARTLINE + _ScreenH[_VN] + 2;
	if (_VblankLine[_VN] > 263) _VblankLine[_VN] = 263; //�����ł�������263�ȉ��ɐ�����B

	if ((MWR & 0x70) >= 0x50) //MWR��0x50�ȏ�̂Ƃ���������B���̏������Ȃ��Ɛ��_�`��(MWR=0x40)�̃X�e�[�^�X��ʂŗ���C�A�h�x���`���[�A�C�����h(MWR=0x10)�̉�ʐ؂�ւ����ɗ���C�}�b�h�X�g�[�J�[�T��(MWR=0x10)�ŗ���Bv2.61
	{
		if (VCR & 0x80) //VCR���傫���Ƃ�
		{
			if (VDW <= 216)
			{
				if (VCR >= 216)
					_VblankLine[_VN] += (VCR-216); //+13�ȏ�ŃX�v���K��MKII�X�e�[�W�W�̃f���V�[���ŏ����I�y���[�^�[�̖ڂ̕����̗��ꂪ�����Bv2.68
			}
			else if (VDW <= 224) //���̏������Ȃ��Ɛ��㕨��R�̃f��(�P�b�̃`�����{�A�b�v�V�[��)�ŗ���Bv2.36
			{
				if (VCR >= 240)
					_VblankLine[_VN] += (VCR-240); //+6�ȏ�Ńh���L����X(MWR=0x50)�̍ŏI�ʂ̊K�i���オ��Ƃ���ł̗��ꁕ�ɋH�Ƀt���[�Y�����肪�����Bv1.61,v2.36�X�V
			}
			else if (VDW <= 232)
				_VblankLine[_VN] -= (232-VDW)/2; //-3�Ő��㕨��R(MWR=0x50,VDW=226)�̃f��(���Ճs�A�m�̃V�[���̎�O)�ŉ�ʗh�ꂪ�����B����������ƃ_�C�i�X�e�B�b�N�q�[���[����(VDW=231)�ŉ�ʉ����Bv2.40
			else
				_VblankLine[_VN] -= 2; //-2�ŃR�Y�~�b�N�t�@���^�W�[�Q�������������̗h�ꂪ���@�Ɠ����ɁBv2.61
		}
		else if (VCR > 4) //VCR���W����菭���傫�����Bv2.49�X�V
		{
			_VblankLine[_VN] += (VCR-3); //3�ȏ�𑫂����ƂŁA�}�W�J���`�F�C�X(VCR=6)�̃^�C�g����ʃf�������[�v����Ƃ��ɉ��v�`�m�C�Y�������Bv1.63,v2.36,v2.41,v2.49,v2.70
										 //9�ȉ��𑫂����ƂŁATRAVEL�G�v����OP�f���łP�t���[���̗��ꂪ�����B5��BGM�Ƃ̃^�C�~���O���x�X�g�B
		}
		else if (VCR < 3) //VCR�����������Bv2.65�ǉ�
		{
			_VblankLine[_VN] -= (3-VCR); //1�ȏ���������ƂŁA�t���b�V���n�C�_�[�X�̎����������̉�ʃu���b�N�A�E�g�������B
		}
		if (_VblankLine[_VN] > 263) _VblankLine[_VN] = 263; //�����ł�������263�ȉ��ɐ�����B
	}

	if ((CR & 0x100) == 0) //�\���o�͑I���̉��ʃr�b�g�������Ă����ꍇ�͏������Ȃ��B���̏������Ȃ��ƃ��C���{�[�A�C�����h��HurryUp���ɗ���B
	{
		if ((MWR & 0x60) == 0) //BG�L�����}�b�v��32x32(0x00),64x32(0x10)�̂Ƃ���������B���̏������Ȃ���BURAI�̃X�^�[�g,F1�T�[�J�X'92�Ō����S�[����(�킸���ȗ���͎��@������)�C���^���G���W�F���̃^�C�g�����,���_�`��(MWR=0x40)�̃X�e�[�^�X��ʂŗ���Bv2.37,v2.41
		{
			if (VCR >= 4) //VCR���W���ȏ�̂Ƃ��B���ꂪ�Ȃ��ƃN���X���C�o�[NG�B
			{
				_VblankLine[_VN]--; //-1�ȏ�ŃX�g�Q�f(MWR=0x10)��VEGA,RYU�X�e�[�W�J�n�����̂P�t���[�����ꂪ�����B-1�ŃX�g�Q�f(MWR=0x10)�̃G���f�B���O(�m�[�R���e�B�j���[)�̏��������(�Ȃ̕����₷��)���œK�B
									//-1�Ńv���C�x�[�g�A�C�h��(MWR=0x10)�̃f���V�[���ŏ�ӂ̗��ꂪ�����B(���������Ƒʖ�)�B
									//-2��-1�ł�����120%(MWR=0x10)�̎����O�f���ŗh�ꂪ�����B����������Ƌt�ɗ���B
									//-2�ȏ�����ƕ��U�i�Q��OP�f���ŉ��ӗ���B-2�ȏ�����ƃ\���W���[�u���C�h�R�ʂŗ���B
									//-2�ȏ�����ƃh���S���X���C���[�p�Y�`���̓d��������f���ŉ��ӂ�����Bv1.65�X�V
									//-3�ȏ�����ƃt���CCD�ŗ���B��������������ƁA����l�`�����i�ŗ���B����������ƃj���W���E�H���A�[�Y�̖ʃN�����h��B
			}
			if (_ScreenH[_VN] >= 240) //�J�[�h�G���W�F���X�ň��������Ȃ����߂ɕK�v(����������ƍŉ��ӂ�����)�Bv1.67
			{
				_VblankLine[_VN]--; //-1�ȏ�ŃX�g�Q�f��VEGA,RYU�X�e�[�W�J�n�����̂P�t���[�����ꂪ�����B�G���f�B���O(�m�[�R���e�B�j���[)�̏��������(�Ȃ̕����₷��)���ς��B
									//-1�Ńv���C�x�[�g�A�C�h���̃f���V�[���ŏ�ӂ̗��ꂪ����(�t�ɑ��������Ă�NG)�B-1�ȏ�Ńp���\���X�^�[�ʃN���A���̗h�ꂪ�����B-1�ł���l�`�����i��OP���ꂪ�����B
									//-2�ȏ�����ƃN���X���C�o�[��NG�B-2�ȏ�����ƃ����r�b�g��NG�B-2�ȏゾ�ƃ\���W���[�u���C�h�R�ʂŗ���B
				if (VDS >= 0x10) //VDS���W�����傫���ꍇ�B���̏������Ȃ���BURAI�̃X�e�[�^�X�\���L�����Z�����Ɉ�u����Bv1.68,v2.37�X�V
					_VblankLine[_VN] -= 4; //-4�ł�����120%�̎����O�f���̂P�t���[�����ꂪ�����Bv2.49,v2.75
			}
			if (VSW == 0) //���������p���X����0�̏ꍇ
			{
				if (_ScreenH[_VN] < 240) //240�ȏ�̂Ƃ������ƁATV�X�|�[�c�t�b�g�{�[���ŉ��ӗ���Bv2.49
					if (VDS <= 27)
						_VblankLine[_VN] -= (27-VDS); //TV�X�|�[�c�A�C�X�z�b�P�[(MWR=0x10)�̃A�i�E���T�[���ꂪ�y���B�傫�������������TV�X�|�[�c�o�X�P�ŉ��ӗ���Bv2.49�X�V
			}
		}
	}
	else //�\���o�͑I���̉��ʃr�b�g�������Ă����ꍇ
		_VblankLine[_VN] = 263; //�X�v���b�V�����C�N�̖ʃN���A���ȂǂłP�t���[���̗��ꂪ�����B���C���{�[�A�C�����h�Bv2.45
	//�������̏�����263�ȉ��ɐ�������ɍs���B������120%OK�B����l�`�����iOK�B

	if (VDW & 0x100) //�p�Y���{�[�C�͓���B�R�[�X�N���A���ɕK�v�Bv2.17
		_VblankLine[_VN] = 2; //2�B4�`9���ƃX�^�b�t���[�����Ɉꎞ��~���Ă��܂��B���@�ł͈ꎞ��~���Ȃ����Ƃ��m�F�ς݁B

	if (_VblankLine[_VN] > 263)
		_VblankLine[_VN] = 263; //�ő�263�B���C���{�[�A�C�����h�Bv1.02�X�V

//Kitao�e�X�g�p
//PRINTF("VbLine=%X, %d, %d, %d  [ %X , %X , %X , %X , %X , %X ] VBline=%d",_DCC,_TvStartLine[_VN],DISPLAY_STARTLINE,_ScreenH[_VN], VPR,VDW,VCR,MWR,DCR,CR, _VblankLine[_VN]);
//PRINTF("Kekka=%x, %x, %x, %x, %x, %x, %x, %x", _Regs[0][0],_Regs[0][1],_Regs[0][2],_Regs[0][3],_Regs[0][4],_Regs[0][5],_Regs[0][6],_Regs[0][7]);
//PRINTF("Kekka=%x, %x, %x, %x, %x, %x, %x, %x", _Regs[0][8],_Regs[0][9],_Regs[0][10],_Regs[0][11],_Regs[0][12],_Regs[0][13],_Regs[0][14],_Regs[0][15]);
//PRINTF("Kekka=%x, %x, %x, %x, %x, %x, %x, %x", _Regs[0][16],_Regs[0][17],_Regs[0][18],_Regs[0][19],_Regs[0][20],_Regs[0][21],_Regs[0][22],_Regs[0][23]);
//PRINTF("Kekka=%x, %x, %x, %x, %x, %x, %x, %x", _Regs[0][24],_Regs[0][25],_Regs[0][26],_Regs[0][27],_Regs[0][28],_Regs[0][29],_Regs[0][30],_Regs[0][31]);
/*
//if (WINMAIN_GetBreakTrap())
{
	char s[100];
	sprintf(s,"Kekka=%d , %d  [ %x , %x , %x ] VBline=%d   ",_TvStartLine[_VN],_ScreenH[_VN],VPR,VDW,VCR,_VblankLine[_VN]);
	int ok;
	ok = MessageBox(WINMAIN_GetHwnd(),
			s,
			"Test",
			MB_YESNO);
	if (ok != IDYES)
		WINMAIN_SetBreakTrap(FALSE);
}
*/
}


//Kitao�ǉ��B�X�[�p�[�O���t�B�b�N�X��VPC�����̃G�~�����[�g�B�v���C�I���e�B����ݒ肷��B
void
VDC_SetVpcPriority()
{
	_VpcPriority[0] = (_VPC[0]     ) & 0xF; //Border1��Border2�����E���̗̈�p
	_VpcPriority[1] = (_VPC[0] >> 4) & 0xF; //Border1���E��Border2��荶���̗̈�p
	_VpcPriority[2] = (_VPC[1]     ) & 0xF; //Border1��荶��Border2���E���̗̈�p
	_VpcPriority[3] = (_VPC[1] >> 4) & 0xF; //Border1��Border2���������̗̈�p
	_VpcBorder1 = ((_VPC[3] & 3) << 8) + _VPC[2] - 128;
	_VpcBorder2 = ((_VPC[5] & 3) << 8) + _VPC[4] - 64;
}


/*-----------------------------------------------------------------------------
	[VDC_Write]
		�u�c�b�ւ̏������ݓ�����L�q���܂��B
-----------------------------------------------------------------------------*/
void
VDC_Write(
	Uint32	regNum,
	Uint8	data)
{
	//Kitao�e�X�g�p
	//if (regNum & 0xFC)
	//{
	//	PRINTF("VDC_Write test! = %X, %X",regNum,data);
	//	return;
	//}

	//Kitao�ǉ��B�X�[�p�[�O���t�B�b�N�X�p
	if (_SuperGrafx)
	{
		_VN = (regNum & 0x10) >> 4; //�A�N�Z�X����VDC(0 or 1)
		if (regNum & 0x08)
		{	//VPC Write;
			regNum &= 7;
			_VPC[regNum] = data;
			switch (regNum)
			{
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
					VDC_SetVpcPriority();
					return;
				case 6:
					CPU_SelectVDC(data & 1);
					return;
			}
			return;
		}
	}
	else
		_VN = 0;

	regNum &= 3; //v2.31�X�V

	//VDC�|�[�g�A�N�Z�X�̃E�F�C�g�B�l�N���X�̗v��(DCC=0,MWR=0x50)��OP�f���ŃA�}�]���̍U���̂͂ݏo��������@�Ɠ��l�ɁB�Q���W�ʐM�������܂�OP(MWR=0x50)�ł��K�v�B
	//  �T�C�����g�f�o�b�K�[�Y(VCR=4,MWR=0x10)�ŉ�ʉ������N�����Ȃ����߂ɕK�v�B�{���o�[�}��'93�X�^�[�g�f��(VCR=4,MWR=0x00)�łP�t���[�������Ȃ����߂ɕK�v�B
	//  ��(VCR=0xEE,MWR=0x10)�̒ʔ̉�ʂŃX�N���[�����ɂP�t���[�������Ȃ����߂ɕK�v�B �T�C�o�[�h�b�W(MWR=0x50)�ŉ�ʂ�����Ȃ����߂ɕK�v�B
	//  �T�[�N�P�Q(VCR=3,MWR=0x40)�ŃX�e�[�^�X��ʂ��J���Ƃ��ɗ���Ȃ����߂ɕK�v�B
	//  �I�[�_�C��(VCR=4,MWR=0x50)�̃V���b�v��������ɂP�t���[������Ȃ����߂ɕK�v�B�p�b�N�����h(VCR=3,MWR=0x10)�ŖʊJ�n��(����2�ʊJ�n)�ɂP�t���[������Ȃ����߂ɕK�v�B
	//  ���b�N�I��(VCR=0xC,MWR=0x50)�ł��ꂽ��ʂŕK�v�B�d�������L(DCC=0,VCR=3,MWR=0x30)�̓q���ɓ����ʂŕK�v�B
	//  �ۂ��Ղ郁�C��(VCR=4,MWR=0x10)�̃I�[�v�j���O�f���ŗ���Ȃ����߂ɕK�v�B
	//  3x3EYES(VCR=0xBA,0xF6,MWR=0x00,0x40)�̃I�[�v�j���O�f���ŉ��Y�����N�����Ȃ����߂ɕK�v�B
	//  ����̐ݒ莞�ɁAVDC�A�N�Z�X���̃E�F�C�g���J�b�g(���@�ł͖�����)�B���[�X�^'91�������@���l�̓����ɁBv2.63�X�V
	if (gCPU_Transfer == 0) //�]�����߈ȊO�ł�VDC�A�N�Z�X�̏ꍇ�Bv2.31�X�V
	{
		//�]�����߈ȊO�ł�VDC�A�N�Z�X�̏ꍇ�A_bVDCAccessWait[_VN]�Ɋւ�炸�ɃA�N�Z�X�E�F�C�g������Bv2.10�ǉ�
		//  �T�C�����g�f�o�b�K�[�Y�C�l�N���X�̗v�ǁC�Q���W�ʐM�������܁C���C�T�[�N�P�Q(MWR=0x40,CR=0x8C)�C���[�X�^&'91(MWR=0x50)�ł̓E�F�C�g���K�v�B
		//  regNum==2�̂Ƃ��ɁA�V�e�B�n���^�[�d�������f��(VCR=3,MWR=0x10,CR=0xCC)�ŃE�F�C�g������Ɖ��ӂ�����Bv2.31�ǉ�
		if (regNum == 3)
		{	//��ʃo�C�g�������ݎ��ɂ܂Ƃ߂ăE�F�C�g�𔭐������邱�ƂŁA�[�������`�����v�ł̃��[�X��ʗ��ꂪ����(�H�ɗh���͎̂��@�����l)�Bv2.40�X�V
			if (_bVDCAccessWait[_VN]) //����ŃE�F�C�g���J�b�g���Ȃ��ƁA�[�r�E�X(VCR=4,MWR=0x00)�ł��ꂽ�Ƃ��ɉE�����ꁕ�H�Ƀt���[�Y�B
			{
				gCPU_ClockCount--; //CPU 1 Clock Wait. �T�C�����g�f�o�b�K�[�Y(MWR=0x10)�C��(MWR=0x10)�ŃE�F�C�g���K�v�B
				gCPU_ClockCount--; //CPU 1 Clock Wait. �{���o�[�}��'93(VCR=4,MWR=0x00)�ł��̂���1�E�F�C�g���K�v�B
			}
			else 
			{
				//MWR=0x00�ȊO�̏ꍇ�͕K��1�E�F�C�g�BMWR=0x00�̂Ƃ��ɓ����ƁA�[�r�E�X(VCR=4,MWR=0x00)�ł��ꂽ�Ƃ��ɉE�����ꁕ�H�Ƀt���[�Y�B
				if (MWR & 0x70)
					gCPU_ClockCount--; //CPU 1 Clock Wait. �ۂ��Ղ郁�C��(MWR=0x10)�ŃE�F�C�g���K�v�B
									   //	MWR=0x10�̂Ƃ���2�E�F�C�g�����ƁA�V�e�B�n���^�[�d�������f��(VCR=3,MWR=0x10,CR=0xCC)�ŉ��ӂ�����B
									   //	MWR=0x50�̂Ƃ���2�E�F�C�g�����ƁA�������l�̐V�`�����ŁA�_���X�V�[���O����BGM��n�߂Ƀm�C�Y������Bv2.58
			}
		}
		else if (regNum == 0)
			gCPU_ClockCount--; //CPU 1 Clock Wait. F1�T�[�J�X�̃X�^�[�e�B���O�O���b�h�\��(MWR=0x50)�ŃE�F�C�g���K�v�B
	}
	else //�]�����߂����VDC�A�N�Z�X�̏ꍇ
	{
		//VDC���p�󋵂ɂ��A�N�Z�X�E�F�C�g������B3x3EYES�C�I�[�_�C���C�{���o�[�}��'93�C�p�b�N�����h�C���b�N�I���ŃE�F�C�g���K�v�B
		if (_bVDCAccessWait[_VN]) //����ŃE�F�C�g���J�b�g���Ȃ��ƁA�����_�[����(VCR=3,MWR=0x30)�C���[���h�X�^�W�A������&'91(VCR=4,MWR=0x50)�Ńt�@�[���ĊJ���ɗ���C�A���K�m�X�Ńt���[�Y�B
			gCPU_ClockCount--; //CPU 1 Clock Wait
		//  ���[���h�X�^�W�A��'91�œ��ۂŉ�ʐ؂�ւ����ɂP�t���[�������͎̂��@�����l�B
	}

	//v1.15�X�V�B�������Bcase���́A�悭�g������̂��ɒu�����ق������������ł������B
	switch (regNum)
	{
		case 3: // ��ʃo�C�g�̏�������
			_Regs[_VN][_AR[_VN]] = (_Regs[_VN][_AR[_VN]] & 0x00FF) | (data << 8); //Kitao�X�V

			// �W���I�ȏ������݈ȊO�ɓ��ʂȏ������K�v�ȏꍇ�͈ȉ��ɋL�q���� 
			switch (_AR[_VN])
			{
				case VDC_VWR:  // vram data write
					write_vram(MAWR, VWR);
					MAWR += _VdcAddrInc[_VN];
					if (_SpDmaCount[_VN] == 0) return;//v1.61�B�������̂���0�Ȃ炷���A��B
					
					//Kitao�ǉ��B�]������VRAM�ւ̏������݂��������ꍇ�ACPU���X�g�[������Bv0.87
					//	��񌹁FKi����̃z�[���y�[�W�uSATB�]������VRAM���C�g�������CPU���]�������܂ŃX�g�[������v
					if ((_SpDmaCount[_VN] == 4)|| //SATB�]�����ɁAVRAM���C�g���s��ꂽ�ꍇ
						((_SpDmaCount[_VN] == 3)&&(_CpuPastCount < 88))) //88�B�񃉃C��5����1�܂ł̃^�C�~���O���Ƃ����B90���ƃ_���W�����G�N�X�v���[����OP�X�^�b�t���[���łP���C������邱�Ƃ���B�_�u���h���S��II�͑����قǍœK�B4����1���Ɗ�X���E��OP�f��(�D������)�ŗ���B�N���X���C�o�[��80(5.5����1)���炢�ȏ�̒l���K�v�B�傫���ƃ`�F�C�XHQ�X�^�[�g���AZIPANG�X�^�[�g���ɂ�◐��Bv2.63�X�V
					{
						if (_VN == 0) //�X�p�O���̏ꍇ�A��d�ɃE�F�C�g���Ă��܂�Ȃ��悤��VDC0�̂Ƃ��̂݃E�F�C�g�Ƃ���B
						{
							//PRINTF("%X, %d, %d , %d", VCR,_ScanLine,_SpDmaCount[0],_CpuPastCount); //test�p
							if (VCR < 4) //VCR���������Ƃ��́A�S�]�����X�g�[��������悤�ɂ����B�N���X���C�o�[,�����_�[�����ŕK�v�Bv2.08,v2.31�X�V
								_SpDmaStole[0] = VDC_CYCLESPERLINE-_CpuPastCount + 1408;//1408; //���C���I�[�܂łԂ�X�g�[���{1408=5.5�N���b�Nx256byte(��R�`�S���C���B����)�Ԃ�CPU���X�g�[���B�N���X���C�o�[�̃f���Q���[�v�ڈȍ~�ŕK�v�B
							else //�ʏ�
								_SpDmaStole[0] = (VDC_CYCLESPERLINE*(_SpDmaCount[0]-2) - _CpuPastCount) /128; //CPU���X�g�[���B1/128�ɂ����B1/80���ƃT�C�h�A�[��SP�̃A�����W���[�h�J�n���ɃX�e�[�^�X�h��B��������邱�ƂŁAZIPANG�ʃX�^�[�g�������@�ɋ߂����Ŏ�l�����肪������Bv2.61�X�V
																											  //						    �G�^�[�i���V�e�B�ŃA�C�e�����莞�Ȃǂŉ�ʗh�����1/64NG�B"�_���W�����G�N�X�v���[���[��OP�X�g�[���[�X�N���[��"��1/50NG�B"���[�h�X����L�Q"�̃G���f�B���O��1/8NG�B�X�g�Q�f�̃x�K�X�e�[�W�J�n���ɑ傫���Ɨ���B
																											  //						    ��X���E��OP�f��(�D������)�ŋH�ɗ���邱�Ƃ�����(1/4���ƋɋH��)�B���ꂷ�����"�`�F�C�XH.Q.�̃^�C�g���f�����"�ɂ�◐��(1/3�ŗ���)�B"�Ƃ�ׂ�[���I"�̃C�x���g�V�[���ŉ��Y�����邱�Ƃ�����B
							gCPU_ClockCount -= _SpDmaStole[0]; //CPU Clock Wait
						}
					}
					//if (_SpDmaCount[_VN] >= 2)
					//	PRINTF("%d , %d", _SpDmaCount[_VN],_CpuPastCount); //test�p
					return;

				case VDC_MARR:  //Kitao�ǉ��BVRAM���[�h�A�h���X���Z�b�g�����Ɠ�����VRAM���[�h�A�N�Z�X�������Ȃ���B
					if (MARR < 0x8000)
						_ReadData[_VN] = _pwVideoRam[_VN][MARR]; //���[�h�A�N�Z�X
					else
						_ReadData[_VN] = 0;
					return;

				case VDC_CR:  // control
					_VdcAddrInc[_VN] = _IncSizeTable[(data >> 3) & 3];
					return;

				case VDC_RCR:  // raster detection
					RCR &= 0x3FF;
					//Kitao�ǉ��B�����ł����Ƀ��X�^��r���s�Ȃ��B�P���C�����ƂɃ��X�^�X�N���[������\�t�g�ŕK�v�ȂƂ�������B
					if (_bRasterRequested[_VN] == FALSE) //�܂����̃��C���Ń��X�^���荞�ݗv�����s���Ă��Ȃ��ꍇ
						if ((((_RasterCounter[_VN]-64) & 0xFF) == RCR-64)&&(_RasterCounter[_VN] >= 64))
						{
							if (CR & VDC_CTRL_RC)
							{
								_VdcStatus[_VN] |= VDC_STAT_RR;
								INTCTRL_Request(INTCTRL_IRQ1);
							}
							_bRasterRequested[_VN] = TRUE;
						}
					return;

				case VDC_BXR:  // bg x scroll
					BXR &= 0x3FF;
					return;

				case VDC_BYR:  // bg y scroll
					BYR &= 0x1FF;
					_LineCounter[_VN] = BYR; //Kitao�X�V�B�V���v���ɂ����B
					if (!_bRasterLate) //Kitao�ǉ��B���C���`��O�Ƀ��X�^���荞�ݗv�����������ꍇ�A_LineCounter�����������C���N�������g��������B����ʃo�C�g�̂Ƃ����s���B�t�H�S�b�g�����[���h�ŕK�v�Bv1.03
						if (_RasterCounter[_VN] != 64) //���荞�݊J�n���C��(_RasterCounter==64)��ł͕K��RasterLate��ԂɂȂ�B�t�H�S�b�g�����[���h�̂��X�V�[��,BURAI�ȂǁB
							++_LineCounter[_VN]; //�_���W�����G�N�X�v���[���[�A�p�b�N�����h�A�u���b�f�B�E���t�A�G�^�[�i���V�e�B���ŕK�v�B
					_LineCounter[_VN] &= _LineCountMask[_VN];
					return;

				case VDC_HSR:  //Kitao�ǉ��BHDS(HSR��bit8-14)���ύX������TV��̐����\���J�n�ʒu���ς��B
					setTvStartPos();
					return;

				case VDC_VPR:  //Kitao�ǉ��BVSync���W�X�^(��ʃo�C�g=VDS)�BVDS���ύX������TV��̍ŏ�i�`�惉�C�����ς��B
					VDC_SetTvStartLine();
					return;

				case VDC_VDW:  // vertical display width
					_ScreenH[_VN] = (VDW & 511) + 1;
					//Kitao�ǉ��BVDW���ύX������TV��̍ŏ�i�`�惉�C�����ς��B
					VDC_SetTvStartLine();
					return;

				case VDC_LENR:
					do_vram_vram_dma();
					return;

				case VDC_SATB: //SATB�̃A�h���X��ݒ聕�]���̗\�������B
					_bUpdateSATB[_VN] = TRUE;
					return;
			}
			return;

		case 2: // ���ʃo�C�g�̏�������
			_Regs[_VN][_AR[_VN]] = (_Regs[_VN][_AR[_VN]] & 0xFF00) | data; //Kitao�X�V�Bv2.50�ǋL�F�����ŏ�ʃo�C�g���N���A�����ꍇ�A�d�������L�̂P�ʒ��Ղ����ʂ�������B

			// �W���I�ȏ������݈ȊO�ɓ��ʂȏ������K�v�ȏꍇ�͈ȉ��ɋL�q���� 
			switch (_AR[_VN])
			{
				case VDC_VWR:  //Kitao�ǉ��Bv1.61
					return; //�������Ȃ��ł����ɖ߂�B�p�ɂɎg���邱��(�u���b�N�]���ȂǂŘA�����Ďg����)��case�̐擪�Ɏ����Ă��邱�Ƃō������ɂȂ�B

				case VDC_BYR:  // BG Y scroll
					_LineCounter[_VN] = BYR; //Kitao�X�V�B�V���v���ɂ����B
					if (!_bRasterLate) //Kitao�ǉ��B���C���`��O�Ƀ��X�^���荞�ݗv�����������ꍇ�A_LineCounter�����������C���N�������g��������B
						if (_RasterCounter[_VN] != 64) //���荞�݊J�n���C��(_RasterCounter==64)��ł͕K��RasterLate��ԂɂȂ�B�t�H�S�b�g�����[���h�̂��X�V�[��,BURAI�ȂǁB
							++_LineCounter[_VN]; //�_���W�����G�N�X�v���[���[�A�p�b�N�����h�A�u���b�f�B�E���t�A�G�^�[�i���V�e�B���ŕK�v�B
					_LineCounter[_VN] &= _LineCountMask[_VN];
					return;

				case VDC_MWR:  // Memory width
					//Kitao�X�V�BMWR���X�V�����Ƃ��́AVblank���Ԓ��Ƀ������}�b�v�̍X�V���s���悤�ɂ����B
					//			 �����_�L���[�u�̃v�����[�O�ASUPER���S�̗D���Ҕ��\���ɉ�ʂ��������������B
					_bMWRchange[_VN] = TRUE; //Kitao�ǉ�
					VDC_SetTvStartLine(); //MWR���ύX������TV��̍ŏ�i�`�惉�C����VBlank���C�����ς��B
					return;

				case VDC_HDR:  // horizontal display
					_ScreenW[_VN] = ((data & 0x7F) + 1) * 8;
					setTvStartPos(); //Kitao�ǉ��BHDR���ύX������TV��̐����\���J�n�ʒu���ς��B
					if ((_ScreenW[_VN] <= 85)&&(VCR <= 4)) //85(256/3�B���@���m�F)�BTRAVEL�G�v����OP�C�X�^�[�u���[�J�[�́u�A�����̒��v�ňꔑ����Ƃ�(_TvMax=112)�A(_VPR���傫�߂̂Ƃ�)�ɂ͂��̏��������Ȃ��Bv2.49�X�V
						_ScreenW[_VN] = _TvWidth; //�t�@�C�i���u���X�^�[�̃X�^�[�g�f���ŕK�v�B��_TvMax�͏����Ȃ܂܁Bv2.14
					return;

				case VDC_VPR:  //Kitao�ǉ��BVSync���W�X�^(���ʃo�C�g=VSW)�BVSW���ύX������TV��̍ŏ�i�`�惉�C����VBlank���C�����ς��B
					VDC_SetTvStartLine();
					return;

				case VDC_VDW:  //Kitao�ǉ��B���ʃo�C�g�����ύX����ꍇ������B�h���S���X���C���[�p�Y�`���Q�B
					_ScreenH[_VN] = (VDW & 511) + 1;
					//VDW���ύX������TV��̍ŏ�i�`�惉�C����VBlank���C�����ς��B
					VDC_SetTvStartLine();
					return;

				case VDC_VCR:  //Kitao�ǉ��BVCR(�����\���I���ʒu)���ύX������TV��̍ŏ�i�`�惉�C����VBlank���C�����ς��B
					VDC_SetTvStartLine();
					return;

				case VDC_SATB: //SATB�̃A�h���X��ݒ聕�]���̗\�������Bv1.61���ʃo�C�g�����������ɂ��ǉ��B
					_bUpdateSATB[_VN] = TRUE;
					return;
			}
			return;

//		case 1: // AR �ɏ�ʃr�b�g�͂Ȃ��B 
//			return;

		case 0: // VDC �̃��W�X�^�ԍ����w�肷��B
			_AR[_VN] = data & 0x1F;	// AR = Address Register 
			return;
	}
}


/*-----------------------------------------------------------------------------
	[VDC_Read]
		�u�c�b����̓ǂݏo��������L�q���܂��B

	[note]
		CR �� D11-D12 �Ō��肳���u�q�`�l�A�h���X�C���N�������g�l��
		MAWR, MARR �̗����ɗL���ł���B (01.10.2004 �m�F�ς�)
-----------------------------------------------------------------------------*/
Uint8
VDC_Read(
	Uint32	regNum)
{
	Uint8	ret;

	//Kitao�ǉ��B�X�[�p�[�O���t�B�b�N�X�p
	if (_SuperGrafx)
	{
		_VN = (regNum & 0x10) >> 4; //�A�N�Z�X����VDC(0 or 1)
		if (regNum & 0x08)
			return (Uint8)_VPC[regNum & 7]; //VPC Read;
	}
	else
		_VN = 0;

	//Kitao�e�X�g�p�B�X�^�[�g�����O�I�f�b�Z�C�Q�̎~�܂�Ƃ���(���A�����ă\���f�B�A�嗤)�Ń��W�X�^No.�ɑ傫�Ȓl�A���B
	//if (regNum & 0xFC)
	//	PRINTF("regNum = %X, %X, %X, %X", regNum,_ReadData[_VN],_VdcStatus[_VN],_AR[_VN]); //test�p

	//regNum��bit6(0x40)��Ys4(����̑�J�̏��)�ŗ����Ă��邱�Ƃ�����A����͗L���BregNum�̍ŏ��(0x80)�̓h���b�v���b�N�ق�z���ŗ����Ă��邱�Ƃ�����A����͗L���B
	//regNum��bit5(0x20)�͐��m���`���ŗ����Ă��邱�Ƃ�����A����͗L���Bbit4�̓X�p�O���Ŏg���Ă���B
	if ((regNum & 0xE0) == 0xE0) //bit5-7�܂őS�Ă������Ă��Ă�ꍇ�Bbit4-7�܂łɂ���ƂP�t���[������Bv1.64�X�V
	{
		//PRINTF("regNum = %X, %X, %X, %X", regNum,_ReadData[_VN],_VdcStatus[_VN],_AR[_VN]); //test�p
		if (_AR[_VN] == VDC_VRR)
			return 0; //�v�����Z�X���[�J�[�Q��0��Ԃ��K�v������Bv2.24
		else
			return 0xFF; //�t�H�[���[�V�����T�b�J�['90�̃G���f�B���O��0xFF��Ԃ����Ƃ��K�v�B0��Ԃ��ƈ�u�����X���[�ɂȂ�B
		//���t�H�[���[�V�����T�b�J�[��regNum���傫�Ȃ܂ܓǂ݂ɗ��邱�Ǝ��̂��A���@�ƈႤ�����ɂȂ��Ă��܂��Ă���\��������B
		//  ����͑Ώ��Ö@�ŁBv2.24�L
	}

	//v1.15�X�V�B�������Bcase���́A�悭�g������̂��ɒu�����ق������������ł������B
	switch (regNum & 3)
	{
		case 3: // ��ʃo�C�g�̓ǂݏo���BKitao�X�V�B_AR��VDC_VRR�ł͂Ȃ��Ƃ����AMARR�̓��e��Ԃ��悤�ɂ����B21�G�����ŕK�v
			ret = (Uint8)(_ReadData[_VN] >> 8);
			if (_AR[_VN] == VDC_VRR)
			{
				MARR += _VdcAddrInc[_VN];
				//Kitao�ǉ��B�A�h���X���C���N�������g���ꂽ�Ɠ�����VRAM���[�h�A�N�Z�X���N����B
				if (MARR < 0x8000)
					_ReadData[_VN] = _pwVideoRam[_VN][MARR]; //���[�h�A�N�Z�X
				else
					_ReadData[_VN] = 0;
			}
			return ret;

		case 2: // ���ʃo�C�g�̓ǂݏo���BKitao�X�V�B_AR��VDC_VRR�ł͂Ȃ��Ƃ����AMARR�̓��e��Ԃ��悤�ɂ����B21�G�����ŕK�v
			return (Uint8)_ReadData[_VN];

		case 1: //v1.62�X�V
			//PRINTF("VDC_Read reg=1 !!"); //test�B�~�Y�o�N��`���P�ʃX�^�[�g����,�X�^�[�u���[�J�[�ȂǂŎg���Ă���B
			return 0; //0xFF��Ԃ��ƃ~�Y�o�N��`���̋��̕ӂ蔻�肪�����Ȃ��Ă��܂��B�����炭�X�e�[�^�X�̏�ʃo�C�g�����Ȃ̂�0�Ƃ��Ă����B
			
		case 0:
			ret = _VdcStatus[_VN];
			//Kitao�X�V�Bv0.96�B�X�g�Q�f�łP�t���[���̗��ꂪ�N����Ȃ����߂ɁA���X�^���荞�݂Ƒ��̊��荞�݂��d�Ȃ��Ă��܂����Ƃ�h���B
			//if (((_VdcStatus[_VN] & VDC_STAT_RR) == 0)||(_VdcStatus[_VN] == VDC_STAT_RR)) //CPU�̊��荞�݃^�C�~���O�̂ق����d�v�B���ݕs�v�ŃV���v���ɁBv1.61�J�b�g
			INTCTRL_Cancel(INTCTRL_IRQ1); //Kitao�X�V�Bv0.95�B�ʏ�̓V���v���ɃL�����Z�������B
			_VdcStatus[_VN] = 0; //Kitao�X�V�B�����炭�V���v���ɁA���[�h�����ƃN���A�����B
			return ret;
	}

	return 0xFF; //v1.62�X�V�BVCE��Read���l�ɁA�|�[�g�ɑ΂��Ă̖����ȃ��W�X�^�w�莞�ɂ�0xFF��Ԃ��Ă����B
}


/*-----------------------------------------------------------------------------
** [CreatePatternTables]
**	�L�����N�^�p�^�[�� �� �r�b�g�}�b�v�f�[�^�ւ̕ϊ��k�t�s���쐬���܂��B
**	CH0 �` CH3 �p�̂S���쐬���܂��B
**
**	CH0 �̂P�o�C�g(D0 - D7) ���C�W�o�C�g�ɓW�J����B���̓W�J�̎d���́F
**
**	byte	00 01 02 03 04 05 06 07
**	data	D7 D6 D5 D4 D3 D2 D1 D0   (�f�[�^�r�b�g�͑S�� D0 �փV�t�g��������)
**
**	CH1 �̂P�o�C�g(D0 - D7) ���C�W�o�C�g�ɓW�J����B���̓W�J�̎d���́F
**
**	byte	00 01 02 03 04 05 06 07
**	data	D7 D6 D5 D4 D3 D2 D1 D0   (�f�[�^�r�b�g�͑S�� D1 �փV�t�g��������)
**
**	CH2 �̂P�o�C�g(D0 - D7) ���C�W�o�C�g�ɓW�J����B���̓W�J�̎d���́F
**
**	byte	00 01 02 03 04 05 06 07
**	data	D7 D6 D5 D4 D3 D2 D1 D0   (�f�[�^�r�b�g�͑S�� D2 �փV�t�g��������)
**
**	CH3 �̂P�o�C�g(D0 - D7) ���C�W�o�C�g�ɓW�J����B���̓W�J�̎d���́F
**
**	byte	00 01 02 03 04 05 06 07
**	data	D7 D6 D5 D4 D3 D2 D1 D0   (�f�[�^�r�b�g�͑S�� D3 �փV�t�g��������)
**
**	[2004.3]
**	CH1-CH3 �� CH0 ������ 1�`3 �r�b�g�V�t�g���������Ȃ̂ŁA
**	CH0 �݂̂��쐬���ACH1�`CH3 �� CH0 ���V�t�g���đΉ�����悤�ɕύX�����B
**---------------------------------------------------------------------------*/
static void
createPatternLUT()
{
	Uint32	i;
	Uint32	D0, D1, D2, D3, D4, D5, D6, D7;

	for (i = 0; i < 256; i++)
	{
		// �S�� D0 �փV�t�g����B
		D7 = (i & 0x80) >> 7;
		D6 = (i & 0x40) >> 6;
		D5 = (i & 0x20) >> 5;
		D4 = (i & 0x10) >> 4;
		D3 = (i & 0x08) >> 3;
		D2 = (i & 0x04) >> 2;
		D1 = (i & 0x02) >> 1;
		D0 = (i & 0x01) >> 0;

		_PatternLUT[i][0] = D7 | (D6 << 8) | (D5 << 16) | (D4 << 24);
		_PatternLUT[i][1] = D3 | (D2 << 8) | (D1 << 16) | (D0 << 24);
	}
}


//Kitao�ǉ�
void
VDC_Reset()
{
	int		i;

	memset(_VideoRam, 0, sizeof(_VideoRam));
	memset(_SpRam, 0, sizeof(_SpRam)); //Kitao�ǉ�
	memset(_Regs, 0, sizeof(_Regs));
	memset(_AR, 0, sizeof(_AR));
	
	memset(_BgPutBuf, 0, sizeof(_BgPutBuf)); //Kitao�ǉ�
	memset(_SpPutBuf, 0, sizeof(_SpPutBuf)); //Kitao�ǉ�

	//Kitao�ǉ��B�X�p�O���p�ɂQ�Ԃ񃊃Z�b�g����
	for (_VN=0; _VN<=1; _VN++)
	{
		_pwVideoRam[_VN] = (Uint16*)&_VideoRam[_VN][0];
		_ReadData[_VN] = 0; //Kitao�ǉ�
		
		//Kitao�ǉ��BVDC_Deinit()����K�v�ȂԂ��������֎����Ă����B
		_VdcStatus[_VN] = 0;
		_bUpdateSATB[_VN] = FALSE;
		_MaxSpPerLine[_VN] = 16; //Kitao�ǉ��Bv2.63
		_bSpOver[_VN] = FALSE;
		_bOverlap[_VN] = FALSE; //Kitao�ǉ�
		_SpDmaCount[_VN] = 0;
		_SpDmaStole[_VN] = 0; //Kitao�ǉ�
		_VramDmaCount[_VN] = 0; //Kitao�ǉ�
		_bVramDmaExecute[_VN] = FALSE; //Kitao�ǉ��Bv1.02
		_bBurstMode[_VN] = FALSE;
		_bVDCAccessWait[_VN] = TRUE; //v2.08�ǉ�
		_bMWRchange[_VN] = FALSE; //Kitao�ǉ�
		_bVDCleared[_VN] = FALSE; //v1.63�ǉ�
		
		_RasterCounter[_VN] = 0;
		_bRasterRequested[_VN] = FALSE; //Kitao�ǉ�
		_LineCounter[_VN] = 0;
		_LineCountMask[_VN] = 0xFF;
		_LineOffset[_VN] = 0; //Kitao�ǉ��Bv1.30
		_PrevVSW[_VN] = 0; //2.10�ǉ�
		
		_BGH[_VN] = 0;
		_BGW[_VN] = 0;
		//
		
		_ScreenW[_VN] = 256;
		_ScreenH[_VN] = 240;
		_TvStartLine[_VN] = 27; //Kitao�ǉ�
		_TvStartLineAdjust[_VN] = 0; //Kitao�ǉ�
		_VblankLine[_VN] = 262;
		_VblankLineTop[_VN] = _VblankLine[_VN]; //Kitao�ǉ�
		_prevCR[_VN] = 0; //Kitao�ǉ��Bv1.21
		
		VDW = 239;
		VCR = 4;
		VPR = 0x0F02;
		
		_VdcAddrInc[_VN] = 1; // ���̏������͕K�v  FIXED 2004.09.11 
		
		invalidate_tile_cache();
	}

	_ScanLine = 0;
 	_DisplayCounter = 0;
	_bRasterLate = TRUE; //Kitao�ǉ�

	//�N���w�i�F�𔒂�
	for (i = 0x000; i < 0x200; i++)
		_Palette333[i] = 0x1FF;
	for (i = 0x000; i < 0x100; i++)
		_PaletteBG[i] = _PaletteSP[i] = 0x00070707; //Kitao�X�V

	_DCC = 0;
	_ColorTableAddr = 0;
	_ColorLatch = 0;
	_TvStartPos = 0; //Kitao�ǉ�
	_TvWidth = 256; //Kitao�ǉ�
	_TvMax = 256; //Kitao�ǉ�

	//Kitao�ǉ��B�X�p�O���p
	memset(_VPC, 0, sizeof(_VPC));
	memset(_VpcPriority, 0, sizeof(_VpcPriority));
	_VpcBorder1 = 0;
	_VpcBorder2 = 0;
}

/*-----------------------------------------------------------------------------
	[VDC_Init]
		VDC�����������܂��B
-----------------------------------------------------------------------------*/
void
VDC_Init()
{
	createPatternLUT();

	VDC_SetAutoRasterTiming(2);//Kitao�ǉ�
	_AutoOverClock = -1;//Kitao�ǉ�
	VDC_SetAutoPerformSpriteLimit(APP_GetDefaultSpriteLimit()); //Kitao�ǉ�
	VDC_SetLayer(); //v2.06�ǉ�
	_WaitPatch = 0; //Kitao�ǉ�
	_bForceRaster = FALSE; //Kitao�ǉ�
	_bForceVBlank = FALSE; //Kitao�ǉ�
	_bShinMegamiTensei = FALSE; //�^�E���_�]���Bv2.20�ǉ�
	_bWorldStadium91 = FALSE; //���[���h�X�^�W�A��'91�Bv2.64�ǉ�
	_bEikanKimi = FALSE; //�h���͌N�ɁBv2.70�ǉ�
	_bPowerLeague = FALSE; //�p���[���[�O�Bv2.70�ǉ�
	_bTheProYakyuu = FALSE; //�U�E�v���싅�B�U�E�v���싅SUPER�Bv2.70�ǉ�

	VDC_Reset();//Kitao�X�V
}


/*-----------------------------------------------------------------------------
	[drawBgLine]
		�a�f���P���C���`�悵�܂��B

	[DEV NOTES]

	�L�����N�^�T�C�Y�F 8x8
	�L�����N�^�W�F�l���[�^�ɒ�`�ł���L�����N�^�̍ő吔�F�S�O�X�U
	�a�`�s�͂P�U�r�b�g�^�L�����N�^�Œ�`����B
	D0	- D11 �F �L�����N�^�R�[�h
	D12 - D15 �F �b�f�J���[(�p���b�g�̏�ʂS�r�b�g)
	[��] �L�����N�^�R�[�h���P�Q�r�b�g�Ȃ̂ŁC�ő�L�����N�^�����S�O�X�U��

	VRAM ���� BAT �̈�̑傫���́C�������� MWR �Ō��肳�����̂Ǝv����B
	�Ⴆ�� MWR �� WxH=32x32 �Ɛݒ肳�ꂽ�ꍇ�́CBAT ��32x32x2 = 2048 �o�C�g
	�ƂȂ�B�܂� VRAM $0000 - $07FF �� BAT �̈�ƂȂ�B�p�^�[������`
	�����̈�(�b�f�A�h���X)�́CBAT �̈�̒���($800)����n�܂�B

	[�X�L�������C���x�[�X�ɂ���]
	�X�L�������C�����O�`�Q�R�X�ňړ�������̂Ƃ���(���m�F)�B
	�^�C���� 8x8 �Ȃ̂ŁC�X�L�������C���ɂ��^�C���̂x�����̃I�t�Z�b�g�́C

		tileOffsetY = scanline / 8;

	�ŋ��܂�B����āC�X�L�������C���Ŏw�肳�ꂽ���C���̕`����s�Ȃ��ɂ́C

		BATWord = (VRAM[tileOffsetY*BGW*2] | (VRAM[tileOffsetY*BGW*2+1] << 8))

	����̂Q�o�C�g��ǂݏo���B���̉��ʂP�Q�r�b�g���R�Q�ŁC�b�f�A�h���X��
	����B

		CGAddr = (BATWord & 0xfff) * 32

	�s�N�Z���̏�ʂS�r�b�g(�J���[�u���b�N)�́CBATWord �̏�ʂS�r�b�g�Ŏw�肳���B

		ColorBlock = (BATWord & 0xf000) >> 8

	���ʂS�r�b�g�ɂ́C�p�^�[��������̂ŁCColorBlock�͏�ʂS�r�b�g�ɕێ����Ă����B
	�b�f�f�[�^�́C�R�Q�o�C�g���琬��C�^�C���̂P���C�����S�o�C�g�Œ�`����B
	�܂�C�P�s�N�Z�����S�r�b�g�ō\������B���̏ڍׂ́C

		CG[0] �̂W�r�b�g: line 0 �� D0	|  CG[10] �̂W�r�b�g: line 0 �� D2
		CG[1] �̂W�r�b�g: line 0 �� D1	|  CG[11] �̂W�r�b�g: line 0 �� D3
		CG[2] �̂W�r�b�g: line 1 �� D0	|  CG[12] �̂W�r�b�g: line 1 �� D2
		CG[3] �̂W�r�b�g: line 1 �� D1	|  CG[13] �̂W�r�b�g: line 1 �� D3
		CG[4] �̂W�r�b�g: line 2 �� D0	|  CG[14] �̂W�r�b�g: line 2 �� D2
		CG[5] �̂W�r�b�g: line 2 �� D1	|  CG[15] �̂W�r�b�g: line 2 �� D3
		CG[6] �̂W�r�b�g: line 3 �� D0	|  CG[16] �̂W�r�b�g: line 3 �� D2
		CG[7] �̂W�r�b�g: line 3 �� D1	|  CG[17] �̂W�r�b�g: line 3 �� D3
		CG[8] �̂W�r�b�g: line 4 �� D0	|  CG[18] �̂W�r�b�g: line 4 �� D2
		CG[9] �̂W�r�b�g: line 4 �� D1	|  CG[19] �̂W�r�b�g: line 4 �� D3
		CG[A] �̂W�r�b�g: line 5 �� D0	|  CG[1A] �̂W�r�b�g: line 5 �� D2
		CG[B] �̂W�r�b�g: line 5 �� D1	|  CG[1B] �̂W�r�b�g: line 5 �� D3
		CG[C] �̂W�r�b�g: line 6 �� D0	|  CG[1C] �̂W�r�b�g: line 6 �� D2
		CG[D] �̂W�r�b�g: line 6 �� D1	|  CG[1D] �̂W�r�b�g: line 6 �� D3
		CG[E] �̂W�r�b�g: line 7 �� D0	|  CG[1E] �̂W�r�b�g: line 7 �� D2
		CG[F] �̂W�r�b�g: line 7 �� D1	|  CG[1F] �̂W�r�b�g: line 7 �� D3

	�ƂȂ��Ă���Bline �͂W�s�N�Z���ō\������C�W�r�b�g�� D0 ���E�[�̃h�b�g
	�ɂȂ�B

	02/05/2004: [����������]

	1. 8bpp ���ł��Ȃ����H

	�p�^�[���ɂS�r�b�g�A�J���[�u���b�N�łS�r�b�g������W�r�b�g�B
	�b�f�J���[�̓^�C�����Ƃɐݒ�\�B
	�^�C���͂a�`�s�ɂS�O�X�U�ݒ�\�B
	�^�C�����S�O�X�U�ݒ肵���ꍇ�A�g�p���� VRAM �̗̈�́A

		4096 * 2 = 8192 [bytes]

	CG �͂P�^�C���̃p�^�[���łR�Q�o�C�g����邽�߁A

		(65536 - 8192) / 32 = 1792 [tiles] 

	1792 �̃��j�[�N�ȃp�^�[�����`�ł���B
	���̃p�^�[���͂P�s�N�Z��������S�r�b�g�Ȃ̂Ŏg�p����p���b�g�̈�͂P�U�D
	���ł��Ȃ�����...

	2. ���O�ɂł��邱�Ƃ͂���Ă��܂�

	BG �̕`��ɂ͎��̂R�̏��������Ȃ��B

		a. �p�^�[���Ƃb�f�J���[����p���b�g�w�W���v�Z����(�G���R�[�h����)
		b. �p���b�g���� GRB333 9 �r�b�g�J���[���擾����
		c. GRB333 �� RGB555 / RGB565 �ɕϊ�����

		a. �G���R�[�h�����̍�����
			�^�C���̃p�^�[���f�[�^�̓t���[�����ɕω����邱�Ƃ�
			���܂�Ȃ�(�������݂����ǂݏo���̕�������)���߁A
			VRAM �ɂb�f�f�[�^���������܂ꂽ�Ƃ��ɃG���R�[�h�������s�Ȃ��A
			�ێ����Ă����ƈȍ~�̓ǂݏo���������ɂȂ�B
			�b�f�J���[�͂a�`�s�œƗ��ɐݒ肳���̂ŁA
			�G���R�[�h�����ł͂b�f�f�[�^(4bits/pixel)�݂̂������̑ΏۂƂ���B

			���ۂɂ͂b�f�͂R�Q�o�C�g���琬�邽�߁A�f�[�^���������܂�邽�т�
			�G���R�[�h�������s�Ȃ��ƍő�R�Q����G���R�[�h�������s�Ȃ����ƂɂȂ�(����)�B
			�����ŁA���̂����قȂ�l�̏������݂��P�o�C�g�ł������
			�u�X�V�t���O�v�𗧂Ă�悤�ɂ��A�`�撼�O�ɍX�V�t���O�������Ă���
			���̂����G���R�[�h�������s�Ȃ��B

			MWR �Őݒ�ł��鉼�z�X�N���[���̍ŏ��T�C�Y�� 32 x 32�B
			���̂Ƃ��b�f�f�[�^�̂��߂̂u�q�`�l�̈���ł��傫�����āA

				65536 - 32 x 32 x 2 = 1984 [patterns]

			1984 �̃p�^�[�����`�ł���B�b�f�f�[�^�� 8x8 �s�N�Z����
			�G���R�[�h�Ȃ̂ŁA���̂悤�ȃe�[�u����p�ӂ���B

				Uint8 decodedpixel[1984][8*8];

			�G���R�[�h��̃s�N�Z���f�[�^�͂S�r�b�g�Ȃ̂ŁA
			��ʂS�r�b�g�͏�Ƀ[���ɂȂ��Ă���B���̃r�b�g���g��Ȃ��̂�
			���������Ȃ��̂ŁA8x8 �s�N�Z���z��̍ŏ��̗v�f
			(decodedpixel[xxxx][0]) �̍ŏ�ʃr�b�g�ɂ́u�X�V�t���O�v
			�����蓖�Ă邱�Ƃɂ���B�Ȃ��A�����ɗ��Ă�u�X�V�t���O�v�́A
			�`��̒��O�ɃG���R�[�h�������Ȃ���ăN���A�����̂�
			�b�f�J���[�Ɗ����邱�Ƃ͂Ȃ��B

		b. GRB333 �擾�̍�����
		c. GRB333 �� RGB555 / RGB565 �ϊ��̍�����
			b �� c �͓����ɏ������Ă��܂��B
			�^�C���f�[�^�� tile (0 <= tile <= 255),
			�p���b�g�� palette[] (9 bits),
			GRB333 �� RGB555 / RGB565 �ϊ��e�[�u���� table (16-bits)
			�Ƃ���ƁA���ۂɕ`�悷��s�N�Z�� pixel �́A

				pixel = table[palette[tile]];

			�œ�����B���� table �� palette �̂Q�d�Q�Ƃ��P�Ɍ��炷���Ƃ͉\�B
			palette �� GRB333 ��Ԃ��e�[�u������ RGB555 / RGB565 ��Ԃ��e�[�u��
			�ɂ��邾���ł悢�B
-----------------------------------------------------------------------------*/
//Kitao�X�Vv1.11�B������VCE�p���b�g�𒼐ڏ����悤�ɂ����B
static void
drawBgLine(
	Uint32	lineCounter)
{
	Uint32		vramAddr;
	Uint32		vramData;
	Uint32		offsetX;		// ��ʓ��^�C����X�I�t�Z�b�g 
	Uint32		offsetXmask;	// v1.65�ǉ�
	Uint32		tileY8;			// �^�C�����̂x���W(0-7)*8�BKitao�X�V�B�������Bv1.08�B
	Uint32		paletteSelect;	// 32�r�b�g�^�ɂ����ق��������ԑ��������Bv1.21
	Uint8*		pSrc;
	Sint32		width;
	Sint32		x = - (BXR & 7); //v1.11�X�V

	//HDW�̒l������������ꍇ�A���������тŖ��߂�B�t�@�C�i���u���X�^�[�ŕK�v�Bv2.14
	if ((_TvMax <= 85)&&(VCR <= 4)) //85(256/3�B���@���m�F)�BTRAVEL�G�v����OP�C�X�^�[�u���[�J�[�́u�A�����̒��v�ňꔑ����Ƃ�(_TvMax=112)�A(_VPR���傫�߂̂Ƃ�)�ɂ͂��̏��������Ȃ��Bv2.49�X�V
	{
		width = HDS - 2;
		while (width-- > 0)
		{
			_BgPutBuf[_VN][x] = 0;  _pScreenBuf[x] = 0;
			_BgPutBuf[_VN][++x] = 0;  _pScreenBuf[x] = 0;
			_BgPutBuf[_VN][++x] = 0;  _pScreenBuf[x] = 0;
			_BgPutBuf[_VN][++x] = 0;  _pScreenBuf[x] = 0;
			_BgPutBuf[_VN][++x] = 0;  _pScreenBuf[x] = 0;
			_BgPutBuf[_VN][++x] = 0;  _pScreenBuf[x] = 0;
			_BgPutBuf[_VN][++x] = 0;  _pScreenBuf[x] = 0;
			_BgPutBuf[_VN][++x] = 0;  _pScreenBuf[x] = 0;  x++;
		}
	}

	offsetXmask = _BGW[_VN] - 1; //v1.65�ǉ��B�������p
	offsetX = ((_TvStartPos + BXR) >> 3) & offsetXmask;
	tileY8 = (lineCounter & 7) << 3;
	vramAddr = ((lineCounter>>3)&(_BGH[_VN]-1)) * _BGW[_VN]; //��ʓ��^�C���̂x�I�t�Z�b�g*_BGW[_VN]�Bv1.08�X�V

	width = _TvMax >> 3;

	//v1.11�ǉ��B�������̂��ߍŏ��̂P�u���b�N�ix��0�ȏォ�ǂ����̔��������j�͕ʏ����B
	vramData = _pwVideoRam[_VN][vramAddr + offsetX]; //vramData = hi4color | pattern address
	paletteSelect = (vramData & 0xF000) >> 8;
	vramData &= 0x7FF;
	if (_BgTileCache[_VN][vramData][0] & 0x20) //�uCG�p�^�[�����ύX���ꂽ�v= bit5�������Ă�����A�^�C���L���b�V�����X�V����B
		update_bg_tile_cache(vramData);
	pSrc = &_BgTileCache[_VN][vramData][tileY8];
	if (x >= 0)	{ _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
	else { pSrc++; }
	if (++x >= 0) { _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
	else { pSrc++; }
	if (++x >= 0) { _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
	else { pSrc++; }
	if (++x >= 0) { _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
	else { pSrc++; }
	if (++x >= 0) { _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
	else { pSrc++; }
	if (++x >= 0) { _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
	else { pSrc++; }
	if (++x >= 0) { _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
	else { pSrc++; }
	if (++x >= 0) { _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
	else { pSrc++; }
	x++;
	offsetX++;
	offsetX &= offsetXmask;
	width--;

	while (width-- > 0)
	{
		// vramData = hi4color | pattern address
		vramData = _pwVideoRam[_VN][vramAddr + offsetX];
		paletteSelect = (vramData & 0xF000) >> 8;
		vramData &= 0x7FF;
		if (_BgTileCache[_VN][vramData][0] & 0x20) //�u�b�f�p�^�[�����ύX���ꂽ�v= bit5�������Ă�����A�^�C���L���b�V�����X�V����B
			update_bg_tile_cache(vramData);
		pSrc = &_BgTileCache[_VN][vramData][tileY8];
		_BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]];
		_BgPutBuf[_VN][++x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]];
		_BgPutBuf[_VN][++x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]];
		_BgPutBuf[_VN][++x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]];
		_BgPutBuf[_VN][++x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]];
		_BgPutBuf[_VN][++x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]];
		_BgPutBuf[_VN][++x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]];
		_BgPutBuf[_VN][++x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]];  x++;
		offsetX++;
		offsetX &= offsetXmask;
	}

	//v1.11�ǉ��B�������̂��ߍŌ�̂P�u���b�N�ix��ScreenW��菬���������ǂ����̔��������j�͕ʏ����B
	if (BXR & 7)
	{
		vramData = _pwVideoRam[_VN][vramAddr + offsetX]; //vramData = hi4color | pattern address
		paletteSelect = (vramData & 0xF000) >> 8;
		vramData &= 0x7FF;
		if (_BgTileCache[_VN][vramData][0] & 0x20) //�u�b�f�p�^�[�����ύX���ꂽ�v= bit5�������Ă�����A�^�C���L���b�V�����X�V����B
			update_bg_tile_cache(vramData);
		pSrc = &_BgTileCache[_VN][vramData][tileY8];
		if (x < _TvMax) { _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
		if (++x < _TvMax) { _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
		if (++x < _TvMax) { _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
		if (++x < _TvMax) { _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
		if (++x < _TvMax) { _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
		if (++x < _TvMax) { _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
		if (++x < _TvMax) { _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
		if (++x < _TvMax) { _BgPutBuf[_VN][x] = *pSrc++;  _pScreenBuf[x] = _PaletteBG[paletteSelect | _BgPutBuf[_VN][x]]; }
	}

	//HDW�̒l������������ꍇ�A�E�������тŖ��߂�B�t�@�C�i���u���X�^�[�ŕK�v�Bv2.14
	if ((_TvMax <= 85)&&(VCR <= 4)) //85(256/3�B���@���m�F)�BTRAVEL�G�v����OP�C�X�^�[�u���[�J�[�́u�A�����̒��v�ňꔑ����Ƃ�(_TvMax=112)�A(_VPR���傫�߂̂Ƃ�)�ɂ͂��̏��������Ȃ��Bv2.49�X�V
	{
		width = ((_TvWidth-_TvMax) >> 3) - (HDS-2);
		while (width-- > 0)
		{
			_BgPutBuf[_VN][x] = 0;  _pScreenBuf[x] = 0;
			_BgPutBuf[_VN][++x] = 0;  _pScreenBuf[x] = 0;
			_BgPutBuf[_VN][++x] = 0;  _pScreenBuf[x] = 0;
			_BgPutBuf[_VN][++x] = 0;  _pScreenBuf[x] = 0;
			_BgPutBuf[_VN][++x] = 0;  _pScreenBuf[x] = 0;
			_BgPutBuf[_VN][++x] = 0;  _pScreenBuf[x] = 0;
			_BgPutBuf[_VN][++x] = 0;  _pScreenBuf[x] = 0;
			_BgPutBuf[_VN][++x] = 0;  _pScreenBuf[x] = 0;  x++;
		}
	}

}


// �X�v���C�g�\���T�u(�X�v���C�g�D��p)
// Kitao�X�V�B�X�v���C�g�D�掞��BG�D�掞�A���ꂼ��ŃT�u�𕪂��č����������Bv1.08
//			  �߂�l��p�~���č������Bv1.65
static inline void
draw_sp_line_normal_s(
	Uint32	spno,			// �X�v���C�g�i���o�[�Bv1.65�ǉ�
	Uint32	pc,				// �p�^�[���ԍ� 
	Uint32	mode2bit, 		// 0x80(bit7)�𗧂ĂČĂԂ�2bit�p�^�[�����[�h�Bbit0�ɂ̓X�v���C�g�C���f�b�N�X�̍ŉ��ʃr�b�g�����ČĂԁBv1.65�X�V
	Uint32	paletteSelect,	// �J���[�p���b�g�C���f�b�N�X�̏�ʂS�r�b�g 
	Sint32	x,				// �X�L�������C����̂w�ʒu 
	Uint32	tileY)			// �^�C����̂x���W 
{
	int			a,i,w;
	Uint32		data;

	x -= _TvStartPos; //v1.11�ǉ�
	a = tileY << 4; //Kitao�ǉ��B������
	w = x + 15;
	if (w >= _TvMax)
		w = _TvMax - 1; //v1.65�X�V�B������
	if ((_TvMax <= 85)&&(VCR <= 4)) //v2.14�ǉ��Bv2.49�X�V
	{
		x += (HDS - 2) * 8;
		w += (HDS - 2) * 8;
	}
	if (x < 0)
	{
		a += -x;
		x = 0;
	} //v1.65�X�V�B������

	for (i=x; i<=w; i++)
	{
		if (mode2bit) //2bit�p�^�[�����[�h�̏ꍇ�Bv1.13�ǉ��BKi�����莑���������������܂����B"�t�@�C�e�B���O����"�ŕK�v�B
		{
			if (mode2bit & 1)
				data = _SpTileCache[_VN][pc][a++] >> 2;
			else
				data = _SpTileCache[_VN][pc][a++] & 0x3;
		}
		else //�ʏ�̃��[�h
			data = _SpTileCache[_VN][pc][a++];
		if (data & 0xF) //�L���ȃs�N�Z���������
		{
			if (!_SpPutBuf[_VN][i])
			{
				// �X�v���C�g��BG�̎�O�ɐݒ肳��Ă����ꍇ�́A 
				// ���D��x�̍����X�v���C�g�̃s�N�Z���������Ƃ����� 
				// �s�N�Z����`�����Ƃ��ł���B 
				_pScreenBuf[i] = _PaletteSP[paletteSelect | data]; //v1.11�X�V�B������VCE�p���b�g�𒼐ڏ����悤�ɂ����B
				if (spno == 0)
					_SpPutBuf[_VN][i] = 0x81; //v1.65�ǉ��B�X�v���C�g�i���o�[0�̃h�b�g�����邱�Ƃ�ޔ��B�X�v���C�g�̏Փ˔����"�X�v���C�g�i���o�[0"��"���̑��̃X�v���C�g"�Ƃ̏Փ˂𔻒肷��悤�ɂ����Bv1.65
				else
					_SpPutBuf[_VN][i] = 1;
			}
			else //���łɎႢ�ԍ��̃X�v���C�g�h�b�g���\������Ă����ꍇ
			{
				if (_SpPutBuf[_VN][i] & 0x80) //v1.65�ǉ��B�X�v���C�g�i���o�[0�̃h�b�g���������ꍇ�A�Փ˂Ƃ���B
					_bOverlap[_VN] = TRUE; //�X�v���C�g�̏Փ�
			}
		}
	}
}

//Kitao�ǉ��B�U�E�v���싅�̃J�E���g�\���X���b�v�p
static inline void
draw_sp_TheProYakyuu(
	Uint32	spno,			// �X�v���C�g�i���o�[
	Uint32	pc,				// �p�^�[���ԍ� 
	Uint32	paletteSelect,	// �J���[�p���b�g�C���f�b�N�X�̏�ʂS�r�b�g 
	Sint32	x,				// �X�L�������C����̂w�ʒu 
	Uint32	tileY,			// �^�C����̂x���W 
	Uint32	line)			// �������̍��W 
{
	int			a,i,w;
	Uint32		data;
	BOOL		bLeft = (x == 17+16);

	x -= _TvStartPos;
	a = tileY << 4;
	w = x + 15;

	for (i=x; i<=w; i++)
	{
		if (((bLeft)&&(i < x+5))||((!bLeft)&&(i > x+13)))
		{
			if ((bLeft)||(line <= 243)||(i > x+15))
				data = _SpTileCache[_VN][pc][a++];
			else
				data = 0x00; //STRIKE�̂R�J�E���g�ڕ����͓h��Ԃ�
		}
		else
		{
			if (line <= 240)
				data = _SpTileCache[_VN][pc][(6<<4) + (a++)];
			else if (line <= 243)
					data = _SpTileCache[_VN][pc+2][(a++) - (10<<4)];
			else if (line <= 246)
			{
				if ((bLeft)||(i < x+8))
					data = _SpTileCache[_VN][pc][(a++) - (6<<4)];
				else
					data = 0x00; //STRIKE�̂R�J�E���g�ڕ����͓h��Ԃ�
			}
			else
				data = _SpTileCache[_VN][pc-2][(a++) + (10<<4)];
		}
		if (data & 0xF)
		{
			if (!_SpPutBuf[_VN][i])
			{
				_pScreenBuf[i] = _PaletteSP[paletteSelect | data];
				_SpPutBuf[_VN][i] = 1;
			}
		}
	}
}

// �X�v���C�g�\���T�u(BG�D��p)
// Kitao�ǉ��B�X�v���C�g�D�掞��BG�D�掞�A���ꂼ��ŃT�u�𕪂��č����������Bv1.08
//			  �߂�l��p�~���č������Bv1.65
static inline void
draw_sp_line_normal_b(
	Uint32	spno,			// �X�v���C�g�i���o�[�Bv1.65�ǉ�
	Uint32	pc,				// �p�^�[���ԍ� 
	Uint32	mode2bit, 		// 0x80�𗧂ĂČĂԂ�2bit�p�^�[�����[�h�B0x01�ɂ̓X�v���C�g�C���f�b�N�X�̍ŉ��ʃr�b�g�����ČĂԁBv1.65�X�V
	Uint32	paletteSelect,	// �J���[�p���b�g�C���f�b�N�X�̏�ʂS�r�b�g 
	Sint32	x,				// �X�L�������C����̂w�ʒu 
	Uint32	tileY)			// �^�C����̂x���W 
{
	int			a,i,w;
	Uint32		data;

	x -= _TvStartPos; //v1.11�ǉ�
	a = tileY << 4; //Kitao�ǉ��B������
	w = x + 15;
	if (w >= _TvMax)
		w = _TvMax - 1; //v1.65�X�V�B������
	if ((_TvMax <= 85)&&(VCR <= 4)) //v2.14�ǉ��Bv2.49�X�V
	{
		x += (HDS - 2) * 8;
		w += (HDS - 2) * 8;
	}
	if (x < 0)
	{
		a += -x;
		x = 0;
	} //v1.65�X�V�B������

	for (i=x; i<=w; i++)
	{
		if (mode2bit) //2bit�p�^�[�����[�h�̏ꍇ�Bv1.13�ǉ��BKi�����莑���������������܂����B"�t�@�C�e�B���O����"�ŕK�v�B
		{
			if (mode2bit & 1)
				data = _SpTileCache[_VN][pc][a++] >> 2;
			else
				data = _SpTileCache[_VN][pc][a++] & 0x3;
		}
		else //�ʏ�̃��[�h
			data = _SpTileCache[_VN][pc][a++];
		if ((data & 0xF) == 0) //�L���ȃs�N�Z���������Ƃ��̓X�L�b�v���� 
			continue;
		// �X�v���C�g��BG�̔w��̏ꍇ�� 
		// BG�̎w�W���c����MSB����1�ɃZ�b�g����B 
		if (_BgPutBuf[_VN][i]) //BG�̃s�N�Z����������
		{
			//v1.65�X�V�BBG�ɉB��Ă���ꍇ�A�X�v���C�g�̏Փ˔���͍s��Ȃ��悤�ɂ����B(���@���m�F)
			//if (_SpPutBuf[_VN][i] & 0x80) //v1.65�X�V�B�X�v���C�g�i���o�[0�̃h�b�g���������ꍇ�A�Փ˂Ƃ���B
			//	_bOverlap[_VN] = TRUE;
			//if (spno == 0)
			//	_SpPutBuf[_VN][i] = 0x82; //v1.65�ǉ��B�X�v���C�g�i���o�[0�̃h�b�g�����邱�Ƃ�ޔ��B�X�v���C�g�̏Փ˔����"�X�v���C�g�i���o�[0"��"���̑��̃X�v���C�g"�Ƃ̏Փ˂𔻒肷��悤�ɂ����Bv1.65
			//else
			_SpPutBuf[_VN][i] = 2; //BG�̔w��ɃX�v���C�g�������ꍇ2�ɐݒ�B�X�p�O���̏����ŕK�v�Bv1.11�X�V
			
		}
		else
		{
			if (!_SpPutBuf[_VN][i])
			{
				// �X�v���C�g��BG�̔w��ɐݒ肳��Ă��Ă��A 
				// ������BG�������͗D��x�̂�荂���X�v���C�g�̃s�N�Z���������ꍇ�� 
				// �s�N�Z����`�����Ƃ��ł���B 
				_pScreenBuf[i] = _PaletteSP[paletteSelect | data]; //v1.11�X�V�B������VCE�p���b�g�𒼐ڏ����悤�ɂ����B
				if (spno == 0)
					_SpPutBuf[_VN][i] = 0x81; //v1.65�ǉ��B�X�v���C�g�i���o�[0�̃h�b�g�����邱�Ƃ�ޔ��B�X�v���C�g�̏Փ˔����"�X�v���C�g�i���o�[0"��"���̑��̃X�v���C�g"�Ƃ̏Փ˂𔻒肷��悤�ɂ����Bv1.65
				else
					_SpPutBuf[_VN][i] = 1;
			}
			else //���łɎႢ�ԍ��̃X�v���C�g�h�b�g���\������Ă����ꍇ
			{
				if (_SpPutBuf[_VN][i] & 0x80) //v1.65�ǉ��B�X�v���C�g�i���o�[0�̃h�b�g���������ꍇ�A�Փ˂Ƃ���B
					_bOverlap[_VN] = TRUE; //�X�v���C�g�̏Փ�
			}
		}
	}
}

// �X�v���C�g�\���T�u(���E���]�B�X�v���C�g�D��p)
// Kitao�X�V�B�X�v���C�g�D�掞��BG�D�掞�A���ꂼ��ŃT�u�𕪂��č����������Bv1.08
//			  �߂�l��p�~���č������Bv1.65
static inline void
draw_sp_line_hflip_s(
	Uint32	spno,			// �X�v���C�g�i���o�[�Bv1.65�ǉ�
	Uint32	pc,				// �p�^�[���ԍ� 
	Uint32	mode2bit, 		// 0x80�𗧂ĂČĂԂ�2bit�p�^�[�����[�h�B0x01�ɂ̓X�v���C�g�C���f�b�N�X�̍ŉ��ʃr�b�g�����ČĂԁBv1.65�X�V
	Uint32	paletteSelect,	// �J���[�p���b�g�C���f�b�N�X�̏�ʂS�r�b�g 
	Sint32	x,				// �X�L�������C����̂w�ʒu 
	Uint32	tileY)			// �^�C����̂x���W 
{
	int			a,i,w;
	Uint32		data;

	x -= _TvStartPos; //v1.11�ǉ�
	a = (tileY << 4) + 15; //Kitao�ǉ��B������
	w = x + 15;
	if (w >= _TvMax)
		w = _TvMax - 1; //v1.65�X�V�B������
	if ((_TvMax <= 85)&&(VCR <= 4)) //v2.14�ǉ��Bv2.49�X�V
	{
		x += (HDS - 2) * 8;
		w += (HDS - 2) * 8;
	}
	if (x < 0)
	{
		a -= -x;
		x = 0;
	} //v1.65�X�V�B������

	for (i=x; i<=w; i++)
	{
		if (mode2bit) //2bit�p�^�[�����[�h�̏ꍇ�Bv1.13�ǉ��BKi�����莑���������������܂����B"�t�@�C�e�B���O����"�ŕK�v�B
		{
			if (mode2bit & 1)
				data = _SpTileCache[_VN][pc][a--] >> 2;
			else
				data = _SpTileCache[_VN][pc][a--] & 0x3;
		}
		else //�ʏ�̃��[�h
			data = _SpTileCache[_VN][pc][a--];
		if ((data & 0xF) == 0) //�L���ȃs�N�Z���������Ƃ��̓X�L�b�v���� 
			continue;
		if (!_SpPutBuf[_VN][i])
		{
			_pScreenBuf[i] = _PaletteSP[paletteSelect | data]; //v1.11�X�V�B������VCE�p���b�g�𒼐ڏ����悤�ɂ����B
			if (spno == 0)
				_SpPutBuf[_VN][i] = 0x81; //v1.65�ǉ��B�X�v���C�g�i���o�[0�̃h�b�g�����邱�Ƃ�ޔ��B�X�v���C�g�̏Փ˔����"�X�v���C�g�i���o�[0"��"���̑��̃X�v���C�g"�Ƃ̏Փ˂𔻒肷��悤�ɂ����Bv1.65
			else
				_SpPutBuf[_VN][i] = 1;
		}
		else //���łɎႢ�ԍ��̃X�v���C�g�h�b�g���\������Ă����ꍇ
		{
			if (_SpPutBuf[_VN][i] & 0x80) //v1.65�ǉ��B�X�v���C�g�i���o�[0�̃h�b�g���������ꍇ�A�Փ˂Ƃ���B
				_bOverlap[_VN] = TRUE; //�X�v���C�g�̏Փ�
		}
	}
}

// �X�v���C�g�\���T�u(���E���]�BBG�D��p)
// Kitao�X�V�B�X�v���C�g�D�掞��BG�D�掞�A���ꂼ��ŃT�u�𕪂��č����������Bv1.08
//			  �߂�l��p�~���č������Bv1.65
static inline void
draw_sp_line_hflip_b(
	Uint32	spno,			// �X�v���C�g�i���o�[�Bv1.65�ǉ�
	Uint32	pc,				// �p�^�[���ԍ� 
	Uint32	mode2bit, 		// 0x80�𗧂ĂČĂԂ�2bit�p�^�[�����[�h�B0x01�ɂ̓X�v���C�g�C���f�b�N�X�̍ŉ��ʃr�b�g�����ČĂԁBv1.65�X�V
	Uint32	paletteSelect,	// �J���[�p���b�g�C���f�b�N�X�̏�ʂS�r�b�g 
	Sint32	x,				// �X�L�������C����̂w�ʒu 
	Uint32	tileY)			// �^�C����̂x���W 
{
	int			a,i,w;
	Uint32		data;

	x -= _TvStartPos; //v1.11�ǉ�
	a = (tileY << 4) + 15; //Kitao�ǉ��B������
	w = x + 15;
	if (w >= _TvMax)
		w = _TvMax - 1; //v1.65�X�V�B������
	if ((_TvMax <= 85)&&(VCR <= 4)) //v2.14�ǉ��Bv2.49�X�V
	{
		x += (HDS - 2) * 8;
		w += (HDS - 2) * 8;
	}
	if (x < 0)
	{
		a -= -x;
		x = 0;
	} //v1.65�X�V�B������

	for (i=x; i<=w; i++)
	{
		if (mode2bit) //2bit�p�^�[�����[�h�̏ꍇ�Bv1.13�ǉ��BKi�����莑���������������܂����B"�t�@�C�e�B���O����"�ŕK�v�B
		{
			if (mode2bit & 1)
				data = _SpTileCache[_VN][pc][a--] >> 2;
			else
				data = _SpTileCache[_VN][pc][a--] & 0x3;
		}
		else //�ʏ�̃��[�h
			data = _SpTileCache[_VN][pc][a--];
		if ((data & 0xF) == 0) //�L���ȃs�N�Z���������Ƃ��̓X�L�b�v���� 
			continue;
		if (_BgPutBuf[_VN][i]) //BG�̃s�N�Z����������
		{
			//v1.65�X�V�BBG�ɉB��Ă���ꍇ�A�X�v���C�g�̏Փ˔���͍s��Ȃ��悤�ɂ����B(���@���m�F)
			//if (_SpPutBuf[_VN][i] & 0x80) //v1.65�X�V�B�X�v���C�g�i���o�[0�̃h�b�g���������ꍇ�A�Փ˂Ƃ���B
			//	_bOverlap[_VN] = TRUE;
			//if (spno == 0)
			//	_SpPutBuf[_VN][i] = 0x82; //v1.65�ǉ��B�X�v���C�g�i���o�[0�̃h�b�g�����邱�Ƃ�ޔ��B�X�v���C�g�̏Փ˔����"�X�v���C�g�i���o�[0"��"���̑��̃X�v���C�g"�Ƃ̏Փ˂𔻒肷��悤�ɂ����Bv1.65
			//else
			_SpPutBuf[_VN][i] = 2; //BG�̔w��ɃX�v���C�g�������ꍇ2�ɐݒ�B�X�p�O���̏����ŕK�v�Bv1.11�X�V
		}
		else
		{
			if (!_SpPutBuf[_VN][i])
			{
				// �X�v���C�g��BG�̔w��ɐݒ肳��Ă��Ă��A 
				// ������BG�������͗D��x�̂�荂���X�v���C�g�̃s�N�Z���������ꍇ�� 
				// �s�N�Z����`�����Ƃ��ł���B 
				_pScreenBuf[i] = _PaletteSP[paletteSelect | data]; //v1.11�X�V�B������VCE�p���b�g�𒼐ڏ����悤�ɂ����B
				if (spno == 0)
					_SpPutBuf[_VN][i] = 0x81; //v1.65�ǉ��B�X�v���C�g�i���o�[0�̃h�b�g�����邱�Ƃ�ޔ��B�X�v���C�g�̏Փ˔����"�X�v���C�g�i���o�[0"��"���̑��̃X�v���C�g"�Ƃ̏Փ˂𔻒肷��悤�ɂ����Bv1.65
				else
					_SpPutBuf[_VN][i] = 1;
			}
			else //���łɎႢ�ԍ��̃X�v���C�g�h�b�g���\������Ă����ꍇ
			{
				if (_SpPutBuf[_VN][i] & 0x80) //v1.65�ǉ��B�X�v���C�g�i���o�[0�̃h�b�g���������ꍇ�A�Փ˂Ƃ���B
					_bOverlap[_VN] = TRUE; //�X�v���C�g�̏Փ�
			}
		}
	}
}


/*-----------------------------------------------------------------------------
	[draw_sp_line]

	width = 32 �̂Ƃ��� index �� D0 ���[���̃A�h���X����X�^�[�g����B


	+---+
	|	|
	+---+

	+---+
	|	|
	+---+
	|	|
	+---+

	+---+
	|	|
	+---+
	|	|
	+---+
	|	|
	+---+
	|	|
	+---+

	+---+---+
	|	|	|
	+---+---+

	+---+---+
	|	|	|
	+---+---+
	|	|	|
	+---+---+

	+---+---+
	|	|	|
	+---+---+
	|	|	|
	+---+---+
	|	|	|
	+---+---+
	|	|	|
	+---+---+

-----------------------------------------------------------------------------*/
//v1.65�X�V�B�߂�l��p�~���Փˊ֘A�̒��ԕϐ����J�b�g���č������B
static void
draw_sp_line(
	Sint32	line)	// ���݂̃��X�^�J�E���^�l
{
	Uint32		i;
	Sint32		x;
	Sint32		y;
	Sint32		width;
	Sint32		height;
	Uint32		tileY;
	Uint32		paletteSelect; //Kitao�X�V
	Uint32		nSpPerLine = 0;
	Uint32		index;
	Uint32		spFlags; //v1.65�ǉ�
	Uint32		mode2bit; //v1.13�ǉ��BKi�����莑���������������܂����B"�t�@�C�e�B���O����"�ŕK�v�Bv1.65�X�V
	BOOL		bDone; //v2.70

	for (i = 0; i < NUM_SPRITES; i++)
	{
		y = _SpRam[_VN][(i<<2)+0] & 0x3FF;
		if (line >= y) //Kitao�X�V�B�������̂���height�ݒ�O�ɑ�P�������`�F�b�N�Bv1.07
		{
			spFlags = _SpRam[_VN][(i<<2)+3]; //v1.65�B�������̂��߂����ŕϐ��ɓ���Ă����B
			height = _HeightTable[(spFlags & 0x3000) >> 12];
			if (line < y + height)
			{
				x = _SpRam[_VN][(i<<2)+1] & 0x3FF; //Kitao�X�V�Bv1.08
				width = spFlags & 0x100; //Kitao�X�V�Bwidth==0�Ȃ牡16�T�C�Y�B����ȊO�Ȃ牡32�T�C�Y�B�������Bv1.08
				index = (_SpRam[_VN][(i<<2)+2] & 0x7FF) >> 1; //Kitao�X�V�B�p�^�[���A�h���X�̎w���bit0�`10�܂ł�L���Ƃ����Bbit10�܂ōL�������Ƃłۂ��Ղ郁�C���̃I�[�v�j���O��A�V�X�l���̃G���h��ʓ��ł��݂��o��̂������B
				if ((MWR & 0xC) == 0x4) //2bit�p�^�[�����[�h�̏ꍇ�Bv1.13�ǉ��BKi�����莑���������������܂����B"�t�@�C�e�B���O����"�ŕK�v�B
					mode2bit = 0x80 | (_SpRam[_VN][(i<<2)+2] & 1); //v1.13�ǉ��Bv1.65�X�V
				else
					mode2bit = 0;

				tileY = line - y;

				// width, height, ���]�t���O�ɉ����� index �l���C������ 
				nSpPerLine++;
				if (width) //��32�T�C�Y�Ȃ�
				{
					index = (index & ~1) | ((spFlags & 0x800) >> 11); //v1.08�X�V�B(spFlags & 0x800)�c���E���]�t���O
					nSpPerLine++; //Kitao�ǉ��B��32���[�h�̂Ƃ��͉��Q�����ƌ��Ȃ����
				}

				if (nSpPerLine > _MaxSpPerLine[_VN]) //Kitao�X�V�B���@�ŉ��ɕ\���ł���X�v���C�g�����z���Ă�����Bv2.63�X�V�B"R-TYPE CD"�i��336,MWR��bit0���^�j�ł͉���14�܂ŁB"R-TYPE CD"�̂�����̑������Č��B
				{
					_bSpOver[_VN] = TRUE;
					if (_bPerformSpriteLimit) //Kitao�ǉ��B�X�v���C�g�������Č�����Ȃ炱���ŕ`��I���i�p���[���[�O�R�̑ŐȌ��ʕ\���ȂǂŕK�v�j
					{
						if ((width)&&(nSpPerLine == _MaxSpPerLine[_VN]+1)) //Kitao�ǉ��B��32�̃X�v���C�g����������������ꍇ
							width = 0; //��16�h�b�g�������\������B���̓`���U�i�h�DII(�v�����[�O����RUN�{�^������������ʂŃ^�C�g�������̉E�ɃS�~)�ŕK�v�B
						else
							break; //�`��I��
					}
				}

				if (y == 0 || x == 0 || y >= 240+64 || x >= _ScreenW[_VN]+32)
					continue; //��ʕ\���͈͊O�Ȃ�

				x -= 32;

				//v1.65�X�V�B�V���v�������킸���ɍ�����
				if (height == 32)
				{
					if (tileY >= 16)
						index = (index | 2) ^ ((spFlags & 0x8000) >> 14); //(spFlags & 0x8000)�c�㉺���]�t���O
					else
						index = (index & ~2) | ((spFlags & 0x8000) >> 14);
				}
				else if (height == 64)
				{
					if (tileY >= 48) //v1.08�X�V�B������
						index = ((index | 6) ^ ((spFlags & 0x8000) >> 13)) ^ ((spFlags & 0x8000) >> 14);
					else if (tileY >= 32)
						index = (((index | 4) & ~2) ^ ((spFlags & 0x8000) >> 13)) | ((spFlags & 0x8000) >> 14);
					else if (tileY >= 16)
						index = (((index & ~4) | 2) | ((spFlags & 0x8000) >> 13)) ^ ((spFlags & 0x8000) >> 14);
					else
						index = (index & ~6) | ((spFlags & 0x8000) >> 13) | ((spFlags & 0x8000) >> 14);
				}

				//index &= 0x1FF;
				if (index > 0x1FF) //�V�X�l���̃G���f�B���O�ŕςȎԂ��\������Ȃ��悤�ɂ��邽�߂ɕK�v�B
				{
					//PRINTF("%X",index); //test
					continue;
				}

				tileY &= 15;
				if (spFlags & 0x8000) //�㉺���]�t���O���ݒ肳��Ă����ꍇ�Bv1.08�X�V�B������
					tileY = 15 - tileY;

				paletteSelect = (spFlags & 0xF) << 4;

				if (_SpTileCache[_VN][index][0] & 0x20)
					update_sp_tile_cache(index);
				if (spFlags & 0x800) //���E���]�t���O���ݒ肳��Ă����ꍇ�Bv1.08�X�V�B������
				{
					if (spFlags & 0x80) //�X�v���C�g�D��̏ꍇ�Bv1.08�X�V�B������
						draw_sp_line_hflip_s(i, index, mode2bit, paletteSelect, x, tileY);
					else //BG�D��̏ꍇ
						draw_sp_line_hflip_b(i, index, mode2bit, paletteSelect, x, tileY);
				}
				else
				{
					if (spFlags & 0x80) //�X�v���C�g�D��̏ꍇ�Bv1.08�X�V�B������
					{
						//�싅�Q�[���ŁA�{�[���ƃX�g���C�N�̕\�����X���b�v���鏈���Bv2.70
						bDone = FALSE;
						if (APP_GetStrikeBallSwap())
						{
							if (_bEikanKimi) //�h���͌N��
							{
								//PRINTF("X = %d", (_SpRam[_VN][(17<<2)+1] & 0x3FF));//test
								//PRINTF("Y = %d", (_SpRam[_VN][(17<<2)+0] & 0x3FF));//test
								if (((_SpRam[_VN][(17<<2)+1] & 0x3FF) == 56)&&((_SpRam[_VN][(17<<2)+0] & 0x3FF) == 244)) //�J�E���g�\����ʂȂ�
								{
									switch (i)
									{
										case 16:
										case 17:
											index = (_SpRam[_VN][((i+3)<<2)+2] & 0x7FF) >> 1; break;
										case 18:
											draw_sp_line_normal_s(i, (_SpRam[_VN][(22<<2)+2] & 0x7FF) >> 1, 0, paletteSelect, x+8, tileY); //3�{�[���ڂ̃J�E���g�\��
											index = (_SpRam[_VN][(21<<2)+2] & 0x7FF) >> 1;
										break;
										case 19:
										case 20:
										case 21:
											index = (_SpRam[_VN][((i-3)<<2)+2] & 0x7FF) >> 1; break;
										case 22:
											bDone = TRUE; break; //�R�{�[���ڂ�i=18(&&x=32)�̂Ƃ��ɕ\���ς�
									}
								}
							}
							if (_bPowerLeague) //�p���[���[�O
							{
								if (i == 2)
								{
									//PRINTF("X, Y = %d, %d", x,y);//test
									if ((x == 32)&&(y == 240)) //�J�E���g�\����ʂȂ�
									{
										if (line < 248)
											tileY += 8;
										else if (line < 256)
											tileY -= 8;
									}
								}
							}
							if (_bTheProYakyuu) //�C���e�b�NCD�싅�R��i�U�E�v���싅�C�U�E�v���싅SUPER�C�U�E�v���싅SUPER'94�j
							{
								//if ((x == 212)&&(y == 184))
								//	PRINTF("i = %d", i); //test
								if ((i >= 9)&&(i <= 38)) //9�c������O�C11�cBALL���C13�cSTRKE���C12&14&18&19&20&22&24&26&28&32&30&38�c�Ŏ҃X�e�[�^�X�\����(SUPER�ȍ~�B�����i�[���o��ƕω�)
								{
									//PRINTF("X, Y = %d, %d", x,y);//test
									if ((x == 212)&&(y == 184)) //�J�E���g�\����ʂȂ�
									{
										if (line < 192)
											tileY += 8;
										else
											tileY -= 8;
									}
								}
								//if ((x == 49)&&(y == 231))
								//	PRINTF("i = %d", i); //test
								if ((i >= 0)&&(i <= 15)) //�����i�[�̐���0(�`�F���W��)�`6�ɕω��B�t�@�[���̂Ƃ�4�`9�ɕω��H�B�_���������Ƃ���7�`11�ɕω��H�B�_��������+SAFE�\���̂Ƃ�+4�Ȃ̂ł��Ԃ�ő�15�܂ł����B
								{
									//PRINTF("X, Y = %d, %d", x,y);//test
									if ((x == 49)&&(y == 231)) //�t�B�[���h�̃J�E���g�\����ʂȂ�
									{
										if (line >= 238)
										{
											draw_sp_TheProYakyuu(i, index, paletteSelect, x, tileY, line);
											bDone = TRUE;
										}
									}
								}
								if ((i >= 2)&&(i <= 17)) //�����i�[�̐���2�`7�ɕω��B�t�@�[���̂Ƃ�6�`10�ɕω��H�B�_���������Ƃ���9�`12�ɕω��H
								{
									//PRINTF("X, Y = %d, %d", x,y);//test
									if ((x == 49)&&(y == 247)) //�t�B�[���h�̃J�E���g�\����ʂȂ�
									{
										if (line <= 249)
										{
											draw_sp_TheProYakyuu(i, index, paletteSelect, x, tileY, line);
											bDone = TRUE;
										}
									}
								}
							}
						}
						if (!bDone)
							draw_sp_line_normal_s(i, index, mode2bit, paletteSelect, x, tileY);
					}
					else //BG�D��̏ꍇ
						draw_sp_line_normal_b(i, index, mode2bit, paletteSelect, x, tileY);
				}

				//��32�T�C�Y�̏ꍇ�A�E���������\��
				if ((width)&&(x+16 < _ScreenW[_VN]))
				{
					index ^= 1;
					if (_SpTileCache[_VN][index][0] & 0x20)
						update_sp_tile_cache(index);
					if (spFlags & 0x800) //HFLIP���ݒ肳��Ă����ꍇ�Bv1.08�X�V�B������
					{
						if (spFlags & 0x80) //�X�v���C�g�D��̏ꍇ�Bv1.08�X�V�B������
							draw_sp_line_hflip_s(i, index, mode2bit, paletteSelect, x+16, tileY);
						else //BG�D��̏ꍇ
							draw_sp_line_hflip_b(i, index, mode2bit, paletteSelect, x+16, tileY);
					}
					else
					{
						if (spFlags & 0x80) //�X�v���C�g�D��̏ꍇ�Bv1.08�X�V�B������
						{
							//�싅�Q�[���ŁA�{�[���ƃX�g���C�N�̕\�����X���b�v���鏈���Bv2.70
							bDone = FALSE;
							if (APP_GetStrikeBallSwap())
							{
								if (_bTheProYakyuu) //�C���e�b�NCD�싅�R��i�U�E�v���싅�C�U�E�v���싅SUPER�C�U�E�v���싅SUPER'94�j
								{
									//if ((x == 17)&&(y == 231))
									//	PRINTF("i = %d", i); //test
									if ((i >= 0)&&(i <= 15)) //�����i�[�̐���0(�`�F���W��)�`6�ɕω��B�t�@�[���̂Ƃ�5�`9�ɕω��H�B�_���������Ƃ���8�`11�ɕω��H�B�_��������+SAFE�\���̂Ƃ�+4�Ȃ̂ł��Ԃ�ő�15�܂ł����B
									{
										//PRINTF("X, Y = %d, %d", x,y);//test
										if ((x == 17)&&(y == 231)) //�t�B�[���h�̃J�E���g�\����ʂȂ�
										{
											if (line >= 238)
											{
												draw_sp_TheProYakyuu(i, index, paletteSelect, x+16, tileY, line);
												bDone = TRUE;
											}
										}
									}
									if ((i >= 2)&&(i <= 17)) //�����i�[�̐���2�`8�ɕω��B�t�@�[���̂Ƃ�7�`11�ɕω��H�B�_���������Ƃ���10�`13�ɕω��H
									{
										//PRINTF("X, Y = %d, %d", x,y);//test
										if ((x == 17)&&(y == 247)) //�t�B�[���h�̃J�E���g�\����ʂȂ�
										{
											if (line <= 249)
											{
												draw_sp_TheProYakyuu(i, index, paletteSelect, x+16, tileY, line);
												bDone = TRUE;
											}
										}
									}
								}
							}
							if (!bDone)
								draw_sp_line_normal_s(i, index, mode2bit, paletteSelect, x+16, tileY);
						}
						else //BG�D��̏ꍇ
							draw_sp_line_normal_b(i, index, mode2bit, paletteSelect, x+16, tileY);
					}
				}
			}
		}
	}
}


/*-----------------------------------------------------------------------------
	[drawLine]
		BG����уX�v���C�g���P���C���`�悵�܂��B
-----------------------------------------------------------------------------*/
static void //Kitao�X�V�B���荞�ݗv���������ōs���悤�ɂ����̂ŁA�߂�l�͕s�v�ɂ����B�X�p�O���ɑΉ������B
drawLine(
	Sint32	scanLine)
{
	int		i;

	_VN=0;

	if (_DisplayCounter < DISPLAY_STARTLINE || _DisplayCounter >= DISPLAY_ENDLINE || _bBurstMode[0])
	{
		//Kitao�X�V�B���\���̈�i���сj�̓X�v���C�g�̓����F�Ŗ��߂���B
		for (i=0; i<_TvMax; i++)
			_pScreenBuf[i] = _PaletteSP[0];
	}
	else
	{
		//�ʏ�́A�����C����CR�̒l�𔽉f������B���C���{�[�A�C�����h�̏ꍇ(CR��bit8-9(�\���o�͑I��)�������Ă���)�A�P���C���O�̒l���g���B���@�œ��l���͖��m�F�Bv1.61�X�V
		//										�\���o�͑I���������Ă��Ă��ABG���X�v���C�g�̂ǂ��炩��\������ꍇ�́A�����C�����g���B�����łȂ��ƁA�X�[�p�[�_���C�A�X�ŃQ�[����ʍŏド�C������\���ɂȂ��Ă��܂����g�C���L�b�Y�ŃX�e�[�^�X�̋��E�Ɏ��L���������܂�Bv1.67,v2.39
		if (((CR & 0x100) == 0)||(CR & 0xC0)) //((CR & 0x100) == 0)�̏������O���ƁA�X�g�Q�f�̃U���M�G�t�ʂŉ�ʉE���̂ق��ɂ��鍽���P���C�����Ƀn�~�o���B
			_prevCR[0] = _Regs[0][VDC_CR];
		
		if ((_prevCR[0] & 0x80)&& //���C���{�[�A�C�����h�ŁA��\���t���O�͂P���C���O�̒l�𔽉f������悤�ɂ����B���v�V�[�������@�Ɠ��l�ɂȂ����Bv1.12
			(_bBGLayer)) //v2.06�ǉ�
				drawBgLine(_LineCounter[0]);
		else
		{
			//BG�̓����F�Ŗ��߂���B���C���{�[�A�C�����h�̐��v�V�[��
			for (i=0; i<_TvMax; i++)
				_pScreenBuf[i] = _PaletteBG[0];
			memset(&_BgPutBuf[0][0], 0, _TvMax); //v1.11�ǉ�
			if ((_TvMax <= 85)&&(VCR <= 4)) //v2.14�ǉ��Bv2.49�X�V
			{
				for (i=_TvMax; i<_TvWidth; i++)
					_pScreenBuf[i] = _PaletteBG[0];
				memset(&_BgPutBuf[0][0], _TvMax, _TvWidth-_TvMax);
			}
		}
		
		if ((_prevCR[0] & 0x40)&& //���C���{�[�A�C�����h�ŁA��\���t���O�͂P���C���O�̒l�𔽉f������悤�ɂ����B���v�V�[�������@�Ɠ��l�ɂȂ����Bv1.12
			(_bSpriteLayer)) //v2.06�ǉ�
		{
			if ((_TvMax <= 85)&&(VCR <= 4)) //v2.14�ǉ��Bv2.49�X�V
				memset(&_SpPutBuf[0][0], 0, _TvWidth);
			else //�ʏ�
				memset(&_SpPutBuf[0][0], 0, _TvMax);
			draw_sp_line(_RasterCounter[0]);
		}
	}
	_prevCR[0] = _Regs[0][VDC_CR]; //�P���C���O��CR�l�Ƃ��ĕۑ��Bv1.21
}

//Kitao�ǉ��B�X�[�p�[�O���t�B�b�N�X�p�Bv1.11�X�V
static void
drawLineSuperGrafx(
	Sint32	scanLine)
{
	int			i;
	Uint32*		pScreenBufR;
	Sint32		x;
	Sint32		n;

	//�Q�ڂ�VDC�iVDC1�B�`�挋�ʂ�_LineBufVDC2�Ɋi�[�j
	_VN=1;
	pScreenBufR = _pScreenBuf;
	_pScreenBuf = &_LineBufVDC2[0];
	if (_DisplayCounter < DISPLAY_STARTLINE || _DisplayCounter >= DISPLAY_ENDLINE || _bBurstMode[1])
	{
		//Kitao�X�V�B���\���̈�i���сj�̓X�v���C�g�̓����F�Ŗ��߂���B
		for (i=0; i<_TvMax; i++)
			_pScreenBuf[i] = _PaletteSP[0];
		memset(&_BgPutBuf[1][0], 0, _TvMax);
		memset(&_SpPutBuf[1][0], 0, _TvMax); //�X�v���C�g�F�Ŗ��߂��邪�A�X�v���C�g��\�����Ă���킯�ł͂Ȃ��̂�0�t�B���B�喂�E���̋N�����̃������`�F�b�N�\���Ŋm�F�Bv1.12
	}
	else
	{
		if (((CR & 0x100) == 0)||(CR & 0x40)) //�ʏ�́A�����C����CR�̒l�𔽉f������B
			_prevCR[1] = _Regs[1][VDC_CR];
		
		if ((_prevCR[1] & 0x80)&&
			(_bBG2Layer)) //v2.06�ǉ�
				drawBgLine(_LineCounter[1]);
		else
		{
			//BG�̓����F�Ŗ��߂���B
			for (i=0; i<_TvMax; i++)
				_pScreenBuf[i] = _PaletteBG[0];
			memset(&_BgPutBuf[1][0], 0, _TvMax);
		}
		
		memset(&_SpPutBuf[1][0], 0, _TvMax);
		if ((_prevCR[1] & 0x40)&&
			(_bSprite2Layer)) //v2.06�ǉ�
				draw_sp_line(_RasterCounter[1]);
	}
	_prevCR[1] = _Regs[1][VDC_CR];

	//�P�ڂ�VDC�iVDC0�B�`�挋�ʂ�_ScreenBuf�Ɋi�[�j
	_VN=0;
	_pScreenBuf = pScreenBufR;
	if (_DisplayCounter < DISPLAY_STARTLINE || _DisplayCounter >= DISPLAY_ENDLINE || _bBurstMode[0])
	{
		//Kitao�X�V�B���\���̈�i���сj�̓X�v���C�g�̓����F�Ŗ��߂���B
		for (i=0; i<_TvMax; i++)
			_pScreenBuf[i] = _PaletteSP[0];
		memset(&_BgPutBuf[0][0], 0, _TvMax);
		memset(&_SpPutBuf[0][0], 0, _TvMax); //�X�v���C�g�F�Ŗ��߂��邪�A�X�v���C�g��\�����Ă���킯�ł͂Ȃ��̂�0�t�B���B�喂�E���̋N�����̃������`�F�b�N�\���Ŋm�F�Bv1.12
	}
	else
	{
		if (((CR & 0x100) == 0)||(CR & 0x40)) //�ʏ�́A�����C����CR�̒l�𔽉f������B
			_prevCR[0] = _Regs[0][VDC_CR];
		
		if ((_prevCR[0] & 0x80)&&
			(_bBGLayer)) //v2.06�ǉ�
				drawBgLine(_LineCounter[0]);
		else
		{
			//BG�̓����F�Ŗ��߂���B
			for (i=0; i<_TvMax; i++)
				_pScreenBuf[i] = _PaletteBG[0];
			memset(&_BgPutBuf[0][0], 0, _TvMax);
		}
		
		memset(&_SpPutBuf[0][0], 0, _TvMax);
		if ((_prevCR[0] & 0x40)&&
			(_bSpriteLayer)) //v2.06�ǉ�
				draw_sp_line(_RasterCounter[0]);
	}
	_prevCR[0] = _Regs[0][VDC_CR];

	//�h�b�g���Ƃ�VDC�D�揇�ʂ��Q�Ƃ��A�ŏI�`�挋�ʂ�_pScreenBuf�Ɏ��߂�B
	//Border1<Border2�̏ꍇ��z��B�����炭�ʏ�͂���BBorder1>Border2�͎g���Ă���\�t�g�����������������ׂ��B
	x = 0;
	for (i=3; i>=0; i--)
	{
		switch (i)
		{
			case 3: //���[����Border1�܂ł�`��
				n = _VpcBorder1 + 1;
				if (n > _TvMax)
					n = _TvMax;
				break;
			case 2: //���ݔ�g�p�BBorder1>Border2�͎g���Ă���\�t�g�����������������B
				continue;
			case 1: //Border1����Border2�܂ł�`��
				n = _VpcBorder2 + 1;
				if (n > _TvMax)
					n = _TvMax;
				break;
			case 0: //Border2����E��`��B�ʏ�͂��ꂾ�����g���Q�[���������B
				n = _TvMax;
				break;
			default:
				n = 0; //�R���p�C���G���[�h�~�̂��߂̏�����
				break;
		}
		switch (_VpcPriority[i])
		{
			//VDC0�����\���i����2�r�b�g��01�j
			case 0x1:
			case 0xD:
			case 0x5:
			case 0x9:
				// ���̂܂܂̏�Ԃ�OK
				x = n;
				break;
			
			//VDC1�����\���i����2�r�b�g��10�j
			case 0x2:
			case 0xE:
			case 0x6:
			case 0xA:
				while (x < n)
				{
					_pScreenBuf[x] = _LineBufVDC2[x];
					x++;
				}
				break;
			
			//VDC0���D���VDC0,VDC1�Ƃ��\���i����2�r�b�g��11�܂���00�j
			case 0x3: //VDC0���D��
			case 0xF: //0xF�c���2�r�b�g��11�̂Ƃ���00�̂Ƃ��Ɠ��l�ɂ����B
			case 0x0:
			case 0xC:
				while (x < n)
				{
					if (!_BgPutBuf[0][x] && !_SpPutBuf[0][x]) //VDC0�������F�Ȃ�
						if (_BgPutBuf[1][x] || _SpPutBuf[1][x]) //VDC1�������F����Ȃ����
							_pScreenBuf[x] = _LineBufVDC2[x];
					x++;
				}
				break;
			case 0x7: //VDC1�̃X�v���C�g��VDC0��BG���O�ɏo��(VDC0�̃X�v���C�g���͌��)
			case 0x4:
				while (x < n)
				{
					if (_SpPutBuf[1][x] & 1) //VDC1�̃h�b�g���X�v���C�g(_SpPutBuf[1][x]==1 or 0x81�̂Ƃ��B2�̂Ƃ��͎�O��BG���\������Ă���)�Ȃ�
					{
						if (!(_SpPutBuf[0][x] & 1)) //VDC0�̃h�b�g���X�v���C�g����Ȃ���΁B���X�v���C�g��BG�̗��ɉB��Ă����ꍇ���A�����炭VDC1�̃X�v���C�g���D�悳���B
							_pScreenBuf[x] = _LineBufVDC2[x];
					}
					else if (_BgPutBuf[1][x]) //VDC1�̃h�b�g��BG�Ȃ�
					{
						if (!_BgPutBuf[0][x] && !_SpPutBuf[0][x]) //VDC0�������F�Ȃ�
							_pScreenBuf[x] = _LineBufVDC2[x];
					}
					x++;
				}
				break;
			case 0xB: //VDC0�̃X�v���C�g��VDC1��BG�ɉB���(VDC1�̃X�v���C�g���͑O)
			case 0x8:
				while (x < n)
				{
					if (_SpPutBuf[1][x] & 1) //VDC1�̃h�b�g���X�v���C�g(_SpPutBuf[1][x]==1 or 0x81�̂Ƃ��B2�̂Ƃ��͎�O��BG���\������Ă���)�Ȃ�
					{
						if (!_BgPutBuf[0][x] && !_SpPutBuf[0][x]) //VDC0�������F�Ȃ�
							_pScreenBuf[x] = _LineBufVDC2[x];
					}
					else if (_BgPutBuf[1][x]) //VDC1�̃h�b�g��BG�Ȃ�
					{
						if ((_SpPutBuf[0][x] & 1)|| //VDC0���X�v���C�g�Ȃ痠��BG���B��Ă��Ă�VDC1��BG���D�悳���H
							(!_BgPutBuf[0][x])) //��������VDC0��BG����Ȃ����
								_pScreenBuf[x] = _LineBufVDC2[x];
					}
					x++;
				}
				break;
		}
	}
}


/*-----------------------------------------------------------------------------
	[VDC_AdvanceClock]
		�w��̃N���b�N������ VDC �̏�����i�߂܂��B

	_ScanLine --- TV �̃X�L�������C��
	_DisplayCounter --- VDC ���̃��C���J�E���^
	_RasterCounter --- ���X�^��r�p�J�E���^
	_LineCounter --- ���C���J�E���^�Ƃ������� VDC �� VRAM �A�h���X
-----------------------------------------------------------------------------*/
//�����ݔ�g�p
void
VDC_AdvanceClock(
	Sint32	clock)
{
	_ClockCounter += clock;

	while (_ClockCounter >= VDC_CYCLESPERLINE)
	{
		_ClockCounter -= VDC_CYCLESPERLINE;
		VDC_AdvanceLine(NULL, 1);
	}
}


//Kitao�ǉ��BVRAM-VRAM�Ԃ�DMA�]�����̂Ƃ��̏����B�X�p�O���ȊO�̃\�t�g�p
static inline void
vramDmaCountCheck()
{
	if (_VramDmaCount[0] > 0)
		if (--_VramDmaCount[0] == 0) //�]���J�n��������������
			if (_Regs[0][VDC_DCR] & 0x2)
			{
				//���荞�ݗv���B�]���������ł͂Ȃ��A�����]���������I�����(�]�����n�܂���)�i�K�ł����ɗv������B
				_VdcStatus[0] |= VDC_STAT_DV;
				INTCTRL_Request(INTCTRL_IRQ1);
			}
}

//Kitao�ǉ��BVRAM-VRAM�Ԃ�DMA�]�����̂Ƃ��̏����B�X�p�O���p
static inline void
vramDmaCountCheckSG()
{
	if (_VramDmaCount[0] > 0)
		if (--_VramDmaCount[0] == 0) //�]���J�n��������������
			if (_Regs[0][VDC_DCR] & 0x2)
			{
				//���荞�ݗv���B�]���������ł͂Ȃ��A�����]���������I�����(�]�����n�܂���)�i�K�ł����ɗv������B
				_VdcStatus[0] |= VDC_STAT_DV;
				INTCTRL_Request(INTCTRL_IRQ1);
			}
	if (_VramDmaCount[1] > 0)
		if (--_VramDmaCount[1] == 0) //�]���J�n��������������
			if (_Regs[1][VDC_DCR] & 0x2)
			{
				//���荞�ݗv���B�]���������ł͂Ȃ��A�����]���������I�����(�]�����n�܂���)�i�K�ł����ɗv������B
				_VdcStatus[1] |= VDC_STAT_DV;
				INTCTRL_Request(INTCTRL_IRQ1);
			}
}

//Kitao�X�V�BCPU�₻�̑�I/O��i�߂鏈��
static void //������inline�ɂ����A�R���p�N�g�ɂ܂Ƃ߂��ق�������(�����̊�)
cpuAdvance(
	Sint32	clock)
{
	int		i;
	Sint32	drawFrame = _DrawFrame;

	if (APP_CheckRecordingNow())
		drawFrame = 1; //���R�[�h�L�^��or�Đ����̏ꍇ�A������N�����Ȃ����ߋȂ̃e���|�̒����͍s�킸�ʏ�Ɠ�������ɂ���Bv2.15
	switch (drawFrame)
	{
		case 1: //�ʏ�
			if (_SuperGrafx == 1)
			{	//�X�p�O��
				for (i=1; i<=clock; i++) //clock�̂Ԃ񂾂�CPU��i�߂�B
				{
					vramDmaCountCheckSG(); //Kiato�ǉ��B
					MOUSE_AdvanceClock();//Kitao�X�V�B���͋@���CPU�����̑O�ɂ����Ȃ��悤�ɂ����B�P�N���b�N���������ƃJ�[�\���̓��������炩�ɁB
					if (gCPU_ClockCount++ >= 0) CPU_ExecuteOperation(); //Kitao�X�V�BCPU�N���b�N���o�߂����ĉ\�Ȃ疽�߂����s����Bv2.00
																		//�P�N���b�N���i�߂�ƕ��񓮍�̐��x�������B�������オ��B
					CDROM_AdvanceClock();
					APU_AdvanceClock(); //Kitao�X�V�BCDDA�����Ȃǂ̂��߁ACDROM�������I����Ă���APU����
					TIMER_AdvanceClock(); //Kitao�ǉ��B�^�C�}�[��CPU�̓����Ɋ֌W�Ȃ������Ői�߂�悤�ɂ����B
					_CpuPastCount++;//Kitao�ǉ��Bv1.00�B�ǂ��܂�CPU��i�߂Ă��邩���킩��悤�ɁB
				}
			}
			else //�������̂��߁A�X�p�O���̂Ƃ��Ə����𕪂����B
			{	//�ʏ�
				for (i=1; i<=clock; i++) //clock�̂Ԃ񂾂�CPU��i�߂�B
				{
					vramDmaCountCheck(); //Kiato�ǉ��B
					MOUSE_AdvanceClock();//Kitao�X�V�B���͋@���CPU�����̑O�ɂ����Ȃ��悤�ɂ����B�P�N���b�N���������ƃJ�[�\���̓��������炩�ɁB
					if (gCPU_ClockCount++ >= 0) CPU_ExecuteOperation(); //Kitao�X�V�BCPU�N���b�N���o�߂����ĉ\�Ȃ疽�߂����s����Bv2.00
																		//�P�N���b�N���i�߂�ƕ��񓮍�̐��x�������B�������オ��B
					CDROM_AdvanceClock();
					APU_AdvanceClock(); //Kitao�X�V�BCDDA�����Ȃǂ̂��߁ACDROM�������I����Ă���APU����
					TIMER_AdvanceClock(); //Kitao�ǉ��B�^�C�}�[��CPU�̓����Ɋ֌W�Ȃ������Ői�߂�悤�ɂ����B
					_CpuPastCount++;//Kitao�ǉ��Bv1.00�B�ǂ��܂�CPU��i�߂Ă��邩���킩��悤�ɁB
				}
			}
			break;
		case 0: //���񂵂̃X�L�b�v�t���[���BBGM�̃e���|�����킹�邽�߂ɁAAPU�ƃ^�C�}�[�͐i�߂Ȃ��B
			if (_SuperGrafx == 1)
			{
				for (i=1; i<=clock; i++)
				{
					vramDmaCountCheckSG();
					MOUSE_AdvanceClock();
					if (gCPU_ClockCount++ >= 0) CPU_ExecuteOperation();
					CDROM_AdvanceClock();
					_CpuPastCount++;
				}
			}
			else //�������̂��߁A�X�p�O���̂Ƃ��Ə����𕪂����B
			{
				for (i=1; i<=clock; i++)
				{
					vramDmaCountCheck();
					MOUSE_AdvanceClock();
					if (gCPU_ClockCount++ >= 0) CPU_ExecuteOperation();
					CDROM_AdvanceClock();
					_CpuPastCount++;
				}
			}
			break;
		case 2: //�P�{�����̑���(�X���[�t���[��)�p�BBGM���X���[�ɂ����Ȃ����߂ɁAAPU�ƃ^�C�}�[��ʏ�̂Q�{�i�߂�B
			if (_SuperGrafx == 1)
			{
				for (i=1; i<=clock; i++) //clock�̂Ԃ񂾂�CPU��i�߂�B
				{
					vramDmaCountCheckSG();
					MOUSE_AdvanceClock();
					if (gCPU_ClockCount++ >= 0) CPU_ExecuteOperation();
					CDROM_AdvanceClock();
					APU_AdvanceClock();
					TIMER_AdvanceClock();
					APU_AdvanceClock();
					TIMER_AdvanceClock();
					_CpuPastCount++;
				}
			}
			else //�������̂��߁A�X�p�O���̂Ƃ��Ə����𕪂����B
			{
				for (i=1; i<=clock; i++) //clock�̂Ԃ񂾂�CPU��i�߂�B
				{
					vramDmaCountCheck();
					MOUSE_AdvanceClock();
					if (gCPU_ClockCount++ >= 0) CPU_ExecuteOperation();
					CDROM_AdvanceClock();
					APU_AdvanceClock();
					TIMER_AdvanceClock();
					APU_AdvanceClock();
					TIMER_AdvanceClock();
					_CpuPastCount++;
				}
			}
			break;
	}
}

/*-----------------------------------------------------------------------------
	[VDC_AdvanceLine]
		�P�X�L�������C�������� VDC �̏�����i�߂܂��B

	_ScanLine --- TV �̃X�L�������C��
	_DisplayCounter --- VDC ���̃��C���J�E���^
	_RasterCounter --- ���X�^��r�p�J�E���^
	_LineCounter --- ���C���J�E���^�Ƃ������� VDC �� VRAM �A�h���X
-----------------------------------------------------------------------------*/
//Kitao�X�V�B�ł��邾���V���v���Ȏ�����ڎw���Ă���Ă݂邱�Ƃɂ����B
//			 ���X�^���荞�ݕ����̗���������B�X�g�Q�f���ł��܂Ɉ�u��ʂ�����錻�ۂ����������B
//	_DisplayCounter��1����n�܂邽�ߐ�ɃC���N�������g���Ďg���B�����ȊO�ɂ�drawLine()�Ȃǂ�����Q�Ƃ����B
//	_RasterCounter��64����n�܂�B
//	_LineCounter��BYR����n�܂�BCPU�����X���b�h�ł��X�V�����B
//	_ScanLine��0����n�܂�B�����ł����g���Ȃ��B
void
VDC_AdvanceLine(
	Uint32*		pScreenBuf,
	Sint32		drawFrame)
{
	int		i;
	int		a;
	Uint16	srcInc;
	Uint16	dstInc;
	Sint32	rasterTimingCount;
	BOOL	bmwr0x40;

	_pScreenBuf = pScreenBuf;
	_DrawFrame = drawFrame;
	_CpuPastCount = 0;

	// ���W���C���N�������g
	_DisplayCounter++;

	for (_VN=0; _VN<=_SuperGrafx; _VN++) //�X�[�p�[�O���t�B�b�N�X���[�h�Ȃ�VDC�Q�Ԃ�𓮂���
	{
		//VRAM-SATB�Ԃ�DMA�]�����̏ꍇ�̏���
		if (_SpDmaCount[_VN] > 0)
		{
			if (--_SpDmaCount[_VN] == 1) //Kitao�X�V�BVBlank�J�n�����R���C����o�߁BSATB�̓]���������B
			{
			//�����̊��荞�ݗv��
				if (DCR & 0x1) //DCR �� D1 ���Z�b�g����Ă���Ƃ��͊������荞�݂�v������
				{
					_VdcStatus[_VN] |= VDC_STAT_DS; //Kitao�ǋL�B(DCR & 0x1)���^�̂Ƃ������X�e�[�^�X���Z�b�g����B"�h���b�v���b�N�ق�z��"�ŕK�v�B
					INTCTRL_Request(INTCTRL_IRQ1);
				}
			}
			/* //DMA�]���Ȃ̂Ńm���E�F�C�g�Ƃ����Bv1.30
			else if (_SpDmaCount[_VN] == 0)
			{
				if (_VN == 0) //�X�p�O���̏ꍇ�A��d�ɃE�F�C�g���Ă��܂�Ȃ��悤��VDC0�̂Ƃ��̂݃E�F�C�g�Ƃ���B
				{
					//Kitao�X�V�BSATB�]���ŏ����CPU�N���b�N�������BDMA�]���Ȃ̂łقƂ�Ǐ���Ȃ��Ɖ���B
					gCPU_ClockCount -= 17; //���������Ԃ�17(�S���̐���)�B
										   //�E�F�C�g���傫������ƁAZIPANG�X�^�[�g���ɂ�◐��(40��NG)�B�v���C�x�[�g�A�C�h����OP�łP�t���[�����ꁕ�Q���W�ʐM�������܂̃f��������Ȃ��B
					if (_WaitPatch != 0) //�W�������łǂ����Ă����܂������Ȃ��\�t�g�p�B���ݔ�g�p�B
						gCPU_ClockCount -= _WaitPatch; //CPU Clock Wait
				}
			}
			*/
		}

	 	if (_DisplayCounter == DISPLAY_STARTLINE) //Kitao�X�V�B�\���J�n���C���s�b�^���ɗ����Ƃ�
	 	{
			_LineCounter[_VN] = BYR;
			_RasterCounter[_VN] = 64;
			_prevCR[_VN] = CR; //v1.21�ǉ��B���C���{�[�A�C�����h�ŕK�v
			
			//v1.63�ǉ��B���Ԓ���VBlank���荞�݂�CPU�����󂯎��Ȃ������ꍇ�A�`�撆��VBlank���荞�݃X�e�[�^�X���N���A�����̃t���[���`���ɒx������VBlank���N�����悤�ɂ����B
			//			 �V�g�̎��Q�̃r�W���A���V�[��������ɁBDE�EJA�ŕ`�撆��ʂ������̂��y���B�ǂݍ��݂̃^�C�~���O�̖��ō���ʃt���[�Y���₷���\�t�g�������炭���肷��͂��B���@�������d�g�݂̓������͖��m�F�ł��B
			if (_VdcStatus[_VN] & VDC_STAT_VD)
				if (VDW < 224) //VDW���������Ƃ��̂݁i�V�g�̉S�Q�cVDW=128�j�B���̏������Ȃ��ƃt�@�C�i�����b�v�c�C���ŗ���C���f�B�\�[�h�̉�ʂ̗��������@�ƈقȂ�C�R�Y�~�b�N�t�@���^�W�[�S�������Ȃ��CIQ�p�j�b�N�̏h�����Ńt���[�Y�C�t�@�[�W�A�X�̎׍c��̃X�^�[�g�f���ŗ���C�_�u���h���S���Q��OP�f���ŗ���C�`�F�C�XHQ�Ń��Z�b�g��ăX�^�[�g�Ńt���[�Y�C���@���X�P�Ńt���[�Y�Bv2.70
				{
					_VdcStatus[_VN] &= ~VDC_STAT_VD;
					_bVDCleared[_VN] = TRUE;
				}
			
			//Kitao�ǉ��B���̎��_�ł�VBlankLine��ۊǁB���̎��_�ł̒l�𗘗p����B���Ղ̌��ŉ�ʗ���������Bv1.19
			_VblankLineTop[_VN] = _VblankLine[_VN];
			//CR,DCR���W�X�^�̏󋵂ɂ���āAVBlank���C���𒲐�����Bv1.67�X�V
			if	((_DCC & 4)&& //DCC��0�̂Ƃ��͒������Ȃ��B�l�N���X�̗v�ǂ�OP�f���Ńi�C�g�̍U�����ɂP�t���[������Ȃ����߂ɕK�v�B�A�}�]���̍U�����ɗ����͎̂��@�����l�Bv1.64
				 ((CR & 0x100) == 0)) //�\���o�͑I���̉��ʃr�b�g�������Ă����ꍇ�͏������Ȃ��B���̏������Ȃ��ƃ��C���{�[�A�C�����h��Hurry!!���ɗ���C�X�v���b�V�����C�N�ŗ���B
			{
				if (_ScreenH[_VN] >= 240) //240�����̂Ƃ���������ƁA�h���L����X�ŏI��,�v�����X�I�u�y���V���ŗ���B�}�W�J���`�F�C�X�̃^�C�g����ʃf�������[�v���鎞�ɉ��v�`�m�C�Y���o��B�t���b�V���n�C�_�[�X,�J�[�h�G���W�F���X�ōŉ��ӗ���Bv1.67
				{
					switch (MWR & 0x70) //�}�b�v�T�C�Y���Ƃɕ����Ȃ��ƃ_�u���h���S���Q(MWR=0x70)�ŗ���B
					{
						//�c��64�L�����}�b�v�̏ꍇ(��128����)
						case 0x50: //�}�b�v�T�C�Y��64x64�̏ꍇ�B���̃P�[�X����ԑ����̂ō������̂��ߐ�ɋL�q
						case 0x40: //�}�b�v�T�C�Y��32x64�̏ꍇ�B
							//BG�ƃX�v���C�g�̕\����ɂ���āA�x�߂����߂�VBlank���N�����B
							if ((CR & 0xC0) != 0xC0) //BG���X�v���C�g�ǂ��炩��\���̏ꍇ
							{
								if (MWR & 0x10) //MWR=0x50�̎��BMWR=0x50�̎���2�ȏ�����ƁA�Q���W�ʐM�������܁C���^���G���W�F���CF1�T�[�J�X'92��NG�Bv2.61�X�V
								{
									if (VCR < 4) //VCR�����������B����l�`�����iOP�f��(VCR=0xF6)�ň����Ă��܂��ƃX���[�B�Q���W�ʐM��������OP�f��(VCR=4)�ň����ƍ���Ȃ��Bv2.63�X�V
										_VblankLineTop[_VN]--; //-1�ȏ�Ń��[�V���O��(BG��\��)�ŉ�ʗh�ꂪ�����Bv2.41�X�V
								}
								else //MWR=0x40�̎�
									_VblankLineTop[_VN]--; //-1�ŃT�[�N�P�Q(MWR=0x40,VCR=3)�ŃX�e�[�^�X�\�����̏㕔���ꂪ���@�Ɠ����ɁB-1�Ő��_�`���̃X�e�[�^�X�\��(MWR=0x240,VCR=0xF6)�̗��ꂪ�����Bv2.63
							}
							if (DCR & 0x10) //VRAM->SATB�֎����]���������s���ꍇ�A�x�߂�VBlank���N�����Bv2.52
								if (VCR >= 4) //VCR���W���ȏ�B
									if (MWR & 0x10) //MWR=0x50���̂݁Bv2.60�ǉ��BMWR=0x40�̂Ƃ��ɒx�点��ƁA���^���G���W�F���Q�̂n�o�f�����\������Ȃ��B
										if ((CR & 0x02) == 0) //�X�v���C�g�̕\���ُ튄�荞�݂��s��Ȃ��Ƃ��̂݁B�T�[�J�X���C�h�ŖI���j�𗎂Ƃ����Ƃ��Ɏ��X�N���鉹�̗��ꂪ�����i�y���j�Bv2.64�ǉ�
											_VblankLineTop[_VN]++; //+1�ŃQ���W�ʐM��������OP�f��OK(MWR=0x50)�B���^���G���W�F���̃^�C�g����ʗ������(MWR=0x50)�BF1�T�[�J�X'92�Ō����S�[���㗐�����(MWR=0x50)�B�J�_�b�V���ŗ������(MWR=0x50)�B���[���h�R�[�g�ŉ��̈���Bv2.58
								break;
						//�c��32�L�����}�b�v�̏ꍇ(��128����)
						case 0x10: //�}�b�v�T�C�Y��64x32�̏ꍇ�B
						case 0x00: //�}�b�v�T�C�Y��32x32�̏ꍇ�B
							if (DCR & 0x01) //VRAM->SATB�ւ̓]���I����̊��荞�ݏ������s���ꍇ�A�x�߂�VBlank���N�����B
								_VblankLineTop[_VN]++; //+1�Ń\���W���[�u���C�h�R�ʂł̗��ꂪ�����B�傫�������������"�N�C�Y�a�l�̖�]"�ŉ�ʗh��Bv2.04,v2.36
							if (DCR & 0x10) //VRAM->SATB�֎����]���������s���ꍇ�A���߂�VBlank���N�����Bv2.49
								if (VCR >= 4) //VCR���W���ȏ�̏ꍇ�B���ꂪ�Ȃ��ƃN���X���C�o�[��OP�f�����[�v(MWR=0x10)�Ń^�C�~���O���킸�B
									_VblankLineTop[_VN]--; //-1�B-1�ł�����120%(MWR=0x10)�̎����O�f���̂P�t���[�����ꂪ�����B-2�ȏ�����ƃt�@�[�W�A�X�̎׍c��퓬�V�[��(MWR=0x10,VCR=0xF6)�ŗ���Bv2.50
							break;
					}
				}
				else if (_ScreenH[_VN] >= 224) //224�����̂Ƃ���������ƕ��̓`���U�i�h�D�Q��OP�ŉ��ӗ���Bv2.43
				{
					switch (MWR & 0x70) //�}�b�v�T�C�Y���Ƃɕ����Ȃ��ƃ_�u���h���S���Q(MWR=0x70)�ŗ���B
					{
						//�c��64�L�����}�b�v�̏ꍇ(��128����)
						case 0x50: //�}�b�v�T�C�Y��64x64�̏ꍇ�B
						case 0x40: //�}�b�v�T�C�Y��32x64�̏ꍇ�B
							//BG�ƃX�v���C�g�̕\����ɂ���đ��߂�VBlank���N�����B
							if ((CR & 0xC0) == 0x80) //BG�����\�����A�X�v���C�g�͕\�����Ȃ��ꍇ�A���߂�VBlank���N�����BBG��\�����ɂ������Ă��܂��ƁA�h���L����X�̍ŏI�ʊK�i��艺��ŗ���Bv2.41�X�V
								_VblankLineTop[_VN] -= 3; //-3�Ő��T����R(MWR=0x50)�̗��ꂪ�����B-2�ȏ�Ńt���b�V���n�C�_�[�X(MWR=0x50)�őΐ팈����P�t���[���u���b�N�A�E�g������(�������������Ă��I�[�o�[���C������)�Bv2.41�X�V
														  //-2�ȏ�Ō��R�q�̖���ʖ�(MWR=0x50)�̃J�[���[�X�̎��Ȃ�(MWR=0x50,ScreenH=224)�łP���C��������������B
							break;
					}
				}
			}
			if ((_VblankLineTop[_VN] < 1)||(_VblankLineTop[_VN] > 263))
				_VblankLineTop[_VN] = 263;
			//Kitao�e�X�g�p
			//PRINTF("VBtest=%X, %d, %d, %d  [ %X , %X , %X , %X, %X , %X ] VBlineTop=%d",_DCC,_TvStartLine[_VN],DISPLAY_STARTLINE,_ScreenH[_VN], VPR,VDW,VCR,MWR,DCR,CR, _VblankLineTop[_VN]);
		}
		else
		{
			_LineCounter[_VN]++;
			_RasterCounter[_VN]++;
		}
		_LineCounter[_VN] &= _LineCountMask[_VN];
		
		//�O��̃��X�^���荞�݂���������Ă��Ȃ������ꍇ�A�����ōĂя����𑣂��B�e�P�T�[�J�X'92�̌�����̏��ʔ��\�ŉ�ʂ𗐂��Ȃ����߂ɕK�v�Bv2.39
		if (_VdcStatus[_VN] & VDC_STAT_RR)
			INTCTRL_Request(INTCTRL_IRQ1);

		//���X�^��r���s�Ȃ�
		if ((_RasterCounter[_VN] == RCR)&&(_RasterCounter[_VN] >= 64))
		{
			if (CR & VDC_CTRL_RC)
			{
				_VdcStatus[_VN] |= VDC_STAT_RR; //Kitao�ǋL�B���荞�݃I���̂Ƃ��̂݃X�e�[�^�X�̓Z�b�g�B�O���f�B�E�X�Ŋm�F�B
				INTCTRL_Request(INTCTRL_IRQ1);
			}
			_bRasterRequested[_VN] = TRUE;
		}
		else
			_bRasterRequested[_VN] = FALSE;
	}

	//Kitao�ǉ��B���X�^��r�����CPU�𓮂����悤�ɂ����B�������邱�ƂŎ��@�ɋ߂����X�^���荞�݂̎󂯎�肪�o����B
	_bRasterLate = FALSE;
	rasterTimingCount = _RasterTimingCount;
	if (_RasterTimingType == 2) //RasterTiming�ݒ肪Normal(88)�̏ꍇ
	{	//v1.41�ǉ��B�����ݏ����Ȃǂ��s�����ǂ����ɂ���āA���X�^���荞�݂���������^�C�~���O���ς��B
		//�^�C�~���O�̒l�͐���l�B���̗v��������ŗ���̂Ŋm���ȏ��͕s���Ȃ̂ŃG�~�����[�^�Ƃ��Ă̓\�t�g�̓��삪�S�������ɂȂ�Ό���͂悵�Ƃ���Bv1.61
		if ((_DCC & 4) == 0) //���̂Ƃ��͓���
		{
			if (_Regs[0][VDC_MWR] > 0xFF) //����
				rasterTimingCount = 76; //76�B�p�`�v�N�\�ԏ�����76�ȉ����K�v�B�X�g���C�_�[��OK�B
			else if ((_Regs[0][VDC_MWR] & 0x60) == 0x00) //32x32��64x32�L������BG�}�b�v�T�C�Y�̏ꍇ
			{
				if (_Regs[0][VDC_VCR] >= 4) //VCR���W��(4)�ȏ�̏ꍇ
					rasterTimingCount = 86; //86�B�X�y�[�X�n���A�[��86�ȉ��K�v(�傫���ƃ|�[�Y����ӂ����)�B�T�C�o�[�N���X�ő傫�߂̒l���K�v�B
				else //VCR�̒l���������ꍇ�Bv1.61
					rasterTimingCount = 69; //69�B�M�����Z�h�b�`�{�[���ŏ����߂̒l���K�v(���������Ă��ʖځB���@�ł���◐�ꂠ��)�B
			}
			else //BG�}�b�v�T�C�Y���傫���ꍇ
			{
				if (_TvWidth == 256) //��256���[�h(5MHz)�̂Ƃ�
					rasterTimingCount = 88; //88�B�����X�^�[�v�����X��83�ȏオ�K�v�B�}�j�A�b�N�v�����X�ő傫�Ȓl��NG�B
				else //��336���[�h(7MHz)�ȏ�̂Ƃ�
					rasterTimingCount = 70; //70�B�X���C�����[���h��70�ȉ����K�v�B
			}
		}
		else if (_Regs[0][VDC_VDW] & 0x100) //����
			rasterTimingCount = 84; //84�B�p�Y���{�[�C�̃R�[�X�N���A����84�ȉ����K�v�B
		else if (_Regs[0][VDC_VPR] & 0x01) //����B�X�g���C�_�[��(90NG)�����ꂾ��(_DCC==0)��D�悳����Bv2.17
			rasterTimingCount = 106; //106�B�~�Y�o�N��`���̂R�ʃ{�X(�m�R�M�����D�Ԃ݂����Ȃ��)��106���œK�B
		else if (_Regs[0][VDC_DCR] & 0x01) //VRAM->SATB�Ԃ̓]���I�����̊��荞�݂��s��(DCR&0x1)�ꍇ�A����Ƃ���B
		{
			if ((_Regs[0][VDC_MWR] & 0x60) == 0x00) //32x32��64x32�L������BG�}�b�v�T�C�Y�̏ꍇ
			{
				if (_Regs[0][VDC_VCR] & 0x80) //VCR�̒l���傫���ꍇ
					rasterTimingCount = 200; //200�B��(���˂���)�̒ʔ̉�ʂŗh��Ȃ����߂ɑ傫�Ȓl���K�v(190NG)�B
				else
					rasterTimingCount = 90; //90�B�\���W���[�u���C�h(�R��)��90�ȉ����K�v(�傫������Ƌ��̏�ӂ������)�B�X�[�p�[�����Y�d�S�Q�̃^�C�g����ʂ�89�ȏオ�K�v�B
			}
			else //BG�}�b�v�T�C�Y���傫���ꍇ
				rasterTimingCount = 58; //58�B�X�[�p�[�o���[�{�[��(VCR=4,MWR=0x30)��58�ȉ����K�v�B�q�b�g�E�W�E�A�C�X(MWR=0x50)��64�ȉ����炢���K�v�B
		}
		else if (_Regs[0][VDC_DCR] & 0x02) //VRAM->VRAM�Ԃ̓]���I�����̊��荞�݂��s��(DCR&0x2)�ꍇ�A����Ƃ���B
			rasterTimingCount = 20; //20�B�}�W�J���`�F�C�X(MWR=0x50)�̂��X�ŏ����߂̒l���K�v�B
		else if ((_Regs[0][VDC_CR] & 0x42) == 0x42) //�X�v���C�g�ُ�̊����݂�����ꍇ�B�X�v���C�g��\����(0x40��0�B���Z�M)�͏���
			rasterTimingCount = 90; //90�B�X�^�[�p���W���[�̃^�C�g����ʂ�90�ȏオ�K�v�B�`�F�C�XH.Q.��91�ȉ����K�v�B�Ō�̔E���B
		else if (_TvWidth == 256) //��256���[�h(5MHz)�̂Ƃ�
		{
			if (_Regs[0][VDC_DCR] == 0x00) //VRAM�]���֘A�̊����ݏ����Ȃǂ��s��Ȃ��Ȃ�B
			{	//�����ݔ��������`�揈���̂ق��������I���\���������Ȃ�B
				if ((_Regs[0][VDC_MWR] & 0x60) == 0x60) //�����炭�}�b�v�T�C�Y���ƂɃ^�C�~���O���قȂ�
				{	//BG�}�b�v�T�C�Y��128x64�̏ꍇ(MWR=0x60,0x70)
					rasterTimingCount = 85; //85�B�p���[�Q�C�g��85�ȉ����K�v�B
				}
				else if (_Regs[0][VDC_MWR] & 0x40) //�����炭�}�b�v�T�C�Y���ƂɃ^�C�~���O���قȂ�
				{	//BG�}�b�v�T�C�Y��32x64,64x64�̏ꍇ(MWR=0x40,0x50)
					if (_Regs[0][VDC_VCR] >= 4) //VCR���W��(4)�ȏ�̏ꍇ
					{
						if ((_Regs[0][VDC_VCR] & 0x80) == 0) //VCR�̒l���傫���Ȃ��ꍇ
							rasterTimingCount = 88; //88�B21�G������86�ȏオ�K�v�B�_���W�����G�N�X�v���[���[OK(�傫�߂̂ق���������ۂ�)�B
						else
							rasterTimingCount = 72; //72�B�����_�L���[�u�퓬��72�ȉ����K�v�B���[���h�q�[���[�Y�Q(�΂̂��ʂ̑���)��72�ӂ肪�œK�B�X�v���K��mk2��8�ʊJ�n�O�f����78�ȉ����K�v�B���Ղ̌�(��256��)OK�B
					}
					else //VCR�̒l���������ꍇ�Bv2.17�X�V
						rasterTimingCount = 70; //70�B�W���b�L�[�`�F��(���ɂP�ʌ㔼)��70�ȉ��K�v�B
				}
				else if (_Regs[0][VDC_MWR] & 0x30) //�����炭�}�b�v�T�C�Y���ƂɃ^�C�~���O���قȂ�
				{	//BG�}�b�v�T�C�Y��64x32,128x32�̏ꍇ(MWR=0x10,0x20,0x30)
					if (_Regs[0][VDC_VCR] >= 4) //VCR���W��(4)�ȏ�̏ꍇ
					{
						if ((_Regs[0][VDC_VCR] & 0x80) == 0) //VCR�̒l���傫���Ȃ��ꍇ
							rasterTimingCount = 61; //61�B�V�O����ZIRIA��OP�f����61�ȉ����K�v�B�X�g�Q�f�ŏ����Ȓl���K�v(�傫���Ă�NG)�B�t�@�C�i���\���W���[��70�ȉ����K�v�B�A�h�x���`���[�A�C�����hOK�B
						else //VCR�̒l������ȏꍇ�BCD�Q�[���ɑ����A���X�^�̃^�C�~���O���Ⴄ�悤���B
							rasterTimingCount = 38; //38�B�V�O�����Q�̐퓬�V�[���Ŕw�i���h��Ȃ����߂�38�ȉ����炢���K�v(���������Ă��ʖ�)�Bv2.62
					}
					else //VCR�̒l���������ꍇ�Bv2.31�ǉ�
						rasterTimingCount = 144; //144�B���r�I���v�X�X�y�V����(VCR=3)��144�ȏオ�œK(�X�e�[�^�X�\���̉��Ɋ��S�ɓG��������)�B���[�h�����i�[(�p�b�N�C���r�f�I��)�ő傫������Ɨǂ��Ȃ��B
				}
				else
				{	//BG�}�b�v�T�C�Y��32x32�̏ꍇ(MWR=0x00)
					rasterTimingCount = 80; //80�B�^���_�]���p�����[�^�U�蕪����80�ӂ肪�œK(�傫�����Ă����������Ă��ʖ�)�B
				}
			}
			else
			{	//VRAM�]���֘A�̊����ݏ����Ȃǂ��s���Ƃ�
				switch (_Regs[0][VDC_MWR] & 0x70) //�����炭�}�b�v�T�C�Y���ƂɃ^�C�~���O���قȂ�
				{
					case 0x50: //64x64�L������BG�}�b�v�T�C�Y�B���CD�Q�[���ł��̃P�[�X����ԑ����̂ō������̂��ߐ�ɋL�q
						if (_Regs[0][VDC_VCR] & 0x80) //VCR�̒l���傫���ꍇ
							rasterTimingCount = 86; //86�B//����1/2�Ƃ���̉ԉł�86�ȉ����K�v�B
						else
						{
							if (_Regs[0][VDC_CR] & 0x40) //�X�v���C�g�\����
								rasterTimingCount = 88; //88�B�[�������`�����v��88�ȏオ�K�v(�H�ɗh��邪���@�����l)�B�e�P�T�[�J�X�̃X�^�[�e�B���O�O���b�h��88�ȉ��K�v�B�_���W�����G�N�X�v���[���[��83�ȏオ�K�v�B
							else //�X�v���C�g��\�����͑��߂ɔ�����s��
								rasterTimingCount = 87; //87�B�G�^�[�i���V�e�B87�ȉ����K�v�B�T���_�[�u���[�h��88�ȉ����K�v�B�_���W�����G�N�X�v���[���[��83�ȏオ�K�v�B�T�C�h�A�[��SP�̃A�����W�Q�[��OK�Bv2.62
						}
						break;
					case 0x10: //64x32�L������BG�}�b�v�T�C�Y�B���̃P�[�X�������B
						if (_Regs[0][VDC_VCR] & 0x80) //VCR�̒l���傫���ꍇ
							rasterTimingCount = 78; //78�B�_�E���^�E���M������̃Q�[�����[�h�I�����(RUN����������̉���)��78�ȉ��K�v�B
						else
						{
							if (_Regs[0][VDC_VCR] < 4) //VCR�̒l���������ꍇ�Bv2.75�X�V
								rasterTimingCount = 88; //88�BTHE���v�̃v���C�f���i�X�^�[�g��ʕ��u�B3�ʁj�̉�ʏ㕔���N�����S��������Ȃ����߂�88��89���K�v�B
														//    �N���X���C�o�[88OK(89NG�B�傫���ƃQ�[���I�[�o�[����ʗh��)�B�p�b�N�����h��81�ȏオ�K�v�B
							else
								rasterTimingCount = 85; //85�B�h���h�R�h���̖ʃN���A�X�N���[������85�ȏ�K�v(84�ȉ����Ɨ���Ȃ����@�Ƒ���)�B�p���[�X�|�[�c��NEWS��85�ȉ����K�v�BZIPANG�^�C�g����ʂ�84�ȏオ�K�v�B�V���r�r���}���Q�ŏ����߂̒l���K�v�B
														//    �T�C�����g�f�o�b�K�[�Y�ŏ����߂̒l�������B�X�v���b�^�[�n�E�XNG(�傫���ƃX�e�[�W�T����(��̏o�Ă���Ƃ���)�ō����킸���ɗ����B���@�ł�������������Ȃ��B���Ԃ̂���Ƃ��Ɋm�F)�Bv2.66�X�V
						}
						break;
					case 0x00: //32x32�L������BG�}�b�v�T�C�Y�B
						rasterTimingCount = 65; //65�B�_�E���^�E���M���s�i�ȑ�^�����65�ȉ����œK�B�I�y���[�V�����E���t�̃X�^�[�g�f��(�p���V���[�g����&�t�F�[�h�A�E�g��)��66�ȉ����K�v�B����΂�S���t�{�[�C�Y�̃^�C�g����ʂ�65�ӂ肪�œK�i����������ƒ����̉_������B�������Ă��傫���Ă������)�B
						break;
					case 0x20: //128x32�L������BG�}�b�v�T�C�Y�B
					case 0x30: //128x32�L������BG�}�b�v�T�C�Y�B
						if (_Regs[0][VDC_VCR] & 0x80) //VCR�̒l���傫���ꍇ
							rasterTimingCount = 58; //58�B���镨��̐퓬�V�[����58���œK�B��͕w�x�`���T�t�@�C�AOK�B
						else
							rasterTimingCount = 83; //83�B�����_�[������83�ȉ����K�v(�������Ă��ʖ�)�B���т܂邱�����OK(�傫�߂̒l�K�v)�B�t�@�C�i�����b�v�c�C��OK�B
						break;
					case 0x60: //128x64�L������BG�}�b�v�T�C�Y�B
					case 0x70: //128x64�L������BG�}�b�v�T�C�Y�B
						rasterTimingCount = 70; //70�B�e�P�p�C���b�g(VCR=3)��70�ӂ肪�K�v(�^�C���̏オ����Ȃ��ӂ肪�œK�B���@�ł����Ȃ胉�X�^�������)�B���ċR���J�C�U�[�h��81�ȉ����K�v�B�M�����Z�T�b�J�[��OK�B
						break;
					case 0x40: //32x64�L������BG�}�b�v�T�C�Y�B
						if ((_Regs[0][VDC_VCR] < 4)&&(_VblankLineTop[0] >= 262)) //VCR�̒l���������ꍇ��VBlankLineTop��262�ȏ�̏ꍇ(���ꂪ�Ȃ��ƃT�[�N�P�Q�ŗ���)�B
							rasterTimingCount = 108; //108�B�h���S���Z�C�o�[�̃Q�[���I�[�o�[����108�ȉ��K�v,�R�ʂ�112�ȏオ���z�Bv2.58
						else
							rasterTimingCount = 28; //28�B���^���G���W�F����28�ȉ��K�v(���������Ă��ʖ�)�B�A�t�^�[�o�[�i�[�Q��56�ȉ��K�v�B�T�[�N�P�Q�ŏ����߂̒l���K�v�B
						break;
				}
			}
		}
		else if (_TvWidth == 336) //��336���[�h(7MHz)�̂Ƃ�
		{	//�����ݔ������`�揈���̑O�ɋN����\���������Ȃ�B
			if (_Regs[0][VDC_DCR] == 0x00) //VRAM�]���֘A�̊����ݏ����Ȃǂ��s��Ȃ��Ȃ�A�ʏ�����A��ɕ`�悪�I���\���������Ȃ�B
			{
				if (_Regs[0][VDC_MWR] & 0x40) //�c64�L������BG�}�b�v�T�C�Y�̏ꍇ
				{
					if (_Regs[0][VDC_VCR] >= 240)
						rasterTimingCount = 87; //87�B���Ղ̌�(��336��)��87�ȉ����K�v�B
					else
						rasterTimingCount = 110; //110�B�v�����X�I�u�y���V����LV8��ʔ��]�̂Ƃ���110�ȏ�(109���Ɖ�ʐؑւ�莞�ɋH�ɗ���)���K�v�B�h���S���X���C���[�p�Y�`����132�ȉ����K�v�B
				}
				else //�c32�L������BG�}�b�v�T�C�Y�̏ꍇ
					rasterTimingCount = 82; //82�BR-TYPE1(VCR=3,MWR=0x10)��82�ȉ����K�v�B�喂�E���R�ʂő傫�Ȓl�͑ʖ�82OK�B
			}
			else
			{	//VRAM�]���֘A�̊����ݏ����Ȃǂ��s���Ƃ�
				if (_Regs[0][VDC_MWR] & 0x40) //�c64�L������BG�}�b�v�T�C�Y�̏ꍇ
				{
					if (_Regs[0][VDC_VCR] & 0x80) //VCR���傫���ꍇ
					{
						if (_Regs[0][VDC_VCR] > 224)
							rasterTimingCount = 88; //88�B�Ղ�Ղ�b�c�^�C�g����ʂ�104�ȉ����K�v�B
						else //VCR���傫����224�ȉ��̏ꍇ
							rasterTimingCount = 134; //134�B�a(�}�b�v��ʂ�II�{�^���A��)��134�ȏオ�K�v�B
					}
					else
						rasterTimingCount = 88; //88�B�T�C�h�A�[��(Hu)���T�C�h�A�[��SP�̃A�[�P�[�h���[�h��86�ȏオ�K�v�B�z���[�X�g�[���[�ő傫���ƑʖځBv2.19
				}
				else //�c32�L������BG�}�b�v�T�C�Y�̏ꍇ
				{
					if (_Regs[0][VDC_VCR] & 0x80) //VCR���傫���ꍇ
						rasterTimingCount = 130; //130�B�Ղ�Ղ�b�c�n�C�X�R�A���(VCR=0xEE,MWR=0x2A)��130�ȏオ�K�v(�o�b�N�A�b�vRAM�̃E�F�C�g�Ƃ����ނ̂Œ���)�BBURAI��111�ȏオ�K�v�B
					else
						rasterTimingCount = 88; //88�B���u�����N��106�ȉ����K�v�B
				}
			}
		}
		else if (_TvWidth == 512) //��512���[�h�ȏ�(10MHz)�̂Ƃ�
		{	//�����ݔ������`�揈���̑O�ɋN����\���������Ȃ�B
			if (_Regs[0][VDC_MWR] & 0x40) //�c64�L������BG�}�b�v�T�C�Y�̏ꍇ
				rasterTimingCount = 132; //132�B�Ƃ肠����5MHz�ʏ��1.5�{
			else //�c32�L������BG�}�b�v�T�C�Y�̏ꍇ
				rasterTimingCount = 88; //88�B������120%(�Z�ɉ��)��95�ȉ����炢���K�v�Bv2.41
		}
	}
	if (_OverClockType >= 100) //�^�[�{�T�C�N�����[�h�̏ꍇ
		if ((_RasterTimingType != 1)&&(_RasterTimingType != 4)&&(_RasterTimingType != 14)) //EARLY�ȊO�Ȃ�
		{
			if (_OverClockType == 100)
				rasterTimingCount = (rasterTimingCount +1) /2; //+2�͎l�̌ܓ��̂��߁B
			else //200,300
				rasterTimingCount = (rasterTimingCount +2) /5; //+2�͎l�̌ܓ��̂��߁B�ۂ��Ղ郁�C����/5���K�v(/4����OP�f���ŏ�ӂ��H�ɗ���)�B
		}
	//Kitao�e�X�g�p
	//_VN=0; PRINTF("RTtest=%d (%d) %X, %d, %d, %d  [ %X , %X , %X , %X , %X , %X ] %X %d VB=%d",rasterTimingCount,_TvWidth,_DCC,_TvStartLine[_VN],DISPLAY_STARTLINE,_ScreenH[_VN], VPR,VDW,VCR,MWR,DCR,CR, _VdcStatus[_VN], _MaxSpPerLine[_VN], _VblankLineTop[_VN]);
	//PRINTF("Kekka=%x, %x, %x, %x, %x, %x, %x, %x", _Regs[0][0],_Regs[0][1],_Regs[0][2],_Regs[0][3],_Regs[0][4],_Regs[0][5],_Regs[0][6],_Regs[0][7]);
	//PRINTF("Kekka=%x, %x, %x, %x, %x, %x, %x, %x", _Regs[0][8],_Regs[0][9],_Regs[0][10],_Regs[0][11],_Regs[0][12],_Regs[0][13],_Regs[0][14],_Regs[0][15]);
	//PRINTF("Kekka=%x, %x, %x, %x, %x, %x, %x, %x", _Regs[0][16],_Regs[0][17],_Regs[0][18],_Regs[0][19],_Regs[0][20],_Regs[0][21],_Regs[0][22],_Regs[0][23]);
	//PRINTF("Kekka=%x, %x, %x, %x, %x, %x, %x, %x", _Regs[0][24],_Regs[0][25],_Regs[0][26],_Regs[0][27],_Regs[0][28],_Regs[0][29],_Regs[0][30],_Regs[0][31]);

	cpuAdvance(rasterTimingCount); //rasterTimingCount�̃p���[�Ԃ񂾂�CPU��i�߂�B���X�^���荞�݌�A�����ɏ����������s���Q�[���̏ꍇ�A������_LineCounter����������������B

	//Kitao�ǋL�B�܂��ArasterTimingCount�̃p���[�Ԃ񂾂�CPU��i�߂��B
	//			 ���݂̃��C���������ɏ������������Q�[���̏ꍇ�́A���̎��_��CPU�ɂ����_LineCounter���������������Ă���B

	if (_ScanLine == 0) //�X�L�������C�����擪
	{
		//_VN=0; PRINTF("WaitTest=%d (%d) %X, %d, %d, %d  [ %X , %X , %X , %X, %X , %X ] %X VB=%d",rasterTimingCount,_TvWidth,_DCC,_TvStartLine[_VN],DISPLAY_STARTLINE,_ScreenH[_VN], VPR,VDW,VCR,MWR,DCR,CR, _VdcStatus[_VN], _VblankLineTop[_VN]);
		for (_VN=0; _VN<=_SuperGrafx; _VN++) //�X�[�p�[�O���t�B�b�N�X���[�h�Ȃ�VDC�Q�Ԃ�𓮂���
		{
			//�X�L�������C���擪����VSW��ۊǂ��Ă����Bv2.09�ǉ�
			_PrevVSW[_VN] = VSW;
			
			//�o�[�X�g���[�h����BKitao�X�V�B�X�L�������C����0���C���̂Ƃ��ɔ��肷��悤�ɂ����B���̃��C���Ŕ�\����ԂȂ�c��̃��C�������ׂĔ�\��(�X�v���C�g�����J���[�Ŗ��܂�)�B����l�`�����i�Q�A�T�C�o�[�N���X�B
			//								 ���X�^���荞�ݔ��肪�I��������ƂɁA�o�[�X�g���[�h��������邱�ƂŁA���C���{�[�A�C�����h��HurryUp�ł̉�ʗ�������肵�ĉ����Bv1.19
			_bBurstMode[_VN] = ((CR & 0xC0) == 0);

			//����̐ݒ莞�ɁAVDC�A�N�Z�X���̃E�F�C�g���J�b�g�B(���@�ł����l���͖��m�F)�B�������̂��߂����Ŕ��肵�Ă����Bv2.17,v2.31,v2.38,v2.41�X�V
			if ((MWR & 0x20)|| //BG�}�b�v�̉��T�C�Y��128�̂Ƃ��̓E�F�C�g���J�b�g�B�����_�[����(MWR=0x30)�ŕK�v�B
			    (MWR & 0x80)|| //CG���[�h��1�̂Ƃ��̓E�F�C�g���J�b�g�B�t�@�[�W�A�X�̎׍c���OP�f��(MWR=0x90)�Ńm�[�E�F�C�g���K�v�Bv2.73
			    ((MWR & 0x70) == 0x40)|| //BG�}�b�v�T�C�Y��32x64�̂Ƃ��̓E�F�C�g���J�b�g�B���^���G���W�F�����ȏЉ��(MWR=0x40)�Ńm�[�E�F�C�g���K�v�Bv2.63
			    (((MWR & 0x70) == 0x50)&&						  //BG�}�b�v�T�C�Y��64x64�ŁAVCR���������Ƃ��̓E�F�C�g���J�b�g�B�������l�̐V�`�����̃_���X�V�[��(MWR=0x50)�J�n���Ƀm�C�Y���o�Ȃ����߂Ƀm�[�E�F�C�g���K�v�Bv2.63
				 ((VCR < 4)||((DCR & 0x12) == 0x10)&&(CR & 0x80)))) //BG�}�b�v�T�C�Y��64x64�ŁASATB�ւ̎����]�����s���Ƃ�(���I�������荞�݃I�t��(�I�����Ƀm�[�E�F�C�g���ƁA�}�W�J���`�F�C�X(DCR=0x12,VCR=6,MWR=0x50)DEMO���Ƀm�C�Y)�����A��BG�\�����̏ꍇ�́A�m�[�E�F�C�g����ɂ���B���[���h�X�^�W�A��(VCR=3,MWR=0x50)�C�A���K�m�X(MWR=0x50)�C��������(MWR=0x50)�ŕK�v�BMWR=0x10�����ƃ��C�U���o�[II�T�ʃN���A���A�I�[�����N�G�X�g�ŕs��Bv2.70�X�V
					_bVDCAccessWait[_VN] = FALSE; //�A���K�m�X(DCR=0x10,MWR=0x50,VCR=4,CR=0xCC)�̑ΐ탂�[�h�Ńm�[�E�F�C�g���K�v�Bv2.41�X�V
												  //�V�e�B�n���^�[(MWR=0x10,VCR=3)�Ńm�[�E�F�C�g���K�v�B�E�F�C�g������ƁA�d����������̉�ʂŉ��ӂ����܂ɗ���B
												  //���[���h�X�^�W�A��(DCR=0x10,MWR=0x50,VCR=3,CR=0xC8)�̃~�[�g���Ƀm�[�E�F�C�g���K�v�B�Q���W�ʐM�������܂̃f���Ńm�[�E�F�C�g���K�v�Bv2.63
			else
				_bVDCAccessWait[_VN] = TRUE; //�{���o�[�}��'93(DCR=0,MWR=0x00,VCR=4)�C�T�C�����g�f�o�b�K�[�Y�̃X�^�[�g��̏e�����V�[��(DCR=0x10,MWR=0x10,VCR=4,CR=0x00?)�ŃE�F�C�g���K�v�B
											 //�p�b�N�����h(MWR=0x10,VCR=3,CR=0)�ŖʊJ�n���ɂP�t���[������Ȃ����߂ɕK�v�B
											 //�X�^�[�u���C�J�[�̊X�⓴�A���o���ۂɃt���[�Y���Ȃ����߂ɁA�E�F�C�g���K�v�B���^���G���W�F��(DCR=0x10,MWR=0x50,VCR=4,CR=0x08?)�̃X�^�[�g�f����Ƀt���[�Y���Ȃ����߂ɃE�F�C�g���K�v�Bv2.63�X�V
			if ((_DCC & 4) == 0) //DCC��bit2���N���A�̂Ƃ��͕K���E�F�C�g������B���ꂪ�Ȃ��ƁA�d�������L(MWR=0x30,VCR=3)�̓q���ŗ���B
				_bVDCAccessWait[_VN] = TRUE;
			if (_bWorldStadium91)
				_bVDCAccessWait[_VN] = FALSE; //���ۂ̉�ʐ؂�ւ����ɂP�t���[������錻�ہi���@�ł��N���邪�A�X�|�[�c�Q�[���Ȃ̂ł����K�����D��j�������Bv2.64
		}
	}

	//�P���C���`��
	if (pScreenBuf != NULL)
	{
		if (_SuperGrafx == 0)
			drawLine(_ScanLine);
		else
			drawLineSuperGrafx(_ScanLine); //Kitao�ǉ��B�X�[�p�[�O���t�B�b�N�p�B
		//drawLine(),drawLineSuperGrafx()�ŁA_bOverlap[_VN]��_bSpOver[_VN]���ݒ肳���Bv1.65�X�V
		for (_VN=0; _VN<=_SuperGrafx; _VN++) //�X�[�p�[�O���t�B�b�N�X���[�h�Ȃ�VDC�Q�Ԃ�𓮂���
		{
			//Kitao�X�V�B�X�v���C�g�̏Փˊ��荞�ݗv���͂����ōs���悤�ɂ����B�Q�l�Fv0.74��VBlank���Ԃōs���悤�ɂ����璴�Z�M�ŕs��B�������ǍD�B
			if (_bOverlap[_VN])
			{
				_bOverlap[_VN] = FALSE;
				if (CR & VDC_CTRL_CC)
				{
					_VdcStatus[_VN] |= VDC_STAT_CR;
					INTCTRL_Request(INTCTRL_IRQ1);
				}
			}
			//Kitao�X�V�B�X�v���C�g�I�[�o�[�̊��荞�ݗv���͂����ōs���悤�ɂ����B
			if (_bSpOver[_VN])
			{
				_bSpOver[_VN] = FALSE;
				if (CR & VDC_CTRL_OC)
				{
					_VdcStatus[_VN] |= VDC_STAT_OR;
					INTCTRL_Request(INTCTRL_IRQ1);
				}
			}
		}
	}
	_bRasterLate = TRUE; //����������BYR�̏����������N�������ꍇ�́A���̂Ƃ���_LineCounter���C���N�������g���Ȃ��B

	//Vblank�����BKitao�ǋL�BVblank�����͂����i�P���C���`�撼���CPU�p���[�g�p�O�j���ǂ��悤���B�p���[�e�j�X�A�\���W���[�u���C�h�A�X�[�p�[�_���C�A�X���Ŋm�F�B
	//			  vblank����ɑ�����CPU�p���[���K�v�ivblank���荞�ݗv�����m����CPU�֓`���邽�߁j�B�p���[�e�j�X�̃^�C�g����ʂŊm�F�B
	_ScanLine++;
	if ((_ScanLine == _VblankLineTop[0])||(_ScanLine == _VblankLineTop[_SuperGrafx])) //VBlank���C���ɗ���
	{
		MOUSE_UpdateDelta(); //Kitao�ǉ��B�����Ń}�E�X�̍��W���A�b�v�f�[�g����B�}�E�X���W���Q�Ƃ����(���Ƃ�����)���O�ɂȂ�A���̈ʒu���ǂ������Bv1.23
		
		//v0.81�ǉ��BVBlank���荞�ݑO�ɂP���C���̓r���܂�CPU�p���[���g��(VBlank���荞�ݗv����x�点��)�B���@�̃^�C�~���O�ɋ߂��Ȃ����B
		//  TvWidth=336���� �Q���W�ʐM�������܂̃X�^�[�g�f��(MWR=0x50�B40.0/100OK)�B
		//  �v���C�x�[�g�A�C�h���̃X�^�[�g����̃f��(MWR=0x10�B38.6NG�B39.0NG�B46.2OK�B�����߂̒l���K�v�B���������Ă��傫�����Ă��ʖځBVblankLineTop�̒l�ɂ���ĕω�����)�B
		//  �T�C�h�A�[���X�y�V������BEFORE�łŃX�^�[�g���ɃX�e�[�^�X�\�����h�Ȃ����߂ɁA�傫�߂̒l���K�v�iMWR=0x50�B38.6���XNG�B38.8OK�j�B
		//  �X�v���K��mk2��8�ʊJ�n�O�f���ő����̃A�b�v������Ȃ����߂ɑ傫�߂̒l���K�v�B�iMWR=0x50�B38.6,40.0OK)�B
		//  �_���W�����G�N�X�v���[���[�̃X�g�[���[�Љ�I�����ɃX�N���[�������P���C����u�����(�傫�߂̒l�����z�BSATB����CPU�X�g�[���̋�ɂ���ĕω�����B"SATB�c/16"����38.2NG)�B
		//  �G�^�[�i���V�e�B�ő傫�߂̒l�ŁA�A�C�e�����莞�Ȃǂŗh�ꂪ�����B39.0NG
		//  �p���[�X�|�[�c�̃j���[�X���O��9TV��ʂŗh��Ȃ����߂ɑ傫�߂̒l���K�v�iMWR=0x10�BSATB����CPU�X�g�[���̋�ɂ���ĕω�����B38.0,40.0OK�j�B
		//  ���[�h�X����L�Q�̃G���f�B���O(MWR=0x50�B40.0OK�BSATB����CPU�X�g�[���̋�ɂ���Ă��ω�����)�B
		//  �T�C�����g�f�o�b�K�[�Y�̃X�^�[�g�Ō��e�����V�[���ŗ����(�����߂̒l���K�v�B39.0/100OK�BVBline�̒l�ɂ����)�B
		//  ���g���[�_�[(MWR=0x10)�ő傫�߂̒l���悳�����B�傫���ƋH�ɉ�ʗh�ꂪ������(�m���ɂ����̒l���֌W���Ă��邩�͕s��)�B
		//	�\���W���[�u���C�h��OP�f��(MWR=0x10�B66.0/100���炢�ȉ����K�v�B�o���邾�������߂̒l�̂ق����Ȃ̃e���|����BSATB�̎����]���͖���)�B
		//  ���^���G���W�F���̃X�^�[�g�㎩�ȏЉ��Ɏ~�܂�Ȃ����߂�(MWR=0x40�B36.0/100OK�B�������ƃ}�l�[�W���[�Љ��̃t�F�[�h�A�E�g��NG�B�傫�ڂ̂ق��������݂����BrasterTimingCount�̒l�ɂ���čœK�l���ς��)�B
		//	�傫���l���ƁA�p���\���X�^�[�ŃX�e�[�W�N���A���ɋH�ɉ�ʂ��h���(MWR=0x10�B61.2NG�BVCR=3)�B
		//  ���[���h�q�[���[�Y�Q(MWR=0x50�B57.0/100�ȉ����K�v)�B���镨��̐퓬�V�[��(MWR=0x30�B61.2NG�B�����Ȓl���K�v�BScreenH=224�BBG��128)�B
		//  �[�������`�����v�̃��[�X�V�[���ő傫�ڂ̂ق��������B
		//  TvWidth=336�ȏ� Mr.�w���̑�`��(MWR=0x50�B40/100�ȉ����K�v)�B
		//  ������120%�̃X�^�[�g����̃f��(40/100�ȉ��ӂ肪�K�v�B�������Ă��傫���Ă��ʖځBVblankLineTop�̒l�ɂ���ĕω�����)�B
		//  ���C���{�[�A�C�����h(27.2/100�ȏオ�K�v)�B
		//  ��rasterTimingCount�̒l��SATB�]���̃E�F�C�g�l�ɂ���āA�����̍œK�l���ω�����B�傫�߂̒l�̂ق������X�^���荞�݂̘R�ꂪ���Ȃ��Ȃ�̂ŁA�ǂ��炩�Ƃ����Ɨ��z�B
		if (_Regs[0][VDC_MWR] & 0x40) //BG�̏c�}�b�v�T�C�Y��64(MWR��0x40�ȏ�)�̏ꍇ�Bv2.61
			a = (int)(VDC_CYCLESPERLINE*40.0/100) - rasterTimingCount; // 40.0/100�B���^���G���W�F���C�T�C�h�A�[���X�y�V����OK�BMr�w���̑�`��OK�B�G�^�[�i���V�e�BOK�Bv2.62�X�V
																	   //           �X�v���K��mk2��8�ʃf���C�_���W�����G�N�X�v���[���[�C���[�h�X����L�Q�̃G���f�B���O�B���[���h�q�[���[�Y�Q�B�Q���W�ʐM�������܂̃X�^�[�g�f���B
		else
			a = (int)(VDC_CYCLESPERLINE*38.4/100) - rasterTimingCount; // 38.4/100�B�v���C�x�[�g�A�C�h��OK�B������120%OK�Bv2.62�X�V
																	   //           �p���[�X�|�[�c�C���[���h�q�[���[�Y�Q�B���镨��B�\���W���[�u���C�h�B�p���\���X�^�[�B
		if (a < 0)
			a = 0;
		else
			cpuAdvance(a);

		//�^�E���_�]���̃I�[�g�}�b�v��ʕ���΍�B���̈ʒu�ŃI�[�o�[�N���b�N����B�����@�ł�����邪�A���K�Ƀv���C�ł���悤���{�Bv2.20
		if (_bShinMegamiTensei)
		{
			if (APP_GetFixShinMegamiTensei())
				for (i=1; i<=3350; i++) //3350��OK�B3360�ȏゾ�Ǝ኱���̏��(COMP���j���[���J���^�C�~���O�Ȃ�)�ő�������C������B3300���ƃV���W���N��㔼�̑傫��MAP��NG�B���̏�ʂŉe�����o�Ȃ��悤�A�Ȃ�ׂ��������l�ɂ���B�t�F�[�h�A�E�g��l��X�̃��b�Z�[�W�\���̂Ƃ��Ɏ��@�̑��x�̂悤�Ɂu������x�̊ԁv������ق������͋C���o�Ă����B
					if (gCPU_ClockCount++ >= 0) CPU_ExecuteOperation();
		}
		
		for (_VN=0; _VN<=_SuperGrafx; _VN++) //�X�[�p�[�O���t�B�b�N�X���[�h�Ȃ�VDC�Q�Ԃ�𓮂���
		{
			if (_ScanLine == _VblankLineTop[_VN])
			{
				//Kitao�ǉ��BMWR�i���������j���W�X�^���ύX����Ă����ꍇ�A�����Ń������}�b�v���X�V����B
				if (_bMWRchange[_VN])
				{
					_bMWRchange[_VN] = FALSE;
					
					bmwr0x40 = ((MWR & 0x40) != 0);
					_BGH[_VN] = (bmwr0x40) ? 64 : 32;
					_BGW[_VN] = _BGWidthTable[(MWR >> 4) & 3];
					_LineCountMask[_VN] = (bmwr0x40) ? 0x1FF : 0xFF;
					_LineCounter[_VN] &= _LineCountMask[_VN];
					invalidate_tile_cache();

					if ((MWR & 9) == 9) //7MHz���[�h(��336)��bit0�������Ă����ꍇ�Bv2.66�X�V
						_MaxSpPerLine[_VN] = 14; //�X�v���C�g������14�����Bv2.63�ǉ�
					else
						_MaxSpPerLine[_VN] = 16; //�X�v���C�g������16����
				}
				
				//Kitao�ǉ��BVRAM-VRAM�Ԃ�DMA�]���R�}���h�����Ă����ꍇ�A�����Ŏ��s����B�����ōs�����Ƃ������O���b�T�[�ŕK�v�B
				if (_bVramDmaExecute[_VN])
				{
					_bVramDmaExecute[_VN] = FALSE;
					
					srcInc = (DCR & 4) ? -1 : 1;
					dstInc = (DCR & 8) ? -1 : 1;
					do
					{
						write_vram(DESR, _pwVideoRam[_VN][SOUR]);
						SOUR += srcInc;
						DESR += dstInc;
					} while (LENR--);
					
					if (DCR & 0x2)
					{
						_VdcStatus[_VN] |= VDC_STAT_DV;
						INTCTRL_Request(INTCTRL_IRQ1);
					}
				}
				
				//Vblank���荞�ݗv��
				if ((CR & VDC_CTRL_VC)||(_bVDCleared[_VN]))
				{
					_bVDCleared[_VN] = FALSE;
					_VdcStatus[_VN] |= VDC_STAT_VD; //���荞�݂𔭐�������Ƃ��̂݃Z�b�g�BKitao�ǋL�FSUPER���S�P�ŕK�v�B
					INTCTRL_Request(INTCTRL_IRQ1);
				}
				
				//DMA from VRAM to SATB (���@�ł͓]������ CPU �����S�ɒ�~���Ȃ�)�B
				if (_bUpdateSATB[_VN] || (DCR & 0x10))
				{
					_bUpdateSATB[_VN] = FALSE;
					update_satb(SATB); //�����ł����X�V���邱�Ƃ��A�V�O����ZIRIA�ŕK�v�B
					_SpDmaCount[_VN] = 4; //4�B�Q�l�F5�ȏゾ�ƃ��~���O�X�̃X�e�[�^�X�\���ɖ��B1���ƃT�C�o�[�N���X�̃f�����������B�傫���ƃX�[�p�[�o���[�ŉ�ʗh��B�������ƃ`�F�C�XH.Q.�ŉ�ʂ��t���b�V������B
					_SpDmaStole[_VN] = 0;
				}
			}
		}
	
		//VBlank��Ɏc���CPU�p���[���g���B
		if (_OverClockCycle < 0) gCPU_ClockCount += _OverClockCycle; //�_�E���N���b�N����ꍇ�B���̃^�C�~���O�œ����Ɠ���ւ̉e�������Ȃ��Bv1.61�ǉ��B��Ƀf�o�b�O�p�B
		cpuAdvance(VDC_CYCLESPERLINE - (rasterTimingCount + a));
	}
	else //�ʏ�
	{
		//Kitao�ǉ��B�c���CPU�p���[��`���Ɏg���B
		if (_OverClockCycle < 0) gCPU_ClockCount += _OverClockCycle; //�_�E���N���b�N����ꍇ�B���̃^�C�~���O�œ����Ɠ���ւ̉e�������Ȃ��Bv1.61�ǉ��B��Ƀf�o�b�O�p�B
		if (_ScanLine <= 179) //�҂�����Ɠ���N���b�N�����킹�邽�߁A179���C���܂ł�1�N���b�N�����i�߂�B
			cpuAdvance(VDC_CYCLESPERLINE -rasterTimingCount +1); //�����_�[��(453.0 != 453.68)�̂Ԃ���i�߂�
		else //180���C���ȍ~
			cpuAdvance(VDC_CYCLESPERLINE -rasterTimingCount);
	}

	//Kitao�ǉ��B�I�[�o�[�N���b�N�@�\��ǉ��B
	if (_OverClockCycle > 0)
	{	//ADPCM�̃A�N�Z�X�^�C�~���O��A�Ȃ̃e���|�Ȃǂւ̉e��������邽�߁ACDROM,APU,TIMER�͐i�߂Ȃ��B
		_bOverClockNow = TRUE;
		if (_SuperGrafx == 1)
		{
			for (i=1; i<=_OverClockCycle; i++)
			{
				vramDmaCountCheckSG();
				MOUSE_AdvanceClock(); //�}�E�X�͓������ǂ��Ȃ�̂Ői�߂�
				if (gCPU_ClockCount++ >= 0) CPU_ExecuteOperation();
			}
		}
		else //�������̂��߁A�X�p�O���̂Ƃ��Ə����𕪂����B
		{
			for (i=1; i<=_OverClockCycle; i++)
			{
				vramDmaCountCheck();
				MOUSE_AdvanceClock(); //�}�E�X�͓������ǂ��Ȃ�̂Ői�߂�
				if (gCPU_ClockCount++ >= 0) CPU_ExecuteOperation();
			}
		}
		_bOverClockNow = FALSE;
	}

	//Kitao�ǉ��B�V���r�r���}���Q�łP�t���[����ʂ�����镔���i�����@�ł��N����j�������B
	//			 ���X�^���荞�݂̗v�����܂��`����Ă��Ȃ������ꍇ�B�I�[�o�[�N���b�N���ĈӒn�ł��`����B
	//			 ���@�ł��N����̂ł��̂܂܂ł��Ǝv�������A���������Y��ɂł���̂Ŏ����B
	//			 ���@�ƈႤ�����ɂȂ�̂ŁA���̃\�t�g�i�V�g�̎����j�ł͋t�ɕ��Q���o�邱�Ƃ�����B
	//           �p�b�N�����h�ŖʃZ���N�g����P�t���[����ʂ�����镔���i�����@�ł��N����j�������B
	//           �^�E���_�]���̃C�x���g�V�[����퓬�V�[���ȂǂŎ��X�P�t���[����ʂ�����镔���i�����@�ł��N����j�������B
	//			 ���@�Ŗ��ɂȂ��Ă���悤�Ȍ��ۂ͂��̂܂܂ɂ��Ă����������A�u���炩�ɕ���Ȃ��ق���������ʁv�Ɍ����Ă͉��K�ȓ����ɂ�������ōs�������Bv2.08�L
	if (_bForceRaster)
	{
		for (_VN=0; _VN<=_SuperGrafx; _VN++) //�X�[�p�[�O���t�B�b�N�X���[�h�Ȃ�VDC�Q�Ԃ�𓮂���
		{
			i = 0;
			while (_VdcStatus[_VN] & VDC_STAT_RR)
			{
				if (gCPU_ClockCount++ >= 0) CPU_ExecuteOperation();
				if (++i > VDC_CYCLESPERLINE*MAX_SCANLINE*2) //�ő��Q�t���[���Ԃ�I�[�o�[�N���b�N�i�����菭�Ȃ��ƃV���r�r���}���Q�ł�◐��j�B����܂ő҂��đʖڂȂ�X���[�B
					break;
			}
		}
	}

	if (_ScanLine == MAX_SCANLINE)
	{
		//Kitao�ǉ��B�p�b�N�����h�ŖʃZ���N�g����P�t���[����ʂ�����镔���i�����@�ł��N����j�������B_bForceRaster���g���悤�ɂ����̂Ō��ݔ�g�p�B
		//           �^�E���_�]���̃C�x���g�V�[����퓬�V�[���ȂǂŎ��X�P�t���[����ʂ�����镔���i�����@�ł��N����j�������Bv2.24
		//			 �V���r�r���}���Q�ŃX�e�[�W�Q(������)�N���A�����̖ʃX�^�[�g���ɂP�t���[����ʂ�����镔���i���m�F���ĂȂ������Ԃ���@�ł��N����B���Ԃ̂���Ƃ��Ɋm�F�j�������Bv2.40
		if (_bForceVBlank)
		{
			for (_VN=0; _VN<=_SuperGrafx; _VN++) //�X�[�p�[�O���t�B�b�N�X���[�h�Ȃ�VDC�Q�Ԃ�𓮂���
			{
				i = 0;
				while (_VdcStatus[_VN] & VDC_STAT_VD)
				{
					if (gCPU_ClockCount++ >= 0) CPU_ExecuteOperation();
					if (++i > VDC_CYCLESPERLINE*MAX_SCANLINE*2) //�ő��Q�t���[���Ԃ�I�[�o�[�N���b�N�B����܂ő҂��đʖڂȂ�X���[�B
						break;
				}
			}
		}
		//���̃t���[���ւ̏���
		_ScanLine = 0;
		_DisplayCounter = 0;
		//VBlank���Ԃɐ����\���J�n�ʒu���ύX����Ă����ꍇ�A���t���[���̐����\���J�n�ʒu��␳����Bv2.09�X�V
		for (_VN=0; _VN<=_SuperGrafx; _VN++) //�X�[�p�[�O���t�B�b�N�X���[�h�Ȃ�VDC�Q�Ԃ�𓮂���
		{
			if	(_DCC & 4) //DCC��0�̂Ƃ��͒������Ȃ��B�d�������L�Bv2.49
				_TvStartLine[_VN] += _LineOffset[_VN]; //�~�Y�o�N��`���̗��A�C�e����ʗh��Č��ɕK�v�B�X�v���b�V�����C�N�̃X�e�[�W�J�n���ɕK�v�Bv2.45�X�V
			_LineOffset[_VN] = 0; //�I�t�Z�b�g�����Z�b�g����B
		}
	}
}


//Kitao�ǉ��B���X�^���荞�ݔ��蒼��`�`��܂łɎg��CPU�p���[��ݒ肷��B
//			 �L�F�G�~�����[�V�����̏������x�����̂��߁A���@�̂悤�Ƀ��C���`��r����"�P�h�b�g�`�悲��"�Ɋ��荞�݂�
//				 ���������邱�Ƃ͂ł��Ȃ����߁A����RasterTiming�̐ݒ肪�K�v�B
//				 ���̂��߁A�f�t�H���g�ݒ肾�Ɖ�ʂ��h�ꂽ�肸��Ă��܂��\�t�g���������o�Ă��܂����A�\�t�g���Ƃ̐ݒ肪
//				 ���܂�΁A���@����������Ȃ��Y��ȃ��C���X�N���[�����ł��闘�_������B
void
VDC_SetRasterTiming(
	Sint32	n)
//n�̒l�� 1=���߂Ɂu���X�^���荞�ݗv���v��m�点��̂��œK�ȃ\�t�g�B2=�����炢�i�ʏ�j�Ɂu���X�^���荞�ݗv���v��m�点��̂��œK�ȃ\�t�g�B3=�x�߂Ɂu���X�^���荞�ݗv���v��m�点��̂��œK�ȃ\�t�g�B
//v1.59�Ń��W�X�^�̐ݒ�ɂ���ă^�C�~���O���ς��(����)�̂��Č��BLATE�ȂǂȂǂ͂قڕs�K�v�ɁBEARLY�����������̃\�t�g�Ō���K�v(�����T�C���͂���͂�)�B
{
	//Normal�ɐݒ肷��Ƃ��ŁA"���j���[�\����Normal�̈ʒu�̂܂�_RasterTimingType�������ύX����Q�[���̏ꍇ"�͂��̐ݒ�l�ɖ߂��B
	if (n == 2)
		if (_AutoRasterTimingType >= 11) //���j���[�\����Normal�̈ʒu�̂܂�_RasterTimingType�������ύX����Q�[��
			n = _AutoRasterTimingType;

	_RasterTimingType = n;

	switch (_RasterTimingType)
	{
		case 1: //EARLY
			_RasterTimingCount = 200; //200
			break;
		case 2: //MIDDLE(Normal)
			//�J�_�b�V���ő傫�߂̒l���K�v�B�G�^�[�i���V�e�B�B�e�P�T�[�J�X�̃X�^�[�e�B���O�O���b�h�B�T�C�h�A�[��SP�ő傫�ڂ̒l���K�v�B�_���W�����G�N�X�v���[���[OK(�傫�ڂ̂ق����ǂ�)�B�傫���ƃ`�F�C�X�g�p�ŗ���B
			_RasterTimingCount = 88; //88�B�莝���̃\�t�g�ł͑��̃Q�[�����قƂ�ǂ�MIDDLE�Ŗ��Ȃ��悤���B
			break;
		case 3: //LATE
			_RasterTimingCount = 67; //67�B�X�v���b�^�[�n�E�X�B�f�r���N���b�V��(69�ȉ��K�v�B���@�ł͗���Ă�)�B�}�W�N�[���B���M�I���B
			break;
		case 4: //MORE EARLY
			_RasterTimingCount = 350; //350�B�Ղւ̓�(210���炢�ȏオ�K�v)�B"�I�[�_�[�U�O���t�H��(U)"�����ꂪ�œK�Ƃ̂���(�C�O�̕�����̏��)�B
			break;
		case 5: //MORE LATE
			_RasterTimingCount = 33; //33�B�X�[�p�[�_���C�A�XII�̃n�C�X�R�A�\���B
			break;
		case 11: //LittleEARLY �A�E�g����(88�`95�K�v�B95�œK)�B
			_RasterTimingCount = 95; //95
			break;
		case 12: //�T�C�h�A�[��SP�p�����������ݔ�g�p�B�T�C�h�A�[��SP�̃A�����W�ł́u_RasterTimingType=2(Normal)�v�Ŋ��荞�݂̎��Ԃ��l������Ƃ��܂������B
			_RasterTimingType = 2;
			_RasterTimingCount = 88;
			break;
		case 13: //LittleLATE �����_�[����(���ݔ�g�p)�B�t�H�S�b�g�����[���h(���ݔ�g�p)�B�X�e�[�g�Z�[�u���Ă����ꍇ���l���Ďc���Ă����B
			_RasterTimingType = 2;
			_RasterTimingCount = 88; //����84,79,80
			break;
		case 14: //MostEARLY ���Ղ̌���p(���ݔ�g�p)�B�X�e�[�g�Z�[�u���Ă����ꍇ���l���Ďc���Ă����B
			_RasterTimingType = 2;
			_RasterTimingCount = 88; //����80,420
			break;
		case 15: //�\���W���[�u���[�h�p�����������ݔ�g�p�B�X�e�[�g�Z�[�u���Ă����ꍇ���l���Ďc���Ă����B
			//�`�F�C�XH.Q.(�ȑO��MORE LATE)�ł��g�p�B�u�ߋ��͌ʐݒ聨���݂̓m�[�}���ݒ�v�ɕς����ꍇ�A�ߋ��o�[�W�����̃X�e�[�g�����[�h�����Ƃ��̂��߂ɂ������g���ĕK���m�[�}���ɖ߂�悤�ɂ���B
			_RasterTimingType = 2;
			_RasterTimingCount = 88; //��305�B�\���W���[�u���[�h(�R�ʏ��Ղ�305�ȏ�K�v�B���t�ɑ傫�����Ă�OP�f���̍Ō�ł�◐��)�B
			break;
	}
}

//Kitao�ǉ�
Sint32
VDC_GetRasterTimingType()
{
	return _RasterTimingType;
}

//Kitao�ǉ��B���̂���Q�[���͋N�����Ɏ����Ń��X�^�^�C�~���O��ݒ肷��BMAINBOARD.c �� CDROM.c ���痘�p�B
void
VDC_SetAutoRasterTiming(
	Sint32	n)
{
	_AutoRasterTimingType = n;
	VDC_SetRasterTiming(n);
}

//Kitao�ǉ�
Sint32
VDC_GetAutoRasterTimingType()
{
	return _AutoRasterTimingType;
}


//Kitao�ǉ��BCPU���I�[�o�[�N���b�N���č���������B
void
VDC_SetOverClock(
	Sint32	n)
//n=0�Ȃ�m�[�}��
{
	_OverClockType = n;
	_OverClockCycle = 0;
	CPU_SetTurboCycle(0);
	switch (_OverClockType)
	{
		case -2: _OverClockCycle = -(Sint32)(VDC_CYCLESPERLINE / 2.0 +0.5); break;	//0.50�{
		case -1: _OverClockCycle = -(Sint32)(VDC_CYCLESPERLINE / 4.0 +0.5); break;	//0.75�{
		case  1: _OverClockCycle = (Sint32)(VDC_CYCLESPERLINE / 4.0 +0.5); break;	//1.25�{
		case  2: _OverClockCycle = (Sint32)(VDC_CYCLESPERLINE / 3.0 +0.5); break;	//1.33�{
		case  3: _OverClockCycle = (Sint32)(VDC_CYCLESPERLINE / 2.0 +0.5); break;	//1.5�{
		case  4: _OverClockCycle = VDC_CYCLESPERLINE; break;				//2.0�{
		case  5: _OverClockCycle = (Sint32)(VDC_CYCLESPERLINE*1.5); break;			//2.5�{
		case  6: _OverClockCycle = (Sint32)(VDC_CYCLESPERLINE*2.0); break;			//3.0�{
		//100,200,300�̓^�[�{�T�C�N�����[�h(����T�C�N�������炷)�BCPU.c�ɂđ��������߂�B
		case 100: CPU_SetTurboCycle(100); break; //�^�[�{�P�{
		case 200: CPU_SetTurboCycle(200); break; //�^�[�{�Q�{
		case 300: CPU_SetTurboCycle(300); _OverClockCycle = (Sint32)(VDC_CYCLESPERLINE / 2.0 +0.5);	break; //�^�[�{�R�{(�^�[�{�Q�{x1.5�{)
	}
}

//Kitao�ǉ��B�g�p���̃I�[�o�[�N���b�N�^�C�v�𓾂�Bcpu.c ����g�p
Sint32
VDC_GetOverClockType()
{
	return _OverClockType;
}

//Kitao�ǉ��B�Q�[���̃^�C�~���O�s����������邽�߂ɁA�����ŃI�[�o�[�N���b�N�ݒ�ɂ���B���ۂ��Ղ郁�C��,IQ�p�j�b�N�Ŏg�p�B
void
VDC_SetAutoOverClock(
	Sint32	n)
{
	_AutoOverClock = n;
	if ((_OverClockType < _AutoOverClock)|| //�����łɃI�[�o�[�N���b�N���Ă����ꍇ�͂��̂܂�
		(_AutoOverClock == 0)) //�X�s�[�h�_�E���̂Ƃ�
			VDC_SetOverClock(_AutoOverClock);
}

//Kitao�ǉ�
Sint32
VDC_GetAutoOverClock()
{
	return _AutoOverClock;
}


//Kitao�ǉ��B���x�^�C�~���O�����킸��肪�N����Q�[���ɃE�F�C�g������B�iSATB�]�����ɃE�F�C�g������j
void
VDC_SetWaitPatch(
	Sint32	cycle)
{
	_WaitPatch = cycle; //�P�t���[���ŃE�F�C�g����T�C�N����
}


//Kitao�ǉ��B�����I�Ƀ��X�^���荞�݂�CPU�ɓ`���܂ő҂��ǂ�����ݒ肷��B�iCPU�ɓ`���܂ŃI�[�o�[�N���b�N����j
void
VDC_SetForceRaster(
	BOOL	forceRaster)
{
	_bForceRaster = forceRaster;
}


//Kitao�ǉ��B�����I��VBlank���荞�݂�CPU�ɓ`���܂ő҂��ǂ�����ݒ肷��B�iCPU�ɓ`���܂ŃI�[�o�[�N���b�N����j
void
VDC_SetForceVBlank(
	BOOL	forceVBlank)
{
	_bForceVBlank = forceVBlank;
}


//Kitao�ǉ��B�X�v���C�g�������Č����邩�ǂ�����ݒ肷��B
void
VDC_SetPerformSpriteLimit(
	BOOL	bPerform)
{
	_bPerformSpriteLimit = bPerform;
}

//Kitao�ǉ��B�X�v���C�g�S�\���Ŗ��̂���Q�[���́A�N�����Ɏ����ŃX�v���C�g�����Č��̐ݒ�ɂ���BMAINBOARD.c �� CDROM.c ���痘�p�B
void
VDC_SetAutoPerformSpriteLimit(
	BOOL	bPerform)
{
	_bAutoPerformSpriteLimit = bPerform;
	_bPerformSpriteLimit = bPerform;
}

//Kitao�ǉ�
BOOL
VDC_GetPerformSpriteLimit()
{
	return _bPerformSpriteLimit;
}


//Kitao�ǉ��B�X�v���C�g,BG��\���E��\���ؑւ���@�\(�J������)�Bv2.06
void
VDC_SetLayer()
{
	_bSpriteLayer = APP_GetSpriteLayer();
	_bSprite2Layer = APP_GetSprite2Layer();
	_bBGLayer  = APP_GetBGLayer();
	_bBG2Layer = APP_GetBG2Layer();
}


Sint32
VDC_GetScanLine()
{
	return _ScanLine;
}


//Kitao�ǉ��B_ScanLine��VBlank���ԊJ�n�̎��̃��C���Ȃ�TRUE��Ԃ��BCDROM.c ���痘�p�B�����ݔ�g�p
BOOL
VDC_CheckVBlankStart()
{
	return (_ScanLine == _VblankLineTop[0] +1);
}


//Kitao�ǉ�
void
VDC_SetScreenWidth(
	Sint32	screenW)
{
	_ScreenW[0] = screenW;
}

//Kitao�X�V
const Sint32
VDC_GetScreenWidth()
{
	return _ScreenW[0];
}


const Sint32
VDC_GetDisplayHeight()
{
	return _ScreenH[0];
}


//Kitao�ǉ��B�e���r��ʏ�́u��ԏ�̃��C���v�̍��W��Ԃ��B
Sint32
VDC_GetTvStartLine()
{
	return _TvStartLine[0] + _TvStartLineAdjust[0]; //v2.47�X�V
}


//Kitao�ǉ�
Uint8
VDC_GetVdcStatus()
{
	return _VdcStatus[0];
}


//Kitao�ǉ�
void
VDC_SetSuperGrafx(
	Sint32	superGrafx)
{
	_SuperGrafx = superGrafx;
}

//Kitao�ǉ�
Sint32
VDC_GetSuperGrafx()
{
	return _SuperGrafx;
}

//Kitao�ǉ��B�I�[�o�[�N���b�N����CPU��������TRUE�B�I�[�o�[�N���b�N���Ă��Ȃ����A�܂��͒ʏ핪�p���[���������Ȃ�FALSE��Ԃ��B
BOOL
VDC_GetOverClockNow()
{
	return _bOverClockNow;
}


/*-----------------------------------------------------------------------------
Kitao�X�V�Bv1.11�B�������̂���VCE.c �������֓��������B
-----------------------------------------------------------------------------*/

//Kitao�ǉ��BTV��ʏ�ł̕\������ݒ肷��
static inline void
set_TvWidth()
{
	if (_DCC & 2)
		_TvWidth = 512;
	else if (_DCC & 1)
		_TvWidth = 336;
	else
		_TvWidth = 256;
	_VN = 0;
	setTvStartPos(); //�����\���J�n�ʒu���X�V
}

//Kitao�ǉ��Bv2.50
static inline void
set_Palette()
{
	Uint32	c;

	_Palette333[_ColorTableAddr] = _ColorLatch; //Kitao�X�V�B�u0RGB�v��32�r�b�g�ϐ��֊i�[����悤�ɂ����Bv1.61�኱�������B
	c = ((_ColorLatch & 0x0038)<<13)|((_ColorLatch & 0x01C0)<<2)|(_ColorLatch & 0x0007);
	if (_ColorTableAddr < 0x0100) //BG�p�p���b�g
	{
		if (_ColorTableAddr == 0x0000) //BG�p�p���b�g�����F
		{
			_PaletteBG[0x00] = _PaletteBG[0x10] = _PaletteBG[0x20] = _PaletteBG[0x30] =
			_PaletteBG[0x40] = _PaletteBG[0x50] = _PaletteBG[0x60] = _PaletteBG[0x70] =
			_PaletteBG[0x80] = _PaletteBG[0x90] = _PaletteBG[0xA0] = _PaletteBG[0xB0] =
			_PaletteBG[0xC0] = _PaletteBG[0xD0] = _PaletteBG[0xE0] = _PaletteBG[0xF0] = c;
		}
		else if (_ColorTableAddr & 0xF) //�����F�ȊO�Ȃ�
			_PaletteBG[_ColorTableAddr] = c;
	}
	else //�X�v���C�g�p�p���b�g
	{
		if (_ColorTableAddr == 0x0100) //�X�v���C�g�p�p���b�g�����F
		{
			_PaletteSP[0x00] = _PaletteSP[0x10] = _PaletteSP[0x20] = _PaletteSP[0x30] =
			_PaletteSP[0x40] = _PaletteSP[0x50] = _PaletteSP[0x60] = _PaletteSP[0x70] =
			_PaletteSP[0x80] = _PaletteSP[0x90] = _PaletteSP[0xA0] = _PaletteSP[0xB0] =
			_PaletteSP[0xC0] = _PaletteSP[0xD0] = _PaletteSP[0xE0] = _PaletteSP[0xF0] = c;
		}
		else if (_ColorTableAddr & 0xF) //�����F�ȊO�Ȃ�
			_PaletteSP[_ColorTableAddr & 0xFF] = c;
	}
}

/*-----------------------------------------------------------------------------
	[VDC_VceWrite]
		VCE�ւ̏������ݓ�����L�q���܂��B
-----------------------------------------------------------------------------*/
/*
	[write_palette]

	convert GRB333 --> RGB555 / RGB565
	and write to the palette.

	basic logic:

	Uint8 G = (color & 0x1c0) >> 6;
	Uint8 R = (color & 0x038) >> 3;
	Uint8 B = (color & 0x007) >> 0;

	Rshift = 10;
	Gshift = 5;
	Bshift = 0;

	_Palette[addr]	= R << (Rshift+2);
	_Palette[addr] |= G << (Gshift+2);
	_Palette[addr] |= B << (Bshift+2);
*/
void
VDC_VceWrite(
	Uint32	regNum,
	Uint8	data)
{
	//CPU 1 Clock Wait  VCE�|�[�g�A�N�Z�X�̃E�F�C�g�B
	//		�d�������L�̃M�����u����ʂłP�t���[���̗��ꂪ�����B
	//		�l�N���X�̗v��(MWR=0x50)��OP�f���Ńi�C�g�̍U�����͂ݏo���Ȃ����߂ɕK�v�B
	//		�o�[�X�g���[�h�̍Œ��́A�E�F�C�g������Ȃ���������Ȃ��B�����PC�ւ̕��ׂ�D�悵�āA��ɃE�F�C�g�����邱�ƂƂ���Bv2.07�L
	if (gCPU_Transfer != 0) //�]�����߂����VDC�A�N�Z�X�̏ꍇ�B���ꂪ�Ȃ��ƁA���㕨��Q�̂n�o�f���ŗ���Bv2.62�X�V
		gCPU_ClockCount--; //CPU 1 Clock Wait

	//v1.15�X�V�B�������Bcase���́A�悭�g������̂��ɒu�����ق������������ł������B
	switch (regNum & 7)
	{
		case 5:	// �J���[�e�[�u���f�[�^���C�g �g
			if (data & 1) //v1.10�X�V
				_ColorLatch |= 0x100;
			else
				_ColorLatch &= 0xFF;
			set_Palette(); //Kitao�X�V�Bv2.50
			_ColorTableAddr++;
			_ColorTableAddr &= 0x1FF;
			return;

		case 4:	// �J���[�e�[�u���f�[�^���C�g �k
			_ColorLatch = data; //Kitao�X�V�B��ʃo�C�g�̓N���A�B���[���h�T�[�L�b�g�Bv2.50
			set_Palette(); //Kitao�X�V�BLow�o�C�g���������������A��ʌ��ʂɔ��f�����B���[���h�T�[�L�b�g�Bv2.50
			return;

		case 3:	// �J���[�e�[�u���A�h���X �g
			_ColorTableAddr = (_ColorTableAddr & 0xFF) | ((data & 1) << 8);
			return;

		case 2:	// �J���[�e�[�u���A�h���X �k
			_ColorTableAddr = (_ColorTableAddr & 0x100) | data; //v2.50�L�F��ʃo�C�g���N���A����ƃh���A�[�K�̓��ŃL�����̐F����
			return;

//		case 1: // �R���g���[�����W�X�^ �g
//			return;

		case 0: // �R���g���[�����W�X�^ �k
			// (�h�b�g�N���b�N���w�肷��Bbit7��1�̂Ƃ��͔������[�h�j
			_DCC = data & 0x87;
			set_TvWidth(); //Kitao�ǉ�
			VDC_SetTvStartLine(); //Kitao�ǉ��B�����\���J�n�ʒu���X�V
			return;
	}
}

/*-----------------------------------------------------------------------------
	[VDC_VceRead]
		VCE����̓ǂݏo��������L�q���܂��D
-----------------------------------------------------------------------------*/
/*
	[read_palette]

	convert RGB555 / RGB565 --> GRB333

	basic logic:

	Uint8 R = (_Palette[addr] & 0x7c00) >> 10;
	Uint8 G = (_Palette[addr] & 0x03e0) >> 5;
	Uint8 B = (_Palette[addr] & 0x001f) >> 0;

	G >>= 2; R >>=	2; B >>= 2;

	return (G << 6) | (R << 3) | B;

	 0RRR RRGG GGGB BBBB
   & 0111 0011 1001 1100  (0x739c)
   = 0RRR 00GG G00B BB00

	 0000 000G GGRR RBBB
*/
Uint8
VDC_VceRead(
	Uint32	regNum)
{
	Uint8	ret;

	switch (regNum & 7) //Kitao�X�V
	{
		case 5:	/* �J���[�e�[�u���f�[�^���[�h �g */
			ret = (Uint8)(_Palette333[_ColorTableAddr++] >> 8) | 0xFE;
			_ColorTableAddr &= 0x1FF;
			return ret;
		case 4:	/* �J���[�e�[�u���f�[�^���[�h �k */
			return (Uint8)_Palette333[_ColorTableAddr];
	}

	//PRINTF("VceRead %X", regNum);
	return 0xFF; //Kitao�X�V�B0�łȂ�0xFF��Ԃ����ƂŁA�~�Y�o�N��`���̂S�ʂ̕s�(��̋O�����قȂ�)�����ɉ��������Bv1.62
}


//Kitao�ǉ��B�e���r��ʂ̉��\���𑜓x�i�h�b�g�N���b�N�Ō��܂�j��Ԃ��B
Sint32
VDC_GetTvWidth()
{
	return _TvWidth;
}

//Kitao�ǉ�
Uint8
VDC_GetDCC()
{
	return _DCC;
}

//v2.68�ǉ��BJoyPad.cpp����G�������h�h���S���̃p�b�`�����Ŏg�p�B
Uint16
VDC_GetMWR()
{
	return _Regs[0][VDC_MWR]; //MWR
}


//Kitao�ǉ��B�X�v���C�g�̓����F��32�r�b�g�J���[�ŕԂ��B
Uint32
VDC_GetSpColorZero()
{
	return _PaletteSP[0]; //�X�v���C�g�̓����F
}


//Kitao�ǉ��Bv2.20
void
VDC_SetShinMegamiTensei(
	BOOL	shinMegamiTensei)
{
	_bShinMegamiTensei = shinMegamiTensei;
}

//Kitao�ǉ��Bv2.20
Sint32
VDC_GetShinMegamiTensei()
{
	return	_bShinMegamiTensei;
}

//Kitao�ǉ��Bv2.64
void
VDC_SetWorldStadium91(
	BOOL	worldStadium91)
{
	_bWorldStadium91 = worldStadium91;
}

//Kitao�ǉ��Bv2.70
void
VDC_SetEikanKimi(
	BOOL	eikanKimi)
{
	_bEikanKimi = eikanKimi;
}

//Kitao�ǉ��Bv2.70
BOOL
VDC_GetEikanKimi()
{
	return _bEikanKimi;
}

//Kitao�ǉ��Bv2.70
void
VDC_SetPowerLeague(
	BOOL	powerLeague)
{
	_bPowerLeague = powerLeague;
}

//Kitao�ǉ��Bv2.70
BOOL
VDC_GetPowerLeague()
{
	return _bPowerLeague;
}

//Kitao�ǉ��Bv2.70
void
VDC_SetTheProYakyuu(
	BOOL	theProYakyuu)
{
	_bTheProYakyuu = theProYakyuu;
}

//Kitao�ǉ��Bv2.70
BOOL
VDC_GetTheProYakyuu()
{
	return _bTheProYakyuu;
}


// save variable
#define SAVE_V(V)	if (fwrite(&V, sizeof(V), 1, p) != 1)	return FALSE
#define LOAD_V(V)	if (fread(&V, sizeof(V), 1, p) != 1)	return FALSE
// save array
#define SAVE_A(A)	if (fwrite(A, sizeof(A), 1, p) != 1)	return FALSE
#define LOAD_A(A)	if (fread(A, sizeof(A), 1, p) != 1)		return FALSE

//Kitao�ǉ��Bv0.89���Â��X�e�[�g�Z�[�u�t�@�C��(�X�[�p�[�O���t�B�b�N�X�����O)�����[�h
BOOL
OldLoadState(
	FILE*		p)
{
	Uint16		Regs[32];
	Uint32		AR;

	Uint8		VideoRam[65536]; //VRAM 64KB
	Uint16*		pwVideoRam; //v2.67�ǉ�
	Uint16		ReadData; //Kitao�ǉ��B���ۂ�VRAM���[�h�A�N�Z�X��VDC�|�[�g��"MARR���C�g��"�ɂ����Ȃ���(����)�B

	Sint32		ScreenW;
	Sint32		ScreenH;
	Uint32		BGH;
	Uint32		BGW;

	Uint16		VdcAddrInc;
	Uint8		VdcStatus;

	Sint32		RasterCounter;
	BOOL		bRasterRequested; //Kitao�ǉ��B���̃��C���̃��X�^���荞�ݗv�����I���Ă�����TRUE
	Sint32		LineCounter;
	Sint32		LineCountMask;

	BOOL		bUpdateSATB;
	Uint32		SpDmaCount;
	Sint32		SpDmaStole;
	Uint32		VramDmaCount; //v0.82

	BOOL		bSpOver;
	BOOL		bOverlap;
	BOOL		bBurstMode;
	BOOL		bMWRchange;

	Uint16		SpRam[64*4];

	Sint32		TvStartLine;
	Sint32		VblankLine;

	Sint32		rasterTimingType;
	BOOL		bPerformSpriteLimit;
	Sint32		waitPatch;
	Sint32		popfulMail;
	Sint32		overClockType;

	LOAD_A(Regs);
	LOAD_A(VideoRam);
	LOAD_A(SpRam);

	LOAD_V(AR);
	if (MAINBOARD_GetStateVersion() >= 10) //Kitao�ǉ��Bv0.72�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(ReadData); //Kitao�ǉ��Bv0.72
	}
	else
	{
		if (Regs[VDC_MARR] < 0x8000)
		{
			pwVideoRam = (Uint16*)&VideoRam[0];
			ReadData = pwVideoRam[Regs[VDC_MARR]]; //v2.67�X�V
		}
		else
			ReadData = 0;
	}

	LOAD_V(ScreenW);
	LOAD_V(ScreenH);
	LOAD_V(BGH);
	LOAD_V(BGW);

	LOAD_V(VdcAddrInc);
	LOAD_V(VdcStatus);

	LOAD_V(_ClockCounter); //Kitao�ǉ�
	LOAD_V(_ScanLine);
	LOAD_V(RasterCounter);
	LOAD_V(bRasterRequested); //Kitao�ǉ�
	if (MAINBOARD_GetStateVersion() >= 7) //Kitao�ǉ��Bv0.62�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_bRasterLate);
	}
	else
		_bRasterLate = TRUE;
	LOAD_V(_DisplayCounter);
	LOAD_V(LineCounter);
	LOAD_V(LineCountMask);

	LOAD_V(bUpdateSATB);
	LOAD_V(bSpOver);
	if (MAINBOARD_GetStateVersion() >= 11) //Kitao�ǉ��Bv0.74�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(bOverlap);
	}
	else
		bOverlap = FALSE;
	LOAD_V(SpDmaCount);
	if (MAINBOARD_GetStateVersion() >= 16) //Kitao�ǉ��Bv0.87�ȍ~�̃Z�[�u�t�@�C���Ȃ�
		LOAD_V(SpDmaStole); //���o�[�W�����̏ꍇ�A���݂Ƃ͈Ⴄ���p�l�Ȃ̂Ŕ�g�p�B�_�~�[�ǂݍ��݁B
	if (MAINBOARD_GetStateVersion() >= 15) //Kitao�ǉ��Bv0.82�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(VramDmaCount);
	}
	else
		VramDmaCount = 0;
	LOAD_V(bBurstMode);
	LOAD_V(bMWRchange); //Kitao�ǉ�

	LOAD_V(VblankLine); //Kitao�ǉ�
	LOAD_V(TvStartLine); //Kitao�ǉ�
	LOAD_V(rasterTimingType); //Kitao�ǉ�
	if (_AutoRasterTimingType != 2) //��_RasterTimingType�������ύX���Ă���ꍇ�͓ǂݍ��܂��A���̂܂�_RasterTimingType���Œ肷��B
		VDC_SetRasterTiming(_AutoRasterTimingType); //�����ύX���Ă���Q�[���̏ꍇ
	else
		VDC_SetRasterTiming(rasterTimingType); //�����ύX���Ă��Ȃ������ꍇ
	LOAD_V(overClockType); //Kitao�ǉ�
	if ((overClockType < _AutoOverClock)||(_AutoOverClock == 0)) //�Q�[�����Ƃ̎����ݒ肪����΂����D�悷��B���łɃI�[�o�[�N���b�N���Ă����ꍇ�͂��̂܂܁B�m�[�}�������̃Q�[���͋�����(���ݖ��g�p)�B
		VDC_SetOverClock(_AutoOverClock);
	else
	{
		if (APP_GetLoadStateSpeedSetting()) //���x�ύX�ݒ�𔽉f����ݒ�̏ꍇ�B���f���Ȃ��ݒ�(�f�t�H���g)�̏ꍇ�́A����̃I�[�o�[�N���b�N�ݒ�������p���B�����Delete�L�[�������Ēm�炸�ɑ��x�ύX���Ă��܂��P�[�X������̂�v2.36����f�t�H���g�ł͔��f���Ȃ��悤�ɂ����B
			VDC_SetOverClock(overClockType);
	}
	LOAD_V(bPerformSpriteLimit); //Kitao�ǉ�
	if (!_bAutoPerformSpriteLimit) //��_bPerformSpriteLimit�������ύX���Ă���ꍇ�͓ǂݍ��܂��A���̂܂�_bPerformSpriteLimit���Œ肷��B
		VDC_SetPerformSpriteLimit(bPerformSpriteLimit); //�����ύX���Ă��Ȃ������ꍇ
	LOAD_V(waitPatch); //Kitao�ǉ��B���݃_�~�[�B_WaitPatch�̓Q�[���ŗL�̏����l�̂܂܂ɂ���B

	if (MAINBOARD_GetStateVersion() >= 8) //Kitao�ǉ��Bv0.64�ȍ~�̃Z�[�u�t�@�C���Ȃ�
		LOAD_V(popfulMail); //v0.83�����g�p

	//VDC�P�ڂ̕ϐ��ɓ��Ă͂߂�
	memcpy(_Regs, Regs, sizeof(Regs));
	_AR[0] = AR;
	memcpy(_VideoRam, VideoRam, sizeof(VideoRam));
	_ReadData[0] = ReadData;
	_ScreenW[0] = ScreenW;
	_ScreenH[0] = ScreenH;
	_BGH[0] = BGH;
	_BGW[0] = BGW;
	_VdcAddrInc[0] = VdcAddrInc;
	_VdcStatus[0] = VdcStatus;
	_RasterCounter[0] = RasterCounter;
	_bRasterRequested[0] = bRasterRequested;
	_LineCounter[0] = LineCounter;
	_LineCountMask[0] = LineCountMask;
	_LineOffset[0] = 0; //v1.30�ǉ�
	_bUpdateSATB[0] = bUpdateSATB;
	_SpDmaCount[0] = SpDmaCount;
	_SpDmaStole[0] = 0;
	_VramDmaCount[0] = VramDmaCount;
	_bVramDmaExecute[0] = FALSE;
	_bSpOver[0] = bSpOver;
	_bOverlap[0] = bOverlap;
	_bBurstMode[0] = bBurstMode;
	_bVDCAccessWait[0] = TRUE; //v2.08�ǉ�
	_bMWRchange[0] = bMWRchange;
	memcpy(_SpRam, SpRam, sizeof(SpRam));
	_TvStartLine[0] = TvStartLine;
	_VblankLine[0] = VblankLine;

	_VN=0; //Kitao�ǉ�
	if (VDW == 0) //v0.95�ȑO�̕s��΍�B��ʂ̏����������Ă��Ȃ��\�t�g(hes�t�@�C���Ȃ�)��0�̂܂ܕۑ����Ă��܂��Ă����̂ŁA�����l(239)������B
	{
		VDW = 239;
		VCR = 4;
		VPR = 0x0F02;
	}
	invalidate_tile_cache(); // remake all the bg and sp tiles
	if ((MWR & 9) == 9) //7MHz���[�h(��336)��bit0�������Ă����ꍇ�Bv2.66�X�V
		_MaxSpPerLine[_VN] = 14; //�X�v���C�g������14�����Bv2.63�ǉ�
	else
		_MaxSpPerLine[_VN] = 16; //�X�v���C�g������16����

	_bVDCleared[0] = FALSE; //v1.63�ǉ�

	//VCE.c �������֓����Bv1.11
	LOAD_V(_DCC);
	LOAD_V(_ColorTableAddr);
	if (MAINBOARD_GetStateVersion() >= 3) //Kitao�ǉ��Bv0.57�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_TvStartPos); //����set_TvWidth()�ōĐݒ肳��邽�߁A���ݔ�K�v�B�_�~�[�ǂݍ��݁Bv1.11
		LOAD_V(_TvWidth); //����set_TvWidth()�ōĐݒ肳��邽�߁A���ݔ�K�v�B�_�~�[�ǂݍ��݁B�Bv1.11
	}
	set_TvWidth(); //Kitao�ǉ��B_TvWidth,_TvStartPos,_TvMax���ŐV�̏�ԂɍX�V�B
	_VN=0;
	VDC_SetTvStartLine();
	_TvStartLineAdjust[_VN] = 0; //v2.47�ǉ�
	VDC_SetVblankLine(); //v2.48�ǉ��B�K�v
	_VblankLineTop[_VN] = _VblankLine[_VN]; //v1.19�ǉ�
	LOAD_A(_Palette333);
	LOAD_A(_PaletteBG); //v1.10�X�V
	LOAD_A(_PaletteSP); //v1.10�X�V
	LOAD_V(_ColorLatch);

	return TRUE;
}

/*-----------------------------------------------------------------------------
	[SaveState]
		��Ԃ��t�@�C���ɕۑ����܂��B 
-----------------------------------------------------------------------------*/
BOOL
VDC_SaveState(
	FILE*		p)
{
	Sint32	overClockType = _OverClockType;

	if (p == NULL)
		return FALSE;

	SAVE_A(_Regs);
	SAVE_A(_VideoRam);
	SAVE_A(_SpRam);

	SAVE_V(_AR);
	SAVE_V(_ReadData); //Kitao�ǉ��Bv0.72

	SAVE_V(_ScreenW);
	SAVE_V(_ScreenH);
	SAVE_V(_BGH);
	SAVE_V(_BGW);

	SAVE_V(_VdcAddrInc);
	SAVE_V(_VdcStatus);

	SAVE_V(_ClockCounter); //Kitao�ǉ�
	SAVE_V(_ScanLine);
	SAVE_V(_RasterCounter);
	SAVE_V(_bRasterRequested); //Kitao�ǉ�
	SAVE_V(_bRasterLate); //Kitao�ǉ��Bv0.62
	SAVE_V(_DisplayCounter);
	SAVE_V(_LineCounter);
	SAVE_V(_LineCountMask);
	SAVE_V(_LineOffset); //Kitao�ǉ��Bv1.30
	SAVE_V(_TvStartLine); //Kitao�ǉ��Bv2.47
	SAVE_V(_TvStartLineAdjust); //Kitao�ǉ��Bv2.47

	SAVE_V(_bUpdateSATB);
	SAVE_V(_bSpOver);
	SAVE_V(_bOverlap); //Kitao�ǉ��Bv0.74
	SAVE_V(_SpDmaCount);
	SAVE_V(_SpDmaStole);
	SAVE_V(_VramDmaCount); //Kitao�ǉ��Bv0.82
	SAVE_V(_bVramDmaExecute); //Kitao�ǉ��Bv1.02
	SAVE_V(_bBurstMode);
	SAVE_V(_bVDCAccessWait); //Kitao�ǉ��Bv2.08
	SAVE_V(_bMWRchange); //Kitao�ǉ�

	SAVE_V(_RasterTimingType); //Kitao�ǉ�
	SAVE_V(_AutoRasterTimingType); //v1.65�ǉ�
	if (_AutoOverClock != -1) //�����ŃI�[�o�[�N���b�N���Ă���Q�[���̏ꍇ�Bv2.20�ǉ�
		if (_OverClockType == _AutoOverClock)
			overClockType = 0; //�����Ɠ�����ԂȂ�A�m�[�}�����x�Ƃ��ăZ�[�u���Ă����B�����o�[�W�����Ŏ����I�[�o�[�N���b�N���Ȃ��ݒ�ɂ��Ă���肪�Ȃ��悤�ɁB
	SAVE_V(overClockType); //Kitao�ǉ�
	SAVE_V(_bPerformSpriteLimit); //Kitao�ǉ�
	SAVE_V(_WaitPatch); //Kitao�ǉ�
	SAVE_V(_bIRQ1CancelExecute);//Kitao�ǉ��Bv1.03�B���ݔ�g�p
	SAVE_V(_bVDCleared); //v1.63�ǉ�

	SAVE_A(_VPC); //Kitao�ǉ��Bv.0.89

	//VCE.c �������֓����Bv1.11
	SAVE_V(_DCC);
	SAVE_V(_ColorTableAddr);

	SAVE_A(_Palette333);
	SAVE_A(_PaletteBG); //v1.10�X�V
	SAVE_A(_PaletteSP); //v1.10�X�V

	SAVE_V(_ColorLatch);

	SAVE_A(_VpcPriority); //v0.89�ǉ�
	SAVE_V(_VpcBorder1); //v0.89�ǉ�
	SAVE_V(_VpcBorder2); //v0.89�ǉ�

	return TRUE;
}

/*-----------------------------------------------------------------------------
	[LoadState]
		��Ԃ��t�@�C������ǂݍ��݂܂��B 
-----------------------------------------------------------------------------*/
BOOL
VDC_LoadState(
	FILE*		p)
{
	Sint32	rasterTimingType;
	Sint32	autoRasterTimingType;
	BOOL	bPerformSpriteLimit;
	Sint32	waitPatch;
	Sint32	popfulMail;
	Sint32	overClockType;

	if (p == NULL)
		return FALSE;

	if (MAINBOARD_GetStateVersion() < 17) //Kitao�ǉ��Bv0.89���Â��Z�[�u�t�@�C���Ȃ�
	{
		return OldLoadState(p);
	}

	LOAD_A(_Regs);
	LOAD_A(_VideoRam);
	LOAD_A(_SpRam);

	LOAD_V(_AR);
	LOAD_V(_ReadData); //Kitao�ǉ��Bv0.72

	LOAD_V(_ScreenW);
	LOAD_V(_ScreenH);
	LOAD_V(_BGH);
	LOAD_V(_BGW);

	LOAD_V(_VdcAddrInc);
	LOAD_V(_VdcStatus);

	LOAD_V(_ClockCounter); //Kitao�ǉ�
	LOAD_V(_ScanLine);
	LOAD_V(_RasterCounter);
	LOAD_V(_bRasterRequested); //Kitao�ǉ�
	LOAD_V(_bRasterLate); //Kitao�ǉ��Bv0.62
	LOAD_V(_DisplayCounter);
	LOAD_V(_LineCounter);
	LOAD_V(_LineCountMask);
	if (MAINBOARD_GetStateVersion() >= 28) //Kitao�ǉ��Bv1.30�ȍ~�̃Z�[�u�t�@�C���Ȃ�
		LOAD_V(_LineOffset); //v2.09����t���[���I���ŕK��0�Ƀ��Z�b�g�����̂Ń_�~�[�ǂݍ��݁B
	_LineOffset[0] = 0;
	_LineOffset[1] = 0;
	if (MAINBOARD_GetStateVersion() >= 45) //Kitao�ǉ��Bv2.47�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_TvStartLine);
		LOAD_V(_TvStartLineAdjust);
	}
	else
	{
		if (MAINBOARD_GetStateVersion() == 44) //Kitao�ǉ��Bv2.47beta�̃Z�[�u�t�@�C���Ȃ�
		{
			LOAD_V(_TvStartLine); //�_�~�[�ǂݍ���
		}
		for (_VN=0; _VN<=_SuperGrafx; _VN++)
		{
			VDC_SetTvStartLine();
			_TvStartLineAdjust[_VN] = 0; //v2.47�ǉ�
		}
	}

	LOAD_V(_bUpdateSATB);
	LOAD_V(_bSpOver);
	LOAD_V(_bOverlap);
	LOAD_V(_SpDmaCount);
	if (MAINBOARD_GetStateVersion() < 22) //Kitao�ǉ��Bv1.00���O�̃Z�[�u�t�@�C���Ȃ�
		LOAD_V(_SpDmaStole);//�_�~�[�B���o�[�W������_SpDmaStole�͈Ⴄ�p�r�Ŏg���Ă����̂Ŕj���B
	_SpDmaStole[0] = 0;
	_SpDmaStole[1] = 0;
	if (MAINBOARD_GetStateVersion() >= 24) //Kitao�ǉ��Bv1.03�ȍ~�̃Z�[�u�t�@�C���Ȃ�
		LOAD_V(_SpDmaStole);
	LOAD_V(_VramDmaCount);
	if (MAINBOARD_GetStateVersion() >= 23) //Kitao�ǉ��Bv1.02�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_bVramDmaExecute);
	}
	else
	{
		_bVramDmaExecute[0] = FALSE;
		_bVramDmaExecute[1] = FALSE;
	}
	LOAD_V(_bBurstMode);
	if (MAINBOARD_GetStateVersion() >= 41) //v2.08�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_bVDCAccessWait);
	}
	else
	{
		_bVDCAccessWait[0] = TRUE;
		_bVDCAccessWait[1] = TRUE;
	}
	LOAD_V(_bMWRchange); //Kitao�ǉ�

	if (MAINBOARD_GetStateVersion() < 26) //Kitao�ǉ��Bv1.11���O�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_VblankLine);
		LOAD_V(_TvStartLine);
		for (_VN=0; _VN<=_SuperGrafx; _VN++)
		{
			VDC_SetTvStartLine(); //�ݒ肵�Ȃ���
			_TvStartLineAdjust[_VN] = 0; //v2.47�ǉ�
		}
	}
	LOAD_V(rasterTimingType); //Kitao�ǉ�
	if (_AutoRasterTimingType != 2) //��_RasterTimingType�������ύX���Ă���ꍇ�͓ǂݍ��܂��A���̂܂�_RasterTimingType���Œ肷��B
		VDC_SetRasterTiming(_AutoRasterTimingType); //�����ύX���Ă���Q�[���̏ꍇ
	else
		VDC_SetRasterTiming(rasterTimingType); //�����ύX���Ă��Ȃ������ꍇ
	if (MAINBOARD_GetStateVersion() >= 37) //Kitao�ǉ��Bv1.65�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(autoRasterTimingType);
		if ((autoRasterTimingType != 2)&&(_AutoRasterTimingType == 2)) //���o�[�W�����ł�_AutoRasterTimingType��ݒ肵�Ă����Q�[�����A���o�[�W�����ł̓m�[�}���ɂȂ����ꍇ�B
			VDC_SetRasterTiming(2); //�����Ńm�[�}���ɖ߂�
	}
	LOAD_V(overClockType); //Kitao�ǉ�
	if ((overClockType < _AutoOverClock)||(_AutoOverClock == 0)) //�Q�[�����Ƃ̎����ݒ肪����΂����D�悷��B���łɃI�[�o�[�N���b�N���Ă����ꍇ�͂��̂܂܁B�m�[�}�������̃Q�[���͋�����(���ݖ��g�p)�B
		VDC_SetOverClock(_AutoOverClock);
	else
	{
		if (APP_GetLoadStateSpeedSetting()) //���x�ύX�ݒ�𔽉f����ݒ�̏ꍇ�B���f���Ȃ��ݒ�(�f�t�H���g)�̏ꍇ�́A����̃I�[�o�[�N���b�N�ݒ�������p���B�����Delete�L�[�������Ēm�炸�ɑ��x�ύX���Ă��܂��P�[�X������̂�v2.36����f�t�H���g�ł͔��f���Ȃ��悤�ɂ����B
			VDC_SetOverClock(overClockType);
	}
	LOAD_V(bPerformSpriteLimit); //Kitao�ǉ�
	if (!_bAutoPerformSpriteLimit) //��_bPerformSpriteLimit�������ύX���Ă���ꍇ�͓ǂݍ��܂��A���̂܂�_bPerformSpriteLimit���Œ肷��B
		VDC_SetPerformSpriteLimit(bPerformSpriteLimit); //�����ύX���Ă��Ȃ������ꍇ
	LOAD_V(waitPatch); //Kitao�ǉ��B���݃_�~�[�B_WaitPatch�̓Q�[���ŗL�̏����l�̂܂܂ɂ���B
	if (MAINBOARD_GetStateVersion() >= 24) //Kitao�ǉ��Bv1.03�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_bIRQ1CancelExecute);//Kitao�ǉ��Bv1.03�B���ݔ�g�p�B
	}
	else
		_bIRQ1CancelExecute = FALSE;
	if (MAINBOARD_GetStateVersion() >= 36) //Kitao�ǉ��Bv1.63�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_bVDCleared);
	}
	else
	{
		_bVDCleared[0] = FALSE;
		_bVDCleared[1] = FALSE;
	}

	if (MAINBOARD_GetStateVersion() < 26) //Kitao�ǉ��Bv1.11���O�̃Z�[�u�t�@�C���Ȃ�
		LOAD_V(popfulMail); //�_�~�[�ǂݍ��݁B

	LOAD_A(_VPC); //Kitao�ǉ��Bv.0.89

	// remake all the bg and sp tiles
	for (_VN=0; _VN<=_SuperGrafx; _VN++) //Kitao�X�V
	{
		if (VDW == 0) //v0.95�ȑO�̕s��΍�B��ʂ̏����������Ă��Ȃ��\�t�g(hes�t�@�C���Ȃ�)��0�̂܂ܕۑ����Ă��܂��Ă����̂ŁA�����l(239)������B
		{
			VDW = 239;
			VCR = 4;
			VPR = 0x0F02;
		}
		invalidate_tile_cache();
		if ((MWR & 9) == 9) //7MHz���[�h(��336)��bit0�������Ă����ꍇ�Bv2.66�X�V
			_MaxSpPerLine[_VN] = 14; //�X�v���C�g������14�����Bv2.63�ǉ�
		else
			_MaxSpPerLine[_VN] = 16; //�X�v���C�g������16����
	}

	//VCE.c �������֓����Bv1.11
	LOAD_V(_DCC);
	LOAD_V(_ColorTableAddr);
	if ((MAINBOARD_GetStateVersion() >= 3)&&(MAINBOARD_GetStateVersion() <= 25)) //Kitao�ǉ��Bv0.57�`v1.10�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_TvStartPos); //����set_TvWidth()�ōĐݒ肳��邽�߁A���ݔ�K�v�B�_�~�[�ǂݍ��݁Bv1.11
		LOAD_V(_TvWidth); //����set_TvWidth()�ōĐݒ肳��邽�߁A���ݔ�K�v�B�_�~�[�ǂݍ��݁Bv1.11
	}
	set_TvWidth(); //Kitao�ǉ��B_TvWidth,_TvStartPos,_TvMax���ŐV�̏�ԂɍX�V�B
	VDC_SetVblankLine(); //v2.48�ǉ��B�K�v
	for (_VN=0; _VN<=_SuperGrafx; _VN++)  //Kitao�ǉ��BTvStartLine(�����\���J�n�ʒu)&VBlankLine���X�V(�X�p�O���̏ꍇVDC�Q�Ƃ��X�V)
		_VblankLineTop[_VN] = _VblankLine[_VN]; //v1.19�ǉ�
	LOAD_A(_Palette333);
	LOAD_A(_PaletteBG); //v1.10�X�V
	LOAD_A(_PaletteSP); //v1.10�X�V
	LOAD_V(_ColorLatch);

	if (MAINBOARD_GetStateVersion() >= 17) //Kitao�ǉ��Bv0.89�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_A(_VpcPriority);
		VDC_SetVpcPriority(); //v0.91���O��_VpcProprity�͎d�l���Ⴄ�̂ł����ŉ��߂čX�V����B
		LOAD_V(_VpcBorder1);
		LOAD_V(_VpcBorder2);
	}

	return TRUE;
}

#undef SAVE_V
#undef SAVE_A
#undef LOAD_V
#undef LOAD_A
