/******************************************************************************
Ootake
�EVista��AERO���ɑΉ����邽�߁ADirect3D�ł̕`��������B����A�@�\�I�ɂ�
  ScreenDD.c(DirectDraw�`��)�Ɠ����B�J���[��32�r�b�g�̂ݑΉ��Ƃ���B

Copyright(C)2006-2016 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

******************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE

#define DIRECT3D_VERSION	0x0900

#define SOURCE_PITCH 		512

#include <D3D9.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "ScreenD3D.h"
#include "Screen.h"
#include "WinMain.h"
#include "App.h"
#include "MainBoard.h"
#include "Printf.h"

extern Uint32 _Gamma[8]; //Kitao�ǉ��B�K���}���v�Z�������l�����Ă����Bv1.14�������BUint32�ɂ����ق����������������B
extern Uint32 _GammaS80[8]; //Kitao�ǉ��B�X�L�������C��80%�p
extern Uint32 _GammaS90[8]; //Kitao�ǉ��B�X�L�������C��90%�p
extern Uint32 _MonoTableR[256]; //���m�N���ϊ��p�e�[�u���B�������̂��ߕK�v�Bv2.28
extern Uint32 _MonoTableG[256]; //
extern Uint32 _MonoTableB[256]; //

//Kitao�ǉ��BDirect3D9Ex�p��`�Bv2.21
static HINSTANCE _hD3D9Dll;
typedef HRESULT (WINAPI* FuncDirect3DCreate9Ex) (UINT, IDirect3D9Ex **);
static FuncDirect3DCreate9Ex _FuncDirect3DCreate9Ex;

static LPDIRECT3D9				_pD3D = NULL; //Direct3D object
static LPDIRECT3DDEVICE9		_pD3DDev = NULL; //�f�o�C�X
static IDirect3D9Ex*			_pD3DEx = NULL; //Direct3DEx object�Bv2.21�ǉ��BWin7/Vista�ŕ`��x�������Ȃ����邽�߂ɕK�v�B
static IDirect3DDevice9Ex*		_pD3DDevEx = NULL; //����
static LPDIRECT3DSURFACE9		_pD3DSBack = NULL; //�o�b�N�o�b�t�@(�����ɓ]������Ǝ��ۂɕ`�悳���)
static LPDIRECT3DSURFACE9		_pD3DSGame = NULL; //���C����ʗp
static LPDIRECT3DSURFACE9		_pD3DSText = NULL; //�e�L�X�g���b�Z�[�W,FPS�\���p
static D3DPRESENT_PARAMETERS	_pD3DParam;

static BOOL		_bOldVideoChip = FALSE; //�Â��r�f�I�`�b�v(�r�f�I�J�[�h)�̏ꍇTRUE�ɁBv2.19

static LONG		_SurfacePitch = 0;

static Sint32	_Width;
static Sint32	_Height;
static Sint32	_Magnification;
static Uint32	_Flags;
static HWND		_hWnd;
static Uint16*	_pScreenPixels;
static BOOL		_bChangedFullScreen = FALSE;
static Sint32	_GameLeft;   //print_message()�ŕ\���ʒu����̂��߂ɁA�Q�[����ʓ]����̍��W���T���Ă����B
static Sint32	_GameRight;  //
static Sint32	_GameTop;    //
static Sint32	_GameBottom; //

//Win9x�p�ϐ�
static DWORD	_PrevWidth;
static DWORD	_PrevHeight;
static DWORD	_PrevBitsPerPixel;
static DWORD	_PrevFrequency;

static DWORD	_LastTimeSyncTime; //�O��Sync�����Ƃ��̃^�C�}�[�J�E���g
static DWORD	_LastTimeSyncTime3; //3�t���[���P�ʂł́A�O��Sync�����Ƃ��̃^�C�}�[�J�E���g�Bv2.43
static DWORD	_Frame; //3�t���[���P�ʂ��v�邽�߂ł́A�O��Sync�����Ƃ��̃^�C�}�[�J�E���g�Bv2.43
static Sint32	_SyncAjust; //VSync���I�t�̂Ƃ���1/60�b�Ԋu�ɂł��邾���߂Â��邽�߂̕ϐ��Bv1.67
static Sint32	_SyncAjust3; //v2.43�ǉ�
static BOOL		_bSyncTo60HzScreen = TRUE;

static LONG		_Pitch;
static LONG		_Pitch2; //pitch��2�{�̒l�����Ă����B���x�A�b�v�p�B
static LONG		_Pitch3; //pitch��3�{�̒l�����Ă����B���x�A�b�v�p�B
static LONG		_Pitch4; //pitch��4�{�̒l�����Ă����B���x�A�b�v�p�B
static Uint32*	_pPixels; //v2.13�X�V�B32bit�P�ʂň����悤�ɂ����B(������)

static char*	_pMessageText = ""; //�e�L�X�g���b�Z�[�W�\���p�o�b�t�@�B�k���i�擪��0�j�̏ꍇ�A��\���B
static char*	_pCenterText = ""; //�Z���^�[�e�L�X�g���b�Z�[�W�\���p�o�b�t�@�B�k���i�擪��0�j�̏ꍇ�A��\���B


//D3D�f�o�C�X�̊J������
static void
d3dSurfaceRelease()
{
	if (_pD3DSText != NULL)
	{	_pD3DSText->Release();	_pD3DSText = NULL;	}

	if (_pD3DSGame != NULL)
	{	_pD3DSGame->Release();	_pD3DSGame = NULL;	}

	if (_pD3DSBack != NULL)
	{	_pD3DSBack->Release();	_pD3DSBack = NULL;	}
}

//Direct3D�p�X�N���[�������S�ɊJ�����܂��B
void
SCREEND3D_Deinit()
{
	if (_pD3D != NULL)
	{
		d3dSurfaceRelease();
		if (APP_GetWindowsVista()) //Vista�ȍ~��Direct3D9Ex���g�����ꍇ
		{
			if (_pD3DDevEx != NULL)
			{
				_pD3DDevEx->Release(); //Ex���ŊJ�����s��
				_pD3DDevEx = NULL;
			}
			_pD3DEx->Release(); //Ex���ŊJ�����s��
			_pD3DEx = NULL;
		}
		else //Vista���O��Windows�̏ꍇ�A���ʂɊJ���B
		{
			if (_pD3DDev != NULL)
				_pD3DDev->Release();
			_pD3D->Release();
		}
		_pD3DDev = NULL;
		_pD3D = NULL;
	}
	if (APP_GetWindowsVista())
		FreeLibrary(_hD3D9Dll); //DLL���J��
}

//v2.70�X�V
static HRESULT
d3dCreate()
{
	HRESULT		hr;

	if (APP_GetWindowsVista())
	{	//v2.21�ǉ�
		hr = _pD3DEx->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
									 &_pD3DParam, NULL, &_pD3DDevEx); //v2.70�X�V�BHARDWARE�����̂ق������ƂȂ��x�����Ȃ��C���B
		if (FAILED(hr))
		{
			hr = _pD3DEx->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										 &_pD3DParam, NULL, &_pD3DDevEx); //v2.71�X�V�B�C���e���̌Â��`�b�v�ȂǂŃV�F�[�_�[�������̏ꍇ�G���[�ɂȂ�̂ł��̏ꍇSOFTWARE�����B
			if (FAILED(hr))
				MessageBox(_hWnd, "ERROR: DIRECT3D::CreateDeviceEx() failed.    ", "Ootake", MB_OK);
		}
		_pD3DDevEx->SetMaximumFrameLatency(0); //�x�����ŏ����ɗ}����BMSDN�̋L�ڂɂ���0���ƃA�_�v�^�̊���l�ɂȂ�炵�����A1���0�̂ق���1�t���[���x�������Ȃ�(GeForce)�̂�0�ɁBAero�I�t�{����ł����XP���ɁB
		_pD3DDev = _pD3DDevEx; //�^�L���X�g�B���Ƃ͒ʏ��Direct3D9�ɔC����B
	}
	else
	{
		hr = _pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
								 &_pD3DParam, &_pD3DDev); //v2.70�X�V�BHARDWARE�����̂ق������ƂȂ��x�����Ȃ��C���B
		if (FAILED(hr))
			hr = _pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									 &_pD3DParam, &_pD3DDev); //v2.71�X�V�B�C���e���̌Â��`�b�v�ȂǂŃV�F�[�_�[�������̏ꍇ�G���[�ɂȂ�̂ł��̏ꍇSOFTWARE�����B
	}
	return hr;
}

static HRESULT
d3dDevReset()
{
	int			a;
	HRESULT		hr;

	if (_pD3DDev == NULL) //���쐬�̏ꍇ
	{
		hr = d3dCreate(); //2.70�X�V
	}
	else //���łɍ쐬�ς݂̏ꍇ
	{
		d3dSurfaceRelease();
		hr = _pD3DDev->Reset(&_pD3DParam);
		if (FAILED(hr)) //���Z�b�g�Ɏ��s�������蒼��
		{
			_pD3DDev->Release();
			_pD3DDev = NULL;
			hr = d3dCreate(); //2.70�X�V
		}
	}
	if (FAILED(hr))
		return hr;

	//�o�b�N�o�b�t�@�[�̃A�h���X���擾
	_pD3DDev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &_pD3DSBack);

    //���C��(�Q�[��)��ʕ\���p�I�t�X�N���[���T�[�t�F�X���쐬����
	if (_Magnification == 1)
		a = 512 + 8; //��+8�͉E�[�ɃN���A�}�[�W�����������ݗp�BDirect3D�ł͉E�[�����ŃN���A���Ă����Ȃ��ƃt�B���^�����̃o�C�g�܂ŎQ�Ƃ���̂ŉE�[������邱�Ƃ�����悤���Bv2.06�X�V�B+1�ő��v�Ǝv�����O�̂���8�̔{���ɂ����B
	else //2�{�ȏ�͑S�ĉ�2�{�B���x�A�b�v�{�������邱�ƂœK�x�Ƀo�C���j�A�t�B���^���|���肢�������ɂȂ�
		a = 512*2 + 8; //��+8�͉E�[�ɃN���A�}�[�W�����������ݗp�BDirect3D�ł͉E�[�����ŃN���A���Ă����Ȃ��ƃt�B���^�����̃o�C�g�܂ŎQ�Ƃ���̂ŉE�[������邱�Ƃ�����悤���Bv2.06�X�V�B+1�ő��v�Ǝv�����O�̂���8�̔{���ɂ����B
	_pD3DDev->CreateOffscreenPlainSurface(a, 256*_Magnification, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &_pD3DSGame, NULL); //D3DPOOL_DEFAULT�ɂ��Ȃ���StretchRect���g���Ȃ��B

    //�e�L�X�g�\���p�I�t�X�N���[���T�[�t�F�X���쐬����
	_pD3DDev->CreateOffscreenPlainSurface(512*2, 32, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &_pD3DSText, NULL);

	return hr;
}

//Direct3D�p�X�N���[�������������܂��B
BOOL
SCREEND3D_Init(
	Sint32		width,
	Sint32		height,
	Sint32		magnification,
	Uint32		flags)
{
	DEVMODE					dm;
	D3DDISPLAYMODE			dmode;
	D3DADAPTER_IDENTIFIER9	di;
	HRESULT					hr;

	//�p�����[�^��ۊ�
	_Width = width;
	_Height = height;
	_Magnification = magnification;
	_Flags = flags;
	_hWnd =	WINMAIN_GetHwnd();

	if (APP_GetWindowsVista()) //Vista�ȍ~��Direct3D9Ex���g������Ȃ��
	{	//v2.21�ǉ�
		_hD3D9Dll = LoadLibrary("d3d9.dll"); //Vista���O��Windows�ŃG���[���N�����Ȃ����߁A���I��DLL�����[�h���Ċ֐����������g�p����B
		_FuncDirect3DCreate9Ex = (FuncDirect3DCreate9Ex)GetProcAddress(_hD3D9Dll, "Direct3DCreate9Ex");
		_FuncDirect3DCreate9Ex(D3D_SDK_VERSION, &_pD3DEx);
		_pD3D = _pD3DEx;
	}
	else //XP�ȑO
		_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (_pD3D == NULL)
	{
		MessageBox(_hWnd, "ERROR: DIRECT3D::Direct3DCreate9() failed.    ", "Ootake", MB_OK);
		return FALSE;
	}

	//�t���X�N���[���̏ꍇ�A ��ʂ̉𑜓x��ݒ肵�A�E�B���h�E������ɔz�u����ʑS��̑傫���ɂ���B
	//	��Direct3D9�̃t���X�N���[�����[�h�́A���j���[�⑼�̃_�C�A���O�\��������ɏo���Ȃ��̂Ŏg���Ȃ��B�蓮�Ńt���X�N���[���ɐ؂�ւ��Ă���E�B���h�E���[�h���g���B
	//										 �^�C�}�[�̐i�ݕ������������Ȃ�s����A�E�B���h�E���[�h�Ȃ����ł���B
	if (flags & SCREEN_FFULLSCREEN) //�t���X�N���[�����[�h�Ȃ�
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
		dm.dmBitsPerPel = 32;
		dm.dmDisplayFrequency = 60;
		dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;
		if ((APP_GetResolutionAutoChange())&&(_bChangedFullScreen))
			hr = ChangeDisplaySettings(&dm, 0); //�ݒ���T�����ɐؑցB�ꕔ�̊��Őؑ֎��̂������������Bv2.23�B�Â�RADEON�Ő؂�ւ����ɉ摜�̗�������m�F�ς݁Bv2.65
		else //�ʏ�
			ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
		WINMAIN_SetFullScreenWindow(width, height);//v2.23�ǉ��B���̃^�C�~���O�ŁA�E�B���h�E�X�^�C���̕ύX���s���悤�ɂ����B�p���[�̖����}�V���ł�DirectX�������Ɏ��Ԃ��|����̂ł��̃^�C�~���O�ŉ�ʂ𐮂����ق����ǂ������B
		_bChangedFullScreen = TRUE;
	}
	else //�E�B���h�E���[�h�Ȃ�
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
			Sleep(1000); //�f�X�N�g�b�v�ɖ߂鏈�������S�ɏI���܂ŔO�̂��߂ɃE�F�C�g������B������DirecDraw�̂Ƃ��̂悤��Direct3D�̃f�o�C�X�̍쐬���s�������Ȃ̂ŁB
		}
		WINMAIN_SetNormalWindow(width, height);//v2.23�ǉ��B���̃^�C�~���O�ŁA�E�B���h�E�X�^�C���̕ύX���s���悤�ɂ����B�p���[�̖����}�V���ł�DirectX�������Ɏ��Ԃ��|����̂ł��̃^�C�~���O�ŉ�ʂ𐮂����ق����ǂ������B
		APP_WindowWithinScreen(); //�E�B���h�E����ʂ���͂ݏo���Ă����ꍇ�A��ʓ��Ɏ��܂�悤�Ɉړ�����B
		_bChangedFullScreen = FALSE;
	}

	//�f�B�X�v���C���[�h���擾�BWindow���[�h�ɂ�VSync�\���ǂ����̔��f���s�����߂ɗ��p
	_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dmode);

	//�f�B�X�v���C�A�_�v�^(�r�f�I�`�b�v)�̏����擾�Bv2.19
	_pD3D->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &di);
	APP_StrToLower(di.Description);
	//PRINTF("VideoCard = %s", di.Description); //Test�p
	if ((strstr(di.Description, "radeon ve") != NULL)||
		(strstr(di.Description, "radeon 2") != NULL)||
		(strstr(di.Description, "radeon 3") != NULL)||
		(strstr(di.Description, "radeon 7") != NULL)||
		(strstr(di.Description, "radeon 8") != NULL)||
		(strstr(di.Description, "radeon 90") != NULL)||
		(strstr(di.Description, "radeon 92") != NULL)||
		(strstr(di.Description, "wonder ve") != NULL)||
		(strstr(di.Description, "wonder 7") != NULL)||
		(strstr(di.Description, "wonder 90") != NULL)||
		(strstr(di.Description, "wonder 92") != NULL))
		{
			//PRINTF("Old! VideoCard = %s ", di.Description); //Test�p
			_bOldVideoChip = TRUE; //�Â��r�f�I�`�b�v
		}

	//Direct3D�f�o�C�X���쐬�B���j���[��_�C�A���O�\���̂��߁A�t���X�N���[�������E�B���h�E�f�o�C�X�Ƃ��č쐬����B
	ZeroMemory(&_pD3DParam, sizeof(_pD3DParam));
	_pD3DParam.hDeviceWindow = _hWnd;
	_pD3DParam.BackBufferWidth = width;
	_pD3DParam.BackBufferHeight = height;
	_pD3DParam.BackBufferFormat = D3DFMT_X8R8G8B8; //32�r�b�g�J���[��p
	_pD3DParam.BackBufferCount = 1;
	_pD3DParam.Windowed = TRUE; //Window���[�h�B�Q�l�FWinodwed��TRUE�̂Ƃ��Ƀ��t���b�V�����[�g��ݒ肷���Create�G���[
	if ((APP_GetSyncTo60HzScreen())&&((dmode.RefreshRate == 60)||(dmode.RefreshRate == 59)||(dmode.RefreshRate == 61))||
		(APP_GetWindowsAutoVSyncBool())) //���t���b�V�����[�g��60Hz(59��61���܂�)��Windows����V-Sync�ݒ�̂Ƃ�����VSync��OK�ɁB
	{
		_pD3DParam.SwapEffect = D3DSWAPEFFECT_DISCARD; //COPY���y��
		_pD3DParam.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		if (APP_GetWindowsAutoVSyncBool()) //v2.65�ǉ�
			_pD3DParam.PresentationInterval = D3DPRESENT_INTERVAL_ONE; //D3DPRESENT_INTERVAL_ONE�́A�t���X�N���[�����ɁAWindows���Ŏ���V-Sync�����̂ŕ\���x������������BRADEON��V-Sync���m�点�^�C�~���O���A�o�E�g�Ȃ悤�Ȃ̂�640x480�t�����ɂ͂�����g�������Ȃ������Bv2.65
		//D3DSWAPEFFECT_FLIP�ɂ��ācD3DSWAPEFFECT_DISCARD(COPY)�ɂ��Ď蓮��VSync���������A�������]���������Ȃ���邽�߂�����CPU�ւ̕��ׂ͌y����
		//							  �����̃^�C�~���O���x���Ƃ��������ď�������(���m�C�Y�ڂ�)�����₷���悤�Ȃ̂ŁA�����DISCARD+IMMEDIATE�ōs���B
		//_pD3DParam.SwapEffect = D3DSWAPEFFECT_FLIP;
		//_pD3DParam.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	}
	else
	{
		_pD3DParam.SwapEffect = D3DSWAPEFFECT_DISCARD; //COPY���y��
		_pD3DParam.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	_pD3DParam.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	hr = d3dDevReset(); //�쐬
	if (FAILED(hr))
	{
		MessageBox(_hWnd, "ERROR: DIRECT3D::CreateDevice() failed.    ", "Ootake", MB_OK);
		SCREEND3D_Deinit();
		return FALSE;
	}

	//�K���}�i���邳�����j���v�Z�ς݂̃e�[�u����p�ӁB
	SCREEN_SetGamma(APP_GetScanLineType(), APP_GetScanLineDensity());

	_LastTimeSyncTime = timeGetTime(); //�O��Sync�����Ƃ��̃^�C�}�[�J�E���g
	_LastTimeSyncTime3 = _LastTimeSyncTime; //v2.43�ǉ�
	_SyncAjust  = 0; //VSync���I�t�̂Ƃ���1/60�b�Ԋu�ɂł��邾���߂Â��邽�߂̕ϐ��Bv1.67
	_SyncAjust3 = 0; //v2.43�ǉ�
	_Frame = 0; //v2.43�ǉ�

	//��ʂ��N���A
	SCREEND3D_Clear(0,0,0);

	return TRUE;
}


//�X�N���[�����[�h��ύX���܂��B 
BOOL
SCREEND3D_ChangeMode(
	Sint32		width,
	Sint32		height,
	Sint32		magnification,
	Uint32		flags)
{
	SCREEND3D_Deinit();
	return SCREEND3D_Init(width, height, magnification, flags);
}


//�����A�����Ԃ�҂��܂��B(VSync����)
BOOL
SCREEND3D_WaitVBlank(
	BOOL	bDraw) //bDraw��TRUE�ɂ��ČĂԂƕ`����s���BFALSE�̏ꍇVSync�҂��̂݁B
{
	Sint32				t;
	D3DRASTER_STATUS	rs;
	HRESULT				hr;
	RECT				rc;
	UINT				bt, bt2;
	UINT				cy, cy2;
	Sint32				top;
	Sint32				h2;

	//Vista��"Aero"��"Vista�X�^���_�[�h(Home Basic�ɂ̂ݑ���)"�̃f�X�N�g�b�v���p���́AWindows���̂�V-Sync�������ōs���̂ŁA�������Ԃ����Ēx���Ȃ�Ȃ��悤��Ootake����V-Sync�ɍ\�킸�A��ɕ`����ς܂���Bv2.02
	if (((APP_GetWindowsVista())&&(APP_DwmIsCompositionEnabled()))||
		(APP_GetWindowsAutoVSyncBool())) //v2.65�ǉ��B�����I��Windows�̎���V-Sync���g�����[�h��ݒu�B�\���x�����N����̂Ŕ񐄏��B�u���E���ǂȂ���v���ȁB
	{
		//Wait����O�ɕ`�揈�����ς܂���B
		if (bDraw)
		{
			//�`�揈��
			hr = _pD3DDev->Present(NULL, NULL, NULL, NULL); //Direct3D�́ASwapEffect��VSync�҂�������̂ɐݒ肷��ƁAPresent���s���Ɏ�����VSync�҂������Ă����B������VSync���Ə������d���Ƃ�������̂Ō���͎蓮�ő҂��B
			if (hr == D3DERR_DEVICELOST)
			{
				d3dDevReset();
				_pD3DDev->Present(NULL, NULL, NULL, NULL);
			}
			if (APP_GetWindowsAutoVSyncBool())
				return TRUE;
			bDraw = FALSE; //�`�揈������
		}
	}

	if (_bSyncTo60HzScreen)
	{
		t = timeGetTime() - _LastTimeSyncTime;
		if (t <= 16) //17ms(1/60s=16.7ms)�ȏ�o�߂��Ă����ꍇ�͑҂��Ȃ��B(timeGetTime()�̌덷������̂�t=17�ł��܂�16.1ms�o�߂̂��Ƃ����邪��x�҂����Ȃ����Ƃ�D��j
		{
			//���̃A�v���̂��߂ɏ�������x�݁B��VBlank�҂����[�v����CPU��L����100%�ɂȂ�̂ŁA��������Əȓd�́B
			t = 16 - t - 11; //-11�͏����������Ȃ����߂̃}�[�W���B-11OK�B-10�ق�OK�B-9�ȉ����ƃe���|�̗h�炬����킸���ɉ����U��C������B16=�P�R�}�̎��Ԗ�16ms�B
							 //-11�������ƁA��قǑ���PC�łȂ��ƈӖ����Ȃ����ASleep()�͂ǂ����Ă��傫�Ȍ덷���o��Ƃ�������悤�Ȃ̂ŁA���̐ݒ�ŁB
			if ((t >= 1)&&(t <= 16-11)) //�^�C�}�[�J�E���^�̃I�[�o�[�t���[���l���āA���͈̔͂̂Ƃ�����Sleep�������Ȃ��B
				Sleep(t);
			//�҂BGetRasterStatus���\�b�h�Ő������������B
			//		�E�B���h�E���ŏ�������Ă��鎞�͂Ȃ���Present�ɂ��VSync�������Ȃ�(���ɂ���邩������Ȃ���Direct3D9�̎d�l���ۂ�)�̂ŁA�蓮��VSync�������s���B
			cy = (UINT)GetSystemMetrics(SM_CYSCREEN);
			cy2 = cy - (cy / 5); //�c1200�̃f�B�X�v���C�̏ꍇ��-250���C��(1200/5)�܂Ń`�F�b�N�B1���C�������̔��肾��Sync�����������Ƃ�����̂ŁA�}�[�W���Ԃ�B-300����LightPSG���ɂQ��VSync���Ă��܂��B�}�C�i�X�����Ȃ���Sync�������Ƃ�����e���|��◐��B
			if (_Flags & SCREEN_FFULLSCREEN)
			{	//�t���X�N���[���̎���0���C����VSync������B
				//��ʏ㕔�̌���(�������̌���)���v�Z
				if (APP_GetFullStretched(TRUE))
				{
					//�A�X�y�N�g���4:3�ɕۂ�
					if (_Width/4 >= _Height/3)
					{	//�c�̂ق����Z���̂ŏc����Ƃ���
						if (MAINBOARD_GetShowOverscanLeft() > 0) //���E�̃I�[�o�[�X�L�����̈��\������Ȃ�
							top = (_Height - (Sint32)((double)_Height * 0.96137 + 0.5)) / 2; //0.96137=224/((268-256)/4*3+224)
						else
							top = 0;
					}
					else
					{	//���̂ق����Z���̂ŉ�����Ƃ���
						h2 = (Sint32)((double)(_Width / 4.0 * 3.0 + 0.5));
						if (MAINBOARD_GetShowOverscanLeft() > 0) //���E�̃I�[�o�[�X�L�����̈��\������Ȃ�
							top = (_Height - (Sint32)((double)h2 * 0.96137 + 0.5)) / 2; //0.96137=224/((268-256)/4*3+224)
						else
							top = (_Height - h2) / 2;
					}
				}
				else if (APP_GetStretched())
				{
					//�A�X�y�N�g���TV��ʂƓ���4:3�ɁB�c�̒�������PCE�W��224�̐����{(�Q�{)�ɂ���
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
					top = (_Height - 224*_Magnification) / 2;
					if (MAINBOARD_GetShowOverscanTop() > 0) //�㑤�̃I�[�o�[�X�L�����̈��\������Ȃ�
					{
						top -= MAINBOARD_GetShowOverscanTop() * _Magnification;
						if (top < 0) top = 0; //��ʂ���͂ݏo���Ă��܂��ꍇ�́A�X�g���b�`(�k��)���đΉ��B1440x900,1600x900�Ȃǂł��蓾��B
					}
				}
				bt = cy - top;
			}
			else if (IsIconic(_hWnd))
			{	//�E�B���h�E���ŏ�������Ă��鎞�͍ŉ�256���C����VSync������B
				bt = cy2;
			}
			else
			{	//�E�B���h�E���[�h�̏ꍇ�A�E�B���h�E�\���̈�ŉ����C�����z��������Sync������B�������Ȃ��Ɖ�ʏ㕔�ł�Sync���Ԃɍ���Ȃ��Bv2.54
				GetWindowRect(_hWnd, &rc);
				bt = (UINT)rc.bottom;
			}
			bt2 = bt + (cy - cy2);
			while (TRUE)
			{
				_pD3DDev->GetRasterStatus(0, &rs);
				if (bt <= cy2)
				{
					if ((rs.ScanLine >= cy2)||(rs.ScanLine == 0)||(rs.InVBlank)) //�X�L�������C���̔���������ق���Sync�𓦂����e���|����Bv2.54
						break; //VBlank���Ԃɓ������烋�[�v�𔲂��o���B
				}
				else //�E�B���h�E�����̂ق��ɂ���ꍇ,�������̓t���X�N���[�����[�h
				{
					if ((_Flags & SCREEN_FFULLSCREEN)&&(cy >= 480)&&(APP_GetVSyncAdjust() > 0)) //PC���ɂ���ẮA�������߂�V-Blank���N�����Ȃ��Ɖ�ʏ㕔�̏��������ɊԂɍ���Ȃ��ꍇ������B�Â�RADEON�@��640x480�̉�ʃ��[�h�ŁA����Ń^�C�~���O�������������Y���V-Sync���o����B400x300,320x240�͕␳����Ƌt�ɑʖځBv2.62�ǉ��Bv2.65�X�V
					{
						if ((rs.InVBlank)||(rs.ScanLine == 0)||(rs.ScanLine >= bt-APP_GetVSyncAdjust())||(rs.ScanLine <= bt2-cy)) //v2.62�B�ubt-APP_GetVSyncAdjust()�v�ő���(APP_GetVSyncAdjust()�h�b�g������)��V-Blank���N�������ƂŁA�Â߂̋@��ŉ�ʏ㕔��������������B�l��-14���Ƒ����@��(GeForce)�ŉ���������B
							break; //VBlank���Ԃɓ������烋�[�v�𔲂��o���B
					}
					else //�ʏ�
					{
						if ((rs.InVBlank)||(rs.ScanLine == 0)||(rs.ScanLine >= bt)||(rs.ScanLine <= bt2-cy))
							break; //VBlank���Ԃɓ������烋�[�v�𔲂��o���B
					}
				}
				t = timeGetTime() - _LastTimeSyncTime;
				if ((t >= 18)||(t < 0)) //17.1ms�ȏ�o�߂��Ă�����Bor�J�E���^���I�[�o�[�t���[
					break;
			}
			//PRINTF("Test %d %d %d", bt, bt2, cy2);
		}
		_LastTimeSyncTime = timeGetTime(); //�O���Sync���I������^�C���Ƃ��ċL�^���Ă���
		if (bDraw)
		{
			//�`�揈��
			hr = _pD3DDev->Present(NULL, NULL, NULL, NULL); //Direct3D�́ASwapEffect��VSync�҂�������̂ɐݒ肷��ƁAPresent���s���Ɏ�����VSync�҂������Ă����B������VSync���Ə������d���Ƃ�������̂Ō���͎蓮�ő҂��B
			if (hr == D3DERR_DEVICELOST)
			{
				d3dDevReset();
				_pD3DDev->Present(NULL, NULL, NULL, NULL);
			}
		}
		return TRUE;
	}
	else //_bSyncTo60HzScreen �� FALSE�̏ꍇ
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
		if (bDraw)
		{
			//�`�揈��
			hr = _pD3DDev->Present(NULL, NULL, NULL, NULL); //Present���Ă�VSync�҂������`�悾������ݒ�ɂȂ��Ă���̂ŁA�҂����ɕ`�悳���B
			if (hr == D3DERR_DEVICELOST)
			{
				d3dDevReset();
				_pD3DDev->Present(NULL, NULL, NULL, NULL);
			}
		}
		return TRUE;
	}
}


void*
SCREEND3D_GetBuffer()
{
	return (void*)_pScreenPixels;
}


const Sint32
SCREEND3D_GetBufferPitch()
{
	return _SurfacePitch/2;
}


//���C��(�Q�[��)��ʗp�I�t�X�N���[�������b�N���āA��������(�`��)�p�A�h���X��ݒ肷��Bv2.13�X�V�B32bit�P�ʂň����悤�ɂ����B
static BOOL
lock_offscreen_surface(
	LONG*				pPitch,
	Uint32**			ppPixels)
{
	D3DLOCKED_RECT	pLockedRect;
	HRESULT			hr;

	hr = _pD3DSGame->LockRect(&pLockedRect, NULL, 0);
	if (hr == D3D_OK)
	{
		*pPitch = pLockedRect.Pitch >> 2; //���P���C���̃o�C�g���B32bit�P�ʂň������߂�4�Ŋ����Ă����Bv2.13�X�V
		*ppPixels = (Uint32*)pLockedRect.pBits;
		return TRUE;
	}
	else
		return FALSE;
}


//��ʑS�̂��N���A���܂��B
void
SCREEND3D_Clear(
	byte	r,
	byte	g,
	byte	b) //v2.73�X�V�B�C�ӂ̐F�ŃN���A�ł���悤�ɂ����B
{
	HRESULT		hr;

	_pD3DDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(r,g,b), 1.0, 0);
	hr = _pD3DDev->Present(NULL, NULL, NULL, NULL); //Present�����s���Ȃ��Ɣ��f����Ȃ��B
	if (hr == D3DERR_DEVICELOST)
	{
		d3dDevReset();
		_pD3DDev->Present(NULL, NULL, NULL, NULL);
	}
}


//�e�L�X�g���b�Z�[�W��ݒ肵�܂��B
void
SCREEND3D_SetMessageText(
	char*	pText)
{
	_pMessageText = pText;
}


//�Z���^�[�e�L�X�g���b�Z�[�W��ݒ肵�܂��B
void
SCREEND3D_SetCenterText(
	char*	pText)
{
	_pCenterText = pText;
}


//�e�L�X�g���b�Z�[�W�̕\������
static void
print_message()
{
	HDC			dc;
	HFONT		prevFont;
	HFONT		hFont;
	LOGFONT		logFont;
	RECT		rcSrc;
	RECT		rcDst;
	RECT		rc;
	int			a,fs;

	if (!APP_GetInit())
		return; //�ŏ��̏��������S�Ċ������Ă��Ȃ��ꍇ�́A�\���������s��Ȃ��BCD-ROM�Q�[�������W���[�������Ƃ��Ƀ��b�Z�[�W������������̂�����Bv1.67

	//�f�o�C�X�R���e�L�X�g���擾
	if (_pD3DSText->GetDC(&dc) != D3D_OK)
		return;

	//�t�H���g�T�C�Y������
	switch (_Magnification)
	{
		case 1: fs = 12; break;
		case 2:	fs = 16; break;
		case 3: fs = 12; break; //v2.44�X�V
		default: //4
			fs = 17; break; //v2.44�X�V
	}
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
	_pD3DSText->ReleaseDC(dc);
	
	//�]�����ʒu���T�C�Y�̒���
	rcSrc.left	= 0;
	rcSrc.top	= 0;
	rcSrc.right	= rc.right;
	rcSrc.bottom= fs;
	//�]����ʒu�̒������\�����������͈̔͂����₷�����邽�߂Ɋg�傷��B
	if ((APP_GetOverscanHideBlackLR())&&(MAINBOARD_GetShowOverscanLeft() == 0)) //���E�̃I�[�o�[�X�L�����̈�ɍ��т�t����Ȃ�
		rcDst.left = _GameLeft; //���т�����̂ŃM���M���܂ō��Ɋ񂹂Ă����h��OK�B
	else //�ʏ�
		rcDst.left = _GameLeft + 3;
	if ((APP_GetOverscanHideBlackTop())&&(MAINBOARD_GetShowOverscanTop() < 8)) //�㑤�̃I�[�o�[�X�L�����̈�ɍ��т�t����Ȃ�
	{
		rcDst.top = _GameTop; //���т�����̂ŃM���M���܂ŏ�Ɋ񂹂Ă����h��OK�B
		a = (8-MAINBOARD_GetShowOverscanTop())*_Magnification;
		if (a < 4) //���ѕ�����4�h�b�g�����Ȃ�
			rcDst.top += (4-a);
	}
	else //�ʏ�
		rcDst.top = _GameTop + 4;
	if (_Magnification >= 3)
	{
		rcDst.right	= rcDst.left + rcSrc.right * 2; //�����Q�{�g��
		rcDst.bottom = rcDst.top + fs * 2; //�c���Q�{�g��
	}
	else
	{
		rcDst.right	= rcDst.left + rcSrc.right;
		rcDst.bottom = rcDst.top + fs;
	}
	if (rcDst.right > _GameRight) //���b�Z�[�W���������Ă͂ݏo�Ă��܂��ꍇ
	{
		rcSrc.right = (LONG)((double)rcSrc.right / ((double)rcDst.right / (double)_GameRight)); //�\�[�X������������
		rcDst.right = _GameRight;
	}
	//�]��
	_pD3DDev->StretchRect(_pD3DSText, &rcSrc, _pD3DSBack, &rcDst, D3DTEXF_NONE); //�����̓N�b�L�������邽��NONE���g���B
}


//FPS�̕\������
static void
print_fps()
{
	HDC			dc;
	HFONT		prevFont;
	HFONT		hFont;
	LOGFONT		logFont;
	RECT		rcSrc;
	RECT		rcDst;
	RECT		rc;
	int			fs;
	char		text[3+1]; //�ꉞ�R���܂ŗp��
	int			a;

	//�f�o�C�X�R���e�L�X�g���擾
	if (_pD3DSText->GetDC(&dc) != D3D_OK)
		return;

	//�t�H���g�T�C�Y������
	switch (_Magnification)
	{
		case 1: fs = 12; break;
		case 2:	fs = 16; break;
		case 3: fs = 12; break; //v2.44�X�V
		default: //4
			fs = 17; break; //v2.44�X�V
	}
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
	_pD3DSText->ReleaseDC(dc);
	
	//�]�����ʒu���T�C�Y�̒���
	rcSrc.left	= 0;
	rcSrc.top	= 0;
	rcSrc.right	= rc.right;
	rcSrc.bottom= fs;
	//�]����ʒu�̒������\�����������͈̔͂����₷�����邽�߂Ɋg�傷��B
	if ((APP_GetOverscanHideBlackLR())&&(MAINBOARD_GetShowOverscanLeft() == 0)) //���E�̃I�[�o�[�X�L�����̈�ɍ��т�t����Ȃ�
		rcDst.left = _GameLeft; //���т�����̂ŃM���M���܂ō��Ɋ񂹂Ă����h��OK�B
	else //�ʏ�
		rcDst.left = _GameLeft + 3;
	if ((APP_GetOverscanHideBlackBottom())&&(MAINBOARD_GetShowOverscanBottom() < 8)) //�����̃I�[�o�[�X�L�����̈�ɍ��т�t����Ȃ�
	{
		rcDst.bottom = _GameBottom; //���т�����̂ŃM���M���܂ŉ��Ɋ񂹂Ă����h��OK�B
		a = (8-MAINBOARD_GetShowOverscanBottom())*_Magnification;
		if (a < 3) //���ѕ�����3�h�b�g�����Ȃ�
			rcDst.bottom -= (3-a);
	}
	else //�ʏ�
		rcDst.bottom = _GameBottom - 3; //�����ɕ\��
	if (_Magnification >= 3)
	{
		rcDst.right	= rcDst.left + rcSrc.right * 2; //�����Q�{�g��
	    rcDst.top = rcDst.bottom - fs * 2; //�c���Q�{�g��
	}
	else
	{
		rcDst.right	= rcDst.left + rcSrc.right;
	    rcDst.top = rcDst.bottom - fs;
	}
	//�]��
	_pD3DDev->StretchRect(_pD3DSText, &rcSrc, _pD3DSBack, &rcDst, D3DTEXF_NONE); //�����̓N�b�L�������邽��NONE���g���B
}


//��ʂ̒����Ƀ��b�Z�[�W��\������Bv2.77�ǉ�
void
print_center_message()
{
	HDC			dc;
	HFONT		prevFont;
	HFONT		hFont;
	LOGFONT		logFont;
	RECT		rcSrc;
	RECT		rcDst;
	RECT		rc;
	int			fs;
	LONG		adjust;

	//�f�o�C�X�R���e�L�X�g���擾
	if (_pD3DSText->GetDC(&dc) != D3D_OK)
		return;

	//�t�H���g�T�C�Y������
	switch (_Magnification)
	{
		case 1: fs = 12; break;
		case 2:	fs = 16; break;
		case 3: fs = 12; break; //v2.44�X�V
		default: //4
			fs = 17; break; //v2.44�X�V
	}
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
	_pD3DSText->ReleaseDC(dc);
	
	//�]�����ʒu���T�C�Y�̒���
	rcSrc.left	= 0;
	rcSrc.top	= 0;
	rcSrc.right	= rc.right;
	rcSrc.bottom= fs;
	//�]����ʒu�̒������\�����������͈̔͂����₷�����邽�߂Ɋg�傷��B
	rcDst.left = _GameLeft;
	rcDst.top  =         0;
	if (_Magnification >= 3)
	{
		rcDst.right	= rcDst.left + rcSrc.right * 2; //�����Q�{�g��
	    rcDst.bottom = fs * 2; //�c���Q�{�g��
	}
	else
	{
		rcDst.right	= rcDst.left + rcSrc.right;
	    rcDst.bottom = fs;
	}
	//�Z���^�����O
	adjust = (_GameRight - _GameLeft) / 2 - (rcDst.right - rcDst.left) / 2;
	rcDst.left   += adjust;
	rcDst.right  += adjust;
	adjust = (_GameBottom - _GameTop) / 2 - (rcDst.bottom - rcDst.top) / 2;
	rcDst.top    += adjust;
	rcDst.bottom += adjust;
	//�]��
	_pD3DDev->StretchRect(_pD3DSText, &rcSrc, _pD3DSBack, &rcDst, D3DTEXF_NONE); //�����̓N�b�L�������邽��NONE���g���B
}


//�`��p�o�b�N�T�[�t�F�X�֓]�����鏈���ȂǁB
static void
zoom_d3dTensou(
	Uint16*		pTvW,	//�]�����̉��s�N�Z�����B��[0]�`[255]��16+224+16(������Overscan)���C���Ԃ�B�����ɂ͕\���J�n(��.�I�[�o�[�X�L�����\�����Ȃ��ꍇ��[16]�ɂȂ�)�̃A�h���X������B
	Sint32		h,		//�]�����̏c�s�N�Z�����B�ʏ��224�B�㉺�̃I�[�o�[�X�L����������ꍇ���̂Ԃ񑝂₵�Ă������ĂԁB
	Sint32		executeCode)
{
	RECT		rcSrc;
	RECT		rcDst;
	Sint32		a,b,c,d,s,i,w2,h2;
	BOOL		bRasterChange = FALSE; //���X�^���ƂɈقȂ�𑜓x���ݒ肳��Ă����ꍇTRUE
	Uint16*		pTvW2 = pTvW;
	Sint32		ot = 16-MAINBOARD_GetShowOverscanTop(); //�]�����̊J�nY���W
	Sint32		wMag; //�������̃\�[�X�{��
	Sint32		hMag; //�c�����̃\�[�X�{��
	Sint32		scanLineType;

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
			//�t���X�g���b�`���͏㉺�̃I�[�o�[�X�L�����̈��\���ł��Ȃ����߁A�㉺�̃I�[�o�[�X�L�����̈���J�b�g�B
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
		//Direct3D��StretchRect�ł�Window�̈ʒu��g�̑����Ԃ�Ȃǂ���������K�v���Ȃ��B���(0,0)���`��̍���ɂȂ�B
		a = 0;
		b = 0;
		if (APP_GetOverscanHideBlackTop()) //�㑤�̃I�[�o�[�X�L�����̈�ɍ��т����ĉB���ݒ�Ȃ�
			b += (8 - MAINBOARD_GetShowOverscanTop()) * _Magnification;
		c = APP_GetGameWidth(_Magnification);
		d = b + (MAINBOARD_GetShowOverscanTop() + 224 + MAINBOARD_GetShowOverscanBottom()) * _Magnification;
		if (((MAINBOARD_GetShowOverscanLeft() > 0)&&((*(pTvW+MAINBOARD_GetShowOverscanTop()+223)) == 512))|| //512�̂Ƃ��̓I�[�o�[�X�L�����\�����Ȃ�
			((MAINBOARD_GetShowOverscanLeft() == 0)&&(APP_GetOverscanHideBlackLR()))||
			(executeCode == 3))
		{	//���E�ɍ��т�z�u
			if (APP_GetVStretched()) //�c��ʃ��[�h�Ȃ�
			{
				a += (Sint32)(5.34 * (double)_Magnification + 0.5);		//5.34=299/256*(256/336)*6dot
				c -= (Sint32)(5.34 * (double)_Magnification + 0.5);
			}
			else if (APP_GetStretched())
			{
				a += (Sint32)(7.01 * (double)_Magnification + 0.5);		//7.01=299/256*6dot
				c -= (Sint32)(7.01 * (double)_Magnification + 0.5);
			}
		}
	}
	_GameLeft   = a; //print_message()�ŕ\���ʒu����̂��߂ɁA�Q�[����ʓ]����̍��W���T���Ă����B
	_GameRight  = c; //
	_GameTop    = b; //
	_GameBottom = d; //

	if (IsIconic(_hWnd)) //�E�B���h�E���ŏ�������Ă��鎞�Bhes���ŏ������Ē����Ƃ��Ȃǂɏ������y������B
		if (executeCode != 2) //�X�N���[���V���b�g�p�֓]���ȊO�̏ꍇ
		{
			//�����A�����Ԃ�҂�
			SCREEND3D_WaitVBlank(FALSE); //�`�揈���͍s��Ȃ�
			return;
		}

	//�`��𑜓x�̕ύX���������ꍇ�A�S�~���c��Ȃ��悤�ɉ�ʑS�̂��N���A����B
	if (MAINBOARD_GetResolutionChange())
		if (MAINBOARD_GetUpdateFullScreen())
			_pD3DDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0, 0);

	//�\�[�X�͈͂����肵�A�f�o�C�X�̃o�b�N�T�[�t�F�X(DirectDraw�ł̃v���C�}���T�[�t�F�X�Ɠ��l)�֓]������B
	if (_Magnification >= 2) //x2�ȏ�̏ꍇ
	{
		scanLineType = APP_GetScanLineType();
		if ((scanLineType >= 1)&&(scanLineType <= 6)) //�X�L�������C��(�c���܂�)��
		{
			if ((scanLineType == 3)||(scanLineType == 4))
				wMag = 1;
			else
				wMag = 2; //x2�ȏ�����͂Q�{�h�b�g�Œ�B�i���x�A�b�v�{�g�傳�ꂽ�Ƃ��Ƀo�C���j�A�t�B���^�����������ɂ�����j
			hMag = _Magnification; //�c�͔{���Ԃ�̃\�[�X��p�ӂ��ē]���B
		}
		else //�m���X�L�������C����
		{
			wMag = 2;
			if (_Magnification == 2)
				hMag = _Magnification; //�c�͔{���Ԃ�̃\�[�X��p�ӂ��ē]���B
			else
				hMag = _Magnification-1; //3x,4x�̂Ƃ��́A���ꂼ��2x,3x�Ɋg��B�i�W���M�[�y�������x�A�b�v�j
		}
	}
	else //x1�̏ꍇ
		wMag = hMag = 1;
	if (!bRasterChange)
	{	//�ʏ�
		if (MAINBOARD_GetFourSplitScreen()) //�d�������L,���[���h�R�[�g,�͂ɂ����񂴂�����,�p���[�h���t�g,�T�C�R�`�F�C�T�[�̂S������ʂ̏ꍇ�Bv2.27�X�V
		{		
			SetRect(&rcSrc, s/4*wMag, ot*hMag, (s/4+s/2)*wMag, (ot+h)*hMag); //�\�[�X�̍��E���ѕ������J�b�g
			//�S���̂P�ɏk�����ĂS��]��
			c = a + (c-a)/2;
			d = b + (d-b)/2;
			w2 = c - a;
			h2 = d - b;
			for (i=1; i<=4; i++)
			{
				SetRect(&rcDst, a, b, c, d);
				switch (APP_GetD3DEffect())
				{
					case 1:
						if ((APP_GetHalfMode())&&((_Magnification == 2)||(_Magnification == 4)))
							_pD3DDev->StretchRect(_pD3DSGame, &rcSrc, _pD3DSBack, &rcDst, D3DTEXF_LINEAR); //Half���[�h��x2,x4��POINT����1/4�k���̉e���ŉ�ʂ��Â��Ȃ�̂�LINEAR�ɂ���B
						else
							_pD3DDev->StretchRect(_pD3DSGame, &rcSrc, _pD3DSBack, &rcDst, D3DTEXF_POINT); //�����ԃh�b�g���N�b�L��
						break;
					case 2: _pD3DDev->StretchRect(_pD3DSGame, &rcSrc, _pD3DSBack, &rcDst, D3DTEXF_LINEAR); //���傤�ǂ����z
						break;
					default: //0
						_pD3DDev->StretchRect(_pD3DSGame, &rcSrc, _pD3DSBack, &rcDst, D3DTEXF_NONE); //���Ȃ�h�b�g���N�b�L��
						break;
				}
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
				w2 = c / _Magnification;
				//PRINTF("%d, %d", s,w2);//test
				w2 = (s-w2)/2;
				SetRect(&rcSrc, w2*wMag, ot*hMag, (s-w2)*wMag, (ot+h)*hMag); //�]������]����Ɠ����h�b�g���ɍ��킹��B
			}
			else if (executeCode == 5) //�I�[�o�[�X�L�����̈�̍��E���J�b�g����ꍇ
				SetRect(&rcSrc, 6*wMag, ot*hMag, (s-6)*wMag, (ot+h)*hMag); //���̂Ƃ����ѕ����̃\�[�X��6�h�b�gx�{���B
			else //�ʏ�
				SetRect(&rcSrc, 0, ot*hMag, s*wMag, (ot+h)*hMag);

			switch (APP_GetD3DEffect())
			{
				case 1: _pD3DDev->StretchRect(_pD3DSGame, &rcSrc, _pD3DSBack, &rcDst, D3DTEXF_POINT); //�����ԃh�b�g���N�b�L��
					break;
				case 2: _pD3DDev->StretchRect(_pD3DSGame, &rcSrc, _pD3DSBack, &rcDst, D3DTEXF_LINEAR); //���傤�ǂ����z
					break;
				default: //0
					_pD3DDev->StretchRect(_pD3DSGame, &rcSrc, _pD3DSBack, &rcDst, D3DTEXF_NONE); //���Ȃ�h�b�g���N�b�L��
					break;
			}
		}
	}
	else
	{	//���X�^���ƂɈقȂ�𑜓x���ݒ肳��Ă����Ƃ��Bv1.28�X�V�B�P���C�����]������悤�ɂ����Bv2.00�X�V�BDirect3D�Ȃ�Vista�ł������B
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
				SetRect(&rcSrc, 6*wMag, (ot+i)*hMag, ((*pTvW)-6)*wMag, (ot+i)*hMag+hMag);
			else //�ʏ�
				SetRect(&rcSrc, 0, (ot+i)*hMag, (*pTvW)*wMag, (ot+i)*hMag+hMag);
			switch (APP_GetD3DEffect())
			{
				case 1: _pD3DDev->StretchRect(_pD3DSGame, &rcSrc, _pD3DSBack, &rcDst, D3DTEXF_POINT); //�����ԃh�b�g���N�b�L��
					break;
				case 2: _pD3DDev->StretchRect(_pD3DSGame, &rcSrc, _pD3DSBack, &rcDst, D3DTEXF_LINEAR); //���傤�ǂ����z
					break;
				default: //0
					_pD3DDev->StretchRect(_pD3DSGame, &rcSrc, _pD3DSBack, &rcDst, D3DTEXF_NONE); //���Ȃ�h�b�g���N�b�L��
					break;
			}
			pTvW++;
		}
	}

	if (executeCode == 2) return;//�X�N���[���V���b�g�p�֓]���̏ꍇ�����ŏI��

	//�e�L�X�g���b�Z�[�W�̕\���BDirect3D9��StretchRect�̓v���[���T�[�t�F�X���m�̓��{�]�����o���Ȃ��̂ŁA
	//							DirectDraw�̂Ƃ��ƈႢ�A�e�L�X�g���b�Z�[�W���o�b�N�o�b�t�@�[�֒��ړ]������悤�ɂ����B
	if (*_pMessageText != 0) //���b�Z�[�W���ݒ肳��Ă����
		print_message();

	//FPS�̕\���Bv1.50�ǉ�
	if (APP_GetShowFPS())
		print_fps();

	//�Z���^�[�e�L�X�g���b�Z�[�W�̕\���Bv2.77�ǉ�
	if (*_pCenterText !=0)
		print_center_message();

	//�����A�����Ԃ�҂����ۂ̕`�揈��
	SCREEND3D_WaitVBlank(TRUE);
}


//�`��B�������������ݏ����B
#define	GB	(d & 0x000000FF)
#define	GG	(d & 0x0000FF00)>>8
#define	GR	(d & 0x00FF0000)>>16
//zoom3x()�Czoom2x()�Czoom1x()�����p�ӁB���x�d���̂��߂��ꂼ��ʃ��[�`���ɁB���C�����Ƃɉ𑜓x��ς��Ă���Q�[���ɑΉ��B
//32�r�b�g�J���[x�S�{�p
static void
zoom4x_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j;
	Uint32*		pSrc0;
	Uint32*		pDst;
	Uint32*		pDst0;
	Uint32		d;

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
			*pDst++ = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB]; //�P�h�b�g�Ԃ񏑂����܂��B
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB]; //�P�h�b�g�Ԃ񏑂����܂��B�����Q�{�g��(90%�c�X�L�������C����)
		}
		*pDst = 0; //Direct3D�ł͉E�[�ɂP�h�b�g�Ԃ�N���A(��)�}�[�W���������Ă����Ȃ��ƉE�[�������B
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90�X�L�������C���ŁBv2.34�X�V�B���������̓O���f�[�V������t�����ɕ��R�ɂ����ق�����a�����Ȃ��B
		{
			d = *pSrc++;
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB]; //v2.34�X�V
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB]; //�����Q�{�g��(90%�c�X�L�������C����)
		}
		*pDst = 0;
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�R��ڂ�90%�X�L�������C���ŁBv2.34�X�V�B���������̓O���f�[�V������t�����ɕ��R�ɂ����ق�����a�����Ȃ��B
		{
			d = *pSrc++;
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB]; //v2.34�X�V
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];  //�����Q�{�g��(90%�c�X�L�������C����)�Bv2.34�X�V
		}
		*pDst = 0;
		pDst = pDst0 + _Pitch3;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB]; //�����Q�{�g��(80%�c�X�L�������C����)
		}
		*pDst = 0;
		pDst0 += _Pitch4;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//32�r�b�g�J���[x�R�{�p
static void
zoom3x_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j;
	Uint32*		pSrc0;
	Uint32*		pDst;	//v2.13�X�V�B32bit�P�ʂɂ��č������B
	Uint32*		pDst0;
	Uint32		d;

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
			*pDst++ = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB]; //4byte�Ԃ�(�P�h�b�g)�������܂��B
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB]; //4byte�Ԃ�(�P�h�b�g)�������܂��B�����Q�{�g��(90%�c�X�L�������C����)
		}
		*pDst = 0; //Direct3D�ł͉E�[�ɂP�h�b�g�Ԃ�N���A(��)�}�[�W���������Ă����Ȃ��ƉE�[�������B
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90%�X�L�������C���ɂ���B
		{
			d = *pSrc++;
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB]; //4byte�Ԃ�(�P�h�b�g)�������܂��B
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB]; //4byte�Ԃ�(�P�h�b�g)�������܂��B�����Q�{�g��
		}
		*pDst = 0;
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB]; //4byte�Ԃ�(�P�h�b�g)�������܂��B
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB]; //4byte�Ԃ�(�P�h�b�g)�������܂��B�����Q�{�g��
		}
		*pDst = 0;
		pDst0 += _Pitch3;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//32�r�b�g�J���[x�Q�{�p�B
static void
zoom2x_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j;
	Uint32*		pSrc0;
	Uint32*		pDst;
	Uint32*		pDst0;
	Uint32		d;

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
		*pDst = 0; //Direct3D�ł͉E�[�ɂP�h�b�g�Ԃ�N���A(��)�}�[�W���������Ă����Ȃ��ƉE�[�������B
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB]; //�����Q�{�g��(80%�c�X�L�������C����)
		}
		*pDst = 0;
		pDst0 += _Pitch2;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//���X�L�������C��32�r�b�g�J���[x�S�{�p
static void
zoom4xHS_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j;
	Uint32*		pSrc0;
	Uint32*		pDst;
	Uint32*		pDst0;
	Uint32		d;

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
			*pDst++ = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB];
		}
		*pDst = 0; //Direct3D�ł͉E�[�ɂP�h�b�g�Ԃ�N���A(��)�}�[�W���������Ă����Ȃ��ƉE�[�������B
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90%�X�L�������C���ŁBv2.35�X�V�B���������̓O���f�[�V������t�����ɕ��R�ɂ����ق�����a�����Ȃ��B
		{
			d = *pSrc++;
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
		}
		*pDst = 0;
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�R��ڂ�90%�X�L�������C���ŁBv2.35�X�V�B���������̓O���f�[�V������t�����ɕ��R�ɂ����ق�����a�����Ȃ��B
		{
			d = *pSrc++;
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
		}
		*pDst = 0;
		pDst = pDst0 + _Pitch3;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
		}
		*pDst = 0;
		pDst0 += _Pitch4;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//���X�L�������C��32�r�b�g�J���[x�R�{�p
static void
zoom3xHS_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j;
	Uint32*		pSrc0;
	Uint32*		pDst;
	Uint32*		pDst0;
	Uint32		d;

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
			*pDst++ = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB];
		}
		*pDst = 0; //Direct3D�ł͉E�[�ɂP�h�b�g�Ԃ�N���A(��)�}�[�W���������Ă����Ȃ��ƉE�[�������B
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90%�X�L�������C���ɂ���B
		{
			d = *pSrc++;
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
		}
		*pDst = 0;
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
		}
		*pDst = 0;
		pDst0 += _Pitch3;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//���X�L�������C��32�r�b�g�J���[x�Q�{�p�B
static void
zoom2xHS_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j;
	Uint32*		pSrc0;
	Uint32*		pDst;
	Uint32*		pDst0;
	Uint32		d;

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
			*pDst++ = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB];
		}
		*pDst = 0; //Direct3D�ł͉E�[�ɂP�h�b�g�Ԃ�N���A(��)�}�[�W���������Ă����Ȃ��ƉE�[�������B
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
		}
		*pDst = 0;
		pDst0 += _Pitch2;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//�m���X�L�������C���łQ�{�R�{�S�{�p�B32�r�b�g�J���[�B
static void
zoom2x3x4xNS_dd32(
	Sint32		bairitsu,		// 2x��3x��4x���B2x�Ȃ�2�B3x�Ȃ�3�B4x�Ȃ�4�B
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j,k;
	Uint32*		pSrc0;
	Uint32*		pDst;
	Uint32*		pDst0;
	Uint32		d;
	Sint32		bairitsu2; //�c�̃h�b�g�����{�Ƀf�W�^���g�傷�邩�Bx2��x3�Ȃ�2�Bx4�Ȃ�3�B

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
				*pDst++ = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB];
				*pDst++ = (_Gamma[GR] << 16)|(_Gamma[GG] << 8)| _Gamma[GB]; //�����Q�{�g��(�X�L�������C���Ȃ�)
			}
			*pDst = 0; //Direct3D�ł͉E�[�ɂP�h�b�g�Ԃ�N���A(��)�}�[�W���������Ă����Ȃ��ƉE�[�������B
			pDst0 += _Pitch;
		}
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//32�r�b�g�J���[x�P�{�p�B�X�L�������C���Ȃ��B
static void
zoom1xNS_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW, 			//
	Sint32		srcH)			// �]�����̍���
{
	int			i,j;
	Uint32*		pSrc0;
	Uint32*		pDst;
	Uint32*		pDst0;
	Uint32		d;

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
		*pDst = 0; //Direct3D�ł͉E�[�ɂP�h�b�g�Ԃ�N���A(��)�}�[�W���������Ă����Ȃ��ƉE�[�������B
		pDst0 += _Pitch;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//TV Mode ��32�r�b�g�J���[���S�{�p�B
static void
zoom4xTV_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j;
	Uint32*		pSrc0;
	Uint32*		pDst;
	Uint32*		pDst0;
	Uint32		d;

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
		*pDst = 0; //Direct3D�ł͉E�[�ɂP�h�b�g�Ԃ�N���A(��)�}�[�W���������Ă����Ȃ��ƉE�[�������B
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90%�X�L�������C���ŁBv2.35�X�V�B���������̓O���f�[�V������t�����ɕ��R�ɂ����ق�����a�����Ȃ��B
		{
			d = *pSrc++;
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
		}
		*pDst = 0;
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�R��ڂ�90%�X�L�������C���ŁBv2.35�X�V�B���������̓O���f�[�V������t�����ɕ��R�ɂ����ق�����a�����Ȃ��B
		{
			d = *pSrc++;
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
		}
		*pDst = 0;
		pDst = pDst0 + _Pitch3;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
		}
		*pDst = 0;
		pDst0 += _Pitch4;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//TV Mode ��32�r�b�g�J���[���R�{�p�B
static void
zoom3xTV_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j;
	Uint32*		pSrc0;
	Uint32*		pDst;
	Uint32*		pDst0;
	Uint32		d;

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
		*pDst = 0; //Direct3D�ł͉E�[�ɂP�h�b�g�Ԃ�N���A(��)�}�[�W���������Ă����Ȃ��ƉE�[�������B
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++) //�Q��ڂ�90%�X�L�������C���ɂ���B
		{
			d = *pSrc++;
			*pDst++ = (_GammaS90[GR] << 16)|(_GammaS90[GG] << 8)| _GammaS90[GB];
		}
		*pDst = 0;
		pDst = pDst0 + _Pitch2;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
		}
		*pDst = 0;
		pDst0 += _Pitch3;
		pSrc0 += SOURCE_PITCH;
		pTvW++;
	}
}

//Half Mode ��32�r�b�g�J���[ ���Q�{�p�B
static void
zoom2xTV_dd32(
	Uint32*		pSrc,			// �]�����̃|�C���^
	Sint32		srcY,			// �]������Y���W
	Uint16*		pTvW,			// �e���C���̕�
	Sint32		srcH)			// �]�����̍���
{
	int			i,j;
	Uint32*		pSrc0;
	Uint32*		pDst;
	Uint32*		pDst0;
	Uint32		d;

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
		*pDst = 0; //Direct3D�ł͉E�[�ɂP�h�b�g�Ԃ�N���A(��)�}�[�W���������Ă����Ȃ��ƉE�[�������B
		pDst = pDst0 + _Pitch;
		pSrc = pSrc0;
		for (j = 0; j < *pTvW; j++)
		{
			d = *pSrc++;
			*pDst++ = (_GammaS80[GR] << 16)|(_GammaS80[GG] << 8)| _GammaS80[GB];
		}
		*pDst = 0;
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
#undef GR
#undef GG
#undef GB


//pSrc�̕`��f�[�^���p�\�R���\�������ɃG���R�[�h���A�o�b�N�o�b�t�@�։摜���������݂܂��B
//		���C�����Ƃɉ𑜓x��ς��Ă���Q�[���i���Ղ̌��C������120%�Ȃǁj�ɂ��Ή��B
void
SCREEND3D_Blt(
	Uint32*		pSrc,
	Sint32		srcX,
	Sint32		srcY,
	Uint16*		pTvW,	//�]�����̉��s�N�Z�����B��srcH���C���̐��Ԃ�
	Sint32		srcH,
	Sint32		executeCode)  //Kitao�ǉ��B���s�R�[�h�B0�c�G���R�[�h�����s���B1�c�v���C�}����ʂ֓]�����s���B2�c�X�N���[���V���b�g�p��ʂ֓]�����s���B
								  //					   3�c���E�ɍ���(�I�[�o�[�X�L������)��z�u���Ă̓]��(���Ƃ�1�Ɠ���)
								  //					   5�c���E�̃I�[�o�[�X�L���������J�b�g���Ă̓]��(���Ƃ�1�Ɠ���)
{
	Uint32*			pSrc32;
	Uint16*			pTvW2;
	Sint32			scanLineType;

	if (pSrc==NULL) return;

	//v1.28�X�V�B���C���r������̃G���R�[�h�ɑΉ��B
	pSrc32 = pSrc + srcY * 512 + srcX;
	pTvW2 = pTvW + srcY;

	if (srcH > 0) //v2.43�X�V
	{
		if (lock_offscreen_surface(&_Pitch, &_pPixels)) //�o�b�N�T�[�t�F�X�����b�N
		{
			_Pitch2 = _Pitch * 2;
			_Pitch3 = _Pitch * 3;
			_Pitch4 = _Pitch * 4;
		
			//���x�d���̂��߂��ꂼ��̉�ʃ��[�h�ŁA�ʁX�̃��[�`�����g���B
			scanLineType = APP_GetScanLineType();
			if (MAINBOARD_GetMonoColor()) //�������[�h�Ȃ�B�͂ɂ����񂴂�����,�p���[�h���t�g���̗��Z
			{	//�������[�h�̏ꍇ�Bv2.28,2.29
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
							case 1:	zoom1xNS_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
									break;
							case 2:
							case 3:
							case 4:
								zoom2x3x4xNS_dd32(_Magnification, pSrc32, srcY, pTvW2, srcH); //32bit�J���[
								break;
						}
						break;
					case 1: //�c���X�L�������C��
						switch (_Magnification)
						{
							case 1:	zoom1xNS_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[�B���m���X�L�������C���Ɠ����B
									break;
							case 2:	zoom2x_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
									break;
							case 3:	zoom3x_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
									break;
							case 4:	zoom4x_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
									break;
						}
						break;
					case 2: //���X�L�������C��
					case 5: //���X�L�������C��2
					case 6: //���X�L�������C��3
						switch (_Magnification)
						{
							case 1:	zoom1xNS_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[�B���m���X�L�������C���Ɠ����B
									break;
							case 2:	zoom2xHS_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
									break;
							case 3:	zoom3xHS_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
									break;
							case 4:	zoom4xHS_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
									break;
						}
						break;
					case 3: //���X�L�������C��2(Fast)
					case 4: //TV���X�L�������C��
						switch (_Magnification)
						{
							case 1:	zoom1xNS_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[�B���m���X�L�������C���Ɠ����B
									break;
							case 2:	zoom2xTV_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
									break;
							case 3:	zoom3xTV_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
									break;
							case 4:	zoom4xTV_dd32(pSrc32, srcY, pTvW2, srcH); //32bit�J���[
									break;
						}
						break;
				}
			}

			//���b�N������
			_pD3DSGame->UnlockRect();
		}
	}

	//�v���C�}����ʂւ̓]��
	if (executeCode > 0)
		zoom_d3dTensou(pTvW+(16-MAINBOARD_GetShowOverscanTop()),
					   srcY+srcH-(16-MAINBOARD_GetShowOverscanTop()),
					   executeCode);
}


//VSync(�����A���҂�)���s�����ǂ�����ݒ�BVSync������ݒ�ł�Sync�ł��Ȃ����̏ꍇ�͎����ňꎞ�I�ɃI�t�ɂ���B
void
SCREEND3D_SetSyncTo60HzScreen(
	BOOL	bSyncTo60HzScreen)
{
	BOOL		bPrevSyncTo60HzScreen = _bSyncTo60HzScreen;
	DEVMODE		dm;

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
	//�ݒ肪�ύX���ꂽ�ꍇ�ADirect3D�I�u�W�F�N�g���������������B
	if (_bSyncTo60HzScreen != bPrevSyncTo60HzScreen)
		if (_pD3D != NULL) //���������I�����Ă���΁B�������O�ɌĂ΂ꂽ�ꍇ(App.c����Ă΂��)�͕ϐ��̍X�V�̂݁B
			SCREEND3D_ChangeMode(_Width, _Height, _Magnification, _Flags);
}

//VSync(�����A���҂�)���s���Ă��邩�ǂ�����Ԃ��BVSync������ݒ�ł�Sync�ł��Ȃ����̏ꍇ��FALSE���Ԃ�Bv2.43
BOOL
SCREEND3D_GetSyncTo60HzScreen()
{
	return _bSyncTo60HzScreen;
}


//Windows�̎���V-Sync�@�\����̕ϐ����X�V����Bv2.65
void
SCREEND3D_UpdateWindowsAutoVSync()
{
	SCREEND3D_ChangeMode(_Width, _Height, _Magnification, _Flags); //Direct3D�I�u�W�F�N�g���������������B
}


//�O���VBlank�҂����I�����������Ԃ��Bv1.28
DWORD
SCREEND3D_GetLastTimeSyncTime()
{
	return _LastTimeSyncTime;
}


//�X�N���[���V���b�g���t�@�C���ɏ������ށBv2.12
void
SCREEND3D_WriteScreenshot(
	FILE*	fp)
{
	int				i,j;
	D3DLOCKED_RECT	pLockedRect;
	HRESULT			hr;
	LONG			pitch;
	Uint32*			pPixels0;
	Uint32*			pPixels;
	Uint32			BGRR; //Bule,Green,Red,Reserved
	Sint32			width;
	Sint32			height;
	Sint32			left;
	Sint32			top;
	Sint32			w2,h2;
	Sint32			wp;

	//�o�b�t�@�ɍĕ`�悷��B
	if (((APP_GetOverscanHideBlackLR())&&(MAINBOARD_GetShowOverscanLeft() == 0))|| //���E�̃I�[�o�[�X�L�����̈�ɍ��ѕ\�����Ă����ꍇ
		((APP_GetOverscanHideBlackTop())&&(MAINBOARD_GetShowOverscanTop() < 8))) //�㑤�̃I�[�o�[�X�L�����̈�ɍ��ѕ\�����Ă����ꍇ
			MAINBOARD_SetResolutionChange(TRUE); //�`�掞�ɃS�~���c��Ȃ��悤�ɉ�ʑS�̂��N���A���Ă���`�悷��B
	MAINBOARD_DrawScreenshot();
	//��_pD3DDev->Present�ł̕\���X�V�͍s��Ȃ��B
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
		left = 0;
		top = 0;
	}

	//�L���v�`�����郁���������b�N
	hr = _pD3DSBack->LockRect(&pLockedRect, NULL, D3DLOCK_READONLY); //READONLY�ō������Bv2.28
	if (hr != D3D_OK) return;

	pitch = pLockedRect.Pitch / 4; //32bit�P�ʂŏ������邽�߃s�b�`��1/4�ɁB
	pPixels0 = (Uint32*)pLockedRect.pBits + pitch*(top+height-1) + left; //�ŉ��i����t�@�C���ɏo�͂��čs��(BMP�̎d�l)�B

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
	_pD3DSBack->UnlockRect();
}


//Kitao�ǉ��B�X�N���[���V���b�g���̂��߂Ɉꎞ�I�ɕ`��{����ύX����BScreen.cpp����g�p�Bv2.13
void
SCREEND3D_SetMagnification(
	Sint32	magnification)
{
	_Magnification = magnification;
}

//Kitao�ǉ��Bv2.13
Sint32
SCREEND3D_GetMagnification()
{
	return _Magnification;
}

//Kitao�ǉ��Bv2.19
BOOL
SCREEND3D_GetOldVideoChip()
{
	return _bOldVideoChip;
}


//���C��(�Q�[��)��ʗp�I�t�X�N���[�����P�F�œh��Ԃ��A�v���C�}����ʂ֓]������Bv2.77�X�V
void
SCREEND3D_Fill(
	Uint32		color)
{
	int			a,i,j;
	LONG		pitch;
	Uint32*		pPixels;
	Uint32*		pPixels0;
	Uint16		tvW[256];

	if (_Magnification == 1)
		a = 512;
	else
		a = 512*2;
	if (lock_offscreen_surface(&pitch, &pPixels))
	{
		pPixels0 = pPixels;
		for (i = 0; i < 256*_Magnification; i++)
		{
			pPixels = pPixels0;
			for (j = 0; j < a; j++)
				*pPixels++ = color; //4byte�Ԃ�(�P�h�b�g)�������܂��B
			for (j = 0; j < 8; j++)
				*pPixels++ = 0; //�E�[�W�h�b�g�͍��Ŗ��߂�iDirect3D�̃t�B���^�[�������ɃS�~���o���Ȃ����ߕK�v�j
			pPixels0 += pitch;
		}
		_pD3DSGame->UnlockRect();
	}

	//�v���C�}����ʂւ̓]��
	for (i = 0; i < 256; i++)
		tvW[i] = 256;
	zoom_d3dTensou(tvW, 224, 1);
}
