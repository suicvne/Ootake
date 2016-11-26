/******************************************************************************
Ootake
�EDirect3D�p��ScreenD3D.c����������߁ADirectDraw�p��ScreenDD.c�ɖ��O��ύX��
  ���B(���O���Ƀt�@�C������ׂ��Ƃ��A�C���Ȃǂ����₷���悤��)
�EWindow�\���ɂ�DirectDraw���g���悤�ɂ����B
�E���@��TV�ɂȂ����Ƃ��̉�ʂ̖��邳�ɋ߂Â��邽�߁A�K���}���グ�ĉ�ʂ𖾂�
  �������₷�������B
�E��ʂ��g�傷��Ƃ��ɁA�h�b�g�̃W���M�[���ڗ����Ȃ��悤�A����ʂ��ڂ₯�Ă�
  �܂�Ȃ��悤�ɁA�Ǝ��̊g�又��(����߂̃X�L�������C��������)�Ŋg�傷��悤
  �ɂ����B
�ETV���[�h��ǉ������Bv0.91
�E�f�B�X�v���C�̃��t���b�V�����[�g��60Hz�ł͂Ȃ������ꍇ�A�����I��VSync���I�t��
  ����悤�ɂ����B
�EDirectDraw��VSync�҂����s���ۂ�CPU�̗��p����100%��ԂɂȂ�̂ŁACPU�p���[��}
  ����ȓd�̓��[�h(��������◎����)��t�����B
�E���C�����Ƃɉ𑜓x��ς���Q�[��(���Ղ̌��C������120%��)�ɑΉ������Bv0.60
�E��L��[���C�����Ƃɉ𑜓x��ς��鏈��]�ŏd���Ȃ��Ă����̂ŁA���C�����Ƃ̉�
  �x�ύX���s���Ă��Ȃ��ʏ�̃Q�[���ł́A���̏������Ȃ����Ƃō����������Bv1.06
�E�X�N���[����Ƀe�L�X�g���b�Z�[�W�̕\�����ł���悤�ɂ����Bv0.64
�EDirectDraw��V-Sync�ŁAGetScanLine()���g���悤�ɂ����B���ɂ���ăT�E���h�Ƀm
  �C�Y�����邱�Ƃւ̑΍�Bv0.95�B���I�[�o�[���C���g�������̃\�t�g�𓯎��ɋN����
  ���Ƃ��ɋt�ɑ傫�ȃm�C�Y������I�ɍڂ��Ă��܂����̂Ō��ɖ߂����Bv0.97
�E�I�t�X�N���[���`��p�̃��������V�X�e���������Ɏ�邱�Ƃ��\�ɂ����B�W���M�[
  �͖ڗ����N�b�L�������掿���D�݂̏ꍇ�ɗ��p�Bv1.31

Copyright(C)2006-2016 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[SCREENDD.c]

	Implement ScreenInterface using Direct Draw.

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

#define DIRECTDRAW_VERSION	0x0900	//Kitao�X�V�B�h���C�o���ɂ���邩������Ȃ����ADirectDraw8�ȍ~��p�ɂ����ق����A���荞�ݏ����ɂ�����Ǝ��Ԃ������Ă����̂��������傫���オ�����B
									//			 8���9�̂ق����S�̂͌y�߂���8���ō������������BDirectX8�̃v���O���}����(��������nVidia�̋�����h���C�o)�͕`��ȊO�̕����������肵�ē��삷��悤�ɍ���Ă���Ă����̂����B
#define SOURCE_PITCH 		512		//Kitao�ǉ�

#include <ddraw.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "ScreenDD.h"
#include "Screen.h"
#include "WinMain.h"
#include "Printf.h"
#include "App.h"
#include "MainBoard.h"

extern Uint32 _Gamma[8]; //Kitao�ǉ��B�K���}���v�Z�������l�����Ă����Bv1.14�������BUint32�ɂ����ق����������������B
extern Uint32 _GammaS80[8]; //Kitao�ǉ��B�X�L�������C��80%�p
extern Uint32 _GammaS90[8]; //Kitao�ǉ��B�X�L�������C��90%�p
extern Uint32 _MonoTableR[256]; //���m�N���ϊ��p�e�[�u���B�������̂��ߕK�v�Bv2.28
extern Uint32 _MonoTableG[256]; //
extern Uint32 _MonoTableB[256]; //

/*--------------------------------------------------------------------------*
 *                           Static variables                               *
 *--------------------------------------------------------------------------*/
static LPDIRECTDRAW				_pDD         = NULL;  // DirectDraw object
static LPDIRECTDRAWCLIPPER		_pDC         = NULL;  // Kitao�ǉ��BDirectDraw clipper object
static LPDIRECTDRAWSURFACE		_pDDSPrimary = NULL;  // DirectDraw primary surface
static LPDIRECTDRAWSURFACE		_pDDSBack    = NULL;  // DirectDraw offscreen surface for BackBuffer
static LPDIRECTDRAWSURFACE		_pDDSText    = NULL;  // Kitao�ǉ��BDirectDraw offscreen surface for Text
static LPDIRECTDRAWSURFACE		_pDDS256     = NULL;  // Kitao�ǉ��BDirectDraw offscreen surface for 256WidthScreen

//Kitao�ǉ��B�ŏ��ɐݒ肵���l���c���Ă����č������B
static	DDSURFACEDESC	_ddsdPrimary;
static	DDSURFACEDESC	_ddsdBack;
static	DDSURFACEDESC	_ddsd256;

static LONG		_SurfacePitch = 0;

static Sint32	_Width;  // width of display
static Sint32	_Height; // height of display
static Sint32	_Magnification; //Kitao�ǉ�
static Uint32	_Flags;
static HWND		_hWnd; //Kitao�ǉ�
static Uint16*	_pScreenPixels;
static BOOL		_bChangedFullScreen = FALSE; //Kitao�ǉ�
static Sint32	_GameLeft;   //print_message()�ŕ\���ʒu����̂��߂ɁA�Q�[����ʓ]����̍��W���T���Ă����B
static Sint32	_GameRight;  //
static Sint32	_GameTop;    //
static Sint32	_GameBottom; //

//Win9x�p�ϐ��BKitao�ǉ�
static DWORD	_PrevWidth;
static DWORD	_PrevHeight;
static DWORD	_PrevBitsPerPixel;
static DWORD	_PrevFrequency;

static DWORD	_LastTimeSyncTime; //Kitao�ǉ��B�O��Sync�����Ƃ��̃^�C�}�[�J�E���g
static DWORD	_LastTimeSyncTime3; //3�t���[���P�ʂł́A�O��Sync�����Ƃ��̃^�C�}�[�J�E���g�Bv2.43
static DWORD	_Frame; //3�t���[���P�ʂ��v�邽�߂ł́A�O��Sync�����Ƃ��̃^�C�}�[�J�E���g�Bv2.43
static Sint32	_SyncAjust; //Kitao�ǉ��BVSync���I�t�̂Ƃ���1/60�b�Ԋu�ɂł��邾���߂Â��邽�߂̕ϐ��Bv1.67
static Sint32	_SyncAjust3; //v2.43�ǉ�
static BOOL		_bSyncTo60HzScreen = TRUE; //Kitao�ǉ�

static Sint32	_BitsPerPixel;
static Uint32	_Rmask;
static Uint32	_Gmask;
static Uint32	_Bmask;

static Uint32	_Rshift;
static Uint32	_Gshift;
//static Uint32	_Bshift;

//static BOOL	_bLocked = FALSE; //Kitao�X�V�B�v���C�}�������b�N����K�v���Ȃ��Ȃ����̂ŃJ�b�g�Bv1.39

static LONG		_Pitch;
static LONG		_Pitch2; //Kitao�ǉ��B //pitch��2�{�̒l�����Ă����B���x�A�b�v�p�B
static LONG		_Pitch3; //Kitao�ǉ��B //pitch��3�{�̒l�����Ă����B���x�A�b�v�p�B
static LONG		_Pitch4; //Kitao�ǉ��B //pitch��4�{�̒l�����Ă����B���x�A�b�v�p�B
static Uint32*	_pPixels; //v2.13�X�V�B32bit�P�ʂň����悤�ɂ����B(������)

static char*	_pMessageText = ""; //Kitao�ǉ��B�e�L�X�g���b�Z�[�W�\���p�o�b�t�@�B�k���i�擪��0�j�̏ꍇ�A���\���B
static char*	_pCenterText = ""; //�Z���^�[�e�L�X�g���b�Z�[�W�\���p�o�b�t�@�B�k���i�擪��0�j�̏ꍇ�A��\���B


/*-----------------------------------------------------------------------------
	[Deinit]
		Finished with all objects we use; release them
-----------------------------------------------------------------------------*/
void
SCREENDD_Deinit()
{
	if (_pDD != NULL)
	{
		if (_pDC != NULL) //Kitao�ǉ�
		{
			_pDDSPrimary->SetClipper(NULL);
			_pDC->Release();
			_pDC = NULL;
		}

		if (_pDDS256 != NULL) //Kitao�ǉ�
		{
			_pDDS256->Release();
			_pDDS256 = NULL;
		}

		if (_pDDSText != NULL) //Kitao�ǉ�
		{
			_pDDSText->Release();
			_pDDSText = NULL;
		}

		if (_pDDSBack != NULL)
		{
			_pDDSBack->Release();
			_pDDSBack = NULL;
		}

		if (_pDDSPrimary != NULL)
		{
			_pDDSPrimary->Release();
			_pDDSPrimary = NULL;
		}

		_pDD->Release();
		_pDD = NULL;
	}
}


static Uint32
get_shift(
	Uint32		mask)
{
	Uint32		i;

	for (i = 0; i < 32; i++)
		if (mask & (1 << i))
			return i;

	return 0;
}


//Kitao�ǉ�
static BOOL
lock_screen256_surface(
	LONG*		pPitch,
	Uint32**	ppPixels)
{
	HRESULT		hRet;
	int			trial = 10;

	while (trial--)
	{
		hRet = _pDDS256->Lock(NULL, &_ddsd256, DDLOCK_WAIT, NULL);
		if (hRet == DD_OK)
		{
			*pPitch = _ddsd256.lPitch >> 2; //���P���C���̃o�C�g���B32bit�P�ʂň������߂�4�Ŋ����Ă����Bv2.77�X�V;
			*ppPixels = (Uint32*)_ddsd256.lpSurface;
			return TRUE;
		}
		else if (hRet == DDERR_SURFACELOST)
		{
			_pDDS256->Restore();
		}
    }

	return FALSE;
}


/*-----------------------------------------------------------------------------
	[Init]
		�X�N���[�������������܂��B 
-----------------------------------------------------------------------------*/
BOOL
SCREENDD_Init(
	Sint32		width,
	Sint32		height,
	Sint32		magnification, //Kitao�ǉ�
	Sint32		bitsPerPixel,
	Uint32		flags) //Kitao�ǉ�
{
	int				i,j;
	HRESULT			hRet;
	DDSURFACEDESC	ddsd;
	HWND			hWnd = WINMAIN_GetHwnd();
	int 			a; //Kitao�ǉ�
	DEVMODE			dm; //Kitao�ǉ�
	LONG			pitch;
	Uint32*			pPixels;
	Uint32*			pPixels0;

	hRet = DirectDrawCreate(NULL, &_pDD, NULL);
	if (hRet != DD_OK)
	{
		MessageBox(hWnd, "ERROR: DIRECTDRAW::DirectDrawCreate() failed.    ", "Ootake", MB_OK); //Kitao�ǉ�
		return FALSE;
	}

	// �������x����ݒ肷��B 
	if (flags & SCREEN_FFULLSCREEN) //Kitao�ǉ��B�t���X�N���[�����[�h�Ȃ�
		hRet = _pDD->SetCooperativeLevel(hWnd, DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
	else//Window���[�h�Ȃ�
		hRet = _pDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL);
	if (hRet != DD_OK)
	{
		MessageBox(hWnd, "ERROR: DIRECTDRAW::SetCooperativeLevel() failed.    ", "Ootake", MB_OK); //Kitao�X�V
		return FALSE;
	}

	// ��ʂ̉𑜓x��ݒ肷��B
	//  Kitao�X�V�B�E�B���h�E�X�^�C���̕ύX�͉�ʂ̉𑜓x��ς��Ă���ɂ����B
	//			   ��𑜓x���獂�𑜓x�ɐ؂�ւ����ꍇ�ɁA���̃A�v���̃E�B���h�E���k��ł��܂����Ƃ����������������Bv0.95
	if (flags & SCREEN_FFULLSCREEN) //Kitao�ǉ��B�t���X�N���[�����[�h�Ȃ�
	{
		if (_bChangedFullScreen == FALSE) //�E�B���h�E(�f�X�N�g�b�v)���t���X�N���[���ւ̐؂�ւ���
		{
			//���̃A�v���̃E�B���h�E�̏�Ԃ�ۑ����Ă����Bv2.24
			SCREEN_SaveWindowPosition();
			//Windows98/Me�̏ꍇ�ACDS_FULLSCREEN�������Ȃ��A�f�X�N�g�b�v�ɖ߂�Ȃ��̂ŁA�蓮�Ō��ɖ߂����ߕύX�O�̐ݒ��ޔ����Ă����B
			if (APP_GetWindows9x())
			{
				memset(&dm, 0, sizeof(DEVMODE));
				dm.dmSize = sizeof(DEVMODE);
				EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
				_PrevWidth = dm.dmPelsWidth;
				_PrevHeight = dm.dmPelsHeight;
				_PrevBitsPerPixel = dm.dmBitsPerPel;
				_PrevFrequency = dm.dmDisplayFrequency;
			}
		}
		memset(&dm, 0, sizeof(DEVMODE));
		dm.dmSize = sizeof(DEVMODE);
		dm.dmPelsWidth = width;
		dm.dmPelsHeight = height;
		dm.dmBitsPerPel = bitsPerPixel;
		dm.dmDisplayFrequency = 60;
		dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;
		if ((APP_GetResolutionAutoChange())&&(_bChangedFullScreen))
			ChangeDisplaySettings(&dm, 0); //�ݒ���T�����ɐؑցB�ꕔ�̊��Őؑ֎��̂������������Bv2.23�B�Â�RADEON�Ő؂�ւ����ɉ摜�̗�������m�F�ς݁Bv2.65
		else //�ʏ�
			ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
		WINMAIN_SetFullScreenWindow(width, height);//v2.23�ǉ��B���̃^�C�~���O�ŁA�E�B���h�E�X�^�C���̕ύX���s���悤�ɂ����B�p���[�̖����}�V���ł�DirectX�������Ɏ��Ԃ��|����̂ł��̃^�C�~���O�ŉ�ʂ𐮂����ق����ǂ������B
		_bChangedFullScreen = TRUE;
	}
	else //Kitao�ǉ��B�E�B���h�E���[�h�Ȃ�
	{
		if (_bChangedFullScreen) //�t���X�N���[�����E�B���h�E�ւ̐؂�ւ���
		{
			if (APP_GetWindows9x()) //Windows98/Me�̏ꍇ�ACDS_FULLSCREEN�������Ȃ��A�����Ńf�X�N�g�b�v�����̏�Ԃɖ߂��Ȃ��̂ŁA�蓮�Ō��ɖ߂��B
			{
				memset(&dm, 0, sizeof(DEVMODE));
				dm.dmSize = sizeof(DEVMODE);
				dm.dmPelsWidth = _PrevWidth;
				dm.dmPelsHeight = _PrevHeight;
				dm.dmBitsPerPel = _PrevBitsPerPixel;
				dm.dmDisplayFrequency = _PrevFrequency;
				dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;
				ChangeDisplaySettings(&dm, 0);		
			}
			else //Windows XP/2000/Vista�ȍ~�̏ꍇ	
				ChangeDisplaySettings(NULL, 0); //�f�X�N�g�b�v�����ɖ߂�
			SCREEN_LoadWindowPosition(); //���̃A�v���̃E�B���h�E��Ԃ����ɖ߂��Bv2.24
			Sleep(1000); //���ɂ���ẮA�f�X�N�g�b�v�ɖ߂�܂ŃE�F�C�g�����Ȃ���DIRECTDRAW��Create�o���Ȃ����Ƃ�����Bv1.61
		}
		WINMAIN_SetNormalWindow(width, height);//v2.23�ǉ��B���̃^�C�~���O�ŁA�E�B���h�E�X�^�C���̕ύX���s���悤�ɂ����B�p���[�̖����}�V���ł�DirectX�������Ɏ��Ԃ��|����̂ł��̃^�C�~���O�ŉ�ʂ𐮂����ق����ǂ������B
		APP_WindowWithinScreen(); //�E�B���h�E����ʂ���͂ݏo���Ă����ꍇ�A��ʓ��Ɏ��܂�悤�Ɉړ�����B
		_bChangedFullScreen = FALSE;
	}

	// �v���C�}���T�[�t�F�X���쐬����
	ZeroMemory(&_ddsdPrimary, sizeof(_ddsdPrimary));
	_ddsdPrimary.dwSize = sizeof(_ddsdPrimary);
	_ddsdPrimary.dwFlags = DDSD_CAPS;
	_ddsdPrimary.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_VIDEOMEMORY;
	hRet = _pDD->CreateSurface(&_ddsdPrimary, &_pDDSPrimary, NULL);
	if (hRet != DD_OK)
	{
		MessageBox(hWnd, "ERROR: DIRECTDRAW::CreateSurface() failed.    ", "Ootake", MB_OK); //Kitao�X�V
		SCREENDD_Deinit();
		return FALSE;
	}

    // �I�t�X�N���[���T�[�t�F�X���쐬����
	ZeroMemory(&_ddsdBack, sizeof(_ddsdBack));
	_ddsdBack.dwSize = sizeof(_ddsdBack);
	_ddsdBack.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	if (APP_GetUseVideoCardMemory())
		_ddsdBack.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
	else
		_ddsdBack.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY; //�V�X�e���������𗘗p(�V���[�v���d��)�Bv1.31�ǉ�
	if (magnification == 1)
	 a = 512;
	else //2�{�ȏ�͑S�ĉ�2�{�B���x�A�b�v�{�������邱�ƂœK�x�Ƀo�C���j�A�t�B���^���|���肢�������ɂȂ�
	 a = 512*2;
	_ddsdBack.dwWidth = a;
	_ddsdBack.dwHeight = 256*magnification; //�I�[�o�[�X�L�����p��256�܂ŗp�ӁB�㑤�̃I�[�o�[�X�L�����̈��241�`256���C���ڂ̗̈���g�p����Bv1.43
	hRet = _pDD->CreateSurface(&_ddsdBack, &_pDDSBack, NULL);
	if (hRet != DD_OK)
	{
		MessageBox(hWnd, "ERROR: DIRECTDRAW::CreateSurface(Back) failed.    ", "Ootake", MB_OK); //Kitao�X�V
		SCREENDD_Deinit();
		return FALSE;
	}

    // Kitao�ǉ��B�e�L�X�g�\���p�I�t�X�N���[���T�[�t�F�X���쐬����
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY; //�e�L�X�g�̓{�����ēǂ݂ɂ����Ȃ�Ȃ��悤�ɃV�X�e����������ɍ쐬
	ddsd.dwWidth = 512*2;
	ddsd.dwHeight = 32;
	_pDD->CreateSurface(&ddsd, &_pDDSText, NULL);

    // Kitao�ǉ��B��256�h�b�g�ėp�\���p�I�t�X�N���[���T�[�t�F�X���쐬����
	ZeroMemory(&_ddsd256, sizeof(_ddsd256));
	_ddsd256.dwSize = sizeof(_ddsd256);
	_ddsd256.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	_ddsd256.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY; //�������{�����ēǂ݂ɂ����Ȃ�Ȃ��悤�ɃV�X�e����������ɍ쐬
	_ddsd256.dwWidth = 256;
	_ddsd256.dwHeight = 224;
	_pDD->CreateSurface(&_ddsd256, &_pDDS256, NULL);

	if (!flags & SCREEN_FFULLSCREEN) //Kitao�ǉ��B�E�B���h�E���[�h�Ȃ�
	{
		//�N���b�p�[��p�� 
		hRet = _pDD->CreateClipper(0, &_pDC, NULL);
		if (hRet != DD_OK)
		{
			MessageBox(hWnd, "ERROR: DIRECTDRAW::CreateClipper failed.    ", "Ootake", MB_OK); //Kitao�X�V
			SCREENDD_Deinit();
			return FALSE;
		}
		//�N���b�p�[�ɃE�B���h�E���֘A�t��
		hRet = _pDC->SetHWnd(0, hWnd);
		if (hRet != DD_OK)
		{
			MessageBox(hWnd, "ERROR: DIRECTDRAW::SetHWnd failed.    ", "Ootake", MB_OK); //Kitao�X�V
			SCREENDD_Deinit();
			return FALSE;
		}
		//�T�[�t�F�X�ɃN���b�p�[���֘A�t��
		hRet = _pDDSPrimary->SetClipper(_pDC);
		if (hRet != DD_OK)
		{
			MessageBox(hWnd, "ERROR: DIRECTDRAW::SetClipper failed.    ", "Ootake", MB_OK); //Kitao�X�V
			SCREENDD_Deinit();
			return FALSE;
		}
     }

	// Get pixel format 
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_PIXELFORMAT | DDSD_CAPS;
	_pDDSPrimary->GetSurfaceDesc(&ddsd);

	_BitsPerPixel = ddsd.ddpfPixelFormat.dwRGBBitCount;
	_Rmask = ddsd.ddpfPixelFormat.dwRBitMask;
	_Gmask = ddsd.ddpfPixelFormat.dwGBitMask;
	_Bmask = ddsd.ddpfPixelFormat.dwBBitMask;

	// Rshift, Gshift, Bshift �����߂�BKitao�X�V
	_Rshift = get_shift(_Rmask);
	if (_Rshift == 10) //RGB555�̂Ƃ�
		_Gshift = 5;
	else //RGB565�̂Ƃ�
		_Gshift = 6;

	// Save our screen resolution
	_Width = width;
	_Height = height;
	_Magnification = magnification;//Kitao�ǉ�
	_Flags = flags;
	_hWnd =	hWnd;

	//Kitao�ǉ��B�K���}�i���邳�����j���v�Z�ς݂̃e�[�u����p�ӁB
	SCREEN_SetGamma(APP_GetScanLineType(), APP_GetScanLineDensity());

	// ��ʃN���A�p�Ɏg�����߁A�I�t�X�N���[��256���N���A���Ă����B
	if (lock_screen256_surface(&pitch, &pPixels))
	{
		pPixels0 = pPixels;
		for (i = 0; i < 224; i++)
		{
			pPixels = pPixels0;
			if (_BitsPerPixel == 16)
			{
				for (j = 0; j < 128; j++)
					*pPixels++ = 0; //4byte�Ԃ�(���Q�h�b�g)�������܂��B
			}
			else
			{
				for (j = 0; j < 256; j++)
					*pPixels++ = 0; //4byte�Ԃ�(���P�h�b�g)�������܂��B
			}
			pPixels0 += pitch;
		}
		_pDDS256->Unlock(NULL);
	}

	_LastTimeSyncTime = timeGetTime(); //Kitao�ǉ��B�O��Sync�����Ƃ��̃^�C�}�[�J�E���g
	_LastTimeSyncTime3 = _LastTimeSyncTime; //v2.43�ǉ�
	_SyncAjust  = 0; //VSync���I�t�̂Ƃ���1/60�b�Ԋu�ɂł��邾���߂Â��邽�߂̕ϐ��Bv1.67
	_SyncAjust3 = 0; //v2.43�ǉ�
	_Frame = 0; //v2.43�ǉ�

	return TRUE;
}


/*-----------------------------------------------------------------------------
	[ChangeMode]
		�X�N���[�����[�h��ύX���܂��B 
-----------------------------------------------------------------------------*/
BOOL
SCREENDD_ChangeMode(
	Sint32		width,
	Sint32		height,
	Sint32		magnification, //Kitao�ǉ�
	Sint32		bitsPerPixel,
	Uint32		flags)
{
	SCREENDD_Deinit();
	return SCREENDD_Init(width, height, magnification, bitsPerPixel, flags);
}


/*-----------------------------------------------------------------------------
	[WaitVBlank]
		�����A�����Ԃ�҂��܂��B 
-----------------------------------------------------------------------------*/
//�����A�����Ԃ�҂��܂��B(VSync����)
BOOL
SCREENDD_WaitVBlank(
	BOOL	bDraw) //bDraw�cDirect3D�p�ɒǉ������p���[���[�^�BTRUE�ɐݒ肵�Ă������ł͏�ɕ`��͍s���Ȃ��BKitao�ǉ�
{
	Sint32	t;

	//Kitao�X�V
	if (_bSyncTo60HzScreen)
	{
		t = timeGetTime() - _LastTimeSyncTime;
		if (t <= 16) //v1.09�ǉ��B17ms(1/60s=16.7ms)�ȏ�o�߂��Ă����ꍇ�͑҂��Ȃ��B(timeGetTime()�̌덷������̂�t=17�ł��܂�16.1ms�o�߂̂��Ƃ����邪��x�҂����Ȃ����Ƃ�D��j
		{
			//Kitao�ǉ��B���̃A�v���̂��߂ɏ�������x�݁B����������Ȃ���WaitForVerticalBlank()�ő҂��Ă���Ԃ�CPU��L����100%�ɂȂ�B
			t = 16 - t - 11; //-11�͏����������Ȃ����߂̃}�[�W���B-11OK�B-10�ق�OK�B-9�ȉ����ƃe���|�̗h�炬����킸���ɉ����U��C������B16=�P�R�}�̎��Ԗ�16ms�BSleep()�͂ǂ����Ă��傫�Ȍ덷���o��Ƃ�������悤���B
			if ((t >= 1)&&(t <= 16-11)) //�^�C�}�[�J�E���^�̃I�[�o�[�t���[���l���āA���͈̔͂̂Ƃ�����Sleep�������Ȃ��B
				Sleep(t);
			//�҂�
			_pDD->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN, NULL);
		}
		_LastTimeSyncTime = timeGetTime(); //�O���Sync���I������^�C���Ƃ��ċL�^���Ă���
		return TRUE;
	}
	else //_bSyncTo60HzScreen �� FALSE�̏ꍇ�BKitao�X�V�B����60fps��p�Ƃ��ăV���v���������Bv1.67
	{
		t = timeGetTime() - _LastTimeSyncTime;
		if (t <= 16) //17ms(1/60s=16.7ms)�ȏ�o�߂��Ă����ꍇ�͑҂��Ȃ��B(timeGetTime()�̌덷������̂�t=17�ł��܂�16.1ms�o�߂̂��Ƃ����邪��x�҂����Ȃ����Ƃ�D��j
		{
			//�҂�
			t = 16 - t; //16=�P�R�}�̎��Ԗ�16ms
			if (_SyncAjust == 0)
				t--; //Sleep�̌덷�ŏ������������Ȃ����߂̃}�[�W���B������16.7ms�ȏ�o�߂��Ă��܂���12�t���[��(200.0ms)���̒��K���킹�����܂������Ȃ����߁A���ꂪ�K�v�B
			if ((t >= 1)&&(t <= 16)) //�^�C�}�[�J�E���^�̃I�[�o�[�t���[���l���āA���͈̔͂̂Ƃ�����Sleep�������Ȃ��B
				Sleep(t);
			if (++_SyncAjust == 4)
				_SyncAjust = 0; //4���1�񂾂�Sleep��Z�߂ɂ���B����ő����̊���59.9Hz�O��ɋ߂Â���(�����̊�)�B
		}
		if ((_Frame % 12) == 11) //Sleep�̌덷�����炷���߁A12�t���[��(200.0ms)�ɂP��A���K���킹���s���Bv2.43
		{
			t = timeGetTime() - _LastTimeSyncTime3;
			if (t <= 200) //201ms�ȏ�o�߂��Ă����ꍇ�͑҂��Ȃ�
			{
				//�҂�
				t = 200 - t; //200=12�R�}�̎���200.0ms�B
				if (_SyncAjust3 == 0)
					t--; //�����59.95Hz�ɋ߂Â���(�����̊�)�B
				if (t>16) t=16;
				if ((t >= 1)&&(t <= 16)) //�^�C�}�[�J�E���^�̃I�[�o�[�t���[���l���āA���͈̔͂̂Ƃ�����Sleep�������Ȃ��B
					Sleep(t);
				if (++_SyncAjust3 == APP_GetNonVSyncTiming())
					_SyncAjust3 = 0; //10(APP_GetNonVSyncTiming())���1�񂾂�Sleep��Z�߂ɂ���B����ő����̊���59.94Hz�O��ɋ߂Â���(�����̊�)�B
			}
			_LastTimeSyncTime3 = timeGetTime(); //3�t���[�����Ƃ�Sync���I������^�C���Ƃ��ċL�^���Ă���
		}
		_LastTimeSyncTime = timeGetTime(); //�O���Sync���I������^�C���Ƃ��ċL�^���Ă���
		_Frame++;
		return TRUE;
	}
}


void*
SCREENDD_GetBuffer()
{
	return (void*)_pScreenPixels;
}


const Sint32
SCREENDD_GetBufferPitch()
{
	return _SurfacePitch/2;
}


//Kitao�ǉ��B�����\���A�h��Ԃ����p�̃v���C�}���T�[�t�F�X�֓]�����鏈���B���݁A�\�[�X�𑜓x256x224�Œ�B
static void
zoom_ddTensou256()
{
	Sint32		w = 256;
	Sint32		h = 224;
	Sint32		a,b;
	RECT		rc;
	RECT		rcDst;
	RECT		rcSrc;

	//�]����̈ʒu����
	if (_Flags & SCREEN_FFULLSCREEN)
		SetRect(&rcDst, 0, 0, _Width, _Height);
	else //�E�B���h�E���[�h�̂Ƃ�
	{
		GetWindowRect(_hWnd, &rc);
		a = rc.left + (rc.right - rc.left - _Width)/2;
		b = rc.bottom - (rc.right - rc.left - _Width)/2 - _Height; //�g�̑����ƕ\���̈�̍����Ԃ������
		SetRect(&rcDst, a, b, a+_Width, b+_Height);
	}

	//�]�����̈ʒu����
	SetRect(&rcSrc, 0, 0, w, h);

	//�v���C�}���T�[�t�F�X�֓]������
	if (_pDDSPrimary->Blt(&rcDst, _pDDS256, &rcSrc, DDBLT_ASYNC, NULL) == DDERR_SURFACELOST)
		_pDDSPrimary->Restore();
}


//Kitao�X�V�Bddsd�̏�����(100�o�C�g���̃������A�N�Z�X)���ȗ����č���������(v1.02�X�V)�Bv2.13�X�V�B32bit�P�ʂň����悤�ɂ����B
static BOOL
lock_offscreen_surface(
	LONG*		pPitch,
	Uint32**	ppPixels)
{
	HRESULT			hRet;
	int				trial = 10;

	while (trial--)
	{
		hRet = _pDDSBack->Lock(NULL, &_ddsdBack, DDLOCK_WAIT, NULL);
		if (hRet == DD_OK)
		{
			*pPitch = _ddsdBack.lPitch >> 2; //���P���C���̃o�C�g���B32bit�P�ʂň������߂�4�Ŋ����Ă����Bv2.13�X�V
			*ppPixels = (Uint32*)_ddsdBack.lpSurface;
			return TRUE;
		}
		else if (hRet == DDERR_SURFACELOST)
		{
			_pDDSBack->Restore();
		}
    }

	return FALSE;
}


//Kitao�ǉ��B��ʑS�̂��N���A����Bv1.43�Bv2.77�X�V
void
SCREENDD_Clear(
	byte	r,
	byte	g,
	byte	b) //v2.73�X�V�B�C�ӂ̐F�ŃN���A�ł���悤�ɂ����B��16�r�b�g���[�h�̂Ƃ��̓��m�N���ȊO���ƐF��������̂Ō��݂̓��m�N���Œ��r�̃f�[�^�̂ݎg�p�B
{
    DDBLTFX		ddbltfx;

    ZeroMemory(&ddbltfx, sizeof(DDBLTFX));
	if (_BitsPerPixel == 16)
		ddbltfx.dwFillColor = (r >> 4 << _Rshift) | (r >> 4 << _Gshift) | (r >> 4);
	else
		ddbltfx.dwFillColor = r*256 + r;
    ddbltfx.dwSize = sizeof(DDBLTFX);
    _pDDSPrimary->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
}


//Kitao�ǉ��B�e�L�X�g���b�Z�[�W��ݒ�
void
SCREENDD_SetMessageText(
	char*	pText)
{
	_pMessageText = pText;
}

//Kitao�ǉ��B�Z���^�[�e�L�X�g���b�Z�[�W��ݒ�
void
SCREENDD_SetCenterText(
	char*	pText)
{
	_pCenterText = pText;
}


//Kitao�ǉ��B�e�L�X�g���b�Z�[�W�̕\��
static void
print_message(
	Sint32	executeCode) //v2.00�X�V
{
	HDC			dc;
	HFONT		prevFont;
	HFONT		hFont;
	LOGFONT		logFont;
	RECT		rcSrc;
	RECT		rcDst;
	RECT		rc;
	BOOL		bHalfMode;
	int			a,fs;
	Sint32		hMagnification; //�c�̕\���{��
	Sint32		scanLineType = APP_GetScanLineType();

	if (!APP_GetInit())
		return; //�ŏ��̏��������S�Ċ������Ă��Ȃ��ꍇ�́A�\���������s��Ȃ��BCD-ROM�Q�[�������W���[�������Ƃ��Ƀ��b�Z�[�W������������̂�����Bv1.67

	//�f�o�C�X�R���e�L�X�g���擾
	if (_pDDSText->GetDC(&dc) != DD_OK)
		return;

	//�t�H���g�T�C�Y������
	if (_Magnification == 1)
		bHalfMode = FALSE;
	else
		bHalfMode = APP_GetHalfMode();
	if ((bHalfMode)||(_Magnification == 1))
		fs = 12; //�t�H���g�T�C�Y�Bv1.09�X�V
	else
		fs = 16;
	if (_Magnification <= 2)
	{
		if ((!bHalfMode)&&((!APP_GetUseVideoCardMemory())||(APP_GetWindowsVista()))) //��x2��Half���[�h���̓t�H���g���������Ă�OK�BVista�̏ꍇ�r�f�I�������ł��X���[�W���O���|����Ȃ��̂œ��l�Ƀt�H���g��傫������B
		{	//�V�X�e�����������g�p���Ă���ꍇ�A256���傫�ȉ𑜓x�ŕ����������̂Ńt�H���g��傫������K�v������Bv1.53
			if (VDC_GetTvWidth() >= 512)
				fs = 32;
			else if (VDC_GetTvWidth() > 256)
				fs = 28;
		}
		else
		{	//x2�ȉ��̏ꍇ�A��512���ɕ������ǂ݂Â炢�̂ő傫������
			if ((!bHalfMode)&&(VDC_GetTvWidth() >= 512))
				fs = 28;
		}
	}
	if ((_Magnification == 3)&&(!bHalfMode)&&
		((!APP_GetUseVideoCardMemory())||(APP_GetWindowsVista()))&&(VDC_GetTvWidth() >= 512)) //x3(��Half���[�h)�ŃV�X�e������������512�ȏ�̏ꍇ�BVista�̏ꍇ�r�f�I�������ł��X���[�W���O���|����Ȃ��̂œ��l�Ƀt�H���g��傫������B
			fs = 28;
	hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	GetObject(hFont, sizeof(LOGFONT), &logFont);
	logFont.lfHeight = fs;
	logFont.lfWidth = 0;
	hFont = CreateFontIndirect(&logFont);
	prevFont = (HFONT)SelectObject(dc, hFont);
	//��������o�b�t�@�ɕ`��
	rc.left		= 0;
	rc.right	= 0;
	rc.top		= 0;
	rc.bottom	=fs;
	SetBkColor(dc, RGB(48,96,48));
	SetTextColor(dc, RGB(255,255,255));
	DrawText(dc, _pMessageText, lstrlen(_pMessageText), &rc,
			 DT_CALCRECT | DT_SINGLELINE | DT_NOPREFIX); //�\���V�~�����[�V�����Brc�ɕ\�������Ƃ��̃T�C�Y������B
	DrawText(dc, _pMessageText, lstrlen(_pMessageText), &rc, DT_SINGLELINE | DT_NOPREFIX); //�\��

	SelectObject(dc, prevFont);
	DeleteObject(hFont);
	_pDDSText->ReleaseDC(dc);
	
	//�]�����ʒu���T�C�Y�̒���
	rcSrc.left	= 0;
	rcSrc.top	= 0;
	rcSrc.right	= rc.right;
	a = VDC_GetTvWidth();
	if (APP_GetOverscanHideBlackLR())
		a += 16;
	else
		a += MAINBOARD_GetShowOverscanLeft()+MAINBOARD_GetShowOverscanRight();
	if (_Magnification > 1)
		a *= 2;
	if (rcSrc.right > a)
		rcSrc.right = a;
	rcSrc.bottom= fs;
	//�]����ʒu�̒������\�����������͈̔͂����₷�����邽�߂Ɋg�傷��B
	if (fs == 12)
	{
		if ((scanLineType == 0)||(scanLineType == 7)||(scanLineType == 8)) //�m���X�L�������C��
		{
			if ((bHalfMode)&&(_Magnification >= 2))
			{
				if (_Magnification == 4)
					hMagnification = 3;
				else
					hMagnification = 2;
			}
			else
				hMagnification = 1;
		}
		else //�m���X�L�������C���ȊO
			hMagnification = _Magnification;
		rcDst.top = 4;
		rcDst.bottom = 4 + fs*hMagnification;
		if (_Magnification == 1)
			rcDst.left = 3;
		else
			rcDst.left = 2;
	}
	else
	{
		if ((scanLineType == 0)||(scanLineType == 7)||(scanLineType == 8)) //�m���X�L�������C��
		{
			if (_Magnification == 4)
				hMagnification = 3;
			else
				hMagnification = 2;
		}
		else //�m���X�L�������C���ȊO
			hMagnification = _Magnification;
		rcDst.top = 4;
		if ((_Magnification == 4)||
			((_Magnification == 3)&&(scanLineType != 0)&&(scanLineType != 7)&&(scanLineType != 8)))
				rcDst.bottom = rcDst.top + fs*2;
		else
			rcDst.bottom = rcDst.top + fs;
		rcDst.left = 3 -_Magnification/4;
	}
	if ((APP_GetFullStretched(TRUE))&&(_Flags & SCREEN_FFULLSCREEN)) //�t���X�g���b�`���[�h�Ȃ�Bv2.00�ǉ�
	{
		rcDst.top += 16*hMagnification;	   //�㑤�I�[�o�[�X�L�����̈敔���𑫂�
		rcDst.bottom += 16*hMagnification; //
	}
	else
	{
		rcDst.top += (16-MAINBOARD_GetShowOverscanTop())*hMagnification;	//�㑤�I�[�o�[�X�L�����̈敔���𑫂�
		rcDst.bottom += (16-MAINBOARD_GetShowOverscanTop())*hMagnification; //
	}
	if ((!APP_GetStretched())&&((_Flags & SCREEN_FFULLSCREEN) == 0)) //�E�B���h�E���[�h�ŃX�g���b�`�����Ȃ��ꍇ�Bv2.14�X�V
	{
		a = APP_GetNonstretchedWidth();
		//PRINTF("Test = %d",a);
		if ((a < 256)||
			((a > 256)&&(a < 336)))
		{
			if (_Magnification > 1)
				a = (a*2 / 2) - (rcSrc.right / 2);
			else
				a = (a / 2) - (rcSrc.right / 2);
			if (a > rcDst.left)
				rcDst.left = a; //���[��؂炳�Ȃ����߂ɒ����ɕ\��
		}
		else if (MAINBOARD_GetShowOverscanLeft() > 0) //���E�̃I�[�o�[�X�L�����̈��\�����Ă���Ȃ�Bv2.15�ǉ�
		{
			if (_Magnification == 1)
				rcDst.left += 8;
			else
				rcDst.left += 8*2;
		}
	}
	else if (executeCode == 5) //�I�[�o�[�X�L�����̈�̍��E���J�b�g����ꍇ
	{
		if (_Magnification == 1)
			rcDst.left += 6;
		else
			rcDst.left += 6*2;
	}
	rcDst.right	= rcDst.left + rcSrc.right;
	if ((APP_GetOverscanHideBlackLR())&&(MAINBOARD_GetShowOverscanLeft() == 0)) //���E�̃I�[�o�[�X�L�����̈�ɍ��т�t����Ȃ�
	{
		rcDst.right -= rcDst.left;
		rcDst.left = 0; //���т�����̂ŃM���M���܂ō��Ɋ񂹂Ă����h��OK�B
	}
	if ((APP_GetOverscanHideBlackTop())&&(MAINBOARD_GetShowOverscanTop() < 8)) //�㑤�̃I�[�o�[�X�L�����̈�ɍ��т�t����Ȃ�
	{
		if ((8-MAINBOARD_GetShowOverscanTop())*hMagnification >= 4) //���ѕ�����4�h�b�g�ȏ゠�����ꍇ
		{
			a = (16-MAINBOARD_GetShowOverscanTop())*hMagnification;
			rcDst.bottom -= (rcDst.top - a);
			rcDst.top =	a; //���т�����̂ŃM���M���܂ŏ�Ɋ񂹂Ă����h��OK�B
		}
	}
	if (MAINBOARD_GetFourSplitScreen()) //�d�������L,���[���h�R�[�g,�͂ɂ����񂴂�����,�p���[�h���t�g,�T�C�R�`�F�C�T�[�̂S������ʂ̏ꍇ�Bv2.27�X�V
	{	//�����̍��ѕ������l��
		if ((_Magnification == 1)||(bHalfMode))
		{
			rcDst.left  += 256/2;
			rcDst.right += 256/2;
		}
		else
		{
			rcDst.left  += 512/2;
			rcDst.right += 512/2;
		}
	}
	//�]��
	if (_pDDSBack->Blt(&rcDst, _pDDSText, &rcSrc, DDBLT_ASYNC, NULL) == DDERR_SURFACELOST)
		_pDDSBack->Restore();
}


//Kitao�ǉ��BFPS�̕\��
static void
print_fps(
	Sint32	executeCode) //v2.00�X�V
{
	HDC			dc;
	HFONT		prevFont;
	HFONT		hFont;
	LOGFONT		logFont;
	RECT		rcSrc;
	RECT		rcDst;
	RECT		rc;
	BOOL		bHalfMode;
	int			fs;
	char		text[3+1]; //�ꉞ�R���܂ŗp��
	int			a;
	Sint32		hMagnification; //�c�̕\���{��
	Sint32		scanLineType = APP_GetScanLineType();

	//�f�o�C�X�R���e�L�X�g���擾
	if (_pDDSText->GetDC(&dc) != DD_OK)
		return;

	//�t�H���g�T�C�Y������
	if (_Magnification == 1)
		bHalfMode = FALSE;
	else
		bHalfMode = APP_GetHalfMode();
	if ((bHalfMode)||(_Magnification == 1))
		fs = 12; //�t�H���g�T�C�Y�Bv1.09�X�V
	else
		fs = 16;
	if (_Magnification <= 2)
	{
		if ((!bHalfMode)&&((!APP_GetUseVideoCardMemory())||(APP_GetWindowsVista()))) //��x2��Half���[�h���̓t�H���g���������Ă�OK�BVista�̏ꍇ�r�f�I�������ł��X���[�W���O���|����Ȃ��̂œ��l�Ƀt�H���g��傫������B
		{	//�V�X�e�����������g�p���Ă���ꍇ�A256���傫�ȉ𑜓x�ŕ����������̂Ńt�H���g��傫������K�v������Bv1.53
			if (VDC_GetTvWidth() >= 512)
				fs = 32;
			else if (VDC_GetTvWidth() > 256)
				fs = 28;
		}
		else
		{	//x2�ȉ��̏ꍇ�A��512���ɕ������ǂ݂Â炢�̂ő傫������
			if ((!bHalfMode)&&(VDC_GetTvWidth() >= 512))
				fs = 28;
		}
	}
	if ((_Magnification == 3)&&(!bHalfMode)&&
		((!APP_GetUseVideoCardMemory())||(APP_GetWindowsVista()))&&(VDC_GetTvWidth() >= 512)) //x3(��Half���[�h)�ŃV�X�e������������512�ȏ�̏ꍇ�BVista�̏ꍇ�r�f�I�������ł��X���[�W���O���|����Ȃ��̂œ��l�Ƀt�H���g��傫������B
			fs = 28;
	hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	GetObject(hFont, sizeof(LOGFONT), &logFont);
	logFont.lfHeight = fs;
	logFont.lfWidth = 0;
	hFont = CreateFontIndirect(&logFont);
	prevFont = (HFONT)SelectObject(dc, hFont);
	//��������o�b�t�@�ɕ`��
	rc.left		= 0;
	rc.right	= 0;
	rc.top		= 0;
	rc.bottom	=fs;
	SetBkColor(dc, RGB(48,96,48));
	SetTextColor(dc, RGB(255,255,255));
	a = MAINBOARD_GetDisplayedFrames();
	if (a > 999) a = 999;
	sprintf(text, "%d", a);
	DrawText(dc, text, lstrlen(text), &rc,
			 DT_CALCRECT | DT_SINGLELINE | DT_NOPREFIX); //�\���V�~�����[�V�����Brc�ɕ\�������Ƃ��̃T�C�Y������B
	DrawText(dc, text, lstrlen(text), &rc, DT_SINGLELINE | DT_NOPREFIX); //�\��
	
	SelectObject(dc, prevFont);
	DeleteObject(hFont);
	_pDDSText->ReleaseDC(dc);
	
	//�]�����ʒu���T�C�Y�̒���
	rcSrc.left	= 0;
	rcSrc.top	= 0;
	rcSrc.right	= rc.right;
	rcSrc.bottom= fs;
	//�]����ʒu�̒������\�����������͈̔͂����₷�����邽�߂Ɋg�傷��B
	if (fs == 12)
	{	//"x1" or "TV mode"
		if ((scanLineType == 0)||(scanLineType == 7)||(scanLineType == 8)) //�m���X�L�������C��
		{
			if ((bHalfMode)&&(_Magnification >= 2))
			{
				if (_Magnification == 4)
					hMagnification = 3;
				else
					hMagnification = 2;
			}
			else
				hMagnification = 1;
		}
		else //�m���X�L�������C���ȊO
			hMagnification = _Magnification;
		rcDst.bottom = 224*hMagnification - 3; //�����ɕ\��
	    rcDst.top = rcDst.bottom - fs*hMagnification;
		if (_Magnification == 1)
			rcDst.left = 3;
		else
			rcDst.left = 2;
	}
	else
	{
		if ((scanLineType == 0)||(scanLineType == 7)||(scanLineType == 8)) //�m���X�L�������C��
		{
			if (_Magnification == 4)
				hMagnification = 3;
			else
				hMagnification = 2;
		}
		else //�m���X�L�������C���ȊO
			hMagnification = _Magnification;
		rcDst.bottom = 224*hMagnification - 3; //�����ɕ\��
		if ((_Magnification == 4)||
			((_Magnification == 3)&&(scanLineType != 0)&&(scanLineType != 7)&&(scanLineType != 8)))
			    rcDst.top = rcDst.bottom - fs*2;
		else
		    rcDst.top = rcDst.bottom - fs;
		rcDst.left = 3 -_Magnification/4;
	}
	rcDst.top += (16+MAINBOARD_GetShowOverscanBottom())*hMagnification;	   //�㉺�̃I�[�o�[�X�L�����̈敔���𑫂��B���16�h�b�g�Ԃ�K�������B
	rcDst.bottom += (16+MAINBOARD_GetShowOverscanBottom())*hMagnification; //
	if ((!APP_GetStretched())&&((_Flags & SCREEN_FFULLSCREEN) == 0)) //�E�B���h�E���[�h�ŃX�g���b�`�����Ȃ��ꍇ�Bv2.14�X�V
	{
		a = APP_GetNonstretchedWidth();
		//PRINTF("Test = %d",a);
		if ((a < 256)||
			((a > 256)&&(a < 336)))
		{
			if (_Magnification > 1)
				a = (a*2 / 2) - (rcSrc.right / 2);
			else
				a = (a / 2) - (rcSrc.right / 2);
			if (a > rcDst.left)
				rcDst.left = a; //���[��؂炳�Ȃ����߂ɒ����ɕ\��
		}
		else if (MAINBOARD_GetShowOverscanLeft() > 0) //���E�̃I�[�o�[�X�L�����̈��\�����Ă���Ȃ�Bv2.15�ǉ�
		{
			if (_Magnification == 1)
				rcDst.left += 8;
			else
				rcDst.left += 8*2;
		}
	}
	else if (executeCode == 5) //�I�[�o�[�X�L�����̈�̍��E���J�b�g����ꍇ
	{
		if (_Magnification == 1)
			rcDst.left += 6;
		else
			rcDst.left += 6*2;
	}
	rcDst.right	= rcDst.left + rcSrc.right;
	if ((APP_GetOverscanHideBlackLR())&&(MAINBOARD_GetShowOverscanLeft() == 0)) //���E�̃I�[�o�[�X�L�����̈�ɍ��т�t����Ȃ�
	{
		rcDst.right -= rcDst.left;
		rcDst.left = 0; //���т�����̂ŃM���M���܂ō��Ɋ񂹂Ă����h��OK�B
	}
	if ((APP_GetOverscanHideBlackBottom())&&(MAINBOARD_GetShowOverscanBottom() < 8)) //�����̃I�[�o�[�X�L�����̈�ɍ��т�t����Ȃ�
	{
		if ((8-MAINBOARD_GetShowOverscanBottom())*hMagnification >= 3) //���ѕ�����3�h�b�g�ȏ゠�����ꍇ
		{
			a = rcDst.bottom - (16+224+MAINBOARD_GetShowOverscanBottom())*hMagnification;
			rcDst.bottom -= a;
			rcDst.top -= a; //���т�����̂ŃM���M���܂ŉ��Ɋ񂹂Ă����h��OK�B
		}
	}
	if (MAINBOARD_GetFourSplitScreen()) //�d�������L,���[���h�R�[�g,�͂ɂ����񂴂�����,�p���[�h���t�g,�T�C�R�`�F�C�T�[�̂S������ʂ̏ꍇ�Bv2.27�X�V
	{	//�����̍��ѕ������l��
		if ((_Magnification == 1)||(bHalfMode))
		{
			rcDst.left  += 256/2;
			rcDst.right += 256/2;
		}
		else
		{
			rcDst.left  += 512/2;
			rcDst.right += 512/2;
		}
	}
	//�]��
	if (_pDDSBack->Blt(&rcDst, _pDDSText, &rcSrc, DDBLT_ASYNC, NULL) == DDERR_SURFACELOST)
		_pDDSBack->Restore();
}


//��ʂ̒����Ƀ��b�Z�[�W��\������Bv2.77�ǉ�
static void
print_center_message(
	Sint32	executeCode)
{
	HDC			dc;
	HFONT		prevFont;
	HFONT		hFont;
	LOGFONT		logFont;
	RECT		rcSrc;
	RECT		rcDst;
	RECT		rc;
	BOOL		bHalfMode;
	int			fs;
	Sint32		hMagnification; //�c�̕\���{��
	LONG		adjust;
	Sint32		scanLineType = APP_GetScanLineType();

	//�f�o�C�X�R���e�L�X�g���擾
	if (_pDDSText->GetDC(&dc) != DD_OK)
		return;

	//�t�H���g�T�C�Y������
	if (_Magnification == 1)
		bHalfMode = FALSE;
	else
		bHalfMode = APP_GetHalfMode();
	if ((bHalfMode)||(_Magnification == 1))
		fs = 12; //�t�H���g�T�C�Y�Bv1.09�X�V
	else
		fs = 16;
	if (_Magnification <= 2)
	{
		if ((!bHalfMode)&&((!APP_GetUseVideoCardMemory())||(APP_GetWindowsVista()))) //��x2��Half���[�h���̓t�H���g���������Ă�OK�BVista�̏ꍇ�r�f�I�������ł��X���[�W���O���|����Ȃ��̂œ��l�Ƀt�H���g��傫������B
		{	//�V�X�e�����������g�p���Ă���ꍇ�A256���傫�ȉ𑜓x�ŕ����������̂Ńt�H���g��傫������K�v������Bv1.53
			if (VDC_GetTvWidth() >= 512)
				fs = 32;
			else if (VDC_GetTvWidth() > 256)
				fs = 28;
		}
		else
		{	//x2�ȉ��̏ꍇ�A��512���ɕ������ǂ݂Â炢�̂ő傫������
			if ((!bHalfMode)&&(VDC_GetTvWidth() >= 512))
				fs = 28;
		}
	}
	if ((_Magnification == 3)&&(!bHalfMode)&&
		((!APP_GetUseVideoCardMemory())||(APP_GetWindowsVista()))&&(VDC_GetTvWidth() >= 512)) //x3(��Half���[�h)�ŃV�X�e������������512�ȏ�̏ꍇ�BVista�̏ꍇ�r�f�I�������ł��X���[�W���O���|����Ȃ��̂œ��l�Ƀt�H���g��傫������B
			fs = 28;
	hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	GetObject(hFont, sizeof(LOGFONT), &logFont);
	logFont.lfHeight = fs;
	logFont.lfWidth = 0;
	hFont = CreateFontIndirect(&logFont);
	prevFont = (HFONT)SelectObject(dc, hFont);
	//��������o�b�t�@�ɕ`��
	rc.left		= 0;
	rc.right	= 0;
	rc.top		= 0;
	rc.bottom	=fs;
	SetBkColor(dc, RGB(48,96,48));
	SetTextColor(dc, RGB(255,255,255));
	DrawText(dc, _pCenterText, lstrlen(_pCenterText), &rc,
			 DT_CALCRECT | DT_SINGLELINE | DT_NOPREFIX); //�\���V�~�����[�V�����Brc�ɕ\�������Ƃ��̃T�C�Y������B
	DrawText(dc, _pCenterText, lstrlen(_pCenterText), &rc, DT_SINGLELINE | DT_NOPREFIX); //�\��
	
	SelectObject(dc, prevFont);
	DeleteObject(hFont);
	_pDDSText->ReleaseDC(dc);
	
	//�]����ʒu�̒������\�����������͈̔͂����₷�����邽�߂Ɋg�傷��B
	if (fs == 12)
	{	//"x1" or "TV mode"
		if ((scanLineType == 0)||(scanLineType == 7)||(scanLineType == 8)) //�m���X�L�������C��
		{
			if ((bHalfMode)&&(_Magnification >= 2))
			{
				if (_Magnification == 4)
					hMagnification = 3;
				else
					hMagnification = 2;
			}
			else
				hMagnification = 1;
		}
		else //�m���X�L�������C���ȊO
			hMagnification = _Magnification;
	}
	else
	{
		if ((scanLineType == 0)||(scanLineType == 7)||(scanLineType == 8)) //�m���X�L�������C��
		{
			if (_Magnification == 4)
				hMagnification = 3;
			else
				hMagnification = 2;
		}
		else //�m���X�L�������C���ȊO
			hMagnification = _Magnification;
	}

	//�]�����ʒu���T�C�Y�̒���
	rcSrc.left	= 0;
	rcSrc.top	= 0;
	rcSrc.right	= rc.right;
	rcSrc.bottom= fs;
	//�]����ʒu�̒������\�����������͈̔͂����₷�����邽�߂Ɋg�傷��B
	rcDst.left = 0;
	rcDst.top  = 0;
	if (_Magnification >= 3)
	{
		rcDst.right	= rcDst.left + rcSrc.right;
	    rcDst.bottom = fs * 2; //�c���Q�{�g��
	}
	else
	{
		rcDst.right	= rcDst.left + rcSrc.right;
	    rcDst.bottom = fs;
	}
	//�Z���^�����O
	GetWindowRect(_hWnd, &rc);
	adjust = 256 - (rcDst.right - rcDst.left) / 2;
	rcDst.left   += adjust;
	rcDst.right  += adjust;
	adjust = (rc.bottom - rc.top) / 2 - (rcDst.bottom - rcDst.top) / 2;
	rcDst.top    += adjust;
	rcDst.bottom += adjust;
	//�]��
	if (_pDDSBack->Blt(&rcDst, _pDDSText, &rcSrc, DDBLT_ASYNC, NULL) == DDERR_SURFACELOST)
		_pDDSBack->Restore();
}


//Kitao�ǉ��B�v���C�}���T�[�t�F�X�֓]�����鏈���ȂǁBv2.00�X�V�B�㑤�̃I�[�o�[�X�L�������C���̈�������œ]������悤�ɂ����B
static void
zoom_ddTensou(
	Uint16*		pTvW,	//�]�����̉��s�N�Z�����B��[0]�`[239]��224+16(������Overscan)���C���Ԃ�B�����ɂ�[0](�擪)�̃A�h���X������B
	Sint32		h,		//�]�����̏c�s�N�Z�����B�ʏ��224�B�����̃I�[�o�[�X�L����������ꍇ���̂Ԃ񑝂₵�Ă������ĂԁB
	Sint32		executeCode)  //���s�R�[�h�B0�c�G���R�[�h�����s���B1�c�v���C�}����ʂ֓]�����s���B2�c�X�N���[���V���b�g�p��ʂ֓]�����s���B
							  //		    3�c���E�ɍ���(�I�[�o�[�X�L������)��z�u���Ă̓]��(���Ƃ�1�Ɠ���)�B4�c�X�N���[���V���b�g��̉�ʕ����]�����s���B
							  //v2.12�X�V   5�c���E�̃I�[�o�[�X�L���������J�b�g���Ă̓]��(���Ƃ�1�Ɠ���)
{
	RECT		rcSrc;
	RECT		rcDst;
	RECT		rc;
	Sint32		a,b,c,d,s,s2,t,i,w2,h2;
	BOOL		bRasterChange = FALSE; //���X�^���ƂɈقȂ�𑜓x���ݒ肳��Ă����ꍇTRUE
	Uint16*		pTvW2 = pTvW;
	Sint32		ot = 16-MAINBOARD_GetShowOverscanTop(); //�]�����̊J�nY���W�Bv2.00�ǉ�
	Sint32		scanLineType = APP_GetScanLineType();

	//�]�����̉������� 
	s = (*pTvW2);
	for (i=0; i<h; i++)
	{
		if ((*pTvW2) != s)
		{
			bRasterChange = TRUE;
			if ((*pTvW) < s)
				s = (*pTvW); //s=��ԏ����������B�t���X�g���b�`���ɂ��݂��o�Ȃ��悤�ɁB
		}
		*pTvW2++;
	}

	//�]����̈ʒu���� 
	if (_Flags & SCREEN_FFULLSCREEN)
	{
		if (APP_GetFullStretched(TRUE))
		{
			//�A�X�y�N�g���4:3�ɕۂ�
			if (_Width/4 >= _Height/3)
			{	//�c�̂ق����Z���̂ŏc����Ƃ���
				w2 = (Sint32)((double)(_Height / 3.0 * 4.0 + 0.5));
				a = (_Width - w2) / 2;
				if ((MAINBOARD_GetShowOverscanLeft() > 0)&&((*(pTvW+MAINBOARD_GetShowOverscanTop()+223)) != 512)&&(executeCode != 3)) //���E�̃I�[�o�[�X�L�����̈��\������Ȃ�
					b = (_Height - (Sint32)((double)_Height * 0.96137 + 0.5)) / 2; //0.96137=224/((268-256)/4*3+224)
				else
					b = 0;
				c = _Width - a;
				d = _Height - b;
			}
			else
			{	//���̂ق����Z���̂ŉ�����Ƃ���
				h2 = (Sint32)((double)(_Width / 4.0 * 3.0 + 0.5));
				a = 0;
				if ((MAINBOARD_GetShowOverscanLeft() > 0)&&((*(pTvW+MAINBOARD_GetShowOverscanTop()+223)) != 512)&&(executeCode != 3)) //���E�̃I�[�o�[�X�L�����̈��\������Ȃ�
					b = (_Height - (Sint32)((double)h2 * 0.96137 + 0.5)) / 2; //0.96137=224/((268-256)/4*3+224)
				else
					b = (_Height - h2) / 2;
				c = _Width;
				d = _Height - b;
			}
			//�t���X�g���b�`���͏㉺�̃I�[�o�[�X�L�����̈��\���ł��Ȃ����߁A�I�[�o�[�X�L�����̈���J�b�g�B
			h -= MAINBOARD_GetShowOverscanTop() + MAINBOARD_GetShowOverscanBottom();
			ot = 16;
			bRasterChange = FALSE; //�t���X�g���b�`���̓��X�^���Ƃ̉𑜓x�ύX���ł��Ȃ��B
		}
		else if (APP_GetStretched())
		{
			if ((MAINBOARD_GetShowOverscanLeft() > 0)&&(executeCode != 3)) //���E�̃I�[�o�[�X�L�����̈��\������Ȃ�
				w2 = (Sint32)(313.24 * (double)_Magnification + 0.5);
			else
				w2 = 299 * _Magnification; //�A�X�y�N�g��Œ�̂��߉���299(2�{��598)�̕\���͈́B
			if (APP_GetVStretched()) //�c��ʃ��[�h�Ȃ�
				w2 = (Sint32)((double)w2 * (256.0/336.0)); //���@���l��256:336�̔�ŏk������i��256�ȊO�̃Q�[�������l�ɉ\�j
			//�A�X�y�N�g���TV��ʂƓ���4:3�ɁB�c�̒�������PCE�W��224�̐����{(�Q�{)�ɂ���
			a = (_Width - w2) / 2;
			b = (_Height - 224*_Magnification) / 2;
			c = a + w2;
			d = b + 224*_Magnification;
			if (MAINBOARD_GetShowOverscanTop() > 0) //�㑤�̃I�[�o�[�X�L�����̈��\������Ȃ�
			{
				b -= MAINBOARD_GetShowOverscanTop() * _Magnification;
				if (b < 0) //��ʂ���͂ݏo���Ă��܂��ꍇ�B1440x900,1600x900�Ȃǂł��蓾��B
				{	//�A�X�y�N�g���ۂ��߁A�I�[�o�[�X�L���������J�b�g�B
					b = (_Height - 224*_Magnification) / 2;
					h -= MAINBOARD_GetShowOverscanTop();
					ot = 16;
				}
			}
			if (MAINBOARD_GetShowOverscanBottom() > 0) //�����̃I�[�o�[�X�L�����̈��\������Ȃ�
			{
				d += MAINBOARD_GetShowOverscanBottom() * _Magnification;
				if (d > _Height) //��ʂ���͂ݏo���Ă��܂��ꍇ�B1440x900,1600x900�Ȃǂł��蓾��B
				{	//�A�X�y�N�g���ۂ��߁A�I�[�o�[�X�L���������J�b�g�B
					d = b + 224*_Magnification;
					h -= MAINBOARD_GetShowOverscanBottom();
				}
			}
		}
		else //�X�g���b�`�����Ȃ��ꍇ
		{
			w2 = (*pTvW)*_Magnification;
			if (w2 > _Width) w2 = _Width; //��ʂ���͂ݏo���Ă��܂��ꍇ�́A�X�g���b�`(�k��)���đΉ��B
			a = (_Width - w2) / 2;
			b = (_Height - 224*_Magnification) / 2;
			c = a + w2;
			d = b + 224*_Magnification;
			if (MAINBOARD_GetShowOverscanTop() > 0) //�㑤�̃I�[�o�[�X�L�����̈��\������Ȃ�
			{
				b -= MAINBOARD_GetShowOverscanTop() * _Magnification;
				if (b < 0) b = 0; //��ʂ���͂ݏo���Ă��܂��ꍇ�́A�X�g���b�`(�k��)���đΉ��B1440x900,1600x900�Ȃǂł��蓾��B
			}
			if (MAINBOARD_GetShowOverscanBottom() > 0) //�����̃I�[�o�[�X�L�����̈��\������Ȃ�
			{
				d += MAINBOARD_GetShowOverscanBottom() * _Magnification;
				if (d > _Height) d = _Height; //��ʂ���͂ݏo���Ă��܂��ꍇ�́A�X�g���b�`(�k��)���đΉ��B1440x900,1600x900�Ȃǂł��蓾��B
			}
		}
	}
	else //�E�B���h�E���[�h�̂Ƃ�
	{
		GetWindowRect(_hWnd, &rc);
		a = rc.left + (rc.right - rc.left - _Width)/2;
		b = rc.bottom - (rc.right - rc.left - _Width)/2 - _Height; //�g�̑����ƕ\���̈�̍����Ԃ������
		if (APP_GetOverscanHideBlackTop()) //�㑤�̃I�[�o�[�X�L�����̈�ɍ��т����ĉB���ݒ�Ȃ�
			b += (8 - MAINBOARD_GetShowOverscanTop()) * _Magnification;
		c = a + APP_GetGameWidth(_Magnification);
		d = b + (MAINBOARD_GetShowOverscanTop() + 224 + MAINBOARD_GetShowOverscanBottom()) * _Magnification;
		if (((MAINBOARD_GetShowOverscanLeft() > 0)&&((*(pTvW+MAINBOARD_GetShowOverscanTop()+223)) == 512))|| //512�̂Ƃ��̓I�[�o�[�X�L�����\�����Ȃ�
			((MAINBOARD_GetShowOverscanLeft() == 0)&&(APP_GetOverscanHideBlackLR()))||
			(executeCode == 3))
		{	//���E�ɍ��т�z�u
			if (APP_GetVStretched()) //�c��ʃ��[�h�Ȃ�
			{
				a += (Sint32)(5.34 * (double)_Magnification + 0.5);		//5.34=299/256*(256/336)*6dot
				c -= (Sint32)(5.34 * (double)_Magnification + 0.5);		//v2.00�X�V�Bgcc����-1���Ă��傤�ǂ̒l��������VisualC++�ł�-1���Ȃ��̂��s�b�^������B
			}
			else if (APP_GetStretched())
			{
				a += (Sint32)(7.01 * (double)_Magnification + 0.5);		//7.01=299/256*6dot
				c -= (Sint32)(7.01 * (double)_Magnification + 0.5);		//v2.00�X�V�Bgcc����-1���Ă��傤�ǂ̒l��������VisualC++�ł�-1���Ȃ��̂��s�b�^������B
			}
		}
	}
	_GameLeft   = a; //print_center_message()�ŕ\���ʒu����̂��߂ɁA�Q�[����ʓ]����̍��W���T���Ă����B
	_GameRight  = c; //
	_GameTop    = b; //
	_GameBottom = d; //

	if (executeCode != 2) //�X�N���[���V���b�g�p�֓]���ȊO�̂Ƃ�
	{
		//�e�L�X�g���b�Z�[�W�̕\��
		if (*_pMessageText != 0) //���b�Z�[�W���ݒ肳��Ă����
			print_message(executeCode);

		//FPS�̕\���Bv1.50�ǉ�
		if (APP_GetShowFPS())
			print_fps(executeCode);

		//�Z���^�[�e�L�X�g���b�Z�[�W�̕\���Bv2.77�ǉ�
		if (*_pCenterText !=0)
			print_center_message(executeCode);
	}

	//�����A�����Ԃ�҂�
	if (executeCode != 4) //�X�N���[���V���b�g��̕������ȊO�̏ꍇ
		SCREENDD_WaitVBlank(FALSE);

	if (IsIconic(_hWnd)) //�E�B���h�E���ŏ�������Ă���Ƃ��Bhes���ŏ������Ē����Ƃ��Ȃǂɏ������y������B
		if (executeCode != 2) //�X�N���[���V���b�g�p�֓]���ȊO�̏ꍇ
			return;

	//�`��𑜓x�̕ύX���������ꍇ�A�S�~���c��Ȃ��悤�ɉ�ʑS�̂��N���A����B
	if (MAINBOARD_GetResolutionChange())
			zoom_ddTensou256(); //�v���C�}���T�[�t�F�X�֓]������

	//�v���C�}���T�[�t�F�X�֓]������
	if (!bRasterChange)
	{	//�ʏ�
		s2 = 1;
		if (_Magnification >= 2) //���Q�ȏ�̏ꍇ
		{
			if ((scanLineType >= 1)&&(scanLineType <= 6)) //�X�L�������C��(�c���܂�)��
			{
				if ((scanLineType != 3)&&(scanLineType != 4))
					s2 = 2; //���͂Q�{�h�b�g�Œ�B�i���x�A�b�v�{�g�傳�ꂽ�Ƃ��Ƀo�C���j�A�t�B���^�����������ɂ�����j
				h  *= _Magnification; //�c�͔{���Ԃ�̃\�[�X��p�ӂ��ē]���B
				ot *= _Magnification; //
			}
			else //�m���X�L�������C����
			{
				s2 = 2;
				if (_Magnification == 2)
				{
					h  *= _Magnification; //�c�͔{���Ԃ�̃\�[�X��p�ӂ��ē]���B
					ot *= _Magnification; //
				}
				else
				{
					h  *= _Magnification-1; //3x,4x�̂Ƃ��́A���ꂼ��2x,3x�Ɋg��B�i�W���M�[�y�������x�A�b�v�j
					ot *= _Magnification-1; //
				}
			}
		}
		if (MAINBOARD_GetFourSplitScreen()) //�d�������L,���[���h�R�[�g,�͂ɂ����񂴂�����,�p���[�h���t�g,�T�C�R�`�F�C�T�[�̂S������ʂ̏ꍇ�Bv2.27�X�V
		{		
			SetRect(&rcSrc, s/4*s2, ot, (s/4+s/2)*s2, ot+h); //�\�[�X�̍��E���ѕ������J�b�g
			//�S���̂P�ɏk�����ĂS��]��
			c = a + (c-a)/2;
			d = b + (d-b)/2;
			w2 = c - a;
			h2 = d - b;
			for (i=1; i<=4; i++)
			{
				SetRect(&rcDst, a, b, c, d);
				if (_pDDSPrimary->Blt(&rcDst, _pDDSBack, &rcSrc, DDBLT_ASYNC, NULL) == DDERR_SURFACELOST)
					_pDDSPrimary->Restore();
				switch (i)
				{
					case 1:	a+=w2; c+=w2; break; //���͉E��
					case 2:	b+=h2; d+=h2; break; //���͉E��
					case 3:	a-=w2; c-=w2; break; //���͍���
				}
			}
		}
		else //�ʏ�
		{
			SetRect(&rcDst, a, b, c, d);
			if ((!APP_GetStretched())&&((_Flags & SCREEN_FFULLSCREEN) == 0)) //�E�B���h�E���[�h�ŃX�g���b�`�����Ȃ��ꍇ�Bv2.14�X�V
			{
				w2 = (c-a) / _Magnification;
				//PRINTF("%d, %d", s,w2);//test
				w2 = (s-w2)/2;
				SetRect(&rcSrc, w2*s2, ot, (s-w2)*s2, ot+h); //�]������]����Ɠ����h�b�g���ɍ��킹��B
			}
			else if (executeCode == 5) //�I�[�o�[�X�L�����̈�̍��E���J�b�g����ꍇ
				SetRect(&rcSrc, 6*s2, ot, (s-6)*s2, ot+h);
			else //�ʏ�
				SetRect(&rcSrc, 0, ot, s*s2, ot+h);
			if (_pDDSPrimary->Blt(&rcDst, _pDDSBack, &rcSrc, DDBLT_ASYNC, NULL) == DDERR_SURFACELOST)
				_pDDSPrimary->Restore();
		}
	}
	else
	{	//���X�^���ƂɈقȂ�𑜓x���ݒ肳��Ă����Ƃ��B��Vista���ƒ��X���[(nVidia���Ŋm�F)�Ŏg�����ɂȂ�Ȃ��BDirect3D�Ȃ�OK�B
		//v1.28�X�V�B�P���C�����]������悤�ɂ����B
		s2 = 1;
		if (_Magnification >= 2) //���Q�ȏ�̏ꍇ
		{
			if ((scanLineType >= 1)&&(scanLineType <= 6)) //�X�L�������C��(�c���܂�)��
			{
				if ((scanLineType != 3)&&(scanLineType != 4))
					s2 = 2; //���R�ȏ�����͂Q�{�h�b�g�Œ�B�i���x�A�b�v�{�g�傳�ꂽ�Ƃ��Ƀo�C���j�A�t�B���^�����������ɂ�����j
				t = _Magnification; //�c�͔{���Ԃ�̃\�[�X��p�ӂ��ē]���B
			}
			else
			{	//�m���X�L�������C����
				s2 = 2;
				if (_Magnification == 2)
					t = _Magnification; //�c�͔{���Ԃ�̃\�[�X��p�ӂ��ē]���B
				else
					t = _Magnification-1; //3x,4x�̂Ƃ��́A���ꂼ��2x,3x�Ɋg��B�i�W���M�[�y�������x�A�b�v�j
			}
		}
		else
			t = 1;
		for (i=0; i<h; i++)
		{
			if (((*pTvW) == 512)&&(MAINBOARD_GetShowOverscanLeft() > 0)) //512�̂Ƃ��̓I�[�o�[�X�L�����\�����Ȃ�
			{	//���E�ɍ��т�z�u
				if (APP_GetVStretched()) //�c��ʃ��[�h�Ȃ�
					SetRect(&rcDst, a+(int)(5.34*(double)_Magnification+0.5), b+i*_Magnification,
									c-(int)(5.34*(double)_Magnification+0.5)-1, b+i*_Magnification+_Magnification);
				else if (APP_GetStretched())
					SetRect(&rcDst, a+(int)(7.01*(double)_Magnification+0.5), b+i*_Magnification,
									c-(int)(7.01*(double)_Magnification+0.5)-1, b+i*_Magnification+_Magnification);
				else
					SetRect(&rcDst, a, b+i*_Magnification, c, b+i*_Magnification+_Magnification);
			}
			else //�ʏ�
				SetRect(&rcDst, a, b+i*_Magnification, c, b+i*_Magnification+_Magnification);
			if (executeCode == 5) //�I�[�o�[�X�L�����̈�̍��E���J�b�g����ꍇ
				SetRect(&rcSrc, 6*s2, (ot+i)*t, ((*pTvW)-6)*s2, (ot+i)*t+t);
			else //�ʏ�
				SetRect(&rcSrc, 0, (ot+i)*t, (*pTvW)*s2, (ot+i)*t+t);
			if (_pDDSPrimary->Blt(&rcDst, _pDDSBack, &rcSrc, DDBLT_ASYNC, NULL) == DDERR_SURFACELOST)
				_pDDSPrimary->Restore();
			pTvW++;
		}
	}
}


/*
	�n�[�h�E�F�A�ɗ���X�g���b�`�`�惂�[�h
	VRAM �� VRAM �]��
	(�X�g���b�`���ꂽ�ꍇ�o�C���j�A�⊮��������)
*/
//Kitao�ǉ�
#define	GB	(d & 0x000000FF)
#define	GG	(d & 0x0000FF00)>>8
#define	GR	(d & 0x00FF0000)>>16
//Kitao�X�V�Bzoom3x()�Czoom2x()�Czoom1x()�����p�ӁB���x�d���̂��߂��ꂼ��ʃ��[�`���ɁB���C�����Ƃɉ𑜓x��ς��Ă���Q�[���ɑΉ��B
static void
zoom4x_dd16(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch4;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = ((_Gamma[GR] << _Rshift)|(_Gamma[GG] << _Gshift) | _Gamma[GB])|
					  (((_GammaS90[GR] << _Rshift)|(_GammaS90[GG] << _Gshift) | _GammaS90[GB]) << 16); //4byte�Ԃ�(�Q�h�b�g)�������܂��B�����Q�{�g��(90%�c�X�L�������C����)
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90%�X�L�������C���ŁBv2.34�X�V
		{
			d = *pSrc++;
			a =(_GammaS90[GR] << _Rshift)|(_GammaS90[GG] << _Gshift) | _GammaS90[GB];
			*pDst++ = a | (a << 16); //�����Q�{�g��(90%�c�X�L�������C����)
		}
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�R��ڂ�90%�X�L�������C���ŁBv2.34�X�V
		{
			d = *pSrc++;
			a =(_GammaS90[GR] << _Rshift)|(_GammaS90[GG] << _Gshift) | _GammaS90[GB];
			*pDst++ = a | (a << 16); //�����Q�{�g��(90%�c�X�L�������C����)
		}
		pDst = pDst0 + _Pitch3;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a =(_GammaS80[GR] << _Rshift)|(_GammaS80[GG] << _Gshift) | _GammaS80[GB];
			*pDst++ = a | (a << 16); //�����Q�{�g��(80%�c�X�L�������C����)
		}
		pDst0 += _Pitch4;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�X�V�B32�r�b�g�J���[�ɂ��Ή��B
static void
zoom4x_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch4;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB]; //4byte�Ԃ�(�P�h�b�g)�������܂��B
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB]; //4byte�Ԃ�(�P�h�b�g)�������܂��B�����Q�{�g��(90%�c�X�L�������C����)
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90%�X�L�������C���ŁBv2.34�X�V
		{
			d = *pSrc++;
			a = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
			*pDst++ = a;
			*pDst++ = a; //�����Q�{�g��(90%�c�X�L�������C����)�Bv2.34�X�V
		}
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�R��ڂ�90%�X�L�������C���ŁBv2.34�X�V
		{
			d = *pSrc++;
			a = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
			*pDst++ = a;
			*pDst++ = a; //�����Q�{�g��(90%�c�X�L�������C����)�Bv2.34�X�V
		}
		pDst = pDst0 + _Pitch3;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
			*pDst++ = a;
			*pDst++ = a; //�����Q�{�g��(80%�c�X�L�������C����)
		}
		pDst0 += _Pitch4;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�X�V�B16�r�b�g�J���[x�R�{�p
static void
zoom3x_dd16(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch3;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = ((_Gamma[GR] << _Rshift)|(_Gamma[GG] << _Gshift) | _Gamma[GB])|
					  (((_GammaS90[GR] << _Rshift)|(_GammaS90[GG] << _Gshift) | _GammaS90[GB]) << 16); //�����Q�{�g��(90%�c�X�L�������C����)
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90%�X�L�������C���ɂ���B
		{
			d = *pSrc++;
			a = (_GammaS90[GR] << _Rshift)|(_GammaS90[GG] << _Gshift) | _GammaS90[GB];
			*pDst++ = a | (a << 16); //�����Q�{�g��(90%�c�X�L�������C����)
		}
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_GammaS80[GR] << _Rshift)|(_GammaS80[GG] << _Gshift) | _GammaS80[GB];
			*pDst++ = a | (a << 16); //�����Q�{�g��(80%�c�X�L�������C����)
		}
		pDst0 += _Pitch3;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�X�V�B32�r�b�g�J���[x�R�{�p
static void
zoom3x_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch3;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB];
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB]; //�����Q�{�g��(90%�c�X�L�������C����)
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90%�X�L�������C���ɂ���B
		{
			d = *pSrc++;
			a = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
			*pDst++ = a;
			*pDst++ = a; //�����Q�{�g��(90%�c�X�L�������C����)
		}
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
			*pDst++ = a;
			*pDst++ = a; //�����Q�{�g��
		}
		pDst0 += _Pitch3;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�X�V�Bx2��16�r�b�g�J���[�p�B
static void
zoom2x_dd16(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch2;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = ((_Gamma[GR] << _Rshift)|(_Gamma[GG] << _Gshift) | _Gamma[GB])|
					  (((_GammaS90[GR] << _Rshift)|(_GammaS90[GG] << _Gshift) | _GammaS90[GB]) << 16); //�����Q�{�g��
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_GammaS80[GR] << _Rshift)|(_GammaS80[GG] << _Gshift) | _GammaS80[GB];
			*pDst++ = a | (a << 16); //�����Q�{�g��
		}
		pDst0 += _Pitch2;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�X�V�Bx2��32�r�b�g�J���[�p�B
static void
zoom2x_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch2;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB];
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB]; //�����Q�{�g��(90%�c�X�L�������C����)
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
			*pDst++ = a;
			*pDst++ = a; //�����Q�{�g��(80%�c�X�L�������C����)
		}
		pDst0 += _Pitch2;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�ǉ��B���X�L�������C��16�r�b�g�J���[x�S�{�p�B���x�d���̂��߂��ꂼ��ʃ��[�`���ɁB
static void
zoom4xHS_dd16(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch4;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_Gamma[GR] << _Rshift)|(_Gamma[GG] << _Gshift) | _Gamma[GB];
			*pDst++ = a | (a << 16);
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90%�X�L�������C���ŁBv2.35�X�V
		{
			d = *pSrc++;
			a = (_GammaS90[GR] << _Rshift)|(_GammaS90[GG] << _Gshift) | _GammaS90[GB];
			*pDst++ = a | (a  << 16);
		}
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�R��ڂ�90%�X�L�������C���ŁBv2.35�X�V
		{
			d = *pSrc++;
			a = (_GammaS90[GR] << _Rshift)|(_GammaS90[GG] << _Gshift) | _GammaS90[GB];
			*pDst++ = a | (a << 16);
		}
		pDst = pDst0 + _Pitch3;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_GammaS80[GR] << _Rshift)|(_GammaS80[GG] << _Gshift) | _GammaS80[GB];
			*pDst++ = a | (a << 16);
		}
		pDst0 += _Pitch4;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�ǉ��B���X�L�������C��32�r�b�g�J���[x�S�{�p
static void
zoom4xHS_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch4;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB];
			*pDst++ = a;
			*pDst++ = a; //�����Q�{�g��
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90%�X�L�������C���ŁBv2.35�X�V
		{
			d = *pSrc++;
			a = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
			*pDst++ = a;
			*pDst++ = a; //�����Q�{�g��
		}
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�R��ڂ�90%�X�L�������C���ŁBv2.35�X�V
		{
			d = *pSrc++;
			a = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
			*pDst++ = a;
			*pDst++ = a; //�����Q�{�g��
		}
		pDst = pDst0 + _Pitch3;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
			*pDst++ = a;
			*pDst++ = a; //�����Q�{�g��
		}
		pDst0 += _Pitch4;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�ǉ��B���X�L�������C��16�r�b�g�J���[x�R�{�p
static void
zoom3xHS_dd16(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch3;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_Gamma[GR] << _Rshift)|(_Gamma[GG] << _Gshift) | _Gamma[GB];
			*pDst++ = a | (a << 16);
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90%�X�L�������C���ɂ���B
		{
			d = *pSrc++;
			a = (_GammaS90[GR] << _Rshift)|(_GammaS90[GG] << _Gshift) | _GammaS90[GB];
			*pDst++ = a | (a << 16);
		}
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_GammaS80[GR] << _Rshift)|(_GammaS80[GG] << _Gshift) | _GammaS80[GB];
			*pDst++ = a | (a << 16);
		}
		pDst0 += _Pitch3;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�ǉ��B���X�L�������C��32�r�b�g�J���[x�R�{�p
static void
zoom3xHS_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch3;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB];
			*pDst++ = a;
			*pDst++ = a; //�����Q�{�g��
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90%�X�L�������C���ɂ���B
		{
			d = *pSrc++;
			a = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
			*pDst++ = a;
			*pDst++ = a; //�����Q�{�g��
		}
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
			*pDst++ = a;
			*pDst++ = a; //�����Q�{�g��
		}
		pDst0 += _Pitch3;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�ǉ��Bx2�̉��X�L�������C��16�r�b�g�J���[�p�B
static void
zoom2xHS_dd16(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch2;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_Gamma[GR] << _Rshift)|(_Gamma[GG] << _Gshift) | _Gamma[GB];
			*pDst++ = a | (a << 16);
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_GammaS80[GR] << _Rshift)|(_GammaS80[GG] << _Gshift) | _GammaS80[GB];
			*pDst++ = a | (a << 16);
		}
		pDst0 += _Pitch2;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�ǉ��Bx2�̉��X�L�������C��32�r�b�g�J���[�p�B
static void
zoom2xHS_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch2;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB];
			*pDst++ = a;
			*pDst++ = a; //�����Q�{�g��
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			a = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
			*pDst++ = a;
			*pDst++ = a; //�����Q�{�g��
		}
		pDst0 += _Pitch2;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�X�V�B�m���X�L�������C���p�B2x3x4x��16�r�b�g�J���[�B���x�d���̂��߃X�L�������C���p�Ə����𕪂����B
static void
zoom2x3x4xNS_dd16(
	Sint32		bairitsu,		// 2x��3x��4x���B2x�Ȃ�2�B3x�Ȃ�3�B4x�Ȃ�4�B
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j,k; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�
	Sint32		bairitsu2; //Kitao�ǉ��B�c�̃h�b�g�����{�Ƀf�W�^���g�傷�邩�B2x��3x�Ȃ�2�B4x�Ȃ�3�B

	if (bairitsu == 2)
		bairitsu2 = 2;
	else
		bairitsu2 = bairitsu -1;

	// �X�L�������C���Ȃ�
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*(_Pitch*bairitsu2);
	for (i = 0; i < srcH; i++)
	{
		for (k = 1; k <= bairitsu2; k++) //�c��bairitsu�{�Ƀf�W�^���g�傷��
		{
			pSrc = pSrc0;
			pDst = pDst0;
			for (j = 0; j < *pTvW; j++)
			{
				d = *pSrc++;
				a = (_Gamma[GR] << _Rshift)|(_Gamma[GG] << _Gshift) | _Gamma[GB];
				*pDst++ = a | (a << 16); //�����Q�{�g��(�X�L�������C���Ȃ�)
			}
			pDst0 += _Pitch;
		}
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�X�V�B�m���X�L�������C����2x3x4x�B32�r�b�g�J���[�p
static void
zoom2x3x4xNS_dd32(
	Sint32		bairitsu,		// 2x��3x��4x���B2x�Ȃ�2�B3x�Ȃ�3�B4x�Ȃ�4�B
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j,k; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�
	Sint32		bairitsu2; //Kitao�ǉ��B�c�̃h�b�g�����{�Ƀf�W�^���g�傷�邩�B2x��3x�Ȃ�2�B4x�Ȃ�3�B

	if (bairitsu == 2)
		bairitsu2 = 2;
	else
		bairitsu2 = bairitsu -1;

	// �X�L�������C���Ȃ�
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*(_Pitch*bairitsu2);
	for (i = 0; i < srcH; i++)
	{
		for (k = 1; k <= bairitsu2; k++) //�c��bairitsu�{�Ƀf�W�^���g�傷��
		{
			pSrc = pSrc0;
			pDst = pDst0;
			for (j = 0; j < *pTvW; j++)
			{
				d = *pSrc++;
				a = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB];
				*pDst++ = a;
				*pDst++ = a; //�����Q�{�g��(�X�L�������C���Ȃ�)
			}
			pDst0 += _Pitch;
		}
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�ǉ��B16�r�b�g�J���[x�P�{�p�B�X�L�������C���Ȃ�
static void
zoom1xNS_dd16(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			 //Kitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �P�{�Ȃ̂ŃX�L�������C���͂Ȃ�
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < (*pTvW >> 1); j++) //�\�[�X�����Q�h�b�g���������ށBv2.13�X�V
		{
			d = *pSrc++;
			a = (_Gamma[GR] << _Rshift)|(_Gamma[GG] << _Gshift) | _Gamma[GB];
			d = *pSrc++;
			*pDst++ = a | (((_Gamma[GR] << _Rshift)|(_Gamma[GG] << _Gshift) | _Gamma[GB]) << 16); //�\�[�X�Q�h�b�g�Ԃ񏑂����܂��
		}
		pDst0 += _Pitch;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�ǉ��B32�r�b�g�J���[x�P�{�p�B�X�L�������C���Ȃ�
static void
zoom1xNS_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW, 			//Kitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�

	// �P�{�Ȃ̂ŃX�L�������C���͖���
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB];
		}
		pDst0 += _Pitch;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�ǉ��BTV Mode ��16�r�b�g�J���[���S�p�B���x�d���̂��߂��ꂼ��ʃ��[�`���ɁB
static void
zoom4xTV_dd16(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch4;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < (*pTvW >> 1); j++) //�\�[�X�����Q�h�b�g���������ށBv2.13�X�V
		{
			d = *pSrc++;
			a = (_Gamma[GR] << _Rshift)|(_Gamma[GG] << _Gshift) | _Gamma[GB];
			d = *pSrc++;
			*pDst++ = a | (((_Gamma[GR] << _Rshift)|(_Gamma[GG] << _Gshift) | _Gamma[GB]) << 16); //�\�[�X�Q�h�b�g�Ԃ񏑂����܂��
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < (*pTvW >> 1); j++) //�Q��ڂ�90%�X�L�������C���ŁBv2.35�X�V
		{
			d = *pSrc++;
			a = (_GammaS90[GR] << _Rshift)|(_GammaS90[GG] << _Gshift) | _GammaS90[GB];
			d = *pSrc++;
			*pDst++ = a | (((_GammaS90[GR] << _Rshift)|(_GammaS90[GG] << _Gshift) | _GammaS90[GB]) << 16);
		}
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < (*pTvW >> 1); j++) //�R��ڂ�90%�X�L�������C���ŁBv2.35�X�V
		{
			d = *pSrc++;
			a = (_GammaS90[GR] << _Rshift)|(_GammaS90[GG] << _Gshift) | _GammaS90[GB];
			d = *pSrc++;
			*pDst++ = a | (((_GammaS90[GR] << _Rshift)|(_GammaS90[GG] << _Gshift) | _GammaS90[GB]) << 16);
		}
		pDst = pDst0 + _Pitch3;
		pSrc = pSrc0;
		for (j = 0; j < (*pTvW >> 1); j++)
		{
			d = *pSrc++;
			a = (_GammaS80[GR] << _Rshift)|(_GammaS80[GG] << _Gshift) | _GammaS80[GB];
			d = *pSrc++;
			*pDst++ = a | (((_GammaS80[GR] << _Rshift)|(_GammaS80[GG] << _Gshift) | _GammaS80[GB]) << 16);
		}
		pDst0 += _Pitch4;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�ǉ��BTV Mode ��32�r�b�g�J���[���S�p�B
static void
zoom4xTV_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch4;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB];
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90%�X�L�������C���ŁBv2.35�X�V
		{
			d = *pSrc++;
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
		}
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�R��ڂ�90%�X�L�������C���ŁBv2.35�X�V
		{
			d = *pSrc++;
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
		}
		pDst = pDst0 + _Pitch3;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
		}
		pDst0 += _Pitch4;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�ǉ��BTV Mode ��16�r�b�g�J���[���R�p�B
static void
zoom3xTV_dd16(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch3;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < (*pTvW >> 1); j++) //�\�[�X�����Q�h�b�g���������ށBv2.13�X�V
		{
			d = *pSrc++;
			a = (_Gamma[GR] << _Rshift)|(_Gamma[GG] << _Gshift) | _Gamma[GB];
			d = *pSrc++;
			*pDst++ = a | (((_Gamma[GR] << _Rshift)|(_Gamma[GG] << _Gshift) | _Gamma[GB]) << 16); //�\�[�X�Q�h�b�g�Ԃ񏑂����܂��
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < (*pTvW >> 1); j++) //�Q��ڂ�90%�X�L�������C���ɂ���B
		{
			d = *pSrc++;
			a = (_GammaS90[GR] << _Rshift)|(_GammaS90[GG] << _Gshift) | _GammaS90[GB];
			d = *pSrc++;
			*pDst++ = a | (((_GammaS90[GR] << _Rshift)|(_GammaS90[GG] << _Gshift) | _GammaS90[GB]) << 16);
		}
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < (*pTvW >> 1); j++)
		{
			d = *pSrc++;
			a = (_GammaS80[GR] << _Rshift)|(_GammaS80[GG] << _Gshift) | _GammaS80[GB];
			d = *pSrc++;
			*pDst++ = a | (((_GammaS80[GR] << _Rshift)|(_GammaS80[GG] << _Gshift) | _GammaS80[GB]) << 16);
		}
		pDst0 += _Pitch3;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�ǉ��BTV Mode ��32�r�b�g�J���[���R�p�B
static void
zoom3xTV_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch3;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB];
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90%�X�L�������C���ɂ���B
		{
			d = *pSrc++;
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
		}
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
		}
		pDst0 += _Pitch3;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�X�V�BTV Mode ��16�r�b�g�J���[ ���Q�p�B
static void
zoom2xTV_dd16(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�
	Uint32		a; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch2;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < (*pTvW >> 1); j++) //�\�[�X�����Q�h�b�g���������ށBv2.13�X�V
		{
			d = *pSrc++;
			a = (_Gamma[GR] << _Rshift)|(_Gamma[GG] << _Gshift) | _Gamma[GB];
			d = *pSrc++;
			*pDst++ = a | (((_Gamma[GR] << _Rshift)|(_Gamma[GG] << _Gshift) | _Gamma[GB]) << 16); //�\�[�X�Q�h�b�g�Ԃ񏑂����܂��
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < (*pTvW >> 1); j++)
		{
			d = *pSrc++;
			a = (_GammaS80[GR] << _Rshift)|(_GammaS80[GG] << _Gshift) | _GammaS80[GB];
			d = *pSrc++;
			*pDst++ = a | (((_GammaS80[GR] << _Rshift)|(_GammaS80[GG] << _Gshift) | _GammaS80[GB]) << 16);
		}
		pDst0 += _Pitch2;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Kitao�X�V�BTV Mode ��32�r�b�g�J���[ ���Q�p�B
static void
zoom2xTV_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕��BKitao�ǉ�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j; //Kitao�ǉ�
	Uint32*		pSrc0; //Kitao�ǉ�
	Uint32*		pDst; //Kitao�ǉ�
	Uint32*		pDst0; //Kitao�ǉ�
	Uint32		d; //Kitao�ǉ�

	// �X�L�������C��80%
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch2;
	for (i = 0; i < srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB];
		}
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
		}
		pDst0 += _Pitch2;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//�������[�h 32�r�b�g�J���[�B������(&�\�[�X�R�[�h)�������D��B�e��ʃ��[�h�ŋ��ʏ����͋��ʂ��čs���Bv2.29
#define	DOGREEN	if (bGreen) {b=a+(a>>3)+(a>>4); if (b>0xFF) b=0xFF; a=a>>2;} else {b=a;}
static void
monoColor_32(
	Sint32		bairitsu,		// �E�B���h�E�\���{��
	Sint32		scanLineType,	// �X�L�������C���̃^�C�v
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕�
	Sint32		srcH,			// �]�����̍���
	Sint32		bGreen)			// �O���[���f�B�X�v���C
{
	int			q,i,j,k;
	Uint32*		pSrc0;
	Uint32*		pDst;
	Uint32*		pDst0;
	Uint32		d;
	Uint32		a;
	Uint32		b;
	int			sl;
	BOOL		bSpecial;

	if (bairitsu == 1)
		scanLineType = 0;
	if (((scanLineType == 2)||(scanLineType == 0)||(scanLineType >= 5))&&(bairitsu >= 2))
		sl = 2; //���X�L�������C�����m���X�L�������C���̏ꍇ
	else
		sl = 1;
	if ((scanLineType == 0)||(scanLineType == 7)||(scanLineType == 8)) //�m���X�L�������C����
	{
		if (bairitsu >= 3)
			bairitsu--;
		pSrc0 = pSrc;
		pDst0 = _pPixels + srcY*_Pitch*bairitsu;
		for (i=0; i<srcH; i++)
		{
			for (q=1; q<=bairitsu; q++)
			{
				pSrc = pSrc0;
				pDst = pDst0;
				for (j=0; j<*pTvW; j++)
				{
					d = *pSrc++;
					a = _MonoTableR[_Gamma[GR]] + _MonoTableG[_Gamma[GG]] + _MonoTableB[_Gamma[GB]]; DOGREEN //R,G,B�̋P�x�𕽋ω��BDOGREEN��`�cbGreen��TRUE�Ȃ�O���[���f�B�X�v���C��
					for (k=0; k<sl; k++) //���X�L�������C���̏ꍇ�A�����h�b�g�łQ�{�g��B
						*pDst++ = (a << 16)|(b << 8)| a; //���m�N�����B�P�h�b�g�Ԃ񏑂����܂��B
				}
				*pDst = 0; //Direct3D�ł͉E�[�ɂP�h�b�g�Ԃ�N���A(��)�}�[�W���������Ă����Ȃ��ƉE�[�������B
				pDst0 += _Pitch;
			}
			pSrc0 += SOURCE_PITCH;
			pTvW++;
		}
	}
	else //�X�L�������C����
	{	
		// �X�L�������C��80%
		bSpecial = (scanLineType == 1); //�c���X�L�������C���̏ꍇTRUE�Bv2.78
		pSrc0 = pSrc;
		pDst0 = _pPixels + srcY*_Pitch*bairitsu;
		for (i=0; i<srcH; i++)
		{
			pSrc = pSrc0;
			pDst = pDst0;
			for (j=0; j<*pTvW; j++)
			{
				d = *pSrc++;
				a = _MonoTableR[_Gamma[GR]] + _MonoTableG[_Gamma[GG]] + _MonoTableB[_Gamma[GB]]; DOGREEN //R,G,B�̋P�x�𕽋ω��BDOGREEN��`�cbGreen��TRUE�Ȃ�O���[���f�B�X�v���C��
					for (k=0; k<sl; k++) //���X�L�������C���̏ꍇ�A�����h�b�g�łQ�{�g��B
					*pDst++ = (a << 16)|(b << 8)| a; //���m�N�����B�P�h�b�g�Ԃ񏑂����܂��B
				if (bSpecial) //�c���X�L�������C���̏ꍇ
				{
					a = _MonoTableR[_GammaS90[GR]] + _MonoTableG[_GammaS90[GG]] + _MonoTableB[_GammaS90[GB]]; DOGREEN //R,G,B�̋P�x�𕽋ω�
					*pDst++ = (a << 16)|(b << 8)| a; //�P�h�b�g�Ԃ񏑂����܂��B�����Q�{�g��(90%�c�X�L�������C����)
				}
			}
			*pDst = 0; //Direct3D�ł͉E�[�ɂP�h�b�g�Ԃ�N���A(��)�}�[�W���������Ă����Ȃ��ƉE�[�������B
			pDst = pDst0 + _Pitch;
			pSrc = pSrc0;
			switch (bairitsu)
			{
			case 4: //x4�{
				for (j=0; j<*pTvW; j++) //�Q��ڂ�90%�X�L�������C���ŁBv2.35�X�V
				{
					d = *pSrc++;
					a = _MonoTableR[_GammaS90[GR]] + _MonoTableG[_GammaS90[GG]] + _MonoTableB[_GammaS90[GB]]; DOGREEN //R,G,B�̋P�x�𕽋ω�
					for (k=0; k<sl; k++) //���X�L�������C���̏ꍇ�A�����h�b�g�łQ�{�g��B
						*pDst++ = (a << 16)|(b << 8)| a; //���m�N�����B�P�h�b�g�Ԃ񏑂����܂��B
					if (bSpecial) //�c���X�L�������C���̏ꍇ
						*pDst++ = (a << 16)|(b << 8)| a; //���m�N�����B�P�h�b�g�Ԃ񏑂����܂��B�����Q�{�g��(90%�c�X�L�������C����)
				}
				*pDst = 0;
				pDst = pDst0 + _Pitch2;
				pSrc = pSrc0;
				for (j=0; j <*pTvW; j++) //�R��ڂ�90%�X�L�������C���ŁBv2.35�X�V
				{
					d = *pSrc++;
					a = _MonoTableR[_GammaS90[GR]] + _MonoTableG[_GammaS90[GG]] + _MonoTableB[_GammaS90[GB]]; DOGREEN //R,G,B�̋P�x�𕽋ω�
					for (k=0; k<sl; k++) //���X�L�������C���̏ꍇ�A�����h�b�g�łQ�{�g��B
						*pDst++ = (a << 16)|(b << 8)| a; //���m�N�����B�P�h�b�g�Ԃ񏑂����܂��B
					if (bSpecial) //�c���X�L�������C���̏ꍇ
						*pDst++ = (a << 16)|(b << 8)| a; //���m�N�����B�P�h�b�g�Ԃ񏑂����܂��B�����Q�{�g��(90%�c�X�L�������C����)
				}
				*pDst = 0;
				pDst = pDst0 + _Pitch3;
				break;
			case 3: //x3�{
				for (j=0; j<*pTvW; j++) //�Q��ڂ�90%�X�L�������C����
				{
					d = *pSrc++;
					a = _MonoTableR[_GammaS90[GR]] + _MonoTableG[_GammaS90[GG]] + _MonoTableB[_GammaS90[GB]]; DOGREEN //R,G,B�̋P�x�𕽋ω�
					for (k=0; k<sl; k++) //���X�L�������C���̏ꍇ�A�����h�b�g�łQ�{�g��B
						*pDst++ = (a << 16)|(b << 8)| a; //���m�N�����B�P�h�b�g�Ԃ񏑂����܂��B
					if (bSpecial) //�c���X�L�������C���̏ꍇ
						*pDst++ = (a << 16)|(b << 8)| a; //���m�N�����B�P�h�b�g�Ԃ񏑂����܂��B�����Q�{�g��(90%�c�X�L�������C����)
				}
				*pDst = 0;
				pDst = pDst0 + _Pitch2;
				break;
				//case 2: //x2�{
				//	x2�{�̂Ƃ��͏����Ȃ��B
			}
			if (bairitsu >= 2)
			{
				pSrc = pSrc0;
				for (j=0; j<*pTvW; j++)
				{
					d = *pSrc++;
					a = _MonoTableR[_GammaS80[GR]] + _MonoTableG[_GammaS80[GG]] + _MonoTableB[_GammaS80[GB]]; DOGREEN //R,G,B�̋P�x�𕽋ω�
					for (k=0; k<sl; k++) //���X�L�������C���̏ꍇ�A�����h�b�g�łQ�{�g��B
						*pDst++ = (a << 16)|(b << 8)| a; //���m�N�����B�P�h�b�g�Ԃ񏑂����܂��B
					if (bSpecial) //�c���X�L�������C���̏ꍇ
						*pDst++ = (a << 16)|(b << 8)| a; //���m�N�����B�P�h�b�g�Ԃ񏑂����܂��B�����Q�{�g��(80%�c�X�L�������C����)
				}
				*pDst = 0;
			}
			pDst0 += _Pitch * bairitsu;
			pSrc0 += SOURCE_PITCH;
			pTvW++;
		}
	}
}
#undef DOGREEN

//�������[�h 16�r�b�g�J���[�B������(&�\�[�X�R�[�h)�������D��B�e��ʃ��[�h�ŋ��ʏ����͋��ʂ��čs���Bv2.29
#define	DOGREEN		if (bGreen) {b=a+(a>>3)+(a>>4); if (b>0x1F) b=0x1F; a=a>>2;} else {b=a;}
#define	DOGREEN2	if (bGreen) {b2=a2+(a2>>3)+(a2>>4); if (b2>0x1F) b2=0x1F; a2=a2>>2;} else {b2=a2;}
static void
monoColor_16(
	Sint32		bairitsu,		// �E�B���h�E�\���{��
	Sint32		scanLineType,	// �X�L�������C���̃^�C�v
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕�
	Sint32		srcH,			// �]�����̍���
	Sint32		bGreen)			// �O���[���f�B�X�v���C
{
	int			i,j;
	Uint32*		pSrc0;
	Uint32*		pDst;
	Uint32*		pDst0;
	Uint32		d;
	Uint32		a,a2;
	Uint32		b,b2;
	int			sl;
	BOOL		bSpecial;

	if (bairitsu == 1)
		scanLineType = 0;
	if (((scanLineType == 2)||(scanLineType == 0)||(scanLineType >= 5))&&(bairitsu >= 2))
		sl = 2; //���X�L�������C�����m���X�L�������C���̏ꍇ
	else
		sl = 1;
	if ((scanLineType == 0)||(scanLineType == 7)||(scanLineType == 8)) //�m���X�L�������C����
	{
		if (bairitsu >= 3)
			bairitsu--;
	}
	bSpecial = (scanLineType == 1); //�c���X�L�������C���̏ꍇTRUE�Bv2.78

	// �X�L�������C��80%�Œ�
	pSrc0 = pSrc;
	pDst0 = _pPixels + srcY*_Pitch*bairitsu;
	for (i=0; i<srcH; i++)
	{
		pSrc = pSrc0;
		pDst = pDst0;
		for (j=0; j<*pTvW; j++)
		{
			d = *pSrc++;
			a = _MonoTableR[_Gamma[GR]] + _MonoTableG[_Gamma[GG]] + _MonoTableB[_Gamma[GB]]; DOGREEN //R,G,B�̋P�x�𕽋ω��BDOGREEN��`�cbGreen��TRUE�Ȃ�O���[���f�B�X�v���C��
			if (sl == 2) //���X�L�������C���̏ꍇ�A�����h�b�g�łQ�{�g��B
				*pDst++ = ((a << _Rshift) | (b << _Gshift) | a) | (((a << _Rshift) | (b << _Gshift) | a) << 16); //���m�N�����B�Q�h�b�g�Ԃ񏑂����܂��B
			else if (bSpecial) //�c���X�L�������C���̏ꍇ
			{
				a2 = _MonoTableR[_GammaS90[GR]] + _MonoTableG[_GammaS90[GG]] + _MonoTableB[_GammaS90[GB]]; DOGREEN2 //R,G,B�̋P�x�𕽋ω�
				*pDst++ = ((a << _Rshift) | (b << _Gshift) | a) | (((a2 << _Rshift) | (b2 << _Gshift) | a2) << 16); //���m�N�����B�Q�h�b�g�Ԃ񏑂����܂��B�����Q�{�g��(90%�c�X�L�������C����)
			}
			else
			{
				d = *pSrc++;
				a2 = _MonoTableR[_Gamma[GR]] + _MonoTableG[_Gamma[GG]] + _MonoTableB[_Gamma[GB]]; DOGREEN2 //R,G,B�̋P�x�𕽋ω��BDOGREEN2��`�cbGreen��TRUE�Ȃ�O���[���f�B�X�v���C��
				*pDst++ = ((a << _Rshift) | (b << _Gshift) | a) | (((a2 << _Rshift) | (b2 << _Gshift) | a2) << 16); //���m�N�����B�Q�h�b�g�Ԃ񏑂����܂��B
				j++; //�\�[�X�Q�h�b�g�Ԃ����x�ɏ�������
			}
		}
		*pDst = 0; //Direct3D�ł͉E�[�ɂP�h�b�g�Ԃ�N���A(��)�}�[�W���������Ă����Ȃ��ƉE�[�������B
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		switch (bairitsu)
		{
			case 4: //x4�{
				for (j=0; j<*pTvW; j++) //�Q��ڂ�90%�X�L�������C���ŁBv2.35�X�V
				{
					d = *pSrc++;
					a = _MonoTableR[_GammaS90[GR]] + _MonoTableG[_GammaS90[GG]] + _MonoTableB[_GammaS90[GB]]; DOGREEN //R,G,B�̋P�x�𕽋ω�
					if (sl == 2) //���X�L�������C���̏ꍇ�A�����h�b�g�łQ�{�g��B
						*pDst++ = ((a << _Rshift) | (b << _Gshift) | a) | (((a << _Rshift) | (b << _Gshift) | a) << 16); //���m�N�����B�Q�h�b�g�Ԃ񏑂����܂��B
					else if (bSpecial) //�c���X�L�������C���̏ꍇ
						*pDst++ = ((a << _Rshift) | (b << _Gshift) | a) | (((a << _Rshift) | (b << _Gshift) | a) << 16); //���m�N�����B�Q�h�b�g�Ԃ񏑂����܂��B�����Q�{�g��(90%�c�X�L�������C����)
					else
					{
						d = *pSrc++;
						a2 = _MonoTableR[_GammaS90[GR]] + _MonoTableG[_GammaS90[GG]] + _MonoTableB[_GammaS90[GB]]; DOGREEN2 //R,G,B�̋P�x�𕽋ω��BDOGREEN2��`�cbGreen��TRUE�Ȃ�O���[���f�B�X�v���C��
						*pDst++ = ((a << _Rshift) | (b << _Gshift) | a) | (((a2 << _Rshift) | (b2 << _Gshift) | a2) << 16); //���m�N�����B�Q�h�b�g�Ԃ񏑂����܂��B
						j++; //�\�[�X�Q�h�b�g�Ԃ����x�ɏ�������
					}
				}
				*pDst = 0;
				pDst = pDst0 + _Pitch2;
				pSrc = pSrc0;
				for (j=0; j <*pTvW; j++) //�R��ڂ�90%�X�L�������C���ŁBv2.35�X�V
				{
					d = *pSrc++;
					a = _MonoTableR[_GammaS90[GR]] + _MonoTableG[_GammaS90[GG]] + _MonoTableB[_GammaS90[GB]]; DOGREEN //R,G,B�̋P�x�𕽋ω�
					if ((sl == 2)||(bSpecial)) //���X�L�������C�����c���X�L�������C���̏ꍇ�A�����h�b�g�łQ�{�g��B
						*pDst++ = ((a << _Rshift) | (b << _Gshift) | a) | (((a << _Rshift) | (b << _Gshift) | a) << 16); //���m�N�����B�Q�h�b�g�Ԃ񏑂����܂��B
					else
					{
						d = *pSrc++;
						a2 = _MonoTableR[_GammaS90[GR]] + _MonoTableG[_GammaS90[GG]] + _MonoTableB[_GammaS90[GB]]; DOGREEN2 //R,G,B�̋P�x�𕽋ω��BDOGREEN2��`�cbGreen��TRUE�Ȃ�O���[���f�B�X�v���C��
						*pDst++ = ((a << _Rshift) | (b << _Gshift) | a) | (((a2 << _Rshift) | (b2 << _Gshift) | a2) << 16); //���m�N�����B�Q�h�b�g�Ԃ񏑂����܂��B
						j++; //�\�[�X�Q�h�b�g�Ԃ����x�ɏ�������
					}
				}
				*pDst = 0;
				pDst = pDst0 + _Pitch3;
				break;
			case 3: //x3�{
				for (j=0; j<*pTvW; j++) //�Q��ڂ�90%�X�L�������C����
				{
					d = *pSrc++;
					a = _MonoTableR[_GammaS90[GR]] + _MonoTableG[_GammaS90[GG]] + _MonoTableB[_GammaS90[GB]]; DOGREEN //R,G,B�̋P�x�𕽋ω�
					if ((sl == 2)||(bSpecial)) //���X�L�������C�����c���X�L�������C���̏ꍇ�A�����h�b�g�łQ�{�g��B
						*pDst++ = ((a << _Rshift) | (b << _Gshift) | a) | (((a << _Rshift) | (b << _Gshift) | a) << 16); //���m�N�����B�Q�h�b�g�Ԃ񏑂����܂��B
					else
					{
						d = *pSrc++;
						a2 = _MonoTableR[_GammaS90[GR]] + _MonoTableG[_GammaS90[GG]] + _MonoTableB[_GammaS90[GB]]; DOGREEN2 //R,G,B�̋P�x�𕽋ω��BDOGREEN2��`�cbGreen��TRUE�Ȃ�O���[���f�B�X�v���C��
						*pDst++ = ((a << _Rshift) | (b << _Gshift) | a) | (((a2 << _Rshift) | (b2 << _Gshift) | a2) << 16); //���m�N�����B�Q�h�b�g�Ԃ񏑂����܂��B
						j++; //�\�[�X�Q�h�b�g�Ԃ����x�ɏ�������
					}
				}
				*pDst = 0;
				pDst = pDst0 + _Pitch2;
				break;
			//case 2: //x2�{
			//	x2�{�̂Ƃ��͏����Ȃ��B
		}
		if (bairitsu >= 2)
		{
			pSrc = pSrc0;
			for (j=0; j<*pTvW; j++)
			{
				d = *pSrc++;
				a = _MonoTableR[_GammaS80[GR]] + _MonoTableG[_GammaS80[GG]] + _MonoTableB[_GammaS80[GB]]; DOGREEN //R,G,B�̋P�x�𕽋ω�
				if ((sl == 2)||(bSpecial)) //���X�L�������C�����c���X�L�������C���̏ꍇ�A�����h�b�g�łQ�{�g��B
					*pDst++ = ((a << _Rshift) | (b << _Gshift) | a) | (((a << _Rshift) | (b << _Gshift) | a) << 16); //���m�N�����B�Q�h�b�g�Ԃ񏑂����܂��B
				else
				{
					d = *pSrc++;
					a2 = _MonoTableR[_GammaS80[GR]] + _MonoTableG[_GammaS80[GG]] + _MonoTableB[_GammaS80[GB]]; DOGREEN2 //R,G,B�̋P�x�𕽋ω��BDOGREEN2��`�cbGreen��TRUE�Ȃ�O���[���f�B�X�v���C��
					*pDst++ = ((a << _Rshift) | (b << _Gshift) | a) | (((a2 << _Rshift) | (b2 << _Gshift) | a2) << 16); //���m�N�����B�Q�h�b�g�Ԃ񏑂����܂��B
					j++; //�\�[�X�Q�h�b�g�Ԃ����x�ɏ�������
				}
			}
			*pDst = 0;
		}
		pDst0 += _Pitch * bairitsu;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}
#undef DOGREEN16
#undef GR
#undef GG
#undef GB


/*-----------------------------------------------------------------------------
	[Blt]
		pSrc ����o�b�N�o�b�t�@�։摜���������݂܂��B�g��^�k���A
-----------------------------------------------------------------------------*/
//Kitao�X�V�B�K���n�[�h�E�F�A�A�N�Z�����[�V�������g�p����B
//			 ���C�����Ƃɉ𑜓x��ς��Ă���Q�[���i���Ղ̌��C������120%�Ȃǁj�ɂ��Ή��B
void
SCREENDD_Blt(
	Uint32*		pSrc,
	Sint32		srcX,
	Sint32		srcY,
	Uint16*		pTvW,	//Kitao�X�V�B�]�����̉��s�N�Z�����B��srcH���C���̐��Ԃ�
	Sint32		srcH,
	Sint32		executeCode)  //Kitao�ǉ��B���s�R�[�h�B0�c�G���R�[�h�����s���B1�c�v���C�}����ʂ֓]�����s���B2�c�X�N���[���V���b�g�p��ʂ֓]�����s���B
							  //					   3�c���E�ɍ���(�I�[�o�[�X�L������)��z�u���Ă̓]��(���Ƃ�1�Ɠ���)�B4�c�X�N���[���V���b�g��̉�ʕ����]�����s���B
							  //v2.12�X�V			   5�c���E�̃I�[�o�[�X�L���������J�b�g���Ă̓]��(���Ƃ�1�Ɠ���)
{
	Uint32*		pSrc32;
	Uint16*		pTvW2;
	Sint32		scanLineType = APP_GetScanLineType();

	if (pSrc==NULL) return;

	//v1.28�X�V�B���C���r������̃G���R�[�h�ɑΉ��B
	pSrc32 = (Uint32*)pSrc + srcY * 512 + srcX;
	pTvW2 = pTvW + srcY;

	//Kitao�X�V�B
	if (srcH > 0) //v2.43�X�V
	{
		if (lock_offscreen_surface(&_Pitch, &_pPixels)) //�o�b�N�T�[�t�F�X�����b�N
		{
			_Pitch2 = _Pitch * 2;
			_Pitch3 = _Pitch * 3;
			_Pitch4 = _Pitch * 4;

			//Kitao�X�V�B���x�d���̂��߂��ꂼ��̉�ʃ��[�h�ŁA�ʁX�̃��[�`�����g���B
			if (MAINBOARD_GetMonoColor()) //�������[�h�Ȃ�B�͂ɂ����񂴂�����,�p���[�h���t�g���̗��Z
			{	//�������[�h�̏ꍇ�Bv2.28,2.29
				if (_BitsPerPixel == 16)
					monoColor_16(_Magnification, scanLineType, pSrc32, srcY, pTvW2, srcH, (MAINBOARD_GetForceMonoColor() == 2)); //16bit�J���[
				else
					monoColor_32(_Magnification, scanLineType, pSrc32, srcY, pTvW2, srcH, (MAINBOARD_GetForceMonoColor() == 2)); //32bit�J���[
			}
			else
			{	//�ʏ�
				switch (scanLineType)
				{
					case 0: //�m���X�L�������C��
					case 7: //�m���X�L�������C��2
					case 8: //�m���X�L�������C��TV
						switch (_Magnification)
						{
							case 1:
								if (_BitsPerPixel == 16)
									zoom1xNS_dd16(pSrc32, srcY, pTvW2, srcH); //16bit�J���[
								else
									zoom1xNS_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
								break;
							case 2:
							case 3:
							case 4:
								if (_BitsPerPixel == 16)
									zoom2x3x4xNS_dd16(_Magnification, pSrc32, srcY, pTvW2, srcH); //16bit�J���[
								else
									zoom2x3x4xNS_dd32(_Magnification, pSrc32, srcY, pTvW2, srcH); //32bit�J���[
								break;
						}
						break;
					case 1: //�c���X�L�������C��
						switch (_Magnification)
						{
							case 1:
								if (_BitsPerPixel == 16)
									zoom1xNS_dd16(pSrc32, srcY, pTvW2, srcH); //16bit�J���[
								else
									zoom1xNS_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
								break;
							case 2:
								if (_BitsPerPixel == 16)
									zoom2x_dd16(pSrc32, srcY, pTvW2, srcH); //16bit�J���[
								else
									zoom2x_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
								break;
							case 3:
								if (_BitsPerPixel == 16)
									zoom3x_dd16(pSrc32, srcY, pTvW2, srcH); //16bit�J���[
								else
									zoom3x_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
								break;
							case 4:
								if (_BitsPerPixel == 16)
									zoom4x_dd16(pSrc32, srcY, pTvW2, srcH); //16bit�J���[
								else
									zoom4x_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
								break;
						}
						break;
					case 2: //���X�L�������C��
					case 5: //���X�L�������C��2
					case 6: //���X�L�������C��3
						switch (_Magnification)
						{
							case 1:
								if (_BitsPerPixel == 16)
									zoom1xNS_dd16(pSrc32, srcY, pTvW2, srcH); //16bit�J���[
								else
									zoom1xNS_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
								break;
							case 2:
								if (_BitsPerPixel == 16)
									zoom2xHS_dd16(pSrc32, srcY, pTvW2, srcH); //16bit�J���[
								else
									zoom2xHS_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
								break;
							case 3:
								if (_BitsPerPixel == 16)
									zoom3xHS_dd16(pSrc32, srcY, pTvW2, srcH); //16bit�J���[
								else
									zoom3xHS_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
								break;
							case 4:
								if (_BitsPerPixel == 16)
									zoom4xHS_dd16(pSrc32, srcY, pTvW2, srcH); //16bit�J���[
								else
									zoom4xHS_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
								break;
						}
						break;
					case 3: //���X�L�������C���Q(Fast)
					case 4: //TV���X�L�������C��
						switch (_Magnification)
						{
							case 1: //�m���X�L�������C���Ɠ���
								if (_BitsPerPixel == 16)
									zoom1xNS_dd16(pSrc32, srcY, pTvW2, srcH); //16bit�J���[
								else
									zoom1xNS_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
								break;
							case 2:
								if (_BitsPerPixel == 16)
									zoom2xTV_dd16(pSrc32, srcY, pTvW2, srcH); //16bit�J���[
								else
									zoom2xTV_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
								break;
							case 3:
								if (_BitsPerPixel == 16)
									zoom3xTV_dd16(pSrc32, srcY, pTvW2, srcH); //16bit�J���[
								else
									zoom3xTV_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
								break;
							case 4:
								if (_BitsPerPixel == 16)
									zoom4xTV_dd16(pSrc32, srcY, pTvW2, srcH); //16bit�J���[
								else
									zoom4xTV_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
								break;
						}
						break;
				}
			}
	
			//���b�N������
			_pDDSBack->Unlock(NULL);
		}
	}		

	//�v���C�}����ʂւ̓]��
	if (executeCode > 0)
		zoom_ddTensou(pTvW+(16-MAINBOARD_GetShowOverscanTop()),
					  srcY+srcH-(16-MAINBOARD_GetShowOverscanTop()),
					  executeCode);
}


//Kitao�ǉ��BVSync(�����A���҂�)���s�����ǂ�����ݒ�
void
SCREENDD_SetSyncTo60HzScreen(
	BOOL	bSyncTo60HzScreen)
{
	DEVMODE		dm; //Kitao�ǉ�

	//�f�B�X�v���C�̌��݂̕\�����g�������߂�BV-Sync���s���邩�ǂ������f����B
	memset(&dm, 0, sizeof(DEVMODE));
	dm.dmSize = sizeof(DEVMODE);
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
	if ((dm.dmDisplayFrequency == 60)||(dm.dmDisplayFrequency == 59)||(dm.dmDisplayFrequency == 61)) //���t���b�V�����[�g��60Hz(59��61���܂�)�������ݒ�̂Ƃ��BForceVSync��v2.65����p�~�B
	{
		_bSyncTo60HzScreen = APP_GetSyncTo60HzScreen();
		APP_EnableVSyncMenu(TRUE); //���j���[�X�V
	}
	else
	{
		_bSyncTo60HzScreen = FALSE;
		APP_EnableVSyncMenu(FALSE); //���j���[�X�V
	}
}

//VSync(�����A���҂�)���s���Ă��邩�ǂ�����Ԃ��BVSync������ݒ�ł�Sync�ł��Ȃ����̏ꍇ��FALSE���Ԃ�Bv2.43
BOOL
SCREENDD_GetSyncTo60HzScreen()
{
	return _bSyncTo60HzScreen;
}


//Kitao�ǉ��B�O���VBlank�҂����I�����������Ԃ��Bv1.28
DWORD
SCREENDD_GetLastTimeSyncTime()
{
	return _LastTimeSyncTime;
}


//Kitao�ǉ��B�X�N���[���V���b�g���t�@�C���ɏ������ށBv2.12
void
SCREENDD_WriteScreenshot(
	FILE*	fp)
{
	int				i,j;
	HRESULT			hr;
	int				trial = 10;
	LONG			pitch;
	Uint32*			pPixels0;
	Uint32*			pPixels;
	Uint32			BGRR; //Bule,Green,Red,Reserved
	Sint32			width;
	Sint32			height;
	Sint32			left;
	Sint32			top;
	Sint32			w2,h2;
	RECT			rc;
	Sint32			wp;

	//�o�b�t�@�ɍĕ`�悷��B
	if (((APP_GetOverscanHideBlackLR())&&(MAINBOARD_GetShowOverscanLeft() == 0))|| //���E�̃I�[�o�[�X�L�����̈�ɍ��ѕ\�����Ă����ꍇ
		((APP_GetOverscanHideBlackTop())&&(MAINBOARD_GetShowOverscanTop() < 8))) //�㑤�̃I�[�o�[�X�L�����̈�ɍ��ѕ\�����Ă����ꍇ
			MAINBOARD_SetResolutionChange(TRUE); //�`�掞�ɃS�~���c��Ȃ��悤�ɉ�ʑS�̂��N���A���Ă���`�悷��B
	MAINBOARD_DrawScreenshot();
	MAINBOARD_SetResolutionChange(FALSE); //���ɖ߂�

	//�T�C�Y���v�Z
	width = APP_GetGameWidth(_Magnification);
	height = APP_GetGameHeight(_Magnification);
	wp = 4 - (width*3 % 4); //�P���C����4byte�P�ʂɐ����邽�߂̒l
	if (wp==4) wp=0;

	//����̈ʒu���v�Z
	if (_Flags & SCREEN_FFULLSCREEN)
	{
		if (APP_GetFullStretched(TRUE))
		{
			//�A�X�y�N�g���4:3�ɕۂ�
			if (_Width/4 >= _Height/3)
			{	//�c�̂ق����Z���̂ŏc����Ƃ���
				w2 = (Sint32)((double)(_Height / 3.0 * 4.0 + 0.5));
				left = (_Width - w2) / 2;
				if (MAINBOARD_GetShowOverscanLeft() > 0) //���E�̃I�[�o�[�X�L�����̈��\������Ȃ�
					top = (_Height - (Sint32)((double)_Height * 0.96137 + 0.5)) / 2; //0.96137=224/((268-256)/4*3+224)
				else
					top = 0;
			}
			else
			{	//���̂ق����Z���̂ŉ�����Ƃ���
				h2 = (Sint32)((double)(_Width / 4.0 * 3.0 + 0.5));
				left = 0;
				if (MAINBOARD_GetShowOverscanLeft() > 0) //���E�̃I�[�o�[�X�L�����̈��\������Ȃ�
					top = (_Height - (Sint32)((double)h2 * 0.96137 + 0.5)) / 2; //0.96137=224/((268-256)/4*3+224)
				else
					top = (_Height - h2) / 2;
			}
		}
		else if (APP_GetStretched())
		{
			if (MAINBOARD_GetShowOverscanLeft() > 0) //���E�̃I�[�o�[�X�L�����̈��\������Ȃ�
				w2 = (Sint32)(313.24 * (double)_Magnification + 0.5);
			else
				w2 = 299 * _Magnification;
			if (APP_GetVStretched()) //�c��ʃ��[�h�Ȃ�
				w2 = (Sint32)((double)w2 * (256.0/336.0));
			//�A�X�y�N�g���TV��ʂƓ���4:3�ɁB�c�̒�������PCE�W��224�̐����{(�Q�{)�ɂ���
			left = (_Width - w2) / 2;
			top = (_Height - 224*_Magnification) / 2;
			if (MAINBOARD_GetShowOverscanTop() > 0) //�㑤�̃I�[�o�[�X�L�����̈��\������Ȃ�
			{
				top -= MAINBOARD_GetShowOverscanTop() * _Magnification;
				if (top < 0) //��ʂ���͂ݏo���Ă��܂��ꍇ�B1440x900,1600x900�Ȃǂł��蓾��B
					top = (_Height - 224*_Magnification) / 2; //�A�X�y�N�g���ۂ��߁A�I�[�o�[�X�L���������J�b�g�B
			}
		}
		else //�m���X�g���b�`�̏ꍇ
		{
			w2 = APP_GetNonstretchedWidth() * _Magnification;
			if (w2 > _Width) w2 = _Width; //��ʂ���͂ݏo���Ă��܂��ꍇ�́A�X�g���b�`(�k��)���đΉ��B
			left = (_Width - w2) / 2;
			top = (_Height - 224*_Magnification) / 2;
			if (MAINBOARD_GetShowOverscanTop() > 0) //�㑤�̃I�[�o�[�X�L�����̈��\������Ȃ�
			{
				top -= MAINBOARD_GetShowOverscanTop() * _Magnification;
				if (top < 0) top = 0; //��ʂ���͂ݏo���Ă��܂��ꍇ�́A�X�g���b�`(�k��)���đΉ��B1440x900,1600x900�Ȃǂł��蓾��B
			}
		}
	}
	else
	{
		GetWindowRect(_hWnd, &rc);
		left = rc.left + (rc.right - rc.left - _Width)/2;
		top = rc.bottom - (rc.right - rc.left - _Width)/2 - _Height; //�g�̑����ƕ\���̈�̍����Ԃ������
	}

	//�L���v�`�����郁���������b�N
	while (trial--)
	{
		hr = _pDDSPrimary->Lock(NULL, &_ddsdPrimary, DDLOCK_WAIT | DDLOCK_READONLY, NULL); //READONLY�ō������Bv2.28
		if (hr == DD_OK)
			break;
    }
	if (hr != DD_OK) return;

	pitch = _ddsdPrimary.lPitch / 4; //32bit�P�ʂŏ������邽�߃s�b�`��1/4�ɁB
	pPixels0 = (Uint32*)_ddsdPrimary.lpSurface + pitch*(top+height-1) + left; //�ŉ��i����t�@�C���ɏo�͂��čs��(BMP�̎d�l)�B

	for (i = 0; i < height; i++)
	{
		pPixels = pPixels0;
		for (j = 0; j < width; j++)
		{
			BGRR = (*pPixels++);
			fwrite(&BGRR, 3, 1, fp); //BGR������������
		}
		if (wp > 0)
		{	//�P���C����4byte�P�ʂɐ�����
			BGRR = 0;
			fwrite(&BGRR, wp, 1, fp);
		}
		pPixels0 -= pitch;
	}
	
	//���b�N������
	_pDDSPrimary->Unlock(NULL);
}


//Kitao�ǉ��B�X�N���[���V���b�g���̂��߂Ɉꎞ�I�ɕ`��{����ύX����BScreen.cpp����g�p�Bv2.13
void
SCREENDD_SetMagnification(
	Sint32	magnification)
{
	_Magnification = magnification;
}

//Kitao�ǉ��Bv2.13
Sint32
SCREENDD_GetMagnification()
{
	return _Magnification;
}

//Kitao�ǉ��Bv2.28
Sint32
SCREENDD_GetBitsPerPixel()
{
	return _BitsPerPixel;
}


//���C��(�Q�[��)��ʗp�I�t�X�N���[�����P�F�œh��Ԃ��A�v���C�}����ʂ֓]������Bv2.77�X�V
//���v���C�}����ʂ֓]���������Ȃ��ꍇ�́AbDraw��FALSE�ɂ��ČĂԁB
void
SCREENDD_Fill(
	Uint32		color,
	BOOL		bDraw)
{
	int			i,j;
	LONG		pitch;
	Uint32*		pPixels;
	Uint32*		pPixels0;
	Uint16		tvW[256];

	if (lock_offscreen_surface(&pitch, &pPixels))
	{
		pPixels0 = pPixels;
		for (i = 0; i < (int)_ddsdBack.dwHeight; i++)
		{
			pPixels = pPixels0;
			if (_BitsPerPixel == 16)
			{
				for (j = 0; j < (int)_ddsdBack.dwWidth/2; j++)
					*pPixels++ = 0; //4byte�Ԃ�(�Q�h�b�g)�������܂��B��16bit�J���[���[�h�ł͐F��������̂�0(��)�Œ�Bv2.77
			}
			else
			{
				for (j = 0; j < (int)_ddsdBack.dwWidth; j++)
					*pPixels++ = color; //4byte�Ԃ�(�P�h�b�g)�������܂��B
			}
			pPixels0 += pitch;
		}
		_pDDSBack->Unlock(NULL);
	}

	if (bDraw)
	{
		for (i = 0; i < 256; i++)
			tvW[i] = 256;
		zoom_ddTensou(tvW, 224, 1); //�v���C�}���T�[�t�F�X�֓]������B
	}
}
