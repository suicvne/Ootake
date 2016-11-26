/*------------------------------------------------------------------------------
	[AppEvent.h]

	Copyright (C) 2004 Ki

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
------------------------------------------------------------------------------*/
#ifndef APP_EVENT_H_INCLUDED
#define APP_EVENT_H_INCLUDED


#include "TypeDefs.h"


enum
{
	APPEVENT_NONE = 0,
	APPEVENT_FILEDIALOG,
	APPEVENT_OPENGAME,
	APPEVENT_CDCHANGE, //Kitao追加
	APPEVENT_RESET,
	APPEVENT_PAUSE,
	APPEVENT_RUN,
	APPEVENT_ADVANCEFRAME_1,
	APPEVENT_ADVANCEFRAME_10,
	APPEVENT_ADVANCEFRAME_100,
	APPEVENT_PAUSE_BUTTON, //Kitao追加
	APPEVENT_WRITE_MEMORY, //Kitao追加
	APPEVENT_ABOUT_WRITEMEM, //Kitao追加
	APPEVENT_RESUME, //Kitao追加
	APPEVENT_AUTO_RESUME, //Kitao追加
	APPEVENT_SAVESTATE,
	APPEVENT_SAVESTATE_1, //Kitao追加
	APPEVENT_SAVESTATE_2, //Kitao追加
	APPEVENT_SAVESTATE_3, //Kitao追加
	APPEVENT_SAVESTATE_4, //Kitao追加
	APPEVENT_SAVESTATE_5, //Kitao追加
	APPEVENT_SAVESTATE_6, //Kitao追加
	APPEVENT_SAVESTATE_7, //Kitao追加
	APPEVENT_SAVESTATE_8, //Kitao追加
	APPEVENT_SAVESTATE_9, //Kitao追加
	APPEVENT_SAVESTATE_10, //Kitao追加
	APPEVENT_SAVESTATE_11, //Kitao追加
	APPEVENT_SAVESTATE_12, //Kitao追加
	APPEVENT_SAVESTATE_13, //Kitao追加
	APPEVENT_SAVESTATE_14, //Kitao追加
	APPEVENT_SAVESTATE_15, //Kitao追加
	APPEVENT_SAVESTATE_16, //Kitao追加
	APPEVENT_SAVESTATE_17, //Kitao追加
	APPEVENT_SAVESTATE_18, //Kitao追加
	APPEVENT_SAVESTATE_19, //Kitao追加
	APPEVENT_SAVESTATE_20, //Kitao追加
	APPEVENT_SAVESTATE_21, //Kitao追加
	APPEVENT_SAVESTATE_22, //Kitao追加
	APPEVENT_SAVESTATE_23, //Kitao追加
	APPEVENT_SAVESTATE_24, //Kitao追加
	APPEVENT_SAVESTATE_25, //Kitao追加
	APPEVENT_SAVESTATE_26, //Kitao追加
	APPEVENT_SAVESTATE_27, //Kitao追加
	APPEVENT_SAVESTATE_28, //Kitao追加
	APPEVENT_SAVESTATE_29, //Kitao追加
	APPEVENT_SAVESTATE_30, //Kitao追加
	APPEVENT_SAVESTATE_31, //Kitao追加
	APPEVENT_SAVESTATE_32, //Kitao追加
	APPEVENT_SAVESTATE_33, //Kitao追加
	APPEVENT_SAVESTATE_34, //Kitao追加
	APPEVENT_SAVESTATE_35, //Kitao追加
	APPEVENT_SAVESTATE_36, //Kitao追加
	APPEVENT_SAVESTATE_37, //Kitao追加
	APPEVENT_SAVESTATE_38, //Kitao追加
	APPEVENT_SAVESTATE_39, //Kitao追加
	APPEVENT_SAVESTATE_40, //Kitao追加
	APPEVENT_SAVESTATE_41, //Kitao追加
	APPEVENT_SAVESTATE_42, //Kitao追加
	APPEVENT_SAVESTATE_43, //Kitao追加
	APPEVENT_SAVESTATE_44, //Kitao追加
	APPEVENT_SAVESTATE_45, //Kitao追加
	APPEVENT_SAVESTATE_46, //Kitao追加
	APPEVENT_SAVESTATE_47, //Kitao追加
	APPEVENT_SAVESTATE_48, //Kitao追加
	APPEVENT_SAVESTATE_49, //Kitao追加
	APPEVENT_SAVESTATE_50, //Kitao追加
	APPEVENT_LOADSTATE,
	APPEVENT_LOADSTATE_P, //Kitao追加
	APPEVENT_LOADSTATE_1, //Kitao追加
	APPEVENT_LOADSTATE_2, //Kitao追加
	APPEVENT_LOADSTATE_3, //Kitao追加
	APPEVENT_LOADSTATE_4, //Kitao追加
	APPEVENT_LOADSTATE_5, //Kitao追加
	APPEVENT_LOADSTATE_6, //Kitao追加
	APPEVENT_LOADSTATE_7, //Kitao追加
	APPEVENT_LOADSTATE_8, //Kitao追加
	APPEVENT_LOADSTATE_9, //Kitao追加
	APPEVENT_LOADSTATE_10, //Kitao追加
	APPEVENT_LOADSTATE_11, //Kitao追加
	APPEVENT_LOADSTATE_12, //Kitao追加
	APPEVENT_LOADSTATE_13, //Kitao追加
	APPEVENT_LOADSTATE_14, //Kitao追加
	APPEVENT_LOADSTATE_15, //Kitao追加
	APPEVENT_LOADSTATE_16, //Kitao追加
	APPEVENT_LOADSTATE_17, //Kitao追加
	APPEVENT_LOADSTATE_18, //Kitao追加
	APPEVENT_LOADSTATE_19, //Kitao追加
	APPEVENT_LOADSTATE_20, //Kitao追加
	APPEVENT_LOADSTATE_21, //Kitao追加
	APPEVENT_LOADSTATE_22, //Kitao追加
	APPEVENT_LOADSTATE_23, //Kitao追加
	APPEVENT_LOADSTATE_24, //Kitao追加
	APPEVENT_LOADSTATE_25, //Kitao追加
	APPEVENT_LOADSTATE_26, //Kitao追加
	APPEVENT_LOADSTATE_27, //Kitao追加
	APPEVENT_LOADSTATE_28, //Kitao追加
	APPEVENT_LOADSTATE_29, //Kitao追加
	APPEVENT_LOADSTATE_30, //Kitao追加
	APPEVENT_LOADSTATE_31, //Kitao追加
	APPEVENT_LOADSTATE_32, //Kitao追加
	APPEVENT_LOADSTATE_33, //Kitao追加
	APPEVENT_LOADSTATE_34, //Kitao追加
	APPEVENT_LOADSTATE_35, //Kitao追加
	APPEVENT_LOADSTATE_36, //Kitao追加
	APPEVENT_LOADSTATE_37, //Kitao追加
	APPEVENT_LOADSTATE_38, //Kitao追加
	APPEVENT_LOADSTATE_39, //Kitao追加
	APPEVENT_LOADSTATE_40, //Kitao追加
	APPEVENT_LOADSTATE_41, //Kitao追加
	APPEVENT_LOADSTATE_42, //Kitao追加
	APPEVENT_LOADSTATE_43, //Kitao追加
	APPEVENT_LOADSTATE_44, //Kitao追加
	APPEVENT_LOADSTATE_45, //Kitao追加
	APPEVENT_LOADSTATE_46, //Kitao追加
	APPEVENT_LOADSTATE_47, //Kitao追加
	APPEVENT_LOADSTATE_48, //Kitao追加
	APPEVENT_LOADSTATE_49, //Kitao追加
	APPEVENT_LOADSTATE_50, //Kitao追加
	APPEVENT_SAVE_BUTTON, //Kitao追加
	APPEVENT_LOAD_BUTTON, //Kitao追加
	APPEVENT_SAVE_DEFAULT, //Kitao追加
	APPEVENT_FOLDER_STATE, //Kitao追加
	APPEVENT_PARTIALMEMORYLOAD,
	APPEVENT_RECORDING,
	APPEVENT_PLAYRECORD,
	APPEVENT_RECORDING_1, //Kitao追加
	APPEVENT_RECORDING_2, //Kitao追加
	APPEVENT_RECORDING_3, //Kitao追加
	APPEVENT_RECORDING_4, //Kitao追加
	APPEVENT_RECORDING_5, //Kitao追加
	APPEVENT_RECORDING_6, //Kitao追加
	APPEVENT_RECORDING_7, //Kitao追加
	APPEVENT_RECORDING_8, //Kitao追加
	APPEVENT_RECORDING_9, //Kitao追加
	APPEVENT_RECORDING_10, //Kitao追加
	APPEVENT_RECORDING_HELP, //Kitao追加
	APPEVENT_PLAYRECORD_1, //Kitao追加
	APPEVENT_PLAYRECORD_2, //Kitao追加
	APPEVENT_PLAYRECORD_3, //Kitao追加
	APPEVENT_PLAYRECORD_4, //Kitao追加
	APPEVENT_PLAYRECORD_5, //Kitao追加
	APPEVENT_PLAYRECORD_6, //Kitao追加
	APPEVENT_PLAYRECORD_7, //Kitao追加
	APPEVENT_PLAYRECORD_8, //Kitao追加
	APPEVENT_PLAYRECORD_9, //Kitao追加
	APPEVENT_PLAYRECORD_10, //Kitao追加
	APPEVENT_MOVERECORD_1, //Kitao追加
	APPEVENT_MOVERECORD_2, //Kitao追加
	APPEVENT_MOVERECORD_3, //Kitao追加
	APPEVENT_MOVERECORD_4, //Kitao追加
	APPEVENT_MOVERECORD_5, //Kitao追加
	APPEVENT_MOVERECORD_6, //Kitao追加
	APPEVENT_MOVERECORD_7, //Kitao追加
	APPEVENT_MOVERECORD_8, //Kitao追加
	APPEVENT_MOVERECORD_9, //Kitao追加
	APPEVENT_MOVERECORD_10, //Kitao追加
	APPEVENT_FOLDER_GAMEPLAY, //Kitao追加
	APPEVENT_FOLDER_BRAM, //Kitao追加
	APPEVENT_FOLDER_MB128, //Kitao追加
	APPEVENT_REDRAWSCREEN,
	APPEVENT_EXIT,
	APPEVENT_SHOWMENU,
	APPEVENT_HIDEMENU,
	APPEVENT_PRIORITY_HIGH, //Kitao追加
	APPEVENT_PRIORITY_NORMAL, //Kitao追加
	APPEVENT_TOGGLESIXBUTTONPAD,

	APPEVENT_RECENT_1, //Kitao追加
	APPEVENT_RECENT_2, //Kitao追加
	APPEVENT_RECENT_3, //Kitao追加
	APPEVENT_RECENT_4, //Kitao追加
	APPEVENT_RECENT_5, //Kitao追加
	APPEVENT_RECENT_6, //Kitao追加
	APPEVENT_RECENT_7, //Kitao追加
	APPEVENT_RECENT_8, //Kitao追加
	APPEVENT_RECENT_9, //Kitao追加
	APPEVENT_RECENT_10, //Kitao追加
	APPEVENT_RECENT_11, //Kitao追加
	APPEVENT_RECENT_12, //Kitao追加
	APPEVENT_RECENT_13, //Kitao追加
	APPEVENT_RECENT_14, //Kitao追加
	APPEVENT_RECENT_15, //Kitao追加
	APPEVENT_RECENT_16, //Kitao追加
	APPEVENT_RECENT_17, //Kitao追加
	APPEVENT_RECENT_18, //Kitao追加
	APPEVENT_RECENT_19, //Kitao追加
	APPEVENT_RECENT_20, //Kitao追加

	APPEVENT_SCREEN_CS, //Kitao追加
	APPEVENT_SCREEN_X1,
	APPEVENT_SCREEN_X2,
	APPEVENT_SCREEN_X3,
	APPEVENT_SCREEN_X4,
	APPEVENT_SCREEN_F1,
	APPEVENT_SCREEN_F2,
	APPEVENT_SCREEN_DISABLEAERO, //Kitao追加
	APPEVENT_SCREEN_USEAERO, //Kitao追加
	APPEVENT_SCREEN_GAMMA1, //Kitao追加
	APPEVENT_SCREEN_GAMMA2,
	APPEVENT_SCREEN_GAMMA3,
	APPEVENT_SCREEN_GAMMA4,
	APPEVENT_SCREEN_GAMMA5,
	APPEVENT_SCREEN_GAMMA6,
	APPEVENT_SCREEN_GAMMA7,
	APPEVENT_SCREEN_BRIGHT1, //Kitao追加
	APPEVENT_SCREEN_BRIGHT2,
	APPEVENT_SCREEN_BRIGHT3,
	APPEVENT_SCREEN_BRIGHT4,
	APPEVENT_SCREEN_BRIGHT5,
	APPEVENT_SCREEN_BRIGHT6,
	APPEVENT_SCREEN_BRIGHT7,
	APPEVENT_SCREEN_BRIGHT8,
	APPEVENT_SCREEN_BRIGHT9,
	APPEVENT_SCREEN_MINIMIZE, //Kitao追加
	APPEVENT_SCREEN_NONSTRETCHED, //Kitao追加
	APPEVENT_SCREEN_STRETCHED,
	APPEVENT_SCREEN_FULLSTRETCHED, //Kitao追加
	APPEVENT_SCREEN_VERTICAL, //Kitao追加
	APPEVENT_SCREEN_MONOCOLOR, //Kitao追加
	APPEVENT_SCREEN_SHOWOVERSCAN, //Kitao追加
	APPEVENT_SCREEN_OVERTB, //Kitao追加
	APPEVENT_SCREEN_OVERTOP, //Kitao追加
	APPEVENT_SCREEN_OVERBOTTOM, //Kitao追加
	APPEVENT_SCREEN_OVERNONETB, //Kitao追加
	APPEVENT_SCREEN_OVERHEIGHT8, //Kitao追加
	APPEVENT_SCREEN_OVERHEIGHT7, //Kitao追加
	APPEVENT_SCREEN_OVERHEIGHT6, //Kitao追加
	APPEVENT_SCREEN_OVERHEIGHT4, //Kitao追加
	APPEVENT_SCREEN_OVERHEIGHT2, //Kitao追加
	APPEVENT_SCREEN_OVERHEIGHT1, //Kitao追加
	APPEVENT_SCREEN_OVERLR, //Kitao追加
	APPEVENT_SCREEN_OVERNONELR, //Kitao追加
	APPEVENT_SCREEN_OVERSTART, //Kitao追加
	APPEVENT_SCREEN_OVERBLACK, //Kitao追加
	APPEVENT_SCREEN_SOVERTB, //Kitao追加
	APPEVENT_SCREEN_SOVERTOP, //Kitao追加
	APPEVENT_SCREEN_SOVERBOTTOM, //Kitao追加
	APPEVENT_SCREEN_SOVERNONETB, //Kitao追加
	APPEVENT_SCREEN_SOVERHEIGHT8, //Kitao追加
	APPEVENT_SCREEN_SOVERHEIGHT7, //Kitao追加
	APPEVENT_SCREEN_SOVERHEIGHT6, //Kitao追加
	APPEVENT_SCREEN_SOVERHEIGHT4, //Kitao追加
	APPEVENT_SCREEN_SOVERHEIGHT2, //Kitao追加
	APPEVENT_SCREEN_SOVERHEIGHT1, //Kitao追加
	APPEVENT_SCREEN_SOVERLR, //Kitao追加
	APPEVENT_SCREEN_SOVERNONELR, //Kitao追加
	APPEVENT_SCREEN_FULLSCREEN,
	APPEVENT_SCREEN_FULLSCREEN640, //Kitao追加
	APPEVENT_SCREEN_FULLSCREENCS1, //Kitao追加
	APPEVENT_SCREEN_FULLSCREENCS2, //Kitao追加
	APPEVENT_SCREEN_FULLSCREENCS3, //Kitao追加
	APPEVENT_SCREEN_FULLSCREENCSA, //Kitao追加
	APPEVENT_SCREEN_SPSCANLINED, //Kitao追加
	APPEVENT_SCREEN_HRSCANLINEDTV, //Kitao追加
	APPEVENT_SCREEN_HRSCANLINED, //Kitao追加
	APPEVENT_SCREEN_HRSCANLINED2, //Kitao追加
	APPEVENT_SCREEN_HRSCANLINED3, //Kitao追加
	APPEVENT_SCREEN_HRSCANLINEDF, //Kitao追加
	APPEVENT_SCREEN_NONSCANLINED, //Kitao追加
	APPEVENT_SCREEN_NONSCANLINED2, //Kitao追加
	APPEVENT_SCREEN_NONSCANLINEDTV, //Kitao追加
	APPEVENT_SCREEN_SCANDENSITY0, //Kitao追加
	APPEVENT_SCREEN_SCANDENSITY10, //Kitao追加
	APPEVENT_SCREEN_SCANDENSITY20, //Kitao追加
	APPEVENT_SCREEN_SCANDENSITY30, //Kitao追加
	APPEVENT_SCREEN_SCANDENSITY40, //Kitao追加
	APPEVENT_SCREEN_SCANDENSITY50, //Kitao追加
	APPEVENT_SCREEN_SCANDENSITY60, //Kitao追加
	APPEVENT_SCREEN_SCANDENSITY70, //Kitao追加
	APPEVENT_SCREEN_SCANDENSITY80, //Kitao追加
	APPEVENT_SCREEN_SCANGAMMA, //Kitao追加
	APPEVENT_SCREEN_SYNC_VBLANK,
	APPEVENT_SCREEN_SYNC_WINDOWS, //Kitao追加
	APPEVENT_SCREEN_SYNC_WINDOWSF, //Kitao追加
	APPEVENT_SCREEN_SYNC_NON, //Kitao追加
	APPEVENT_SCREEN_SYNC_ADJUST, //Kitao追加
	APPEVENT_SCREEN_DIRECT3D, //Kitao追加
	APPEVENT_SCREEN_DIRECTDRAW, //Kitao追加
	APPEVENT_SCREEN_USE_VIDEOMEM, //Kitao追加
	APPEVENT_SCREEN_USE_SYSTEMMEM, //Kitao追加
	APPEVENT_SCREEN_USE_SYSTEMMEMW, //Kitao追加
	APPEVENT_SCREEN_FULL16BITCOLOR, //Kitao追加
	APPEVENT_SCREEN_FULL32BITCOLOR, //Kitao追加
	APPEVENT_SCREEN_STARTWINDOW, //Kitao追加
	APPEVENT_SCREEN_STARTFULL, //Kitao追加
	APPEVENT_SCREEN_TOPMOST, //Kitao追加
	APPEVENT_SCREEN_ACTIVATE, //Kitao追加
	APPEVENT_SCREEN_NONACTIVATE, //Kitao追加
	APPEVENT_SCREEN_UNPAUSE, //Kitao追加

	APPEVENT_INPUT_TWO_BUTTON_PAD,
	APPEVENT_INPUT_THR_BUTTON_PAD, //Kitao追加
	APPEVENT_INPUT_SIX_BUTTON_PAD,
	APPEVENT_INPUT_MOUSE,
	APPEVENT_INPUT_MULTI_TAP,
	APPEVENT_INPUT_MB128,
	APPEVENT_INPUT_SWAP_SELRUN, //Kitao追加
	APPEVENT_INPUT_SWAP_IANDII, //Kitao追加
	APPEVENT_INPUT_TURBO_1, //Kitao追加
	APPEVENT_INPUT_TURBO_2, //Kitao追加
	APPEVENT_INPUT_TURBO_RUN, //Kitao追加
	APPEVENT_INPUT_TURBO_HIGH, //Kitao追加
	APPEVENT_INPUT_TURBO_MIDDLE, //Kitao追加
	APPEVENT_INPUT_TURBO_LOW, //Kitao追加
	APPEVENT_INPUT_TURBO_OFF, //Kitao追加
	APPEVENT_INPUT_CHECKPAD_LR, //Kitao追加

	APPEVENT_INPUT_CONFIGURE_PAD1,
	APPEVENT_INPUT_CONFIGURE_PAD2,
	APPEVENT_INPUT_CONFIGURE_PAD3,
	APPEVENT_INPUT_CONFIGURE_PAD4,
	APPEVENT_INPUT_CONFIGURE_PAD5,
	APPEVENT_INPUT_CONFIGURE_TB1, //Kitao追加
	APPEVENT_INPUT_CONFIGURE_TB2, //Kitao追加
	APPEVENT_INPUT_CONFIGURE_TB3, //Kitao追加
	APPEVENT_INPUT_CONFIGURE_TB4, //Kitao追加
	APPEVENT_INPUT_CONFIGURE_TB5, //Kitao追加
	APPEVENT_INPUT_CONFIGURE_INIT, //Kitao追加
	APPEVENT_INPUT_CONFIGURE_KEYBG, //Kitao追加
	APPEVENT_INPUT_CONFIGURE_JOYBG, //Kitao追加
	APPEVENT_INPUT_FUNCTION, //Kitao追加
	APPEVENT_INPUT_FB_CURSOR, //Kitao追加
	APPEVENT_INPUT_FB_IandII, //Kitao追加
	APPEVENT_INPUT_FB_SEL, //Kitao追加
	APPEVENT_INPUT_FB_RUN, //Kitao追加
	APPEVENT_INPUT_FB_VSPEEDUP, //Kitao追加
	APPEVENT_INPUT_FB_SAVELOAD, //Kitao追加

	APPEVENT_AUDIO_SR96000,
	APPEVENT_AUDIO_SR88200,
	APPEVENT_AUDIO_SR64000,
	APPEVENT_AUDIO_SR48000,
	APPEVENT_AUDIO_SR44100,
	APPEVENT_AUDIO_SR32000,
	APPEVENT_AUDIO_SR22050,
	APPEVENT_AUDIO_SR11025,

	APPEVENT_AUDIO_SB1024, //Kitao更新
	APPEVENT_AUDIO_SB1152,
	APPEVENT_AUDIO_SB1280,
	APPEVENT_AUDIO_SB1408,
	APPEVENT_AUDIO_SB1536,
	APPEVENT_AUDIO_SB1664,
	APPEVENT_AUDIO_SB1792,
	APPEVENT_AUDIO_SB2048,
	APPEVENT_AUDIO_SB2176,
	APPEVENT_AUDIO_SB2304,
	APPEVENT_AUDIO_SB2560,
	APPEVENT_AUDIO_SB3072,
	APPEVENT_AUDIO_HQPSG1, //Kitao追加
	APPEVENT_AUDIO_HQPSG2, //Kitao追加
	APPEVENT_AUDIO_HQPSG3, //Kitao追加

	APPEVENT_AUDIO_METHOD7SC, //Kitao追加
	APPEVENT_AUDIO_METHOD7SM, //Kitao追加
	APPEVENT_AUDIO_METHOD9SC, //Kitao追加
	APPEVENT_AUDIO_METHOD9SM, //Kitao追加
	APPEVENT_AUDIO_METHOD20, //Kitao追加

	APPEVENT_AUDIO_STEREO, //Kitao追加
	APPEVENT_AUDIO_MONO, //Kitao追加

	APPEVENT_AUDIO_NORMALBUFFER, //Kitao追加
	APPEVENT_AUDIO_BIGBUFFER, //Kitao追加
	APPEVENT_AUDIO_MOSTBUFFER, //Kitao追加

	APPEVENT_AUDIO_CDDAAUTO, //Kitao追加
	APPEVENT_AUDIO_CDDA593, //Kitao追加
	APPEVENT_AUDIO_CDDA594, //Kitao追加
	APPEVENT_AUDIO_CDDA595, //Kitao追加
	APPEVENT_AUDIO_CDDA596, //Kitao追加
	APPEVENT_AUDIO_CDDA597, //Kitao追加
	APPEVENT_AUDIO_CDDA598, //Kitao追加
	APPEVENT_AUDIO_CDDA599, //Kitao追加
	APPEVENT_AUDIO_CDDA600, //Kitao追加
	APPEVENT_AUDIO_CDDA601, //Kitao追加
	APPEVENT_AUDIO_CDDA602, //Kitao追加
	APPEVENT_AUDIO_CDDAP000, //Kitao追加
	APPEVENT_AUDIO_CDDAP005, //Kitao追加
	APPEVENT_AUDIO_SYNC_VBLANK, //Kitao追加
	APPEVENT_AUDIO_DELAYFRAME0, //Kitao追加
	APPEVENT_AUDIO_DELAYFRAME1, //Kitao追加
	APPEVENT_AUDIO_DELAYFRAME2, //Kitao追加
	APPEVENT_AUDIO_DELAYFRAME3, //Kitao追加
	APPEVENT_AUDIO_DELAYFRAME4, //Kitao追加

	APPEVENT_AUDIO_SETVOLUME,
	APPEVENT_AUDIO_DEFAULTVOLUME, //Kitao追加

	APPEVENT_VOLUME_NORMAL, //Kitao追加
	APPEVENT_VOLUME_3QUARTERS, //Kitao追加
	APPEVENT_VOLUME_HALF, //Kitao追加
	APPEVENT_VOLUME_QUARTER, //Kitao追加
	APPEVENT_VOLUME_MUTE, //Kitao追加
	APPEVENT_VOLUME_DEFAULT, //Kitao追加
	APPEVENT_VOLUME_12, //Kitao追加
	APPEVENT_VOLUME_11, //Kitao追加
	APPEVENT_VOLUME_10, //Kitao追加
	APPEVENT_VOLUME_9, //Kitao追加
	APPEVENT_VOLUME_8, //Kitao追加
	APPEVENT_VOLUME_7, //Kitao追加
	APPEVENT_VOLUME_6, //Kitao追加
	APPEVENT_VOLUME_5, //Kitao追加
	APPEVENT_VOLUME_4, //Kitao追加
	APPEVENT_VOLUME_3, //Kitao追加
	APPEVENT_VOLUME_2, //Kitao追加
	APPEVENT_VOLUME_1, //Kitao追加
	APPEVENT_VOLUME_UP, //Kitao追加
	APPEVENT_VOLUME_DOWN, //Kitao追加
	APPEVENT_VOLUME_STEP, //Kitao追加
	APPEVENT_VOLUME_STEP10, //Kitao追加
	APPEVENT_VOLUME_STEP8, //Kitao追加
	APPEVENT_VOLUME_STEP6, //Kitao追加
	APPEVENT_VOLUME_STEP5, //Kitao追加
	APPEVENT_VOLUME_STEP4, //Kitao追加
	APPEVENT_VOLUME_STEP3, //Kitao追加
	APPEVENT_VOLUME_STEP2, //Kitao追加
	APPEVENT_VOLUME_STEP1, //Kitao追加
	APPEVENT_VOLUME_DETAILUP, //Kitao追加
	APPEVENT_VOLUME_DETAILDN, //Kitao追加
	APPEVENT_VOLUME_ATTENTION, //Kitao追加
	APPEVENT_VOLUME_CONTROL, //Kitao追加
	APPEVENT_VOLUME_MUTE1, //Kitao追加
	APPEVENT_VOLUME_MUTE2, //Kitao追加
	APPEVENT_VOLUME_MUTE3, //Kitao追加
	APPEVENT_VOLUME_MUTE4, //Kitao追加
	APPEVENT_VOLUME_MUTE5, //Kitao追加
	APPEVENT_VOLUME_MUTE6, //Kitao追加
	APPEVENT_VOLUME_MUTEA, //Kitao追加
	APPEVENT_VOLUME_MUTEU, //Kitao追加

	APPEVENT_INFO_SHOWFPS, //Kitao追加
	APPEVENT_INFO_TESTDELAY, //Kitao追加
	APPEVENT_INFO_MANUENGLISH,  //Kitao追加
	APPEVENT_INFO_MANUJAPANESE,  //Kitao追加
	APPEVENT_INFO_README,  //Kitao追加
	APPEVENT_INFO_HOMEPAGE,  //Kitao追加
	APPEVENT_INFO_VERSION,  //Kitao追加

	APPEVENT_DEVICE_CD0,  //Kitao追加
	APPEVENT_DEVICE_CD1,  //Kitao追加
	APPEVENT_DEVICE_CD2,  //Kitao追加
	APPEVENT_DEVICE_CD3,  //Kitao追加
	APPEVENT_DEVICE_CD4,  //Kitao追加
	APPEVENT_DEVICE_CD5,  //Kitao追加
	APPEVENT_DEVICE_CD6,  //Kitao追加
	APPEVENT_DEVICE_CD7,  //Kitao追加
	APPEVENT_DEVICE_CD8,  //Kitao追加
	APPEVENT_DEVICE_CD9,  //Kitao追加
	APPEVENT_CD_PLAYINSTALL, //Kitao追加
	APPEVENT_CD_INSTALL, //Kitao追加
	APPEVENT_CD_FULLINSTALL, //Kitao追加
	APPEVENT_CD_UNINSTALL, //Kitao追加
	APPEVENT_CD_OPENINSTALL, //Kitao追加
	APPEVENT_CD_SETSYSCARD, //Kitao追加
	APPEVENT_CD_SETSYSCARD1, //Kitao追加
	APPEVENT_CD_SETSYSCARD2, //Kitao追加
	APPEVENT_CD_JUUOUKI, //Kitao追加
	APPEVENT_CD_OSYSCARD1, //Kitao追加
	APPEVENT_CD_OSYSCARD2, //Kitao追加
	APPEVENT_CD_BACKUPFULL, //Kitao追加
	APPEVENT_CD_ARCADECARD, //Kitao追加
	APPEVENT_CD_HELP, //Kitao追加

	APPEVENT_CHANGE_CDC,  //Kitao追加
	APPEVENT_CHANGE_CD0,  //Kitao追加
	APPEVENT_CHANGE_CD1,  //Kitao追加
	APPEVENT_CHANGE_CD2,  //Kitao追加
	APPEVENT_CHANGE_CD3,  //Kitao追加
	APPEVENT_CHANGE_CD4,  //Kitao追加
	APPEVENT_CHANGE_CD5,  //Kitao追加
	APPEVENT_CHANGE_CD6,  //Kitao追加
	APPEVENT_CHANGE_CD7,  //Kitao追加
	APPEVENT_CHANGE_CD8,  //Kitao追加
	APPEVENT_CHANGE_CD9,  //Kitao追加
	APPEVENT_F1_NORESET, //Kitao追加

	APPEVENT_STARTFASTCD_ON,  //Kitao追加
	APPEVENT_STARTFASTCD_OFF,  //Kitao追加
	APPEVENT_STARTFASTCD_PRE,  //Kitao追加

	APPEVENT_STARTFASTSEEK_ON,  //Kitao追加
	APPEVENT_STARTFASTSEEK_OFF,  //Kitao追加
	APPEVENT_STARTFASTSEEK_PRE,  //Kitao追加

	APPEVENT_AUTO_GRADIUS2, //Kitao追加
	APPEVENT_AUTO_MEGATEN, //Kitao追加
	APPEVENT_STARTSPRITE_OFF,  //Kitao追加
	APPEVENT_STARTSPRITE_ON,  //Kitao追加
	APPEVENT_STARTSPRITE_PRE,  //Kitao追加

	APPEVENT_MENU_HIDEMENU,  //Kitao追加
	APPEVENT_MENU_HIDEMESSAGE,  //Kitao追加

	APPEVENT_SPEED_V0,  //Kitao追加
	APPEVENT_SPEED_V1,  //Kitao追加
	APPEVENT_SPEED_V2,  //Kitao追加
	APPEVENT_SPEED_V3,  //Kitao追加
	APPEVENT_SPEED_V4,  //Kitao追加
	APPEVENT_SPEED_V5,  //Kitao追加
	APPEVENT_SPEED_V6,  //Kitao追加
	APPEVENT_SPEED_V7,  //Kitao追加
	APPEVENT_SPEED_V8,  //Kitao追加
	APPEVENT_SPEED_V9,  //Kitao追加
	APPEVENT_SPEED_VAL,  //Kitao追加
	APPEVENT_SPEED_VUSE,  //Kitao追加
	APPEVENT_SPEED_VSET,  //Kitao追加
	APPEVENT_SPEED_VUP,  //Kitao追加
	APPEVENT_SPEED_VDOWN,  //Kitao追加
	APPEVENT_SPEED_P0,  //Kitao追加
	APPEVENT_SPEED_T3,  //Kitao追加
	APPEVENT_SPEED_T2,  //Kitao追加
	APPEVENT_SPEED_T1,  //Kitao追加
	APPEVENT_SPEED_P6,  //Kitao追加
	APPEVENT_SPEED_P5,  //Kitao追加
	APPEVENT_SPEED_P4,  //Kitao追加
	APPEVENT_SPEED_P3,  //Kitao追加
	APPEVENT_SPEED_P2,  //Kitao追加
	APPEVENT_SPEED_P1,  //Kitao追加
	APPEVENT_SPEED_M1,  //Kitao追加
	APPEVENT_SPEED_M2,  //Kitao追加
	APPEVENT_SPEED_CSET,  //Kitao追加
	APPEVENT_SPEED_UNLOAD, //Kitao追加
	APPEVENT_SPEED_LOAD, //Kitao追加
	APPEVENT_SPEED_FASTCD,  //Kitao追加
	APPEVENT_SPEED_FASTSEEK,  //Kitao追加
	APPEVENT_SPEED_HELP,  //Kitao追加

	APPEVENT_RASTERTIMING_MEARLY,  //Kitao追加
	APPEVENT_RASTERTIMING_EARLY,  //Kitao追加
	APPEVENT_RASTERTIMING_MIDDLE,  //Kitao追加
	APPEVENT_RASTERTIMING_LATE,  //Kitao追加
	APPEVENT_RASTERTIMING_MLATE,  //Kitao追加

	APPEVENT_INVALIDATE_CDINST, //Kitao追加
	APPEVENT_SUPERGRAFX,  //Kitao追加
	APPEVENT_SPRITEOVER,  //Kitao追加
	APPEVENT_POWERON_EFFECT, //Kitao追加
	APPEVENT_STRIKEBALL, //Kitao追加

	APPEVENT_LAYER_SPRITE, //Kitao追加
	APPEVENT_LAYER_BG, //Kitao追加
	APPEVENT_LAYER_SPRITE2, //Kitao追加
	APPEVENT_LAYER_BG2, //Kitao追加
	APPEVENT_SPRITEBG_BUTTON, //Kitao追加

	APPEVENT_BIT_CONVERT,  //Kitao追加
	APPEVENT_SHOW_DEBUG,  //Kitao追加

	APPEVENT_ALL_DEFAULT, //Kitao追加

	APPEVENT_OUTPUT_SCREENSHOT, //Kitao追加
	APPEVENT_FOLDER_SCREENSHOT, //Kitao追加
	APPEVENT_SCREENSHOT_BUTTON, //Kitao追加
	APPEVENT_SCREENSHOT_DEFAULT, //Kitao追加
	APPEVENT_SCREENSHOT_X1, //Kitao追加
	APPEVENT_SCREENSHOT_X2, //Kitao追加
	APPEVENT_SCREENSHOT_X3, //Kitao追加
	APPEVENT_SCREENSHOT_X4, //Kitao追加
	APPEVENT_SCREENSHOT_XN, //Kitao追加
	APPEVENT_SCREENSHOT_SIZE, //Kitao追加
	APPEVENT_SSHOT_SAMEPLAYING, //Kitao追加
	APPEVENT_SSHOT_SPSCANLINED, //Kitao追加
	APPEVENT_SSHOT_HRSCANLINEDTV, //Kitao追加
	APPEVENT_SSHOT_HRSCANLINED, //Kitao追加
	APPEVENT_SSHOT_HRSCANLINED2, //Kitao追加
	APPEVENT_SSHOT_HRSCANLINED3, //Kitao追加
	APPEVENT_SSHOT_HRSCANLINEDF, //Kitao追加
	APPEVENT_SSHOT_NONSCANLINED, //Kitao追加
	APPEVENT_SSHOT_NONSCANLINED2, //Kitao追加
	APPEVENT_SSHOT_NONSCANLINEDTV, //Kitao追加
	APPEVENT_SSHOT_SAVEFOLDER, //Kitao追加
	APPEVENT_SSHOT_SAVEDIALOG, //Kitao追加

	APPEVENT_OUTPUT_WAV1, //Kitao追加
	APPEVENT_OUTPUT_WAV123, //Kitao追加
	APPEVENT_OUTPUT_WAV12, //Kitao追加
	APPEVENT_OUTPUT_WAV2, //Kitao追加
	APPEVENT_OUTPUT_WAV3, //Kitao追加
	APPEVENT_OUTPUT_WAV0, //Kitao追加
	APPEVENT_OUTPUT_WAVS1, //Kitao追加
	APPEVENT_OUTPUT_WAVS2, //Kitao追加
	APPEVENT_OUTPUT_WAVNT, //Kitao追加
	APPEVENT_OUTPUT_WAVBE, //Kitao追加
	APPEVENT_OUTPUT_AVI, //Kitao追加
	APPEVENT_ABOUT_AVI //Kitao追加
};


typedef struct
{
	Sint32		screenWidth;
	Sint32		screenHeight;
	Sint32		bitsPerPixel;
	Sint32		magnification;
	BOOL		bFullScreen;
	BOOL		bScanLine;
	BOOL		bStretched;
	BOOL		bSync60HzScreen;
	BOOL		bHardwareAcceleration;
} ScreenModeArg;


typedef struct
{
	Sint32		bufferSize;
	Sint32		sampleRate;
	Sint32		overSampleRate;
	Sint32		masterVolume;
	BOOL		bReverb;
} SoundModeArg;


BOOL
APPEVENT_Init();

BOOL
APPEVENT_Deinit();


BOOL
APPEVENT_Set(
	const Sint32	event,
	const void*		pParam);

const Sint32
APPEVENT_GetEventID();

const void*
APPEVENT_GetParam(
	const Sint32	event);

void
APPEVENT_Ack();


#endif // APP_EVENT_H_INCLUDED
