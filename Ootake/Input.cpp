/******************************************************************************
Ootake
�EPCE�p�b�h1�`5�ɃL�[�{�[�h�̃L�[���܂߂Ď��R�Ɋ��蓖�Ăł���悤�ɂ����B
�EWindows�p16�{�^���p�b�h�ƃn�b�g�X�C�b�`�i�A�i���O�Ή��p�b�h�ł悭�g���Ă�
  ��j�ɂ��Ή������B
�E�������̂��߂�DirectInput�̃A�N�Z�X���̎擾�̓A�N�e�B�u�ɂȂ����Ƃ��P�񂾂��s
  ���悤�ɂ����B���l�ɃA�N�Z�X���̈��n�����f�B�A�N�e�u���ɂP�񂾂��s���悤�ɂ�
  ���B
�E�v���C���R�[�h���ɁAWindows�p�b�h�̏�Ԃł͂Ȃ��A�uPCE�p�b�h�̏�ԁv�Ƃ��ċL
  �^����悤�ɂ����B����͗e�ʂƑΉ��\�t�g�����l���A�Q�{�^���R���g���[���P��
  �݋L�^�B����A�ݒ�łU�{�^����}���`�^�b�v�ł̋L�^�ɂ��Ή��������B
�E�U�{�^�����A�ː�p�{�^���ƂQ�v���C���[�p�b�h�̃v���C���R�[�h�ɂ��Ή������B
  v2.15

Copyright(C)2006-2009 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[Input.c]
		���͂̎������s�Ȃ��܂��B

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
#define DIRECTINPUT_VERSION	0x0800	//Kitao�ǉ��B���ɂ���邩������Ȃ����ADirectInput5���y���B7,8���Ƃ��x������B�X�y�[�X�n���A�[���킩��₷���B

#include <windows.h>
#include <string.h>
#include "Input.h"
#include "WinMain.h"
#include "Printf.h"
#include "JoyPad.h"
#include "MainBoard.h"
#include "App.h"


#define INPUT_BUFFERSIZE		8+60*60*120*10*7			// 8heder + 60frame * 60sec * 120min * 10�� * 7byte(5player)  //Kitao�X�V�B1frame�̃L�[�X�e�[�^�X�X�V�񐔂�s��ɂ������߁A�o�b�t�@�����₵���B�P�t���[����10��Ă΂��Ƃ��ĂT�l�v���C���łQ���ԎB���傫��(��30MB)�ɂ����B�w�b�_���t����悤�ɂ����B
#define N_MAXJOYSTICK			5


static LPDIRECTINPUT			_pDI		= NULL;			// DirectInput �C���^�[�t�F�[�X�|�C���^
static LPDIRECTINPUTDEVICE		_pDIDKey	= NULL;			// DirectInput Keyboard device
static LPDIRECTINPUTDEVICE2		_pDIDJoy[N_MAXJOYSTICK];	// DirectInput Joystick device  Kitao�X�V�BLPDIRECTINPUTDEVICE2�ɂ����B


typedef struct
{
	DIJOYSTATE2					joyState;
	Uint32						buttonState; //Kitao�X�V�B16�{�^���ɑΉ��B�n�b�g�X�C�b�`�Ԃ�����ꂽ�̂�Uint32�ɁB
} JOYSTICK; //Kitao�X�V


static char						_DIKeys[256];					// �L�[�{�[�h�̃X�e�[�^�X��������z��

static Sint32					_nJoySticks = 0;

static Uint8					_InputBuffer[INPUT_BUFFERSIZE];	// record pad #1&#2 //Kitao�X�V�BPCE�p�b�h�̏�ԂƂ��ċL�^����悤�ɂ����B
static Sint32					_InputBufferIndex;
static Sint32					_InputBufferIndexEnd = INPUT_BUFFERSIZE;
static Sint32					_InputPlayRecordPad; //Kitao�ǉ��B�ǂݍ��ݒ��v���C���R�[�h�t�@�C���̋L�^�p�b�h���Bv2.15

static BOOL						_bRecord;
static BOOL						_bPlayRecord;
static BOOL						_bInit;

//Kitao�ǉ��Bv1.21
static BOOL						_bGameSetting;
static BOOL						_bKonamiStereo;
static BOOL						_bGradiusII;

static JOYSTICK					_Joystick[N_MAXJOYSTICK];

//Kitao�ǉ�
static PCEPAD	_PcePad[6]; //���݂̊ePCE�p�b�h[1]�`[5]�̃{�^���ݒ�([0]�͔�g�p)


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
	diDR.lMin = -100;
	diDR.lMax = +100;
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

/*-----------------------------------------------------------------------------
	[DIEnumDevicesCallback]
	JoyStick�f�o�C�X���擾����R�[���o�b�N�֐�
-----------------------------------------------------------------------------*/
static BOOL
CALLBACK
DIEnumDevicesCallback(
	LPCDIDEVICEINSTANCE	lpddi,
	LPVOID				pvRef)
{
	HWND					hWnd;
	HRESULT					hResult;
	LPDIRECTINPUTDEVICE		pDIDJoy; //Kitao�ǉ�
	DIPROPDWORD				diDD;

	hWnd = WINMAIN_GetHwnd();

	//���������W���C�X�e�B�b�N�f�o�C�X���쐬����
	hResult = _pDI->CreateDevice(lpddi->guidInstance, &pDIDJoy, NULL);
	if (hResult != DI_OK)
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
	if (APP_GetJoypadBackground())
		_pDIDJoy[_nJoySticks]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	else
		_pDIDJoy[_nJoySticks]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	//JoyStick�f�o�C�X�̎���񋓂���BKitao�ǉ�
	_pDIDJoy[_nJoySticks]->EnumObjects(DIEnumAxisCallback, NULL, DIDFT_AXIS);

	_nJoySticks++;

	//�R���g���[����5���o���ꂽ��I������
	if(_nJoySticks==N_MAXJOYSTICK)
		return DIENUM_STOP; //�񋓂��I��������
	else
		return DIENUM_CONTINUE; //���̃f�o�C�X��T��
}


/*-----------------------------------------------------------------------------
	[Init]
		���������܂��B
-----------------------------------------------------------------------------*/
BOOL
INPUT_Init()
{
	HRESULT		hResult;
	HANDLE		hWnd;
	int			i;

	if (_bInit)
		INPUT_Deinit();

	memset(_PcePad, 0xFF, sizeof(_PcePad)); //0xFFFF(-1)�ŏ�����
	ZeroMemory(_Joystick, sizeof(_Joystick));
	_InputBufferIndex = 0;

	hWnd = WINMAIN_GetHwnd();

	// DirectInput�C���^�[�t�F�[�X���擾����
	if (DirectInput8Create(WINMAIN_GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8A, (LPVOID*)&_pDI, NULL) != DI_OK)
		return FALSE;

	//�L�[�{�[�h�f�o�C�X���擾����
	if (_pDI->CreateDevice(GUID_SysKeyboard, &_pDIDKey, NULL) != DI_OK)
		return FALSE;

	//�f�[�^�t�H�[�}�b�g��ݒ肷��
	if (_pDIDKey->SetDataFormat(&c_dfDIKeyboard) != DI_OK)
		return FALSE;

	//�������x�����w�肷��  Kitao�X�V�B�����ݒ��DISCL_NONEXCLUSIVE�Ɂ��o�b�N�O���E���h�ł�����\�ɂ����B
	if (APP_GetKeyboardBackground())
		hResult = _pDIDKey->SetCooperativeLevel((HWND)hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	else
		hResult = _pDIDKey->SetCooperativeLevel((HWND)hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	//�L�[�{�[�h�̃A�N�Z�X���𓾂Ă����B
	_pDIDKey->Acquire();

	//JoyStick�f�o�C�X��񋓂���
	_pDI->EnumDevices(DI8DEVTYPE_JOYSTICK, DIEnumDevicesCallback, NULL, DIEDFL_ATTACHEDONLY);

	//Kitao�ǉ��B�ŏ��ɃA�N�Z�X���𓾂Ă����B
	for (i = 0; i < _nJoySticks; i++)
		_pDIDJoy[i]->Acquire();

	_bInit = TRUE;

	return _bInit;
}


/*-----------------------------------------------------------------------------
	[Deinit]
		�I�����܂��B
-----------------------------------------------------------------------------*/
void
INPUT_Deinit()
{
	Uint32		i;

	if (!_bInit)
		return;

	if (_pDIDKey != NULL)
	{
		_pDIDKey->Unacquire(); //Kitao�ǋL�BUnacquire��Release�O�ɂP�񂾂��s���悤�ɂ���BUnacquire���J��Ԃ��ƁA���ɂ���Ă͕s����ɂȂ�炵���B
		_pDIDKey->Release();
		_pDIDKey = NULL;
	}

	for (i = 0; i < N_MAXJOYSTICK; ++i)
	{
		if (_pDIDJoy[i] != NULL)
		{
			_pDIDJoy[i]->Unacquire(); //Kitao�ǋL�BUnacquire��Release�O�ɂP�񂾂��s���悤�ɂ���BUnacquire���J��Ԃ��ƁA���ɂ���Ă͕s����ɂȂ�炵���B
			_pDIDJoy[i]->Release();
			_pDIDJoy[i] = NULL;
		}
	}

	if (_pDI != NULL)
	{
		_pDI->Release();
		_pDI = NULL;
	}

	_nJoySticks = 0;
	_bInit = FALSE;
}


/*-----------------------------------------------------------------------------
	[ConnectButton]
		���[�U�[��`�̃{�^���Ɠ��̓{�^����ڑ����܂��B
-----------------------------------------------------------------------------*/
//Kitao�X�V�BApp.c�œǂݍ���_PcePad2[]�܂���_PcePad6[]�̓��e���A�������_PcePad[]�ɂ����f������֐��Ƃ����B
void
INPUT_ConnectButton(
	Sint32		padID,	//padID�cPCE�p�b�h�i���o�[(1�`5)
	PCEPAD*		pcepad) //pcepad�c_PcePad2[]��_PcePad6[]�̃A�h���X
{
	_PcePad[padID] = *pcepad;
	return;
}


//Kitao�ǉ��B�{�^���̃X�e�[�^�X�i������Ă������ǂ����j���`�F�b�N����T�u�B
//a�c�L�[�i���o�[or�W���C�p�b�h�̃{�^���i���o�[�B�߂�l�́A���̃L�[,�{�^����������Ă����ꍇ��TRUE�B
BOOL
INPUT_CheckButtonState(
	Sint32	a)
{
	Sint32	winJoyID;

	if (a == -1) //���ݒ�̏ꍇ
		return FALSE;
	
	if (a <= 255) //�L�[�{�[�h�̃L�[���ݒ肳��Ă����ꍇ
		return (_DIKeys[a] & 0x80);
	else //�W���C�p�b�h�̃L�[�E�{�^�����ݒ肳��Ă����ꍇ
	{
		a -= 300;
		winJoyID = 0;
		while (a >= 100)
		{
			winJoyID++;
			a -= 100;
		}
		if (a < 50) //�\���L�[�E�n�b�g�X�C�b�`�ނȂ�
		{
			switch (a)
			{
				case 0: //0�`3 �\���L�[
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_UP) != 0;
				case 1:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_RIGHT) != 0;
				case 2:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_DOWN) != 0;
				case 3:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_LEFT) != 0;
				case 4: //4�`7 �n�b�g�X�C�b�`
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_POVUP) != 0;
				case 5:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_POVRIGHT) != 0;
				case 6:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_POVDOWN) != 0;
				case 7:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_POVLEFT) != 0;
			}
		}
		else //�{�^���ނȂ�
		{
			switch (a - 50)
			{
				case 0:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON1) != 0;
				case 1:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON2) != 0;
				case 2:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON3) != 0;
				case 3:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON4) != 0;
				case 4:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON5) != 0;
				case 5:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON6) != 0;
				case 6:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON7) != 0;
				case 7:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON8) != 0;
				case 8:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON9) != 0;
				case 9:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON10) != 0;
				case 10:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON11) != 0;
				case 11:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON12) != 0;
				case 12:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON13) != 0;
				case 13:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON14) != 0;
				case 14:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON15) != 0;
				case 15:
					return (_Joystick[winJoyID].buttonState & INPUT_JOYSTICK_BUTTON16) != 0;
			}
		}
	}
	return FALSE;
}

//Kitao�ǉ��B�w��̃{�^���̃X�e�[�^�X�i������Ă������ǂ����j���I���ɂ���B�v���C�o�b�N���Ɏg�p
//a�c�L�[�i���o�[or�W���C�p�b�h�̃{�^���i���o�[
static void
set_button_state(
	int	a)
{
	Sint32	winJoyID;

	if (a == -1) //���ݒ�̏ꍇ
		return;
	
	if (a <= 255) //�L�[�{�[�h�̃L�[���ݒ肳��Ă����ꍇ
	{
		_DIKeys[a] |= 0x80;
		return;
	}
	else //�W���C�p�b�h�̃L�[�E�{�^�����ݒ肳��Ă����ꍇ
	{
		a -= 300;
		winJoyID = 0;
		while (a >= 100)
		{
			winJoyID++;
			a -= 100;
		}
		if (a < 50) //�\���L�[�E�n�b�g�X�C�b�`�ނȂ�
		{
			switch (a)
			{
				case 0: //0�`3 �\���L�[
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_UP;
					return;
				case 1:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_RIGHT;
					return;
				case 2:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_DOWN;
					return;
				case 3:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_LEFT;
					return;
				case 4: //4�`7 �n�b�g�X�C�b�`
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_POVUP;
					return;
				case 5:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_POVRIGHT;
					return;
				case 6:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_POVDOWN;
					return;
				case 7:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_POVLEFT;
					return;
			}
		}
		else //�{�^���ނȂ�
		{
			switch (a - 50)
			{
				case 0:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON1;
					return;
				case 1:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON2;
					return;
				case 2:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON3;
					return;
				case 3:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON4;
					return;
				case 4:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON5;
					return;
				case 5:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON6;
					return;
				case 6:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON7;
					return;
				case 7:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON8;
					return;
				case 8:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON9;
					return;
				case 9:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON10;
					return;
				case 10:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON11;
					return;
				case 11:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON12;
					return;
				case 12:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON13;
					return;
				case 13:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON14;
					return;
				case 14:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON15;
					return;
				case 15:
					_Joystick[winJoyID].buttonState |= INPUT_JOYSTICK_BUTTON16;
					return;
			}
		}
	}
}

//Kitao�ǉ��B�w��̃{�^���̃X�e�[�^�X�i������Ă������ǂ����j���I�t�ɂ���B�R�i�~�̃I�[�g�X�e���I���Ɏg�p
//a�c�L�[�i���o�[or�W���C�p�b�h�̃{�^���i���o�[
static void
reset_button_state(
	int	a)
{
	Sint32	winJoyID;

	if (a == -1) //���ݒ�̏ꍇ
		return;
	
	if (a <= 255) //�L�[�{�[�h�̃L�[���ݒ肳��Ă����ꍇ
	{
		_DIKeys[a] &= ~0x80;
		return;
	}
	else //�W���C�p�b�h�̃L�[�E�{�^�����ݒ肳��Ă����ꍇ
	{
		a -= 300;
		winJoyID = 0;
		while (a >= 100)
		{
			winJoyID++;
			a -= 100;
		}
		if (a < 50) //�\���L�[�E�n�b�g�X�C�b�`�ނȂ�
		{
			switch (a)
			{
				case 0: //0�`3 �\���L�[
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_UP;
					return;
				case 1:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_RIGHT;
					return;
				case 2:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_DOWN;
					return;
				case 3:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_LEFT;
					return;
				case 4: //4�`7 �n�b�g�X�C�b�`
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_POVUP;
					return;
				case 5:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_POVRIGHT;
					return;
				case 6:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_POVDOWN;
					return;
				case 7:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_POVLEFT;
					return;
			}
		}
		else //�{�^���ނȂ�
		{
			switch (a - 50)
			{
				case 0:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON1;
					return;
				case 1:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON2;
					return;
				case 2:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON3;
					return;
				case 3:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON4;
					return;
				case 4:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON5;
					return;
				case 5:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON6;
					return;
				case 6:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON7;
					return;
				case 7:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON8;
					return;
				case 8:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON9;
					return;
				case 9:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON10;
					return;
				case 10:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON11;
					return;
				case 11:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON12;
					return;
				case 12:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON13;
					return;
				case 13:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON14;
					return;
				case 14:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON15;
					return;
				case 15:
					_Joystick[winJoyID].buttonState &= ~INPUT_JOYSTICK_BUTTON16;
					return;
			}
		}
	}
}

/*-----------------------------------------------------------------------------
	[UpdateState]
		���͏󋵂��X�V���܂��B
-----------------------------------------------------------------------------*/
void
INPUT_UpdateState(
	BOOL	bRecord) //Kitao�ǉ��B�L�^�E�Đ����s���Ȃ�TRUE�B
{
	int			i;
	Uint8		rc; //v2.15�X�V
	HRESULT		hResult;

	//Kitao�X�V�BWindows�p�b�h�ł͂Ȃ��APCE�p�b�h�̏�ԂƂ��ċL�^����悤�ɂ����B����͗e�ʂƑΉ��\�t�g�����l���A�Q�{�^���R���g���[���P�̂݁B����A�ݒ�łU�{�^����}���`�^�b�v�ɂ��Ή��������B
	//           INPUT_UpdateState()��JOYPAD_Read���Ă΂�邽�тɂ��悤�ɂ������߁A�L�^�e�ʂ͕s��B1�L�^��8�r�b�g�ɂ����̂ł��̂Ԃ�͔����B
	if ((bRecord)&&(_bPlayRecord))
	{
		memset(_DIKeys, 0, sizeof(_DIKeys)); //�L�[�{�[�h�̃X�e�[�^�X���N���A
		for (i = 0; i < _nJoySticks; ++i)
			_Joystick[i].buttonState = 0; //�W���C�X�e�B�b�N�̃X�e�[�^�X���N���A
		
		rc = _InputBuffer[_InputBufferIndex++];
		if (rc & 0x01)
			set_button_state(_PcePad[1].buttonU);
		if (rc & 0x02)
			set_button_state(_PcePad[1].buttonR);
		if (rc & 0x04)
			set_button_state(_PcePad[1].buttonD);
		if (rc & 0x08)
			set_button_state(_PcePad[1].buttonL);
		if (rc & 0x10)
			set_button_state(_PcePad[1].buttonSel);
		if (rc & 0x20)
			set_button_state(_PcePad[1].buttonRun);
		if (rc & 0x40)
			set_button_state(_PcePad[1].button1);
		if (rc & 0x80)
			set_button_state(_PcePad[1].button2);

		if (_InputPlayRecordPad == 2)
		{
			rc = _InputBuffer[_InputBufferIndex++];
			if (rc & 0x01)
				set_button_state(_PcePad[2].buttonU);
			if (rc & 0x02)
				set_button_state(_PcePad[2].buttonR);
			if (rc & 0x04)
				set_button_state(_PcePad[2].buttonD);
			if (rc & 0x08)
				set_button_state(_PcePad[2].buttonL);
			if (rc & 0x10)
				set_button_state(_PcePad[2].buttonSel);
			if (rc & 0x20)
				set_button_state(_PcePad[2].buttonRun);
			if (rc & 0x40)
				set_button_state(_PcePad[2].button1);
			if (rc & 0x80)
				set_button_state(_PcePad[2].button2);
			//�U�{�^��or�A�ː�p�{�^��(�{�^��5,6���g�p)�̏�Ԃ�ǂݏo��
			rc = _InputBuffer[_InputBufferIndex++];
			if (rc & 0x01)
				set_button_state(_PcePad[1].button3);
			if (rc & 0x02)
				set_button_state(_PcePad[1].button4);
			if (rc & 0x04)
				set_button_state(_PcePad[1].button5);
			if (rc & 0x08)
				set_button_state(_PcePad[1].button6);
			if (rc & 0x10)
				set_button_state(_PcePad[2].button3);
			if (rc & 0x20)
				set_button_state(_PcePad[2].button4);
			if (rc & 0x40)
				set_button_state(_PcePad[2].button5);
			if (rc & 0x80)
				set_button_state(_PcePad[2].button6);
		}
		
		if (_InputBufferIndex == _InputBufferIndexEnd)
		{
			i = APP_GetInputPlayRecordNumber();
			APP_EndPlayRecord();
			if (i == 0)
				PRINTF("End of Record Data.");
			else
				PRINTF("End of Record Data #%d.", i);
			MAINBOARD_ScreenUpdate(TRUE,TRUE); //�����Ƀ��b�Z�[�W�\�����X�V
			APP_RunEmulator(FALSE);
		}
	}
	else
	{
		// �L�[�{�[�h�̏�Ԃ�ǂ�
		hResult =_pDIDKey->GetDeviceState(256, _DIKeys);

		// �ǂݎ��Ɏ��s�������̏���
		if (hResult != DI_OK) //���s�����Ƃ��̓A�N�Z�X������蒼���Ă�蒼��
		{
			_pDIDKey->Acquire();
			_pDIDKey->GetDeviceState(256, _DIKeys);
		}

		// �W���C�X�e�B�b�N�����݂��鎞�̓W���C�X�e�B�b�N�̏�Ԃ��ǂ�
		for (i=0; i<_nJoySticks; i++)
		{
			// �|�[�����O���s�Ȃ��BKitao�X�V�BDirectInputDevice2�ւ̊g���͏��������ɂP�x�����s���悤�ɂ���(������)�B
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
			if (_Joystick[i].joyState.lY < -25)	_Joystick[i].buttonState |= INPUT_JOYSTICK_UP;
			if (_Joystick[i].joyState.lX > +25)	_Joystick[i].buttonState |= INPUT_JOYSTICK_RIGHT;
			if (_Joystick[i].joyState.lY > +25)	_Joystick[i].buttonState |= INPUT_JOYSTICK_DOWN;
			if (_Joystick[i].joyState.lX < -25)	_Joystick[i].buttonState |= INPUT_JOYSTICK_LEFT;
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

		//Kitao�X�V�BWindows�p�b�h�ł͂Ȃ��APCE�p�b�h�̏�ԂƂ��ċL�^����悤�ɂ����B����͗e�ʂƑΉ��\�t�g�����l���A�Q�{�^���R���g���[���P�̂݁B����A�ݒ�łU�{�^����}���`�^�b�v�ɂ��Ή��������B
		//           INPUT_UpdateState()��JOYPAD_Read���Ă΂�邽�тɂ��悤�ɂ������߁A�L�^�e�ʂ͕s��B1�L�^��8�r�b�g�ɂ����̂ł��̂Ԃ�͔����B
		if ((bRecord)&&(_bRecord))
		{
			rc = 0;
			if (INPUT_CheckButtonState(_PcePad[1].buttonU))
				rc |= 0x01;
			if (INPUT_CheckButtonState(_PcePad[1].buttonR))
				rc |= 0x02;
			if (INPUT_CheckButtonState(_PcePad[1].buttonD))
				rc |= 0x04;
			if (INPUT_CheckButtonState(_PcePad[1].buttonL))
				rc |= 0x08;
			if (INPUT_CheckButtonState(_PcePad[1].buttonSel))
				rc |= 0x10;
			if (INPUT_CheckButtonState(_PcePad[1].buttonRun))
				rc |= 0x20;
			if (INPUT_CheckButtonState(_PcePad[1].button1))
				rc |= 0x40;
			if (INPUT_CheckButtonState(_PcePad[1].button2))
				rc |= 0x80;
			_InputBuffer[_InputBufferIndex++] = rc;

			if (APP_GetInputRecordMode() == 2)
			{
				rc = 0;
				if (INPUT_CheckButtonState(_PcePad[2].buttonU))
					rc |= 0x01;
				if (INPUT_CheckButtonState(_PcePad[2].buttonR))
					rc |= 0x02;
				if (INPUT_CheckButtonState(_PcePad[2].buttonD))
					rc |= 0x04;
				if (INPUT_CheckButtonState(_PcePad[2].buttonL))
					rc |= 0x08;
				if (INPUT_CheckButtonState(_PcePad[2].buttonSel))
					rc |= 0x10;
				if (INPUT_CheckButtonState(_PcePad[2].buttonRun))
					rc |= 0x20;
				if (INPUT_CheckButtonState(_PcePad[2].button1))
					rc |= 0x40;
				if (INPUT_CheckButtonState(_PcePad[2].button2))
					rc |= 0x80;
				_InputBuffer[_InputBufferIndex++] = rc;
				//�U�{�^��or�A�ː�p�{�^��(�{�^��5,6���g�p)�̏�Ԃ���������
				rc = 0;
				if (INPUT_CheckButtonState(_PcePad[1].button3))
					rc |= 0x01;
				if (INPUT_CheckButtonState(_PcePad[1].button4))
					rc |= 0x02;
				if (INPUT_CheckButtonState(_PcePad[1].button5))
					rc |= 0x04;
				if (INPUT_CheckButtonState(_PcePad[1].button6))
					rc |= 0x08;
				if (INPUT_CheckButtonState(_PcePad[2].button3))
					rc |= 0x10;
				if (INPUT_CheckButtonState(_PcePad[2].button4))
					rc |= 0x20;
				if (INPUT_CheckButtonState(_PcePad[2].button5))
					rc |= 0x40;
				if (INPUT_CheckButtonState(_PcePad[2].button6))
					rc |= 0x80;
				_InputBuffer[_InputBufferIndex++] = rc;
			}

			if (_InputBufferIndex == INPUT_BUFFERSIZE)
			{
				APP_EndRecording();
				PRINTF("End of input buffer. Recording stopped.");
			}
		}
	}

	//Kitao�ǉ��B�Q�[�����Ƃ̎������쏈���B��Record�I����̂��̈ʒu�ŁBv1.15
	if (_bGameSetting) //���x�𗎂Ƃ��Ȃ����߂��̃t���O�ŁA�������s�����ǂ������ɔ��肷��B
	{
		//�O���f�B�E�X�C�����֎ցC�p���f�B�E�X���I�������I�ɃX�e���I�N���ɂ���B
		if (_bKonamiStereo)
		{
			reset_button_state(_PcePad[1].buttonU);  //�\���L�[�𗣂�����Ԃɂ���B�����֎ւŕK�v�B
			reset_button_state(_PcePad[1].buttonR);  //
			reset_button_state(_PcePad[1].buttonD);  //
			reset_button_state(_PcePad[1].buttonL);  //
			reset_button_state(_PcePad[1].buttonSel);//SEL�{�^���𗣂�����Ԃɂ���
			reset_button_state(_PcePad[1].buttonRun);//RUN�{�^���𗣂�����Ԃɂ���
			set_button_state(_PcePad[1].button1);	 //�P�{�^�����������ςȂ��ɂ��ꂽ��Ԃɂ���
		}
		//�O���f�B�E�XII�ŁA�����I�Ƀ��[�U�[�E�X�v���b�h�{����������Ȃ��ݒ�ɂ���B
		if (_bGradiusII)
		{
			//������Ȃ��ݒ�
			reset_button_state(_PcePad[1].buttonSel);//SEL�{�^���𗣂�����Ԃɂ���
			reset_button_state(_PcePad[1].buttonRun);//RUN�{�^���𗣂�����Ԃɂ���
			if (_PcePad[2].buttonD == -1) //�R���g���[���Q�̉��L�[�̐ݒ肪���Z�b�g����Ă���ꍇ
				_PcePad[2].buttonD = 902; //���z�I�ɐݒ�(902�͎��ۂ̓��͋@��ł͓��͂ł��Ȃ��l)���Ă���
			set_button_state(_PcePad[2].buttonD); //�R���g���[���[�Q�̉��L�[���������ςȂ��ɂ��ꂽ��Ԃɂ���
			//�A�[�P�[�h���[�h(�I���W�i���ʂƃ|�[�Y�@�\����)
			//set_button_state(_PcePad[1].buttonU);
			//set_button_state(_PcePad[1].button1);
			//set_button_state(_PcePad[1].button2);
		}
	}
}


/*-----------------------------------------------------------------------------
	[IsPressed]
		�w��̃{�^����������Ă��邩�ǂ�����Ԃ��܂��D
-----------------------------------------------------------------------------*/
//Kitao�X�V�B�����l�v���C�̂Ƃ����L�[�{�[�h�̃{�^�����g����悤�ɂ����B
BOOL
INPUT_IsPressed(
	Sint32	padID, //Kitao�X�V�BjoyID��padID(1�`5)�ցBPC�G���W���̃p�b�h�i���o�[�ŊǗ�����悤�ɂ����B
	Sint32	userButtonID)
{
	Sint32	a = -1;

	switch (userButtonID)
	{
		case JOYPAD_BUTTON_UP:
			a = _PcePad[padID].buttonU;
			break;
		case JOYPAD_BUTTON_RIGHT:
			a = _PcePad[padID].buttonR;
			break;
		case JOYPAD_BUTTON_DOWN:
			a = _PcePad[padID].buttonD;
			break;
		case JOYPAD_BUTTON_LEFT:
			a = _PcePad[padID].buttonL;
			break;
		case JOYPAD_BUTTON_SELECT:
			a = _PcePad[padID].buttonSel;
			break;
		case JOYPAD_BUTTON_RUN:
			a = _PcePad[padID].buttonRun;
			break;
		case JOYPAD_BUTTON_I:
			a = _PcePad[padID].button1;
			break;
		case JOYPAD_BUTTON_II:
			a = _PcePad[padID].button2;
			break;
		case JOYPAD_BUTTON_III:
			a = _PcePad[padID].button3;
			break;
		case JOYPAD_BUTTON_IV:
			a = _PcePad[padID].button4;
			break;
		case JOYPAD_BUTTON_V:
			a = _PcePad[padID].button5;
			break;
		case JOYPAD_BUTTON_VI:
			a = _PcePad[padID].button6;
			break;
	}

	return INPUT_CheckButtonState(a);
}


void
INPUT_Record(
	BOOL		bRecord)
{
	Sint32	softVersion;

	_bRecord = bRecord;

	if (_bRecord)
	{
		memset(_InputBuffer, 0, sizeof(_InputBuffer));
		_InputBufferIndex = 0;
		//Kitao�ǉ��B�w�b�_�[��t����B
		_InputBuffer[_InputBufferIndex++] = 1; //���R�[�h�t�@�C���̃o�[�W����
		switch (APP_GetInputRecordMode())
		{
			case 2:
				_InputBuffer[_InputBufferIndex++] = 2; //�p�b�h�� 1�`5�B
				_InputBuffer[_InputBufferIndex++] = 6; //�{�^���� 2or6�B
				break;
			default: //1
				_InputBuffer[_InputBufferIndex++] = 1; //�p�b�h�� 1�`5�B
				_InputBuffer[_InputBufferIndex++] = 2; //�{�^���� 2or6�B
				break;
		}
		softVersion = APP_GetSoftVersion(); //Ootake�{�̂̃o�[�W����(�����_���J�b�g���ĂR��������)
		_InputBuffer[_InputBufferIndex++] = (Uint8)(softVersion % 256); //Ootake�{�̂̃o�[�W����
		_InputBuffer[_InputBufferIndex++] = (Uint8)(softVersion / 256); //Ootake�{�̂̃o�[�W����
		_InputBuffer[_InputBufferIndex++] = 0; //�\��
		_InputBuffer[_InputBufferIndex++] = 0; //�\��
		_InputBuffer[_InputBufferIndex++] = 0; //�\��

		if (_bPlayRecord)
			_bPlayRecord = FALSE;
	}
}

void
INPUT_PlayRecord(
	BOOL		bPlayrecord)
{
	_bPlayRecord = bPlayrecord;

	if (_bRecord)
		_bRecord = FALSE;

	_InputBufferIndex = 0;
	//Kitao�ǉ��B�w�b�_�[��ǂށB�����o�[�W�����ł͓ǂݔ�΂�����
	_InputBufferIndex++; //���R�[�h�t�@�C���̃o�[�W����
	_InputPlayRecordPad = _InputBuffer[_InputBufferIndex++]; //�p�b�h�� 1�`5�B���o�[�W������1��2�B
	_InputBufferIndex++; //�{�^���� 2or6�B���o�[�W������2�{�^����p
	_InputBufferIndex++; //Ootake�{�̂̃o�[�W����
	_InputBufferIndex++; //Ootake�{�̂̃o�[�W����
	_InputBufferIndex++; //�\��
	_InputBufferIndex++; //�\��
	_InputBufferIndex++; //�\��
}


//Kitao�X�V
BOOL
INPUT_WriteBuffer(
	FILE*		fp)
{
	if (fwrite(&_InputBufferIndex, sizeof(_InputBufferIndex), 1, fp) != 1) return FALSE; //�o�b�t�@�ɗ��܂����o�C�g������������
	return fwrite(_InputBuffer, sizeof(Uint8)*_InputBufferIndex, 1, fp) == 1; //�o�b�t�@�ɗ��܂������e����������
}

//Kitao�X�V
BOOL
INPUT_ReadBuffer(
	FILE*		fp)
{
	if (fread(&_InputBufferIndexEnd, sizeof(_InputBufferIndexEnd), 1, fp) != 1)	return FALSE; //�o�C�g����ǂݍ���
	return fread(_InputBuffer, sizeof(Uint8)*_InputBufferIndexEnd, 1, fp) == 1; //���e��ǂݍ���
}


Sint32
INPUT_GetNumJoystick()
{
	return _nJoySticks;
}


/*-----------------------------------------------------------------------------
	[IsTriggered]
	�{�^�����g���K���ꂽ���ǂ�����Ԃ��܂��D
-----------------------------------------------------------------------------*/
BOOL
INPUT_IsTriggered(
	Sint32		userButtonID)
{
	/* ������ */
	return FALSE;
}


//Kitao�ǉ��B�������̂��߂�DirectInput�̃A�N�Z�X���̎擾�̓A�N�e�B�u�ɂȂ����Ƃ��P�񂾂��s���悤�ɂ����B
void
INPUT_Acquire()
{
	int i;

	//�L�[�{�[�h
	if (_pDIDKey != NULL)
		_pDIDKey->Acquire();

	//�W���C�X�e�B�b�N
	for (i = 0; i < _nJoySticks; ++i)
		if (_pDIDJoy[i] != NULL)
			_pDIDJoy[i]->Acquire();
}


//Kitao�ǉ��B�e�Q�[�����Ƃ̎�������ݒ�����Z�b�g(�I�t��)����B
void
INPUT_ResetGameSetting()
{
	_bGameSetting = FALSE;
	_bKonamiStereo = FALSE;
	_bGradiusII = FALSE;
}

//Kitao�ǉ��B�O���f�B�E�X�C�����֎ցC�p���f�B�E�X���I�������I�ɃX�e���I�N���ɂ���B
void
INPUT_SetKonamiStereo(
	BOOL	bKonamiStereo)
{
	_bKonamiStereo = bKonamiStereo;
	_bGameSetting = _bKonamiStereo;
}

//Kitao�ǉ��B�O���f�B�E�XII�ŁA���[�U�[�E�X�v���b�h�{����������Ȃ��ݒ�ɁB
void
INPUT_SetGradiusII(
	BOOL	bGradiusII)
{
	_bGradiusII = bGradiusII;
	_bGameSetting = _bGradiusII;
}
