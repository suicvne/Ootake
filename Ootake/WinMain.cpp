/******************************************************************************
Ootake
�EDirectInput�̃A�N�Z�X���̎擾���A�E�B���h�E���A�N�e�B�u�ɂȂ����Ƃ��ɂP�x��
  �������Ȃ��悤�ɂ����B�i�������j
�EPAINT�������̃C�x���g�������ȗ������Bv0.95�B�i�������j
�EWindows�̃{�����[���~�L�T�[�́A���̃A�v���ւ̉e�����o�Ă��܂����ߎg�p���Ȃ���
  ���ɂ����B
�E�V���[�g�J�b�g�L�[��ǉ��E�ύX�����B�X�e�[�g�Z�[�u�ƃ��[�h�́A�t���������Ȃ�
  �悤�ɓ��������Ƃ���'S'��'L'�ɂ����B
�E�}�E�X�z�C�[���̉�]����ŃZ���N�g�{�^��(���])�E�����{�^��(������])���@�\
  ������悤�ɂ����B�z�C�[��(�^�񒆃{�^��)���N���b�N���邱�Ƃł��A�����{�^����
  �@�\������悤�ɂ����B
�E�E�B���h�E���[�h���ɁA��Ɏ�O�ɕ\������悤�ɂ����B
�E�N�����͉��_��ԂŋN������悤�ɂ����B

Copyright(C)2006-2016 Kitao Nakamura.
    Attach the source code when you open the remodeling version and the
    succession version to the public. and, please contact me by E-mail.
    Business use is prohibited.
	Additionally, it applies to "GNU General Public License". 
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[WinMain.c]

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

#define _WIN32_WINNT 0x0400 //WM_MOUSEWHEEL�g�p�̂��ߕK�v
#define DIRECTINPUT_VERSION	0x0500	//Kitao�ǉ��B���ɂ���邩������Ȃ����ADirectInput5���y���B7���Ƃ��x������B�X�y�[�X�n���A�[���킩��₷���B

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "WinMain.h"
#include "resource.h"
#include "AppEvent.h"
#include "MainBoard.h"
#include "AudioConfig.h"
#include "App.h"
#include "Input.h"
#include "Printf.h"

static BOOL _bBreakTrap; //Kitao�ǉ��B�f�o�b�O�p

static HINSTANCE	_hInstance;
static HWND			_hMainWnd;

static char			_Caption[2048]; //Kitao�ǉ��B���ݕ\�����̃L���v�V����


static int
init_argc(
	LPSTR		lpCmdLine)
{
	int		argc = 1;

	while (lpCmdLine != NULL)
	{
		while (*lpCmdLine == ' ') // ' '�̓X�L�b�v���� 
			++lpCmdLine;

		if (strlen(lpCmdLine) > 0)
			++argc;
		else
			break;

		// " �𔭌������ꍇ�͎��� " �܂ł��P�� argument �Ƃ��� 
		if (*lpCmdLine == '"')
		{
			++lpCmdLine;

			// " ��������݂��� 
			if (strchr(lpCmdLine, '"') != NULL)
				lpCmdLine = strchr(lpCmdLine, '"') + 1; // " ���X�L�b�v����
			else
			{
				// �݂���Ȃ������ꍇ�� argument �Ȃ��Ƃ݂Ȃ� 
				argc = 1;
				break;
			}
		}
		else
		{
			if (strchr(lpCmdLine, ' ') != NULL)
				lpCmdLine = strchr(lpCmdLine, ' ');
			else
				break;
		}
	}

	return argc;
}


static char**
init_argv(
	int			argc,
	LPSTR		lpCmdLine)
{
	char**		ppArgv;
	char*		p;
	int			i;

	if (argc == 0)
		return NULL;

	ppArgv = (char**)GlobalAlloc(GMEM_FIXED, sizeof(char*) * argc);

	if (ppArgv == NULL)
		exit(-1);


	for (i = 0; i < argc; i++)
	{
		ppArgv[i] = (char*)GlobalAlloc(GMEM_FIXED, MAX_PATH+1);

		if (i == 0)
			GetModuleFileName(NULL, ppArgv[i], MAX_PATH+1); //argv[0]
		else
		{
			// ' ' �̓X�L�b�v���� 
			while (*lpCmdLine == ' ')
				++lpCmdLine;

			// " �𔭌������ꍇ�͎��� " �܂ł� argument �Ƃ��� 
			if (*lpCmdLine == '"')
			{
				p = lpCmdLine + 1;
				strcpy(ppArgv[i], p);

				// ���� " ��T�� 
				if ((p = strchr(ppArgv[i], '"')) != NULL)
				{
					*p = '\0';
					// " �Q���X�L�b�v���� 
					lpCmdLine += strlen(ppArgv[i]) + 2;
				}
				else
				{
					// ���� " ���Ȃ������ꍇ�̓��[�v���ʂ��� 
					// (argc �̏������Ō����ς݂Ȃ̂ł����ɂ͂��Ȃ��͂�) 
					break;
				}
			}
			else
			{
				strcpy(ppArgv[i], lpCmdLine);

				if ((p = strchr(ppArgv[i], ' ')) != NULL)
					*p = '\0';

				lpCmdLine += strlen(ppArgv[i]);
			}
		}
	}

	return ppArgv;
}


static void
set_fullscreen_windowstyle(
	HWND	hWnd,
	int		width,
	int		height)
{
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~(WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION | WS_DLGFRAME)); //Kitao�X�V
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, width, height, SWP_FRAMECHANGED | SWP_NOCOPYBITS | SWP_NOREDRAW | SWP_DEFERERASE | SWP_NOSENDCHANGING); //Kitao�X�V�B�t���X�N���[���؂�ւ����̑��x�A�b�v�Bv2.23�Bv2.65
}


static void
set_normal_windowstyle(
	HWND	hWnd,
	int		width,
	int		height)
{
	RECT		rc;
	DWORD		dwStyle;
	int			x;
	int			y;

	dwStyle = GetWindowLong(hWnd, GWL_STYLE) | (WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION | WS_DLGFRAME); //Kitao�X�V�B�E�B���h�E�T�C�Y�ύX�s�ɁB
	SetWindowLong(hWnd, GWL_STYLE, dwStyle);

	GetWindowRect(hWnd, &rc);
	x = rc.left;
	y = rc.top;

	SetRect(&rc, 0, 0, width, height);

	AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), GetMenu(hWnd) != NULL);
	if (APP_GetWindowTopMost())
		SetWindowPos(hWnd, HWND_TOPMOST, x, y, rc.right - rc.left, rc.bottom - rc.top, SWP_FRAMECHANGED); //Kitao�X�V�B��Ɏ�O�ɕ\���B
	else
		SetWindowPos(hWnd, HWND_NOTOPMOST, x, y, rc.right - rc.left, rc.bottom - rc.top, SWP_FRAMECHANGED);
}


//Kitao�ǉ��B�E�B���h�E�ړ����������A�N�e�B�u���Ƀ|�[�Y���������鏈��
static void
cancelPause()
{
	RECT	rc;

	if (MAINBOARD_GetPause() == FALSE) //�|�[�Y���ł͂Ȃ������ꍇ
		return;

	if (APP_GetPauseNoRelease()) //�t���X�N���[���ƃE�B���h�E�̃��[�h�ؑ֒���A�E�B���h�E�ŏ������̓|�[�Y���������Ȃ��B�i���̗����듮���h���̂ɕK�v�j
		return;

	if (!APP_GetFullScreen()) //�E�B���h�E�\���̏ꍇ
		MAINBOARD_ScreenUpdate(TRUE,TRUE); //�X�N���[�����ĕ`��

	if (APP_GetRunning()) //���j���[���\������Ă��Ȃ��ꍇ
	{
		//�����A�E�B���h�E�E���Ɖ�������ʂ���͂ݏo�Ă����ꍇ�́A�|�[�Y���ꂽ�܂܂ɂ���B
		GetWindowRect(_hMainWnd, &rc);
		if ((rc.right <= GetSystemMetrics(SM_CXSCREEN))&&
			(rc.bottom <= GetSystemMetrics(SM_CYSCREEN))) //�E���Ɖ������͂ݏo���Ă��Ȃ����
		{
			if ((rc.left < 0)&&(rc.top < 0)) //�������㑤���͂ݏo���Ă����ꍇ
				MoveWindow(_hMainWnd, 0, 0,
							rc.right-rc.left, rc.bottom-rc.top, TRUE);//�E�B���h�E�̈ʒu��ς���
			else
			if (rc.left < 0) //�������͂ݏo���Ă����ꍇ
				MoveWindow(_hMainWnd, 0, rc.top,
							rc.right-rc.left, rc.bottom-rc.top, TRUE);//�E�B���h�E�̈ʒu��ς���
			else
			if (rc.top < 0) //�㑤���͂ݏo���Ă����ꍇ
				MoveWindow(_hMainWnd, rc.left, 0,
							rc.right-rc.left, rc.bottom-rc.top, TRUE);//�E�B���h�E�̈ʒu��ς���
			MAINBOARD_Pause(FALSE);//�|�[�Y����
		}
	}
}

static LRESULT CALLBACK
wnd_proc(
	HWND		hWnd,
	UINT		uMsg,
	WPARAM		wParam,
	LPARAM		lParam)
{
	short		delta;//Kitao�ǉ��B�}�E�X�z�C�[�����o�p
	Sint32		a;
	HWND		hP;
	MSG			msg;

	switch(uMsg)
	{
	//Kitao�ǉ��BDirectInput�̃A�N�Z�X���̎擾�������ł���悤�ɂ����B�i�������j
	case WM_ACTIVATE:
		if (APP_GetInit()) //���������������Ă���Ƃ��̂݁Bv2.77
		{
			if (wParam == 0) //��A�N�e�B�u�ɂȂ�Ƃ�
			{
				if ((APP_GetDrawMethod() == 2)&&(APP_GetFullScreen())) //DirectDraw�̃t���X�N���[���Ŕ�A�N�e�B�u�ɂȂ�ꍇ
				{
					hP = GetWindow((HWND)lParam, GW_OWNER); //�_�C�A���O�̐e�n���h��
					if (hP != _hMainWnd) //Ootake�̃_�C�A���O���A�N�e�B�u�ɂȂ�ۂɂ͏������Ȃ��B
					{
						APP_ToggleFullscreen();//Window���[�h�֋����I�ɖ߂��B�������Ȃ��Ăуt�H�[�J�X�𓾂��Ȃ��B
						APP_RunEmulator(FALSE);//��ʂ��P�N���b�N�Ń|�[�Y�����ł���悤�Ƀ��j���[��\�����Ẵ|�[�Y�B
					}
				}
				if (APP_GetInactivePause())
					if (!MAINBOARD_GetPause()) //�|�[�Y���Ă��Ȃ��ꍇ
						MAINBOARD_Pause(TRUE);//�|�[�Y
			}
			else //�A�N�e�B�u�ɂȂ�Ƃ�
			{
				INPUT_Acquire(); //DirectInput�̃A�N�Z�X�����𓾂�
				if (IsIconic(hWnd) == FALSE) //�ŏ�������Ă���Ƃ��͂����Ń|�[�Y���������Ȃ��i�ŏ�������ɑ��̃A�v���t�H�[�J�X���ڂ�Ƃ��ɁA��uOotake���A�N�e�B�u�ɂȂ邽�߁j
					cancelPause(); //�|�[�Y���������B�ŏ�������m�[�}���ɖ߂��ꂽ�Ƃ��ɕK�v�B
			}
		}
		break;

	//Kitao�ǉ��B�E�B���h�E���ړ��h���b�O���̓G�~�����[�^������|�[�Y����B
	case WM_ENTERSIZEMOVE:
		if (!MAINBOARD_GetPause()) //�|�[�Y���Ă��Ȃ��ꍇ
			MAINBOARD_Pause(TRUE);//�|�[�Y
		break;
	//Kitao�ǉ��B�E�B���h�E�̈ړ��h���b�O���I�������G�~�����[�^����̃|�[�Y����������B
	case WM_EXITSIZEMOVE:
		if (!APP_GetFullScreen()) //�t���X�N���[�����͋@�\�����Ȃ�(���̃A�v���փt�H�[�J�X���ڂ����Ƃ��Ɍ듮�삷�邽��)
		{
			APP_SaveWindowPosition(); //�E�B���h�E�̈ʒu��ۑ����Ă����B
			cancelPause(); //�|�[�Y��������
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_F1: //Kitao�X�V CD�Q�[���v���C���́A[F1]�L�[��CD�̓���ւ����ł���悤�ɂ����B
			if (GetKeyState(VK_CONTROL) < 0) //Ctrl�L�[�������Ȃ���̏ꍇ
				APPEVENT_Set(APPEVENT_CDCHANGE, NULL); //CD Play
			else //�ʏ�
			{
				if (APP_GetF1NoReset())
					APPEVENT_Set(APPEVENT_CHANGE_CDC, NULL);
				else
				{
					if ((APP_GetCDGame())&&(!APP_GetCueFile()))
						APPEVENT_Set(APPEVENT_CDCHANGE, NULL);
					else
						APPEVENT_Set(APPEVENT_RESET, NULL);
				}
			}
			break;
		case VK_ESCAPE:		APPEVENT_Set(APPEVENT_RUN, NULL);					break;//[Esc]�L�[ Kitao�X�V
		case VK_MENU: //[Alt]�L�[ v2.66�X�V�BAlt�L�[�𗣂��Ă���MENU�\������悤�ɂ����B
				APPEVENT_Set(APPEVENT_SHOWMENU, NULL); //MENU�\��
				break;
		case 'O':			APPEVENT_Set(APPEVENT_FILEDIALOG, NULL);			break;//[O]�L�[ Kitao�X�V
		case 'P':			APPEVENT_Set(APPEVENT_CD_PLAYINSTALL, NULL);		break;//[P]�L�[ Kitao�X�V
		//case 'S':			APPEVENT_Set(APPEVENT_SAVESTATE, NULL);				break;//[S]�L�[ Kitao�X�V
		//case 'L':			APPEVENT_Set(APPEVENT_LOADSTATE, NULL);				break;//[L]�L�[ Kitao�X�V
		//case VK_F4:		APPEVENT_Set(APPEVENT_PARTIALMEMORYLOAD, NULL);		break;
		case VK_F4:			APPEVENT_Set(APPEVENT_SHOW_DEBUG, NULL);			break;//[F4]��DEBUG�E�B���h�E��\�� Kitao�X�V
		case VK_F5:			APPEVENT_Set(APPEVENT_RECORDING, NULL);				break;//[F5]��RECORD Kitao�X�V
		case VK_F6:			APPEVENT_Set(APPEVENT_PLAYRECORD, NULL);			break;//[F6]��PLAYBACK Kitao�X�V
		case VK_F8: //[F8]�ŉ���MUTE�Bv1.63
				if (APP_GetVolumeEffect() == 0) //���ł�MUTE�������ꍇ�m�[�}���ɖ߂��B
				{
					APP_ReturnCaption(); //���b�Z�[�W������
					APPEVENT_Set(APPEVENT_VOLUME_NORMAL, NULL);
				}
				else
				{
					PRINTF("Mute Volume. ([F8]=Return)");
					APPEVENT_Set(APPEVENT_VOLUME_MUTE, NULL);
				}
				break;
		case VK_F9:			APPEVENT_Set(APPEVENT_SCREEN_MINIMIZE, NULL);		break;//Kitao�ǉ�
		case VK_F11: //Kitao�ǉ�
			APPEVENT_Set(APPEVENT_SCREEN_SHOWOVERSCAN, NULL); //�I�[�o�[�X�L�����̈�\���ؑ�
			break;
		case VK_F12:
			if (GetKeyState(VK_CONTROL) < 0) //Ctrl�L�[�������Ȃ���̏ꍇ
			{	//"Windows Aero"(Win7/Vista)�̖����E�L���ؑցBv2.21�ǉ�
				if (APP_GetDisableWindowsAero())
					APPEVENT_Set(APPEVENT_SCREEN_USEAERO, NULL);
				else
					APPEVENT_Set(APPEVENT_SCREEN_DISABLEAERO, NULL);
			}
			else //�ʏ�
				APPEVENT_Set(APPEVENT_SCREEN_FULLSCREEN, NULL); //�t���X�N���[���ؑ�
			break;
		case 'R': //Kitao�ǉ��B[R]�L�[
			APP_RunEmulator(FALSE); //�|�[�Y���ă��j���[���o���B�t���X�N���[�����ɕK�v�Bv2.70
			keybd_event(VK_MENU, 0, 0, 0);//Alt�L�[
			keybd_event('R', 0, 0, 0);
			keybd_event('R', 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
			break;
		case VK_PRIOR: //Kitao�ǉ��B[PageUp]�L�[
			//���ʃA�b�v
			if (GetKeyState(VK_CONTROL) < 0) //Ctrl�L�[�������Ȃ���̏ꍇ
				APPEVENT_Set(APPEVENT_VOLUME_DETAILUP, NULL); //�ׂ������ʒ���
			else //�ʏ�
				APPEVENT_Set(APPEVENT_VOLUME_UP, NULL);
			break;
		case VK_NEXT: //Kitao�ǉ��B[PageDown]�L�[
			//���ʃ_�E��
			if (GetKeyState(VK_CONTROL) < 0) //Ctrl�L�[�������Ȃ���̏ꍇ
				APPEVENT_Set(APPEVENT_VOLUME_DETAILDN, NULL); //�ׂ������ʒ���
			else //�ʏ�
				APPEVENT_Set(APPEVENT_VOLUME_DOWN, NULL);
			break;
		case VK_HOME: //Kitao�ǉ��B[Home]�L�[
			//Video�X�s�[�h���A�b�v
			APPEVENT_Set(APPEVENT_SPEED_VUP, NULL);
			break;
		case VK_END: //Kitao�ǉ��B[End]�L�[
			//Video�X�s�[�h���_�E��
			APPEVENT_Set(APPEVENT_SPEED_VDOWN, NULL);
			break;
		case VK_INSERT: //Kitao�ǉ��B[Insert]�L�[
			APP_ToggleUseVideoSpeedUpButton();
			break;
		case VK_DELETE: //Kitao�ǉ��B[Delete]�L�[
			if (GetKeyState(VK_SHIFT) < 0) //Shift�L�[�������Ȃ���̏ꍇ
			{	//�{�����グ��B�ō����̎��̓m�[�}���B
				switch (VDC_GetOverClockType())
				{
					case   0:	APPEVENT_Set(APPEVENT_SPEED_P1, NULL);	break;
					case   1:	APPEVENT_Set(APPEVENT_SPEED_P2, NULL);	break;
					case   2:	APPEVENT_Set(APPEVENT_SPEED_P3, NULL);	break;
					case   3:	APPEVENT_Set(APPEVENT_SPEED_P4, NULL);	break;
					case   4:	APPEVENT_Set(APPEVENT_SPEED_P5, NULL);	break;
					case   5:	APPEVENT_Set(APPEVENT_SPEED_P6, NULL);	break;
					case   6:	APPEVENT_Set(APPEVENT_SPEED_T1, NULL);	break;
					case 100:	APPEVENT_Set(APPEVENT_SPEED_T2, NULL);	break;
					case 200:	APPEVENT_Set(APPEVENT_SPEED_T3, NULL);	break;
					case 300:	APPEVENT_Set(APPEVENT_SPEED_P0, NULL);	break;
				}
			}
			else if (GetKeyState(VK_CONTROL) < 0) //Ctrl�L�[�������Ȃ���̏ꍇ
			{	//�{����������B�m�[�}���̎��͍ō����B
				switch (VDC_GetOverClockType())
				{
					case   0:	APPEVENT_Set(APPEVENT_SPEED_T3, NULL);	break;
					case   1:	APPEVENT_Set(APPEVENT_SPEED_P0, NULL);	break;
					case   2:	APPEVENT_Set(APPEVENT_SPEED_P1, NULL);	break;
					case   3:	APPEVENT_Set(APPEVENT_SPEED_P2, NULL);	break;
					case   4:	APPEVENT_Set(APPEVENT_SPEED_P3, NULL);	break;
					case   5:	APPEVENT_Set(APPEVENT_SPEED_P4, NULL);	break;
					case   6:	APPEVENT_Set(APPEVENT_SPEED_P5, NULL);	break;
					case 100:	APPEVENT_Set(APPEVENT_SPEED_P6, NULL);	break;
					case 200:	APPEVENT_Set(APPEVENT_SPEED_T1, NULL);	break;
					case 300:	APPEVENT_Set(APPEVENT_SPEED_T2, NULL);	break;
				}
			}
			else //�ʏ퉟��
			{	//�}�C�Z�b�e�B���O�������x�ɐ؂�ւ���B���łɃZ�b�e�B���O�������x�ɂȂ��Ă����ꍇ�̓m�[�}���ɖ߂��Bv1.61
				
				if (VDC_GetOverClockType() == APP_GetMySetOverClockType())
				{
					if (VDC_GetAutoOverClock() != -1) //�����ŃI�[�o�[�N���b�N���Ă���Q�[���̏ꍇ�Bv2.20
						a = VDC_GetAutoOverClock();
					else
						a = 0; //�m�[�}���ɖ߂�
				}
				else
					a = APP_GetMySetOverClockType();
				switch (a)
				{
					case   0:	APPEVENT_Set(APPEVENT_SPEED_P0, NULL);	break;
					case 300:	APPEVENT_Set(APPEVENT_SPEED_T3, NULL);	break;
					case 200:	APPEVENT_Set(APPEVENT_SPEED_T2, NULL);	break;
					case 100:	APPEVENT_Set(APPEVENT_SPEED_T1, NULL);	break;
					case   6:	APPEVENT_Set(APPEVENT_SPEED_P6, NULL);	break;
					case   5:	APPEVENT_Set(APPEVENT_SPEED_P5, NULL);	break;
					case   4:	APPEVENT_Set(APPEVENT_SPEED_P4, NULL);	break;
					case   3:	APPEVENT_Set(APPEVENT_SPEED_P3, NULL);	break;
					case   2:	APPEVENT_Set(APPEVENT_SPEED_P2, NULL);	break;
					case   1:	APPEVENT_Set(APPEVENT_SPEED_P1, NULL);	break;
					case  -1:	APPEVENT_Set(APPEVENT_SPEED_M1, NULL);	break;
					case  -2:	APPEVENT_Set(APPEVENT_SPEED_M2, NULL);	break;
				}
			}
			break;
		case VK_BACK: //Kitao�ǉ��B[BackSpace]�L�[
			APP_SetSpeedNormal();
			break;
		case VK_F2:		APPEVENT_Set(APPEVENT_ADVANCEFRAME_1, NULL);		break;//Kitao�ǉ�
		case '1':		APPEVENT_Set(APPEVENT_INPUT_TURBO_1, NULL);			break;//Kitao�ǉ�
		case '2':		APPEVENT_Set(APPEVENT_INPUT_TURBO_2, NULL);			break;//Kitao�ǉ�
		case '3':		APPEVENT_Set(APPEVENT_INPUT_TURBO_RUN, NULL);		break;//Kitao�ǉ�
		case '4':		APPEVENT_Set(APPEVENT_INPUT_TURBO_HIGH, NULL);		break;//Kitao�ǉ�
		case '5':		APPEVENT_Set(APPEVENT_INPUT_TURBO_MIDDLE, NULL);	break;//Kitao�ǉ�
		case '6':		APPEVENT_Set(APPEVENT_INPUT_TURBO_LOW, NULL);		break;//Kitao�ǉ�
		case '7':		APPEVENT_Set(APPEVENT_INPUT_TURBO_OFF, NULL);		break;//Kitao�ǉ�
		case '8':		APPEVENT_Set(APPEVENT_INPUT_SWAP_SELRUN, NULL);		break;//Kitao�ǉ�
		//case 'Q':		WINMAIN_SetBreakTrap(~WINMAIN_GetBreakTrap());		break;//Kitao�ǉ��B�f�o�b�O�p�B
		}
		break;

	case WM_SYSKEYDOWN:
		switch (wParam)
		{
			case VK_RETURN: //[Enter]�L�[ v2.66�ǉ�
					if (GetKeyState(VK_MENU) < 0) //Alt�L�[�������Ȃ���̏ꍇ
					{
						APPEVENT_Set(APPEVENT_SCREEN_FULLSCREEN, NULL); //�t���X�N���[���ؑ�
						while (PeekMessage(&msg, hWnd, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE)); //�L�[�o�b�t�@���N���A
					}
					break;
			case '1': //[1]�L�[ v2.66�ǉ�
					if (!APP_GetFullScreen()) //�E�B���h�E���[�h�̏ꍇ�̂ݗL��
						if (GetKeyState(VK_MENU) < 0) //Alt�L�[�������Ȃ���̏ꍇ
							{
								APPEVENT_Set(APPEVENT_SCREEN_X1, NULL); //�E�B���h�E�T�C�Y��x1�ɁB
								while (PeekMessage(&msg, hWnd, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE)); //�L�[�o�b�t�@���N���A
							}
					break;
			case '2': //[2]�L�[ v2.66�ǉ�
					if (!APP_GetFullScreen()) //�E�B���h�E���[�h�̏ꍇ�̂ݗL��
						if (GetKeyState(VK_MENU) < 0) //Alt�L�[�������Ȃ���̏ꍇ
							{
								APPEVENT_Set(APPEVENT_SCREEN_X2, NULL); //�E�B���h�E�T�C�Y��x2�ɁB
								while (PeekMessage(&msg, hWnd, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE)); //�L�[�o�b�t�@���N���A
							}
					break;
			case '3': //[3]�L�[ v2.66�ǉ�
					if (!APP_GetFullScreen()) //�E�B���h�E���[�h�̏ꍇ�̂ݗL��
						if (GetKeyState(VK_MENU) < 0) //Alt�L�[�������Ȃ���̏ꍇ
							{
								APPEVENT_Set(APPEVENT_SCREEN_X3, NULL); //�E�B���h�E�T�C�Y��x3�ɁB
								while (PeekMessage(&msg, hWnd, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE)); //�L�[�o�b�t�@���N���A
							}
					break;
			case '4': //[4]�L�[ v2.66�ǉ�
					if (!APP_GetFullScreen()) //�E�B���h�E���[�h�̏ꍇ�̂ݗL��
						if (GetKeyState(VK_MENU) < 0) //Alt�L�[�������Ȃ���̏ꍇ
							{
								APPEVENT_Set(APPEVENT_SCREEN_X4, NULL); //�E�B���h�E�T�C�Y��x4�ɁB
								while (PeekMessage(&msg, hWnd, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE)); //�L�[�o�b�t�@���N���A
							}
					break;
		}
		break;

	case WM_LBUTTONDOWN:
		if ((!MOUSE_IsConnected())||(MAINBOARD_GetPause()))
				APPEVENT_Set(APPEVENT_RUN, NULL);//Kitao�ǉ��B�}�E�X��g�p���G�~�����[�^���|�[�Y���Ȃ�A�N���b�N�Ń|�[�Yor�����B
		MOUSE_LButtonDown(TRUE);
		break;

	case WM_LBUTTONUP:
		MOUSE_LButtonDown(FALSE);
		break;

	case WM_RBUTTONDOWN:
		if ((!MOUSE_IsConnected())||(MAINBOARD_GetPause()))
				APPEVENT_Set(APPEVENT_RUN, NULL);//Kitao�ǉ��B�}�E�X��g�p���G�~�����[�^���|�[�Y���Ȃ�A�E�N���b�N�Ń|�[�Yor�����B
		MOUSE_RButtonDown(TRUE);
		break;

	case WM_RBUTTONUP:
		MOUSE_RButtonDown(FALSE);
		break;

	case WM_MBUTTONDOWN: //Kitao�ǉ��B�}�E�X�̐^�񒆃{�^�����_�E�����ꂽ�Ƃ�
		if (!MOUSE_IsConnected())
			APPEVENT_Set(APPEVENT_RUN, NULL);//�^�񒆃{�^���N���b�N�Ń|�[�Yor�����B
		MOUSE_RunButtonDown(TRUE);
		break;

	case WM_MBUTTONUP: //Kitao�ǉ��B�}�E�X�̐^�񒆃{�^���������ꂽ�Ƃ�
		MOUSE_RunButtonDown(FALSE);
		break;

	case WM_MOUSEWHEEL: //Kitao�ǉ��B�}�E�X�̃z�C�[���𓮂������Ƃ�
		if (MOUSE_GetMouseWheelFlg() == 0)
		{
			delta = HIWORD(wParam);
			if (delta < 0) //������
			{
				MOUSE_SelButtonDown(FALSE);//���Z�b�g����ɂȂ��Ă��܂�Ȃ��悤��SELECT�{�^���͗���
				MOUSE_RunButtonDown(TRUE);//RUN�{�^�������������Ƃɂ���
				MOUSE_SetMouseWheelFlg();
			}
			else if (delta > 0) //�����
			{
				MOUSE_RunButtonDown(FALSE);//���Z�b�g����ɂȂ��Ă��܂�Ȃ��悤��RUN�{�^���͗���
				MOUSE_SelButtonDown(TRUE);//SELECT�{�^�������������Ƃɂ���
				MOUSE_SetMouseWheelFlg();
			}
		}
		break;

	case WM_DROPFILES:
		{
			HDROP		hDrop;
			char		dragFilePathName[MAX_PATH+1];

			hDrop = (HDROP)wParam;
			DragQueryFile(hDrop, 0, dragFilePathName, MAX_PATH+1);

			APPEVENT_Set(APPEVENT_OPENGAME, dragFilePathName);

			DragFinish(hDrop);
		}
		break;

	case WM_ENTERMENULOOP:
		APP_RunEmulator(FALSE); //Kitao�ǉ�
		APPEVENT_Set(APPEVENT_SHOWMENU, NULL);
		break;

	case WM_CLOSE:
		if (APP_GetFullScreen()) //Kitao�ǉ��B�t���X�N���[���̂Ƃ��̓f�X�N�g�b�v�𗐂��Ă��܂�Ȃ��悤�ɃE�B���h�E���[�h�ɖ߂��Ă���I������B�E�B���h�E��CLOSE����O�ɍs��Ȃ��Ə�������Ȃ��B
			APP_ToggleFullscreen();
		APPEVENT_Set(APPEVENT_EXIT, NULL);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_SET_FULLSCREEN_WS:
		set_fullscreen_windowstyle(hWnd, (int)wParam, (int)lParam);
		APPEVENT_Set(APPEVENT_REDRAWSCREEN, NULL);
		return 0;

	case WM_SET_NORMAL_WS:
		set_normal_windowstyle(hWnd, (int)wParam, (int)lParam);
		APPEVENT_Set(APPEVENT_REDRAWSCREEN, NULL);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case WM_OPEN_FILE:				APPEVENT_Set(APPEVENT_FILEDIALOG, NULL);			break;
		case WM_CD_CHANGE:				APPEVENT_Set(APPEVENT_CDCHANGE, NULL);				break;//Kitao�ǉ�
		case WM_RESET_EMULATOR:			APPEVENT_Set(APPEVENT_RESET, NULL);					break;
		case WM_RUN_EMULATOR:			APPEVENT_Set(APPEVENT_RUN, NULL);					break;
//		case WM_STOP_EMULATOR:			APPEVENT_Set(APPEVENT_PAUSE, NULL);					break;
		case WM_PAUSE_BUTTON:			APPEVENT_Set(APPEVENT_PAUSE_BUTTON, NULL);			break;//Kitao�ǉ�
		case WM_SET_RESUME:				APPEVENT_Set(APPEVENT_RESUME, NULL);				break;//Kitao�ǉ�
		case WM_AUTO_RESUME:			APPEVENT_Set(APPEVENT_AUTO_RESUME, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE:				APPEVENT_Set(APPEVENT_SAVESTATE, NULL);				break;
		case WM_SAVE_STATE_1:			APPEVENT_Set(APPEVENT_SAVESTATE_1, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_2:			APPEVENT_Set(APPEVENT_SAVESTATE_2, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_3:			APPEVENT_Set(APPEVENT_SAVESTATE_3, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_4:			APPEVENT_Set(APPEVENT_SAVESTATE_4, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_5:			APPEVENT_Set(APPEVENT_SAVESTATE_5, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_6:			APPEVENT_Set(APPEVENT_SAVESTATE_6, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_7:			APPEVENT_Set(APPEVENT_SAVESTATE_7, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_8:			APPEVENT_Set(APPEVENT_SAVESTATE_8, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_9:			APPEVENT_Set(APPEVENT_SAVESTATE_9, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_10:			APPEVENT_Set(APPEVENT_SAVESTATE_10, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_11:			APPEVENT_Set(APPEVENT_SAVESTATE_11, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_12:			APPEVENT_Set(APPEVENT_SAVESTATE_12, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_13:			APPEVENT_Set(APPEVENT_SAVESTATE_13, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_14:			APPEVENT_Set(APPEVENT_SAVESTATE_14, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_15:			APPEVENT_Set(APPEVENT_SAVESTATE_15, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_16:			APPEVENT_Set(APPEVENT_SAVESTATE_16, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_17:			APPEVENT_Set(APPEVENT_SAVESTATE_17, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_18:			APPEVENT_Set(APPEVENT_SAVESTATE_18, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_19:			APPEVENT_Set(APPEVENT_SAVESTATE_19, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_20:			APPEVENT_Set(APPEVENT_SAVESTATE_20, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_21:			APPEVENT_Set(APPEVENT_SAVESTATE_21, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_22:			APPEVENT_Set(APPEVENT_SAVESTATE_22, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_23:			APPEVENT_Set(APPEVENT_SAVESTATE_23, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_24:			APPEVENT_Set(APPEVENT_SAVESTATE_24, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_25:			APPEVENT_Set(APPEVENT_SAVESTATE_25, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_26:			APPEVENT_Set(APPEVENT_SAVESTATE_26, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_27:			APPEVENT_Set(APPEVENT_SAVESTATE_27, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_28:			APPEVENT_Set(APPEVENT_SAVESTATE_28, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_29:			APPEVENT_Set(APPEVENT_SAVESTATE_29, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_30:			APPEVENT_Set(APPEVENT_SAVESTATE_30, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_31:			APPEVENT_Set(APPEVENT_SAVESTATE_31, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_32:			APPEVENT_Set(APPEVENT_SAVESTATE_32, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_33:			APPEVENT_Set(APPEVENT_SAVESTATE_33, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_34:			APPEVENT_Set(APPEVENT_SAVESTATE_34, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_35:			APPEVENT_Set(APPEVENT_SAVESTATE_35, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_36:			APPEVENT_Set(APPEVENT_SAVESTATE_36, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_37:			APPEVENT_Set(APPEVENT_SAVESTATE_37, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_38:			APPEVENT_Set(APPEVENT_SAVESTATE_38, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_39:			APPEVENT_Set(APPEVENT_SAVESTATE_39, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_40:			APPEVENT_Set(APPEVENT_SAVESTATE_40, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_41:			APPEVENT_Set(APPEVENT_SAVESTATE_41, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_42:			APPEVENT_Set(APPEVENT_SAVESTATE_42, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_43:			APPEVENT_Set(APPEVENT_SAVESTATE_43, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_44:			APPEVENT_Set(APPEVENT_SAVESTATE_44, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_45:			APPEVENT_Set(APPEVENT_SAVESTATE_45, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_46:			APPEVENT_Set(APPEVENT_SAVESTATE_46, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_47:			APPEVENT_Set(APPEVENT_SAVESTATE_47, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_48:			APPEVENT_Set(APPEVENT_SAVESTATE_48, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_49:			APPEVENT_Set(APPEVENT_SAVESTATE_49, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_STATE_50:			APPEVENT_Set(APPEVENT_SAVESTATE_50, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE:				APPEVENT_Set(APPEVENT_LOADSTATE, NULL);				break;
		case WM_LOAD_STATE_P:			APPEVENT_Set(APPEVENT_LOADSTATE_P, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_1:			APPEVENT_Set(APPEVENT_LOADSTATE_1, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_2:			APPEVENT_Set(APPEVENT_LOADSTATE_2, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_3:			APPEVENT_Set(APPEVENT_LOADSTATE_3, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_4:			APPEVENT_Set(APPEVENT_LOADSTATE_4, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_5:			APPEVENT_Set(APPEVENT_LOADSTATE_5, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_6:			APPEVENT_Set(APPEVENT_LOADSTATE_6, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_7:			APPEVENT_Set(APPEVENT_LOADSTATE_7, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_8:			APPEVENT_Set(APPEVENT_LOADSTATE_8, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_9:			APPEVENT_Set(APPEVENT_LOADSTATE_9, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_10:			APPEVENT_Set(APPEVENT_LOADSTATE_10, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_11:			APPEVENT_Set(APPEVENT_LOADSTATE_11, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_12:			APPEVENT_Set(APPEVENT_LOADSTATE_12, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_13:			APPEVENT_Set(APPEVENT_LOADSTATE_13, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_14:			APPEVENT_Set(APPEVENT_LOADSTATE_14, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_15:			APPEVENT_Set(APPEVENT_LOADSTATE_15, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_16:			APPEVENT_Set(APPEVENT_LOADSTATE_16, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_17:			APPEVENT_Set(APPEVENT_LOADSTATE_17, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_18:			APPEVENT_Set(APPEVENT_LOADSTATE_18, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_19:			APPEVENT_Set(APPEVENT_LOADSTATE_19, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_20:			APPEVENT_Set(APPEVENT_LOADSTATE_20, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_21:			APPEVENT_Set(APPEVENT_LOADSTATE_21, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_22:			APPEVENT_Set(APPEVENT_LOADSTATE_22, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_23:			APPEVENT_Set(APPEVENT_LOADSTATE_23, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_24:			APPEVENT_Set(APPEVENT_LOADSTATE_24, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_25:			APPEVENT_Set(APPEVENT_LOADSTATE_25, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_26:			APPEVENT_Set(APPEVENT_LOADSTATE_26, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_27:			APPEVENT_Set(APPEVENT_LOADSTATE_27, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_28:			APPEVENT_Set(APPEVENT_LOADSTATE_28, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_29:			APPEVENT_Set(APPEVENT_LOADSTATE_29, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_30:			APPEVENT_Set(APPEVENT_LOADSTATE_30, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_31:			APPEVENT_Set(APPEVENT_LOADSTATE_31, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_32:			APPEVENT_Set(APPEVENT_LOADSTATE_32, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_33:			APPEVENT_Set(APPEVENT_LOADSTATE_33, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_34:			APPEVENT_Set(APPEVENT_LOADSTATE_34, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_35:			APPEVENT_Set(APPEVENT_LOADSTATE_35, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_36:			APPEVENT_Set(APPEVENT_LOADSTATE_36, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_37:			APPEVENT_Set(APPEVENT_LOADSTATE_37, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_38:			APPEVENT_Set(APPEVENT_LOADSTATE_38, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_39:			APPEVENT_Set(APPEVENT_LOADSTATE_39, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_40:			APPEVENT_Set(APPEVENT_LOADSTATE_40, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_41:			APPEVENT_Set(APPEVENT_LOADSTATE_41, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_42:			APPEVENT_Set(APPEVENT_LOADSTATE_42, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_43:			APPEVENT_Set(APPEVENT_LOADSTATE_43, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_44:			APPEVENT_Set(APPEVENT_LOADSTATE_44, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_45:			APPEVENT_Set(APPEVENT_LOADSTATE_45, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_46:			APPEVENT_Set(APPEVENT_LOADSTATE_46, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_47:			APPEVENT_Set(APPEVENT_LOADSTATE_47, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_48:			APPEVENT_Set(APPEVENT_LOADSTATE_48, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_49:			APPEVENT_Set(APPEVENT_LOADSTATE_49, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_STATE_50:			APPEVENT_Set(APPEVENT_LOADSTATE_50, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_BUTTON:			APPEVENT_Set(APPEVENT_SAVE_BUTTON, NULL);			break;//Kitao�ǉ�
		case WM_LOAD_BUTTON:			APPEVENT_Set(APPEVENT_LOAD_BUTTON, NULL);			break;//Kitao�ǉ�
		case WM_SAVE_DEFAULT:			APPEVENT_Set(APPEVENT_SAVE_DEFAULT, NULL);			break;//Kitao�ǉ�
		case WM_FOLDER_STATE:			APPEVENT_Set(APPEVENT_FOLDER_STATE, NULL);			break;//Kitao�ǉ�
		case WM_RECORDING_GAMEPLAY:		APPEVENT_Set(APPEVENT_RECORDING, NULL);				break;
		case WM_PLAYRECORD_GAMEPLAY:	APPEVENT_Set(APPEVENT_PLAYRECORD, NULL);			break;
		case WM_RECORDING_1:			APPEVENT_Set(APPEVENT_RECORDING_1, NULL);			break;//Kitao�ǉ�
		case WM_RECORDING_2:			APPEVENT_Set(APPEVENT_RECORDING_2, NULL);			break;//Kitao�ǉ�
		case WM_RECORDING_3:			APPEVENT_Set(APPEVENT_RECORDING_3, NULL);			break;//Kitao�ǉ�
		case WM_RECORDING_4:			APPEVENT_Set(APPEVENT_RECORDING_4, NULL);			break;//Kitao�ǉ�
		case WM_RECORDING_5:			APPEVENT_Set(APPEVENT_RECORDING_5, NULL);			break;//Kitao�ǉ�
		case WM_RECORDING_6:			APPEVENT_Set(APPEVENT_RECORDING_6, NULL);			break;//Kitao�ǉ�
		case WM_RECORDING_7:			APPEVENT_Set(APPEVENT_RECORDING_7, NULL);			break;//Kitao�ǉ�
		case WM_RECORDING_8:			APPEVENT_Set(APPEVENT_RECORDING_8, NULL);			break;//Kitao�ǉ�
		case WM_RECORDING_9:			APPEVENT_Set(APPEVENT_RECORDING_9, NULL);			break;//Kitao�ǉ�
		case WM_RECORDING_10:			APPEVENT_Set(APPEVENT_RECORDING_10, NULL);			break;//Kitao�ǉ�
		case WM_RECORDING_HELP:			APPEVENT_Set(APPEVENT_RECORDING_HELP, NULL);		break;//Kitao�ǉ�
		case WM_PLAYRECORD_1:			APPEVENT_Set(APPEVENT_PLAYRECORD_1, NULL);			break;//Kitao�ǉ�
		case WM_PLAYRECORD_2:			APPEVENT_Set(APPEVENT_PLAYRECORD_2, NULL);			break;//Kitao�ǉ�
		case WM_PLAYRECORD_3:			APPEVENT_Set(APPEVENT_PLAYRECORD_3, NULL);			break;//Kitao�ǉ�
		case WM_PLAYRECORD_4:			APPEVENT_Set(APPEVENT_PLAYRECORD_4, NULL);			break;//Kitao�ǉ�
		case WM_PLAYRECORD_5:			APPEVENT_Set(APPEVENT_PLAYRECORD_5, NULL);			break;//Kitao�ǉ�
		case WM_PLAYRECORD_6:			APPEVENT_Set(APPEVENT_PLAYRECORD_6, NULL);			break;//Kitao�ǉ�
		case WM_PLAYRECORD_7:			APPEVENT_Set(APPEVENT_PLAYRECORD_7, NULL);			break;//Kitao�ǉ�
		case WM_PLAYRECORD_8:			APPEVENT_Set(APPEVENT_PLAYRECORD_8, NULL);			break;//Kitao�ǉ�
		case WM_PLAYRECORD_9:			APPEVENT_Set(APPEVENT_PLAYRECORD_9, NULL);			break;//Kitao�ǉ�
		case WM_PLAYRECORD_10:			APPEVENT_Set(APPEVENT_PLAYRECORD_10, NULL);			break;//Kitao�ǉ�
		case WM_MOVERECORD_1:			APPEVENT_Set(APPEVENT_MOVERECORD_1, NULL);			break;//Kitao�ǉ�
		case WM_MOVERECORD_2:			APPEVENT_Set(APPEVENT_MOVERECORD_2, NULL);			break;//Kitao�ǉ�
		case WM_MOVERECORD_3:			APPEVENT_Set(APPEVENT_MOVERECORD_3, NULL);			break;//Kitao�ǉ�
		case WM_MOVERECORD_4:			APPEVENT_Set(APPEVENT_MOVERECORD_4, NULL);			break;//Kitao�ǉ�
		case WM_MOVERECORD_5:			APPEVENT_Set(APPEVENT_MOVERECORD_5, NULL);			break;//Kitao�ǉ�
		case WM_MOVERECORD_6:			APPEVENT_Set(APPEVENT_MOVERECORD_6, NULL);			break;//Kitao�ǉ�
		case WM_MOVERECORD_7:			APPEVENT_Set(APPEVENT_MOVERECORD_7, NULL);			break;//Kitao�ǉ�
		case WM_MOVERECORD_8:			APPEVENT_Set(APPEVENT_MOVERECORD_8, NULL);			break;//Kitao�ǉ�
		case WM_MOVERECORD_9:			APPEVENT_Set(APPEVENT_MOVERECORD_9, NULL);			break;//Kitao�ǉ�
		case WM_MOVERECORD_10:			APPEVENT_Set(APPEVENT_MOVERECORD_10, NULL);			break;//Kitao�ǉ�
		case WM_FOLDER_GAMEPLAY:		APPEVENT_Set(APPEVENT_FOLDER_GAMEPLAY, NULL);		break;//Kitao�ǉ�
		case WM_FOLDER_BRAM:			APPEVENT_Set(APPEVENT_FOLDER_BRAM, NULL);			break;//Kitao�ǉ�
		case WM_FOLDER_MB128:			APPEVENT_Set(APPEVENT_FOLDER_MB128, NULL);			break;//Kitao�ǉ�
		case WM_TRACE_1_FRAME:			APPEVENT_Set(APPEVENT_ADVANCEFRAME_1, NULL);		break;
		case WM_TRACE_10_FRAME:			APPEVENT_Set(APPEVENT_ADVANCEFRAME_10, NULL);		break;
		case WM_TRACE_100_FRAME:		APPEVENT_Set(APPEVENT_ADVANCEFRAME_100, NULL);		break;
		case WM_WRITE_MEMORY:			APPEVENT_Set(APPEVENT_WRITE_MEMORY, NULL);			break;//Kitao�ǉ�
		case WM_ABOUT_WRITEMEM:			APPEVENT_Set(APPEVENT_ABOUT_WRITEMEM, NULL);		break;//Kitao�ǉ�

		case WM_RECENT_1:				APPEVENT_Set(APPEVENT_RECENT_1, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_2:				APPEVENT_Set(APPEVENT_RECENT_2, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_3:				APPEVENT_Set(APPEVENT_RECENT_3, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_4:				APPEVENT_Set(APPEVENT_RECENT_4, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_5:				APPEVENT_Set(APPEVENT_RECENT_5, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_6:				APPEVENT_Set(APPEVENT_RECENT_6, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_7:				APPEVENT_Set(APPEVENT_RECENT_7, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_8:				APPEVENT_Set(APPEVENT_RECENT_8, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_9:				APPEVENT_Set(APPEVENT_RECENT_9, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_10:				APPEVENT_Set(APPEVENT_RECENT_10, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_11:				APPEVENT_Set(APPEVENT_RECENT_11, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_12:				APPEVENT_Set(APPEVENT_RECENT_12, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_13:				APPEVENT_Set(APPEVENT_RECENT_13, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_14:				APPEVENT_Set(APPEVENT_RECENT_14, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_15:				APPEVENT_Set(APPEVENT_RECENT_15, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_16:				APPEVENT_Set(APPEVENT_RECENT_16, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_17:				APPEVENT_Set(APPEVENT_RECENT_17, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_18:				APPEVENT_Set(APPEVENT_RECENT_18, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_19:				APPEVENT_Set(APPEVENT_RECENT_19, NULL);				break;//Kitao�ǉ�
		case WM_RECENT_20:				APPEVENT_Set(APPEVENT_RECENT_20, NULL);				break;//Kitao�ǉ�

		case WM_SCREEN_CS:				APPEVENT_Set(APPEVENT_SCREEN_CS, NULL);				break;//Kitao�ǉ�
		case WM_SCREEN_X1:				APPEVENT_Set(APPEVENT_SCREEN_X1, NULL);				break;
		case WM_SCREEN_X2:				APPEVENT_Set(APPEVENT_SCREEN_X2, NULL);				break;
		case WM_SCREEN_X3:				APPEVENT_Set(APPEVENT_SCREEN_X3, NULL);				break;
		case WM_SCREEN_X4:				APPEVENT_Set(APPEVENT_SCREEN_X4, NULL);				break;
		case WM_SCREEN_F1:				APPEVENT_Set(APPEVENT_SCREEN_F1, NULL);				break;//Kitao�ǉ�
		case WM_SCREEN_F2:				APPEVENT_Set(APPEVENT_SCREEN_F2, NULL);				break;//Kitao�ǉ�
		case WM_SCREEN_DISABLEAERO:		APPEVENT_Set(APPEVENT_SCREEN_DISABLEAERO, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_USEAERO:			APPEVENT_Set(APPEVENT_SCREEN_USEAERO, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_GAMMA1:			APPEVENT_Set(APPEVENT_SCREEN_GAMMA1, NULL);			break;//Kitao�ǉ�
		case WM_SCREEN_GAMMA2:			APPEVENT_Set(APPEVENT_SCREEN_GAMMA2, NULL);			break;//Kitao�ǉ�
		case WM_SCREEN_GAMMA3:			APPEVENT_Set(APPEVENT_SCREEN_GAMMA3, NULL);			break;//Kitao�ǉ�
		case WM_SCREEN_GAMMA4:			APPEVENT_Set(APPEVENT_SCREEN_GAMMA4, NULL);			break;//Kitao�ǉ�
		case WM_SCREEN_GAMMA5:			APPEVENT_Set(APPEVENT_SCREEN_GAMMA5, NULL);			break;//Kitao�ǉ�
		case WM_SCREEN_GAMMA6:			APPEVENT_Set(APPEVENT_SCREEN_GAMMA6, NULL);			break;//Kitao�ǉ�
		case WM_SCREEN_GAMMA7:			APPEVENT_Set(APPEVENT_SCREEN_GAMMA7, NULL);			break;//Kitao�ǉ�
		case WM_SCREEN_BRIGHT1:			APPEVENT_Set(APPEVENT_SCREEN_BRIGHT1, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_BRIGHT2:			APPEVENT_Set(APPEVENT_SCREEN_BRIGHT2, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_BRIGHT3:			APPEVENT_Set(APPEVENT_SCREEN_BRIGHT3, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_BRIGHT4:			APPEVENT_Set(APPEVENT_SCREEN_BRIGHT4, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_BRIGHT5:			APPEVENT_Set(APPEVENT_SCREEN_BRIGHT5, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_BRIGHT6:			APPEVENT_Set(APPEVENT_SCREEN_BRIGHT6, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_BRIGHT7:			APPEVENT_Set(APPEVENT_SCREEN_BRIGHT7, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_BRIGHT8:			APPEVENT_Set(APPEVENT_SCREEN_BRIGHT8, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_BRIGHT9:			APPEVENT_Set(APPEVENT_SCREEN_BRIGHT9, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_MINIMIZE:		APPEVENT_Set(APPEVENT_SCREEN_MINIMIZE, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_NONSTRETCHED:	APPEVENT_Set(APPEVENT_SCREEN_NONSTRETCHED, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_STRETCHED:		APPEVENT_Set(APPEVENT_SCREEN_STRETCHED, NULL);		break;
		case WM_SCREEN_FULLSTRETCHED:	APPEVENT_Set(APPEVENT_SCREEN_FULLSTRETCHED, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_VERTICAL:		APPEVENT_Set(APPEVENT_SCREEN_VERTICAL, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_MONOCOLOR:		APPEVENT_Set(APPEVENT_SCREEN_MONOCOLOR, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_SHOWOVERSCAN:	APPEVENT_Set(APPEVENT_SCREEN_SHOWOVERSCAN, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_OVERTB:			APPEVENT_Set(APPEVENT_SCREEN_OVERTB, NULL);			break;//Kitao�ǉ�
		case WM_SCREEN_OVERTOP:			APPEVENT_Set(APPEVENT_SCREEN_OVERTOP, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_OVERBOTTOM:		APPEVENT_Set(APPEVENT_SCREEN_OVERBOTTOM, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_OVERNONETB:		APPEVENT_Set(APPEVENT_SCREEN_OVERNONETB, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_OVERHEIGHT8:		APPEVENT_Set(APPEVENT_SCREEN_OVERHEIGHT8, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_OVERHEIGHT7:		APPEVENT_Set(APPEVENT_SCREEN_OVERHEIGHT7, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_OVERHEIGHT6:		APPEVENT_Set(APPEVENT_SCREEN_OVERHEIGHT6, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_OVERHEIGHT4:		APPEVENT_Set(APPEVENT_SCREEN_OVERHEIGHT4, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_OVERHEIGHT2:		APPEVENT_Set(APPEVENT_SCREEN_OVERHEIGHT2, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_OVERHEIGHT1:		APPEVENT_Set(APPEVENT_SCREEN_OVERHEIGHT1, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_OVERLR:			APPEVENT_Set(APPEVENT_SCREEN_OVERLR, NULL);			break;//Kitao�ǉ�
		case WM_SCREEN_OVERNONELR:		APPEVENT_Set(APPEVENT_SCREEN_OVERNONELR, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_OVERSTART:		APPEVENT_Set(APPEVENT_SCREEN_OVERSTART, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_OVERBLACK:		APPEVENT_Set(APPEVENT_SCREEN_OVERBLACK, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_SOVERTB:			APPEVENT_Set(APPEVENT_SCREEN_SOVERTB, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_SOVERTOP:		APPEVENT_Set(APPEVENT_SCREEN_SOVERTOP, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_SOVERBOTTOM:		APPEVENT_Set(APPEVENT_SCREEN_SOVERBOTTOM, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SOVERNONETB:		APPEVENT_Set(APPEVENT_SCREEN_SOVERNONETB, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SOVERHEIGHT8:	APPEVENT_Set(APPEVENT_SCREEN_SOVERHEIGHT8, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SOVERHEIGHT7:	APPEVENT_Set(APPEVENT_SCREEN_SOVERHEIGHT7, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SOVERHEIGHT6:	APPEVENT_Set(APPEVENT_SCREEN_SOVERHEIGHT6, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SOVERHEIGHT4:	APPEVENT_Set(APPEVENT_SCREEN_SOVERHEIGHT4, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SOVERHEIGHT2:	APPEVENT_Set(APPEVENT_SCREEN_SOVERHEIGHT2, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SOVERHEIGHT1:	APPEVENT_Set(APPEVENT_SCREEN_SOVERHEIGHT1, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SOVERLR:			APPEVENT_Set(APPEVENT_SCREEN_SOVERLR, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_SOVERNONELR:		APPEVENT_Set(APPEVENT_SCREEN_SOVERNONELR, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_FULLSCREEN:		APPEVENT_Set(APPEVENT_SCREEN_FULLSCREEN, NULL);		break;
		case WM_SCREEN_FULLSCREEN640:	APPEVENT_Set(APPEVENT_SCREEN_FULLSCREEN640, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_FULLSCREENCS1:	APPEVENT_Set(APPEVENT_SCREEN_FULLSCREENCS1, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_FULLSCREENCS2:	APPEVENT_Set(APPEVENT_SCREEN_FULLSCREENCS2, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_FULLSCREENCS3:	APPEVENT_Set(APPEVENT_SCREEN_FULLSCREENCS3, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_FULLSCREENCSA:	APPEVENT_Set(APPEVENT_SCREEN_FULLSCREENCSA, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SPSCANLINED:		APPEVENT_Set(APPEVENT_SCREEN_SPSCANLINED, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_HRSCANLINEDTV:	APPEVENT_Set(APPEVENT_SCREEN_HRSCANLINEDTV, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_HRSCANLINED:		APPEVENT_Set(APPEVENT_SCREEN_HRSCANLINED, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_HRSCANLINED2:	APPEVENT_Set(APPEVENT_SCREEN_HRSCANLINED2, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_HRSCANLINED3:	APPEVENT_Set(APPEVENT_SCREEN_HRSCANLINED3, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_HRSCANLINEDF:	APPEVENT_Set(APPEVENT_SCREEN_HRSCANLINEDF, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_NONSCANLINED:	APPEVENT_Set(APPEVENT_SCREEN_NONSCANLINED, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_NONSCANLINED2:	APPEVENT_Set(APPEVENT_SCREEN_NONSCANLINED2, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_NONSCANLINEDTV:	APPEVENT_Set(APPEVENT_SCREEN_NONSCANLINEDTV, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SCANDENSITY0:	APPEVENT_Set(APPEVENT_SCREEN_SCANDENSITY0, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SCANDENSITY10:	APPEVENT_Set(APPEVENT_SCREEN_SCANDENSITY10, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SCANDENSITY20:	APPEVENT_Set(APPEVENT_SCREEN_SCANDENSITY20, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SCANDENSITY30:	APPEVENT_Set(APPEVENT_SCREEN_SCANDENSITY30, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SCANDENSITY40:	APPEVENT_Set(APPEVENT_SCREEN_SCANDENSITY40, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SCANDENSITY50:	APPEVENT_Set(APPEVENT_SCREEN_SCANDENSITY50, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SCANDENSITY60:	APPEVENT_Set(APPEVENT_SCREEN_SCANDENSITY60, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SCANDENSITY70:	APPEVENT_Set(APPEVENT_SCREEN_SCANDENSITY70, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SCANDENSITY80:	APPEVENT_Set(APPEVENT_SCREEN_SCANDENSITY80, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_SCANGAMMA:		APPEVENT_Set(APPEVENT_SCREEN_SCANGAMMA, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_SYNC_VBLANK:		APPEVENT_Set(APPEVENT_SCREEN_SYNC_VBLANK, NULL);	break;
		case WM_SCREEN_SYNC_WINDOWS:	APPEVENT_Set(APPEVENT_SCREEN_SYNC_WINDOWS, NULL);	break;//Kitao�ǉ��Bv2.65
		case WM_SCREEN_SYNC_WINDOWSF:	APPEVENT_Set(APPEVENT_SCREEN_SYNC_WINDOWSF, NULL);	break;//Kitao�ǉ��Bv2.65
		case WM_SCREEN_SYNC_NON:		APPEVENT_Set(APPEVENT_SCREEN_SYNC_NON, NULL);		break;//Kitao�ǉ��Bv2.65
		case WM_SCREEN_SYNC_ADJUST:		APPEVENT_Set(APPEVENT_SCREEN_SYNC_ADJUST, NULL);	break;//Kitao�ǉ��Bv2.65
		case WM_SCREEN_DIRECT3D:		APPEVENT_Set(APPEVENT_SCREEN_DIRECT3D, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_DIRECTDRAW:		APPEVENT_Set(APPEVENT_SCREEN_DIRECTDRAW, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_USE_VIDEOMEM:	APPEVENT_Set(APPEVENT_SCREEN_USE_VIDEOMEM, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_USE_SYSTEMMEM:	APPEVENT_Set(APPEVENT_SCREEN_USE_SYSTEMMEM, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_USE_SYSTEMMEMW:	APPEVENT_Set(APPEVENT_SCREEN_USE_SYSTEMMEMW, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_FULL16BITCOLOR:	APPEVENT_Set(APPEVENT_SCREEN_FULL16BITCOLOR, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_FULL32BITCOLOR:	APPEVENT_Set(APPEVENT_SCREEN_FULL32BITCOLOR, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_STARTWINDOW:		APPEVENT_Set(APPEVENT_SCREEN_STARTWINDOW, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_STARTFULL:		APPEVENT_Set(APPEVENT_SCREEN_STARTFULL, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_TOPMOST:			APPEVENT_Set(APPEVENT_SCREEN_TOPMOST, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_ACTIVATE:		APPEVENT_Set(APPEVENT_SCREEN_ACTIVATE, NULL);		break;//Kitao�ǉ�
		case WM_SCREEN_NONACTIVATE:		APPEVENT_Set(APPEVENT_SCREEN_NONACTIVATE, NULL);	break;//Kitao�ǉ�
		case WM_SCREEN_UNPAUSE:			APPEVENT_Set(APPEVENT_SCREEN_UNPAUSE, NULL);		break;//v2.26�ǉ�

		case WM_INPUT_TURBO_1:			APPEVENT_Set(APPEVENT_INPUT_TURBO_1, NULL);			break;//Kitao�ǉ�
		case WM_INPUT_TURBO_2:			APPEVENT_Set(APPEVENT_INPUT_TURBO_2, NULL);			break;//Kitao�ǉ�
		case WM_INPUT_TURBO_RUN:		APPEVENT_Set(APPEVENT_INPUT_TURBO_RUN, NULL);		break;//Kitao�ǉ�
		case WM_INPUT_TURBO_HIGH:		APPEVENT_Set(APPEVENT_INPUT_TURBO_HIGH, NULL);		break;//Kitao�ǉ�
		case WM_INPUT_TURBO_MIDDLE:		APPEVENT_Set(APPEVENT_INPUT_TURBO_MIDDLE, NULL);	break;//Kitao�ǉ�
		case WM_INPUT_TURBO_LOW:		APPEVENT_Set(APPEVENT_INPUT_TURBO_LOW, NULL);		break;//Kitao�ǉ�
		case WM_INPUT_TURBO_OFF:		APPEVENT_Set(APPEVENT_INPUT_TURBO_OFF, NULL);		break;//Kitao�ǉ�
		case WM_INPUT_TWO_BUTTON_PAD:	APPEVENT_Set(APPEVENT_INPUT_TWO_BUTTON_PAD, NULL);	break;
		case WM_INPUT_THR_BUTTON_PAD:	APPEVENT_Set(APPEVENT_INPUT_THR_BUTTON_PAD, NULL);	break;//Kitao�ǉ�
		case WM_INPUT_SIX_BUTTON_PAD:	APPEVENT_Set(APPEVENT_INPUT_SIX_BUTTON_PAD, NULL);	break;
		case WM_INPUT_MOUSE:			APPEVENT_Set(APPEVENT_INPUT_MOUSE, NULL);			break;
		case WM_INPUT_MULTI_TAP:		APPEVENT_Set(APPEVENT_INPUT_MULTI_TAP, NULL);		break;
		case WM_INPUT_MB128:			APPEVENT_Set(APPEVENT_INPUT_MB128, NULL);			break;
		case WM_INPUT_SWAP_SELRUN:		APPEVENT_Set(APPEVENT_INPUT_SWAP_SELRUN, NULL);		break;//Kitao�ǉ�
		case WM_INPUT_SWAP_IANDII:		APPEVENT_Set(APPEVENT_INPUT_SWAP_IANDII, NULL);		break;//Kitao�ǉ�
		case WM_INPUT_CHECKPAD_LR:		APPEVENT_Set(APPEVENT_INPUT_CHECKPAD_LR, NULL);		break;//Kitao�ǉ�

		case WM_INPUT_CONFIGURE_PAD1:	APPEVENT_Set(APPEVENT_INPUT_CONFIGURE_PAD1, NULL);	break;
		case WM_INPUT_CONFIGURE_PAD2:	APPEVENT_Set(APPEVENT_INPUT_CONFIGURE_PAD2, NULL);	break;
		case WM_INPUT_CONFIGURE_PAD3:	APPEVENT_Set(APPEVENT_INPUT_CONFIGURE_PAD3, NULL);	break;
		case WM_INPUT_CONFIGURE_PAD4:	APPEVENT_Set(APPEVENT_INPUT_CONFIGURE_PAD4, NULL);	break;
		case WM_INPUT_CONFIGURE_PAD5:	APPEVENT_Set(APPEVENT_INPUT_CONFIGURE_PAD5, NULL);	break;
		case WM_INPUT_CONFIGURE_TB1:	APPEVENT_Set(APPEVENT_INPUT_CONFIGURE_TB1, NULL);	break;//Kitao�ǉ�
		case WM_INPUT_CONFIGURE_TB2:	APPEVENT_Set(APPEVENT_INPUT_CONFIGURE_TB2, NULL);	break;//Kitao�ǉ�
		case WM_INPUT_CONFIGURE_TB3:	APPEVENT_Set(APPEVENT_INPUT_CONFIGURE_TB3, NULL);	break;//Kitao�ǉ�
		case WM_INPUT_CONFIGURE_TB4:	APPEVENT_Set(APPEVENT_INPUT_CONFIGURE_TB4, NULL);	break;//Kitao�ǉ�
		case WM_INPUT_CONFIGURE_TB5:	APPEVENT_Set(APPEVENT_INPUT_CONFIGURE_TB5, NULL);	break;//Kitao�ǉ�
		case WM_INPUT_CONFIGURE_INIT:	APPEVENT_Set(APPEVENT_INPUT_CONFIGURE_INIT, NULL);	break;//Kitao�ǉ�
		case WM_INPUT_CONFIGURE_KEYBG:	APPEVENT_Set(APPEVENT_INPUT_CONFIGURE_KEYBG, NULL);	break;//Kitao�ǉ�
		case WM_INPUT_CONFIGURE_JOYBG:	APPEVENT_Set(APPEVENT_INPUT_CONFIGURE_JOYBG, NULL);	break;//Kitao�ǉ�
		case WM_INPUT_FUNCTION:			APPEVENT_Set(APPEVENT_INPUT_FUNCTION, NULL);		break;//Kitao�ǉ�
		case WM_INPUT_FB_CURSOR:		APPEVENT_Set(APPEVENT_INPUT_FB_CURSOR, NULL);		break;//Kitao�ǉ�
		case WM_INPUT_FB_IandII:		APPEVENT_Set(APPEVENT_INPUT_FB_IandII, NULL);		break;//Kitao�ǉ�
		case WM_INPUT_FB_SEL:			APPEVENT_Set(APPEVENT_INPUT_FB_SEL, NULL);			break;//Kitao�ǉ�
		case WM_INPUT_FB_RUN:			APPEVENT_Set(APPEVENT_INPUT_FB_RUN, NULL);			break;//Kitao�ǉ�
		case WM_INPUT_FB_VSPEEDUP:		APPEVENT_Set(APPEVENT_INPUT_FB_VSPEEDUP, NULL);		break;//Kitao�ǉ�
		case WM_INPUT_FB_SAVELOAD:		APPEVENT_Set(APPEVENT_INPUT_FB_SAVELOAD, NULL);		break;//Kitao�ǉ�

/*		case WM_AUDIO_SR96000:			APPEVENT_Set(APPEVENT_AUDIO_SR96000, NULL);			break;
		case WM_AUDIO_SR88200:			APPEVENT_Set(APPEVENT_AUDIO_SR88200, NULL);			break;
		case WM_AUDIO_SR64000:			APPEVENT_Set(APPEVENT_AUDIO_SR64000, NULL);			break;
		case WM_AUDIO_SR48000:			APPEVENT_Set(APPEVENT_AUDIO_SR48000, NULL);			break;
		case WM_AUDIO_SR44100:			APPEVENT_Set(APPEVENT_AUDIO_SR44100, NULL);			break;
		case WM_AUDIO_SR32000:			APPEVENT_Set(APPEVENT_AUDIO_SR32000, NULL);			break;
		case WM_AUDIO_SR22050:			APPEVENT_Set(APPEVENT_AUDIO_SR22050, NULL);			break;
		case WM_AUDIO_SR11025:			APPEVENT_Set(APPEVENT_AUDIO_SR11025, NULL);			break;
*/
		case WM_AUDIO_SB1024:			APPEVENT_Set(APPEVENT_AUDIO_SB1024, NULL);			break;
		case WM_AUDIO_SB1152:			APPEVENT_Set(APPEVENT_AUDIO_SB1152, NULL);			break;//v2.37�ǉ�
		case WM_AUDIO_SB1280:			APPEVENT_Set(APPEVENT_AUDIO_SB1280, NULL);			break;
		case WM_AUDIO_SB1408:			APPEVENT_Set(APPEVENT_AUDIO_SB1408, NULL);			break;//v2.37�ǉ�
		case WM_AUDIO_SB1536:			APPEVENT_Set(APPEVENT_AUDIO_SB1536, NULL);			break;
		case WM_AUDIO_SB1664:			APPEVENT_Set(APPEVENT_AUDIO_SB1664, NULL);			break;//v1.28�ǉ�
		case WM_AUDIO_SB1792:			APPEVENT_Set(APPEVENT_AUDIO_SB1792, NULL);			break;
		case WM_AUDIO_SB2048:			APPEVENT_Set(APPEVENT_AUDIO_SB2048, NULL);			break;
		case WM_AUDIO_SB2176:			APPEVENT_Set(APPEVENT_AUDIO_SB2176, NULL);			break;//v2.20�ǉ�
		case WM_AUDIO_SB2304:			APPEVENT_Set(APPEVENT_AUDIO_SB2304, NULL);			break;
		case WM_AUDIO_SB2560:			APPEVENT_Set(APPEVENT_AUDIO_SB2560, NULL);			break;
		case WM_AUDIO_SB3072:			APPEVENT_Set(APPEVENT_AUDIO_SB3072, NULL);			break;
		case WM_AUDIO_HQPSG1:			APPEVENT_Set(APPEVENT_AUDIO_HQPSG1, NULL);			break;//v1.39�ǉ�
		case WM_AUDIO_HQPSG2:			APPEVENT_Set(APPEVENT_AUDIO_HQPSG2, NULL);			break;//v1.39�ǉ�
		case WM_AUDIO_HQPSG3:			APPEVENT_Set(APPEVENT_AUDIO_HQPSG3, NULL);			break;//v1.39�ǉ�

		case WM_AUDIO_STEREO:			APPEVENT_Set(APPEVENT_AUDIO_STEREO, NULL);			break;//Kitao�ǉ�
		case WM_AUDIO_MONO:				APPEVENT_Set(APPEVENT_AUDIO_MONO, NULL);			break;//Kitao�ǉ�

		case WM_AUDIO_METHOD7SC:		APPEVENT_Set(APPEVENT_AUDIO_METHOD7SC, NULL);		break;//Kitao�ǉ�
		case WM_AUDIO_METHOD7SM:		APPEVENT_Set(APPEVENT_AUDIO_METHOD7SM, NULL);		break;//Kitao�ǉ�
		case WM_AUDIO_METHOD9SC:		APPEVENT_Set(APPEVENT_AUDIO_METHOD9SC, NULL);		break;//Kitao�ǉ�
		case WM_AUDIO_METHOD9SM:		APPEVENT_Set(APPEVENT_AUDIO_METHOD9SM, NULL);		break;//Kitao�ǉ�
		case WM_AUDIO_METHOD20:			APPEVENT_Set(APPEVENT_AUDIO_METHOD20, NULL);		break;//Kitao�ǉ�

		case WM_AUDIO_NORMALBUFFER:		APPEVENT_Set(APPEVENT_AUDIO_NORMALBUFFER, NULL);	break;//Kitao�ǉ�
		case WM_AUDIO_BIGBUFFER:		APPEVENT_Set(APPEVENT_AUDIO_BIGBUFFER, NULL);		break;//Kitao�ǉ�
		case WM_AUDIO_MOSTBUFFER:		APPEVENT_Set(APPEVENT_AUDIO_MOSTBUFFER, NULL);		break;//Kitao�ǉ�

		case WM_AUDIO_CDDAAUTO:			APPEVENT_Set(APPEVENT_AUDIO_CDDAAUTO, NULL);		break;//Kitao�ǉ�
		case WM_AUDIO_CDDA593:			APPEVENT_Set(APPEVENT_AUDIO_CDDA593, NULL);			break;//Kitao�ǉ�
		case WM_AUDIO_CDDA594:			APPEVENT_Set(APPEVENT_AUDIO_CDDA594, NULL);			break;//Kitao�ǉ�
		case WM_AUDIO_CDDA595:			APPEVENT_Set(APPEVENT_AUDIO_CDDA595, NULL);			break;//Kitao�ǉ�
		case WM_AUDIO_CDDA596:			APPEVENT_Set(APPEVENT_AUDIO_CDDA596, NULL);			break;//Kitao�ǉ�
		case WM_AUDIO_CDDA597:			APPEVENT_Set(APPEVENT_AUDIO_CDDA597, NULL);			break;//Kitao�ǉ�
		case WM_AUDIO_CDDA598:			APPEVENT_Set(APPEVENT_AUDIO_CDDA598, NULL);			break;//Kitao�ǉ�
		case WM_AUDIO_CDDA599:			APPEVENT_Set(APPEVENT_AUDIO_CDDA599, NULL);			break;//Kitao�ǉ�
		case WM_AUDIO_CDDA600:			APPEVENT_Set(APPEVENT_AUDIO_CDDA600, NULL);			break;//Kitao�ǉ�
		case WM_AUDIO_CDDA601:			APPEVENT_Set(APPEVENT_AUDIO_CDDA601, NULL);			break;//Kitao�ǉ�
		case WM_AUDIO_CDDA602:			APPEVENT_Set(APPEVENT_AUDIO_CDDA602, NULL);			break;//Kitao�ǉ�
		case WM_AUDIO_CDDAP000:			APPEVENT_Set(APPEVENT_AUDIO_CDDAP000, NULL);		break;//Kitao�ǉ�
		case WM_AUDIO_CDDAP005:			APPEVENT_Set(APPEVENT_AUDIO_CDDAP005, NULL);		break;//Kitao�ǉ�
		case WM_AUDIO_SYNC_VBLANK:		APPEVENT_Set(APPEVENT_AUDIO_SYNC_VBLANK, NULL);		break;//Kitao�ǉ��Bv2.65
		case WM_AUDIO_DELAYFRAME0:		APPEVENT_Set(APPEVENT_AUDIO_DELAYFRAME0, NULL);		break;//Kitao�ǉ�
		case WM_AUDIO_DELAYFRAME1:		APPEVENT_Set(APPEVENT_AUDIO_DELAYFRAME1, NULL);		break;//Kitao�ǉ�
		case WM_AUDIO_DELAYFRAME2:		APPEVENT_Set(APPEVENT_AUDIO_DELAYFRAME2, NULL);		break;//Kitao�ǉ�
		case WM_AUDIO_DELAYFRAME3:		APPEVENT_Set(APPEVENT_AUDIO_DELAYFRAME3, NULL);		break;//Kitao�ǉ�
		case WM_AUDIO_DELAYFRAME4:		APPEVENT_Set(APPEVENT_AUDIO_DELAYFRAME4, NULL);		break;//Kitao�ǉ�

		case WM_AUDIO_SETVOLUME:		APPEVENT_Set(APPEVENT_AUDIO_SETVOLUME, NULL);		break;
		case WM_AUDIO_DEFAULTVOLUME:	APPEVENT_Set(APPEVENT_AUDIO_DEFAULTVOLUME, NULL);	break;//Kitao�ǉ�
		case WM_VOLUME_NORMAL:			APPEVENT_Set(APPEVENT_VOLUME_NORMAL, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_3QUARTERS:		APPEVENT_Set(APPEVENT_VOLUME_3QUARTERS, NULL);		break;//Kitao�ǉ�
		case WM_VOLUME_HALF:			APPEVENT_Set(APPEVENT_VOLUME_HALF, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_QUARTER:			APPEVENT_Set(APPEVENT_VOLUME_QUARTER, NULL);		break;//Kitao�ǉ�
		case WM_VOLUME_MUTE:			APPEVENT_Set(APPEVENT_VOLUME_MUTE, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_DEFAULT:			APPEVENT_Set(APPEVENT_VOLUME_DEFAULT, NULL);		break;//Kitao�ǉ�
		case WM_VOLUME_12:				APPEVENT_Set(APPEVENT_VOLUME_12, NULL);				break;//Kitao�ǉ��Bv2.62
		case WM_VOLUME_11:				APPEVENT_Set(APPEVENT_VOLUME_11, NULL);				break;//Kitao�ǉ��Bv2.62
		case WM_VOLUME_10:				APPEVENT_Set(APPEVENT_VOLUME_10, NULL);				break;//Kitao�ǉ�
		case WM_VOLUME_9:				APPEVENT_Set(APPEVENT_VOLUME_9, NULL);				break;//Kitao�ǉ�
		case WM_VOLUME_8:				APPEVENT_Set(APPEVENT_VOLUME_8, NULL);				break;//Kitao�ǉ�
		case WM_VOLUME_7:				APPEVENT_Set(APPEVENT_VOLUME_7, NULL);				break;//Kitao�ǉ�
		case WM_VOLUME_6:				APPEVENT_Set(APPEVENT_VOLUME_6, NULL);				break;//Kitao�ǉ�
		case WM_VOLUME_5:				APPEVENT_Set(APPEVENT_VOLUME_5, NULL);				break;//Kitao�ǉ�
		case WM_VOLUME_4:				APPEVENT_Set(APPEVENT_VOLUME_4, NULL);				break;//Kitao�ǉ�
		case WM_VOLUME_3:				APPEVENT_Set(APPEVENT_VOLUME_3, NULL);				break;//Kitao�ǉ�
		case WM_VOLUME_2:				APPEVENT_Set(APPEVENT_VOLUME_2, NULL);				break;//Kitao�ǉ�
		case WM_VOLUME_1:				APPEVENT_Set(APPEVENT_VOLUME_1, NULL);				break;//Kitao�ǉ�
		case WM_VOLUME_STEP10:			APPEVENT_Set(APPEVENT_VOLUME_STEP10, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_STEP8:			APPEVENT_Set(APPEVENT_VOLUME_STEP8, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_STEP6:			APPEVENT_Set(APPEVENT_VOLUME_STEP6, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_STEP5:			APPEVENT_Set(APPEVENT_VOLUME_STEP5, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_STEP4:			APPEVENT_Set(APPEVENT_VOLUME_STEP4, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_STEP3:			APPEVENT_Set(APPEVENT_VOLUME_STEP3, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_STEP2:			APPEVENT_Set(APPEVENT_VOLUME_STEP2, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_STEP1:			APPEVENT_Set(APPEVENT_VOLUME_STEP1, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_DETAILUP:		APPEVENT_Set(APPEVENT_VOLUME_DETAILUP, NULL);		break;//Kitao�ǉ�
		case WM_VOLUME_DETAILDN:		APPEVENT_Set(APPEVENT_VOLUME_DETAILDN, NULL);		break;//Kitao�ǉ�
		case WM_VOLUME_ATTENTION:		APPEVENT_Set(APPEVENT_VOLUME_ATTENTION, NULL);		break;//Kitao�ǉ�
		case WM_VOLUME_CONTROL:			APPEVENT_Set(APPEVENT_VOLUME_CONTROL, NULL);		break;//Kitao�ǉ�
		case WM_VOLUME_MUTE1:			APPEVENT_Set(APPEVENT_VOLUME_MUTE1, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_MUTE2:			APPEVENT_Set(APPEVENT_VOLUME_MUTE2, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_MUTE3:			APPEVENT_Set(APPEVENT_VOLUME_MUTE3, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_MUTE4:			APPEVENT_Set(APPEVENT_VOLUME_MUTE4, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_MUTE5:			APPEVENT_Set(APPEVENT_VOLUME_MUTE5, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_MUTE6:			APPEVENT_Set(APPEVENT_VOLUME_MUTE6, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_MUTEA:			APPEVENT_Set(APPEVENT_VOLUME_MUTEA, NULL);			break;//Kitao�ǉ�
		case WM_VOLUME_MUTEU:			APPEVENT_Set(APPEVENT_VOLUME_MUTEU, NULL);			break;//Kitao�ǉ�

		case WM_INFO_SHOWFPS:			APPEVENT_Set(APPEVENT_INFO_SHOWFPS, NULL);			break;//Kitao�ǉ�
		case WM_INFO_TESTDELAY:			APPEVENT_Set(APPEVENT_INFO_TESTDELAY, NULL);		break;//Kitao�ǉ�
		case WM_INFO_MANUENGLISH:		APPEVENT_Set(APPEVENT_INFO_MANUENGLISH, NULL);		break;//Kitao�ǉ�
		case WM_INFO_MANUJAPANESE:		APPEVENT_Set(APPEVENT_INFO_MANUJAPANESE, NULL);		break;//Kitao�ǉ�
		case WM_INFO_README:			APPEVENT_Set(APPEVENT_INFO_README, NULL);			break;//Kitao�ǉ�
		case WM_INFO_HOMEPAGE:			APPEVENT_Set(APPEVENT_INFO_HOMEPAGE, NULL);			break;//Kitao�ǉ�
		case WM_INFO_VERSION:			APPEVENT_Set(APPEVENT_INFO_VERSION, NULL);			break;//Kitao�ǉ�

		case WM_DEVICE_CD0:				APPEVENT_Set(APPEVENT_DEVICE_CD0, NULL);			break;//Kitao�ǉ�
		case WM_DEVICE_CD1:				APPEVENT_Set(APPEVENT_DEVICE_CD1, NULL);			break;//Kitao�ǉ�
		case WM_DEVICE_CD2:				APPEVENT_Set(APPEVENT_DEVICE_CD2, NULL);			break;//Kitao�ǉ�
		case WM_DEVICE_CD3:				APPEVENT_Set(APPEVENT_DEVICE_CD3, NULL);			break;//Kitao�ǉ�
		case WM_DEVICE_CD4:				APPEVENT_Set(APPEVENT_DEVICE_CD4, NULL);			break;//Kitao�ǉ�
		case WM_DEVICE_CD5:				APPEVENT_Set(APPEVENT_DEVICE_CD5, NULL);			break;//Kitao�ǉ�
		case WM_DEVICE_CD6:				APPEVENT_Set(APPEVENT_DEVICE_CD6, NULL);			break;//Kitao�ǉ�
		case WM_DEVICE_CD7:				APPEVENT_Set(APPEVENT_DEVICE_CD7, NULL);			break;//Kitao�ǉ�
		case WM_DEVICE_CD8:				APPEVENT_Set(APPEVENT_DEVICE_CD8, NULL);			break;//Kitao�ǉ�
		case WM_DEVICE_CD9:				APPEVENT_Set(APPEVENT_DEVICE_CD9, NULL);			break;//Kitao�ǉ�
		case WM_CD_PLAYINSTALL:			APPEVENT_Set(APPEVENT_CD_PLAYINSTALL, NULL);		break;//Kitao�ǉ�
		case WM_CD_INSTALL:				APPEVENT_Set(APPEVENT_CD_INSTALL, NULL);			break;//Kitao�ǉ�
		case WM_CD_FULLINSTALL:			APPEVENT_Set(APPEVENT_CD_FULLINSTALL, NULL);		break;//Kitao�ǉ�
		case WM_CD_UNINSTALL:			APPEVENT_Set(APPEVENT_CD_UNINSTALL, NULL);			break;//Kitao�ǉ�
		case WM_CD_OPENINSTALL:			APPEVENT_Set(APPEVENT_CD_OPENINSTALL, NULL);		break;//Kitao�ǉ�
		case WM_CD_SETSYSCARD:			APPEVENT_Set(APPEVENT_CD_SETSYSCARD, NULL);			break;//Kitao�ǉ�
		case WM_CD_SETSYSCARD1:			APPEVENT_Set(APPEVENT_CD_SETSYSCARD1, NULL);		break;//Kitao�ǉ�
		case WM_CD_SETSYSCARD2:			APPEVENT_Set(APPEVENT_CD_SETSYSCARD2, NULL);		break;//Kitao�ǉ�
		case WM_CD_JUUOUKI:				APPEVENT_Set(APPEVENT_CD_JUUOUKI, NULL);			break;//Kitao�ǉ�
		case WM_CD_OSYSCARD1:			APPEVENT_Set(APPEVENT_CD_OSYSCARD1, NULL);			break;//Kitao�ǉ�
		case WM_CD_OSYSCARD2:			APPEVENT_Set(APPEVENT_CD_OSYSCARD2, NULL);			break;//Kitao�ǉ�
		case WM_CD_BACKUPFULL:			APPEVENT_Set(APPEVENT_CD_BACKUPFULL, NULL);			break;//Kitao�ǉ�
		case WM_CD_ARCADECARD:			APPEVENT_Set(APPEVENT_CD_ARCADECARD, NULL);			break;//Kitao�ǉ�
		case WM_CD_HELP:				APPEVENT_Set(APPEVENT_CD_HELP, NULL);				break;//Kitao�ǉ�

		case WM_CHANGE_CDC:				APPEVENT_Set(APPEVENT_CHANGE_CDC, NULL);			break;//Kitao�ǉ�
		case WM_CHANGE_CD0:				APPEVENT_Set(APPEVENT_CHANGE_CD0, NULL);			break;//Kitao�ǉ�
		case WM_CHANGE_CD1:				APPEVENT_Set(APPEVENT_CHANGE_CD1, NULL);			break;//Kitao�ǉ�
		case WM_CHANGE_CD2:				APPEVENT_Set(APPEVENT_CHANGE_CD2, NULL);			break;//Kitao�ǉ�
		case WM_CHANGE_CD3:				APPEVENT_Set(APPEVENT_CHANGE_CD3, NULL);			break;//Kitao�ǉ�
		case WM_CHANGE_CD4:				APPEVENT_Set(APPEVENT_CHANGE_CD4, NULL);			break;//Kitao�ǉ�
		case WM_CHANGE_CD5:				APPEVENT_Set(APPEVENT_CHANGE_CD5, NULL);			break;//Kitao�ǉ�
		case WM_CHANGE_CD6:				APPEVENT_Set(APPEVENT_CHANGE_CD6, NULL);			break;//Kitao�ǉ�
		case WM_CHANGE_CD7:				APPEVENT_Set(APPEVENT_CHANGE_CD7, NULL);			break;//Kitao�ǉ�
		case WM_CHANGE_CD8:				APPEVENT_Set(APPEVENT_CHANGE_CD8, NULL);			break;//Kitao�ǉ�
		case WM_CHANGE_CD9:				APPEVENT_Set(APPEVENT_CHANGE_CD9, NULL);			break;//Kitao�ǉ�
		case WM_F1_NORESET:				APPEVENT_Set(APPEVENT_F1_NORESET, NULL);			break;//Kitao�ǉ�

		case WM_STARTFASTCD_ON:			APPEVENT_Set(APPEVENT_STARTFASTCD_ON, NULL);		break;//Kitao�ǉ�
		case WM_STARTFASTCD_OFF:		APPEVENT_Set(APPEVENT_STARTFASTCD_OFF, NULL);		break;//Kitao�ǉ�
		case WM_STARTFASTCD_PRE:		APPEVENT_Set(APPEVENT_STARTFASTCD_PRE, NULL);		break;//Kitao�ǉ�

		case WM_STARTFASTSEEK_ON:		APPEVENT_Set(APPEVENT_STARTFASTSEEK_ON, NULL);		break;//Kitao�ǉ�
		case WM_STARTFASTSEEK_OFF:		APPEVENT_Set(APPEVENT_STARTFASTSEEK_OFF, NULL);		break;//Kitao�ǉ�
		case WM_STARTFASTSEEK_PRE:		APPEVENT_Set(APPEVENT_STARTFASTSEEK_PRE, NULL);		break;//Kitao�ǉ�

		case WM_AUTO_GRADIUS2:			APPEVENT_Set(APPEVENT_AUTO_GRADIUS2, NULL);			break;//Kitao�ǉ�
		case WM_AUTO_MEGATEN:			APPEVENT_Set(APPEVENT_AUTO_MEGATEN, NULL);			break;//Kitao�ǉ�
		case WM_STARTSPRITE_OFF:		APPEVENT_Set(APPEVENT_STARTSPRITE_OFF, NULL);		break;//Kitao�ǉ�
		case WM_STARTSPRITE_ON:			APPEVENT_Set(APPEVENT_STARTSPRITE_ON, NULL);		break;//Kitao�ǉ�
		case WM_SPRITEBG_BUTTON:		APPEVENT_Set(APPEVENT_SPRITEBG_BUTTON, NULL);				break;//Kitao�ǉ�
		case WM_STARTSPRITE_PRE:		APPEVENT_Set(APPEVENT_STARTSPRITE_PRE, NULL);		break;//Kitao�ǉ�
		case WM_POWERON_EFFECT:			APPEVENT_Set(APPEVENT_POWERON_EFFECT, NULL);		break;//Kitao�ǉ�
		case WM_STRIKEBALL:				APPEVENT_Set(APPEVENT_STRIKEBALL, NULL);			break;//Kitao�ǉ�

		case WM_MENU_HIDEMENU:			APPEVENT_Set(APPEVENT_MENU_HIDEMENU, NULL);			break;//Kitao�ǉ�
		case WM_MENU_HIDEMESSAGE:		APPEVENT_Set(APPEVENT_MENU_HIDEMESSAGE, NULL);		break;//Kitao�ǉ�

		case WM_PRIORITY_HIGH:			APPEVENT_Set(APPEVENT_PRIORITY_HIGH, NULL);			break;//Kitao�ǉ�
		case WM_PRIORITY_NORMAL:		APPEVENT_Set(APPEVENT_PRIORITY_NORMAL, NULL);		break;//Kitao�ǉ�

		case WM_SPEED_V0:				APPEVENT_Set(APPEVENT_SPEED_V0, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_V1:				APPEVENT_Set(APPEVENT_SPEED_V1, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_V2:				APPEVENT_Set(APPEVENT_SPEED_V2, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_V3:				APPEVENT_Set(APPEVENT_SPEED_V3, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_V4:				APPEVENT_Set(APPEVENT_SPEED_V4, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_V5:				APPEVENT_Set(APPEVENT_SPEED_V5, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_V6:				APPEVENT_Set(APPEVENT_SPEED_V6, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_V7:				APPEVENT_Set(APPEVENT_SPEED_V7, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_V8:				APPEVENT_Set(APPEVENT_SPEED_V8, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_V9:				APPEVENT_Set(APPEVENT_SPEED_V9, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_VAL:				APPEVENT_Set(APPEVENT_SPEED_VAL, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_VUSE:				APPEVENT_Set(APPEVENT_SPEED_VUSE, NULL);			break;//Kitao�ǉ�
		case WM_SPEED_VSET:				APPEVENT_Set(APPEVENT_SPEED_VSET, NULL);			break;//Kitao�ǉ�
		case WM_SPEED_P0:				APPEVENT_Set(APPEVENT_SPEED_P0, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_T3:				APPEVENT_Set(APPEVENT_SPEED_T3, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_T2:				APPEVENT_Set(APPEVENT_SPEED_T2, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_T1:				APPEVENT_Set(APPEVENT_SPEED_T1, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_P6:				APPEVENT_Set(APPEVENT_SPEED_P6, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_P5:				APPEVENT_Set(APPEVENT_SPEED_P5, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_P4:				APPEVENT_Set(APPEVENT_SPEED_P4, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_P3:				APPEVENT_Set(APPEVENT_SPEED_P3, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_P2:				APPEVENT_Set(APPEVENT_SPEED_P2, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_P1:				APPEVENT_Set(APPEVENT_SPEED_P1, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_M1:				APPEVENT_Set(APPEVENT_SPEED_M1, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_M2:				APPEVENT_Set(APPEVENT_SPEED_M2, NULL);				break;//Kitao�ǉ�
		case WM_SPEED_CSET:				APPEVENT_Set(APPEVENT_SPEED_CSET, NULL);			break;//Kitao�ǉ�
		case WM_SPEED_UNLOAD:			APPEVENT_Set(APPEVENT_SPEED_UNLOAD, NULL);			break;//Kitao�ǉ�
		case WM_SPEED_LOAD:				APPEVENT_Set(APPEVENT_SPEED_LOAD, NULL);			break;//Kitao�ǉ�
		case WM_SPEED_FASTCD:			APPEVENT_Set(APPEVENT_SPEED_FASTCD, NULL);			break;//Kitao�ǉ�
		case WM_SPEED_FASTSEEK:			APPEVENT_Set(APPEVENT_SPEED_FASTSEEK, NULL);		break;//Kitao�ǉ�
		case WM_SPEED_HELP:				APPEVENT_Set(APPEVENT_SPEED_HELP, NULL);			break;//Kitao�ǉ�

		case WM_RASTERTIMING_MEARLY:	APPEVENT_Set(APPEVENT_RASTERTIMING_MEARLY, NULL);	break;//Kitao�ǉ�
		case WM_RASTERTIMING_EARLY:		APPEVENT_Set(APPEVENT_RASTERTIMING_EARLY, NULL);	break;//Kitao�ǉ�
		case WM_RASTERTIMING_MIDDLE:	APPEVENT_Set(APPEVENT_RASTERTIMING_MIDDLE, NULL);	break;//Kitao�ǉ�
		case WM_RASTERTIMING_LATE:		APPEVENT_Set(APPEVENT_RASTERTIMING_LATE, NULL);		break;//Kitao�ǉ�
		case WM_RASTERTIMING_MLATE:		APPEVENT_Set(APPEVENT_RASTERTIMING_MLATE, NULL);	break;//Kitao�ǉ�

		case WM_INVALIDATE_CDINST:		APPEVENT_Set(APPEVENT_INVALIDATE_CDINST, NULL);		break;//Kitao�ǉ�
		case WM_SUPERGRAFX:				APPEVENT_Set(APPEVENT_SUPERGRAFX, NULL);			break;//Kitao�ǉ�
		case WM_SPRITEOVER:				APPEVENT_Set(APPEVENT_SPRITEOVER, NULL);			break;//Kitao�ǉ�

		case WM_LAYER_SPRITE:			APPEVENT_Set(APPEVENT_LAYER_SPRITE, NULL);			break;//Kitao�ǉ�
		case WM_LAYER_BG:				APPEVENT_Set(APPEVENT_LAYER_BG, NULL);				break;//Kitao�ǉ�
		case WM_LAYER_SPRITE2:			APPEVENT_Set(APPEVENT_LAYER_SPRITE2, NULL);			break;//Kitao�ǉ�
		case WM_LAYER_BG2:				APPEVENT_Set(APPEVENT_LAYER_BG2, NULL);				break;//Kitao�ǉ�

		case WM_BIT_CONVERT:			APPEVENT_Set(APPEVENT_BIT_CONVERT, NULL);			break;//Kitao�ǉ�
		case WM_SHOW_DEBUG:				APPEVENT_Set(APPEVENT_SHOW_DEBUG, NULL);			break;//Kitao�ǉ�

		case WM_ALL_DEFAULT:			APPEVENT_Set(APPEVENT_ALL_DEFAULT, NULL);			break;//Kitao�ǉ�

		case WM_OUTPUT_SCREENSHOT:		APPEVENT_Set(APPEVENT_OUTPUT_SCREENSHOT, NULL);		break;//Kitao�ǉ�
		case WM_FOLDER_SCREENSHOT:		APPEVENT_Set(APPEVENT_FOLDER_SCREENSHOT, NULL);		break;//Kitao�ǉ�
		case WM_SCREENSHOT_BUTTON:		APPEVENT_Set(APPEVENT_SCREENSHOT_BUTTON, NULL);		break;//Kitao�ǉ�
		case WM_SCREENSHOT_DEFAULT:		APPEVENT_Set(APPEVENT_SCREENSHOT_DEFAULT, NULL);	break;//Kitao�ǉ�
		case WM_SCREENSHOT_X1:			APPEVENT_Set(APPEVENT_SCREENSHOT_X1, NULL);			break;//Kitao�ǉ�
		case WM_SCREENSHOT_X2:			APPEVENT_Set(APPEVENT_SCREENSHOT_X2, NULL);			break;//Kitao�ǉ�
		case WM_SCREENSHOT_X3:			APPEVENT_Set(APPEVENT_SCREENSHOT_X3, NULL);			break;//Kitao�ǉ�
		case WM_SCREENSHOT_X4:			APPEVENT_Set(APPEVENT_SCREENSHOT_X4, NULL);			break;//Kitao�ǉ�
		case WM_SCREENSHOT_XN:			APPEVENT_Set(APPEVENT_SCREENSHOT_XN, NULL);			break;//Kitao�ǉ�
		case WM_SCREENSHOT_SIZE:		APPEVENT_Set(APPEVENT_SCREENSHOT_SIZE, NULL);		break;//Kitao�ǉ�
		case WM_SSHOT_SAMEPLAYING:		APPEVENT_Set(APPEVENT_SSHOT_SAMEPLAYING, NULL);		break;//Kitao�ǉ�
		case WM_SSHOT_SPSCANLINED:		APPEVENT_Set(APPEVENT_SSHOT_SPSCANLINED, NULL);		break;//Kitao�ǉ�
		case WM_SSHOT_HRSCANLINEDTV:	APPEVENT_Set(APPEVENT_SSHOT_HRSCANLINEDTV, NULL);	break;//Kitao�ǉ�
		case WM_SSHOT_HRSCANLINED:		APPEVENT_Set(APPEVENT_SSHOT_HRSCANLINED, NULL);		break;//Kitao�ǉ�
		case WM_SSHOT_HRSCANLINED2:		APPEVENT_Set(APPEVENT_SSHOT_HRSCANLINED2, NULL);	break;//Kitao�ǉ�
		case WM_SSHOT_HRSCANLINED3:		APPEVENT_Set(APPEVENT_SSHOT_HRSCANLINED3, NULL);	break;//Kitao�ǉ�
		case WM_SSHOT_HRSCANLINEDF:		APPEVENT_Set(APPEVENT_SSHOT_HRSCANLINEDF, NULL);	break;//Kitao�ǉ�
		case WM_SSHOT_NONSCANLINED:		APPEVENT_Set(APPEVENT_SSHOT_NONSCANLINED, NULL);	break;//Kitao�ǉ�
		case WM_SSHOT_NONSCANLINED2:	APPEVENT_Set(APPEVENT_SSHOT_NONSCANLINED2, NULL);	break;//Kitao�ǉ�
		case WM_SSHOT_NONSCANLINEDTV:	APPEVENT_Set(APPEVENT_SSHOT_NONSCANLINEDTV, NULL);	break;//Kitao�ǉ�
		case WM_SSHOT_SAVEFOLDER:		APPEVENT_Set(APPEVENT_SSHOT_SAVEFOLDER, NULL);		break;//Kitao�ǉ�
		case WM_SSHOT_SAVEDIALOG:		APPEVENT_Set(APPEVENT_SSHOT_SAVEDIALOG, NULL);		break;//Kitao�ǉ�
		case WM_OUTPUT_WAV1:			APPEVENT_Set(APPEVENT_OUTPUT_WAV1, NULL);			break;//Kitao�ǉ�
		case WM_OUTPUT_WAV123:			APPEVENT_Set(APPEVENT_OUTPUT_WAV123, NULL);			break;//Kitao�ǉ�
		case WM_OUTPUT_WAV12:			APPEVENT_Set(APPEVENT_OUTPUT_WAV12, NULL);			break;//Kitao�ǉ�
		case WM_OUTPUT_WAV2:			APPEVENT_Set(APPEVENT_OUTPUT_WAV2, NULL);			break;//Kitao�ǉ�
		case WM_OUTPUT_WAV3:			APPEVENT_Set(APPEVENT_OUTPUT_WAV3, NULL);			break;//Kitao�ǉ�
		case WM_OUTPUT_WAV0:			APPEVENT_Set(APPEVENT_OUTPUT_WAV0, NULL);			break;//Kitao�ǉ�
		case WM_OUTPUT_WAVS1:			APPEVENT_Set(APPEVENT_OUTPUT_WAVS1, NULL);			break;//Kitao�ǉ�
		case WM_OUTPUT_WAVS2:			APPEVENT_Set(APPEVENT_OUTPUT_WAVS2, NULL);			break;//Kitao�ǉ�
		case WM_OUTPUT_WAVNT:			APPEVENT_Set(APPEVENT_OUTPUT_WAVNT, NULL);			break;//Kitao�ǉ�
		case WM_OUTPUT_WAVBE:			APPEVENT_Set(APPEVENT_OUTPUT_WAVBE, NULL);			break;//Kitao�ǉ�
		case WM_OUTPUT_AVI:				APPEVENT_Set(APPEVENT_OUTPUT_AVI, NULL);			break;//Kitao�ǉ�
		case WM_ABOUT_AVI:				APPEVENT_Set(APPEVENT_ABOUT_AVI, NULL);				break;//Kitao�ǉ�

		case WM_EXIT: //v2.70�X�V
			if (APP_GetFullScreen())
				APP_ToggleFullscreen();
			APPEVENT_Set(APPEVENT_EXIT, NULL);
			break;
		}
		break;

	//v2.49�ǉ��B�]���̑Ώ����@�ŃX�N���[���Z�[�o�[���}�~����ȂȂ��������ɂ��Ή��B
	case WM_SYSCOMMAND:
		if ((wParam == SC_SCREENSAVE)||(wParam == SC_MONITORPOWER))
			return 1;
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//�E�B���h�E���������\���Bv2.77�X�V
void
WINMAIN_SetMiniSize()
{
	RECT	rc;

	SetRect(&rc, 0, 0, 598, 16);
	AdjustWindowRect(&rc, GetWindowLong(_hMainWnd, GWL_STYLE), GetMenu(_hMainWnd) != NULL);
	SetWindowPos(_hMainWnd, HWND_NOTOPMOST, 20, 16, rc.right - rc.left, rc.bottom - rc.top, SWP_FRAMECHANGED);
	UpdateWindow(_hMainWnd);
}


static HWND
create_main_window(
	HINSTANCE		hInstance,
	int				nCmdShow)
{
	WNDCLASS	wc;
	HWND		hWnd;
	const char	className[] = MAINCAPTION;

	ZeroMemory(&wc, sizeof(wc));
	wc.style		 = 0;
	wc.lpfnWndProc	 = wnd_proc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = LoadIcon(hInstance, MAKEINTRESOURCE(OOTAKEICON)); //Kitao�X�V�B�A�C�R����ǂݍ��݁Bv2.00�X�V
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName	 = "";
	wc.lpszClassName = className;

	if (RegisterClass(&wc) == 0)
		return NULL;

	hWnd = CreateWindow(
		className,
		className,
		WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION | WS_DLGFRAME, //Kitao�X�V�B�E�B���h�E�T�C�Y�ύX�s�ɁB
		20,
		16,
		598,
		16, //Kitao�X�V�B���h���������悤�ɋN�����͉��_��ԂŋN������悤�ɂ����B
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hWnd == NULL)
		return NULL;

	//Kitao�X�V
	ShowWindow(hWnd, nCmdShow);
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) | (WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION | WS_DLGFRAME));
	WINMAIN_SetMiniSize();
	ImmAssociateContext(hWnd, 0); //Kitao�ǉ��BIME�𖳌��ɂ���Bv0.79

	// Drag&Drop�������� 
	DragAcceptFiles(hWnd, TRUE);

	return hWnd;
}


static void
deinit_argv(
	int		argc,
	char**	ppArgv)
{
	while (argc--)
		GlobalFree((HGLOBAL)ppArgv[argc]);

	GlobalFree((HGLOBAL)ppArgv);
}


const HINSTANCE
WINMAIN_GetHInstance()
{
	return _hInstance;
}

const HWND
WINMAIN_GetHwnd()
{
	return _hMainWnd;
}


void
WINMAIN_SetCaption(
	const char*		pCaption)
{
	if (pCaption)
	{
		sprintf(_Caption, "%s", &(*pCaption)); //Kitao�ǉ��Bv1.50fixed(for gcc). Thanks for Nao-san report.
		SetWindowText(_hMainWnd, pCaption);
	}
	else
		SetWindowText(_hMainWnd, APP_GetAppName());
}


//Kitao�ǉ�
char*
WINMAIN_GetCaption()
{
	return _Caption;
}


Uint32
WINMAIN_ShowCursor(
	BOOL		bShow)
{
	if (bShow)
	{
		while (ShowCursor(bShow) < 0);
		APP_ResetMouseStopCount(); //Kitao�ǉ��B�}�E�X�������I�ɉB�����߂̃J�E���^�����Z�b�g����B
	}
	else
		while (ShowCursor(bShow) >= 0);

	return 0;
}

void
WINMAIN_SetFullScreenWindow(
	Sint32		width,
	Sint32		height)
{
	set_fullscreen_windowstyle(_hMainWnd, (int)width, (int)height); //�E�B���h�E�X�^�C���̕ύX�͂����ɍs���悤�ɂ����B�������x�A�b�v�Bv2.23
	APPEVENT_Set(APPEVENT_REDRAWSCREEN, NULL); //�E�B���h�E�X�^�C���ύX������ɉ�ʂ��ĕ`��
}


void
WINMAIN_SetNormalWindow(
	Sint32		width,
	Sint32		height)
{
	set_normal_windowstyle(_hMainWnd, (int)width, (int)height); //�E�B���h�E�X�^�C���̕ύX�͂����ɍs���悤�ɂ����B�������x�A�b�v�Bv2.23
	APPEVENT_Set(APPEVENT_REDRAWSCREEN, NULL); //�E�B���h�E�X�^�C���ύX������ɉ�ʂ��ĕ`��
}

//Kitao�ǉ��Bv2.04
void
WINMAIN_SetPriority(
	DWORD	dwPriorityClass)
{
	HANDLE	hProcess;

	hProcess = OpenProcess(PROCESS_SET_INFORMATION, TRUE, GetCurrentProcessId());
	SetPriorityClass(hProcess, dwPriorityClass);
	CloseHandle(hProcess);
}


int
WINAPI
WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	char**		argv;
	int			argc;
	int			ret;

	_hInstance = hInstance;

	argc = init_argc(lpCmdLine);
	argv = init_argv(argc, lpCmdLine);

	if (argv == NULL)
		return -1;

	//Kitao�ǉ��B�v���Z�X�̗D��x���グ��B(Vista�̃E�B���h�E���[�h�ŕK�{�B�����̈��萫����)
	WINMAIN_SetPriority(ABOVE_NORMAL_PRIORITY_CLASS); //v2.04�X�V

	_hMainWnd = create_main_window(hInstance, nCmdShow);

	if (_hMainWnd == NULL)
	{
		deinit_argv(argc, argv);
		return -1;
	}

	ret = __main__(argc, argv);

	deinit_argv(argc, argv);

	return ret;
}


//Kitao�ǉ��B�Z�[�t�e�B�ɃE�F�C�g�������s�����߂̊֐��Bv2.42�ǉ�
//			 Sleep(0)�Ŗ������[�v�ɂȂ��Ă��܂���OS���ƌł܂�댯������̂ŁA���̎��Ԃ��o�߂����ꍇ��Sleep(1)�ɐ؂�ւ��đ҂B
void
WINMAIN_SafetySleepZero(
	DWORD	startTime,
	DWORD	endTime)
{
	DWORD	t = timeGetTime();

	if ((t >= endTime)||(t < startTime)) //��莞�ԂɒB�������A�������̓^�C�}�[�J�E���^���I�[�o�[�t���[����0�ɖ߂����ꍇ
		Sleep(1); //Sleep(0)�ƈႢ�ACPU���L���Ȃ��̂ŁA���S��Ootake���I���ł���B
	else
		Sleep(0); //Sleep(1)���ׂ��ȃ^�C�~���O�ŃE�F�C�g���ł���B�����ȃ^�C�~���O���K�v�ȏꍇ�ŗL���B
}


//Kitao�ǉ��B�f�o�b�O�p
void
WINMAIN_SetBreakTrap(
	BOOL bBrakTrap)
{
	_bBreakTrap = bBrakTrap;
}

//Kitao�ǉ��B�f�o�b�O�p
BOOL
WINMAIN_GetBreakTrap()
{
	return _bBreakTrap;
}
