/******************************************************************************
Ootake
�EDirect3D�ł̕`��ɂ��Ή������BVista�Ή��B
�EWindow�\���ɂ�DirectDraw���g���悤�ɂ����B
�E���񂵋@�\��t�����B

Copyright(C)2006-2016 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[Screen.c]

	Implement ScreenInterface.

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
#include <math.h> //pow()�֐��ŕK�v
#include "Screen.h"
#include "ScreenDD.h"
#include "ScreenD3D.h"
//#include "GDIScreen.h"
#include "TIMER.h"
#include "VDC.h"
#include "CDROM.h"
#include "APU.h"
#include "App.h"
#include "MainBoard.h"
#include "WinMain.h"
#include "Printf.h"

Uint32 _Gamma[8]; //Kitao�ǉ��B�K���}���v�Z�������l�����Ă����Bv1.14�������BUint32�ɂ����ق����������������B
Uint32 _GammaS80[8]; //Kitao�ǉ��B�X�L�������C��80%�p
Uint32 _GammaS90[8]; //Kitao�ǉ��B�X�L�������C��90%�p
Uint32 _MonoTableR[256]; //���m�N���ϊ��p�e�[�u���B�������̂��ߕK�v�Bv2.28
Uint32 _MonoTableG[256]; //
Uint32 _MonoTableB[256]; //

static Sint32	_Width;
static Sint32	_Height;
static Sint32	_Magnification;	//������(Screen.cpp)�ł�_Magnification�̓X�N���[���V���b�g�p�\�������̂Ƃ��́A����ƈ�v���Ȃ����Ƃ�����̂Œ��ӁBv2.28�L
static Sint32	_BitsPerPixel;  //������(Screen.cpp)�ł�_BitsPerPixel�́A"DirectDraw�t���X�N���[���J���[�̐ݒ�"�̒l�ł����āA���ݕ\������BitsPerPixel�ƈ�v���Ă���Ƃ͌���Ȃ��̂Œ��ӁBv2.28�L
static Uint32	_Flags;

//Kitao�ǉ��Bv2.70
static Uint32	_SBSwapBuf[40*16]; //40(���h�b�g)*16(�c�h�b�g)*sizeof(Uint32)
static Uint32	_SBWorldStadium91[]   = {0x00030303,0x00070707,0x00000000,0x00000000,0x00070700,0x00070700};
static Uint32	_SBWorldStadium[]     = {0x00000006,0x00000002,0x00000002,0x00000002,0x00070700,0x00070700};
static Uint32	_SBWorldStadium2[]    = {0x00000006,0x00000002,0x00000002,0x00000500,0x00000500,0x00000500};
static Uint32	_SBPowerLeague34593[] = {0x00070701,0x00070701,0x00000000,0x00000000,0x00000000,0x00070701};
static Uint32	_SBPowerLeague2[]     = {0x00070701,0x00070701,0x00000000,0x00000000,0x00000000,0x00070701};
static Uint32	_SBPowerLeague[]      = {0x00010101,0x00060605,0x00060605,0x00060605,0x00060605,0x00010101};
static Uint32	_SBEikanKimi1[]       = {0x00070707,0x00000301,0x00000301,0x00000301,0x00070707};
static Uint32	_SBEikanKimi2[]       = {0x00060606,0x00000200,0x00000200,0x00000200,0x00060606};
static Uint32	_SBEikanKimi3[]       = {0x00050505,0x00000100,0x00000100,0x00000100,0x00050505};
static Uint32	_SBEikanKimi4[]       = {0x00040404,0x00000000,0x00000000,0x00000000,0x00040404};
static Uint32	_SBEikanKimi5[]       = {0x00030303,0x00000000,0x00000000,0x00000000,0x00030303};
static Uint32	_SBEikanKimi6[]       = {0x00020202,0x00000000,0x00000000,0x00000000,0x00020202};
static Uint32	_SBEikanKimi7[]       = {0x00010101,0x00000000,0x00000000,0x00000000,0x00010101};
static Uint32	_SBEikanKimi8[]       = {0x00000000,0x00010101,0x00010101,0x00000000,0x00000000};
static Uint32	_SBNaxatStadium[]     = {0x00050507,0x00050507,0x00050507,0x00050507,0x00050507,0x00000000};
static Uint32	_SBRomRomStadium[]    = {0x00000000,0x00000000,0x00070707,0x00070707,0x00070707,0x00000000};
static Uint32	_SBBaseballer1[]      = {0x00070707,0x00040507,0x00000202,0x00000202,0x00000202,0x00070707};
static Uint32	_SBBaseballer2[]      = {0x00040404,0x00020304,0x00000101,0x00000101,0x00000101,0x00040404};
static Uint32	_SBBaseballer3[]      = {0x00030303,0x00020303,0x00000101,0x00000101,0x00000101,0x00030303};
static Uint32	_SBKoregaPro1[]       = {0x00010204,0x00000000,0x00000000,0x00000000,0x00000000};
static Uint32	_SBKoregaPro2[]       = {0x00010203,0x00000000,0x00000000,0x00000000,0x00000000};
static Uint32	_SBKoregaPro3[]       = {0x00010202,0x00000000,0x00000000,0x00000000,0x00000000};
static Uint32	_SBKoregaPro4[]       = {0x00010101,0x00000000,0x00000000,0x00000000,0x00000000};
static Uint32	_SBKoregaPro5[]       = {0x00000103,0x00060606,0x00060606,0x00060606,0x00060606};
static Uint32	_SBKoregaPro6[]       = {0x00000002,0x00050505,0x00050505,0x00050505,0x00050505};
static Uint32	_SBKoregaPro7[]       = {0x00000001,0x00040404,0x00040404,0x00040404,0x00040404};
static Uint32	_SBKoregaPro8[]       = {0x00000000,0x00030303,0x00030303,0x00030303,0x00030303};
static Uint32	_SBKoregaPro9[]       = {0x00000000,0x00020202,0x00020202,0x00020202,0x00020202};
static Uint32	_SBKoregaProA[]       = {0x00000000,0x00010101,0x00010101,0x00010101,0x00010101};
static Uint32	_SBTheProYakyuu1[]    = {0x00000000,0x00070707,0x00070707,0x00070707,0x00070707};
static Uint32	_SBTheProYakyuu2[]    = {0x00000000,0x00060606,0x00060606,0x00060606,0x00060606};
static Uint32	_SBTheProYakyuu3[]    = {0x00000000,0x00050505,0x00050505,0x00050505,0x00050505};
static Uint32	_SBTheProYakyuu4[]    = {0x00000000,0x00040404,0x00040404,0x00040404,0x00040404};
static Uint32	_SBTheProYakyuu11[]   = {0x00000000,0x00070707,0x00070707,0x00000000,0x00070707};
static Uint32	_SBTheProYakyuu12[]   = {0x00000000,0x00060606,0x00060606,0x00000000,0x00060606};
static Uint32	_SBTheProYakyuu13[]   = {0x00000000,0x00050505,0x00050505,0x00000000,0x00050505};
static Uint32	_SBTheProYakyuu14[]   = {0x00000000,0x00040404,0x00040404,0x00000000,0x00040404};
static Uint32	_SBTheProYakyuu15[]   = {0x00000000,0x00030303,0x00030303,0x00000000,0x00030303};
static Uint32	_SBTheProYakyuu16[]   = {0x00000000,0x00020202,0x00020202,0x00000000,0x00020202};
static Uint32	_SBTheProYakyuu17[]   = {0x00000000,0x00010101,0x00010101,0x00000000,0x00010101};
static Uint32	_SBTheProYakyuu21[]   = {0x00000000,0x00000000,0x00070707,0x00070707,0x00000000};
static Uint32	_SBTheProYakyuu22[]   = {0x00000000,0x00000000,0x00060606,0x00060606,0x00000000};
static Uint32	_SBTheProYakyuu23[]   = {0x00000000,0x00000000,0x00050505,0x00050505,0x00000000};
static Uint32	_SBTheProYakyuu24[]   = {0x00000000,0x00000000,0x00040404,0x00040404,0x00000000};
static Uint32	_SBTheProYakyuu25[]   = {0x00000000,0x00000000,0x00030303,0x00030303,0x00000000};
static Uint32	_SBTheProYakyuu26[]   = {0x00000000,0x00000000,0x00020202,0x00020202,0x00000000};
static Uint32	_SBTheProYakyuu27[]   = {0x00000000,0x00000000,0x00010101,0x00010101,0x00000000};

//Kitao�ǉ��B���A�v���̃E�B���h�E�̏�Ԃ�ۑ����Ă������߂̕ϐ��Bv2.24
static HWND				_OtherAppWindowHWnd[512];
static WINDOWPLACEMENT	_OtherAppWindowPlacement[512];
static Sint32			_OtherAppWindowN;


//Kitao�ǉ��B�E�B���h�E�ʒu�ۑ��̂��߂̃R�[���o�b�N�Bv2.24
static BOOL
CALLBACK EnumWindowsSaveProc(HWND hWnd, LPARAM lParam)
{
	if ((IsWindowVisible(hWnd))&&(hWnd != WINMAIN_GetHwnd()))
	{
		if (_OtherAppWindowN < 512)
		{
			_OtherAppWindowHWnd[_OtherAppWindowN] = hWnd;
			_OtherAppWindowPlacement[_OtherAppWindowN].length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(hWnd, &_OtherAppWindowPlacement[_OtherAppWindowN]);
			_OtherAppWindowN++;
		}
	}
	return TRUE;
}

//Kitao�ǉ��B�E�B���h�E�ʒu�ۑ��Bv2.24
void
SCREEN_SaveWindowPosition()
{
	_OtherAppWindowN = 0;
	EnumWindows(EnumWindowsSaveProc, NULL);
	//PRINTF("WindowN %d",_OtherAppWindowN); //test
}

//Kitao�ǉ��B�E�B���h�E�ʒu��߂����߂̃R�[���o�b�N�Bv2.24
static BOOL
CALLBACK EnumWindowsLoadProc(HWND hWnd, LPARAM lParam)
{
	int		i;	

	for (i=0; i<_OtherAppWindowN; i++)
		if (_OtherAppWindowHWnd[i] == hWnd)
		{
			SetWindowPlacement(hWnd, &_OtherAppWindowPlacement[i]);
			break;
		}
	return TRUE;
}

//Kitao�ǉ��B�E�B���h�E�ʒu��߂��Bv2.24
void
SCREEN_LoadWindowPosition()
{
	EnumWindows(EnumWindowsLoadProc, NULL);
}


/*-----------------------------------------------------------------------------
	[Init]
		�X�N���[�����[�h��������(�ύX)���܂��B Kitao�X�V�Bv2.28
-----------------------------------------------------------------------------*/
BOOL
SCREEN_Init(
	Sint32		width,
	Sint32		height,
	Sint32		magnification, //Kitao�ǉ�
	Uint32		bitsPerPixel,
	Uint32		flags)
{
	BOOL	ret;
	Uint32	i;

	_Width = width;
	_Height = height;
	_Magnification = magnification; //Kitao�ǉ�
	_BitsPerPixel = bitsPerPixel;
	_Flags = flags;

	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			SCREEND3D_Deinit();
			ret = SCREEND3D_Init(_Width, _Height, _Magnification, _Flags);
			break;
		case 2: //DirectDraw
			SCREENDD_Deinit();
			ret = SCREENDD_Init(_Width, _Height, _Magnification, _BitsPerPixel, _Flags);
			break;
		default:
			ret = FALSE;
			break;
	}

	//���m�N���ϊ��p�e�[�u�����쐬�Bv2.28�ǉ�
	if ((APP_GetDrawMethod() == 2)&&(SCREENDD_GetBitsPerPixel() == 16))
	{	//16bit�J���[�iDirectDraw�̂݁j
		for (i=0; i<32; i++)
		{
			//R,G,B�̋P�x�𕽋ω����ă��m�N����
			_MonoTableR[i] = (Uint32)((pow((i * 0.298912) / 32.0, 1.0/1.076900) * 32.0)); //����ʂ̈Â���}���邽�߃K���}���グ��B
			_MonoTableG[i] = (Uint32)((pow((i * 0.586611) / 32.0, 1.0/1.076900) * 32.0)); //��RGB�������Ƃ��ɒl�I�[�o�[���Ȃ����߂ɏ����_�ȉ��͐؂�̂āB
			_MonoTableB[i] = (Uint32)((pow((i * 0.114478) / 32.0, 1.0/1.076900) * 32.0)); //��16bit�͐؂�̂Ă�ꂽ�Ԃ�̈Â����傫���̂ł������l�����ăK���}������B
		}
	}
	else
	{	//32bit�J���[
		for (i=0; i<256; i++)
		{
			//R,G,B�̋P�x�𕽋ω����ă��m�N����
			_MonoTableR[i] = (Uint32)((pow((i * 0.298912) / 256.0, 1.0/1.0752080) * 256.0)); //����ʂ̈Â���}���邽�߃K���}���グ��B
			_MonoTableG[i] = (Uint32)((pow((i * 0.586611) / 256.0, 1.0/1.0752080) * 256.0)); //��RGB�������Ƃ��ɒl�I�[�o�[���Ȃ����߂ɏ����_�ȉ��͐؂�̂āB
			_MonoTableB[i] = (Uint32)((pow((i * 0.114478) / 256.0, 1.0/1.0752080) * 256.0)); //
		}
	}

	return ret;
}


/*-----------------------------------------------------------------------------
	[Deinit]
		�X�N���[���̏I���������s�Ȃ��܂��B
-----------------------------------------------------------------------------*/
void
SCREEN_Deinit()
{
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			SCREEND3D_Deinit();
			break;
		case 2: //DirectDraw
			SCREENDD_Deinit();
			break;
	}
}


/*-----------------------------------------------------------------------------
	[ToggleFullScreen]
		�X�N���[�����E�C���h�E�^�t���X�N���[���ɐ؂�ւ��܂��D
-----------------------------------------------------------------------------*/
BOOL
SCREEN_ToggleFullScreen()
{
	if (_Flags & SCREEN_FFULLSCREEN)
		_Flags &= ~SCREEN_FFULLSCREEN;
	else
		_Flags |= SCREEN_FFULLSCREEN;
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			SCREEND3D_Deinit();
			return SCREEND3D_Init(_Width, _Height, _Magnification, _Flags);
		case 2: //DirectDraw
			SCREENDD_Deinit();
			return SCREENDD_Init(_Width, _Height, _Magnification, _BitsPerPixel, _Flags);
		default:
			return FALSE;
	}
}


/*-----------------------------------------------------------------------------
	[WaitVBlank]
		�����A�����Ԃ�҂��܂��B 
-----------------------------------------------------------------------------*/
//Kitao�X�V
BOOL
SCREEN_WaitVBlank(
	BOOL	bDraw) //bDraw��TRUE�ɂ��ČĂԂƕ`����s���BFALSE�̏ꍇVSync�҂��̂݁BDirect3D���p���p�BKitao�ǉ��B
{
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			return SCREEND3D_WaitVBlank(bDraw);
		case 2: //DirectDraw
			return SCREENDD_WaitVBlank(FALSE); //DirectDraw�̂Ƃ��͏�ɕ`��͍s���Ȃ��B
		default:
			return FALSE;
	}
}


void*
SCREEN_GetBuffer()
{
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			return SCREEND3D_GetBuffer();
		case 2: //DirectDraw
			return SCREENDD_GetBuffer();
		default:
			return NULL;
	}
}


const Sint32
SCREEN_GetBufferPitch()
{
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			return SCREEND3D_GetBufferPitch();
		case 2: //DirectDraw
			return SCREENDD_GetBufferPitch();
		default:
			return 0;
	}
}


//Kitao�ǉ��B�X�N���[���S�̂��N���A����B���Q�[����ʂ͈̔͊O�̕������܂߂āA�f�B�X�v���C�S�̂��N���A���܂��Bv1.43
void
SCREEN_Clear(
	byte	r,
	byte	g,
	byte	b) //v2.73�X�V�B�C�ӂ̐F�ŃN���A�ł���悤�ɂ����B��16�r�b�g���[�h�̂Ƃ��̓��m�N���ȊO���ƐF��������̂Ō��݂̓��m�N���Œ��r�̃f�[�^�̂ݎg�p�B
{
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			SCREEND3D_Clear(r,g,b);
			break;
		case 2: //DirectDraw
			SCREENDD_Clear(r,g,b);
			break;
	}
}


//Kitao�ǉ��B�Q�[����ʂ��w��F�ŃN���A����Bv2.77
void
SCREEN_Fill(
	Uint32	color)
{
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			SCREEND3D_Fill(color);
			break;
		case 2: //DirectDraw
			SCREENDD_Fill(color, TRUE);
			break;
	}
}


/*-----------------------------------------------------------------------------
	[Blt]
		pSrc ����o�b�N�o�b�t�@�։摜���������݂܂��B�g��^�k���A
	�ĂԑO�� SCREEN_Lock() ���܂��傤�B
-----------------------------------------------------------------------------*/
//Kitao�X�V�B���C�����Ƃɉ𑜓x��ς��Ă���Q�[��(���Ղ̌��C������120%�Ȃ�)�ɑΉ��B
void
SCREEN_Blt(
	Uint32*		pSrc,
	Sint32		srcX,
	Sint32		srcY,
	Uint16*		pSrcW,	//Kitao�X�V�B�]�����̉��s�N�Z�����B��srcH���C���̐��Ԃ�
	Sint32		srcH,	//Kitao�X�V�BdstW��dstH �̓J�b�g�����B(�����ŌŒ肹���A�l�X�ȑ傫���ł̃y�[�X�g�ɑΉ����邽��)
	Sint32		executeCode)  //Kitao�ǉ��B���s�R�[�h�B0�c�G���R�[�h�����s���B1�c�v���C�}����ʂ֓]�����s���B
							  //					   3�c���E�ɍ���(�I�[�o�[�X�L������)��z�u���Ă̓]��(���Ƃ�1�Ɠ���)
							  //					   5�c���E�̃I�[�o�[�X�L���������J�b�g���Ă̓]��(���Ƃ�1�Ɠ���)
{
	int		a,i;

	if (APP_GetStrikeBallSwap())
	{
		//���[���h�X�^�W�A��'91�ŃX�g���C�N�ƃ{�[���̕\�����X���b�v����Bv2.70
		if (MAINBOARD_GetWorldStadium91())
			if ((srcY <= 16+136)&&(srcY+srcH >= 16+144+7))
				if (memcmp(_SBWorldStadium91, pSrc+(16+136)*512+14, 4*6) == 0) //�X�g���C�N���\������Ă�����
				{
					for (i = 0; i < 8; i++)
						memcpy(_SBSwapBuf+i*40, pSrc+(16+136+i)*512+16, 4*32);
					for (i = 0; i < 8; i++)
						memcpy(pSrc+(16+136+i)*512+16, pSrc+(16+144+i)*512+16, 4*32);
					for (i = 0; i < 8; i++)
						memcpy(pSrc+(16+144+i)*512+16, _SBSwapBuf+i*40, 4*32);
				}
		//���[���h�X�^�W�A��(����)�ŃX�g���C�N�ƃ{�[���̕\�����X���b�v����Bv2.70
		if (MAINBOARD_GetWorldStadium())
			if ((srcY <= 16+136)&&(srcY+srcH >= 16+144+7))
				if (memcmp(_SBWorldStadium, pSrc+(16+136)*512+14, 4*6) == 0) //�X�g���C�N���\������Ă�����
				{
					for (i = 0; i < 8; i++)
						memcpy(_SBSwapBuf+i*40, pSrc+(16+136+i)*512+16, 4*32);
					for (i = 0; i < 8; i++)
						memcpy(pSrc+(16+136+i)*512+16, pSrc+(16+144+i)*512+16, 4*32);
					for (i = 0; i < 8; i++)
						memcpy(pSrc+(16+144+i)*512+16, _SBSwapBuf+i*40, 4*32);
				}
				//else if (memcmp(_SBWorldStadium2, pSrc+(16+144)*512+14, 4*6) == 0) //�{�[���J�E���g�������\������Ă����ꍇ�B��ł��c��Q�l�̂Ƃ��̃^�C�����ɕK�v�B
				//{
				//	for (i = 0; i < 8; i++)
				//		memcpy(pSrc+(16+144+i)*512+16, pSrc+(16+176+i)*512+16, 4*32); //�{�[���J�E���g�\���������B����͏����Ȃ��ق������R�Ȃ̂Ń{�c�B
				//}
		//�p���[���[�O�R,�S,�T,'93�ŃX�g���C�N�ƃ{�[���̕\�����X���b�v����Bv2.70
		if (MAINBOARD_GetPowerLeague34593())
			if ((srcY <= 16+136)&&(srcY+srcH >= 16+146+7))
				if (memcmp(_SBPowerLeague34593, pSrc+(16+137)*512+210, 4*6) == 0) //�X�g���C�N���\������Ă�����
				{
					for (i = 0; i < 8; i++)
						memcpy(_SBSwapBuf+i*40, pSrc+(16+136+i)*512+210, 4*8);
					for (i = 0; i < 8; i++)
						memcpy(_SBSwapBuf+(8+i)*40, pSrc+(16+146+i)*512+210, 4*8);
					for (i = 0; i < 8; i++)
						memcpy(pSrc+(16+136+i)*512+210, pSrc+(16+136+i)*512+222, 4*8);
					for (i = 0; i < 8; i++)
						memcpy(pSrc+(16+146+i)*512+210, pSrc+(16+146+i)*512+222, 4*8);
					for (i = 0; i < 8; i++)
						memcpy(pSrc+(16+136+i)*512+222, _SBSwapBuf+i*40, 4*8);
					for (i = 0; i < 8; i++)
						memcpy(pSrc+(16+146+i)*512+222, _SBSwapBuf+(8+i)*40, 4*8);
				}
		//�p���[���[�O�Q�ŃX�g���C�N�ƃ{�[���̕\�����X���b�v����Bv2.70
		if (MAINBOARD_GetPowerLeague2())
			if ((srcY <= 16+136)&&(srcY+srcH >= 16+144+7))
				if (memcmp(_SBPowerLeague2, pSrc+(16+137)*512+216, 4*6) == 0) //�X�g���C�N���\������Ă�����
				{
					for (i = 0; i < 8; i++)
						memcpy(_SBSwapBuf+i*40, pSrc+(16+136+i)*512+216, 4*32);
					for (i = 0; i < 8; i++)
						memcpy(pSrc+(16+136+i)*512+216, pSrc+(16+144+i)*512+216, 4*32);
					for (i = 0; i < 8; i++)
						memcpy(pSrc+(16+144+i)*512+216, _SBSwapBuf+i*40, 4*32);
				}
		//�p���[���[�O�̃X�R�A�{�[�h��ʂŁA�ŃX�g���C�N�ƃ{�[���̕\�����X���b�v����B�������̃J�E���g�̓X�v���C�g�Ȃ̂�VDC.cpp�ɂĂ����Ȃ��Bv2.70
		if (VDC_GetPowerLeague())
			if ((srcY <= 16+121)&&(srcY+srcH >= 16+129+7))
				if (memcmp(_SBPowerLeague, pSrc+(16+121)*512+145, 4*6) == 0) //�X�g���C�N���\������Ă�����
				{
					for (i = 0; i < 8; i++)
						memcpy(_SBSwapBuf+i*40, pSrc+(16+121+i)*512+144, 4*32);
					for (i = 0; i < 8; i++)
						memcpy(pSrc+(16+121+i)*512+144, pSrc+(16+129+i)*512+144, 4*32);
					for (i = 0; i < 8; i++)
						memcpy(pSrc+(16+129+i)*512+144, _SBSwapBuf+i*40, 4*32);
				}
		//�h���͌N�ɂ̃X�R�A�{�[�h��ʂŁA�X�g���C�N�ƃ{�[���̕\�����X���b�v����B�������̃J�E���g�̓X�v���C�g�Ȃ̂�VDP.cpp�ɂĂ����Ȃ��Bv2.70
		if (VDC_GetEikanKimi())
		{
			if ((srcY <= 16+9)&&(srcY+srcH >= 16+17+8)&&
				(memcmp(_SBEikanKimi1, pSrc+(16+10)*512+287, 4*5) == 0)) //�X�g���C�N���\������Ă�����B���`�[���ΐ�̃X�R�A�{�[�h�\����
			{
				for (i = 0; i < 8; i++)
					memcpy(_SBSwapBuf+i*40, pSrc+(16+9+i)*512+286, 4*32);
				for (i = 0; i < 8; i++)
					memcpy(pSrc+(16+9+i)*512+286, pSrc+(16+17+i)*512+286, 4*32);
				for (i = 0; i < 8; i++)
					memcpy(pSrc+(16+17+i)*512+286, _SBSwapBuf+i*40, 4*32);
			}
			else if ((srcY <= 16+9)&&(srcY+srcH >= 16+17+7)&&
					 ((memcmp(_SBEikanKimi8, pSrc+(16+21)*512+313, 4*5) == 0)||
					  (memcmp(_SBEikanKimi2, pSrc+(16+10)*512+287, 4*5) == 0)||
					  (memcmp(_SBEikanKimi3, pSrc+(16+10)*512+287, 4*5) == 0)||
					  (memcmp(_SBEikanKimi4, pSrc+(16+10)*512+287, 4*5) == 0)||
					  (memcmp(_SBEikanKimi5, pSrc+(16+10)*512+287, 4*5) == 0)||
					  (memcmp(_SBEikanKimi6, pSrc+(16+10)*512+287, 4*5) == 0)||
					  (memcmp(_SBEikanKimi7, pSrc+(16+10)*512+287, 4*5) == 0))) //�X�g���C�N���\������Ă�����B�����I����
			{
				for (i = 0; i < 8; i++)
					memcpy(_SBSwapBuf+i*40, pSrc+(16+9+i)*512+286, 4*32);
				for (i = 0; i < 8; i++)
					memcpy(pSrc+(16+9+i)*512+286, pSrc+(16+17+i)*512+286, 4*32);
				for (i = 0; i < 8; i++)
					memcpy(pSrc+(16+17+i)*512+286, _SBSwapBuf+i*40, 4*32);
			}
			else if ((srcY <= 16+7)&&(srcY+srcH >= 16+15+7)&&
					 ((memcmp(_SBEikanKimi8, pSrc+(16+19)*512+313, 4*5) == 0)||
					  (memcmp(_SBEikanKimi2, pSrc+(16+ 8)*512+287, 4*5) == 0)||
					  (memcmp(_SBEikanKimi3, pSrc+(16+ 8)*512+287, 4*5) == 0)||
					  (memcmp(_SBEikanKimi4, pSrc+(16+ 8)*512+287, 4*5) == 0)||
					  (memcmp(_SBEikanKimi5, pSrc+(16+ 8)*512+287, 4*5) == 0)||
					  (memcmp(_SBEikanKimi6, pSrc+(16+ 8)*512+287, 4*5) == 0)||
					  (memcmp(_SBEikanKimi7, pSrc+(16+ 8)*512+287, 4*5) == 0))) //�X�g���C�N���\������Ă�����B���`�[�����m�̑ΐ펞
			{
				for (i = 0; i < 8; i++)
					memcpy(_SBSwapBuf+i*40, pSrc+(16+7+i)*512+286, 4*32);
				for (i = 0; i < 8; i++)
					memcpy(pSrc+(16+7+i)*512+286, pSrc+(16+15+i)*512+286, 4*32);
				for (i = 0; i < 8; i++)
					memcpy(pSrc+(16+15+i)*512+286, _SBSwapBuf+i*40, 4*32);
			}
		}
		//�i�O�U�b�g�X�^�W�A��
		if (MAINBOARD_GetNaxatStadium())
		{
			if ((srcY <= 16+168)&&(srcY+srcH >= 16+176+7)&&
				(memcmp(_SBNaxatStadium, pSrc+(16+182)*512+17, 4*6) == 0)) //�A�E�g�J�E���g���\������Ă�����
			{
				for (i = 0; i < 8; i++)
					memcpy(_SBSwapBuf+i*40, pSrc+(16+168+i)*512+16, 4*32);
				for (i = 0; i < 8; i++)
					memcpy(pSrc+(16+168+i)*512+16, pSrc+(16+176+i)*512+16, 4*32);
				for (i = 0; i < 8; i++)
					memcpy(pSrc+(16+176+i)*512+16, _SBSwapBuf+i*40, 4*32);
			}
		}
		//ROMROM�X�^�W�A��
		if (CDROM_GetRomRomStadium())
		{
			if ((srcY <= 16+185)&&(srcY+srcH >= 16+193+7)&&
				(memcmp(_SBRomRomStadium, pSrc+(16+185)*512+16, 4*6) == 0)) //�X�g���C�N���\������Ă�����
			{
				if (*(pSrc+(16+185)*512+25) == 0x00000000) //��ŃE�B���h�E��\����
					a = 40;
				else
					a = 8;
				for (i = 0; i < 8; i++)
					memcpy(_SBSwapBuf+i*40, pSrc+(16+185+i)*512+16, 4*a);
				for (i = 0; i < 8; i++)
					memcpy(pSrc+(16+185+i)*512+16, pSrc+(16+193+i)*512+16, 4*a);
				for (i = 0; i < 8; i++)
					memcpy(pSrc+(16+193+i)*512+16, _SBSwapBuf+i*40, 4*a);
			}
		}
		//�M�����W�F���h�x�[�X�{�[���[
		if (CDROM_GetBaseballer())
		{
			if ((srcY <= 16+64)&&(srcY+srcH >= 16+72+7)&&
				((memcmp(_SBBaseballer1, pSrc+(16+65)*512+17, 4*6) == 0)||
				 (memcmp(_SBBaseballer2, pSrc+(16+65)*512+17, 4*6) == 0)||
				 (memcmp(_SBBaseballer3, pSrc+(16+65)*512+17, 4*6) == 0))) //�X�g���C�N���\������Ă���
			{
				for (i = 0; i < 8; i++)
					memcpy(_SBSwapBuf+i*40, pSrc+(16+64+i)*512+16, 4*32);
				for (i = 0; i < 8; i++)
					memcpy(pSrc+(16+64+i)*512+16, pSrc+(16+72+i)*512+16, 4*32);
				for (i = 0; i < 8; i++)
					memcpy(pSrc+(16+72+i)*512+16, _SBSwapBuf+i*40, 4*32);
			}
		}
		//���ꂪ�v���싅'89�����ꂪ�v���싅'90
		if (MAINBOARD_GetKoregaPro())
		{
			if ((srcY <= 16+144)&&(srcY+srcH >= 16+152+7)&&
				((memcmp(_SBKoregaPro1, pSrc+(16+153)*512+224, 4*5) == 0)|| //�{�[���̂R�ڂ̃J�E���g���\������Ă�����
				 (memcmp(_SBKoregaPro2, pSrc+(16+153)*512+224, 4*5) == 0)||
				 (memcmp(_SBKoregaPro3, pSrc+(16+153)*512+224, 4*5) == 0)||
				 (memcmp(_SBKoregaPro4, pSrc+(16+153)*512+224, 4*5) == 0)||
				 (memcmp(_SBKoregaPro5, pSrc+(16+145)*512+192, 4*5) == 0)|| //�X�g���C�N���\������Ă�����
				 (memcmp(_SBKoregaPro6, pSrc+(16+145)*512+192, 4*5) == 0)||
				 (memcmp(_SBKoregaPro7, pSrc+(16+145)*512+192, 4*5) == 0)||
				 (memcmp(_SBKoregaPro8, pSrc+(16+145)*512+192, 4*5) == 0)||
				 (memcmp(_SBKoregaPro9, pSrc+(16+145)*512+192, 4*5) == 0)||
				 (memcmp(_SBKoregaProA, pSrc+(16+145)*512+192, 4*5) == 0)))
			{
				for (i = 0; i < 8; i++)
					memcpy(_SBSwapBuf+i*40, pSrc+(16+144+i)*512+192, 4*40);
				for (i = 0; i < 8; i++)
					memcpy(pSrc+(16+144+i)*512+192, pSrc+(16+152+i)*512+192, 4*40);
				for (i = 0; i < 8; i++)
					memcpy(pSrc+(16+152+i)*512+192, _SBSwapBuf+i*40, 4*40);
			}
		}
		if (VDC_GetTheProYakyuu()) //�C���e�b�NCD�싅�R��i�U�E�v���싅�C�U�E�v���싅SUPER�C�U�E�v���싅SUPER'94�j
		{
			if ((srcY <= 16+113)&&(srcY+srcH >= 16+128)&&
				((memcmp(_SBTheProYakyuu1, pSrc+(16+113)*512+212, 4*5) == 0)||
				 (memcmp(_SBTheProYakyuu2, pSrc+(16+113)*512+212, 4*5) == 0)||
				 (memcmp(_SBTheProYakyuu3, pSrc+(16+113)*512+212, 4*5) == 0)||
				 (memcmp(_SBTheProYakyuu4, pSrc+(16+113)*512+212, 4*5) == 0))) //�Őȉ�ʂŃ{�[���J�E���g���\������Ă�����
			{
				if (*(pSrc+(16+120)*512+213) != 0x00000000) //�܂����C���̏ꍇ
				{
					memcpy(pSrc+(16+128)*512+212, pSrc+(16+120)*512+212, 4*2); //O(�A�E�g)�̍���w�i���C��
					*(pSrc+(16+120)*512+213) = 0x00000000; //B(�{�[��)�̍����w�i���C��
				}
			}
			if ((srcY <= 16+165)&&(srcY+srcH >= 16+169)&&
				((memcmp(_SBTheProYakyuu11, pSrc+(16+169)*512+38, 4*5) == 0)||
				 (memcmp(_SBTheProYakyuu12, pSrc+(16+169)*512+38, 4*5) == 0)||
				 (memcmp(_SBTheProYakyuu13, pSrc+(16+169)*512+38, 4*5) == 0)||
				 (memcmp(_SBTheProYakyuu14, pSrc+(16+169)*512+38, 4*5) == 0)||
				 (memcmp(_SBTheProYakyuu15, pSrc+(16+169)*512+38, 4*5) == 0)||
				 (memcmp(_SBTheProYakyuu16, pSrc+(16+169)*512+38, 4*5) == 0)||
				 (memcmp(_SBTheProYakyuu17, pSrc+(16+169)*512+38, 4*5) == 0))) //�t�B�[���h��ʂŃ{�[���J�E���g���\������Ă�����
			{
				if ((*(pSrc+(16+166)*512+62) != 0x00070003)&&
					((*(pSrc+(16+166)*512+62) != 0x00000000)||(*(pSrc+(16+169)*512+39) != 0x00070707))) //�s���N�F(������)�̃����i�[���f�B�X�e�B�l�[�V�����łȂ����or�t�F�[�h�A�E�g��
						*(pSrc+(16+166)*512+62) = *(pSrc+(16+169)*512+39); //VDC.cpp�ŏ����ł��Ȃ����������i���ۊԔ����j�������ŏ���
			}
			if ((srcY <= 16+174)&&(srcY+srcH >= 16+175)&&
				((memcmp(_SBTheProYakyuu21, pSrc+(16+175)*512+40, 4*5) == 0)||
				 (memcmp(_SBTheProYakyuu22, pSrc+(16+175)*512+40, 4*5) == 0)||
				 (memcmp(_SBTheProYakyuu23, pSrc+(16+175)*512+40, 4*5) == 0)||
				 (memcmp(_SBTheProYakyuu24, pSrc+(16+175)*512+40, 4*5) == 0)||
				 (memcmp(_SBTheProYakyuu25, pSrc+(16+175)*512+40, 4*5) == 0)||
				 (memcmp(_SBTheProYakyuu26, pSrc+(16+175)*512+40, 4*5) == 0)||
				 (memcmp(_SBTheProYakyuu27, pSrc+(16+175)*512+40, 4*5) == 0))) //�t�B�[���h��ʂŃX�g���C�N���\������Ă�����
			{
				memcpy(pSrc+(16+175)*512+47, pSrc+(16+174)*512+47, 4*3); //VDC.cpp�ŏ����ł��Ȃ����������i���X�^�P�ʂŃL�����F�������������Ă���j�������ŏ���
				memcpy(pSrc+(16+175)*512+53, pSrc+(16+174)*512+53, 4*3); //����
			}
		}
	}
	//Uint32* pT = pSrc+(16+113)*512+212; PRINTF("Color = %08X %08X %08X %08X %08X %08X", *pT,*(pT+1),*(pT+2),*(pT+3),*(pT+4),*(pT+5)); //Test�p

	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			SCREEND3D_Blt(pSrc, srcX, srcY, pSrcW, srcH, executeCode);
			break;
		case 2: //DirectDraw
			SCREENDD_Blt(pSrc, srcX, srcY, pSrcW, srcH, executeCode);
			break;
	}
}


//Kitao�ǉ��BVSync(�����A���҂�)���s�����ǂ�����ݒ�B���݂̃f�B�X�v���C�\������VSync���s���邩�ǂ����̃`�F�b�N���s���B
void
SCREEN_SetSyncTo60HzScreen(
	BOOL	bSyncTo60HzScreen)
{
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			SCREEND3D_SetSyncTo60HzScreen(bSyncTo60HzScreen);
			break;
		case 2: //DirectDraw
			SCREENDD_SetSyncTo60HzScreen(bSyncTo60HzScreen);
			break;
	}
}

//Kitao�ǉ��BVSync(�����A���҂�)���s���Ă��邩�ǂ����𓾂�i���݂̃f�B�X�v���C�\������VSync���s���邩�ǂ����̃`�F�b�N�𔽉f�����l�j�B
BOOL
SCREEN_GetSyncTo60HzScreen()
{
	BOOL	bSyncTo60HzScreen;

	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			bSyncTo60HzScreen = SCREEND3D_GetSyncTo60HzScreen();
			break;
		case 2: //DirectDraw
			bSyncTo60HzScreen = SCREENDD_GetSyncTo60HzScreen();
			break;
	}

	return bSyncTo60HzScreen;
}


//Kitao�ǉ��B�e�L�X�g���b�Z�[�W��ݒ�
void
SCREEN_SetMessageText(
	char*	pText)
{
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			SCREEND3D_SetMessageText(pText);
			break;
		case 2: //DirectDraw
			SCREENDD_SetMessageText(pText);
			break;
	}
}


//Kitao�ǉ��B�K���}�i���邳�����j���v�Z�ς݂̃e�[�u����p�ӁBv2.28�X�V�BDirect3D��DirectDraw�ŋ��p�ɂ����B
void
SCREEN_SetGamma(
	Sint32	scanLineType,
	Sint32	scanLineDensity) //�X�L�������C���̔Z�x(%)
{
	Sint32	magnification;
	Sint32	bitsPerPixel;
	int 	a,i;
	double	d = APP_GetGammaValue(); //�c���X�L�������C�����̊�{�K���}�l
	Sint32	b = APP_GetBrightValue(); //�u���C�g�l�X

	//��{�ݒ�ł͂Ȃ��A���ݎ��ۂɕ\������Ă���Magnification��BitsPerPixel���擾����Bv2.28
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			magnification = SCREEND3D_GetMagnification();
			bitsPerPixel = 32; //32bit�Œ�
			break;
		case 2: //DirectDraw
			magnification = SCREENDD_GetMagnification();
			bitsPerPixel = SCREENDD_GetBitsPerPixel();
			break;
		default:
			magnification = 2;
			bitsPerPixel = 32;
			break;
	}

	//���X�L�������C���̏ꍇ�A�X�L�������C���ňÂ��Ȃ�Ԃ�A�K���}�𖾂�߂ɂ���B�m���X�L�������C���̏ꍇ�A�K���}���Â߂ɂ���B
	if (magnification >= 2)
	{
		switch (scanLineType)
		{
			case 1: //�c���X�L�������C���i�f�t�H���g�j
				break;
			case 2: //�������X�L�������C��
			case 3: //�������X�L�������C���t�@�[�X�g
			case 4: //TV�X�L�������C��
			case 5: //�������X�L�������C���V���[�v
			case 6: //�������X�L�������C�����A�V���[�v
				d = (1-15/800)*d; // (1-15/800)*1.305 �c�����Ɣ�ׂĖ��邢�Ԃ������
				if (APP_GetOptimizeGamma())
					d = d * (1+(80-(double)scanLineDensity)*0.005); // �_�E���������邳�����グ��Bv2.35�X�V
				break;
			default: //�m���X�L�������C��(0,7,8)
				d = (1-95/800)*d; // (1-95/800)*1.305 �c�����Ɣ�ׂĖ��邢�Ԃ������
				break;
		}
	}
	else //�m���X�L�������C����������x1�̏ꍇ
		d = (1-95/800)*d; // (1-95/800)*1.305 �c�����Ɣ�ׂĖ��邢�Ԃ������

	if ((scanLineType >= 2)&&(scanLineType <= 6)) //���X�L�������C���̏ꍇ�Bv2.35�X�V
	{
		if (bitsPerPixel == 16)
		{
			for (i=0; i<=7 ; i++)
			{
				if (i == 0)
					a = 0; //���͐^������
				else
					a = (i << 2) + b; //+1�B��������������͈͂ŏ����߂ɂ����ق����ڂɂ����Ȃ��B
				_Gamma[i] = (Uint32)((pow((double)a / 32.0, 1.0/d) * 32.0) +0.5);
				_GammaS80[i] = (Uint32)((pow((double)a*((double)scanLineDensity / 100) / 32.0, 1.0/d) * 32.0) +0.5); //�X�L�������C���{���p
				_GammaS90[i] = (Uint32)((pow((double)a*((double)(scanLineDensity+(100-scanLineDensity)/2) / 100) / 32.0, 1.0/d) * 32.0) +0.5); //�X�L�������C���ƃh�b�g�̋��E�p
			}
		}
		else //32�r�b�g�J���[�̏ꍇ
		{
			for (i=0; i<=7 ; i++)
			{
				if (i == 0)
					a = 0; //���͐^������
				else
					a = (i << 5) + b; //+1�B��������������͈͂ŏ����߂ɂ����ق����ڂɂ����Ȃ��B
				_Gamma[i] = (Uint32)((pow((double)a / 256.0, 1.0/d) * 256.0) +0.5);
				_GammaS80[i] = (Uint32)((pow((double)a*((double)scanLineDensity / 100) / 256.0, 1.0/d) * 256.0) +0.5); //�X�L�������C���{���p
				_GammaS90[i] = (Uint32)((pow((double)a*((double)(scanLineDensity+(100-scanLineDensity)/2) / 100) / 256.0, 1.0/d) * 256.0) +0.5); //�X�L�������C���ƃh�b�g�̋��E�p
			}
		}
	}
	else //���X�L�������C���ȊO�̏ꍇ�B���X�L�������C��80%����Ƃ���Bv2.35�X�V
	{
		if (bitsPerPixel == 16)
		{
			for (i=0; i<=7 ; i++)
			{
				a = i*4 + (Sint32)((double)b/9 * ((double)i/7) + 0.5); //���͐^�����ɁB���͔���������͈͂ŏ����߂ɂ����ق����ڂɂ����Ȃ��Bv2.35�X�V
				_Gamma[i] = (Uint32)((pow((double)a / 32.0, 1.0/d) * 32.0) +0.5);
				_GammaS80[i] = (Uint32)((pow((double)a*0.80 / 32.0, 1.0/d) * 32.0) +0.5); //�X�L�������C��80%�p�i�X�L�������C���{���j
				_GammaS90[i] = (Uint32)((pow((double)a*0.90 / 32.0, 1.0/d) * 32.0) +0.5); //�X�L�������C��90%�p�i�X�L�������C���ƃh�b�g�̋��E�p�j
			}
		}
		else //32�r�b�g�J���[�̏ꍇ
		{
			for (i=0; i<=7 ; i++)
			{
				a = i*32 + (Sint32)((double)b * ((double)i/7) + 0.5); //���͐^�����ɁB���͔���������͈͂ŏ����߂ɂ����ق����ڂɂ����Ȃ��Bv2.35�X�V
				_Gamma[i] = (Uint32)((pow((double)a / 256.0, 1.0/d) * 256.0) +0.5);
				_GammaS80[i] = (Uint32)((pow((double)a*0.80 / 256.0, 1.0/d) * 256.0) +0.5); //�X�L�������C��80%�p�i�X�L�������C���{���j
				_GammaS90[i] = (Uint32)((pow((double)a*0.90 / 256.0, 1.0/d) * 256.0) +0.5); //�X�L�������C��90%�p�i�X�L�������C���ƃh�b�g�̋��E�p�j
			}
		}
	}
}


//Kitao�ǉ��B�O���VBlank�҂����I�����������Ԃ��B
DWORD
SCREEN_GetLastTimeSyncTime()
{
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			return SCREEND3D_GetLastTimeSyncTime();
		case 2: //DirectDraw
			return SCREENDD_GetLastTimeSyncTime();
		default:
			return 0;
	}
}


//Kitao�ǉ��B�X�N���[���V���b�g��Bitmap���������ށBv2.12
void
SCREEN_WriteScreenshot(
	FILE*	fp)
{
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			SCREEND3D_WriteScreenshot(fp);
			break;
		case 2: //DirectDraw
			SCREENDD_WriteScreenshot(fp);
			break;
	}
}


//Kitao�ǉ��B�`��{����ݒ肷��Bv2.36
void
SCREEN_SetMagnification(
	Sint32	magnification)
{
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			SCREEND3D_SetMagnification(magnification);
			break;
		case 2: //DirectDraw
			SCREENDD_SetMagnification(magnification);
			break;
	}
}


//Kitao�ǉ��B���ۂɁu�`�揈���Ŏg�p���Ă���v�`��{���𓾂�Bv2.36
Sint32
SCREEN_GetMagnification()
{
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			return SCREEND3D_GetMagnification();
		case 2: //DirectDraw
			return SCREENDD_GetMagnification();
	}
	return 0;
}


//Kitao�ǉ��B�`�掞�̃h�b�g�g�嗦��ݒ肷��B
void
SCREEN_SetPixelMagnification(
	Sint32*		wMag,
	Sint32*		hMag)
{
	Sint32		magnification;
	Sint32		scanLineType;

	//��{�ݒ�ł͂Ȃ��A���ݎ��ۂɕ\������Ă���Magnification���擾����Bv2.28
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			magnification = SCREEND3D_GetMagnification();
			break;
		case 2: //DirectDraw
			magnification = SCREENDD_GetMagnification();
			break;
		default:
			magnification = 2;
			break;
	}

	if (magnification >= 2) //x2�ȏ�̏ꍇ
	{
		scanLineType = APP_GetScanLineType();
		if ((scanLineType >= 1)&&(scanLineType <= 6)) //�X�L�������C��(�c���܂�)��
		{
			if ((scanLineType == 3)||(scanLineType == 4))
				*wMag = 1;
			else
				*wMag = 2; //x2�ȏ�����͂Q�{�h�b�g�Œ�B�i���x�A�b�v�{�g�傳�ꂽ�Ƃ��Ƀo�C���j�A�t�B���^�����������ɂ�����j
			*hMag = magnification; //�c�͔{���Ԃ�̃\�[�X��p�ӂ��ē]���B
		}
		else //�m���X�L�������C����
		{
			*wMag = 2;
			if (magnification == 2)
				*hMag = magnification; //�c�͔{���Ԃ�̃\�[�X��p�ӂ��ē]���B
			else
				*hMag = magnification-1; //3x,4x�̂Ƃ��́A���ꂼ��2x,3x�Ɋg��B�i�W���M�[�y�������x�A�b�v�j
		}
	}
	else //x1�̏ꍇ
		*wMag = *hMag = 1;
}


//Kitao�ǉ��B�Q�[����ʐ^�񒆂Ƀ��b�Z�[�W��\������Bv2.77
void
SCREEN_SetCenterText(
	char*	pText)
{
	switch (APP_GetDrawMethod())
	{
		case 1: //Direct3D
			SCREEND3D_SetCenterText(pText);
			break;
		case 2: //DirectDraw
			SCREENDD_SetCenterText(pText);
			break;
	}
}


//Kitao�ǉ��B�f�B�X�v���C�̐����������g���𑪒肵�ĕԂ��Bv2.43
Sint32
SCREEN_GetVerticalScanFrequency()
{
	Sint32	vsf = 0;
	Sint32	a;
	DWORD	t, t2;
	MSG		msg;

	MAINBOARD_ScreenClear();
	SCREEN_SetCenterText(" Checking Now... Please wait for 60 seconds. ");
	MAINBOARD_ScreenUpdateClear(); //�Q�[����ʂ̓N���A�B���b�Z�[�W�̂ݕ\������B�Q�[���J�n�O�ł��g����֐��B
	//return 0; //Test�p

	SCREEN_WaitVBlank(FALSE); //"�O��VBlank���I���������"���X�V���邽�߂ɕK�v�B
	t = timeGetTime();
	t2 = t + 60000;
	while (t2 < t) //�I���\�莞���̃^�C�}�[�J�E���^���I�[�o�[�t���[���Ă����ꍇ�A�J�n�\�莞���̃^�C�}�[�J�E���^��0�ɖ߂�܂ő҂B
	{
		SCREEN_WaitVBlank(FALSE); //"�O��VBlank���I���������"���X�V���邽�߂ɕK�v�B
		t = timeGetTime();
		t2 = t + 60000;
	}
	
	while (timeGetTime() <= t2)
	{
		vsf++;
		SetCursor(LoadCursor(NULL, IDC_WAIT)); //�J�[�\���������v�ɁB
		Sleep(12); //12�B�A��V-Sync�����ɂ��v���s�ǂ�h�����߃E�F�C�g���K�v(�Ƃ���V-Sync�ݒ�I�t���ɕK�v)�B11���ƌv���s��(�����茻��)���������B���܂�傫��Sleep����ƒx���}�V���ŋt�ɏ��������ɂ��v���s�ǁB
		SCREEN_WaitVBlank(FALSE);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	vsf -= 6; //�덷������̂��A-6�ł��傤�ǎ��ۂ̎��g���\�L(�f�B�X�v���C��info�{�^��)�Ɠ����ɂȂ����B�S�Ă̊��ł��ꂪ���Ă͂܂�Ȃ��ƈӖ����Ȃ��̂ŗv�m�F�B
	vsf = vsf * 10 / 6;
	//�l�̌ܓ�
	a = vsf % 10; //��̈ʂ�ޔ�
	vsf /= 10; //��̈ʂ��J�b�g
	if (a < 2)
		vsf *= 10;
	else if (a < 7)
		vsf = vsf * 10 + 5;
	else
		vsf = vsf * 10 + 10;

	SetCursor(LoadCursor(NULL, IDC_ARROW)); //�J�[�\�������ɖ߂�
	SCREEN_SetCenterText("");
	MAINBOARD_ScreenUpdateClear();

	return vsf;
}
