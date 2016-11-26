/******************************************************************************
Ootake
�EPCE�p�b�h1�`5�ɃL�[�{�[�h�̃L�[���܂߂Ď��R�Ɋ��蓖�Ăł���悤�ɂ����B
�EWindows�p16�{�^���p�b�h�ƃn�b�g�X�C�b�`�i�A�i���O�Ή��p�b�h�ł悭�g���Ă�
  ��j�ɂ��Ή������B
�Ev0.54�B�W���C�p�b�h���͂̔��蕔�����Q�[���{�ԓ��l��DirectInput�ōs���悤�ɂ�
  ���B�i0.53�ȑO�̂Q�{�ȏ�W���C�p�b�h���Ȃ��ł����Ƃ��̕s��������j
�E�A�ː�p�{�^���̐ݒ��ǉ��B�Q�{�^���C�R�{�^���p�b�h���ɁA�{�^���T,�U�̊���
  ���ė̈���g�p����B�i�U�{�^���p�b�h���ɂ͐ݒ�ł��Ȃ��d�l�j
�E������p�{�^���̐ݒ��ǉ��B
�E�X�e�[�g�Z�[�u�p�{�^���̐ݒ��ǉ��B
�E�X�N���[���V���b�g�p�{�^���̐ݒ��ǉ��B

Copyright(C)2006-2016 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[PadConfig.c]

		Implements a pad configuration window.

	Copyright (C) 2005 Ki

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

#define DIRECTINPUT_VERSION	0x0800	//Kitao�ǉ��B���ɂ���邩������Ȃ����ADirectInput5���y���B7���Ƃ��x������B�X�y�[�X�n���A�[���킩��₷���B

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "PadConfig.h"
#include "resource.h"
#include "WinMain.h"
#include "Input.h"
#include "JoyPad.h" //Kitao�ǉ�


#define PADCONFIG_CAPTION	"Pad Configuration"


#define LINE_LEN			70 //Kitao�X�V
#define N_LINES				20

#define N_MAXJOYSTICK		5


//Kitao�X�V�B�n�b�g�X�C�b�`��16�{�^���p�b�h�ɂ��Ή��B
static const Sint32	button[INPUT_NUM_BUTTON] =
{
	INPUT_JOYSTICK_UP,       INPUT_JOYSTICK_RIGHT,    INPUT_JOYSTICK_DOWN,     INPUT_JOYSTICK_LEFT,
	INPUT_JOYSTICK_POVUP,    INPUT_JOYSTICK_POVRIGHT, INPUT_JOYSTICK_POVDOWN,  INPUT_JOYSTICK_POVLEFT,
	INPUT_JOYSTICK_BUTTON1,  INPUT_JOYSTICK_BUTTON2,  INPUT_JOYSTICK_BUTTON3,  INPUT_JOYSTICK_BUTTON4,
	INPUT_JOYSTICK_BUTTON5,  INPUT_JOYSTICK_BUTTON6,  INPUT_JOYSTICK_BUTTON7,  INPUT_JOYSTICK_BUTTON8,
	INPUT_JOYSTICK_BUTTON9,  INPUT_JOYSTICK_BUTTON10, INPUT_JOYSTICK_BUTTON11, INPUT_JOYSTICK_BUTTON12,
	INPUT_JOYSTICK_BUTTON13, INPUT_JOYSTICK_BUTTON14, INPUT_JOYSTICK_BUTTON15, INPUT_JOYSTICK_BUTTON16
};

typedef struct
{
	DIJOYSTATE2		joyState;
	Uint32			buttonState; //Kitao�X�V�B16�{�^���ɑΉ��B�n�b�g�X�C�b�`�Ԃ�����ꂽ�̂�Uint32�ɁB
} JOYSTICK;


//Kitao�ǉ��BDirectInput���g�p����B
static LPDIRECTINPUT			_pDI		= NULL;			// DirectInput �C���^�[�t�F�[�X�|�C���^
static LPDIRECTINPUTDEVICE		_pDIDKey	= NULL;			// DirectInput Keyboard device
//static LPDIRECTINPUTDEVICE2		_pDIDJoy[N_MAXJOYSTICK];	// DirectInput Joystick device
static LPDIRECTINPUTDEVICE8		_pDIDJoy[N_MAXJOYSTICK];	// DirectInput Joystick device

static Uint32		_FontWidth;
static Uint32		_FontHeight;
static const char*	_pCaption = PADCONFIG_CAPTION;
static HWND			_hPWnd;
static HINSTANCE	_hInstance = NULL;
static HWND			_hWnd;
static BOOL			_bWindowCreated; //Kitao�ǉ�

static char*		_pText[N_LINES];
static char			_Text[N_LINES][LINE_LEN];
static Uint32		_Line = 0;


static Sint32		_nJoySticks;
static JOYSTICK		_Joystick[N_MAXJOYSTICK];

static Sint32		_Mode; //Kitao�ǉ��B0�c�ʏ�̐ݒ�B1�c�A�ː�p�{�^���̐ݒ�B2�c���񂵗p�{�^���̐ݒ�B3�c�X�e�[�g�Z�[�u�p�{�^���̐ݒ�B4�c�X�e�[�g���[�h�p�{�^���̐ݒ�B
						   //			5�c�X�N���[���V���b�g�p�{�^���̐ݒ�B6�c�t�@���N�V�����p�{�^���̐ݒ�B7�c�t�@���N�V�����{�^�����̃X�e�[�g�Z�[�u�����[�h�p�{�^���̐ݒ�B
						   //			8�c�|�[�Y�p�{�^���̐ݒ�B9�c�X�v���C�g��BG�̔�\���E�\���ؑփ{�^���̐ݒ�B
static Sint32		_PadID; //Kitao�ǉ�
static PCEPAD*		_pPad; //Kitao�ǉ�
static Sint32		_SetOk = -1; //Kitao�ǉ��B�߂�l�B�ݒ芮���Ȃ�1�B�L�����Z���Ȃ�-1�B���ݒ蒆��0�B
static Sint32*		_pSetOk = 0; //Kitao�ǉ�
static char			_DIKeys[256]; //Kitao�ǉ��B�L�[�{�[�h�̏�ԗp


/* �t�H���g�̍������擾���� */
static Uint32
get_font_height(
	HWND			hWnd)
{
	HDC				hDC;
	HFONT			hFont;
	HFONT			hFontOld;
	TEXTMETRIC		tm;

	hDC      = GetDC(hWnd);
	hFont    = (HFONT)GetStockObject(OEM_FIXED_FONT);   /* �Œ�s�b�`�t�H���g */
	hFontOld = (HFONT)SelectObject(hDC, hFont);

	GetTextMetrics(hDC, &tm);

	SelectObject(hDC, hFontOld);
	DeleteObject(hFont);
	ReleaseDC(hWnd, hDC);

	return (Uint32)(tm.tmHeight);
}

/* �t�H���g�̉������擾���� */
static Uint32
get_font_width(
	HWND			hWnd)
{
	HDC				hDC;
	HFONT			hFont;
	HFONT			hFontOld;
	TEXTMETRIC		tm;

	hDC      = GetDC(hWnd);
	hFont    = (HFONT)GetStockObject(OEM_FIXED_FONT);   /* �Œ�s�b�`�t�H���g */
	hFontOld = (HFONT)SelectObject(hDC, hFont);

	GetTextMetrics(hDC, &tm);

	SelectObject(hDC, hFontOld);
	DeleteObject(hFont);
	ReleaseDC(hWnd, hDC);

	return (Uint32)tm.tmAveCharWidth;
}


//Kitao�X�V
static void
set_window_size(
	HWND			hWnd)
{
	RECT	rc;
	Uint32	wndW = _FontWidth  * LINE_LEN;
	Uint32	wndH = _FontHeight * N_LINES;
	int		y;

	SetRect(&rc, 0, 0, wndW, wndH);
	AdjustWindowRectEx(&rc, GetWindowLong(hWnd, GWL_STYLE),
						GetMenu(hWnd) != NULL, GetWindowLong(hWnd, GWL_EXSTYLE));
	wndW = rc.right - rc.left;
	wndH = rc.bottom - rc.top;
	GetWindowRect(_hPWnd, &rc);
	y = rc.top;
	if (y + (int)wndH > GetSystemMetrics(SM_CYSCREEN))
	{
		y = GetSystemMetrics(SM_CYSCREEN) - wndH ;
		if (y<0) y=0;
	}
	MoveWindow(hWnd, rc.left, y, wndW, wndH, TRUE);
}


static void
update_window(
	HWND			hWnd)
{
	HDC				hDC;
	HFONT			hFont;
	HFONT			hFontOld;
	PAINTSTRUCT		ps;
	Uint32			i;

	/* �`�揀�� */
	hDC      = BeginPaint(hWnd, &ps);
	hFont    = (HFONT)GetStockObject(OEM_FIXED_FONT);
	hFontOld = (HFONT)SelectObject(hDC, hFont);
	SetBkColor(hDC, RGB(0,0,0));
	SetTextColor(hDC, RGB(224, 224, 224));

	/* �����̔w�i��h��Ԃ� */
	SetBkMode(hDC, OPAQUE);

	for (i=0; i<_Line; i++)
	{
		TextOut(hDC, 0, i*_FontHeight, _pText[i], strlen(_pText[i]));
	}

	/* �I������ */
	EndPaint(hWnd, &ps);
	SelectObject(hDC, hFontOld);
	DeleteObject(hFont);
	ReleaseDC(hWnd, hDC);
}


static void
add_text(
	const char*		pText, ...)
{
	Uint32		i;
	va_list		ap;
	char*		p;

	va_start(ap, pText);
	vsprintf(_pText[_Line++], pText, ap);
	va_end(ap);

	// scroll a line
	if (_Line == N_LINES)
	{
		p = _pText[0];
		for (i = 1; i < N_LINES; ++i)
		{
			_pText[i-1] = _pText[i];
		}
		_pText[N_LINES-1] = p;
		*p = '\0';

		--_Line;
	}

	InvalidateRect(_hWnd, NULL, FALSE); //Kitao�X�V
	UpdateWindow(_hWnd);
}


/*-----------------------------------------------------------------------------
	[joypad_update_state]
		���͏󋵂��X�V���܂��B
-----------------------------------------------------------------------------*/
static void
joypad_update_state()
{
	int		i;
	HRESULT hResult;

	for (i = 0; i < _nJoySticks; i++)
	{
		// �|�[�����O���s�Ȃ�
		hResult = _pDIDJoy[i]->Poll();
		if (hResult != DI_OK) //���s�����Ƃ��̓A�N�Z�X������蒼���Ă�蒼��
		{
			_pDIDJoy[i]->Acquire();
			_pDIDJoy[i]->Poll();
		}

		// �W���C�X�e�B�b�N�̏�Ԃ�ǂ�
		_pDIDJoy[i]->GetDeviceState(sizeof(DIJOYSTATE2), &_Joystick[i].joyState);

		// �{�^���̏�Ԃ��X�V���� (�Ƃ肠���� 12 �̃{�^���ɑΉ�) Kitao�X�V�B16�̃{�^���ɑΉ�
		_Joystick[i].buttonState = 0;
		if (_Joystick[i].joyState.rgbButtons[0] & 0x80)		_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON1;
		if (_Joystick[i].joyState.rgbButtons[1] & 0x80)		_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON2;
		if (_Joystick[i].joyState.rgbButtons[2] & 0x80)		_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON3;
		if (_Joystick[i].joyState.rgbButtons[3] & 0x80)		_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON4;
		if (_Joystick[i].joyState.rgbButtons[4] & 0x80)		_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON5;
		if (_Joystick[i].joyState.rgbButtons[5] & 0x80)		_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON6;
		if (_Joystick[i].joyState.rgbButtons[6] & 0x80)		_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON7;
		if (_Joystick[i].joyState.rgbButtons[7] & 0x80)		_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON8;
		if (_Joystick[i].joyState.rgbButtons[8] & 0x80)		_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON9;
		if (_Joystick[i].joyState.rgbButtons[9] & 0x80)		_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON10;
		if (_Joystick[i].joyState.rgbButtons[10] & 0x80)	_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON11;
		if (_Joystick[i].joyState.rgbButtons[11] & 0x80)	_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON12;
		if (_Joystick[i].joyState.rgbButtons[12] & 0x80)	_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON13;
		if (_Joystick[i].joyState.rgbButtons[13] & 0x80)	_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON14;
		if (_Joystick[i].joyState.rgbButtons[14] & 0x80)	_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON15;
		if (_Joystick[i].joyState.rgbButtons[15] & 0x80)	_Joystick[i].buttonState |= INPUT_JOYSTICK_BUTTON16;
		if (_Joystick[i].joyState.lY < -250)	_Joystick[i].buttonState |= INPUT_JOYSTICK_UP;
		if (_Joystick[i].joyState.lX > +250)	_Joystick[i].buttonState |= INPUT_JOYSTICK_RIGHT;
		if (_Joystick[i].joyState.lY > +250)	_Joystick[i].buttonState |= INPUT_JOYSTICK_DOWN;
		if (_Joystick[i].joyState.lX < -250)	_Joystick[i].buttonState |= INPUT_JOYSTICK_LEFT;
		//Kitao�X�V�B�n�b�g�X�C�b�`�i�A�i���O�Ή��R���g���[���̏\���{�^���ł悭�g����j�ɂ��Ή��B
		if (_Joystick[i].joyState.rgdwPOV[0] == 0)				_Joystick[i].buttonState |= INPUT_JOYSTICK_POVUP;
		if (_Joystick[i].joyState.rgdwPOV[0] == 45*DI_DEGREES)
		{
			_Joystick[i].buttonState |= INPUT_JOYSTICK_POVUP;
			_Joystick[i].buttonState |= INPUT_JOYSTICK_POVRIGHT;
		}
		if (_Joystick[i].joyState.rgdwPOV[0] == 90*DI_DEGREES)	_Joystick[i].buttonState |= INPUT_JOYSTICK_POVRIGHT;
		if (_Joystick[i].joyState.rgdwPOV[0] == 135*DI_DEGREES)
		{
			_Joystick[i].buttonState |= INPUT_JOYSTICK_POVRIGHT;
			_Joystick[i].buttonState |= INPUT_JOYSTICK_POVDOWN;
		}
		if (_Joystick[i].joyState.rgdwPOV[0] == 180*DI_DEGREES)		_Joystick[i].buttonState |= INPUT_JOYSTICK_POVDOWN;
		if (_Joystick[i].joyState.rgdwPOV[0] == 225*DI_DEGREES)
		{
			_Joystick[i].buttonState |= INPUT_JOYSTICK_POVDOWN;
			_Joystick[i].buttonState |= INPUT_JOYSTICK_POVLEFT;
		}
		if (_Joystick[i].joyState.rgdwPOV[0] == 270*DI_DEGREES)	_Joystick[i].buttonState |= INPUT_JOYSTICK_POVLEFT;
		if (_Joystick[i].joyState.rgdwPOV[0] == 315*DI_DEGREES)
		{
			_Joystick[i].buttonState |= INPUT_JOYSTICK_POVLEFT;
			_Joystick[i].buttonState |= INPUT_JOYSTICK_POVUP;
		}
	}
}


//Kitao�ǉ��B�L�[�{�[�h�̏�Ԃ�ǂݎ���čX�V����B
static void
keyborad_update_state()
{
	HRESULT hResult;

	// �L�[�{�[�h�̏�Ԃ�ǂ�
	hResult =_pDIDKey->GetDeviceState(256, &_DIKeys);

	// �ǂݎ��Ɏ��s�������̏���
	if (hResult != DI_OK) //���s�����Ƃ��̓A�N�Z�X������蒼���Ă�蒼��
	{
		_pDIDKey->Acquire();
		_pDIDKey->GetDeviceState(256, &_DIKeys);
	}
}


static BOOL
pump_message()
{
	MSG			msg;

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (_hInstance == NULL)
		return FALSE;

	return TRUE;
}


static BOOL
get_button(
	Sint16*		pButton)
{
	Sint16		q,i; //Kitao�ǉ�
	Sint16		theJoystick = -1; //Kitao�ǉ�
	Sint16		theButton = -1;

	while (theButton < 0)
	{
		Sleep(1);

		if (!pump_message())
			return FALSE;

		//�W���C�X�e�B�b�N
		joypad_update_state(); //�W���C�X�e�B�b�N�̏�Ԃ�ǂ�
		for (q=0; q<=_nJoySticks-1; q++) //Kitao�ǉ��B�Ȃ���Ă���S�ẴW���C�X�e�B�b�N�̃{�^�����󂯕t����悤�ɂ����B
			for (i=0; i<=INPUT_NUM_BUTTON-1; i++)
				if (_Joystick[q].buttonState & button[i]) //�{�^����������Ă�����
				{
					//�����ꂽ�{�^�����������܂ő҂�
					while (_Joystick[q].buttonState & button[i])
					{
						Sleep(1);
						if (!pump_message())
							return FALSE;
						joypad_update_state();
					}
					
					theJoystick = q+1; //Kitao�ǉ��B�ǂ̃W���C�X�e�B�b�N�̃{�^����
					theButton = i;
					if (theButton <=7) //�\���L�[or�n�b�g�X�C�b�`
						*pButton = (200 + theJoystick*100) + theButton;
					else //�{�^��
						*pButton = (200 + theJoystick*100 +50) + (theButton -8);
					
					return TRUE;
				}

		//Kitao�ǉ��B�L�[�{�[�h
		keyborad_update_state(); //�L�[�{�[�h�̏�Ԃ�ǂ�
		for (i=0; i<=255; i++)
			if ((_DIKeys[i] & 0x80)&&(i != DIK_ESCAPE)&&(i != DIK_CAPITAL)&&(i != DIK_KANJI)&& //�����L�[��������Ă�����iEsc��CAPS������(���p/�S�p)�L�[�ȊO�j�Bv0.83�X�V(Ki����C�����肪�Ƃ��������܂�)
				(i != DIK_CAPITAL)&&(i != DIK_KANA)) //�uCapsLock�L�[�v�Ɓu���ȃL�[�v�������ɁB(�����Ă��܂��ƃL�[���󂯕t���Ȃ��Ȃ�)�Bv1.33�ǉ�
			{
				//�����ꂽ�{�^�����������܂ő҂�
				while (_DIKeys[i] & 0x80)
				{
					Sleep(1);
					if (!pump_message())
						return FALSE;
					keyborad_update_state();
				}
				
				if (i == DIK_F1) //F1�L�[�Ȃ�ݒ���N���A
					i = -1;
				*pButton = i;
				
				return TRUE;
			}
	}
	return FALSE;
}


//Kitao�X�V
static BOOL
configure(
	Sint32		mode, //Kitao�ǉ��B0�c�ʏ�̐ݒ�B1�c�A�ː�p�{�^���̐ݒ�B2�`�c����{�^���̐ݒ�
	Sint32		padID, //Kitao�X�V�BjoyID��padID(1�`5)�ցBPC�G���W���̃p�b�h�i���o�[�ŊǗ�����悤�ɂ����B
	PCEPAD*		pPad)
{
	Sint16		up        = -1;
	Sint16		right     = -1;
	Sint16		down      = -1;
	Sint16		left      = -1;
	Sint16		select    = -1;
	Sint16		run       = -1;
	Sint16		buttonI   = -1;
	Sint16		buttonII  = -1;
	Sint16		buttonIII = -1;
	Sint16		buttonIV  = -1;
	Sint16		buttonV   = -1;
	Sint16		buttonVI  = -1;

	add_text("\n");

	switch (mode)
	{
		case 0:
		case 1:	//�ʏ�̐ݒ�or�A�ː�p�{�^���̐ݒ�
			if (JOYPAD_GetConnectSixButton()) //Kitao�ǉ�
				add_text("Setting of Player#%ld for \"6 Button Pad\": (\"Esc\"=Abort \"F1\"=Clear)", padID);
			else if (JOYPAD_GetConnectThreeButton()) //Kitao�ǉ�
				add_text("Setting of Player#%ld for \"3 Button Pad\": (\"Esc\"=Abort \"F1\"=Clear)", padID);
			else
				add_text("Setting of Player#%ld for \"2 Button Pad\": (\"Esc\"=Abort \"F1\"=Clear)", padID);
			if (mode == 1)
			{	//�A�˃{�^���̐ݒ莞�B�{�^���T,�U�ɘA�ː�p�{�^����ݒ�B
				up		= pPad->buttonU;
				right	= pPad->buttonR;
				down	= pPad->buttonD;
				left	= pPad->buttonL;
				select	= pPad->buttonSel;
				run		= pPad->buttonRun;
				buttonI	= pPad->button1;
				buttonII= pPad->button2;
				buttonIII=pPad->button3;
				buttonIV= pPad->button4;
				add_text("Press a button for \"turbo button I\"..."); if (!get_button(&buttonV)) return FALSE;
				add_text("Press a button for \"turbo button II\"...");  if (!get_button(&buttonVI))  return FALSE;
			}
			else 
			{	//�ʏ펞
				add_text("Press a button for \"UP\"...");         if (!get_button(&up))        return FALSE;
				add_text("Press a button for \"RIGHT\"...");      if (!get_button(&right))     return FALSE;
				add_text("Press a button for \"DOWN\"...");       if (!get_button(&down))      return FALSE;
				add_text("Press a button for \"LEFT\"...");       if (!get_button(&left))      return FALSE;
				add_text("Press a button for \"SELECT\"...");     if (!get_button(&select))    return FALSE;
				add_text("Press a button for \"RUN\"...");        if (!get_button(&run))       return FALSE;
				add_text("Press a button for \"button I\"...");   if (!get_button(&buttonI))   return FALSE;
				add_text("Press a button for \"button II\"...");  if (!get_button(&buttonII))  return FALSE;
				if (JOYPAD_GetConnectSixButton()) //Kitao�ǉ�
				{
					add_text("Press a button for \"button III\"..."); if (!get_button(&buttonIII)) return FALSE;
					add_text("Press a button for \"button IV\"...");  if (!get_button(&buttonIV))  return FALSE;
					add_text("Press a button for \"button V\"...");   if (!get_button(&buttonV))   return FALSE;
					add_text("Press a button for \"button VI\"...");  if (!get_button(&buttonVI))  return FALSE;
				}
				else if (JOYPAD_GetConnectThreeButton()) //Kitao�ǉ�
				{
					add_text("Press a button for \"button IIIr[=RUN]\"..."); if (!get_button(&buttonIII)) return FALSE;
					add_text("Press a button for \"button IIIs[=SELECT]\"...");  if (!get_button(&buttonIV)) return FALSE;
				}
			}
			break;
		case 2: //���񂵗p�{�^���̐ݒ�
			add_text("Setting of \"Video Speed Up Button\": (\"Esc\"=Abort \"F1\"=Clear)");
			add_text("Press a button for \"Video Speed Up Button\"...");   if (!get_button(&buttonI)) return FALSE;
			break;
		case 3: //�X�e�[�g�Z�[�u�p�{�^���̐ݒ�
			add_text("Setting of \"Save State Button\": (\"Esc\"=Abort \"F1\"=Default[S])");
			add_text("Press a button for \"Save State Button\"...");   if (!get_button(&buttonI)) return FALSE;
			break;
		case 4: //�X�e�[�g���[�h�p�{�^���̐ݒ�
			add_text("Setting of \"Load State Button\": (\"Esc\"=Abort \"F1\"=Default[L])");
			add_text("Press a button for \"Load State Button\"...");   if (!get_button(&buttonI)) return FALSE;
			break;
		case 5: //�X�N���[���V���b�g�p�{�^���̐ݒ�
			add_text("Setting of \"Screenshot Button\": (\"Esc\"=Abort \"F1\"=Default[PrintScr])");
			add_text("Press a button for \"Screenshot Button\"...");   if (!get_button(&buttonI)) return FALSE;
			break;
		case 6: //�t�@���N�V�����p�{�^���̐ݒ�
			add_text("Setting of \"Function Button\": (\"Esc\"=Abort \"F1\"=Clear)");
			add_text("Press a button for \"Function Button\"...");   if (!get_button(&buttonI)) return FALSE;
			break;
		case 7: //�t�@���N�V�����{�^�����̃Z�[�u�����[�h�p�{�^���̐ݒ�
			add_text("Setting of \"Function SaveState Button\": (\"Esc\"=Abort \"F1\"=Clear)");
			add_text("Press a button for \"Function SaveState Button\"...");   if (!get_button(&buttonI)) return FALSE;
			add_text("Setting of \"Function LoadState Button\": (\"Esc\"=Abort \"F1\"=Clear)");
			add_text("Press a button for \"Function LoadState Button\"...");   if (!get_button(&buttonII)) return FALSE;
			break;
		case 8: //�|�[�Y�p�{�^���̐ݒ�
			add_text("Setting of \"Pause Button\": (\"Esc\"=Abort \"F1\"=Clear)");
			add_text("Press a button for \"Pause Button\"...");   if (!get_button(&buttonI)) return FALSE;
			break;
		case 9: //�X�v���C�g��BG�̔�\���E�\���ؑ֗p�{�^���̐ݒ�
			add_text("Setting of \"Sprite Button\": (\"Esc\"=Abort \"F1\"=Clear)");
			add_text("Press a button for \"Sprite Button\"...");   if (!get_button(&buttonI)) return FALSE;
			add_text("Setting of \"BG Button\": (\"Esc\"=Abort \"F1\"=Clear)");
			add_text("Press a button for \"BG Button\"...");   if (!get_button(&buttonII)) return FALSE;
			add_text("Setting of \"Sprite2(for SG) Button\": (\"Esc\"=Abort \"F1\"=Clear)");
			add_text("Press a button for \"Sprite2(for SG) Button\"...");   if (!get_button(&buttonIII)) return FALSE;
			add_text("Setting of \"BG2(for SG) Button\": (\"Esc\"=Abort \"F1\"=Clear)");
			add_text("Press a button for \"BG2(for SG) Button\"...");   if (!get_button(&buttonIV)) return FALSE;
			break;
	}

	//Kitao�X�V
	pPad->buttonU	= up;		//��L�[�̐ݒ�B�A�X�L�[�R�[�h(0�`255)�B�W���C�p�b�h�P(300�`399�B100�{�^���܂őΉ�)�B�W���C�p�b�h�Q(400�`499)�B�ȉ��W���C�p�b�h�T�{�܂œ��l�B
	pPad->buttonR	= right;	//�E�L�[�̐ݒ�
	pPad->buttonD	= down;		//���L�[�̐ݒ�
	pPad->buttonL	= left;		//���L�[�̐ݒ�
	pPad->buttonSel	= select;	//Select�{�^���̐ݒ�
	pPad->buttonRun	= run;		//Run�{�^���̐ݒ�
	pPad->button1	= buttonI;	//I�{�^���̐ݒ�
	pPad->button2	= buttonII;	//II�{�^���̐ݒ�
	pPad->button3	= buttonIII;//III�{�^���̐ݒ�
	pPad->button4	= buttonIV;	//IV�{�^���̐ݒ�
	pPad->button5	= buttonV;	//V�{�^���̐ݒ�
	pPad->button6	= buttonVI;	//VI�{�^���̐ݒ�

	return TRUE;
}


static LRESULT CALLBACK
padconfig_wnd_proc(
	HWND		hWnd,
	UINT		uMsg,
	WPARAM		wParam,
	LPARAM		lParam)
{
	int		i;

	switch(uMsg)
	{
	case WM_CREATE:
		EnableWindow(_hPWnd, FALSE);//Kitao�ǉ��B�e�E�C���h�E�𖳌������ă��[�_���ɁB
		_FontWidth  = get_font_width(hWnd);
		_FontHeight = get_font_height(hWnd);
		set_window_size(hWnd);
		break;

	case WM_PAINT:
		update_window(hWnd);
		_bWindowCreated = TRUE; //v0.74�ǉ�
		break;

	case WM_ACTIVATE: //Kitao�ǉ�
		if (wParam != 0) //�A�N�e�B�u�ɂȂ�Ƃ�
		{
			//DirectInput�̃A�N�Z�X�����𓾂�
			//�L�[�{�[�h
			if (_pDIDKey != NULL)
				_pDIDKey->Acquire();
			//�W���C�X�e�B�b�N
			for (i = 0; i < _nJoySticks; ++i)
				if (_pDIDJoy[i] != NULL)
					_pDIDJoy[i]->Acquire();
		}
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PADCONFIG_Deinit();
			return 0;
		}
		break;

	case WM_CLOSE:
		PADCONFIG_Deinit();
		return 0;
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//Kitao�ǉ��BJoyStick�f�o�C�X�̎����擾����R�[���o�b�N�֐�
static BOOL
CALLBACK
DIEnumAxisCallback(
	LPCDIDEVICEOBJECTINSTANCE	lpddi,
	LPVOID						pvRef)
{
	DIPROPRANGE				diDR;
	DIPROPDWORD				diDD;

	//�����������̐ݒ������B
	ZeroMemory(&diDR, sizeof(diDR));
	diDR.diph.dwSize       = sizeof(diDR);
	diDR.diph.dwHeaderSize = sizeof(diDR.diph);
	diDR.diph.dwHow        = DIPH_BYID;
	diDR.diph.dwObj        = lpddi->dwType;
	diDR.lMin = -1000;
	diDR.lMax = +1000;
	_pDIDJoy[_nJoySticks]->SetProperty(DIPROP_RANGE, &diDR.diph);

	//��Ύ��ɐݒ�B
	ZeroMemory(&diDD, sizeof(diDD));
	diDD.diph.dwSize       = sizeof(diDD);
	diDD.diph.dwHeaderSize = sizeof(diDD.diph);
	diDD.diph.dwHow        = DIPH_DEVICE;
	diDD.dwData		       = DIPROPAXISMODE_ABS;
	_pDIDJoy[_nJoySticks]->SetProperty(DIPROP_AXISMODE, &diDD.diph);

	//�f�b�h�]�[����0�ɐݒ�B�f�W�^���p�b�h�ł��L���BDirectX7�ȍ~�ł�����ł����Ԕ������ǂ��Ȃ�BKitao�ǉ�
	ZeroMemory(&diDD, sizeof(diDD));
	diDD.diph.dwSize       = sizeof(diDD);
	diDD.diph.dwHeaderSize = sizeof(diDD.diph);
	diDD.diph.dwHow        = DIPH_DEVICE;
	diDD.dwData		       = 0;
	_pDIDJoy[_nJoySticks]->SetProperty(DIPROP_DEADZONE, &diDD.diph);

	//�O�a�]�[�����ő�ɁBKitao�ǉ�
	ZeroMemory(&diDD, sizeof(diDD));
	diDD.diph.dwSize       = sizeof(diDD);
	diDD.diph.dwHeaderSize = sizeof(diDD.diph);
	diDD.diph.dwHow        = DIPH_DEVICE;
	diDD.dwData		       = 10000;
	_pDIDJoy[_nJoySticks]->SetProperty(DIPROP_SATURATION, &diDD.diph);

	return DIENUM_CONTINUE; //���̎���T��
}

static BOOL
CALLBACK
DIEnumDevicesCallback(
	LPCDIDEVICEINSTANCE	lpddi,
	LPVOID				pvRef)
{
	HRESULT					hResult;
	LPDIRECTINPUTDEVICE		pDIDJoy; //Kitao�ǉ�
	DIPROPDWORD				diDD;

	//���������W���C�X�e�B�b�N�f�o�C�X���쐬����
	hResult = _pDI->CreateDevice(lpddi->guidInstance, &pDIDJoy, NULL);
	if(hResult != DI_OK)
		return DIENUM_CONTINUE; //���s�����璆�~���Ď���T��
	
	//Kitao�ǉ��B������DirectInputDevice2�Ɋg�����Ă����悤�ɂ����i�������j�B
	pDIDJoy->QueryInterface(IID_IDirectInputDevice8, (LPVOID*)&_pDIDJoy[_nJoySticks]);
	pDIDJoy->Release();
	
	//�f�[�^�t�H�[�}�b�g��ݒ肷��
	_pDIDJoy[_nJoySticks]->SetDataFormat(&c_dfDIJoystick2);

	//�o�b�t�@���ŏ��ɁB�������ǂ��Ȃ�BKitao�ǉ�
	ZeroMemory(&diDD, sizeof(diDD));
	diDD.diph.dwSize       = sizeof(diDD);
	diDD.diph.dwHeaderSize = sizeof(diDD.diph);
	diDD.diph.dwHow        = DIPH_DEVICE;
	diDD.dwData		       = 1;
	_pDIDJoy[_nJoySticks]->SetProperty(DIPROP_BUFFERSIZE, &diDD.diph);

	//�������x�����w�肷��  Kitao�X�V�B�����ݒ��DISCL_NONEXCLUSIVE�Ɂ��o�b�N�O���E���h�ł�����\�ɂ����B
	_pDIDJoy[_nJoySticks]->SetCooperativeLevel(_hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	//JoyStick�f�o�C�X�̎���񋓂���BKitao�ǉ�
	_pDIDJoy[_nJoySticks]->EnumObjects(DIEnumAxisCallback, NULL, DIDFT_AXIS);

	_nJoySticks++;

	//�R���g���[����5���o���ꂽ��I������
	if(_nJoySticks==N_MAXJOYSTICK)
		return DIENUM_STOP; //�񋓂��I��������
	else
		return DIENUM_CONTINUE; //���̃f�o�C�X��T��
}

//Kitao�X�V�B�L�[�{�[�h�ɂ��Ή��B�W���C�X�e�B�b�N���D���ȃW���C�X�e�B�b�N���D���Ȕԍ��Ŏg����悤�ɂ����B
static BOOL
padconfig_main()
{
	WNDCLASS	wc;
	HWND		hWnd;
	BOOL		bOk;
	HRESULT 	hResult;
	int			i;
	RECT		rc;

	ZeroMemory(&wc, sizeof(wc));
	wc.style		 = 0;
	wc.lpfnWndProc	 = padconfig_wnd_proc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = _hInstance;
	wc.hIcon		 = LoadIcon(_hInstance, MAKEINTRESOURCE(OOTAKEICON)); //�A�C�R����ǂݍ��݁Bv2.00�X�V
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName	 = "";
	wc.lpszClassName = _pCaption;

	if (RegisterClass(&wc) == 0)
		return FALSE;

	_bWindowCreated = FALSE; //Kitao�ǉ�

	hWnd = CreateWindow(
		_pCaption,
		_pCaption,
		WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		_hPWnd, //v2.77
		NULL,
		_hInstance,
		NULL
	);

	if (hWnd == NULL)
		return FALSE;

	_hWnd	   = hWnd;

	CloseWindow(_hPWnd);//�e�E�B���h�E���ŏ���
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
	GetWindowRect(hWnd, &rc);
	SetWindowPos(hWnd, HWND_TOP, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_FRAMECHANGED); //���̃E�B���h�E���u��Ɏ�O�ɕ\���v
	while (_bWindowCreated == FALSE) //�E�B���h�E�̐��������܂ő҂Bv0.74
		Sleep(1);
	ImmAssociateContext(hWnd, 0); //Kitao�ǉ��BIME�𖳌��ɂ���Bv0.79

	//�ȉ�Kitao�ǉ��B
	//Windows�W���C�X�e�B�b�N�p�̕ϐ���������
	_nJoySticks = 0;
	ZeroMemory(_Joystick, sizeof(_Joystick));
	// DirectInput�C���^�[�t�F�[�X���擾����
	if (DirectInput8Create(WINMAIN_GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8A, ((LPVOID*)&_pDI), NULL) != DI_OK)
		return FALSE;

	//�L�[�{�[�h�f�o�C�X���擾����
	if (_pDI->CreateDevice(GUID_SysKeyboard, &_pDIDKey, NULL) != DI_OK)
		return FALSE;
	//�f�[�^�t�H�[�}�b�g��ݒ肷��
	if (_pDIDKey->SetDataFormat(&c_dfDIKeyboard) != DI_OK)
		return FALSE;
	//�������x�����w�肷��
	hResult=_pDIDKey->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	//�L�[�{�[�h�̃A�N�Z�X���𓾂Ă����B
	_pDIDKey->Acquire();
	//JoyStick�f�o�C�X��񋓂���
	
	_pDI->EnumDevices(DI8DEVTYPE_JOYSTICK, DIEnumDevicesCallback, NULL, DIEDFL_ATTACHEDONLY);
	if (_nJoySticks == 0)
		add_text("PADCONFIG: No supported joystick found.");
	else
		add_text("PADCONFIG: %ld joystick(s) found.", _nJoySticks);
	//�ŏ��ɃA�N�Z�X���𓾂Ă����B
	for (i = 0; i < _nJoySticks; i++)
		_pDIDJoy[i]->Acquire();

	//���͐ݒ�
	bOk = configure(_Mode, _PadID, _pPad);
	if (bOk)
		_SetOk = 1; //�ݒ芮���̈�

	PostMessage(hWnd, WM_CLOSE, 0, 0);
	return bOk;
}


//Kitao�X�V�B�����l�v���C�̂Ƃ����L�[�{�[�h�̃{�^�����g����悤�ɂ����B
BOOL
PADCONFIG_Init(
	HWND		hWnd,
	HINSTANCE	hInstance,
	Sint32	 	mode, //Kitao�ǉ��B0�c�ʏ�̐ݒ�B1�c�A�ː�p�{�^���̐ݒ�B2�c���񂵗p�{�^���̐ݒ�B3�c�X�e�[�g�Z�[�u�p�{�^���̐ݒ�B4�c�X�e�[�g���[�h�p�{�^���̐ݒ�B5�c�X�N���[���V���b�g�p�{�^���̐ݒ�B
					  //		   6�c�t�@���N�V�����p�{�^���̐ݒ�B7�c�t�@���N�V�����{�^�����̃X�e�[�g�Z�[�u�����[�h�p�{�^���̐ݒ�B8�c�|�[�Y�p�{�^���̐ݒ�B9�c�X�v���C�g��BG�̔�\���E�\���ؑփ{�^���̐ݒ�B
	Sint32	 	padID,
	PCEPAD* 	pPad,
	Sint32*		setOk)
{
	int				i;

	_hPWnd = hWnd; //�e�E�B���h�E�̃n���h���Bv2.77
	_hInstance = hInstance;
	_Line      = 0;

	_Mode	= mode;
	_PadID	= padID;
	_pPad	= pPad;
	_pSetOk	= setOk;
	_SetOk	= -1; //�L�����Z��

	for (i=0; i<N_LINES; i++)
		_pText[i] = _Text[i];

	return padconfig_main();
}


void
PADCONFIG_Deinit()
{
	int	i;

	if (_hInstance != NULL)
	{
		if (_pDIDKey != NULL)
		{
			_pDIDKey->Unacquire();
			_pDIDKey->Release();
			_pDIDKey = NULL;
		}
		for (i = 0; i < N_MAXJOYSTICK; ++i)
		{
			if (_pDIDJoy[i] != NULL)
			{
				_pDIDJoy[i]->Unacquire();
				_pDIDJoy[i]->Release();
				_pDIDJoy[i] = NULL;
			}
		}
		if (_pDI != NULL)
		{
			_pDI->Release();
			_pDI = NULL;
		}
		DestroyWindow(_hWnd);
		_hWnd = NULL;
		UnregisterClass(_pCaption, _hInstance);
		_hInstance = NULL;
		
		//���C���E�B���h�E�Ƀt�H�[�J�X��߂����̑傫���ɁB
		EnableWindow(_hPWnd, TRUE);
		OpenIcon(_hPWnd);
		
		*_pSetOk = _SetOk; //�߂�l��ݒ�B���̏u�ԂɃ��C���E�B���h�E�͓����o���B
	}
}

