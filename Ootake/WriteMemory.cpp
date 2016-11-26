/******************************************************************************
Ootake

 [WriteMemory.cpp]
	���������e���������̃R�}���h����͂��邽�߂̃t�H�[��

Copyright(C)2006-2013 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

******************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE

#include "WriteMemory.h"
#include "resource.h"
#include "WinMain.h"
#include "App.h"
#include "Printf.h"
#include "MainBoard.h"

#define LINE_LEN	59
#define N_LINES 	6

enum WriteMemoryComponent
{
	EDIT_CODE = 1,
	BUTTON_CLEAR,
	BUTTON_SET,
};
static HWND			_hWndC[1+1]; //�e�R���|�[�l���g�̃n���h��

static WNDPROC		_WPEdit; //�L�[�t�b�N�̂���

static HBRUSH		_hMyb; //����u���V�F
static HFONT		_hFontB; //�{�^���p�t�H���g

static Uint32		_FontWidth;
static Uint32		_FontHeight;
static const char*	_pCaption = "\"Ootake\" Write Memory";
static HINSTANCE	_hInstance = NULL;
static HWND 		_hWnd;
static HWND 		_hParentWnd;
static BOOL 		_bToggle;

static char			_Code[32] = "";	//�O����͂����R�[�h��ۑ��p
static Sint32		_SetOk = -1;	//�߂�l�B�ݒ芮���Ȃ�1�BEDIT�󗓂Őݒ芮��(Continuous����)�Ȃ�2�B�L�����Z���Ȃ�-1�B���ݒ蒆��0�B
static Uint32*		_pMpr;			//�߂�l�ݒ�p
static Uint32*		_pAddr;			//
static Uint8*		_pData;			//
static BOOL*		_pbContinuous;	//
static Sint32*		_pSetOk = 0;	//


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
	Uint32	wndW = _FontWidth  * LINE_LEN + 3;
	Uint32	wndH = _FontHeight * N_LINES - 2;
	int		y;

	SetRect(&rc, 0, 0, wndW, wndH);
	AdjustWindowRectEx(&rc, GetWindowLong(hWnd, GWL_STYLE),
						GetMenu(hWnd) != NULL, GetWindowLong(hWnd, GWL_EXSTYLE));
	wndW = rc.right - rc.left;
	wndH = rc.bottom - rc.top;
	GetWindowRect(_hParentWnd, &rc);
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
	HDC 			hDC;
	HFONT			hFont;
	HFONT			hFontOld;
	PAINTSTRUCT 	ps;
	Uint32			x;
	Uint32			y;

	/* �`�揀�� */
	hDC = BeginPaint(hWnd, &ps);
	SetBkMode(hDC, OPAQUE);	//�����̔w�i��h��Ԃ�
	SetBkColor(hDC, RGB(64,128,64));
	SetTextColor(hDC, RGB(240,240,240));
	hFont = (HFONT)GetStockObject(OEM_FIXED_FONT);
	hFontOld = (HFONT)SelectObject(hDC, hFont);

	x = _FontWidth*3 -4;
	y = _FontHeight -4;
	TextOut(hDC, x, y, "Input \"<mpr><addr>:<value><cont>\"  e.g.)\"F62000:255+\"", 53);

	x = _FontWidth*3 -6;
	y += _FontHeight;
	TextOut(hDC, x, y, "( <value>=decimal. If <cont>='+' then keeping value. )", 54);

	/* �I������ */
	EndPaint(hWnd, &ps);
	SelectObject(hDC, hFontOld);
	DeleteObject(hFont);
	ReleaseDC(hWnd, hDC);
}


//Close�����Bv2.70�X�V
static LRESULT CALLBACK
writeMemory_close()
{
	WRITEMEM_Deinit();
	if (_bToggle)
		APP_ToggleFullscreen(); //�t���X�N���[���ɖ߂��B
	return 0;
}

static LRESULT CALLBACK
SetButtonPushed()
{
	char	code[32];
	char	buf[32];
	char*	pBuf;
	char	buf2[32];

	GetWindowText(_hWndC[EDIT_CODE], code, 32);
	if (code[0] == 0) //�󗓂�SET�{�^�����������ꍇ
	{
		_SetOk = 2; //�󗓂Őݒ芮���̈�
		strcpy(_Code, code); //���͂����R�[�h��ۊ�
		return writeMemory_close();
	}

	strcpy(buf, code);
	pBuf =strchr(buf, ':');
	if (pBuf != NULL)
	{
		*pBuf = 0;
		if (strlen(buf) == 6)
		{
			strncpy(buf2, buf, 2);
			*(buf2 + 2) = 0;
			*_pMpr = (Uint32)strtol(buf2, NULL, 16);
			strncpy(buf2, buf+2, 4);
			*(buf2 + 4) = 0;
			*_pAddr = (Uint32)strtol(buf2, NULL, 16);
			strcpy(buf2, pBuf+1);
			pBuf =strchr(buf2, '+');
			if (pBuf != NULL)
			{
				*_pbContinuous = TRUE;
				*pBuf = 0;
			}
			else
				*_pbContinuous = FALSE;
			pBuf =strchr(buf2, 'X');
			if (pBuf != NULL) //16�i���w��̏ꍇ
			{
				strcpy(buf2, pBuf+1);
				*_pData = (Uint8)strtol(buf2, NULL, 16);
				_SetOk = 1; //�ݒ芮���̈�
				strcpy(_Code, code); //���͂����R�[�h��ۊ�
				return writeMemory_close();
			}
			if (strlen(buf2) <= 3)
			{
				buf[0] = buf2[0];
				buf[1] = 0;
				if (strtol(buf, NULL, 16) < 10) //�ꌅ�ڂ�16�i���̕���(A-F)�������Ă��Ȃ����
				{
					buf[0] = buf2[1];
					buf[1] = 0;
					if (strtol(buf, NULL, 16) < 10) //�񌅖ڂ�16�i���̕���(A-F)�������Ă��Ȃ����
					{
						*_pData = (Uint8)atoi(buf2);
						_SetOk = 1; //�ݒ芮���̈�
						strcpy(_Code, code); //���͂����R�[�h��ۊ�
						return writeMemory_close();
					}
					else
						MessageBox(_hWnd, "Error. \"<value>\" should be 1-3 Digits (Decimal).    \nIf Hexadecimal is used, add \"0x\".    ", "Ootake", MB_OK);
				}
				else
					MessageBox(_hWnd, "Error. \"<value>\" should be 1-3 Digits (Decimal).    \nIf Hexadecimal is used, add \"0x\".    ", "Ootake", MB_OK);
			}
			else
				MessageBox(_hWnd, "Error. \"<value>\" should be 1-3 Digits (Decimal).    \nIf Hexadecimal is used, add \"0x\".    ", "Ootake", MB_OK);
		}
		else
			MessageBox(_hWnd, "Error. \"<mpr><addr>\" should be 6 Digits (Hexadecimal).    ", "Ootake", MB_OK);
	}
	else
		MessageBox(_hWnd, "Error. Separator[ : ] is not found.    ", "Ootake", MB_OK);

	//�G���[�_�C�A���O���o������̏���
	//MAINBOARD_ScreenUpdate(TRUE); //�G���[�_�C�A���O�\�������ꍇ�A���C����ʂ������̂ōX�V�B�����������WriteMemory�t�H�[�����̂���u������̂ŃJ�b�g
	SetFocus(GetDlgItem(_hWnd, EDIT_CODE));//�G�f�B�b�g�{�b�N�X�Ƀt�H�[�J�X

	return 0;
}

//EDIT�R���|�[�l���g��ł̃L�[���͂����m���邽�߂̃t�b�N
static LRESULT CALLBACK
EditProc(
	HWND		hWnd,
	UINT		uMsg,
	WPARAM		wParam,
	LPARAM		lParam)
{
	if (uMsg == WM_CHAR) //�L�[���͂������ςɂ��邽��WM_KEYDOWN�łȂ�WM_CHAR���g�p
	{
		//Esc�L�[��������Ă��������
		if (wParam == VK_ESCAPE)
			return SetButtonPushed(); //0��Ԃ����Ƃ�WM_CHAR�������ςɁB�r�[�v����炳���ɍςށB
		//Enter�L�[��������Ă�����[SET]�{�^�������������Ƃɂ���
		if (wParam == VK_RETURN)
			return SetButtonPushed(); //0��Ԃ����Ƃ�WM_CHAR�������ςɁB�r�[�v����炳���ɍςށB
	}
	return CallWindowProc(_WPEdit, hWnd, uMsg, wParam, lParam);
} 


static LRESULT CALLBACK
writeMemory_wnd_proc(
	HWND		hWnd,
	UINT		uMsg,
	WPARAM		wParam,
	LPARAM		lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		EnableWindow(_hParentWnd, FALSE);//Kitao�ǉ��B�e�E�C���h�E�𖳌������ă��[�_���ɁB
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

	case WM_SIZE:
		if (_bToggle) //DirectDraw�Ńt���X�N���[���������ꍇ�A�ؑ֌�ɃE�B���h�E�̃A�N�e�B�u�����K�v
		{
			SetForegroundWindow(_hParentWnd);
			SetForegroundWindow(hWnd);
		}
		break;

	case WM_PAINT:
		update_window(hWnd);
		SetFocus(GetDlgItem(hWnd, EDIT_CODE));//�G�f�B�b�g�{�b�N�X�Ƀt�H�[�J�X
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			return writeMemory_close();
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case BUTTON_CLEAR:
				SetWindowText(_hWndC[EDIT_CODE], "");//�N���A
				SetFocus(GetDlgItem(hWnd, EDIT_CODE));//�G�f�B�b�g�{�b�N�X�Ƀt�H�[�J�X
				break;

			case BUTTON_SET:
				//�߂�l��ݒ�
				SetButtonPushed();
				break;
		}
		break;

	case WM_CLOSE:
		return writeMemory_close();
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


static BOOL
writeMemory_main()
{
	WNDCLASS	wc;
	HWND		hWnd;
	RECT		rc;
	Uint32		x;
	Uint32		y;
	HWND		hWndTmp;
	
	ZeroMemory(&wc, sizeof(wc));
	wc.style		 = 0;
	wc.lpfnWndProc	 = writeMemory_wnd_proc;
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
		WS_SYSMENU | WS_CAPTION,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		WINMAIN_GetHwnd(),
		NULL,
		_hInstance,
		NULL
	);

	if (hWnd == NULL)
		return FALSE;

	_hWnd = hWnd;

	//�G�f�B�b�g�{�b�N�X���쐬
	x = _FontWidth*11;
	y = _FontHeight*3+_FontHeight/2-2;
	_hWndC[1] = CreateWindow(
		"EDIT", "",
		WS_CHILD | WS_VISIBLE | ES_UPPERCASE,
		x, y+4, _FontWidth*18+_FontWidth/2, _FontHeight+2,
		_hWnd, (HMENU)EDIT_CODE, _hInstance, NULL
	);
	_WPEdit = (WNDPROC)GetWindowLong(_hWndC[1], GWL_WNDPROC); //�L�[�t�b�N���邽�߂Ɍ��̃v���V�[�W���A�h���X��ޔ�
	SetWindowLong(_hWndC[1], GWL_WNDPROC, (LONG)EditProc);	  //���O�̃t�b�N�ɏ�������
	SetWindowText(_hWndC[1], _Code);//�O��̓��͕�������f�t�H���g�ɂ���
	SendMessage(_hWndC[1], WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));//�t�H���g��ݒ�
	//SendMessage(_hWndC[1], EM_SETSEL, (WPARAM)0, (LPARAM)-1);//������I����Ԃɂ���
	SendMessage(_hWndC[1], EM_SETSEL, (WPARAM)32, (LPARAM)32);//�J�[�\�����E�[�֎����Ă���

	//Clear�{�^�����쐬
	x = _FontWidth*30+2;
	y = _FontHeight*3+_FontHeight/2-2;
	hWndTmp = CreateWindow(
		"BUTTON", "Clear",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x, y, _FontWidth*11, _FontHeight+_FontHeight/2,
		_hWnd, (HMENU)BUTTON_CLEAR, _hInstance, NULL
	);
	SendMessage(hWndTmp, WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));//�t�H���g��ݒ�

	//SET�{�^�����쐬
	x = _FontWidth*41+_FontWidth/2;
	y = _FontHeight*3+_FontHeight/2-2;
	hWndTmp = CreateWindow(
		"BUTTON", "Set",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x, y, _FontWidth*11, _FontHeight+_FontHeight/2,
		_hWnd, (HMENU)BUTTON_SET, _hInstance, NULL
	);
	SendMessage(hWndTmp, WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));//�t�H���g��ݒ�

	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);
	GetWindowRect(_hWnd, &rc);
	SetWindowPos(_hWnd, HWND_TOP, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_FRAMECHANGED);
	ImmAssociateContext(_hWnd, 0); //IME�𖳌��ɂ���

	return TRUE;
}


BOOL
WRITEMEM_Init(
	HWND		hWnd,
	HINSTANCE	hInstance,
	Uint32*		mpr,
	Uint32*		addr,
	Uint8*		data,
	BOOL*		bContinuous,
	Sint32*		setOk)
{
	if (_hInstance != NULL)
		WRITEMEM_Deinit();

	_hParentWnd = hWnd;
	_hInstance = hInstance;

	_pMpr = mpr;
	_pAddr = addr;
	_pData = data;
	_pbContinuous = bContinuous;
	_pSetOk	= setOk;
	_SetOk	= -1; //�L�����Z��

	return writeMemory_main();
}


void
WRITEMEM_Deinit()
{
	if (_hInstance != NULL)
	{
		DestroyWindow(_hWnd);
		_hWnd = NULL;
		UnregisterClass(_pCaption, _hInstance);
		_hInstance = NULL;
		
		DeleteObject(_hFontB); //�{�^���p�t�H���g���J��
		DeleteObject(_hMyb); //�u���V���J��
		
		//���C���E�B���h�E��Enable�ɖ߂��B
		if (APP_GetFullScreen())
			ShowWindow(WINMAIN_GetHwnd(), SW_SHOWNORMAL);
		EnableWindow(WINMAIN_GetHwnd(), TRUE);
		//�e�E�B���h�E�Ƀt�H�[�J�X��߂��O�ʂɁB
		EnableWindow(_hParentWnd, TRUE);
		SetForegroundWindow(_hParentWnd);
		
		*_pSetOk = _SetOk; //�߂�l��ݒ�B���̏u�Ԃɐe�E�B���h�E�̃X���b�h�͓����o���B
	}
}


char*
WRITEMEM_GetCode()
{
	return _Code;
}

void
WRITEMEM_ClearCode()
{
	strcpy(_Code, "");
}
