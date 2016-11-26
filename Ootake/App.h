/******************************************************************************
	[App.h]
		�A�v���P�[�V�����̃C���^�t�F�C�X���`���܂��D

	Copyright (C) 2004 Ki

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/
#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include "TypeDefs.h"

#define	APP_CONFIG_FILENAME	"Ootake.dat" //Kitao�X�V

//Kitao�ǉ�
#ifndef SPI_GETFOREGROUNDLOCKTIMEOUT
#define SPI_GETFOREGROUNDLOCKTIMEOUT 0x2000
#endif
#ifndef SPI_SETFOREGROUNDLOCKTIMEOUT
#define SPI_SETFOREGROUNDLOCKTIMEOUT 0x2001
#endif


enum AppEvent
{
	APP_IDLE,
	APP_QUIT,
};

BOOL
APP_Init(
	int		argc,
	char**	argv);

Sint32
APP_ProcessEvents();

BOOL
APP_Deinit();

//Kitao�ǉ�
void
APP_RunEmulator(
	BOOL	bRun);

//Kitao�ǉ�
BOOL
APP_GetCDGame();

//Kitao�ǉ�
void
APP_SetCDGame();

//Kitao�ǉ�
void
APP_SetGameFileNameBuf();

//Kitao�ǉ��B�E�B���h�E�̈ʒu��ۑ��BWinMain.c������g�p�B
void
APP_SaveWindowPosition();

//Kitao�ǉ��BV-Sync���j���[��Enable�܂��͊D�F�ɁB
void
APP_EnableVSyncMenu(
	BOOL screen60hz);

//Kitao�ǉ��B���j���[��\�������ǂ�����Ԃ�
BOOL
APP_GetRunning();

//Kitao�ǉ��B�A�v���P�[�V����(Ootake)�̃p�X��Ԃ��B
char*
APP_GetAppPath();

//Kitao�ǉ��B�g�p����CD�h���C�u�̃i���o�[��Ԃ��B��0�Ȃ�P��ځB1�Ȃ�Q��ځB
Sint32
APP_GetCurrentCdDrive();

//Kitao�ǉ��BPSG�̃{�����[����Ԃ��B
Uint32
APP_GetPsgVolume();

//Kitao�ǉ��BADPCM�̃{�����[����Ԃ��B
Uint32
APP_GetAdpcmVolume();

//Kitao�ǉ��BCD�̃{�����[����Ԃ��B
Uint32
APP_GetCdVolume();

//Kitao�ǉ�
void
APP_SetStretched(
	BOOL	bStretched,
	BOOL	bVStretched,
	BOOL	bFullStretched);

//Kitao�ǉ�
void
APP_SetStartStretchMode(
	Sint32	startStretchMode);

//v2.64�ǉ�
Sint32
APP_GetStartStretchMode();

//Kitao�ǉ�
void
APP_TurboCycleMenu(
	BOOL	bAuto);

//Kitao�ǉ�
void
APP_SetAutoOverClock(
	Sint32	n);

//Kitao�ǉ�
void
APP_SetSpeedNormal();

//Kitao�ǉ�
Sint32
APP_GetRenshaSpeedSel();

//Kitao�ǉ�
void
APP_SetRenshaSpeedSel(
	Sint32	renshaSpeedSel);

//Kitao�ǉ�
void
APP_EndRecording();

//Kitao�ǉ�
void
APP_EndPlayRecord();

//Kitao�ǉ�
void
APP_SetFullScreen(
	BOOL	bFullScreen);

//Kitao�ǉ�
BOOL
APP_GetFullScreen();

//Kitao�ǉ�
BOOL
APP_GetHideMessage();

//Kitao�ǉ�
BOOL
APP_GetFullHideMessage();

//Kitao�ǉ�
void
APP_SetHideMessage(
	BOOL	bHideMessage);

//Kitao�ǉ�
void
APP_SetFullHideMessage(
	BOOL	bFullHideMessage);

//Kitao�ǉ�
BOOL
APP_GetDefaultFastCD();

//Kitao�ǉ�
BOOL
APP_GetDefaultFastSeek();

//Kitao�ǉ�
BOOL
APP_GetDefaultSpriteLimit();

//Kitao�ǉ�
void
APP_SetInputConfiguration();

//Kitao�ǉ�
char*
APP_GetGameFileNameBuf();

//Kitao�ǉ�
char*
APP_GetGameFilePathName();

//Kitao�ǉ�
void
APP_SetAppName(
	char*	pAppName);

//Kitao�ǉ�
char*
APP_GetAppName();

//Kitao�ǉ�
BOOL
APP_GetStretched();

//Kitao�ǉ�
BOOL
APP_GetVStretched();

//Kitao�ǉ�
BOOL
APP_GetFullStretched(
	BOOL	bFilter);

//Kitao�ǉ�
BOOL
APP_GetSyncTo60HzScreen();

//Kitao�ǉ�
void
APP_SetSyncTo60HzScreen(
	BOOL	bSyncTo60HzScreen);

//Kitao�ǉ�
BOOL
APP_GetForceVSync();

//Kitao�ǉ�
Sint32
APP_GetScanLineType();

//Kitao�ǉ�
void
APP_SetScanLineType(
	Sint32	scanLineType,
	BOOL	configWrite);

//Kitao�ǉ�
Sint32
APP_GetScanLineDensity();

//Kitao�ǉ�
BOOL
APP_GetOptimizeGamma();

//Kitao�ǉ�
double
APP_GetGammaValue();

//Kitao�ǉ�
Sint32
APP_GetBrightValue();

//Kitao�ǉ�
BOOL
APP_GetHalfMode();

//Kitao�ǉ�
Sint32
APP_GetMonoColorMode();

//Kitao�ǉ�
void
APP_SetUseVideoSpeedUpButton(
	BOOL	bUseVideoSpeedUpButton);

//Kitao�ǉ�
BOOL
APP_GetUseVideoSpeedUpButton();

//Kitao�ǉ�
void
APP_ToggleUseVideoSpeedUpButton();

//Kitao�ǉ�
void
APP_MenuShow(
	BOOL	bShow);

//Kitao�ǉ�
void
APP_SetForegroundWindowOotake();

//Kitao�ǉ�
BOOL
APP_GetWindows9x();

//Kitao�ǉ�
BOOL
APP_GetWindowsVista();

//Kitao�ǉ�
BOOL
APP_GetWindows7();

//Kitao�ǉ�
BOOL
APP_GetPauseNoRelease();

//Kitao�ǉ�
void
APP_ResetMouseStopCount();

//Kitao�ǉ�
void
APP_SetF1NoReset(
	BOOL	bF1NoReset);

//Kitao�ǉ�
BOOL
APP_GetF1NoReset();

//Kitao�ǉ�
void
APP_UpdateMenu();

//Kitao�ǉ�
void
APP_OpenInstallFolder();

//Kitao�ǉ�
void
APP_OpenSaveFolder();

//Kitao�ǉ�
void
APP_SetStartFullScreen(
	BOOL	bStartFullScreen);

//Kitao�ǉ�
BOOL
APP_GetStartFullScreen();

//Kitao�ǉ�
void
APP_SetSoundMethod(
	Sint32	soundMethod);

//Kitao�ǉ�
Sint32
APP_GetSoundMethod();

//Kitao�ǉ�
void
APP_SetSoundType(
	Sint32	soundType);

//Kitao�ǉ�
Sint32
APP_GetSoundType();

//Kitao�ǉ�
BOOL
APP_GetAutoStereo();

//Kitao�ǉ�
BOOL
APP_GetAutoGradiusII();

//Kitao�ǉ�
BOOL
APP_GetFixShinMegamiTensei();

//Kitao�ǉ�
BOOL
APP_OutputWavEnd();

//Kitao�ǉ�
BOOL
APP_GetOutputWavNext();

//Kitao�ǉ�
char*
APP_GetWavFileName();

//Kitao�ǉ�
BOOL
APP_GetUseVideoCardMemory();

//Kitao�ǉ�
BOOL
APP_GetWindowTopMost();

//Kitao�ǉ��Bv2.48
void
APP_SetWindowTopMostTemp(
	BOOL	bWindowTopMost);

//Kitao�ǉ�
Sint32
APP_GetCustomWidth1();
Sint32
APP_GetCustomHeight1();
Sint32
APP_GetCustomWidth2();
Sint32
APP_GetCustomHeight2();
Sint32
APP_GetCustomWidth3();
Sint32
APP_GetCustomHeight3();

//Kitao�ǉ�
BOOL
APP_GetResolutionAutoChange();

//Kitao�ǉ�
BOOL
APP_AutoChangeScreenMode(
	Sint32	magnification);

//Kitao�ǉ�
Sint32
APP_GetSoundBufferSize();

//Kitao�ǉ�
void
APP_SetSoundBufferSize(
	Sint32	bufSize);

//Kitao�ǉ�
Sint32
APP_GetPsgQuality();

//Kitao�ǉ�
void
APP_SetPsgQuality(
	Sint32	psgQuality);

//Kitao�ǉ�
BOOL
APP_GetJoypadBackground();

//Kitao�ǉ��Bv2.48
void
APP_SetJoypadBackgroundTemp(
	BOOL	bJoypadBackground);

//Kitao�ǉ�
BOOL
APP_GetKeyboardBackground();

//Kitao�ǉ�
BOOL
APP_UpdateScreenMode(
	BOOL	bWindowCenter);

//Kitao�ǉ�
BOOL
APP_GetInit();

//Kitao�ǉ�
void
APP_SetShowOverscanTop(
	Sint32	showOverscanTop);

//Kitao�ǉ�
void
APP_SetShowOverscanBottom(
	Sint32	showOverscanBottom);

//Kitao�ǉ�
void
APP_SetShowOverscanLeft(
	Sint32	showOverscanLeft);

//Kitao�ǉ�
void
APP_SetShowOverscanRight(
	Sint32	showOverscanRight);

//Kitao�ǉ�
void
APP_SetShowOverscanHeight(
	Sint32	showOverscanHeight);

//Kitao�ǉ�
BOOL
APP_GetOverscanHideBlackTop();

//Kitao�ǉ�
BOOL
APP_GetOverscanHideBlackBottom();

//Kitao�ǉ�
BOOL
APP_GetOverscanHideBlackLR();

//Kitao�ǉ�
Sint32
APP_GetWindowsVolume();

//Kitao�ǉ�
void
APP_ResumeWindowsVolume(
	Sint32	windowsVolume);

//Kitao�ǉ�
Sint32
APP_GetMySetOverClockType();

//Kitao�ǉ�
Uint32
APP_GetVolumeEffect();

//Kitao�ǉ�
void
APP_ReturnCaption();

//Kitao�ǉ�
char*
APP_StrToLower(
	char*	pStr);

//Kitao�ǉ�
char*
APP_ExtractFileExt(
	char*	p);

//Kitao�ǉ�
BOOL
APP_GetShowFPS();

//Kitao�ǉ�
void
APP_SetShowFPS(
	BOOL	bShowFPS);

//Kitao�ǉ�
Sint32
APP_GetDrawMethod();

//Kitao�ǉ�
void
APP_SetDrawMethod(
	Sint32	drawMethod);

//Kitao�ǉ�
Sint32
APP_GetD3DEffect();

//Kitao�ǉ�
Sint32
APP_GetScreenWidth();

//Kitao�ǉ�
Sint32
APP_GetScreenHeight();

//Kitao�ǉ�
void
APP_SetScreenWH(
	Sint32	screenW,
	Sint32	screenH);

//Kitao�ǉ�
void
APP_SetFullScreen640();

//Kitao�ǉ�
void
APP_SetMagnification(
	Sint32	magnification);

//Kitao�ǉ�
BOOL
APP_GetSpriteLayer();

//Kitao�ǉ�
BOOL
APP_GetSprite2Layer();

//Kitao�ǉ�
BOOL
APP_GetBGLayer();

//Kitao�ǉ�
BOOL
APP_GetBG2Layer();

//Kitao�ǉ�
BOOL
APP_GetInvalidateCdInstall();

//Kitao�ǉ�
char*
APP_ChangeToOtherSysCard1();

//Kitao�ǉ�
Sint32
APP_GetNonstretchedWidth();

//Kitao�ǉ�
Sint32
APP_GetGameWidth(
	Sint32	magnification);

//Kitao�ǉ�
Sint32
APP_GetGameHeight(
	Sint32	magnification);

//Kitao�ǉ�
Sint32
APP_GetInputRecordMode();

//Kitao�ǉ�
Sint32
APP_GetInputPlayRecordNumber();

//Kitao�ǉ�
BOOL
APP_CheckRecordingNow();

//Kitao�ǉ�
Sint32
APP_GetSoftVersion();

//Kitao�ǉ��Bv2.77
char*
APP_GetSoftVersionChar();

//Kitao�ǉ�
BOOL
APP_GetDisableWindowsAero();

//Kitao�ǉ�
BOOL
APP_DwmIsCompositionEnabled();

//Kitao�ǉ�
void
APP_WindowWithinScreen();

//Kitao�ǉ�
void
APP_ToggleFullscreen();

//Kitao�ǉ�
BOOL
APP_GetCueFile();

//Kitao�ǉ�
char*
APP_GetCueFilePathName();

//Kitao�ǉ�
BOOL
APP_GetInactivePause();

//Kitao�ǉ�
Sint32
APP_GetCddaAdjust();

//Kitao�ǉ�
double
APP_GetCddaAdjustHz();

//Kitao�ǉ��Bv2.33
Sint32
APP_GetCddaDelayFrame();

//Kitao�ǉ��Bv2.36
BOOL
APP_GetLoadStateSpeedSetting();

//Kitao�ǉ��Bv2.38
Sint32
APP_GetFunctionButton();

//Kitao�ǉ��Bv2.39
BOOL
APP_ShowWriteMemoryForm(
	HWND		hWnd,
	HINSTANCE	hInstance);

//Kitao�ǉ��Bv2.42
BOOL
APP_GetHesFile();

//Kitao�ǉ��Bv2.43
Sint32
APP_GetNonVSyncTiming();

//Kitao�ǉ��Bv2.48
char*
APP_GetRecentRom(
	Sint32	n);

//Kitao�ǉ��Bv2.48
BOOL
APP_CheckButtonState(
	Sint32	n);

//Kitao�ǉ��Bv2.61
BOOL
APP_CheckFuncAndSelConflict();

//Kitao�ǉ��Bv2.50
BOOL
APP_GetCDSpeedDown();

//Kitao�ǉ��Bv2.59
BOOL
APP_GetCheckSimultaneouslyPush();

//Kitao�ǉ��Bv2.63
void
APP_CheckStateTime(
	Sint32	num,
	char*	pBufS,
	char*	pBufL);

//Kitao�ǉ��Bv2.63
BOOL
APP_GetLoadingResumeFile();

//Kitao�ǉ��Bv2.64
Sint32
APP_GetFullMagnification();

//Kitao�ǉ��Bv2.64
Sint32
APP_GetShowOverscanTop();
//Kitao�ǉ��Bv2.64
Sint32
APP_GetShowOverscanBottom();
//Kitao�ǉ��Bv2.64
Sint32
APP_GetShowOverscanLeft();
//Kitao�ǉ��Bv2.64
Sint32
APP_GetShowOverscanRight();

//Kitao�ǉ��Bv2.65
BOOL
APP_GetWindowsAutoVSyncBool();

//Kitao�ǉ��Bv2.65
Sint32
APP_GetVSyncAdjust();

//Kitao�ǉ��Bv2.70
BOOL
APP_GetStrikeBallSwap();

//Kitao�ǉ��Bv2.70
BOOL
APP_GetCutTrackHeadNoise();

//Kitao�ǉ��Bv2.77
BOOL
APP_FileDialog(
	Sint32		type,
	HWND		hWnd,
	char*		openFilePathName,
	char*		gameFilePathName);

//Kitao�ǉ��Bv2.77
void
APP_SetShortcutButton(
	HWND		hWnd,
	HINSTANCE	hInstance,
	Sint32		mode);

//Kitao�ǉ��Bv2.77
BOOL
APP_CheckShortcutKey(
	int		button);

//Kitao�ǉ��Bv2.77
BOOL
APP_ConfigurePad(
	HWND		hWnd,
	HINSTANCE	hInstance,
	Uint32		padID);

//Kitao�ǉ��Bv2.77
void
APP_SetCddaTimingAuto();

//Kitao�ǉ��Bv2.77
void
APP_SetAutoResumeMode(
	BOOL	bAutoResume);

//Kitao�ǉ��Bv2.77
BOOL
APP_SaveConfig();

#endif // APP_H_INCLUDED
