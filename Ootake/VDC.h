/*-----------------------------------------------------------------------------
	[VDC.h]

	Copyright (C) 2004 Ki

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
-----------------------------------------------------------------------------*/
#ifndef VDC_H_INCLUDED
#define VDC_H_INCLUDED

#include <stdio.h>
#include "TypeDefs.h"


#define VDC_CYCLESPERLINE	453	//453.68124207858048162230671736375 Kitao�X�V�Bv0.81
#define MAX_SCANLINE		263	//v0.81�X�V


/*
** AR �̒l�ɂ���ăA�N�Z�X����郌�W�X�^
*/
#define		VDC_MAWR			0x00
#define		VDC_MARR			0x01
#define		VDC_VWR				0x02
#define		VDC_VRR				0x02
#define		VDC_CR				0x05
#define		VDC_RCR				0x06
#define		VDC_BXR				0x07
#define		VDC_BYR				0x08
#define		VDC_MWR				0x09
#define		VDC_HSR				0x0A
#define		VDC_HDR				0x0B
#define		VDC_VPR				0x0C
#define		VDC_VDW				0x0D
#define		VDC_VCR				0x0E
#define		VDC_DCR				0x0F
#define		VDC_SOUR			0x10
#define		VDC_DESR			0x11
#define		VDC_LENR			0x12
#define		VDC_SATB			0x13


/*
** VDC STATUS
*/
#define		VDC_STAT_CR				0x01  // sprite collision
#define		VDC_STAT_OR				0x02  // over detection
#define		VDC_STAT_RR				0x04  // raster detection
#define		VDC_STAT_DS				0x08  // DMA (VRAM-SATB) end
#define		VDC_STAT_DV				0x10  // DMA (VRAM-VRAM) end
#define		VDC_STAT_VD				0x20  // vertical retrace period
#define		VDC_STAT_BSY			0x40  // VRAM reading / writing

/*
** VDC CONTROL (R05)
*/
#define		VDC_CTRL_CC				0x01	// enable IRQ on sprite collision
#define		VDC_CTRL_OC				0x02	// enable IRQ on "over"
#define		VDC_CTRL_RC				0x04	// enable IRQ1 on raster detection
#define		VDC_CTRL_VC				0x08	// enable IRQ1 on v-retrace period

/*
** DMA CONTROL ($0F)
*/
#define		VDC_DMACTRL_CR			0x01	// request IRQ1 after VRAM->SATB DMA
#define		VDC_DMACTRL_OR			0x02	// request IRQ1 after VRAM->VRAM DMA


/*-----------------------------------------------------------------------------
	Define Function Prototypes
-----------------------------------------------------------------------------*/
void //Kitao�X�V�B�߂�l�͕s�v�ɂ����B
VDC_Init();

void //Kitao�ǉ�
VDC_Reset();

Uint8
VDC_Read(Uint32 regNum);

void
VDC_Write(
	Uint32	regNum,
	Uint8	data);

void //Kitao�X�V�B�߂�l�͕s�v�ɂ����B
VDC_AdvanceClock(
	Sint32	clock);

//Kitao�X�V
void
VDC_AdvanceLine(
	Uint32*		pScreenBuf,
	Sint32		drawFrame);

const Sint32
VDC_GetDisplayHeight();

//Kitao�ǉ�
Sint32
VDC_GetTvStartLine();

Sint32
VDC_GetScanLine();

//Kitao�ǉ�
BOOL
VDC_CheckVBlankStart();

//Kitao�ǉ�
void
VDC_SetScreenWidth(
	Sint32	screenW);

//Kitao�X�V
const Sint32
VDC_GetScreenWidth();

//Kitao�ǉ��Bv2.14
Sint32
VDC_GetHDR();

BOOL
VDC_SaveState(
	FILE*	p);

BOOL
VDC_LoadState(
	FILE*	p);

//Kitao�ǉ�
void
VDC_SetRasterTiming(
	Sint32	n);

//Kitao�ǉ�
Sint32
VDC_GetRasterTimingType();

//Kitao�ǉ�
void
VDC_SetAutoRasterTiming(
	Sint32	n);

//Kitao�ǉ�
Sint32
VDC_GetAutoRasterTimingType();

//Kitao�ǉ�
void
VDC_SetOverClock(
	Sint32	n);

//Kitao�ǉ�
Sint32
VDC_GetOverClockType();

//Kitao�ǉ�
void
VDC_SetAutoOverClock(
	Sint32	n);

//Kitao�ǉ�
Sint32
VDC_GetAutoOverClock();

//Kitao�ǉ�
void
VDC_SetWaitPatch(
	Sint32	cycle);

//Kitao�ǉ�
void
VDC_SetForceRaster(
	BOOL	forceRaster);

void
VDC_SetForceVBlank(
	BOOL	forceVBlank);

//Kitao�ǉ�
void
VDC_SetPerformSpriteLimit(
	BOOL	bPerform);

//Kitao�ǉ�
void
VDC_SetAutoPerformSpriteLimit(
	BOOL	bPerform);

//Kitao�ǉ�
BOOL
VDC_GetPerformSpriteLimit();

//Kitao�ǉ�
void
VDC_SetLayer();

//Kitao�ǉ�
void
VDC_SetIRQ1CancelExecute();

//Kitao�ǉ�
Uint8
VDC_GetVdcStatus();

//Kitao�ǉ�
void
VDC_SetSuperGrafx(
	Sint32	superGrafx);

//Kitao�ǉ�
Sint32
VDC_GetSuperGrafx();

//Kitao�ǉ�
void
VDC_SetTvStartLine();

//Kitao�ǉ�
void
VDC_SetVblankLine();

//Kitao�ǉ�
void
VDC_SetVpcPriority();

//Kitao�ǉ�
void
VDC_SetTvStartPos();

//Kitao�ǉ�
BOOL
VDC_GetOverClockNow();

//Kitao�ǉ�
void
VDC_SetShinMegamiTensei(
	BOOL	shinMegamiTensei);

//Kitao�ǉ�
Sint32
VDC_GetShinMegamiTensei();

//Kitao�ǉ�
void
VDC_SetWorldStadium91(
	BOOL	worldStadium91);

//Kitao�ǉ��Bv2.70
void
VDC_SetEikanKimi(
	BOOL	eikanKimi);

//Kitao�ǉ��Bv2.70
BOOL
VDC_GetEikanKimi();

//Kitao�ǉ��Bv2.70
void
VDC_SetPowerLeague(
	BOOL	powerLeague);

//Kitao�ǉ��Bv2.70
BOOL
VDC_GetPowerLeague();

//Kitao�ǉ��Bv2.70
void
VDC_SetTheProYakyuu(
	BOOL	theProYakyuu);

//Kitao�ǉ��Bv2.70
BOOL
VDC_GetTheProYakyuu();


//Kitao�X�V�Bv1.11����VCE.c �������֓��������B
void
VDC_VceWrite(
	Uint32	regNum,
	Uint8	data);

Uint8
VDC_VceRead(Uint32 regNum);

//Kitao�ǉ�
Sint32
VDC_GetTvWidth();

//Kitao�ǉ�
Uint8
VDC_GetDCC();

//Kitao�ǉ�
Uint32
VDC_GetSpColorZero();

//v2.68�ǉ�
Uint16
VDC_GetMWR();


#endif		/* VDC_H_INCLUDED */
