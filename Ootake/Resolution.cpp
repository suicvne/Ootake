/******************************************************************************
Ootake

 [Resolution.c]
	�t���X�N���[���̉𑜓x��ݒ肷��t�H�[��

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
#include "resolution.h"
#include "Resource.h"
#include "WinMain.h"
#include "App.h"

#define LINE_LEN	37
#define N_LINES 	5

#define COMBOBOX_RESOLUTION		1
#define BUTTON_SET			2


static HBRUSH		_hMyb; //����u���V�F
static HFONT		_hFontB; //�{�^���p�t�H���g

static Uint32		_FontWidth;
static Uint32		_FontHeight;
static const char*	_pCaption = "\"Ootake\" Resolution setting";
static HINSTANCE	_hInstance = NULL;
static HWND 		_hWnd;

static Sint32		_EnumN; //�񋓂����\���\�ȉ𑜓x�̐�
static Sint32 		_EnumWidth[256]; //�񋓂����\���\�ȉ𑜓x(��)���i�[�p
static Sint32 		_EnumHeight[256]; //�񋓂����\���\�ȉ𑜓x(�c)���i�[�p

static Sint32		_SetNum; //1�`3
static Sint32		_ResolutionWidth = -1; //�߂�l(���肵���ꍇ1�ȏ�̒l���Ԃ����)�B�L�����Z���Ȃ�-1�B���ݒ蒆��0�B�f�t�H���g�ɖ߂��Ȃ�1�B
static Sint32*		_pResolutionWidth;
static Sint32		_ResolutionHeight = -1; //�߂�l(���肵���ꍇ1�ȏ�̒l���Ԃ����)�B�L�����Z���Ȃ�-1�B���ݒ蒆��0�B�f�t�H���g�ɖ߂��Ȃ�1�B
static Sint32*		_pResolutionHeight;


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
	RECT		rc;
	Uint32		wndW = _FontWidth  * LINE_LEN +2;
	Uint32		wndH = _FontHeight * N_LINES -2 + _FontHeight/2;

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
	char			buf[16+1];

	/* �`�揀�� */
	hDC = BeginPaint(hWnd, &ps);
	SetBkMode(hDC, OPAQUE);	//�����̔w�i��h��Ԃ�
	SetBkColor(hDC, RGB(64,128,64));
	SetTextColor(hDC, RGB(240,240,240));
	hFontOld = (HFONT)SelectObject(hDC, _hFontB);

	sprintf(buf, "FullScreen < %d >", (int)_SetNum);
	TextOut(hDC, _FontWidth*2+1, _FontHeight-2, buf, 16);

	/* �I������ */
	EndPaint(hWnd, &ps);
	SelectObject(hDC, hFontOld);
	ReleaseDC(hWnd, hDC);
}


static LRESULT CALLBACK
resolution_wnd_proc(
	HWND		hWnd,
	UINT		uMsg,
	WPARAM		wParam,
	LPARAM		lParam)
{
	Sint32	a;

	switch(uMsg)
	{
	case WM_CREATE:
		EnableWindow(WINMAIN_GetHwnd(), FALSE);//���C���E�B���h�E�𖳌������ă��[�_���ɁB
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
		{
			RESOLUTION_Deinit();
			return 0;
		}
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case COMBOBOX_RESOLUTION:
				if (HIWORD(wParam) == CBN_CLOSEUP)
					SetFocus(GetDlgItem(hWnd, BUTTON_SET));//OK�{�^���Ƀt�H�[�J�X
				break;
			case BUTTON_SET:
				a = SendMessage(GetDlgItem(hWnd, COMBOBOX_RESOLUTION), CB_GETCURSEL, 0, 0);
				_ResolutionWidth = _EnumWidth[a]; //�߂�l��ݒ�
				_ResolutionHeight = _EnumHeight[a]; //�߂�l��ݒ�
				RESOLUTION_Deinit();
				return 0;
		}
		break;

	case WM_CLOSE:
		RESOLUTION_Deinit();
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


static BOOL
resolution_main()
{
	WNDCLASS	wc;
	HWND		hWnd;
	RECT		rc;
	Uint32		x;
	Uint32		y;
	HWND		hWndTmp;
	DEVMODE		dm[1024];
	int			i,j,k;
	char		buf[256];
	BOOL		ok;
	Sint32		w,h;

	ZeroMemory(&wc, sizeof(wc));
	wc.style		 = 0;
	wc.lpfnWndProc	 = resolution_wnd_proc;
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

	//�X�N���[�����[�h�p�R���{�{�b�N�X���쐬
	x = _FontWidth*2;
	y = _FontHeight*2;
	hWndTmp = CreateWindow(
		"COMBOBOX", "",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
		x, y, _FontWidth*23, _FontHeight*16,
		_hWnd, (HMENU)COMBOBOX_RESOLUTION, _hInstance, NULL
	);
	SendMessage(hWndTmp, WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));//�t�H���g��ݒ�
	SendMessage(hWndTmp, CB_ADDSTRING, 0, (LPARAM)"Default");
	//�f�B�X�v���C�̗��p�\�ȉ𑜓x��񋓂���
	_EnumN = 0;
	_EnumWidth [0] = 1; //�f�t�H���g
	_EnumHeight[0] = 1; //  ��I�������ꍇ�̖߂�l
	memset(&dm, 0, sizeof(DEVMODE));
    for (i=0; i<1024; i++)
    {
		dm[i].dmSize = sizeof(DEVMODE);
		if (!EnumDisplaySettings(NULL,i,&dm[i])) break;
	}
	for (j=0; j<i; j++)
	{
		if (dm[j].dmBitsPerPel >= 16)
		{
			ok = TRUE;
			for (k=1; k<=_EnumN; k++)
				if ((dm[j].dmPelsWidth == _EnumWidth[k])&&(dm[j].dmPelsHeight == _EnumHeight[k])) //���łɗ񋓍ς݂̉𑜓x
				{
					ok = FALSE;
					break;
				}
			if (ok)
				if (_EnumN < 255)
				{
					_EnumN++;
					_EnumWidth[_EnumN] = dm[j].dmPelsWidth;
					_EnumHeight[_EnumN] = dm[j].dmPelsHeight;
					sprintf(buf, "%d x %d", (int)dm[j].dmPelsWidth, (int)dm[j].dmPelsHeight);
					SendMessage(hWndTmp, CB_ADDSTRING, 0, (LPARAM)buf);
				}
		}
	}
	if (((_SetNum == 1)&&(APP_GetCustomWidth1() == 640)&&(APP_GetCustomHeight1() == 480))||
		((_SetNum == 2)&&(APP_GetCustomWidth2() == 320)&&(APP_GetCustomHeight2() == 240))||
		((_SetNum == 3)&&(APP_GetCustomWidth3() == 400)&&(APP_GetCustomHeight3() == 300)))
			SendMessage(hWndTmp, CB_SETCURSEL, 0, 0);
	else
	{
		switch (_SetNum)
		{
			case 1:
				w = APP_GetCustomWidth1();
				h = APP_GetCustomHeight1();
				break;
			case 2:
				w = APP_GetCustomWidth2();
				h = APP_GetCustomHeight2();
				break;
			case 3:
				w = APP_GetCustomWidth3();
				h = APP_GetCustomHeight3();
				break;
			default: //�R���p�C���G���[���
				w = 0;
				h = 0;
				break;
		}
		for (k=1; k<=_EnumN; k++)
			if ((w == _EnumWidth[k])&&(h == _EnumHeight[k])) //���łɗ񋓍ς݂̉𑜓x
				break;
		if (k>_EnumN) k=0;
		SendMessage(hWndTmp, CB_SETCURSEL, k, 0);
	}

	//�{�^�����쐬
	x = _FontWidth*26;
	y = _FontHeight*2;
	hWndTmp = CreateWindow(
		"BUTTON", "Set",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x, y, _FontWidth*8, _FontHeight*2-6,
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
RESOLUTION_Init(
	HINSTANCE	hInstance,
	Sint32		setNum,
	Sint32*		resolutionWidth,
	Sint32*		resolutionHeight)
{
	if (_hInstance != NULL)
		RESOLUTION_Deinit();

	_hInstance = hInstance;

	_SetNum = setNum;

	_pResolutionWidth = resolutionWidth;
	_ResolutionWidth = -1;//�L�����Z��
	_pResolutionHeight = resolutionHeight;
	_ResolutionHeight = -1;//�L�����Z��

	return resolution_main();
}


void
RESOLUTION_Deinit()
{
	if (_hInstance != NULL)
	{
		DestroyWindow(_hWnd);
		_hWnd = NULL;
		UnregisterClass(_pCaption, _hInstance);
		_hInstance = NULL;
		
		DeleteObject(_hFontB); //�{�^���p�t�H���g���J��
		DeleteObject(_hMyb); //�u���V���J��
		
		//���C���E�B���h�E�Ƀt�H�[�J�X��߂��O�ʂɁB
		EnableWindow(WINMAIN_GetHwnd(), TRUE);
		SetForegroundWindow(WINMAIN_GetHwnd());
		
		*_pResolutionWidth = _ResolutionWidth; //�߂�l��ݒ�
		*_pResolutionHeight = _ResolutionHeight; //�߂�l��ݒ�B���̏u�Ԃ�App.c �ɐ��䂪�߂�B
	}
}

