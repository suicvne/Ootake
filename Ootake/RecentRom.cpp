/******************************************************************************
Ootake

 [RecentRom.cpp]
	�ŋߋN�������Q�[���̈ꗗ��\�����邽�߂̃t�H�[��

Copyright(C)2006-2016 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

******************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "RecentRom.h"
#include "resource.h"
#include "WinMain.h"
#include "App.h"

#define LINE_LEN	48
#define N_LINES 	22

enum RecentComponent
{
	LISTBOX_SELECTEDROM = 1
};
static HWND			_hWndC[1+1]; //�e�R���|�[�l���g�̃n���h��

static WNDPROC		_WPListBox; //�L�[�t�b�N�̂���
static BOOL			_bKeyRepeatDown;
static BOOL			_bKeyRepeatUp;
static BOOL			_bKeyRepeatSel;
static BOOL			_bKeyRepeatRun;

static HBRUSH		_hMyb; //����u���V�F
static HFONT		_hFontB; //���X�g�p�t�H���g

static Uint32		_FontWidth;
static Uint32		_FontHeight;
static const char*	_pCaption = "\"Ootake\" Game Select";
static HINSTANCE	_hInstance = NULL;
static HWND 		_hWnd;
static BOOL 		_bToggle;

static Sint32		_SelectedRom = -1; //�߂�l(���肵���ꍇ1�`9999���Ԃ����)�B�L�����Z���Ȃ�-1�B���ݒ蒆��0�B
static Sint32*		_pSelectedRom;


/* �t�H���g�̍������擾���� */
static Uint32
get_font_height(
	HWND			hWnd)
{
	HDC 			hDC;
	HFONT			hFont;
	HFONT			hFontOld;
	TEXTMETRIC		tm;

	hDC 	 = GetDC(hWnd);
	hFont	 = (HFONT)GetStockObject(OEM_FIXED_FONT);	 /* �Œ�s�b�`�t�H���g */
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
	HDC 			hDC;
	HFONT			hFont;
	HFONT			hFontOld;
	TEXTMETRIC		tm;

	hDC 	 = GetDC(hWnd);
	hFont	 = (HFONT)GetStockObject(OEM_FIXED_FONT);	 /* �Œ�s�b�`�t�H���g */
	hFontOld = (HFONT)SelectObject(hDC, hFont);

	GetTextMetrics(hDC, &tm);

	SelectObject(hDC, hFontOld);
	DeleteObject(hFont);
	ReleaseDC(hWnd, hDC);

	return (Uint32)tm.tmAveCharWidth;
}


static void
set_window_size(
	HWND			hWnd)
{
	RECT	rc;
	Uint32	wndW = _FontWidth  * LINE_LEN - 3;
	Uint32	wndH = _FontHeight * N_LINES - 5;
	int		y;

	SetRect(&rc, 0, 0, wndW, wndH);
	AdjustWindowRectEx(&rc, GetWindowLong(hWnd, GWL_STYLE),
						GetMenu(hWnd) != NULL, GetWindowLong(hWnd, GWL_EXSTYLE));
	wndW = rc.right - rc.left;
	wndH = rc.bottom - rc.top;
	GetWindowRect(WINMAIN_GetHwnd(), &rc);
	y = rc.top;
	if (y + (int)wndH > GetSystemMetrics(SM_CYSCREEN))
	{
		y = GetSystemMetrics(SM_CYSCREEN) - wndH ;
		if (y<0) y=0;
	}
	MoveWindow(hWnd, rc.left, y, wndW, wndH, TRUE);
}


//Close�����Bwnd_proc�̒���WM_CLOSE�𑗂�ƃn���h�����s��ɂȂ��Č듮��([O]��[P]�L�[�������ă_�C�����O���J���ƃ��C���E�B���h�E���e�ɂȂ�Ȃ��Bv2.69�ȑO)���������̂ŁA���ꂪ�K�v�Bv2.70�X�V
static LRESULT CALLBACK
recent_close()
{
	RECENT_Deinit();
	if (_bToggle) //DirectDraw�Ńt���X�N���[���������ꍇ
	{
		APP_RunEmulator(FALSE); //�E�B���h�E���A�N�e�B�u�ɂ��邽�߂Ƀ��j���[��\�����Ẵ|�[�Y�B
		APP_ToggleFullscreen(); //�t���X�N���[���ɖ߂��B
		APP_RunEmulator(TRUE); //�����Ń|�[�Y�������Ă����Ȃ��ƁA�Ȃ�����ł̓|�[�Y���������܂������Ȃ��BDirectDraw�ׂ͍��ȓ��삪�s����œ���BDirect3D��OK�B
	}
	if (_SelectedRom == 0)
		_SelectedRom = -1; //�L�����Z��
	return 0;
}

//LISTBOX�R���|�[�l���g��ł̃L�[���͂����m���邽�߂̃t�b�N
static LRESULT CALLBACK
ListBoxProc(
	HWND		hWnd,
	UINT		uMsg,
	WPARAM		wParam,
	LPARAM		lParam)
{
	if (uMsg == WM_CHAR) //�L�[���͂������ςɂ��邽��WM_KEYDOWN�łȂ�WM_CHAR���g�p
	{
		if (wParam == VK_ESCAPE) //Esc�L�[��������Ă��������
			return recent_close(); //0��Ԃ����Ƃ�WM_CHAR�������ςɁB�r�[�v����炳���ɍςށB
		if (wParam == 'O')
		{
			_SelectedRom = -2; //Open Rom
			return recent_close(); //0��Ԃ����Ƃ�WM_CHAR�������ςɁB�r�[�v����炳���ɍςށB
		}
		if (wParam == 'P')
		{
			_SelectedRom = -3; //Open Cue
			return recent_close(); //0��Ԃ����Ƃ�WM_CHAR�������ςɁB�r�[�v����炳���ɍςށB
		}
	}
	return CallWindowProc(_WPListBox, hWnd, uMsg, wParam, lParam);
} 

static LRESULT CALLBACK
recent_wnd_proc(
	HWND		hWnd,
	UINT		uMsg,
	WPARAM		wParam,
	LPARAM		lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		EnableWindow(WINMAIN_GetHwnd(), FALSE);//Kitao�ǉ��B���C���E�C���h�E�𖳌������ă��[�_���ɁB
		_bToggle = FALSE;
		if (APP_GetFullScreen())
		{
			if (APP_GetDrawMethod() == 2)
			{
				APP_ToggleFullscreen(); //DirectDraw�̏ꍇ�A��ʂƃt�H�[�J�X�������̂ŁA�E�B���h�E���[�h�ɋ����B
				_bToggle = TRUE;
			}
			else
				ShowWindow(WINMAIN_GetHwnd(), SW_HIDE); //�t���X�N���[���̏ꍇ�A���C���E�B���h�E���B���B
		}
		_hFontB = (HFONT)GetStockObject(SYSTEM_FONT);
		_FontWidth	= get_font_width(hWnd);
		_FontHeight = get_font_height(hWnd);
		set_window_size(hWnd);
		break;

	case WM_SIZE:
		if (_bToggle) //DirectDraw�Ńt���X�N���[���������ꍇ�A�ؑ֌�ɃE�B���h�E�̃A�N�e�B�u�����K�v
		{
			SetForegroundWindow(WINMAIN_GetHwnd());
			SetForegroundWindow(hWnd);
		}
		break;

	case WM_PAINT:
		SetFocus(_hWnd);//���X�g�{�b�N�X����t�H�[�J�X���O��
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			_SelectedRom = -1; //�L�����Z��
			return recent_close();
		}
		if (wParam == 'O')
		{
			_SelectedRom = -2; //Open Rom
			return recent_close();
		}
		if (wParam == 'P')
		{
			_SelectedRom = -3; //Open Cue
			return recent_close();
		}
		break;

	case WM_COMMAND:
		switch(HIWORD(wParam))
		{
			case LBN_DBLCLK:
				//�߂�l��ݒ�
				_SelectedRom = SendMessage(GetDlgItem(hWnd, LISTBOX_SELECTEDROM), LB_GETCURSEL, 0, 0) + 1;
				return recent_close();
		}
		break;

	case WM_CLOSE:
		return recent_close();
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


static BOOL
recent_main()
{
	WNDCLASS	wc;
	HWND		hWnd;
	RECT		rc;
	Uint32		x;
	Uint32		y;
	Sint32		i;
	MSG			msg;
	Sint32		a;

	ZeroMemory(&wc, sizeof(wc));
	wc.style		 = 0;
	wc.lpfnWndProc	 = recent_wnd_proc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = _hInstance;
	wc.hIcon		 = LoadIcon(_hInstance, MAKEINTRESOURCE(OOTAKEICON)); //�A�C�R����ǂݍ���
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
		WS_SYSMENU | WS_CAPTION,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		NULL, //�e�E�B���h�E�Ȃ��̂ق����E�B���h�E����鏈��������
		NULL,
		_hInstance,
		NULL
	);

	if (hWnd == NULL)
		return FALSE;

	_hWnd = hWnd;

	//ROM�Z���N�g�p���X�g�{�b�N�X���쐬
	x = _FontWidth*2 - 2;
	y = _FontHeight - 5;
	_hWndC[1] = CreateWindow(
		"LISTBOX", "",
		WS_CHILD | WS_VISIBLE | LBS_NOTIFY,
		x, y, _FontWidth*44, _FontHeight*20,
		_hWnd, (HMENU)LISTBOX_SELECTEDROM, _hInstance, NULL
	);
	_WPListBox = (WNDPROC)GetWindowLong(_hWndC[1], GWL_WNDPROC); //�L�[�t�b�N���邽�߂Ɍ��̃v���V�[�W���A�h���X��ޔ�
	SetWindowLong(_hWndC[1], GWL_WNDPROC, (LONG)ListBoxProc); //���O�̃t�b�N�ɏ�������
	SendMessage(_hWndC[1], WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));//�t�H���g��ݒ�
	for (i=1; i<=20; i++)
		SendMessage(_hWndC[1], LB_ADDSTRING, 0, (LPARAM)APP_GetRecentRom(i));
	SendMessage(_hWndC[1], LB_SETCURSEL, 0, 0);

	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);
	GetWindowRect(_hWnd, &rc);
	SetWindowPos(_hWnd, HWND_TOP, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_FRAMECHANGED);
	ImmAssociateContext(_hWnd, 0); //IME�𖳌��ɂ���

	//���[�v����
	while (_SelectedRom == 0)
	{
		Sleep(1);

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (APP_CheckButtonState(11)) //I�{�^�����������ꍇ
		{
			//�߂�l��ݒ�
			_SelectedRom = SendMessage(GetDlgItem(hWnd, LISTBOX_SELECTEDROM), LB_GETCURSEL, 0, 0) + 1;
			PostMessage(hWnd, WM_CLOSE, 0, 0);
		}
		if (APP_CheckButtonState(18)) //RUN�{�^�����������ꍇ
		{
			if (_bKeyRepeatRun)
			{	//�O�񉟂��āA�܂��������ςȂ��̏ꍇ
				if (!APP_CheckButtonState(18))
					_bKeyRepeatRun = FALSE;
			}
			else
			{
				//�߂�l��ݒ�
				_SelectedRom = SendMessage(GetDlgItem(hWnd, LISTBOX_SELECTEDROM), LB_GETCURSEL, 0, 0) + 1;
				PostMessage(hWnd, WM_CLOSE, 0, 0);
			}
		}
		else
			_bKeyRepeatRun = FALSE;

		if (APP_CheckButtonState(12)) //II�{�^�����������ꍇ
		{
			_SelectedRom = -1; //�L�����Z��
			PostMessage(hWnd, WM_CLOSE, 0, 0);
		}

		if (APP_CheckButtonState(2)) //���{�^�����������ꍇ
		{
			if (_bKeyRepeatDown)
			{	//�O�񉟂��āA�܂��������ςȂ��̏ꍇ
				if (!APP_CheckButtonState(2))
					_bKeyRepeatDown = FALSE;
			}
			else
			{
				a = SendMessage(GetDlgItem(hWnd, LISTBOX_SELECTEDROM), LB_GETCURSEL, 0, 0) + 1;
				if (a == 20)
					a = 0;
				SendMessage(GetDlgItem(hWnd, LISTBOX_SELECTEDROM), LB_SETCURSEL, (WPARAM)a, 0);
				_bKeyRepeatDown = TRUE;
			}
		}
		else
			_bKeyRepeatDown = FALSE;
		if ((APP_CheckButtonState(17))&&(APP_CheckFuncAndSelConflict())) //SELECT�{�^�����������ꍇ
		{
			if (_bKeyRepeatSel)
			{	//�O�񉟂��āA�܂��������ςȂ��̏ꍇ
				if (!APP_CheckButtonState(17))
					_bKeyRepeatSel = FALSE;
			}
			else
			{
				a = SendMessage(GetDlgItem(hWnd, LISTBOX_SELECTEDROM), LB_GETCURSEL, 0, 0) + 1;
				if (a == 20)
					a = 0;
				SendMessage(GetDlgItem(hWnd, LISTBOX_SELECTEDROM), LB_SETCURSEL, (WPARAM)a, 0);
				_bKeyRepeatSel = TRUE;
			}
		}
		else
			_bKeyRepeatSel = FALSE;

		if (APP_CheckButtonState(8)) //��{�^�����������ꍇ
		{
			if (_bKeyRepeatUp)
			{	//�O�񉟂��āA�܂��������ςȂ��̏ꍇ
				if (!APP_CheckButtonState(8))
					_bKeyRepeatUp = FALSE;
			}
			else
			{
				a = SendMessage(GetDlgItem(hWnd, LISTBOX_SELECTEDROM), LB_GETCURSEL, 0, 0) - 1;
				if (a == -1)
					a = 19;
				SendMessage(GetDlgItem(hWnd, LISTBOX_SELECTEDROM), LB_SETCURSEL, (WPARAM)a, 0);
				_bKeyRepeatUp = TRUE;
			}
		}
		else
			_bKeyRepeatUp = FALSE;
	}

	//����L�[�𗣂��܂ő҂B���ꂪ�Ȃ��ƃQ�[�����A���Ɍ둀��̉\������B
	while ((APP_CheckButtonState(11))||(APP_CheckButtonState(12))||(APP_CheckButtonState(18))) //I,II,RUN�L�[���S�ė������܂ő҂B
		Sleep(1);
	
	//�߂�l��ݒ�
	*_pSelectedRom = _SelectedRom; //���̏u�Ԃ�App.c �ɐ��䂪�߂�B

	return TRUE;
}


BOOL
RECENT_Init(
	HINSTANCE	hInstance,
	Sint32*		selectedRom)
{
	if (_hInstance != NULL)
		RECENT_Deinit();

	_hInstance = hInstance;

	_bKeyRepeatDown	= FALSE;
	_bKeyRepeatUp	= FALSE;
	_bKeyRepeatSel	= FALSE;
	_bKeyRepeatRun	= TRUE; //Run�{�^���͉����ꂽ��Ԃł������Ă΂��

	_pSelectedRom = selectedRom;
	_SelectedRom = 0;

	return recent_main();
}


void
RECENT_Deinit()
{
	if (_hInstance != NULL)
	{
		DestroyWindow(_hWnd);
		_hWnd = NULL;
		UnregisterClass(_pCaption, _hInstance);
		_hInstance = NULL;
		
		DeleteObject(_hFontB); //�{�^���p�t�H���g���J��
		DeleteObject(_hMyb); //�u���V���J��
		
		//���C���E�B���h�E��Enable�ɖ߂��A�O�ʂɁB
		if (APP_GetFullScreen())
			ShowWindow(WINMAIN_GetHwnd(), SW_SHOWNORMAL);
		EnableWindow(WINMAIN_GetHwnd(), TRUE);
		SetForegroundWindow(WINMAIN_GetHwnd());
	}
}

