/******************************************************************************
	[CDInterface.h]

	CD-ROM �f�o�C�X�𑀍삷�邽�߂̃C���^�t�F�C�X���`���܂��B
	Define interface for controlling CD-ROM device.

	Copyright (C) 2004 Ki

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
******************************************************************************/
#ifndef CDROM_INTERFACE_H_INCLUDED
#define CDROM_INTERFACE_H_INCLUDED


#include "TypeDefs.h"


//#defines of flags for the status callback function
#define CDIF_SEEK			0x00000001
#define CDIF_READ			0x00000002
#define CDIF_SUBQ			0x00000004
#define CDIF_READCDDA		0x00000008//Kitao�ǉ�
#define CDIF_PLAYCDDA		0x00000010//Kitao�ǉ�
#define CDIF_READCDDA2		0x00000020//Kitao�ǉ�
#define CDIF_SEEKDATA		0x00000040//Kitao�ǉ�
#define CDIF_INSTALL		0x00000080//Kitao�ǉ�
#define CDIF_INSTALLWAV		0x00000100//Kitao�ǉ�
#define CDIF_SEEKHDD		0x00000200//Kitao�ǉ�
#define CDIF_SEEKDATAHDD	0x00000400//Kitao�ǉ�
#define CDIF_READHDD		0x00000800//Kitao�ǉ�
#define CDIF_READCDDAHDD	0x00001000//Kitao�ǉ�
#define CDIF_READCDDA2HDD	0x00002000//Kitao�ǉ�

#define CDIF_ERROR			0x80000000


/*-----------------------------------------------------------------------------
	[Init]
		���������܂��B 
-----------------------------------------------------------------------------*/
Sint32 //v2.33�X�V�B-1=�G���[�B0�`=��������CD-ROM(DVD,BD)�h���C�u���B
CDIF_Init(void (*callback)(Uint32 flags));


/*-----------------------------------------------------------------------------
	[Deinit]
		�I�����܂��B 
-----------------------------------------------------------------------------*/
void
CDIF_Deinit();

Sint32
CDIF_GetNumDevices();

BOOL
CDIF_SelectDevice(
	Sint32	deviceNum);

Sint32
CDIF_GetFirstTrack();

Sint32
CDIF_GetLastTrack();

//Kitao�ǉ�
Uint32
CDIF_GetTrackNumber(
	Uint32		m,
	Uint32		s,
	Uint32		f);

Uint32
CDIF_GetTrackStartPositionMSF(
	Sint32		track);

Uint32
CDIF_GetTrackStartPositionLBA(
	Sint32		track);


BOOL
CDIF_SetSpeed(
	Uint32		speed);		// �{�� 

BOOL
CDIF_IsDeviceBusy();


/*-----------------------------------------------------------------------------
	[ReadSector]
		�Z�N�^��ǂݏo���܂��B
-----------------------------------------------------------------------------*/
BOOL
CDIF_ReadSector(
	Uint8*			pBuf,				// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Uint32			sector,				// �Z�N�^�ԍ� 
	Uint32			nSectors,			// �ǂݏo���Z�N�^�� 
	BOOL			bCallback);

//Kitao�ǉ��B�f�[�^��Read���钼�O�p�B�Z�N�^�[�̐�ǂ݂��s���B
BOOL
CDIF_SeekData(
	Uint8*			pBuf,				// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Uint32			sector,				// �Z�N�^�ԍ� 
	Uint32			nSectors,			// �ǂݏo���Z�N�^�� 
	BOOL			bCallback);

/*-----------------------------------------------------------------------------
	[ReadSubChannelQ]
		�p�T�u�`���l����ǂݏo���܂��B
-----------------------------------------------------------------------------*/
BOOL
CDIF_ReadSubChannelQ(
	Uint8*		pBuf,		// 10-byte buffer
	BOOL		bCallback);


//Kitao�ǉ�
BOOL
CDIF_SeekCdda(
	Uint8	minStart,
	Uint8	secStart,
	Uint8	frmStart);

//Kitao�ǉ�
BOOL
CDIF_ReadCddaSector(
	Uint8*		pBuf,				// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Uint32		sector,				// �Z�N�^�ԍ� 
	Sint32		nSectors,			// �ǂݏo���Z�N�^�� 
	BOOL		bCallback);

//Kitao�ǉ�
BOOL
CDIF_ReadCddaSectorHDD(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Sint32		track,		// �ǂݍ��ރg���b�N�i���o�[
	Uint32		addr,		// �ǂݍ��ރA�h���X�B�g���b�N(���t�@�C��)�̐擪��0x0000�Ƃ���B
	Sint32		nSectors,	// �ǂݏo���Z�N�^�� 
	BOOL		bCallback);

//Kitao�X�V
BOOL
CDIF_Seek(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Sint32		track,		// �ǂݍ��ރg���b�N�i���o�[
	Uint32		sector,		// �Z�N�^�ԍ� 
	Sint32		nSectors,	// �ǂݏo���Z�N�^�� 
	BOOL		bCallback);

//Kitao�ǉ�
BOOL
CDIF_SeekHDD(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Sint32		track,		// �ǂݍ��ރg���b�N�i���o�[
	Uint32		addr,		// �ǂݍ��ރA�h���X�B�g���b�N(���t�@�C��(WAVE�w�b�_������̂�45�o�C�g�ڂ���))�̐擪��0x0000�Ƃ���B
	Sint32		nSectors,	// �ǂݏo���Z�N�^�� 
	BOOL		bCallback);

//Kitao�ǉ�
BOOL
CDIF_PlayCdda(
	BOOL	bCallback);

//Kitao�ǉ�
BOOL
CDIF_ReadCddaSector2(
	Uint8*		pBuf,				// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Uint32		sector,				// �Z�N�^�ԍ� 
	Sint32		nSectors,			// �ǂݏo���Z�N�^�� 
	BOOL		bCallback);

//Kitao�ǉ�
BOOL
CDIF_ReadCddaSector2HDD(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Sint32		track,		// �ǂݍ��ރg���b�N�i���o�[
	Uint32		addr,		// �ǂݍ��ރA�h���X�B�g���b�N(���t�@�C��)�̐擪��0x0000�Ƃ���B
	Sint32		nSectors,	// �ǂݏo���Z�N�^�� 
	BOOL		bCallback);

//Kitao�ǉ�
Sint32
CDIF_GetDriveLetters(
	int	n);

//Kitao�ǉ�
Sint32
CDIF_GetDeviceInUse();

//Kitao�ǉ�
BOOL
CDIF_CDInstall(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Uint32		sector,		// �Z�N�^�ԍ� 
	Uint32		nSectors,	// �ǂݏo���Z�N�^�� 
	BOOL		bCallback);

//Kitao�ǉ�
BOOL
CDIF_CDInstallWav(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Sint32		track,		// �ǂݍ��ރg���b�N�i���o�[
	Uint32		sector,		// �Z�N�^�ԍ� 
	Uint32		nSectors,	// �ǂݏo���Z�N�^�� 
	BOOL		bCallback);

//Kitao�ǉ�
BOOL
CDIF_SeekDataHDD(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ���
	Sint32		track,		// �ǂݍ��ރg���b�N�i���o�[
	Uint32		addr,		// �ǂݍ��ރA�h���X�B�g���b�N(���t�@�C��)�̐擪��0x0000�Ƃ���B
	Uint32		nSectors,	// �ǂݏo���Z�N�^��
	BOOL		bCallback);

//Kitao�ǉ�
BOOL
CDIF_ReadSectorHDD(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Sint32		track,		// �ǂݍ��ރg���b�N�i���o�[
	Uint32		addr,		// �ǂݍ��ރA�h���X�B�g���b�N(���t�@�C��)�̐擪��0x0000�Ƃ���B
	Sint32		nSectors,	// �ǂݏo���Z�N�^�� 
	BOOL		bCallback);

//Kitao�ǉ�
BOOL
CDIF_CddaStartWait(
	BOOL		bCallback);

//Kitao�ǉ��B
void
CDIF_WaitDeviceBusy();

//Kitao�ǉ�
BOOL
CDIF_SetBadInstalled(
	FILE*	fp);

//Kitao�ǉ�
BOOL
CDIF_GetBadInstalled();


#endif /* CDROM_INTERFACE_H_INCLUDED */
