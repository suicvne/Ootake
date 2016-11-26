/******************************************************************************
Ootake

 [Option.cpp]
	�X�^�[�g���ɐݒ��ύX���邽�߂̃t�H�[��

Copyright(C)2006-2016 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

******************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "Option.h"
#include "resource.h"
#include "Startup.h"
#include "WinMain.h"
#include "App.h"
#include "JoyPad.h"
#include "ScreenD3D.h"

#define LINE_LEN	47
#define N_LINES 	23

enum OptionComponent
{
	BUTTON_HELP = 1,
	BUTTON_CDDATIMING,
	BUTTON_FUNCKEY,
	BUTTON_PADCONFIG,
	BUTTON_RESUME,
	COMBOBOX_SCREENTYPE,
	COMBOBOX_DRAWMODE,
	COMBOBOX_SOUNDBUFFER,
	BUTTON_LIGHT,
	BUTTON_DEFAULT,
	BUTTON_SET,
};
static HWND			_hWndC[BUTTON_SET]; //�e�R���|�[�l���g�̃n���h��

static HBRUSH		_hMyb; //����u���V�F
static HFONT		_hFontB; //�{�^���p�t�H���g

static Uint32		_FontWidth;
static Uint32		_FontHeight;
static const char*	_pCaption = "\"Ootake\" Setting";
static HINSTANCE	_hInstance = NULL;
static HWND 		_hWnd = NULL;


static Sint32		_ScreenType = -1; //�߂�l(���肵���ꍇ1�`5���Ԃ����)�B�L�����Z���Ȃ�-1�B���ݒ蒆��0�B
static Sint32*		_pScreenType;
static Sint32		_DrawMode = -1; //�߂�l(���肵���ꍇ1�`4���Ԃ����)�B�L�����Z���Ȃ�-1�B���ݒ蒆��0�B
static Sint32*		_pDrawMode;
static Sint32		_SoundBuffer = -1; //�߂�l(���肵���ꍇ1�`9���Ԃ����)�B�L�����Z���Ȃ�-1�B���ݒ蒆��0�B
static Sint32*		_pSoundBuffer;


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
	Uint32		wndW = _FontWidth  * LINE_LEN +_FontWidth;
	Uint32		wndH = _FontHeight * N_LINES +_FontHeight/2 -1;

	SetRect(&rc, 0, 0, wndW, wndH);
	AdjustWindowRectEx(&rc, GetWindowLong(hWnd, GWL_STYLE),
						GetMenu(hWnd) != NULL, GetWindowLong(hWnd, GWL_EXSTYLE));
	wndW = rc.right - rc.left;
	wndH = rc.bottom - rc.top;
	GetWindowRect(STARTUP_GetHwnd(), &rc);
	MoveWindow(hWnd, rc.left, rc.bottom - wndH, wndW, wndH, TRUE);
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

	x = _FontWidth*2 +1;
	y = _FontHeight/2;
	TextOut(hDC, x, y, "Important Setting  �d�v�Ȑݒ�", 29);
	y += _FontHeight*9 +1;
	TextOut(hDC, x, y, "Push button, and Explanation is displayed.", 42);
	y += _FontHeight;
	TextOut(hDC, x, y, "�{�^���������Ɛ������\������܂��B", 34);

	y = _FontHeight*13 -1;
	TextOut(hDC, x, y, "Video Setting  �r�f�I���̐ݒ�", 31);
	y += _FontHeight*5;
	TextOut(hDC, x, y, "Sound Setting  �T�E���h���̐ݒ�", 33);

	/* �I������ */
	EndPaint(hWnd, &ps);
	SelectObject(hDC, hFontOld);
	DeleteObject(hFont);
	ReleaseDC(hWnd, hDC);
}


static LRESULT CALLBACK
option_wnd_proc(
	HWND		hWnd,
	UINT		uMsg,
	WPARAM		wParam,
	LPARAM		lParam)
{
	BOOL		bOk;
	Sint32		screenType;

	switch(uMsg)
	{
	case WM_CREATE:
		EnableWindow(STARTUP_GetHwnd(), FALSE);//�X�^�[�g�A�b�v�E�B���h�E�𖳌������ă��[�_���ɁB
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
			OPTION_Deinit();
			return 0;
		}
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case BUTTON_HELP: //v2.77�ǉ�
				MessageBox(hWnd,
					"For the important setting of Ootake, please use the four buttons on    \n"
					"the left.    \n"
					"In lower side of the setting screen, the setting of Video and Sound    \n"
					"can be set. When you press the [Set]button(bottom-right of window),    \n"
					"it will reflect the setting.    \n"
					"In addition, the menu appears when you click on the game screen    \n"
					"during game play. It can be a variety of settings. Please select   \n"
					"[Info -> Manual-English] menu(rightmost of menu), and the    \n"
					"explanation of each menu is displayed.    \n"
					"\n"
					"In Japanese language\n"
					"���̂S�̃{�^���ŁAOotake�̓���ɕK�v�ƂȂ��{�I�ȁi�d�v�ȁj   \n"
					"�ݒ���s���܂��B\n"
					"�ݒ��ʉ����́A�r�f�I�ƃT�E���h�̐ݒ�́A��ԉE����[Set]�{�^��   \n"
					"�������ƁA�ݒ肪���f����܂��B   \n"
					"�����̐ݒ�́A�Q�[���v���C���ɉ�ʂ��N���b�N����ƌ���郁�j���[   \n"
					"������ݒ肷�邱�Ƃ��ł��܂��B�e���j���[�̐����́A���j���[��ԉE��   \n"
					"[Info -> Manual-Japanese]��I�����Ă��������B   ",
					"About Ootake Setting", MB_OK);
				break;

			case BUTTON_CDDATIMING: //v2.77�ǉ�
				bOk = MessageBox(hWnd,
					"The timing value of the CD sound (CD-DA and ADPCM) is set    \n"
					"automatically to match the sound to the picture.    \n"
					"The set completion is about 60 seconds. Please close other heavy    \n"
					"applications for an accurate measurement now. This automatic    \n"
					"setting starts when \"Yes\" is pushed.    \n"
					"\n"
					"In Japanese language\n"
					"���g���̃p�\�R�����ɂ����āA�G��CD�����iCD-DA,ADPCM�j�̃Y��   \n"
					"���N����Ȃ��悤�ɁA�^�C�~���O�l�������ݒ肵�܂��B\n"
					"�ݒ芮���܂Ŗ�60�b�Ԋ|����܂��B���̊ԁAOotake���������������Ȃ�   \n"
					"���߂ɁA���̏d���A�v���P�[�V�����͕��Ă��������B\"�͂�\"�������ƁA   \n"
					"�����ݒ���J�n���܂��B",
					"About \"CD-DA Play Timing\" Setting", MB_YESNO);
				if (bOk == IDYES)
				{
					screenType = SendMessage(GetDlgItem(hWnd, COMBOBOX_SCREENTYPE), CB_GETCURSEL, 0, 0) + 1;
					switch (screenType) //�E�B���h�E���[�h���t���X�N���[�����[�h���̐ݒ��ύX���Ă���ꍇ�A�����Őݒ���m�肷��B
					{
					case 1:	APP_SetStartFullScreen(FALSE); break;
					case 2:
						APP_SetMagnification(2); //x2�{�ɐݒ�
						APP_SetStartFullScreen(FALSE);
						break;
					case 3:
						APP_SetMagnification(3); //x3�{�ɐݒ�
						APP_SetStartFullScreen(FALSE);
						break;
					case 4:
						APP_SetMagnification(4); //x4�{�ɐݒ�
						APP_SetStartFullScreen(FALSE);
						break;
					case 5:	APP_SetStartFullScreen(TRUE); break;
					case 6:
						APP_SetFullScreen640(); //640x480�ɐݒ�
						APP_SetStartFullScreen(TRUE);
						break;
					}
					APP_UpdateScreenMode(FALSE); //�Q�[���E�B���h�E�����������\��
					SetForegroundWindow(WINMAIN_GetHwnd()); //�Q�[���E�B���h�E����O�ɕ\��
					if (APP_GetFullScreen())
						Sleep(3000); //Windows�̉�ʐ؂�ւ��̏������������Ă���ԂɌv�����n�߂Ă��܂��Ə��������Ō�v���ɂȂ��Ă��܂��̂łR�b�҂B
					else
						Sleep(1000); //Window���[�h�̏ꍇ�͂P�b�B
					APP_SetCddaTimingAuto(); //�^�C�~���O�������ݒ�
					APP_SaveConfig();//�ݒ��ۑ�
					MessageBox(WINMAIN_GetHwnd(),
						"While playing a game, the menu (click on the game screen)    \n"
						"[Audio -> Adjust CD-DA (for Sync) -> Adjust CD-DA Auto Set]    \n"
						"can be used to set this setting.    \n"
						"If there is a gap of CD-DA, please use it.    \n"
						"\n"
						"In Japanese language\n"
						"���̐ݒ�́A�Q�[�������j���[�i�Q�[����ʂ��N���b�N�j��   \n"
						"�uAudio -> Adjust CD-DA (for Sync) -> Adjust CD-DA Auto Set�v   \n"
						"������ݒ肷�邱�Ƃ��ł��܂��B���Y�����������ꍇ�A�Đݒ肵�Ă݂�   \n"
						"���������B   \n"
						"���Q�[���ɂ���ẮA���@�ł����Y�����Ă�����̂�����܂��B   \n"
						"�@Ootake���������̃Q�[���ȏꍇ�A���m�点��������΁A�\�Ȍ���   \n"
						"�@�ł����A�C���������܂��B   ",
						"About \"CD-DA Play Timing\" Setting", MB_OK);
					if (APP_GetFullScreen()) //�t���X�N���[�����[�h�������ꍇ�A�f�X�N�g�b�v�\���֖߂��B
					{
						APP_SetFullScreen(FALSE);
						APP_UpdateScreenMode(FALSE);
						APP_SetFullScreen(TRUE);
					}
					WINMAIN_SetMiniSize(); //�Q�[���E�B���h�E���ŏ���
					SetForegroundWindow(hWnd); //�ݒ�E�B���h�E����O�ɕ\��
				}
				break;
		
			case BUTTON_FUNCKEY: //v2.77�ǉ�
				bOk = MessageBox(hWnd,
					"Witn Ootake, you can set the \"Function Button\" on your joypad.    \n"
					"[ Set the button you press with your left hand index finger(e.g.     \n"
					"  L2 button at the PS-Pad) to the \"Function Button\". It is    \n"
					"  very useful because it can be various settings at hand. ]    \n"
					"Function Button + [I]  button -> Switching of Auto-fire(Turbo)    \n"
					"Function Button + [II] button -> Switching of Auto-fire(Turbo)    \n"
					"Function Button + [RUN] button -> Switching the Game Soft.    \n"
					"Function Button + [SELECT] button -> Shooting of Screenshots    \n"
					"Function Button + Up,Down,Left,Right -> Audio Volume control    \n"
					"+ Operate while Pressing the Function Button    \n"
					"Press \"Yes\" button, and Setup-Screen appears.    \n\n"
					"In Japanese language\n"
					"Ootake�́A�W���C�p�b�h���\"�t�@���N�V�����{�^��\"��ݒ�ł��܂��B   \n"
					"[ ����l�����w�ŉ����{�^���i�Ⴆ��PS�^�Ȃ�L2�{�^���j���t�@���N   \n"
					"  �V�����{�^���ɐݒ肷��ƁA�茳�ŐF�X�ݒ�ł���̂ŕ֗��ł��B]   \n"
					"�t�@���N�V�����{�^���{ I�{�^�� or II�{�^���c�u�A�ːݒ�̐ؑցv   \n"
					"�t�@���N�V�����{�^���{ RUN�{�^���c�u�Q�[���̐ؑցv   \n"
					"�t�@���N�V�����{�^���{ SELECT�{�^���c�u�X�N���[���V���b�g�ۑ��v   \n"
					"�t�@���N�V�����{�^���{ �\���L�[�c�u���ʂ̒��߁v   \n"
					"����L�̑���́A�t�@���N�V�����{�^���������Ȃ��瑀�삵�܂��B   \n"
					"�u�͂��v�������Ɛݒ��ʂ��o�܂��̂ŁA�{�^���������Ă��������B   \n",
					"About \"Function Button\" Setting", MB_YESNO);
				if (bOk == IDYES)
				{
					APP_SetShortcutButton(_hWnd, _hInstance, 6);
					APP_SaveConfig();//�ݒ��ۑ�
				}
				break;
		
			case BUTTON_PADCONFIG: //v2.77�ǉ�
				bOk = MessageBox(hWnd,
					"In real machine \"PC Engine(TG16)\", three types of game pad (    \n"
					"[2 button pad],[3 button pad],and [6 button pad]) exists.    \n"
					"In Ootake, setting of the button is set by three separate    \n"
					"settings. And, settings of three types are saved.    \n"
					"Press \"Yes\" button, and Setup-Screen appears. In the order of    \n"
					"[2 button pad],[3 button pad],and [6 button pad], please set it.    \n"
					"+In real machine, [RUN] or [SELECT] either is selected at    \n"
					" [III]button of [3 button pad]. In Ootake, set [IIIr]button and    \n"
					" [IIIs]button, and they can be used at the same time.    \n\n"
					"In Japanese language\n"
					"PC�G���W���i���@�j�ɂ́A�u�Q�{�^���v�u�R�{�^���v�u�U�{�^���v��   \n"
					"�R��ނ̃Q�[���p�b�h�����݂��܂��B   \n"
					"Ootake�ł́A�{�^���ݒ���R��ޕʁX�ɐݒ肵�A�ʁX�ɕۑ����܂��B   \n"
					"�u�͂��v�������Ɛݒ��ʂ��o�܂��̂ŁA�u�Q�{�^���v�u�R�{�^���v   \n"
					"�u�U�{�^���v�̏��ɂR��ނԂ�A�{�^���������Đݒ肵�Ă��������B   \n"
					"���u�R�{�^���p�b�h�v�́A���@�ł͂R�{�^���ڂ��uRUN,SELECT�ǂ���   \n"
					"�@����؂�ւ��Ďg�p�v�ł������AOotake�ł́ARUN��SELECT��ʁX   \n"
					"�@�ɂ��ꂼ����uIIIr�{�^��,IIIs�{�^���Ƃ��Đݒ�v���܂��B   \n",
					"About \"PCE-Pad Controller\" Setting", MB_YESNO);
				if (bOk == IDYES)
				{
					//�Q�{�^���p�b�h��ݒ�
					APP_ConfigurePad(_hWnd, _hInstance, 1);
					//�R�{�^���p�b�h��ݒ�
					JOYPAD_UseThreeButton(TRUE);
					APP_SetInputConfiguration();
					APP_ConfigurePad(_hWnd, _hInstance, 1);
					//�U�{�^���p�b�h��ݒ�
					JOYPAD_UseSixButton(TRUE);
					APP_SetInputConfiguration();
					APP_ConfigurePad(_hWnd, _hInstance, 1);
					//�Q�{�^���p�b�h���Ȃ����Ă����Ԃɖ߂�
					APP_ReturnCaption(); //�U�{�^���p�b�h�ݒ芮���̃��b�Z�[�W�������B
					JOYPAD_UseThreeButton(FALSE);
					JOYPAD_UseSixButton(FALSE);
					APP_SetInputConfiguration();
					APP_SaveConfig();//�ݒ��ۑ�
					MessageBox(hWnd,
						"Pad configuration is complete.    \n"
						"In the game for 2-5 players, connect multiple game pads to your    \n"
						"PC. Or, use the keyboard.    \n"
						"For the setting of 2-5 players, click the    \n"
						"[Input -> Configure Pad #2-#5] menu.    \n"
						"(The menu appears when you click on the game screen during    \n"
						"game play.)    \n\n"
						"In Japanese language\n"
						"�p�b�h�ݒ肪�������܂����B   \n"
						"�Ȃ��A�Q�l�`�T�l�v���C�Ή��̃Q�[���ł́A�p�\�R���ɃQ�[���p�b�h��   \n"
						"�����Ȃ��邩�A�L�[�{�[�h�̗��p�ŁA���@���l�̃v���C���ł��܂��B   \n"
						"�Q�`�T�v���C���[�̃R���g���[���[�ݒ�́A�Q�[�������j���[�i�Q�[��   \n"
						"��ʂ��N���b�N����Əo�܂��j�̉E����Q�ڂɂ���   \n"
						"�uInput -> Configure Pad #2-#5�v���j���[����s���Ă��������B   ",
						"About \"PCE-Pad Controller\" Setting", MB_OK);
				}
				break;

			case BUTTON_RESUME: //v2.77�ǉ�
				bOk = MessageBox(hWnd,
					"Ootake has \"Resume Mode\" that performing a state save    \n"
					"automatically. When the game is started in the next time,    \n"
					"you can play from the continuation of the last end. In addition,    \n"
					"the settings(Sound Volume and Auto-fire, etc.) are loaded in    \n"
					"every game.    \n"
					"For using \"Resume Mode\", click the [File -> Set Resume] menu,    \n"
					"and \"Resume Mode\" switch of the playing game become ON.    \n"
					"(The menu appears when you click on the game screen during    \n"
					"game play.)    \n"
					"If you want to automatically turn on the \"Resume Mode\" in all    \n"
					"of the games, press [Yes]button(at bottom of this window).    \n"
					"If you want to manually turn on(off) to each game, press    \n"
					"[No]button(at bottom of this window).    \n"
					"\n"
					"In Japanese language\n"
					"Ootake�́A�Q�[���I�����Ɏ����ŃX�e�[�g�Z�[�u���s���u���W���[���@�\�v   \n"
					"������܂��B����̃Q�[���J�n���ɁA�O��I��������������v���C�ł��A   \n"
					"�T�E���h���ʂ�A�˓��̐ݒ���A�Q�[�����ɓǂݍ��܂�܂��B   \n"
					"�u���W���[���@�\�v�́A���W���[���@�\���g�������Q�[�����v���C���ɁA   \n"
					"���j���[�i�Q�[����ʂ��N���b�N�j����A[File -> Set Resume]���j���[��   \n"
					"�I�����ă`�F�b�N�����邱�ƂŃI���ɂł��܂��B   \n"
					"�S�ẴQ�[���Łu���W���[���@�\�v�������I�ɃI���ɂ������ꍇ�́A   \n"
					"���́u�͂��v�������Ă��������B��L�̂悤�Ɏ蓮�ŃQ�[�����ɃI���I�t   \n"
					"�������ꍇ�́A�u�������v�������Ă��������B   ",
					"About \"Resume(Auto Save) Mode\" Setting", MB_YESNO);
				if (bOk == IDYES)
					APP_SetAutoResumeMode(TRUE);
				else
					APP_SetAutoResumeMode(FALSE);
				APP_SaveConfig();//�ݒ��ۑ�
				break;
		
			case COMBOBOX_SCREENTYPE:
			case COMBOBOX_DRAWMODE:
			case COMBOBOX_SOUNDBUFFER:
				if (HIWORD(wParam) == CBN_CLOSEUP)
					SetFocus(GetDlgItem(hWnd, BUTTON_SET));//OK�{�^���Ƀt�H�[�J�X
				break;

			case BUTTON_LIGHT:
				SendMessage(_hWndC[COMBOBOX_SCREENTYPE], CB_SETCURSEL, 5, 0);
				SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_SETCURSEL, 5, 0);
				SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_SETCURSEL, 7, 0);
				break;

			case BUTTON_DEFAULT:
				SendMessage(_hWndC[COMBOBOX_SCREENTYPE], CB_SETCURSEL, 2, 0);
				SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_SETCURSEL, 0, 0);
				SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_SETCURSEL, 5, 0);
				break;

			case BUTTON_SET:
				//�߂�l��ݒ�
				_ScreenType = SendMessage(GetDlgItem(hWnd, COMBOBOX_SCREENTYPE), CB_GETCURSEL, 0, 0) + 1;
				_DrawMode = SendMessage(GetDlgItem(hWnd, COMBOBOX_DRAWMODE), CB_GETCURSEL, 0, 0) + 1;
				_SoundBuffer = SendMessage(GetDlgItem(hWnd, COMBOBOX_SOUNDBUFFER), CB_GETCURSEL, 0, 0) + 1;
				OPTION_Deinit();
				return 0;
		}
		break;

	case WM_CLOSE:
		OPTION_Deinit();
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


static BOOL
option_main()
{
	WNDCLASS	wc;
	HWND		hWnd;
	RECT		rc;
	Uint32		x;
	Uint32		y;
	HWND		hWndTmp;
	char		pCaption[64];
	
	strcpy_s(pCaption, 64, "\"Ootake v");
	strcat_s(pCaption, 64, APP_GetSoftVersionChar());
	strcat_s(pCaption, 64, "\" Setting");
	
	ZeroMemory(&wc, sizeof(wc));
	wc.style		 = 0;
	wc.lpfnWndProc	 = option_wnd_proc;
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
		pCaption,
		WS_SYSMENU | WS_CAPTION,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		STARTUP_GetHwnd(),
		NULL,
		_hInstance,
		NULL
	);

	if (hWnd == NULL)
		return FALSE;

	_hWnd = hWnd;

	//CD-DA Timing�{�^�����쐬
	x = _FontWidth*2;
	y = _FontHeight +_FontHeight/2 +3;
	hWndTmp = CreateWindow(
		"BUTTON", "Set CD-DA Play Timing",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x, y, _FontWidth*38, _FontHeight*2-3,
		_hWnd, (HMENU)BUTTON_CDDATIMING, _hInstance, NULL
	);
	SendMessage(hWndTmp, WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));//�t�H���g��ݒ�

	//Help�{�^�����쐬
	x += _FontWidth*40;
	hWndTmp = CreateWindow(
		"BUTTON", "?",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x, y, _FontWidth*4, _FontHeight*2-3,
		_hWnd, (HMENU)BUTTON_HELP, _hInstance, NULL
	);
	SendMessage(hWndTmp, WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));

	//FunctionButton�{�^�����쐬
	x = _FontWidth*2;
	y += _FontHeight*2;
	hWndTmp = CreateWindow(
		"BUTTON", "Set Function-Button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x, y, _FontWidth*38, _FontHeight*2-3,
		_hWnd, (HMENU)BUTTON_FUNCKEY, _hInstance, NULL
	);
	SendMessage(hWndTmp, WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));

	//PadConfig�{�^�����쐬
	y += _FontHeight*2;
	hWndTmp = CreateWindow(
		"BUTTON", "Set Button of PCE-Pad Controller",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x, y, _FontWidth*38, _FontHeight*2-3,
		_hWnd, (HMENU)BUTTON_PADCONFIG, _hInstance, NULL
	);
	SendMessage(hWndTmp, WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));

	//Resume�{�^�����쐬
	y += _FontHeight*2;
	hWndTmp = CreateWindow(
		"BUTTON", "Set Resume (Auto Save) Mode",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x, y, _FontWidth*38, _FontHeight*2-3,
		_hWnd, (HMENU)BUTTON_RESUME, _hInstance, NULL
	);
	SendMessage(hWndTmp, WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));

	//�t���X�N���[��or�E�B���h�E���[�h�ؑ֗p�R���{�{�b�N�X���쐬
	x = _FontWidth*2;
	y = _FontHeight*14;
	_hWndC[COMBOBOX_SCREENTYPE] = CreateWindow(
		"COMBOBOX", "",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
		x, y, _FontWidth*42, _FontHeight*9,
		_hWnd, (HMENU)COMBOBOX_SCREENTYPE, _hInstance, NULL
	);
	SendMessage(_hWndC[COMBOBOX_SCREENTYPE], WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));//�t�H���g��ݒ�
	SendMessage(_hWndC[COMBOBOX_SCREENTYPE], CB_ADDSTRING, 0, (LPARAM)"Start Window mode");
	SendMessage(_hWndC[COMBOBOX_SCREENTYPE], CB_ADDSTRING, 0, (LPARAM)"Start Window (x2)");
	SendMessage(_hWndC[COMBOBOX_SCREENTYPE], CB_ADDSTRING, 0, (LPARAM)"Start Window (x3)");
	SendMessage(_hWndC[COMBOBOX_SCREENTYPE], CB_ADDSTRING, 0, (LPARAM)"Start Window (x4)");
	SendMessage(_hWndC[COMBOBOX_SCREENTYPE], CB_ADDSTRING, 0, (LPARAM)"Start FullScreen mode");
	SendMessage(_hWndC[COMBOBOX_SCREENTYPE], CB_ADDSTRING, 0, (LPARAM)"Start FullScreen (640x480)");
	if (APP_GetStartFullScreen())
		SendMessage(_hWndC[COMBOBOX_SCREENTYPE], CB_SETCURSEL, 4, 0);
	else
		SendMessage(_hWndC[COMBOBOX_SCREENTYPE], CB_SETCURSEL, 0, 0);

	//TV or RGB�ؑ֗p�R���{�{�b�N�X���쐬
	x = _FontWidth*2;
	y += _FontHeight*2;
	_hWndC[COMBOBOX_DRAWMODE] = CreateWindow(
		"COMBOBOX", "",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
		x, y, _FontWidth*42, _FontHeight*14,
		_hWnd, (HMENU)COMBOBOX_DRAWMODE, _hInstance, NULL
	);
	SendMessage(_hWndC[COMBOBOX_DRAWMODE], WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));
	SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_ADDSTRING, 0, (LPARAM)"Special Scanlined (Sharp&Gentle)");
	SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_ADDSTRING, 0, (LPARAM)"TV Scanlined (Smooth, Fast)");
	SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_ADDSTRING, 0, (LPARAM)"Horizontal Scanlined");
	SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_ADDSTRING, 0, (LPARAM)"Horizontal Scanlined 2 (Sharp)");
	SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_ADDSTRING, 0, (LPARAM)"Horizontal Scanlined 3 (More)");
	SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_ADDSTRING, 0, (LPARAM)"Horizontal Scanlined F (Fast)");
	SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_ADDSTRING, 0, (LPARAM)"Non-Scanlined (Fast)");
	SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_ADDSTRING, 0, (LPARAM)"Non-Scanlined 2 (Sharp, Fast)");
	SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_ADDSTRING, 0, (LPARAM)"Non-Scanlined TV (Smooth, Fast)");
	switch (APP_GetScanLineType())
	{
		case 0: SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_SETCURSEL, 6, 0); break;
		case 1: SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_SETCURSEL, 0, 0); break;
		case 2: SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_SETCURSEL, 2, 0); break;
		case 3: SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_SETCURSEL, 5, 0); break;
		case 4: SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_SETCURSEL, 1, 0); break;
		case 5: SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_SETCURSEL, 3, 0); break;
		case 6: SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_SETCURSEL, 4, 0); break;
		case 7: SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_SETCURSEL, 7, 0); break;
		case 8: SendMessage(_hWndC[COMBOBOX_DRAWMODE], CB_SETCURSEL, 8, 0); break;
	}

	//�T�E���h�o�b�t�@�p�R���{�{�b�N�X���쐬
	x = _FontWidth*2;
	y = _FontHeight*19;
	_hWndC[COMBOBOX_SOUNDBUFFER] = CreateWindow(
		"COMBOBOX", "",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
		x, y, _FontWidth*42, _FontHeight*18,
		_hWnd, (HMENU)COMBOBOX_SOUNDBUFFER, _hInstance, NULL
	);
	SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));
	SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_ADDSTRING, 0, (LPARAM)"Buffer 1024 (Not Delay)");
	SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_ADDSTRING, 0, (LPARAM)"Buffer 1152");
	SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_ADDSTRING, 0, (LPARAM)"Buffer 1280");
	SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_ADDSTRING, 0, (LPARAM)"Buffer 1408");
	SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_ADDSTRING, 0, (LPARAM)"Buffer 1536");
	SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_ADDSTRING, 0, (LPARAM)"Buffer 1664 (Default)");
	SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_ADDSTRING, 0, (LPARAM)"Buffer 1792");
	SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_ADDSTRING, 0, (LPARAM)"Buffer 2048");
	SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_ADDSTRING, 0, (LPARAM)"Buffer 2176");
	SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_ADDSTRING, 0, (LPARAM)"Buffer 2304");
	SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_ADDSTRING, 0, (LPARAM)"Buffer 2560");
	SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_ADDSTRING, 0, (LPARAM)"Buffer 3072 (Beauty,Delay)");
	switch (APP_GetSoundBufferSize())
	{
		case 1024: SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_SETCURSEL,  0, 0); break;
		case 1152: SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_SETCURSEL,  1, 0); break;
		case 1280: SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_SETCURSEL,  2, 0); break;
		case 1408: SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_SETCURSEL,  3, 0); break;
		case 1536: SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_SETCURSEL,  4, 0); break;
		case 1792: SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_SETCURSEL,  6, 0); break;
		case 2048: SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_SETCURSEL,  7, 0); break;
		case 2176: SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_SETCURSEL,  8, 0); break;
		case 2304: SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_SETCURSEL,  9, 0); break;
		case 2560: SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_SETCURSEL, 10, 0); break;
		case 3072: SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_SETCURSEL, 11, 0); break;
		default: //1664
			SendMessage(_hWndC[COMBOBOX_SOUNDBUFFER], CB_SETCURSEL, 5, 0); break;
	}

	//Light�{�^�����쐬
	x = _FontWidth*2;
	y = _FontHeight*21;
	hWndTmp = CreateWindow(
		"BUTTON", "Light(Fast)",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x, y, _FontWidth*13, _FontHeight*2-3,
		_hWnd, (HMENU)BUTTON_LIGHT, _hInstance, NULL
	);
	SendMessage(hWndTmp, WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));//�t�H���g��ݒ�

	//Default�{�^�����쐬
	x += _FontWidth*14;
	hWndTmp = CreateWindow(
		"BUTTON", "Default(HQ)",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x, y, _FontWidth*14, _FontHeight*2-3,
		_hWnd, (HMENU)BUTTON_DEFAULT, _hInstance, NULL
	);
	SendMessage(hWndTmp, WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));

	//Set�{�^�����쐬
	x = _FontWidth*36;
	y = _FontHeight*21;
	hWndTmp = CreateWindow(
		"BUTTON", "Set",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x, y, _FontWidth*10, _FontHeight*2-3,
		_hWnd, (HMENU)BUTTON_SET, _hInstance, NULL
	);
	SendMessage(hWndTmp, WM_SETFONT, (WPARAM)_hFontB, MAKELPARAM(TRUE, 0));

	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);
	GetWindowRect(_hWnd, &rc);
	SetWindowPos(_hWnd, HWND_TOP, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_FRAMECHANGED);
	ImmAssociateContext(_hWnd, 0); //IME�𖳌��ɂ���

	return TRUE;
}


BOOL
OPTION_Init(
	HINSTANCE	hInstance,
	Sint32*		screenType,
	Sint32*		drawMode,
	Sint32*		soundBuffer)
{
	if (_hInstance != NULL)
		OPTION_Deinit();

	_hInstance = hInstance;

	_pScreenType = screenType;
	_ScreenType = -1;//�L�����Z��
	_pDrawMode = drawMode;
	_DrawMode = -1;//�L�����Z��
	_pSoundBuffer = soundBuffer;
	_SoundBuffer = -1;//�L�����Z��

	return option_main();
}


void
OPTION_Deinit()
{
	if (_hInstance != NULL)
	{
		DestroyWindow(_hWnd);
		_hWnd = NULL;
		UnregisterClass(_pCaption, _hInstance);
		_hInstance = NULL;
		
		DeleteObject(_hFontB); //�{�^���p�t�H���g���J��
		DeleteObject(_hMyb); //�u���V���J��
		
		//�X�^�[�g�A�b�v�E�B���h�E�Ƀt�H�[�J�X��߂��O�ʂɁB
		EnableWindow(STARTUP_GetHwnd(), TRUE);
		SetForegroundWindow(STARTUP_GetHwnd());
		
		//�߂�l��ݒ�
		*_pScreenType = _ScreenType;
		*_pDrawMode = _DrawMode;
		*_pSoundBuffer = _SoundBuffer; //���̏u�Ԃ�Startup.c �ɐ��䂪�߂�B
	}
}


HWND
OPTION_GetHWnd()
{
	return _hWnd;
}

