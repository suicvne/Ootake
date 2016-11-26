/******************************************************************************
Ootake
�ECD-DA�̍Đ���WAV�ōs���悤�ɂ����̂ŁACD-DA�̃Z�N�^�[��ǂݍ��ރ��[�`�����
  �������B
�E�t�@�C���n���h���̍쐬������ɂ����s���悤�ɂ��āACD�A�N�Z�X�������������萫
  ���グ���B�ȑO��葽���̊��ŃV���[���b�N�z�[���Y��C�[�X�S�Ȃǂ̃A�N�Z�X��
  �V�r�A�ȃQ�[�������K�ɓ����悤�ɂȂ����Bv1.00
�ECD-DA��p�̃V�[�N���[�`���iPCE���Ɍ��ʂ�Ԃ��Ȃ��j��ǉ������B
�E�f�[�^���[�h��p�̃V�[�N���[�`����ǉ������Bv0.61
�ENT�n��OS�ŗ��p�����ꍇ�A���萫���l���A�K��SPTI���g���悤�ɂ����Bv0.57
�EASPI�g�p�̏ꍇ���h���C�u����ݒ肷��悤�ɂ����Bv0.57
�E�t�@�C������ASPICdrom.c ����CDInerface.c �ύX�����Bv0.64
�E���[�h�G���[(�f�[�^�g���b�N�����y�Đ����悤�Ƃ����ꍇ�Ȃ�)���̏��������@�̓�
  ��ɋ߂Â����Bv2.11

Copyright(C)2006-2011 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[CDInterface.c]

	CD-ROM �f�o�C�X�̐���� SPTI�܂��� ASPI �}�l�[�W���𗘗p���Ď������܂��B

	Implement CD-ROM device control using ASPI manager.

	[Reference]
		C Magazine 11, 2001 ���݂ɑ���SCSI/ATAPI

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
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stddef.h>				// offsetof(structName, memberName)
#include "CDInterface.h"
#include "SCSIDEFS.h"
#include "WNASPI32.h"
#include "Printf.h"
#include "CDROM.h"
#include "ADPCM.h"
#include "WinMain.h"
#include "App.h"
#include "APU.h"

#define CDIF_EVENT		TEXT("CDIF_EVENT")
#define CDIF_EXIT		0x80000000

/* defines for SPTI */
#define IOCTL_SCSI_PASS_THROUGH_DIRECT	0x4D014
#define SCSI_IOCTL_DATA_IN				1

typedef struct
{
	Uint16			Length;
	Uint8			ScsiStatus;
	Uint8			PathId;
	Uint8			TargetId;
	Uint8			Lun;
	Uint8			CdbLength;
	Uint8			SenseInfoLength;
	Uint8			DataIn;
	unsigned int	DataTransferLength;
	Uint32			TimeOutValue;
	void*			DataBuffer;
	unsigned int	SenseInfoOffset;
	Uint8			Cdb[16];
} SCSI_PASS_THROUGH_DIRECT;

typedef struct
{
	SCSI_PASS_THROUGH_DIRECT		sptd;
    Uint32							Filler;			// realign buffer to double word boundary
    Uint8							ucSenseBuf[32];
} SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER;	

typedef DWORD (*LPGETASPI32SUPPORTINFO)(void);
typedef DWORD (*LPSENDASPI32COMMAND)(LPSRB);

typedef struct
{
	Uint32		adapter;
	Uint32		target;
	Uint32		lun;
	BOOL		bATAPI;
} CdromInfo;

typedef struct
{
	Uint32		lba;
	BOOL		bAudio;
} TrackInfo;

//v2.32�X�V�BplaySec��elapsedSec���J�b�g�Btrack(startLBA�̃g���b�N)��ǉ��B
typedef struct
{
	Uint32		command;
	Uint8*		pBuf;
	Uint32		startLBA;
	Uint32		endLBA;
	Sint32		track;
	BOOL		bPlaying;
	BOOL		bPaused;
	BOOL		bCallback;
} CdArg;

static HANDLE					_hWNASPI32 = INVALID_HANDLE_VALUE;
static LPGETASPI32SUPPORTINFO	_pfnGetASPI32SupportInfo;
static LPSENDASPI32COMMAND		_pfnSendASPI32Command;

static Sint32					_FirstTrack = 1;
static Sint32					_LastTrack;

static Sint32					_nAdapters;

static BOOL						_bInit = FALSE; //Kitao�ǉ��Bv1.04
static Sint32					_nCdromDevice;
static Sint32					_DeviceInUse;
static CdromInfo				_CdromInfo[4];

static TrackInfo				_TrackInfo[256];	// [0] �͎g��Ȃ� 

static volatile BOOL			_bDeviceBusy = FALSE;

static HANDLE					_hEvent;
static HANDLE					_hThread = INVALID_HANDLE_VALUE;
static DWORD					_dwThreadID;
static volatile CdArg			_CdArg; //v2.05�X�V�Bvolatile�ɁB

static Sint32					_DriveLetters[26];	// 'A'�`'Z'�BKitao�X�V�BASPI�̂Ƃ����ݒ肷��悤�ɂ����B
static BOOL						_bUseSpti;
static HANDLE					_SPTIfileHandle = INVALID_HANDLE_VALUE; //Kitao�ǉ��Bv1.00

static void						(*_Callback)(Uint32);

static BYTE						_ReadBuf[2048 + 0x10]; //Kitao�X�V�B����Ɉ�x�����e�ʊm�ۂ��邱�Ƃō������Bv1.00
static BYTE*					_pReadBuf; //Kitao�X�V
static BYTE						_CDDAReadBuf[2352 + 0x10]; //Kitao�ǉ��BCDDA�p�Bv1.00
static BYTE*					_pCDDAReadBuf; //Kitao�ǉ�

static BOOL						_bBadInstalled; //cue�N�������ۂɁA�Â�Ootake�Ń��b�s���O�������߂̕s�������ꍇTRUE�ɁBv2.31


//Kitao�ǉ��B_CdArg���N���A����
static void
clearCdArg()
{
	ZeroMemory((CdArg*)&_CdArg, sizeof(_CdArg));
}


//Kitao�ǉ��BCD�f�o�C�X���g�p���̂Ƃ��ɑ҂�
//�^�C�~���O�ɂ���Ă�APU�X���b�h�̏����Ɠ����ɃA�N�Z�X���Ă��܂��\�������邽�߂�����l���Bv2.03
static void
waitDeviceBusy()
{
	int		i;
	DWORD	t1, t2;

	//APU�X���b�h���������̏ꍇ�I���܂ő҂�
	t1 = timeGetTime();
	t2 = t1 + 10000;//10�b�ȏ�҂����ꍇ�́A���C���X���b�h�Ńn�[�h�I�ȃg���u�����o���\���������Ƒz�肵�ASleep(1)�֐؂�ւ���OS�̈���ɔ�����B
	while (APU_GetApuBusy())
		WINMAIN_SafetySleepZero(t1, t2); //���C���X���b�h�ŃG�~�����[�g�������̏ꍇ�A1/1000�b�҂��͑傫���̂�(0)�ő҂Bv2.04�B���S��Sleep(0)���s���Bv2.42�X�V

	//CD�f�o�C�X���g�p���̏ꍇ�I���܂ő҂B40�b�o�߂��Ă��������Ȃ��ꍇ�̓G���[�Ɣ��f���Ė������[�v�𔲂���B
	i = 0;
	while (_bDeviceBusy && i<40000)
	{
		Sleep(1); //��40�b�o�ߔ���̂���Sleep(0)�͑ʖځBv2.05
		i++;
	}
}


//Kitao�ǉ��B
void
CDIF_WaitDeviceBusy()
{
	waitDeviceBusy();
}


static void
lba2msf(
	Uint32		lba,
	Uint32*		m,
	Uint32*		s,
	Uint32*		f)
{
	*m = lba / 75 / 60;
	*s = (lba - *m * 75 * 60) / 75;
	*f = lba - (*m * 75 * 60) - (*s * 75);
}


static Uint32
msf2lba(
	Uint32		m,
	Uint32		s,
	Uint32		f)
{
	return (m*60 + (s-2)) * 75 + f;
}


/*-----------------------------------------------------------------------------
	[execute_scsi_command]
		SCSI �A�_�v�^�փR�}���h�𔭍s���܂��B 
-----------------------------------------------------------------------------*/
static BOOL
execute_scsi_command(
	Uint8			*pOutBuf,
	int				outBufLen,
	BYTE			HaId,
	BYTE			targetId,
	BYTE			Lun,
	Uint8			*pCDB,
	int				cdbLen)
{
	//SPTI�p
	SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER	swb;
	ULONG									ulReturned;
	BOOL									res;
	char									path[10];
	//ASPI�p
	HANDLE				hEvent;	// �I���ʒm���s�Ȃ��I�u�W�F�N�g�ւ̃n���h��
	SRB_ExecSCSICmd		cmd;	// �R�}���h�\���� 

	if (_nCdromDevice == 0) //�h���C�u���ڑ��̏ꍇ�Bv2.33�ǉ�
		return FALSE;

	if (_bUseSpti)
	{	//SPTI�ŃR�}���h�����s���邽�߂̏��� 
		ZeroMemory(&swb, sizeof(swb));

		swb.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
		swb.sptd.CdbLength          = cdbLen;				// �R�}���h�̒���
		swb.sptd.SenseInfoLength    = 24;					//
		swb.sptd.DataIn             = SCSI_IOCTL_DATA_IN;	// �ǂ݂Ƃ胂�[�h
		swb.sptd.DataBuffer         = pOutBuf;				// �o�b�t�@�|�C���^
		swb.sptd.DataTransferLength = outBufLen;			// �o�b�t�@�T�C�Y
		swb.sptd.TimeOutValue       = 30;					// �^�C���A�E�g�܂ł̎��ԁBv2.31�X�V
		swb.sptd.SenseInfoOffset    = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, ucSenseBuf); // ucSenseBuf�̃I�t�Z�b�g
		//swb.sptd.PathId = 0; //Kitao�X�V
		//swb.sptd.TargetId = 0; //Kitao�X�V
		//swb.sptd.Lun = 0; //Kitao�X�V

		memcpy(swb.sptd.Cdb, pCDB, cdbLen);

		res = DeviceIoControl(	_SPTIfileHandle,
								IOCTL_SCSI_PASS_THROUGH_DIRECT,
								&swb,
								sizeof(swb),
								&swb,
								sizeof(swb),
								&ulReturned,
								NULL);
		if(res && swb.sptd.ScsiStatus == 0)
			return TRUE;
		else
		{	//Kitao�X�V�B���s�����ꍇ�A�n���h�����Ď擾���Ă�����x���݂�Bv1.00
			if (_SPTIfileHandle != INVALID_HANDLE_VALUE)
				CloseHandle(_SPTIfileHandle);
			sprintf(path, "\\\\.\\%c:", (int)(_DriveLetters[_DeviceInUse]));
			_SPTIfileHandle = CreateFile(path,
										GENERIC_READ | GENERIC_WRITE,
										FILE_SHARE_READ,
										NULL,
										OPEN_EXISTING,
										0,
										NULL); 
			res = DeviceIoControl(	_SPTIfileHandle,
									IOCTL_SCSI_PASS_THROUGH_DIRECT,
									&swb,
									sizeof(swb),
									&swb,
									sizeof(swb),
									&ulReturned,
									NULL);
			if(res && swb.sptd.ScsiStatus == 0)
				return TRUE;
		}
	}
	else
	{	//ASPI�ŃR�}���h�����s���邽�߂̏��� 
		// notification event ���쐬���� 
		if ((hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)) == NULL)
			return FALSE;

		ZeroMemory(&cmd, sizeof(SRB_ExecSCSICmd));
		cmd.SRB_Cmd 		= SC_EXEC_SCSI_CMD;
		cmd.SRB_HaId		= HaId;
		cmd.SRB_Flags		= SRB_DIR_IN | SRB_EVENT_NOTIFY; // �ǂݏo�����ʒm���w�� 
		cmd.SRB_Target		= targetId;
		cmd.SRB_Lun			= Lun;
		cmd.SRB_BufLen		= outBufLen;
		cmd.SRB_SenseLen	= SENSE_LEN;
		cmd.SRB_PostProc	= (LPVOID)hEvent;

		cmd.SRB_BufPointer	= pOutBuf;
		cmd.SRB_BufLen		= outBufLen;
		cmd.SRB_CDBLen		= cdbLen;

		CopyMemory(cmd.CDBByte, pCDB, cdbLen);

		// �R�}���h�����s���A�I���ʒm��҂� 
		if (_pfnSendASPI32Command((void*)&cmd) == SS_PENDING)
			WaitForSingleObject(hEvent, INFINITE);

		CloseHandle(hEvent);

		if (cmd.SRB_Status == SS_COMP)
			return TRUE;
	}

	return FALSE;
}


static void
service_abort(
	int			adapter,
	void*		pSRB)
{
	SRB_Abort	SRBforAbort;

	// SRB�̃A�{�[�g����
	ZeroMemory(&SRBforAbort, sizeof(SRBforAbort));
	SRBforAbort.SRB_Cmd     = SC_ABORT_SRB;
	SRBforAbort.SRB_HaId    = (BYTE)adapter;
	SRBforAbort.SRB_ToAbort = pSRB;
	if (_pfnSendASPI32Command(&SRBforAbort) != SS_COMP)
	{
		PRINTF("service_abort() failed.");
	}
}


static int
get_device_type(
	int		adapter,
	int		target,
	int		lun,
	BOOL*	pbATAPI)
{
	const DWORD			TIMEOUT = 10 * 1000;
	HANDLE				hEvent;
	DWORD				waitStatus;
	SRB_ExecSCSICmd		srb;
	BYTE				localBuf[256];
	BYTE*				pBuf;
	int					devicetypenum;

	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hEvent == NULL)	return -1;

	*pbATAPI = FALSE;

	ZeroMemory(localBuf, sizeof(localBuf));

	// �擪�A�h���X���P�U�o�C�g���E�̃o�b�t�@��p�ӂ��� 
	pBuf = (BYTE*)(((Uint32)&localBuf[0] + 0xF) & ~0xF);

	ZeroMemory(&srb, sizeof(srb));
	srb.SRB_Cmd			= SC_EXEC_SCSI_CMD;
	srb.SRB_HaId		= (BYTE)adapter;
	srb.SRB_Lun			= (BYTE)lun;
	srb.SRB_Target		= (BYTE)target;
	srb.SRB_Flags		= SRB_DIR_IN | SRB_EVENT_NOTIFY;
	srb.SRB_BufLen		= 128;
	srb.SRB_SenseLen	= SENSE_LEN;
	srb.SRB_BufPointer	= pBuf;
	srb.SRB_CDBLen		= 6;
	srb.SRB_PostProc	= (LPVOID)hEvent;
	srb.CDBByte[0]		= SCSI_INQUIRY;
	srb.CDBByte[4]		= 128;

	if (_pfnSendASPI32Command(&srb) == SS_PENDING)
	{
		waitStatus = WaitForSingleObject(hEvent, TIMEOUT);
		if (waitStatus == WAIT_TIMEOUT)
		{
			service_abort(adapter, &srb);
			return -1;
		}
	}
	CloseHandle(hEvent);

	if (srb.SRB_Status == SS_COMP)
	{
		devicetypenum = (int)pBuf[0] & 0x1F;
		if (((pBuf[2] & 7) == 0) || (srb.SRB_TargStat != STATUS_GOOD))
			*pbATAPI = TRUE;
	}
	else
		return -1;

	return devicetypenum;
}


static Sint32
scan_cdrom_devices()
{
	SRB_HAInquiry	srb;
	int				adapter;
	int				target;
	int				lun;
	BOOL			bATAPI;
	int				nDevice;

	nDevice = 0;

	for (adapter = 0; adapter < _nAdapters; adapter++)
	{
		ZeroMemory(&srb, sizeof(srb));
		srb.SRB_Cmd   = SC_HA_INQUIRY;
		srb.SRB_Flags = 0;
		srb.SRB_HaId  = (BYTE)adapter;

		if (_pfnSendASPI32Command(&srb) != SS_COMP)
			return FALSE;

		for (target = 0; target < 8; target++)
		{
			if (target == srb.HA_SCSI_ID)
				continue;

			for (lun = 0; lun < 8; lun++)
			{
				if (get_device_type(adapter, target, lun, &bATAPI) != DTYPE_CDROM)
					continue;

				_CdromInfo[nDevice].adapter = adapter;
				_CdromInfo[nDevice].target  = target;
				_CdromInfo[nDevice].lun     = lun;
				_CdromInfo[nDevice].bATAPI  = bATAPI;
				++nDevice;
			}
		}
	}

	return nDevice;
}


/*-----------------------------------------------------------------------------
	[read_toc]
		�S�g���b�N�� TOC ��ǂݏo���܂��B
-----------------------------------------------------------------------------*/
static BOOL
read_toc()
{
	BYTE	cdb[10];
	BYTE	toc[0x400+0x10];
	BYTE*	pTOC;
	BYTE*	pLBA;
	BYTE	ha  = (BYTE)_CdromInfo[_DeviceInUse].adapter;
	BYTE	tg  = (BYTE)_CdromInfo[_DeviceInUse].target;
	BYTE	lun = (BYTE)_CdromInfo[_DeviceInUse].lun;
	Sint32	i;
	Sint32	j;

	const Sint32	nTrial = 3;

	if (_nCdromDevice == 0)
		return FALSE;

	// �擪�A�h���X���P�U�o�C�g���E�̃o�b�t�@��p�ӂ��� 
	pTOC = (BYTE*)(((Uint32)&toc[0] + 0xF) & ~0xF);

	for (i = 0; i < nTrial; i++)
	{
		ZeroMemory(cdb, sizeof(cdb));
		cdb[0] = 0x43;		// read TOC
		cdb[1] = 0x00;		// 0x02 for MSF
		cdb[7] = 0x04;
		cdb[8] = 0x00;

		if (!execute_scsi_command(pTOC, 0x400, ha, tg, lun, cdb, sizeof(cdb)))
			continue;

		_LastTrack = (Uint32)pTOC[3];

		for (j = 1; j <= _LastTrack+1; j++)
		{
			pLBA = &pTOC[4+(j-1)*8+4];
			_TrackInfo[j].lba = (pLBA[0]<<24) + (pLBA[1]<<16) + (pLBA[2]<<8) + pLBA[3];
			_TrackInfo[j].bAudio = ((pTOC[4+(j-1)*8+1] & 0x4) == 0) ? TRUE : FALSE;
//			printf("track %d\n", j+1);
//			printf("LBA = %d\n", _TrackInfo[j+1].lba);
//			printf("bAudio = %d\n", _TrackInfo[j+1].bAudio);
		}
		return TRUE;
	}

	return FALSE;
}


//Kitao�ǉ��B�C���X�g�[������Ootake�o�[�W������ǂݍ���Ő���Ƀ��b�s���O�o���Ă���t�@�C�����ǂ����𔻒f����BCDROM.cpp��������p�Bv2.31
BOOL //�o�[�W�����̋L�ڂ��Ȃ������ꍇFALSE��Ԃ��B�o�[�W�����L�ڂ̗L���ɂ�����炸�A_bBadInstalled���ݒ肳���B
CDIF_SetBadInstalled(
	FILE*	fp)
{
	char	buf[256];
	char	ver[4];
	int		v;

	_bBadInstalled = FALSE;
	strcpy(buf, "");
	if (fgets(buf, 255, fp))
	{
		if (strstr(buf,"REM ver"))
		{
			ver[0] = buf[7];
			ver[1] = buf[8];
			ver[2] = buf[9];
			ver[3] = 0;
			v = atoi(ver);
			if (v < 232) //v2.32�����̏ꍇ�A���y�g���b�N�P���̃��b�s���O�s�����B
				_bBadInstalled = TRUE;
			if (v == 250) //v2.50�̏ꍇ�A���y�g���b�N�P��CUE�t�@�C���̃��b�s���O�s�����B
				_bBadInstalled = TRUE;
			return TRUE;
		}
		else //�o�[�W�����L�ڂ��Ȃ��ꍇ
			_bBadInstalled = TRUE; //���y�g���b�N�P���̃��b�s���O�s��\������B
	}
	return FALSE;
}

//Kitao�ǉ��BCue�t�@�C������TOC���쐬����Bv2.24
static BOOL
read_toc_cue()
{
	FILE*	fp;
	FILE*	fp2;
	char	buf[256];
	char	buf2[256];
	char*	r;
	Uint32	tn;	
	Uint32	lba;
	char*	pi;
	char*	pi2;
	char	installPath[MAX_PATH+1];
	char	fn[MAX_PATH+1];
	DWORD	size;

	fp = fopen(APP_GetCueFilePathName(), "r");
	if (fp == NULL)	return FALSE;

	SetCursor(LoadCursor(NULL, IDC_WAIT)); //�g���b�N�������Ǝ��Ԃ��|����̂ŁA�J�[�\���������v�ɁB

	strcpy(installPath, APP_GetCueFilePathName());
	pi = strrchr(installPath, '\\');
	if (pi != NULL)	*(pi+1)=0; //installPath�̃t�@�C�����������J�b�g

	tn = 1; //�g���b�N�i���o�[
	lba = 0;

	//v2.31�ǉ��B�C���X�g�[������Ootake�o�[�W������ǂݍ���Ő���Ƀ��b�s���O�o���Ă���t�@�C�����ǂ����𔻒f����B
	if (!CDIF_SetBadInstalled(fp))
	{	//�o�[�W�����L�ڂ��Ȃ��ꍇ(v2.30�ȑO��cue)�A�t�@�C����擪����J���Ȃ����B
		fclose(fp);
		fp = fopen(APP_GetCueFilePathName(), "r");
	}

	while (TRUE)
	{
		strcpy(buf, "");
		while (strstr(buf,"FILE ") == NULL)
		{
			r = fgets(buf, 255, fp);
			if (r == NULL) break;
		}
		if (r == NULL)
			 break; //"FILE"��������Ȃ��Ȃ�����I��
		pi = strstr(buf,"FILE ") + 5;
		if (*pi == '"') pi++;
		strcpy(buf2, pi);
		pi2 = strstr(buf2,".");
		if (pi2 != NULL)
		{
			pi2 += 4;
			strcpy(buf, pi2);
			*pi2 = 0; //buf2�̓��e���t�@�C�����݂̂ɂȂ�
		}
		strcpy(fn, installPath);
		strcat(fn, buf2);
		fp2 = fopen(fn, "rb");
		if (fp2 == NULL) break;
		fseek(fp2, 0, SEEK_END);
		size = ftell(fp2);
		fclose(fp2);
		r = fgets(buf2, 255, fp); //"TRACK"�̍s��ǂݔ�΂�
		r = fgets(buf2, 255, fp);
		if (r != NULL)
			if (strstr(buf2,"PREGAP") != NULL)
				lba += 150; //�v���M���b�v�Ԃ�𑫂�
		_TrackInfo[tn].lba = lba;
		if (strstr(buf,"BINARY") != NULL) //iso�̏ꍇ
		{
			_TrackInfo[tn].bAudio = FALSE;
			lba += size / 2048;
		}
		else //wav�̏ꍇ
		{
			_TrackInfo[tn].bAudio = TRUE;
			lba += (size - 44) / 2352; //44=WAVE�w�b�_�Ԃ�
		}
		tn++;
	}
	fclose(fp);

	//���[�h�A�E�g��ݒ�
	_TrackInfo[tn].bAudio = FALSE;
	_TrackInfo[tn].lba = lba;
	_LastTrack = tn - 1;

	SetCursor(LoadCursor(NULL, IDC_ARROW)); //�J�[�\�������ɖ߂�

	//PRINTF("TrackInfo Test = %X", _TrackInfo[10].lba);

	if (_LastTrack == 0)
		return FALSE;
	else
		return TRUE;
}


static void
cdb_play(
	BYTE*		cdb,
	CdArg*		pArg)
{
	ZeroMemory(cdb, sizeof(BYTE)*10);

	cdb[0] = SCSI_PLAYAUD_12;

	cdb[2] = (BYTE)(pArg->startLBA >> 24);
	cdb[3] = (BYTE)(pArg->startLBA >> 16);
	cdb[4] = (BYTE)(pArg->startLBA >> 8);
	cdb[5] = (BYTE)pArg->startLBA;

	cdb[6] = (BYTE)(pArg->endLBA >> 24);
	cdb[7] = (BYTE)(pArg->endLBA >> 16);
	cdb[8] = (BYTE)(pArg->endLBA >> 8);
	cdb[9] = (BYTE)pArg->endLBA;
}


static void
cdb_pause(
	BYTE*		cdb,
	CdArg*		pArg)
{
	BYTE		lun = (BYTE)_CdromInfo[_DeviceInUse].lun;

	cdb[0] = 0x4B;
	cdb[1] = (lun << 5) | 1;
	cdb[2] = 0;
	cdb[3] = 0;
	cdb[4] = 0;
	cdb[5] = 0;
	cdb[6] = 0;
	cdb[7] = 0;
	cdb[8] = 0;
	cdb[9] = 0;
}


static void
cdb_resume(
	BYTE*		cdb,
	CdArg*		pArg)
{
	BYTE		lun = (BYTE)_CdromInfo[_DeviceInUse].lun;

	cdb[0] = 0x4B;
	cdb[1] = (lun << 5) | 1;
	cdb[2] = 0;
	cdb[3] = 0;
	cdb[4] = 0;
	cdb[5] = 0;
	cdb[6] = 0;
	cdb[7] = 0;
	cdb[8] = 1;
	cdb[9] = 0;
}


static void
cdb_stop(
	BYTE*		cdb,
	CdArg*		pArg)
{
	BYTE		lun = (BYTE)_CdromInfo[_DeviceInUse].lun;

	cdb[0] = 0x4B;
	cdb[1] = (lun << 5) | 1;
	cdb[2] = 0;
	cdb[3] = 0;
	cdb[4] = 0;
	cdb[5] = 0;
	cdb[6] = 0;
	cdb[7] = 0;
	cdb[8] = 0;
	cdb[9] = 0;
}


static void
cdb_seek(
	BYTE*		cdb,
	CdArg*		pArg)
{
	BYTE		lun = (BYTE)_CdromInfo[_DeviceInUse].lun;

	ZeroMemory(cdb, sizeof(BYTE)*10);

	cdb[0] = 0x2B;
	cdb[1] = lun << 5;
	cdb[2] = (BYTE)(pArg->startLBA >> 24);
	cdb[3] = (BYTE)(pArg->startLBA >> 16);
	cdb[4] = (BYTE)(pArg->startLBA >>  8);
	cdb[5] = (BYTE)(pArg->startLBA      );
}


static BOOL
execute_command(
	BYTE*		cdb,
	CdArg*		pArg)
{
	BYTE		ha  = (BYTE)_CdromInfo[_DeviceInUse].adapter;
	BYTE		tg  = (BYTE)_CdromInfo[_DeviceInUse].target;
	BYTE		lun = (BYTE)_CdromInfo[_DeviceInUse].lun;

	if (execute_scsi_command(NULL, 0, ha, tg, lun, cdb, sizeof(BYTE)*10))
		return TRUE;

	return FALSE;
}


//Kitao�X�V�B��x�̃A�N�Z�X�œǂݍ��ރZ�N�^�[���𑽂����A�����������Bv1.00
//�V���[���b�N�z�[���Y���������������������ׂ����������͂��B
static BOOL
execute_read(
	BYTE*		cdb,
	CdArg*		pArg)
{
	BYTE	ha  = (BYTE)_CdromInfo[_DeviceInUse].adapter;
	BYTE	tg  = (BYTE)_CdromInfo[_DeviceInUse].target;
	BYTE	lun = (BYTE)_CdromInfo[_DeviceInUse].lun;

	int			i;
	int			nSectors;
	Uint32		lba;

	nSectors = pArg->endLBA - pArg->startLBA;
	lba      = pArg->startLBA;

	for (i=0; i<nSectors; i++)
	{
		ZeroMemory(cdb, sizeof(BYTE)*10);
		cdb[0]     = 0x28;	//   READ10�B�h���C�u�̌݊����̖�������邽�߁APC2E�Ɠ��l��READ10���g���悤�ɂ����Bv0.69�B
		cdb[1]     = (BYTE)(lun << 5);
		cdb[3]     = (BYTE)(lba >> 16);
		cdb[4]     = (BYTE)(lba >> 8);
		cdb[5]     = (BYTE)(lba);
		cdb[8]     = 1; //Kitao�Q�l�B�����ŕ����Z�N�^�ǂݍ������Ƃ���Ǝ��s���邱�Ƃ��������B
		
		if (execute_scsi_command(_pReadBuf, 2048, ha, tg, lun, cdb, sizeof(BYTE)*10))
		{
			CopyMemory(pArg->pBuf + i*2048, _pReadBuf, 2048);
			lba++;
		}
		else
		{
			ZeroMemory(pArg->pBuf + i*2048, 2048*(nSectors-i)); //�ǂݍ��߂Ȃ������̈��0�Ŗ��߂Ă��烊�^�[���Bv2.11�X�V
			return FALSE;
		}
	}

	return TRUE;
}


//Kitao�ǉ��BCD�f�[�^���C���X�g�[�����Ă������ꍇ�p��read����(CD�̑����HDD�̃t�@�C���փA�N�Z�X)�B
//			 v1.58���炱�̃X���b�h�ōs���悤�ɂ���(���C���X���b�h���Ƒ傫�ȓǂݍ��ݎ��ɁA�x�������ꍇ�����m�C�Y���o������)�B
static BOOL
execute_readHdd(
	BYTE*		cdb,
	CdArg*		pArg)	//pArg->track�Ƀg���b�N�i���o�[�CpArg->endLBA�ɓǂݍ��ރZ�N�^�[��(nSectors)�CpArg->startLBA�ɓǂݍ��݊J�n�A�h���X��ݒ肵�ČĂԁB
{
	int		nSectors;
	int		track;
	FILE*	fp;
	char	fileName[MAX_PATH+1];

	nSectors = pArg->endLBA;
	track = pArg->track;

	CDROM_SetInstallFileName(track, fileName);
	if ((fp = fopen(fileName, "rb")) != NULL)
	{
		fseek(fp, pArg->startLBA, SEEK_SET);
		fread(pArg->pBuf, nSectors*2048, 1, fp);
		fclose(fp);
		return TRUE;
	}
	else
		return FALSE;
}


//Kitao�ǉ��BCD-DA(���y�f�[�^)�̃Z�N�^�[��ǂݍ��ށBv2.32�f�[�^�g���b�N���ǂ����̔��f�͂����ƌ��������K�v�������̂ő��x�̖����܂߂�scsi�h���C�o�ɔC����悤�ɂ����B
static BOOL
execute_readCdda(
	BYTE*		cdb,
	CdArg*		pArg)
{
	BYTE	ha  = (BYTE)_CdromInfo[_DeviceInUse].adapter;
	BYTE	tg  = (BYTE)_CdromInfo[_DeviceInUse].target;
	BYTE	lun = (BYTE)_CdromInfo[_DeviceInUse].lun;

	int		i;
	int		nSectors;
	Uint32	lba;

	nSectors = pArg->endLBA - pArg->startLBA;
	lba      = pArg->startLBA;

	for (i=0; i<nSectors; i++)
	{
		ZeroMemory(cdb, sizeof(BYTE)*12);
		cdb[0]     = 0xBE;	//   READ CD LBA
		cdb[1]     = 0x04;	//   CDDA Sector ����œǂ񂾏ꍇ�A�h���C�u�ɂ���Ă͒ᑬ(�É�)�œǂݍ���ł����H
		cdb[2]     = (BYTE)(lba >> 24);
		cdb[3]     = (BYTE)(lba >> 16);
		cdb[4]     = (BYTE)(lba >> 8);
		cdb[5]     = (BYTE)(lba);
		cdb[8]     = 1; //Kitao�Q�l�B�����ŕ����Z�N�^�ǂݍ������Ƃ���Ƃ��܂������Ȃ������B
		cdb[9]     = 0x10;	//   UserData
		
		//PRINTF("READ CD LBA = %X", lba);//test
		if (execute_scsi_command(_pCDDAReadBuf, 2352, ha, tg, lun, cdb, sizeof(BYTE)*12))
		{
			CopyMemory(pArg->pBuf + i*2352, _pCDDAReadBuf, 2352);
			lba++;
		}
		else
		{
			ZeroMemory(pArg->pBuf + i*2352, (nSectors-i)*2352); //�ǂݍ��߂Ȃ������̈��0�Ŗ��߂Ă��烊�^�[���B���@���X�S��ACT4�f���V�[���ŕK�v�Bv2.11�X�V
			return FALSE;
		}
	}

	return TRUE;
}


//Kitao�ǉ��BCD�f�[�^���C���X�g�[�����Ă������ꍇ�p��CD-DAread����(CD�̑����HDD�̃t�@�C���փA�N�Z�X)�B
static BOOL
execute_readCddaHdd(
	BYTE*		cdb,
	CdArg*		pArg)	//pArg->track�Ƀg���b�N�i���o�[�CpArg->endLBA�ɓǂݍ��ރZ�N�^�[��(nSectors)�CpArg->startLBA�ɓǂݍ��݊J�n�A�h���X��ݒ肵�ČĂԁB
{
	int		i;
	int		nSectors;
	FILE*	fp;
	char	fileName[MAX_PATH+1];
	size_t	size;

	nSectors = pArg->endLBA;
	ZeroMemory(pArg->pBuf, nSectors*2352); //�ǂݍ��߂Ȃ������̈��0�Ŗ��߂�B���@���X�S��ACT4�f���V�[���ŕK�v�Bv2.26

	CDROM_SetInstallWavFileName(pArg->track, fileName);
	if ((fp = fopen(fileName, "rb")) != NULL)
	{
		fseek(fp, pArg->startLBA, SEEK_SET);
		size = fread(pArg->pBuf, nSectors*2352, 1, fp);
		if (size == 0)
		{	//�S�̈��ǂݍ��߂Ȃ������ꍇ�A���̃g���b�N�����y�g���b�N�Ȃ�A��������ǂݏo���B
			fseek(fp, pArg->startLBA, SEEK_SET);
			for (i=0; i<nSectors; i++) //���g���b�N����ǂ��܂œǂ߂������m���߂�
				if (fread(pArg->pBuf + i*2352, 2352, 1, fp) == 0)
					break;
			fclose(fp);
			CDROM_SetInstallWavFileName(pArg->track + 1, fileName);
			if ((fp = fopen(fileName, "rb")) != NULL)
			{
				fseek(fp, 44, SEEK_SET); //44=�g�`�f�[�^�̐擪
				size = fread(pArg->pBuf + i*2352, (nSectors - i)*2352, 1, fp);
				fclose(fp);
				if (size != 0)
					return TRUE; //�S�̈��ǂݍ��߂�
			}
			return FALSE;
			//���R�̒Z��������g���b�N���܂������Ă���ꍇ�͋��炭�����P�[�X�Ȃ̂ŁA����͑z�肵�Ȃ��B
		}
		else
		{
			fclose(fp);
			return TRUE; //�S�̈��ǂݍ��߂�
		}
	}
	else
		return FALSE;
}


static BOOL
execute_subq(
	BYTE*		cdb,
	CdArg*		pArg)
{
	BYTE	subq[20];
	BYTE	ha  = (BYTE)_CdromInfo[_DeviceInUse].adapter;
	BYTE	tg  = (BYTE)_CdromInfo[_DeviceInUse].target;
	BYTE	lun = (BYTE)_CdromInfo[_DeviceInUse].lun;
	BYTE*	pBuf = (BYTE*)pArg->pBuf;

	ZeroMemory(cdb, sizeof(BYTE)*10);
	cdb[0]		= 0x42;
	cdb[1]		= (lun << 5) | 2;
	cdb[2]		= 0x40;				// sub q channel
	cdb[3]		= 0x01;				// current pos info
	cdb[6]		= 0;
	cdb[7]		= 0;
	cdb[8]		= sizeof(subq);		// buffer length

	if (execute_scsi_command(subq, sizeof(subq), ha, tg, lun, cdb, sizeof(BYTE)*10))
	{
//		pBuf[1] = subq[0] >> 4;		// control
		pBuf[1] = subq[7];
		pBuf[2] = subq[6];			// track #
//		pBuf[3] = subq[7];			// index ??
		pBuf[3] = subq[0] >> 4;		// control
		pBuf[4] = subq[13];			// min (track)
		pBuf[5] = subq[14];			// sec (track)
		pBuf[6] = subq[15];			// frame (track)
		pBuf[7] = subq[9];			// min (total)
		pBuf[8] = subq[10];			// sec (total)
		pBuf[9] = subq[11];			// frame (total)

		return TRUE;
	}

	return FALSE;
}


static DWORD WINAPI
cdif_main_thread(
	LPVOID	param)
{
	BYTE		cdb[12]; //Kitao�X�V
	HANDLE		hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, CDIF_EVENT);
	CdArg*		pArg = (CdArg*)param;
	BOOL		bSuccess;
	int			retry;

	while (hEvent != NULL)
	{
		WaitForSingleObject(hEvent, INFINITE);

		//PRINTF("Test %X", pArg->command);
		if (pArg->command == CDIF_EXIT)
			break;

		bSuccess = FALSE;
		retry = 1; //�G���[���̃��g���C�񐔁B���@��ł��͈͊O�̃Z�N�^�[�ȂǂɃA�N�Z�X�����݂悤�Ƃ���\�t�g������A���̏ꍇ�́A�G���[��Ԃ��K�v������B
				   //			             �Ȃ̂Ń��g���C�񐔂𑽂���������ƃ\�t�g�̓��삪���������ꂪ����B���~���O�X��OP�f���ȂǁB
				   //						 ����̓��g���C���Ȃ��悤�ɂ��āA����e�X�g�p�Ɏg���Bv2.17�ǉ�

		while ((!bSuccess)&&(retry > 0)) //Kitao�X�V�B��������܂ōő�retry��J��Ԃ���悤�ɂ����Bv2.17
		{
			switch (pArg->command)
			{
				case CDIF_READ://Kitao�X�V
					bSuccess = execute_read(cdb, pArg);
					break;

				case CDIF_READHDD://Kitao�ǉ�
					bSuccess = execute_readHdd(cdb, pArg);
					break;

				case CDIF_SEEK:  //Audio Seek�BKitao�X�V�B�V�[�N���ɏ���o�b�t�@�Ԃ��ǂݍ��ނ悤�ɂ����Bv2.29
					bSuccess = execute_readCdda(cdb, pArg); //READCDDA�Ɠ��������B�R�[���o�b�N��̏������قȂ�B
					break;

				case CDIF_SEEKHDD: //Kitao�ǉ��B���y�g���b�N�f�[�^���C���X�g�[�����Ă������ꍇ�p��Audio Seek�B�V�[�N���ɏ���o�b�t�@�Ԃ��ǂݍ��ނ悤�ɂ����Bv2.29�X�V
					bSuccess = execute_readCddaHdd(cdb, pArg); //READCDDAHDD�Ɠ��������B�R�[���o�b�N��̏������قȂ�B
					break;

				case CDIF_PLAYCDDA://Kitao�ǉ��Bv2.29
					bSuccess = TRUE; //�������Ȃ��ŋA��BCDIF_PLAYCDDA�́A�E�F�C�g�����邽�߂ɗ��p�B
					break;

				case CDIF_READCDDA://Kitao�ǉ�
				case CDIF_READCDDA2://Kitao�ǉ��B�����ł̏�����CDIF_READCDDA�Ƌ��ʁB�R�[���o�b�N��̏������قȂ�B
					bSuccess = execute_readCdda(cdb, pArg);
					break;

				case CDIF_READCDDAHDD://Kitao�ǉ�
				case CDIF_READCDDA2HDD://Kitao�ǉ��B�����ł̏�����CDIF_READCDDAHDD�Ƌ��ʁB�R�[���o�b�N��̏������قȂ�B
					bSuccess = execute_readCddaHdd(cdb, pArg);
					break;

				case CDIF_SEEKDATA: //Kitao�ǉ��B�Z�J���_���o�b�t�@�ɐ�ǂ݂������Ȃ��B
					bSuccess = execute_read(cdb, pArg);
					//�������ł̏�����CDIF_READ�Ɠ��������A�R�[���o�b�N��̏������قȂ�B
					break;

				case CDIF_SEEKDATAHDD: //Kitao�ǉ��B�f�[�^���C���X�g�[�����Ă������ꍇ�p�̃V�[�N(CD�̑����HDD�̃t�@�C���փA�N�Z�X)�B�Z�J���_���o�b�t�@�ɐ�ǂ݂������Ȃ��B
					bSuccess = execute_readHdd(cdb, pArg);
					break;

				case CDIF_SUBQ:
					bSuccess = execute_subq(cdb, pArg);
					break;

				case CDIF_INSTALL://Kitao�ǉ�
					bSuccess = execute_read(cdb, pArg);
					break;

				case CDIF_INSTALLWAV://Kitao�ǉ�
					bSuccess = execute_readCdda(cdb, pArg);
					break;
			}

			/* �����̊�����ʒm���� */
			if (_Callback && pArg->bCallback)
			{
				if (bSuccess)
					_Callback(pArg->command);
				else
				{	//���s�����ꍇ�A���g���C����Bv2.17�X�V
					//PRINTF("CD-ROM Read Error."); //�G���[���N�������Ƃ��O���(�G���[��Ԃ��Ȃ��ᓮ���Ȃ�)�Q�[�������邽�߁A�G���[���b�Z�[�W�͕\�������B���~���O�X��OP�ȂǁB
					retry--;
					if (retry == 0) //���łɌvretreu��g���C(retry-1�񃊃g���C)���Ă�����A������߂ăG���[�Ŗ߂�B
						_Callback(pArg->command | CDIF_ERROR);
					else
						Sleep(1000); //�����ł�����PC�󋵂�ω������邽�߁A�P�b�E�F�C�g������B���ꂪ�����ƁA�G���[�O��̃\�t�g�Ń��b�T������\��������B
				}
			}
			else
				bSuccess = TRUE; //�R�[���o�b�N���Ȃ��ꍇ�A��ɐ����Ƃ��ă��[�v�𔲂���Bv2.17
		}

		_bDeviceBusy = FALSE; //Kitao�X�V�B�R�[���o�b�N���I���Ă���f�o�C�X�r�W�[�������B
	}

	CloseHandle(hEvent);
	ExitThread(TRUE);

	return 0;
}


Sint32
CDIF_GetNumDevices()
{
	return _nCdromDevice;
}


BOOL
CDIF_SelectDevice(
	Sint32	deviceNum)
{
	char	path[10];

	if (APP_GetCueFile()) //Cue�t�@�C������N�����郂�[�h�̏ꍇ�Bv2.24
		return read_toc_cue();

	if ((deviceNum >= 0)&&(deviceNum < _nCdromDevice))
	{
		_DeviceInUse = deviceNum;
		//Kitao�X�V�B������SPTI�̃n���h�����擾���Ă����悤�ɂ���(������������)
		if (_bUseSpti)
		{
			if (_SPTIfileHandle != INVALID_HANDLE_VALUE)
				CloseHandle(_SPTIfileHandle);
			sprintf(path, "\\\\.\\%c:", (int)(_DriveLetters[_DeviceInUse]));
			_SPTIfileHandle = CreateFile(path,
										GENERIC_READ | GENERIC_WRITE,
										FILE_SHARE_READ,
										NULL,
										OPEN_EXISTING,
										0,
										NULL); 
		}
		return read_toc();
	}

	return FALSE;
}


/*-----------------------------------------------------------------------------
	[Deinit]
		SPTI�܂���ASPI���I�����܂��B
-----------------------------------------------------------------------------*/
void
CDIF_Deinit()
{
	if (_bInit) //Kitao�X�V�B���������������Ă����Ƃ����������Ȃ��Bv1.04
		waitDeviceBusy();

	if (_hEvent != NULL) //Kitao�ǉ��Bv1.04
	{
		_CdArg.command = CDIF_EXIT;
		SetEvent(_hEvent);
		
		// �X���b�h�̏I����҂� 
		if (_hThread != INVALID_HANDLE_VALUE)
		{
			WaitForSingleObject(_hThread, INFINITE);
			CloseHandle(_hThread);
			_hThread = INVALID_HANDLE_VALUE;
		}
		
		CloseHandle(_hEvent);
	}

	//Kitao�ǉ�
	if (_SPTIfileHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_SPTIfileHandle);
		_SPTIfileHandle = INVALID_HANDLE_VALUE;
	}

	if (_hWNASPI32 != INVALID_HANDLE_VALUE)
	{
		FreeLibrary((HMODULE)_hWNASPI32);
		_hWNASPI32 = INVALID_HANDLE_VALUE;
	}

	_nAdapters = 0;
	_nCdromDevice = 0;
	_bUseSpti = TRUE;
	ZeroMemory(_DriveLetters, sizeof(_DriveLetters));

	_bDeviceBusy = FALSE;

	_bInit = FALSE; //Kitao�ǉ��Bv1.04
}


/*-----------------------------------------------------------------------------
	[Init]
		SPTI�܂���ASPI�����������܂��B
-----------------------------------------------------------------------------*/
Sint32 //v2.33�X�V�B-1=�G���[�B0�`=��������CD-ROM(DVD,BD)�h���C�u���B
CDIF_Init(
	void	(*callback)(Uint32))
{
	int			i;
	char		buf[4*26+2];
	DWORD		dwSupportInfo;

	if (callback == NULL)
		return -1;
	_Callback = callback;
	_bInit = TRUE; //Kitao�ǉ��Bv1.04�Bv2.33

	//�擪�A�h���X��16�o�C�g���E�̃o�b�t�@��p�ӂ���B�iKitao�X�V�B�����Ńo�b�t�@�������ݒ肵�Ă����悤�ɂ����B�������j
	_pReadBuf = (BYTE*)(((Uint32)&_ReadBuf[0] + 0xF) & ~0xF);
	_pCDDAReadBuf = (BYTE*)(((Uint32)&_CDDAReadBuf[0] + 0xF) & ~0xF);

	//�L���ȃh���C�u���^�[���擾���� 
	ZeroMemory(&buf, sizeof(buf));
	GetLogicalDriveStrings(sizeof(buf), buf);

	//Kitao�X�V�BCD-ROM�h���C�u������
	for (i=0; buf[i]!=0; i+=4)
		if (GetDriveType(&buf[i]) == DRIVE_CDROM)
		{
			_DriveLetters[_nCdromDevice++] = buf[i];
			if (_nCdromDevice >= 26)
				break;
		}

	//Kitao�ǉ��BOS��NT�n�Ȃ�SPTI���g�p����B�����萫���h���C�u��������ւ���Ă��܂��\��������邽�߁B
	if (APP_GetWindows9x())	//Win95,98,Me�Ȃ�
	{
		_bUseSpti = FALSE;
		
		// load WNASPI32.DLL
		if ((_hWNASPI32 = LoadLibrary("WNASPI32.DLL")) == 0)
		{
			PRINTF("CDIF_Init: \"WNASPI32.DLL\" not found.");
			return -1;
		}

		// load the address of GetASPI32SupportInfo
		_pfnGetASPI32SupportInfo = (LPGETASPI32SUPPORTINFO)GetProcAddress((HMODULE)_hWNASPI32, "GetASPI32SupportInfo");
		if (_pfnGetASPI32SupportInfo == NULL)
		{
			PRINTF("CDIF_Init: DLL function \"GetASPI32SupportInfo\" not found.");
			return -1;
		}
		// load the address of SendASPI32Command
		_pfnSendASPI32Command = (LPSENDASPI32COMMAND)GetProcAddress((HMODULE)_hWNASPI32, "SendASPI32Command");
		if (_pfnSendASPI32Command == NULL)
		{
			PRINTF("CDIF_Init: DLL function \"SendASPI32Command\" not found.");
			return -1;
		}
		
		//Kitao�X�V�BASPI�Ńh���C�u����ݒ�
		dwSupportInfo = _pfnGetASPI32SupportInfo();
		if (HIBYTE(LOWORD(dwSupportInfo)) == SS_COMP)
		{
			_nAdapters = LOBYTE(LOWORD(dwSupportInfo));
			_nCdromDevice = scan_cdrom_devices();
		}
	}
	else //NT�n(2000,XP,����ȍ~��)�Ȃ�
		_bUseSpti = TRUE;

	// �X���b�h����p�̃C�x���g���쐬���� 
	_hEvent = CreateEvent(NULL , FALSE, FALSE , CDIF_EVENT);
	if (_hEvent == NULL)
	{
		CDIF_Deinit();
		return -1;
	}
	// ���C���X���b�h���쐬���Ď��s����
	clearCdArg(); //��ɏ���������悤�ɂ����Bv1.04
	_hThread = CreateThread(NULL, 0, cdif_main_thread, (LPVOID)&_CdArg, 0, &_dwThreadID);
	if (_hThread == NULL)
	{
		CDIF_Deinit();
		return -1;
	}

	return _nCdromDevice; //v2.33����CD-ROM�h���C�u�̑�����Ԃ��悤�ɂ����B�P������p�ł���CD-ROM�h���C�u�������ꍇ�ł�����������������������0��Ԃ��B
}


Sint32
CDIF_GetFirstTrack()
{
	return _FirstTrack;
}


Sint32
CDIF_GetLastTrack()
{
	return _LastTrack;
}


//MSF�̒l����g���b�N�i���o�[��Ԃ��Bv2.11�ǉ�
Uint32
CDIF_GetTrackNumber(
	Uint32	m,
	Uint32	s,
	Uint32	f)
{
	Sint32	track = _FirstTrack;
	Uint32	msf = (m << 16) + (s << 8) + f;
	Uint32	msf2;
	Uint32	lba;
	Uint32	lba2;

	while (track <= _LastTrack+1) //Kitao�X�V�B�ŏI�g���b�N��CD-DA���点��悤��lastTrack+1�Ƃ����BLinda3�Ŕ���
	{
		msf2 = CDIF_GetTrackStartPositionMSF(track) >> 8;
		if (msf < msf2)
		{
			if (_TrackInfo[track].bAudio == FALSE) //�f�[�^�g���b�N�������ꍇ�A�v���M���b�v���l������B
			{
				lba = msf2lba(m, s, f) + 150;
				lba2 = msf2lba((msf2 >> 16), (msf2 >> 8) & 0xFF, msf2 & 0xFF) - 150;
				if (lba >= lba2) //�M���b�v�̈�ɓ����Ă����ꍇ�A���̃g���b�N�ԍ���Ԃ��B
					return track;
			}
			return track - 1;
		}
		track++;
	}

	return 0;
}


/*-----------------------------------------------------------------------------
	[GetTrackStartPositionLBA]
		�g���b�N�̊J�n�ʒu�� LBA �ŕԂ��܂��B
-----------------------------------------------------------------------------*/
Uint32
CDIF_GetTrackStartPositionLBA(
	Sint32	track)
{
	// LastTrack+1 �ɂ̓��[�h�A�E�g�f�[�^�������Ă���̂ŋ����� 
	if (track > _LastTrack+1)
		return 0;

	return _TrackInfo[track].lba;
}


/*-----------------------------------------------------------------------------
	[GetTrackStartPositionMSF]
		�g���b�N�̊J�n�ʒu�� MSF �ŕԂ��܂��B
-----------------------------------------------------------------------------*/
Uint32
CDIF_GetTrackStartPositionMSF(
	Sint32	track)
{
	Uint32	lba;
	Uint8	min;
	Uint8	sec;
	Uint8	frame;
	Uint8	datatrack;

	if (track > _LastTrack+1)
		return 0;
	
	lba   = _TrackInfo[track].lba + 150; //Kitao�ǋL�B150�c�v���M���b�v(�Q�b)
	min   = (Uint8)(lba / 75 / 60);
	sec   = (Uint8)((lba - (Uint32)min * 75 * 60) / 75);
	frame = (Uint8)(lba - ((Uint32)min * 75 * 60) - ((Uint32)sec * 75));

	datatrack = _TrackInfo[track].bAudio ? 0 : 4;

	return (min << 24) + (sec << 16) + (frame << 8) + datatrack;
}


//CD-ROM��Read���x��ݒ肷��BKitao�X�Vv2.50
BOOL
CDIF_SetSpeed(
	Uint32	speed)		// �{�� 
{
	BYTE	cdb[12];
	BYTE	ha  = (BYTE)_CdromInfo[_DeviceInUse].adapter;
	BYTE	tg  = (BYTE)_CdromInfo[_DeviceInUse].target;
	BYTE	lun = (BYTE)_CdromInfo[_DeviceInUse].lun;
	BOOL	bSuccess;

	waitDeviceBusy();
	_bDeviceBusy = TRUE;

	if (speed == 0)
		speed = 0xFFFF; //Kitao�X�V�B0�̏ꍇ�A�ō����ɐݒ肷��悤�ɂ����B
	else
		speed *= 176;

	ZeroMemory(cdb, sizeof(cdb)); //Kitao�ǉ�
	cdb[0] = 0xBB; //Set CD Speed
	cdb[1] = lun << 5;
	cdb[2] = (BYTE)(speed >> 8); //Read Speed
	cdb[3] = (BYTE)speed;		 //
	cdb[4] = 0xFF; //Write Speed
	cdb[5] = 0xFF; //

	bSuccess = execute_scsi_command(NULL, 0, ha, tg, lun, cdb, sizeof(cdb));
	_bDeviceBusy = FALSE;

	return bSuccess;
}


/*-----------------------------------------------------------------------------
	[ReadSector]
		�w��̃h���C�u����w��̃Z�N�^��ǂݏo���܂��B
-----------------------------------------------------------------------------*/
//Kitao�X�V�B�f�[�^��Read�̓Z�J���_���o�b�t�@�֓ǂݍ��ނ悤�ɂ����Bv0.80�B
BOOL
CDIF_ReadSector(
	Uint8*		pBuf,				// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Uint32		sector,				// �Z�N�^�ԍ� 
	Uint32		nSectors,			// �ǂݏo���Z�N�^�� 
	BOOL		bCallback)
{
	waitDeviceBusy();
	_bDeviceBusy = TRUE;

	clearCdArg();
	_CdArg.command = CDIF_READ;
	_CdArg.pBuf = pBuf;
	_CdArg.startLBA = sector;
	_CdArg.endLBA   = sector + nSectors;
	_CdArg.bCallback = bCallback;

	SetEvent(_hEvent);

	return TRUE;
}


//Kitao�ǉ��B�f�[�^��Read�̓Z�J���_���o�b�t�@�֓ǂݍ��ނ悤�ɂ����BCD�C���X�g�[�����Ă������Ƃ��p�Bv2.24�ǉ�
BOOL
CDIF_ReadSectorHDD(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Sint32		track,		// �ǂݍ��ރg���b�N�i���o�[
	Uint32		addr,		// �ǂݍ��ރA�h���X�B�g���b�N(���t�@�C��)�̐擪��0x0000�Ƃ���B
	Sint32		nSectors,	// �ǂݏo���Z�N�^�� 
	BOOL		bCallback)
{
	waitDeviceBusy();
	_bDeviceBusy = TRUE;

	clearCdArg();
	_CdArg.command = CDIF_READHDD;
	_CdArg.pBuf = pBuf;
	_CdArg.track = track; //�g���b�N�i���o�[���i�[
	_CdArg.startLBA = addr; //�A�h���X���i�[
	_CdArg.endLBA   = nSectors; //�Z�N�^�[�����i�[
	_CdArg.bCallback = bCallback;

	SetEvent(_hEvent);

	return TRUE;
}


//Kitao�ǉ��BCD-DA����ǂݍ��ݗp
BOOL
CDIF_ReadCddaSector(
	Uint8*		pBuf,				// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Uint32		sector,				// �Z�N�^�ԍ� 
	Sint32		nSectors,			// �ǂݏo���Z�N�^�� 
	BOOL		bCallback)
{
	waitDeviceBusy();
	_bDeviceBusy = TRUE;

	clearCdArg();
	_CdArg.command = CDIF_READCDDA;
	_CdArg.pBuf = pBuf;
	_CdArg.startLBA = sector;
	_CdArg.endLBA   = sector + nSectors;
	_CdArg.bCallback = bCallback;

	SetEvent(_hEvent);

	return TRUE;
}

//Kitao�ǉ��BCD-DA����ǂݍ��ݗp�BCD�C���X�g�[�����Ă������Ƃ��p�Bv2.24�ǉ�
BOOL
CDIF_ReadCddaSectorHDD(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Sint32		track,		// �ǂݍ��ރg���b�N�i���o�[
	Uint32		addr,		// �ǂݍ��ރA�h���X�B�g���b�N(���t�@�C��(WAVE�w�b�_������̂�45�o�C�g�ڂ���))�̐擪��0x0000�Ƃ���B
	Sint32		nSectors,	// �ǂݏo���Z�N�^�� 
	BOOL		bCallback)
{
	waitDeviceBusy();
	_bDeviceBusy = TRUE;

	clearCdArg();
	_CdArg.command = CDIF_READCDDAHDD;
	_CdArg.pBuf = pBuf;
	_CdArg.track = track; //�g���b�N�i���o�[���i�[
	_CdArg.startLBA = 44 + addr; //�A�h���X���i�[�B��44=WAVE�w�b�_�Ԃ�
	_CdArg.endLBA   = nSectors; //�Z�N�^�[�����i�[
	_CdArg.bCallback = bCallback;

	SetEvent(_hEvent);

	return TRUE;
}


//���y�g���b�N�փV�[�N���s���BKitao�X�V�B����o�b�t�@�ւ�READ���s���悤�ɂ����Bv2.29
BOOL
CDIF_Seek(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Sint32		track,		// �ǂݍ��ރg���b�N�i���o�[
	Uint32		sector,		// �Z�N�^�ԍ� 
	Sint32		nSectors,	// �ǂݏo���Z�N�^�� 
	BOOL		bCallback)
{
	waitDeviceBusy();
	_bDeviceBusy = TRUE;

	clearCdArg();
	_CdArg.command = CDIF_SEEK;
	_CdArg.pBuf = pBuf;
	_CdArg.track = track; //�g���b�N�i���o�[���i�[�Bv2.32�ǉ�
	_CdArg.startLBA = sector;
	_CdArg.endLBA   = sector + nSectors;
	_CdArg.bCallback = bCallback;

	SetEvent(_hEvent);

	return TRUE;
}

//Kitao�ǉ��BCDIF_Seek(���y�g���b�N�փV�[�N���s��)��HDD�ŁB�g���b�N�f�[�^��CD�C���X�g�[�����Ă������ꍇ�Ƀn�[�h�f�B�X�N����f�[�^��ǂݍ��ށBv2.29
BOOL
CDIF_SeekHDD(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Sint32		track,		// �ǂݍ��ރg���b�N�i���o�[
	Uint32		addr,		// �ǂݍ��ރA�h���X�B�g���b�N(���t�@�C��(WAVE�w�b�_������̂�45�o�C�g�ڂ���))�̐擪��0x0000�Ƃ���B
	Sint32		nSectors,	// �ǂݏo���Z�N�^�� 
	BOOL		bCallback)
{
	waitDeviceBusy();
	_bDeviceBusy = TRUE;

	clearCdArg();
	_CdArg.command = CDIF_SEEKHDD;
	_CdArg.pBuf = pBuf;
	_CdArg.track = track; //�g���b�N�i���o�[���i�[
	_CdArg.startLBA = 44 + addr; //�A�h���X���i�[�B��44=WAVE�w�b�_�Ԃ�
	_CdArg.endLBA   = nSectors; //�Z�N�^�[�����i�[
	_CdArg.bCallback = bCallback;

	SetEvent(_hEvent);

	return TRUE;
}

//Kitao�ǉ��B�Đ����J�n����B���ۂɂ͍Đ��̍��}���o�������ŉ������Ȃ��B�R�[���o�b�N�ɂāA���@�ɋ߂��E�F�C�g�𔭐������邽�߂̏����Bv2.29
BOOL
CDIF_PlayCdda(
	BOOL	bCallback)
{
	waitDeviceBusy();
	_bDeviceBusy = TRUE;

	clearCdArg();
	_CdArg.command = CDIF_PLAYCDDA;
	_CdArg.bCallback = bCallback;

	SetEvent(_hEvent);

	return TRUE;
}


//Kitao�ǉ��BCD-DA�ǉ��ǂݍ��ݗp�B������APU�X���b�h��ŌĂяo�����B
BOOL
CDIF_ReadCddaSector2(
	Uint8*		pBuf,				// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Uint32		sector,				// �Z�N�^�ԍ� 
	Sint32		nSectors,			// �ǂݏo���Z�N�^�� 
	BOOL		bCallback)
{
	int		i;

	//CD�f�o�C�X���g�p���̏ꍇ�I���܂ő҂BAPU�X���b�h��Ŏ��s�����̂�APU�r�W�[�҂��͂��Ȃ��B
	//��CD-DA�����Đ����Ȃ̂ő���CD�f�o�C�X�g�p���̂��Ƃ͖����͂������A�O�̂��߂ɂ����ł��҂悤�ɂ��Ă����B
	i = 0;
	while (_bDeviceBusy && i<40000)
	{
		Sleep(1); //��40�b�o�ߔ���̂���Sleep(0)�͑ʖځBv2.05
		i++;
	}
	_bDeviceBusy = TRUE;

	clearCdArg();
	_CdArg.command = CDIF_READCDDA2;
	_CdArg.pBuf = pBuf;
	_CdArg.startLBA = sector;
	_CdArg.endLBA   = sector + nSectors;
	_CdArg.bCallback = bCallback;

	SetEvent(_hEvent);

	return TRUE;
}

//Kitao�ǉ��BCD-DA�ǉ��ǂݍ��ݗp�B������APU�X���b�h��ŌĂяo�����BCD�C���X�g�[�����Ă������Ƃ��p�Bv2.24�ǉ�
BOOL
CDIF_ReadCddaSector2HDD(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Sint32		track,		// �ǂݍ��ރg���b�N�i���o�[
	Uint32		addr,		// �ǂݍ��ރA�h���X�B�g���b�N(���t�@�C��(WAVE�w�b�_������̂�45�o�C�g�ڂ���))�̐擪��0x0000�Ƃ���B
	Sint32		nSectors,	// �ǂݏo���Z�N�^�� 
	BOOL		bCallback)
{
	int		i;

	//CD�f�o�C�X���g�p���̏ꍇ�I���܂ő҂BAPU�X���b�h��Ŏ��s�����̂�APU�r�W�[�҂��͂��Ȃ��B
	//��CD-DA�����Đ����Ȃ̂ő���CD�f�o�C�X�g�p���̂��Ƃ͖����͂������A�O�̂��߂ɂ����ł��҂悤�ɂ��Ă����B
	i = 0;
	while (_bDeviceBusy && i<40000)
	{
		Sleep(1); //��40�b�o�ߔ���̂���Sleep(0)�͑ʖځBv2.05
		i++;
	}
	_bDeviceBusy = TRUE;

	clearCdArg();
	_CdArg.command = CDIF_READCDDA2HDD;
	_CdArg.pBuf = pBuf;
	_CdArg.track = track; //�g���b�N�i���o�[���i�[
	_CdArg.startLBA = 44 + addr; //�A�h���X���i�[�B��44=WAVE�w�b�_�Ԃ�
	_CdArg.endLBA   = nSectors; //�Z�N�^�[�����i�[
	_CdArg.bCallback = bCallback;

	SetEvent(_hEvent);

	return TRUE;
}


/*-----------------------------------------------------------------------------
	[IsDeviceBusy]
		CDROM�f�o�C�X���R�}���h���s�����ǂ�����Ԃ��܂��B

	return:
		BOOL			TRUE --- device is busy
		BOOL			FALSE -- device is idle
-----------------------------------------------------------------------------*/
BOOL
CDIF_IsDeviceBusy()
{
	return _bDeviceBusy;
}


//Kitao�ǉ��B�f�[�^��Read���钼�O�p�B�Z�N�^�[�̐�ǂ݂��s���B
BOOL
CDIF_SeekData(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ���
	Uint32		sector,		// �Z�N�^�ԍ�
	Uint32		nSectors,	// �ǂݏo���Z�N�^��
	BOOL		bCallback)
{
	waitDeviceBusy();
	_bDeviceBusy = TRUE;

	clearCdArg();
	_CdArg.command = CDIF_SEEKDATA;
	_CdArg.pBuf = pBuf;
	_CdArg.startLBA = sector;
	_CdArg.endLBA   = sector + nSectors;
	_CdArg.bCallback = bCallback;

	SetEvent(_hEvent);

	return TRUE;
}

//Kitao�ǉ��BCDIF_SeekData��HDD�ŁB�g���b�N�f�[�^��CD�C���X�g�[�����Ă������ꍇ�Ƀn�[�h�f�B�X�N����f�[�^��ǂݍ��ށB
BOOL
CDIF_SeekDataHDD(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ���
	Sint32		track,		// �ǂݍ��ރg���b�N�i���o�[
	Uint32		addr,		// �ǂݍ��ރA�h���X�B�g���b�N(���t�@�C��)�̐擪��0x0000�Ƃ���B
	Uint32		nSectors,	// �ǂݏo���Z�N�^��
	BOOL		bCallback)
{
	waitDeviceBusy();
	_bDeviceBusy = TRUE;

	clearCdArg();
	_CdArg.command = CDIF_SEEKDATAHDD;
	_CdArg.pBuf = pBuf;
	_CdArg.track = track; //�g���b�N�i���o�[���i�[
	_CdArg.startLBA = addr; //�A�h���X���i�[
	_CdArg.endLBA   = nSectors; //�Z�N�^�[�����i�[
	_CdArg.bCallback = bCallback;

	SetEvent(_hEvent);

	return TRUE;
}

//Kitao�ǉ��B�n�[�h�I�ɉ��y�g���b�N�փV�[�N����B�X�e�[�g���[�h���Ɏg�p�B�V���O���X���b�h�œ���B
BOOL
CDIF_SeekCdda(
	Uint8	minStart,
	Uint8	secStart,
	Uint8	frmStart)
{
	BYTE		cdb[10];
	BOOL		bSuccess;

	waitDeviceBusy();
	if (APP_GetCueFile()) //Cue�t�@�C������N�����郂�[�h�̏ꍇ�Bv2.24
		return TRUE;
	_bDeviceBusy = TRUE;

	clearCdArg();
	_CdArg.startLBA = msf2lba(minStart, secStart, frmStart);

	cdb_seek(cdb, (CdArg*)&_CdArg);
	bSuccess = execute_command(cdb, (CdArg*)&_CdArg);
	if (bSuccess)
		_CdArg.bPlaying = FALSE;
	_bDeviceBusy = FALSE;

	return bSuccess;
}


/*-----------------------------------------------------------------------------
	[ReadSubChannelQ]
		�b�c�Đ����ɃT�u�p�`���l����ǂݏo���܂��B
-----------------------------------------------------------------------------*/
//�����ݔ�g�p
BOOL
CDIF_ReadSubChannelQ(
	Uint8*		pBuf,		// 10-byte buffer
	BOOL		bCallback)
{
	waitDeviceBusy();
	_bDeviceBusy = TRUE;

	clearCdArg();
	_CdArg.command  = CDIF_SUBQ;
	_CdArg.pBuf     = pBuf;
	_CdArg.bCallback = bCallback;

	SetEvent(_hEvent);

	return TRUE;
}


//Kitao�ǉ��BISO�C���X�g�[�����̃Z�N�^�[���[�h�����B
BOOL
CDIF_CDInstall(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Uint32		sector,		// �Z�N�^�ԍ� 
	Uint32		nSectors,	// �ǂݏo���Z�N�^�� 
	BOOL		bCallback)
{
	waitDeviceBusy();
	_bDeviceBusy = TRUE;

	clearCdArg();
	_CdArg.command = CDIF_INSTALL;
	_CdArg.pBuf = pBuf;
	_CdArg.startLBA = sector;
	_CdArg.endLBA   = sector + nSectors;
	_CdArg.bCallback = bCallback;

	SetEvent(_hEvent);

	return TRUE;
}

//Kitao�ǉ��BWAV�C���X�g�[�����̃Z�N�^�[���[�h�����B
BOOL
CDIF_CDInstallWav(
	Uint8*		pBuf,		// �ǂݍ��񂾃Z�N�^�f�[�^�̕ۑ��� 
	Sint32		track,		// �ǂݍ��ރg���b�N�i���o�[
	Uint32		sector,		// �Z�N�^�ԍ� 
	Uint32		nSectors,	// �ǂݏo���Z�N�^�� 
	BOOL		bCallback)
{
	waitDeviceBusy();
	_bDeviceBusy = TRUE;

	clearCdArg();
	_CdArg.command = CDIF_INSTALLWAV;
	_CdArg.pBuf = pBuf;
	_CdArg.track = track; //�g���b�N�i���o�[���i�[�Bv2.32�ǉ�
	_CdArg.startLBA = sector;
	_CdArg.endLBA   = sector + nSectors;
	_CdArg.bCallback = bCallback;

	SetEvent(_hEvent);

	return TRUE;
}


//Kitao�ǉ�
Sint32
CDIF_GetDriveLetters(
	int	n)
{
	return _DriveLetters[n];
}


//Kitao�ǉ�
Sint32
CDIF_GetDeviceInUse()
{
	return _DeviceInUse;
}

//Kitao�ǉ��Bv2.31
BOOL
CDIF_GetBadInstalled()
{
	return _bBadInstalled;
}
