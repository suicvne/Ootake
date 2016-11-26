//THIS  this has everything for the main emulator screen!

/*-----------------------------------------------------------------------------
	{WinMain.h]

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
-----------------------------------------------------------------------------*/
#ifndef WINMAIN_H_INCLUDED
#define WINMAIN_H_INCLUDED

#include "TypeDefs.h"


//Kitao�ǉ��BMAIN��CAPTION�͑�������g���悤�ɂ����̂ł����Œ�`
#ifdef DEBUGBUILD
#define MAINCAPTION		"Ootake DEBUG BUILD " __DATE__
#else
#define MAINCAPTION		"Ootake"
#endif


enum UserDefinedWM
{
	WM_SET_FULLSCREEN_WS = WM_APP,
	WM_SET_NORMAL_WS,
};

/* ���j���[�R�}���h�� 100 �����`���� */
enum MenuCommand
{
	WM_OPEN_FILE = 100,
	WM_CD_CHANGE, //Kitao�ǉ�
	WM_RESET_EMULATOR,
	WM_RUN_EMULATOR,
	WM_STOP_EMULATOR,
	WM_TRACE_1_FRAME,
	WM_TRACE_10_FRAME,
	WM_TRACE_100_FRAME,
	WM_PAUSE_BUTTON, //Kitao�ǉ�
	WM_WRITE_MEMORY, //Kitao�ǉ�
	WM_ABOUT_WRITEMEM, //Kitao�ǉ�
	WM_SET_RESUME, //Kitao�ǉ�
	WM_AUTO_RESUME, //Kitao�ǉ�
	WM_SAVE_STATE,
	WM_SAVE_STATE_1, //Kitao�ǉ�
	WM_SAVE_STATE_2, //Kitao�ǉ�
	WM_SAVE_STATE_3, //Kitao�ǉ�
	WM_SAVE_STATE_4, //Kitao�ǉ�
	WM_SAVE_STATE_5, //Kitao�ǉ�
	WM_SAVE_STATE_6, //Kitao�ǉ�
	WM_SAVE_STATE_7, //Kitao�ǉ�
	WM_SAVE_STATE_8, //Kitao�ǉ�
	WM_SAVE_STATE_9, //Kitao�ǉ�
	WM_SAVE_STATE_10, //Kitao�ǉ�
	WM_SAVE_STATE_11, //Kitao�ǉ�
	WM_SAVE_STATE_12, //Kitao�ǉ�
	WM_SAVE_STATE_13, //Kitao�ǉ�
	WM_SAVE_STATE_14, //Kitao�ǉ�
	WM_SAVE_STATE_15, //Kitao�ǉ�
	WM_SAVE_STATE_16, //Kitao�ǉ�
	WM_SAVE_STATE_17, //Kitao�ǉ�
	WM_SAVE_STATE_18, //Kitao�ǉ�
	WM_SAVE_STATE_19, //Kitao�ǉ�
	WM_SAVE_STATE_20, //Kitao�ǉ�
	WM_SAVE_STATE_21, //Kitao�ǉ�
	WM_SAVE_STATE_22, //Kitao�ǉ�
	WM_SAVE_STATE_23, //Kitao�ǉ�
	WM_SAVE_STATE_24, //Kitao�ǉ�
	WM_SAVE_STATE_25, //Kitao�ǉ�
	WM_SAVE_STATE_26, //Kitao�ǉ�
	WM_SAVE_STATE_27, //Kitao�ǉ�
	WM_SAVE_STATE_28, //Kitao�ǉ�
	WM_SAVE_STATE_29, //Kitao�ǉ�
	WM_SAVE_STATE_30, //Kitao�ǉ�
	WM_SAVE_STATE_31, //Kitao�ǉ�
	WM_SAVE_STATE_32, //Kitao�ǉ�
	WM_SAVE_STATE_33, //Kitao�ǉ�
	WM_SAVE_STATE_34, //Kitao�ǉ�
	WM_SAVE_STATE_35, //Kitao�ǉ�
	WM_SAVE_STATE_36, //Kitao�ǉ�
	WM_SAVE_STATE_37, //Kitao�ǉ�
	WM_SAVE_STATE_38, //Kitao�ǉ�
	WM_SAVE_STATE_39, //Kitao�ǉ�
	WM_SAVE_STATE_40, //Kitao�ǉ�
	WM_SAVE_STATE_41, //Kitao�ǉ�
	WM_SAVE_STATE_42, //Kitao�ǉ�
	WM_SAVE_STATE_43, //Kitao�ǉ�
	WM_SAVE_STATE_44, //Kitao�ǉ�
	WM_SAVE_STATE_45, //Kitao�ǉ�
	WM_SAVE_STATE_46, //Kitao�ǉ�
	WM_SAVE_STATE_47, //Kitao�ǉ�
	WM_SAVE_STATE_48, //Kitao�ǉ�
	WM_SAVE_STATE_49, //Kitao�ǉ�
	WM_SAVE_STATE_50, //Kitao�ǉ�
	WM_LOAD_STATE,
	WM_LOAD_STATE_P, //Kitao�ǉ�
	WM_LOAD_STATE_1, //Kitao�ǉ�
	WM_LOAD_STATE_2, //Kitao�ǉ�
	WM_LOAD_STATE_3, //Kitao�ǉ�
	WM_LOAD_STATE_4, //Kitao�ǉ�
	WM_LOAD_STATE_5, //Kitao�ǉ�
	WM_LOAD_STATE_6, //Kitao�ǉ�
	WM_LOAD_STATE_7, //Kitao�ǉ�
	WM_LOAD_STATE_8, //Kitao�ǉ�
	WM_LOAD_STATE_9, //Kitao�ǉ�
	WM_LOAD_STATE_10, //Kitao�ǉ�
	WM_LOAD_STATE_11, //Kitao�ǉ�
	WM_LOAD_STATE_12, //Kitao�ǉ�
	WM_LOAD_STATE_13, //Kitao�ǉ�
	WM_LOAD_STATE_14, //Kitao�ǉ�
	WM_LOAD_STATE_15, //Kitao�ǉ�
	WM_LOAD_STATE_16, //Kitao�ǉ�
	WM_LOAD_STATE_17, //Kitao�ǉ�
	WM_LOAD_STATE_18, //Kitao�ǉ�
	WM_LOAD_STATE_19, //Kitao�ǉ�
	WM_LOAD_STATE_20, //Kitao�ǉ�
	WM_LOAD_STATE_21, //Kitao�ǉ�
	WM_LOAD_STATE_22, //Kitao�ǉ�
	WM_LOAD_STATE_23, //Kitao�ǉ�
	WM_LOAD_STATE_24, //Kitao�ǉ�
	WM_LOAD_STATE_25, //Kitao�ǉ�
	WM_LOAD_STATE_26, //Kitao�ǉ�
	WM_LOAD_STATE_27, //Kitao�ǉ�
	WM_LOAD_STATE_28, //Kitao�ǉ�
	WM_LOAD_STATE_29, //Kitao�ǉ�
	WM_LOAD_STATE_30, //Kitao�ǉ�
	WM_LOAD_STATE_31, //Kitao�ǉ�
	WM_LOAD_STATE_32, //Kitao�ǉ�
	WM_LOAD_STATE_33, //Kitao�ǉ�
	WM_LOAD_STATE_34, //Kitao�ǉ�
	WM_LOAD_STATE_35, //Kitao�ǉ�
	WM_LOAD_STATE_36, //Kitao�ǉ�
	WM_LOAD_STATE_37, //Kitao�ǉ�
	WM_LOAD_STATE_38, //Kitao�ǉ�
	WM_LOAD_STATE_39, //Kitao�ǉ�
	WM_LOAD_STATE_40, //Kitao�ǉ�
	WM_LOAD_STATE_41, //Kitao�ǉ�
	WM_LOAD_STATE_42, //Kitao�ǉ�
	WM_LOAD_STATE_43, //Kitao�ǉ�
	WM_LOAD_STATE_44, //Kitao�ǉ�
	WM_LOAD_STATE_45, //Kitao�ǉ�
	WM_LOAD_STATE_46, //Kitao�ǉ�
	WM_LOAD_STATE_47, //Kitao�ǉ�
	WM_LOAD_STATE_48, //Kitao�ǉ�
	WM_LOAD_STATE_49, //Kitao�ǉ�
	WM_LOAD_STATE_50, //Kitao�ǉ�
	WM_SAVE_BUTTON, //Kitao�ǉ�
	WM_LOAD_BUTTON, //Kitao�ǉ�
	WM_SAVE_DEFAULT, //Kitao�ǉ�
	WM_FOLDER_STATE, //Kitao�ǉ�
	WM_RECORDING_GAMEPLAY,
	WM_PLAYRECORD_GAMEPLAY,
	WM_RECORDING_1, //Kitao�ǉ�
	WM_RECORDING_2, //Kitao�ǉ�
	WM_RECORDING_3, //Kitao�ǉ�
	WM_RECORDING_4, //Kitao�ǉ�
	WM_RECORDING_5, //Kitao�ǉ�
	WM_RECORDING_6, //Kitao�ǉ�
	WM_RECORDING_7, //Kitao�ǉ�
	WM_RECORDING_8, //Kitao�ǉ�
	WM_RECORDING_9, //Kitao�ǉ�
	WM_RECORDING_10, //Kitao�ǉ�
	WM_RECORDING_HELP, //Kitao�ǉ�
	WM_PLAYRECORD_1, //Kitao�ǉ�
	WM_PLAYRECORD_2, //Kitao�ǉ�
	WM_PLAYRECORD_3, //Kitao�ǉ�
	WM_PLAYRECORD_4, //Kitao�ǉ�
	WM_PLAYRECORD_5, //Kitao�ǉ�
	WM_PLAYRECORD_6, //Kitao�ǉ�
	WM_PLAYRECORD_7, //Kitao�ǉ�
	WM_PLAYRECORD_8, //Kitao�ǉ�
	WM_PLAYRECORD_9, //Kitao�ǉ�
	WM_PLAYRECORD_10, //Kitao�ǉ�
	WM_MOVERECORD_1, //Kitao�ǉ�
	WM_MOVERECORD_2, //Kitao�ǉ�
	WM_MOVERECORD_3, //Kitao�ǉ�
	WM_MOVERECORD_4, //Kitao�ǉ�
	WM_MOVERECORD_5, //Kitao�ǉ�
	WM_MOVERECORD_6, //Kitao�ǉ�
	WM_MOVERECORD_7, //Kitao�ǉ�
	WM_MOVERECORD_8, //Kitao�ǉ�
	WM_MOVERECORD_9, //Kitao�ǉ�
	WM_MOVERECORD_10, //Kitao�ǉ�
	WM_FOLDER_GAMEPLAY, //Kitao�ǉ�
	WM_FOLDER_BRAM, //Kitao�ǉ�
	WM_FOLDER_MB128, //Kitao�ǉ�

	WM_RECENT_1, //Kitao�ǉ�
	WM_RECENT_2, //Kitao�ǉ�
	WM_RECENT_3, //Kitao�ǉ�
	WM_RECENT_4, //Kitao�ǉ�
	WM_RECENT_5, //Kitao�ǉ�
	WM_RECENT_6, //Kitao�ǉ�
	WM_RECENT_7, //Kitao�ǉ�
	WM_RECENT_8, //Kitao�ǉ�
	WM_RECENT_9, //Kitao�ǉ�
	WM_RECENT_10, //Kitao�ǉ�
	WM_RECENT_11, //Kitao�ǉ�
	WM_RECENT_12, //Kitao�ǉ�
	WM_RECENT_13, //Kitao�ǉ�
	WM_RECENT_14, //Kitao�ǉ�
	WM_RECENT_15, //Kitao�ǉ�
	WM_RECENT_16, //Kitao�ǉ�
	WM_RECENT_17, //Kitao�ǉ�
	WM_RECENT_18, //Kitao�ǉ�
	WM_RECENT_19, //Kitao�ǉ�
	WM_RECENT_20, //Kitao�ǉ�

	WM_SCREEN_CS, //Kitao�ǉ�
	WM_SCREEN_X1,
	WM_SCREEN_X2,
	WM_SCREEN_X3,
	WM_SCREEN_X4,
	WM_SCREEN_F1,
	WM_SCREEN_F2,
	WM_SCREEN_DISABLEAERO, //Kitao�ǉ�
	WM_SCREEN_USEAERO, //Kitao�ǉ�
	WM_SCREEN_GAMMA, //Kitao�ǉ�
	WM_SCREEN_GAMMA1,
	WM_SCREEN_GAMMA2,
	WM_SCREEN_GAMMA3,
	WM_SCREEN_GAMMA4,
	WM_SCREEN_GAMMA5,
	WM_SCREEN_GAMMA6,
	WM_SCREEN_GAMMA7,
	WM_SCREEN_BRIGHT, //Kitao�ǉ�
	WM_SCREEN_BRIGHT1,
	WM_SCREEN_BRIGHT2,
	WM_SCREEN_BRIGHT3,
	WM_SCREEN_BRIGHT4,
	WM_SCREEN_BRIGHT5,
	WM_SCREEN_BRIGHT6,
	WM_SCREEN_BRIGHT7,
	WM_SCREEN_BRIGHT8,
	WM_SCREEN_BRIGHT9,
	WM_SCREEN_MINIMIZE, //Kitao�ǉ�
	WM_SCREEN_NONSTRETCHED, //Kitao�ǉ�
	WM_SCREEN_STRETCHED,
	WM_SCREEN_FULLSTRETCHED, //Kitao�ǉ�
	WM_SCREEN_VERTICAL, //Kitao�ǉ�
	WM_SCREEN_MONOCOLOR, //Kitao�ǉ�
	WM_SCREEN_SHOWOVERSCAN, //Kitao�ǉ�
	WM_SCREEN_OVERTB, //Kitao�ǉ�
	WM_SCREEN_OVERTOP, //Kitao�ǉ�
	WM_SCREEN_OVERBOTTOM, //Kitao�ǉ�
	WM_SCREEN_OVERNONETB, //Kitao�ǉ�
	WM_SCREEN_OVERHEIGHT8, //Kitao�ǉ�
	WM_SCREEN_OVERHEIGHT7, //Kitao�ǉ�
	WM_SCREEN_OVERHEIGHT6, //Kitao�ǉ�
	WM_SCREEN_OVERHEIGHT4, //Kitao�ǉ�
	WM_SCREEN_OVERHEIGHT2, //Kitao�ǉ�
	WM_SCREEN_OVERHEIGHT1, //Kitao�ǉ�
	WM_SCREEN_OVERLR, //Kitao�ǉ�
	WM_SCREEN_OVERNONELR, //Kitao�ǉ�
	WM_SCREEN_OVERSTART, //Kitao�ǉ�
	WM_SCREEN_OVERBLACK, //Kitao�ǉ�
	WM_SCREEN_SOVERTB, //Kitao�ǉ�
	WM_SCREEN_SOVERTOP, //Kitao�ǉ�
	WM_SCREEN_SOVERBOTTOM, //Kitao�ǉ�
	WM_SCREEN_SOVERNONETB, //Kitao�ǉ�
	WM_SCREEN_SOVERHEIGHT8, //Kitao�ǉ�
	WM_SCREEN_SOVERHEIGHT7, //Kitao�ǉ�
	WM_SCREEN_SOVERHEIGHT6, //Kitao�ǉ�
	WM_SCREEN_SOVERHEIGHT4, //Kitao�ǉ�
	WM_SCREEN_SOVERHEIGHT2, //Kitao�ǉ�
	WM_SCREEN_SOVERHEIGHT1, //Kitao�ǉ�
	WM_SCREEN_SOVERLR, //Kitao�ǉ�
	WM_SCREEN_SOVERNONELR, //Kitao�ǉ�
	WM_SCREEN_FULLSCREEN,
	WM_SCREEN_FULLSCREEN640, //Kitao�ǉ�
	WM_SCREEN_FULLSCREENCS1, //Kitao�ǉ�
	WM_SCREEN_FULLSCREENCS2, //Kitao�ǉ�
	WM_SCREEN_FULLSCREENCS3, //Kitao�ǉ�
	WM_SCREEN_FULLSCREENCSA, //Kitao�ǉ�
	WM_SCREEN_SCANLINE, //Kitao�ǉ�
	WM_SCREEN_SPSCANLINED, //Kitao�ǉ�
	WM_SCREEN_HRSCANLINEDTV, //Kitao�ǉ�
	WM_SCREEN_HRSCANLINED, //Kitao�ǉ�
	WM_SCREEN_HRSCANLINED2, //Kitao�ǉ�
	WM_SCREEN_HRSCANLINED3, //Kitao�ǉ�
	WM_SCREEN_HRSCANLINEDF, //Kitao�ǉ�
	WM_SCREEN_NONSCANLINED, //Kitao�ǉ�
	WM_SCREEN_NONSCANLINED2, //Kitao�ǉ�
	WM_SCREEN_NONSCANLINEDTV, //Kitao�ǉ�
	WM_SCREEN_SCANDENSITY, //Kitao�ǉ�
	WM_SCREEN_SCANDENSITY0, //Kitao�ǉ�
	WM_SCREEN_SCANDENSITY10, //Kitao�ǉ�
	WM_SCREEN_SCANDENSITY20, //Kitao�ǉ�
	WM_SCREEN_SCANDENSITY30, //Kitao�ǉ�
	WM_SCREEN_SCANDENSITY40, //Kitao�ǉ�
	WM_SCREEN_SCANDENSITY50, //Kitao�ǉ�
	WM_SCREEN_SCANDENSITY60, //Kitao�ǉ�
	WM_SCREEN_SCANDENSITY70, //Kitao�ǉ�
	WM_SCREEN_SCANDENSITY80, //Kitao�ǉ�
	WM_SCREEN_SCANGAMMA, //Kitao�ǉ�
	WM_SCREEN_SYNC_VBLANK,
	WM_SCREEN_SYNC_WINDOWS, //Kitao�ǉ�
	WM_SCREEN_SYNC_WINDOWSF, //Kitao�ǉ�
	WM_SCREEN_SYNC_NON, //Kitao�ǉ�
	WM_SCREEN_SYNC_ADJUST, //Kitao�ǉ�
	WM_SCREEN_DIRECT3D, //Kitao�ǉ�
	WM_SCREEN_DIRECTDRAW, //Kitao�ǉ�
	WM_SCREEN_SETDIRECTDRAW, //Kitao�ǉ�
	WM_SCREEN_USE_VIDEOMEM, //Kitao�ǉ�
	WM_SCREEN_USE_SYSTEMMEM, //Kitao�ǉ�
	WM_SCREEN_USE_SYSTEMMEMW, //Kitao�ǉ�
	WM_SCREEN_FULL16BITCOLOR, //Kitao�ǉ�
	WM_SCREEN_FULL32BITCOLOR, //Kitao�ǉ�
	WM_SCREEN_STARTWINDOW, //Kitao�ǉ�
	WM_SCREEN_STARTFULL, //Kitao�ǉ�
	WM_SCREEN_TOPMOST, //Kitao�ǉ�
	WM_SCREEN_ACTIVATE, //Kitao�ǉ�
	WM_SCREEN_NONACTIVATE, //Kitao�ǉ�
	WM_SCREEN_UNPAUSE, //Kitao�ǉ�

	WM_INPUT_TWO_BUTTON_PAD,
	WM_INPUT_THR_BUTTON_PAD, //Kitao�ǉ�
	WM_INPUT_SIX_BUTTON_PAD,
	WM_INPUT_MOUSE,
	WM_INPUT_MULTI_TAP,
	WM_INPUT_MB128,
	WM_INPUT_SWAP_SELRUN, //Kitao�ǉ�
	WM_INPUT_SWAP_IANDII, //Kitao�ǉ�
	WM_INPUT_TURBO_1, //Kitao�ǉ�
	WM_INPUT_TURBO_2, //Kitao�ǉ�
	WM_INPUT_TURBO_RUN, //Kitao�ǉ�
	WM_INPUT_TURBO_HIGH, //Kitao�ǉ�
	WM_INPUT_TURBO_MIDDLE, //Kitao�ǉ�
	WM_INPUT_TURBO_LOW, //Kitao�ǉ�
	WM_INPUT_TURBO_OFF, //Kitao�ǉ�
	WM_INPUT_CHECKPAD_LR, //Kitao�ǉ�

	WM_INPUT_CONFIGURE_PAD1,
	WM_INPUT_CONFIGURE_PAD2,
	WM_INPUT_CONFIGURE_PAD3,
	WM_INPUT_CONFIGURE_PAD4,
	WM_INPUT_CONFIGURE_PAD5,
	WM_INPUT_CONFIGURE_TB1,
	WM_INPUT_CONFIGURE_TB2,
	WM_INPUT_CONFIGURE_TB3,
	WM_INPUT_CONFIGURE_TB4,
	WM_INPUT_CONFIGURE_TB5,
	WM_INPUT_CONFIGURE_INIT, //Kitao�ǉ�
	WM_INPUT_CONFIGURE_KEYBG, //Kitao�ǉ�
	WM_INPUT_CONFIGURE_JOYBG, //Kitao�ǉ�
	WM_INPUT_FUNCTION, //Kitao�ǉ�
	WM_INPUT_FB_CURSOR, //Kitao�ǉ�
	WM_INPUT_FB_IandII, //Kitao�ǉ�
	WM_INPUT_FB_SEL, //Kitao�ǉ�
	WM_INPUT_FB_RUN, //Kitao�ǉ�
	WM_INPUT_FB_VSPEEDUP, //Kitao�ǉ�
	WM_INPUT_FB_SAVELOAD, //Kitao�ǉ�

	WM_AUDIO_SR96000,		/* not supported */
	WM_AUDIO_SR88200,		/* not supported */
	WM_AUDIO_SR64000,
	WM_AUDIO_SR48000,
	WM_AUDIO_SR44100,
	WM_AUDIO_SR32000,
	WM_AUDIO_SR22050,
	WM_AUDIO_SR11025,

	WM_AUDIO_SB1024, //Kitao�X�V
	WM_AUDIO_SB1152,
	WM_AUDIO_SB1280,
	WM_AUDIO_SB1408,
	WM_AUDIO_SB1536,
	WM_AUDIO_SB1664,
	WM_AUDIO_SB1792,
	WM_AUDIO_SB2048,
	WM_AUDIO_SB2176,
	WM_AUDIO_SB2304,
	WM_AUDIO_SB2560,
	WM_AUDIO_SB3072,
	WM_AUDIO_HQPSG1, //Kitao�ǉ�
	WM_AUDIO_HQPSG2, //Kitao�ǉ�
	WM_AUDIO_HQPSG3, //Kitao�ǉ�

	WM_AUDIO_STEREO, //Kitao�ǉ�
	WM_AUDIO_MONO, //Kitao�ǉ�

	WM_AUDIO_METHOD7SC, //Kitao�ǉ�
	WM_AUDIO_METHOD7SM, //Kitao�ǉ�
	WM_AUDIO_METHOD9SC, //Kitao�ǉ�
	WM_AUDIO_METHOD9SM, //Kitao�ǉ�
	WM_AUDIO_METHOD20, //Kitao�ǉ�

	WM_AUDIO_NORMALBUFFER, //Kitao�ǉ�
	WM_AUDIO_BIGBUFFER, //Kitao�ǉ�
	WM_AUDIO_MOSTBUFFER, //Kitao�ǉ�

	WM_AUDIO_CDDAAUTO, //Kitao�ǉ�
	WM_AUDIO_CDDA593, //Kitao�ǉ�
	WM_AUDIO_CDDA594, //Kitao�ǉ�
	WM_AUDIO_CDDA595, //Kitao�ǉ�
	WM_AUDIO_CDDA596, //Kitao�ǉ�
	WM_AUDIO_CDDA597, //Kitao�ǉ�
	WM_AUDIO_CDDA598, //Kitao�ǉ�
	WM_AUDIO_CDDA599, //Kitao�ǉ�
	WM_AUDIO_CDDA600, //Kitao�ǉ�
	WM_AUDIO_CDDA601, //Kitao�ǉ�
	WM_AUDIO_CDDA602, //Kitao�ǉ�
	WM_AUDIO_CDDAP000, //Kitao�ǉ�
	WM_AUDIO_CDDAP005, //Kitao�ǉ�
	WM_AUDIO_SYNC_VBLANK, //Kitao�ǉ�
	WM_AUDIO_DELAYFRAME0, //Kitao�ǉ�
	WM_AUDIO_DELAYFRAME1, //Kitao�ǉ�
	WM_AUDIO_DELAYFRAME2, //Kitao�ǉ�
	WM_AUDIO_DELAYFRAME3, //Kitao�ǉ�
	WM_AUDIO_DELAYFRAME4, //Kitao�ǉ�

	WM_AUDIO_SETVOLUME,
	WM_AUDIO_DEFAULTVOLUME, //Kitao�ǉ�

	WM_VOLUME_TEMP, //Kitao�ǉ�
	WM_VOLUME_NORMAL, //Kitao�ǉ�
	WM_VOLUME_3QUARTERS, //Kitao�ǉ�
	WM_VOLUME_HALF, //Kitao�ǉ�
	WM_VOLUME_QUARTER, //Kitao�ǉ�
	WM_VOLUME_MUTE, //Kitao�ǉ�
	WM_VOLUME_DEFAULT, //Kitao�ǉ�
	WM_VOLUME_12, //Kitao�ǉ�
	WM_VOLUME_11, //Kitao�ǉ�
	WM_VOLUME_10, //Kitao�ǉ�
	WM_VOLUME_9, //Kitao�ǉ�
	WM_VOLUME_8, //Kitao�ǉ�
	WM_VOLUME_7, //Kitao�ǉ�
	WM_VOLUME_6, //Kitao�ǉ�
	WM_VOLUME_5, //Kitao�ǉ�
	WM_VOLUME_4, //Kitao�ǉ�
	WM_VOLUME_3, //Kitao�ǉ�
	WM_VOLUME_2, //Kitao�ǉ�
	WM_VOLUME_1, //Kitao�ǉ�
	WM_VOLUME_UP, //Kitao�ǉ�
	WM_VOLUME_DOWN, //Kitao�ǉ�
	WM_VOLUME_STEP, //Kitao�ǉ�
	WM_VOLUME_STEP10, //Kitao�ǉ�
	WM_VOLUME_STEP8, //Kitao�ǉ�
	WM_VOLUME_STEP6, //Kitao�ǉ�
	WM_VOLUME_STEP5, //Kitao�ǉ�
	WM_VOLUME_STEP4, //Kitao�ǉ�
	WM_VOLUME_STEP3, //Kitao�ǉ�
	WM_VOLUME_STEP2, //Kitao�ǉ�
	WM_VOLUME_STEP1, //Kitao�ǉ�
	WM_VOLUME_DETAIL, //Kitao�ǉ�
	WM_VOLUME_DETAILUP, //Kitao�ǉ�
	WM_VOLUME_DETAILDN, //Kitao�ǉ�
	WM_VOLUME_ATTENTION, //Kitao�ǉ�
	WM_VOLUME_CONTROL, //Kitao�ǉ�
	WM_VOLUME_MUTEPSG, //Kitao�ǉ�
	WM_VOLUME_MUTE1, //Kitao�ǉ�
	WM_VOLUME_MUTE2, //Kitao�ǉ�
	WM_VOLUME_MUTE3, //Kitao�ǉ�
	WM_VOLUME_MUTE4, //Kitao�ǉ�
	WM_VOLUME_MUTE5, //Kitao�ǉ�
	WM_VOLUME_MUTE6, //Kitao�ǉ�
	WM_VOLUME_MUTEA, //Kitao�ǉ�
	WM_VOLUME_MUTEU, //Kitao�ǉ�

	WM_INFO_SHOWFPS, //Kitao�ǉ�
	WM_INFO_TESTDELAY, //Kitao�ǉ�
	WM_INFO_MANUENGLISH, //Kitao�ǉ�
	WM_INFO_MANUJAPANESE, //Kitao�ǉ�
	WM_INFO_README, //Kitao�ǉ�
	WM_INFO_HOMEPAGE, //Kitao�ǉ�
	WM_INFO_VERSION, //Kitao�ǉ�

	WM_DEVICE_CD0, //Kitao�ǉ�
	WM_DEVICE_CD1, //Kitao�ǉ�
	WM_DEVICE_CD2, //Kitao�ǉ�
	WM_DEVICE_CD3, //Kitao�ǉ�
	WM_DEVICE_CD4, //Kitao�ǉ�
	WM_DEVICE_CD5, //Kitao�ǉ�
	WM_DEVICE_CD6, //Kitao�ǉ�
	WM_DEVICE_CD7, //Kitao�ǉ�
	WM_DEVICE_CD8, //Kitao�ǉ�
	WM_DEVICE_CD9, //Kitao�ǉ�
	WM_CD_PLAYINSTALL, //Kitao�ǉ�
	WM_CD_INSTALL, //Kitao�ǉ�
	WM_CD_FULLINSTALL, //Kitao�ǉ�
	WM_CD_UNINSTALL, //Kitao�ǉ�
	WM_CD_OPENINSTALL, //Kitao�ǉ�
	WM_CD_SETSYSCARD, //Kitao�ǉ�
	WM_CD_SETSYSCARD1, //Kitao�ǉ�
	WM_CD_SETSYSCARD2, //Kitao�ǉ�
	WM_CD_JUUOUKI, //Kitao�ǉ�
	WM_CD_OSYSCARD1, //Kitao�ǉ�
	WM_CD_OSYSCARD2, //Kitao�ǉ�
	WM_CD_BACKUPFULL, //Kitao�ǉ�
	WM_CD_ARCADECARD, //Kitao�ǉ�
	WM_CD_HELP, //Kitao�ǉ�

	WM_CHANGE_CDC, //Kitao�ǉ�
	WM_CHANGE_CD0, //Kitao�ǉ�
	WM_CHANGE_CD1, //Kitao�ǉ�
	WM_CHANGE_CD2, //Kitao�ǉ�
	WM_CHANGE_CD3, //Kitao�ǉ�
	WM_CHANGE_CD4, //Kitao�ǉ�
	WM_CHANGE_CD5, //Kitao�ǉ�
	WM_CHANGE_CD6, //Kitao�ǉ�
	WM_CHANGE_CD7, //Kitao�ǉ�
	WM_CHANGE_CD8, //Kitao�ǉ�
	WM_CHANGE_CD9, //Kitao�ǉ�
	WM_F1_NORESET, //Kitao�ǉ�

	WM_STARTFASTCD_ON, //Kitao�ǉ�
	WM_STARTFASTCD_OFF, //Kitao�ǉ�
	WM_STARTFASTCD_PRE, //Kitao�ǉ�

	WM_STARTFASTSEEK_ON, //Kitao�ǉ�
	WM_STARTFASTSEEK_OFF, //Kitao�ǉ�
	WM_STARTFASTSEEK_PRE, //Kitao�ǉ�

	WM_AUTO_GRADIUS2, //Kitao�ǉ�
	WM_AUTO_MEGATEN, //Kitao�ǉ�
	WM_STARTSPRITE_OFF, //Kitao�ǉ�
	WM_STARTSPRITE_ON, //Kitao�ǉ�
	WM_STARTSPRITE_PRE, //Kitao�ǉ�

	WM_MENU_HIDEMENU, //Kitao�ǉ�
	WM_MENU_HIDEMESSAGE, //Kitao�ǉ�

	WM_PRIORITY_HIGH, //Kitao�ǉ�
	WM_PRIORITY_NORMAL, //Kitao�ǉ�

	WM_SPEED_V0, //Kitao�ǉ�
	WM_SPEED_V1, //Kitao�ǉ�
	WM_SPEED_V2, //Kitao�ǉ�
	WM_SPEED_V3, //Kitao�ǉ�
	WM_SPEED_V4, //Kitao�ǉ�
	WM_SPEED_V5, //Kitao�ǉ�
	WM_SPEED_V6, //Kitao�ǉ�
	WM_SPEED_V7, //Kitao�ǉ�
	WM_SPEED_V8, //Kitao�ǉ�
	WM_SPEED_V9, //Kitao�ǉ�
	WM_SPEED_VAL, //Kitao�ǉ�
	WM_SPEED_VUSE, //Kitao�ǉ�
	WM_SPEED_VSET, //Kitao�ǉ�
	WM_SPEED_CPU, //Kitao�ǉ�
	WM_SPEED_P0, //Kitao�ǉ�
	WM_SPEED_T3, //Kitao�ǉ�
	WM_SPEED_T2, //Kitao�ǉ�
	WM_SPEED_T1, //Kitao�ǉ�
	WM_SPEED_P6, //Kitao�ǉ�
	WM_SPEED_P5, //Kitao�ǉ�
	WM_SPEED_P4, //Kitao�ǉ�
	WM_SPEED_P3, //Kitao�ǉ�
	WM_SPEED_P2, //Kitao�ǉ�
	WM_SPEED_P1, //Kitao�ǉ�
	WM_SPEED_M1, //Kitao�ǉ�
	WM_SPEED_M2, //Kitao�ǉ�
	WM_SPEED_CSET, //Kitao�ǉ�
	WM_SPEED_UNLOAD, //Kitao�ǉ�
	WM_SPEED_LOAD, //Kitao�ǉ�
	WM_SPEED_FASTCD, //Kitao�ǉ�
	WM_SPEED_FASTSEEK, //Kitao�ǉ�
	WM_SPEED_HELP, //Kitao�ǉ�

	WM_RASTERTIMING_MEARLY, //Kitao�ǉ�
	WM_RASTERTIMING_EARLY, //Kitao�ǉ�
	WM_RASTERTIMING_MIDDLE, //Kitao�ǉ�
	WM_RASTERTIMING_LATE, //Kitao�ǉ�
	WM_RASTERTIMING_MLATE, //Kitao�ǉ�

	WM_INVALIDATE_CDINST, //Kitao�ǉ�
	WM_SUPERGRAFX, //Kitao�ǉ�
	WM_SPRITEOVER, //Kitao�ǉ�

	WM_LAYER_SPRITE, //Kitao�ǉ�
	WM_LAYER_BG, //Kitao�ǉ�
	WM_LAYER_SPRITE2, //Kitao�ǉ�
	WM_LAYER_BG2, //Kitao�ǉ�
	WM_SPRITEBG_BUTTON, //Kitao�ǉ�
	WM_POWERON_EFFECT, //Kitao�ǉ�
	WM_STRIKEBALL, //Kitao�ǉ�

	WM_BIT_CONVERT, //Kitao�ǉ�
	WM_SHOW_DEBUG, //Kitao�ǉ�

	WM_ALL_DEFAULT, //Kitao�ǉ�

	WM_EXIT,

	WM_OUTPUT_SCREENSHOT, //Kitao�ǉ�
	WM_FOLDER_SCREENSHOT, //Kitao�ǉ�
	WM_SCREENSHOT_BUTTON, //Kitao�ǉ�
	WM_SCREENSHOT_DEFAULT, //Kitao�ǉ�
	WM_SCREENSHOT_X1, //Kitao�ǉ�
	WM_SCREENSHOT_X2, //Kitao�ǉ�
	WM_SCREENSHOT_X3, //Kitao�ǉ�
	WM_SCREENSHOT_X4, //Kitao�ǉ�
	WM_SCREENSHOT_XN, //Kitao�ǉ�
	WM_SCREENSHOT_SIZE, //Kitao�ǉ�
	WM_SSHOT_SAMEPLAYING, //Kitao�ǉ�
	WM_SSHOT_SPSCANLINED, //Kitao�ǉ�
	WM_SSHOT_HRSCANLINEDTV, //Kitao�ǉ�
	WM_SSHOT_HRSCANLINED, //Kitao�ǉ�
	WM_SSHOT_HRSCANLINED2, //Kitao�ǉ�
	WM_SSHOT_HRSCANLINED3, //Kitao�ǉ�
	WM_SSHOT_HRSCANLINEDF, //Kitao�ǉ�
	WM_SSHOT_NONSCANLINED, //Kitao�ǉ�
	WM_SSHOT_NONSCANLINED2, //Kitao�ǉ�
	WM_SSHOT_NONSCANLINEDTV, //Kitao�ǉ�
	WM_SSHOT_SAVEFOLDER, //Kitao�ǉ�
	WM_SSHOT_SAVEDIALOG, //Kitao�ǉ�

	WM_OUTPUT_WAV1, //Kitao�ǉ�
	WM_OUTPUT_WAV123, //Kitao�ǉ�
	WM_OUTPUT_WAV12, //Kitao�ǉ�
	WM_OUTPUT_WAV2, //Kitao�ǉ�
	WM_OUTPUT_WAV3, //Kitao�ǉ�
	WM_OUTPUT_WAV0, //Kitao�ǉ�
	WM_OUTPUT_WAVS1, //Kitao�ǉ�
	WM_OUTPUT_WAVS2, //Kitao�ǉ�
	WM_OUTPUT_WAVNT, //Kitao�ǉ�
	WM_OUTPUT_WAVBE, //Kitao�ǉ�
	WM_OUTPUT_AVI, //Kitao�ǉ�
	WM_ABOUT_AVI //Kitao�ǉ�
};


extern int	__main__(int argc, char** argv);


const HINSTANCE
WINMAIN_GetHInstance();

const HWND
WINMAIN_GetHwnd();

void
WINMAIN_SetFullScreenWindow(
	Sint32		width,
	Sint32		height);

void
WINMAIN_SetNormalWindow(
	Sint32		width,
	Sint32		height);

void
WINMAIN_SetCaption(
	const char*		pCaption);

//Kitao�ǉ�
char*
WINMAIN_GetCaption();

Uint32
WINMAIN_ShowCursor(
	BOOL		bShow);

//Kitao�ǉ�
void
WINMAIN_SetPriority(
	DWORD	dwPriorityClass);

//Kitao�ǉ�
void
WINMAIN_SafetySleepZero(
	DWORD	startTime,
	DWORD	endTime);

//v2.77
void
WINMAIN_SetMiniSize();


//Kitao�ǉ��B�f�o�b�O�p
void
WINMAIN_SetBreakTrap(
	BOOL bBrakTrap);

//Kitao�ǉ��B�f�o�b�O�p
BOOL
WINMAIN_GetBreakTrap();


#endif /* WINMAIN_H_INCLUDED */
