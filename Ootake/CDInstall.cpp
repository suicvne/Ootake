/******************************************************************************
Ootake

 [CDInstall.c]
	CD�̃f�[�^���C���X�g�[�����邱�ƂŃA�N�Z�X�̍�������}��

Copyright(C)2006-2016 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

******************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <process.h>
#include "CDInstall.h"
#include "resource.h"
#include "WinMain.h"
#include "CDROM.h"
#include "TocDB.h"
#include "App.h"
#include "CDInterface.h"


#define CDINSTALL_CAPTION 	"Ootake CD Install"

#define LINE_LEN	59
#define N_LINES 	7

#define BUTTON_ABORT	0


static HBRUSH		_hMyb; //����u���V�F
static HFONT		_hFont; //�ʏ핶���p�t�H���g
static HFONT		_hFontB; //�{�^���p�t�H���g

static Uint32		_FontWidth;
static Uint32		_FontHeight;
static const char*	_pCaption = CDINSTALL_CAPTION;
static HINSTANCE	_hInstance = NULL;
static HWND 		_hWnd;
static BOOL			_bFullInstall; //v2.24�ǉ�


//CD Install �X���b�h
static HANDLE	_hThread;
static DWORD	_dwThreadID;

static Sint32	_Result;


/* �t�H���g�̍������擾���� */
static Uint32
get_font_height(
	HWND			hWnd)
{
	HDC 			hDC;
	HFONT			hFontOld;
	TEXTMETRIC		tm;

	hDC 	 = GetDC(hWnd);
	hFontOld = (HFONT)SelectObject(hDC, _hFont);

	GetTextMetrics(hDC, &tm);

	SelectObject(hDC, hFontOld);
	ReleaseDC(hWnd, hDC);

	return (Uint32)(tm.tmHeight);
}

/* �t�H���g�̉������擾���� */
static Uint32
get_font_width(
	HWND			hWnd)
{
	HDC 			hDC;
	HFONT			hFontOld;
	TEXTMETRIC		tm;

	hDC 	 = GetDC(hWnd);
	hFontOld = (HFONT)SelectObject(hDC, _hFont);

	GetTextMetrics(hDC, &tm);

	SelectObject(hDC, hFontOld);
	ReleaseDC(hWnd, hDC);

	return (Uint32)tm.tmAveCharWidth;
}


static void
set_window_size(
	HWND			hWnd)
{
	RECT		rc;
	Uint32		wndW = _FontWidth  * LINE_LEN;
	Uint32		wndH = _FontHeight * N_LINES;

	SetRect(&rc, 0, 0, wndW, wndH);
	AdjustWindowRectEx(&rc, GetWindowLong(hWnd, GWL_STYLE),
						GetMenu(hWnd) != NULL, GetWindowLong(hWnd, GWL_EXSTYLE));
	wndW = rc.right - rc.left;
	wndH = rc.bottom - rc.top;
	GetWindowRect(WINMAIN_GetHwnd(), &rc);
	MoveWindow(hWnd, rc.left, rc.top, wndW, wndH, TRUE);
}


static void
update_window(
	HWND			hWnd)
{
	HDC 			hDC;
	HFONT			hFontOld;
	PAINTSTRUCT 	ps;
	Uint32			x;
	Uint32			y;
	char			buf[100];

	/* �`�揀�� */
	hDC = BeginPaint(hWnd, &ps);
	SetBkMode(hDC, OPAQUE);	//�����̔w�i��h��Ԃ�
	SetBkColor(hDC, RGB(64,128,64));
	SetTextColor(hDC, RGB(240,240,240));
	hFontOld = (HFONT)SelectObject(hDC, _hFont);

	x = _FontWidth*2 +1;
	y = _FontHeight;

	sprintf(buf, "\"%s\"", TOCDB_GetGameTitle());
	TextOut(hDC, x, y, buf, strlen(buf)); y+=_FontHeight;
	sprintf(buf, " Required HDD Space - %dMB.", (int)CDROM_GetInstallRequiredHDD());
	TextOut(hDC, x, y, buf, strlen(buf)); y+=_FontHeight;
	y+=_FontHeight;

	/* �I������ */
	EndPaint(hWnd, &ps);
	SelectObject(hDC, hFontOld);
	ReleaseDC(hWnd, hDC);
}


//Close�����Bv2.70�X�V
static LRESULT CALLBACK
cdinstall_close()
{
	if (MessageBox(_hWnd, "Abort Install?", "Ootake", MB_YESNO) == IDYES)
	{
		if (_Result == 0) //Yes�{�^���������܂ł̊ԂɃC���X�g�[�������������ꍇ���l��
			_Result = -1; //���f
	}
	return 0; //�����ɑ�����
}

static LRESULT CALLBACK
cdinstall_wnd_proc(
	HWND		hWnd,
	UINT		uMsg,
	WPARAM		wParam,
	LPARAM		lParam)
{
	LOGFONT		logFont;

	switch(uMsg)
	{
	case WM_CREATE:
		EnableWindow(WINMAIN_GetHwnd(), FALSE);//���C���E�B���h�E�𖳌������ă��[�_���ɁB
		_hFont = (HFONT)GetStockObject(SYSTEM_FONT);
		GetObject(_hFont, sizeof(LOGFONT), &logFont);
		logFont.lfWeight = FW_BOLD;
		_hFont = CreateFontIndirect(&logFont);
		_hFontB = CreateFont(  0,						// �����B0 = �f�t�H���g
		                       0,						// ���B0�Ȃ獂���ɍ�������
    		                   0,						// �p�x
        		               0,						// �x�[�X���C���Ƃ̊p�x
            		           FW_NORMAL,				// ����
                		       FALSE,					// �C�^���b�N
                    		   FALSE,					// �A���_�[���C��
		                       FALSE,					// �ł�������
    		                   0,						// ���{�����舵���Ƃ���SHIFTJIS_CHARSET�ɂ���B
        		               0,						// �o�͐��x
            		           0,						// �N���b�s���O���x
                		       0,						// �o�͕i��
                    		   0,						// �s�b�`�ƃt�@�~���[
	                    	   ""						// ���̖�
							); //�p��̃f�t�H���g�t�H���g�ɐݒ�
		_FontWidth	= get_font_width(hWnd);
		_FontHeight = get_font_height(hWnd);
		set_window_size(hWnd);
		break;

	case WM_PAINT:
		update_window(hWnd);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			return cdinstall_close();
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case BUTTON_ABORT:
				return cdinstall_close();
		}
		break;

	case WM_CLOSE:
		return cdinstall_close();
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


static DWORD WINAPI
cdinstall_thread()
{
	Sint32			installRequiredHDD = CDROM_GetInstallRequiredHDD();
	ULARGE_INTEGER	ulFreeBytesAvailableToCaller;
	ULARGE_INTEGER	ulTotalNumberOfFreeBytes;
	ULARGE_INTEGER	ulTotalNumberOfBytes;
	Sint32			check;

	//��荞�߂�g���b�N���Ȃ������ꍇ�BCD�����ĂȂ��Ƃ����܂ށB
	if (installRequiredHDD == 0)
	{
		MessageBox(_hWnd, "There is no data that can be installed. Please put CD-ROM of the \"PC Engine\".    ", "Ootake", MB_OK);
		_Result = -1; //���s,���f
		PostMessage(_hWnd, WM_QUIT, 0, 0);
		return 0;
	}

	//HDD�̋󂫗e�ʂ�����Ȃ��ꍇ�A���b�Z�[�W��\�����Ē��~����B
	if(GetDiskFreeSpaceEx(APP_GetAppPath(), &ulFreeBytesAvailableToCaller, &ulTotalNumberOfBytes, &ulTotalNumberOfFreeBytes))
		if ((__int64)ulTotalNumberOfFreeBytes.QuadPart/1024/1024 < installRequiredHDD+100)
		{
			MessageBox(_hWnd, "Free space of HDD doesn't suffice.    ", "Ootake", MB_OK);
			_Result = -1; //���s,���f
			PostMessage(_hWnd, WM_QUIT, 0, 0);
			return 0;
		}

	//���łɃC���X�g�[���������ς݂̏ꍇ�A���b�Z�[�W��\�����ďI���B
	check = CDROM_CheckCDInstall(); //CDIF_GetBadInstalled()�̒l���ݒ肳���B
	if (((!_bFullInstall)&&(check != 0))||
		((_bFullInstall)&&(check == 2)&&((!CDIF_GetBadInstalled())||(APP_GetCueFile())))) //�t���C���X�g�[�����A�o�b�h�C���X�g�[��(�Â�Ootake�ł̃C���X�g�[��)�ł���CUE�t�@�C���N���ł͂Ȃ��ꍇ�́A�t���C���X�g�[����蒼����������B
	{
		if (check == 2)
		{
			if ((_bFullInstall)&&(CDIF_GetBadInstalled())&&(APP_GetCueFile())) //�o�b�h�C���X�g�[��(�Â�Ootake�ł̃C���X�g�[��)��cue�N���̏ꍇ
				MessageBox(_hWnd, "It is started with \"Installed Play\" now.    \nPlease start with \"CD-ROM drive\" to FullInstall.    ", "Ootake", MB_OK);
			else
				MessageBox(_hWnd, "\"CD FullInstall\" of this game is already completed.    ", "Ootake", MB_OK);
		}
		else
			MessageBox(_hWnd, "\"CD Install\" of this game is already completed.    ", "Ootake", MB_OK);
		_Result = 1; //����
		PostMessage(_hWnd, WM_QUIT, 0, 0);
		return 0;
	}

	//�C���X�g�[������
	if (CDROM_CDInstall(_hWnd, _bFullInstall))
	{
        if (_bFullInstall)
		{
			MessageBox(_hWnd, "\"CD FullInstall\" of this game was completed.    \n\n"
							  "- Please use \"Image File(CUE+ISO+WAV)\" carefully.    \n"
							  "  Because distributing \"Image File(CUE+ISO+WAV)\" is illegal.    \n"
							  "  Please avoid direct sunshine and moisture, and keep    \n"
							  "  \"Mastering CD-ROM\" importantly.\n\n"
							  "In Japanese language\n"
							  "���C���[�W�t�@�C��(CUE+ISO+WAV)�́A���̕��֔z�z����ƒ��쌠    \n"
							  "�@�ᔽ�ɂȂ�܂��̂ŁA�K���T�d�Ɉ����Ă��������B�܂��A�I���W�i��    \n"
							  "�̎�CD�Ղ����L��������K�v������܂��B��CD�Ղ́A���˓�����    \n"
							  "���C�������؂ɕۊǂȂ����Ă��������B", "Ootake", MB_OK);
		}
		else
			MessageBox(_hWnd, "\"CD Install\" of this game was completed.    ", "Ootake", MB_OK);
		_Result = 1; //����
	}
	else
		_Result = -1; //���s,���f

	PostMessage(_hWnd, WM_QUIT, 0, 0);
	return 0;
}


BOOL
CDINSTALL_Init(
	HINSTANCE		hInstance,
	BOOL			bFullInstall)
{
	WNDCLASS		wc;
	HWND			hWnd;
	Uint32			x;
	Uint32			y;
	HWND			hWndTmp;
	MSG				msg;

	if (_hInstance != NULL)
		CDINSTALL_Deinit();

	//�t���C���X�g�[�����ǂ����̕ϐ���ݒ�
	_bFullInstall = bFullInstall;

	//HDD�̕K�v�e�ʂ��v�Z���Ă���
	CDROM_SetInstallRequiredHDD(_bFullInstall);

	_hInstance = hInstance;
	_Result = 0;

	ZeroMemory(&wc, sizeof(wc));
	wc.style		 = 0;
	wc.lpfnWndProc	 = cdinstall_wnd_proc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = _hInstance;
	wc.hIcon		 = LoadIcon(_hInstance, MAKEINTRESOURCE(OOTAKEICON)); //�A�C�R����ǂݍ��݁Bv2.00�X�V
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	_hMyb = CreateSolidBrush(RGB(64,128,64)); //�u���V�����
	wc.hbrBackground = _hMyb;
	wc.lpszMenuName  = "";
	wc.lpszClassName = _pCaption;

	if (RegisterClass(&wc) == 0)
		return FALSE;

	hWnd = CreateWindow(
		_pCaption,
		_pCaption,
		WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		WINMAIN_GetHwnd(),
		NULL,
		_hInstance,
		NULL
	); //���C���X���b�h��Create���邱�Ƃ�CD��荞�ݒ��ł��{�^���̎�t�����ł���B

	if (hWnd == NULL)
		return 0;

	_hWnd = hWnd;

	//�{�^�����쐬
	x = _FontWidth*19 + _FontWidth/2;
	y = _FontHeight*4 +3;
	hWndTmp = CreateWindow(
		"BUTTON", "&Abort (Esc key)",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x, y, _FontWidth*21, _FontHeight*2-3,
		_hWnd, (HMENU)BUTTON_ABORT, _hInstance, NULL
	);
	SendMessage(hWndTmp, WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));//�����̃t�H���g��ݒ�

	CloseWindow(WINMAIN_GetHwnd());//���C���E�B���h�E���ŏ���
	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);
	ImmAssociateContext(_hWnd, 0); //IME�𖳌��ɂ���

	//CD�ǂݎ�菈����p�X���b�h���쐬���Ď��s����	
	_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)cdinstall_thread, NULL, 0, &_dwThreadID);

	//���b�Z�[�W���[�v 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CDINSTALL_Deinit();
	return TRUE;
}


void
CDINSTALL_Deinit()
{
	if (_hInstance != NULL)
	{
		CloseHandle(_hThread);
		
		DestroyWindow(_hWnd);
		_hWnd = NULL;
		UnregisterClass(_pCaption, _hInstance);
		_hInstance = NULL;
		
		DeleteObject(_hFont); //�ʏ핶���p�t�H���g���J��
		DeleteObject(_hFontB); //�{�^���p�t�H���g���J��
		DeleteObject(_hMyb); //�u���V���J��
		
		//���C���E�B���h�E�Ƀt�H�[�J�X��߂����̑傫���ɁB
		EnableWindow(WINMAIN_GetHwnd(), TRUE);
		OpenIcon(WINMAIN_GetHwnd());
	}
}


Sint32
CDINSTALL_GetResult()
{
	return _Result;
}

