/******************************************************************************
Ootake
�EPSG,ADPCM,CDDA���ꂼ���DirectSound�o�b�t�@��p�ӂ��邱�ƂŁA�e�T�E���h�̃_�C
  �i�~�b�N�����W���ő���Ɏ��A���������コ�����B
�E�o�b�t�@�̃u���b�N���S�ɕ����邱�ƂŁA���̒x���ƃp�\�R���ւ̕��ׂ��y������
  ���B
�E����̍Đ����ɂ̓E�F�C�g�����邱�ƂŁA����Đ��ɋN����m�C�Y�����������B
�E����͍Đ��T���v�����[�g��44.1KHz�Œ�Ƃ����B(CD-DA�Đ����̑��x�A�b�v�̂���)
�E�o�b�t�@�������ݎ��̃��������b�N�͋N�����ƏI�����̂P��̂ݍs���悤�ɂ��č���
  �������Bv1.02
�ECoInitialize��DirectSoundCreate()���g�����ꍇ�͕s�v�̂悤�Ȃ̂ŃJ�b�g�B����
  ��S_FALSE��Ԃ����Ƃŋ����I�����Ă�����������΁A�����悤�ɂȂ邩�������
  ���Bv1.04�BCOINIT_MULTITHREADED�����C���X���b�h�ōs���Ă��邱�Ƃ��l�����āA
  Audio�X���b�h�ł��O�̂���CoInitializeEx���s���悤�ɂ����Bv2.19
�E�N���e�B�J���Z�N�V�����͕K�v�Ȃ�(�������݂������ɍs����킯�ł͂Ȃ�)�悤��
  �̂ŁA�ȗ��������������Bv1.09

Copyright(C)2006-2013 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[AudioOut.c]
		�I�[�f�B�I�C���^�t�F�C�X�� DirectSound �𗘗p���Ď������܂��B

		Implement audio interface using DirectSound.

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
#define DIRECTSOUND_VERSION	0x0900	//DirectSound9�̃��C�u�����ŏ������s���B9�̓p���`�ƕi�̃o�����X�悵(SOFT�o�b�t�@���Ƃǂ̃Q�[��������ȏ�BHARD�o�b�t�@�ɂ���ƃp���`�ǂ������Q�[���ɂ���Ă͋����ɕi���Ȃ��Ȃ�P�[�X��)��CDDA�ŗ�(�O��II�Ȃǂ�SOFT�o�b�t�@�̂ق����������Y��)�B									//			 8�̓p���`������(�\���W���[�u���C�h�͍œK�������BHARD�o�b�t�@���Ƌ����ɕi���Ȃ�)�B7��SOFT�o�b�t�@���Ɖ��ɂ��p���`��������(���Ƀ\���W���[�u���C�h)��HARD�o�b�t�@���ƃp���`�ƕi�̃o�����X�ŗǁB

#define _WIN32_DCOM //v2.19�ǉ�

#include <stdio.h>
#include <dsound.h>
#include "AudioOut9.h"
#include "AudioOut.h"
#include "WinMain.h"
#include "Printf.h"
#include "App.h"

//Kitao�X�V�B�\�t�g��PSG,ADPCM,CDDA���~�b�N�X���ĉ���炵���ꍇ�A�_�C�i�~�b�N�����W��1/3�ɉ����Ȃ��Ă͂����Ȃ��̂ŉ������傫�������Ă��܂��B���̂��ߊeCh��p�̃o�b�t�@�Ŗ炷�悤�ɂ����B
static	LPDIRECTSOUND			_pDS	= NULL;
static	LPDIRECTSOUNDBUFFER		_pDSBP	= NULL; //Kitao�ǉ��B�v���C�}���p
static	LPDIRECTSOUNDBUFFER		_pDSB1	= NULL; //Kitao�ǉ��BPSG�Đ��p
static	LPDIRECTSOUNDBUFFER		_pDSB2	= NULL; //Kitao�ǉ��BADPCM�Đ��p
static	LPDIRECTSOUNDBUFFER		_pDSB3	= NULL; //Kitao�ǉ��BCDDA�Đ��p
static	LPVOID					_LpvPtr1; //Kitao�ǉ��BPSG�Đ��p�B�����ł����x�A�b�v���邽�ߔz��ɂ���PSG,ADPCM,CDDA�p���ꂼ��̕ϐ���p�ӁB
static	DWORD					_DwBytes1; 
static	LPVOID					_LpvPtr2; //Kitao�ǉ��BADPCM�Đ��p
static	DWORD					_DwBytes2; 
static	LPVOID					_LpvPtr3; //Kitao�ǉ��BCDDA�Đ��p
static	DWORD					_DwBytes3; 

static	LPDIRECTSOUNDNOTIFY		_LpDSN1; //Kitao�X�V�B���̍\���̂������[�X��Deinit���ɂ����B3ch�Ԃ�p�ӁB
static	LPDIRECTSOUNDNOTIFY		_LpDSN2; //			  v2.36�L�F3ch�Ɨ������ăo�b�t�@���Ď����邱�Ƃł��ꂼ��̉����̔����^�C�~���O����������ƍ����B
static	LPDIRECTSOUNDNOTIFY		_LpDSN3; //					   1ch�Ԃ�̃C�x���g�����ŊĎ����ς܂�����Ď��ȊO�̃`�����l���ł̓^�C�~���O�����܂����Ȃ��ĉ������������B�h���S���X���C���[�p�Y�`����ADPCM�h�������킩��₷���B
static	DSBPOSITIONNOTIFY		_PosNotify1[AOUT9_BUFFERRATE+1]; //Kitao�ǉ��BPSG�Đ��p
static	DSBPOSITIONNOTIFY		_PosNotify2[AOUT9_BUFFERRATE+1]; //Kitao�ǉ��BADPCM�Đ��p
static	DSBPOSITIONNOTIFY		_PosNotify3[AOUT9_BUFFERRATE+1]; //Kitao�ǉ��BCDDA�Đ��p
static	HANDLE					_hEvent1[AOUT9_BUFFERRATE+1]; //Kitao�ǉ��BPSG�Đ��p
static	HANDLE					_hEvent2[AOUT9_BUFFERRATE+1]; //Kitao�ǉ��BADPCM�Đ��p
static	HANDLE					_hEvent3[AOUT9_BUFFERRATE+1]; //Kitao�ǉ��BCDDA�Đ��p

static	DWORD				_dwBufSize;
static	HANDLE				_hThread;
static	DWORD				_dwThreadID;

static	volatile BOOL		_bPlay; //v2.05�X�V�Bvolatile�ɁB
static	volatile BOOL		_bThreadEnd; //Kitao�ǉ��B�X���b�h���I���������Ƃ�TRUE�ɂ��Ēm�点��B
static	volatile BOOL		_bThreadStarted; //v2.71�ǉ��B�X���b�h���m���ɓ����o������TRUE�ɁB

static	Sint16*				_pAudioBuf1 = NULL; //Kitao�ǉ��BOutput����PSG�p
static	Sint16*				_pAudioBuf2 = NULL; //Kitao�ǉ��BOutput����ADPCM�p
static	Sint16*				_pAudioBuf3 = NULL; //Kitao�ǉ��BOutput����CDDA�p
static 	void				(*_pCallBack)(int ch, Sint16* pBuf, Sint32 nSamples) = NULL; //Kitao�X�V�Bch(�`�����l���i���o�[)��ǉ�

static	BOOL				_bAudioInit = FALSE;


//v2.36�X�V
static void
buffer_lock_1()
{
	HRESULT		hr;

	hr = _pDSB1->Lock(0, _dwBufSize, &_LpvPtr1, &_DwBytes1, NULL, NULL, 0); //�������ݐ�̃|�C���^�𓾂�Bv2.36�X�V�B��2�u���b�N�̎w���NULL�ɂ��邱�ƂŁA��1�u���b�N�݂̂Ń��b�N�ł���B
	if (hr ==DSERR_BUFFERLOST) //���s�����ꍇ���X�g�A���Ă��������x���݂�
	{
		_pDSB1->Restore();
		_pDSB1->Lock(0, _dwBufSize, &_LpvPtr1, &_DwBytes1, NULL, NULL, 0);
	}
}
static void
buffer_lock_2()
{
	HRESULT		hr;

	hr = _pDSB2->Lock(0, _dwBufSize, &_LpvPtr2, &_DwBytes2, NULL, NULL, 0);
	if (hr ==DSERR_BUFFERLOST)
	{
		_pDSB2->Restore();
		_pDSB2->Lock(0, _dwBufSize, &_LpvPtr2, &_DwBytes2, NULL, NULL, 0);
	}
}
static void
buffer_lock_3()
{
	HRESULT		hr;

	hr = _pDSB3->Lock(0, _dwBufSize, &_LpvPtr3, &_DwBytes3, NULL, NULL, 0);
	if (hr ==DSERR_BUFFERLOST)
	{
		_pDSB3->Restore();
		_pDSB3->Lock(0, _dwBufSize, &_LpvPtr3, &_DwBytes3, NULL, NULL, 0);
	}
}
static void
buffer_unlock_1()
{
	_pDSB1->Unlock(_LpvPtr1, _DwBytes1, NULL, NULL);
}
static void
buffer_unlock_2()
{
	_pDSB2->Unlock(_LpvPtr2, _DwBytes2, NULL, NULL);
}
static void
buffer_unlock_3()
{
	_pDSB3->Unlock(_LpvPtr3, _DwBytes3, NULL, NULL);
}

/*-----------------------------------------------------------------------------
	[write_streaming_buffer]
		DirectSoundBuffer �ɏo�͂��鉹���f�[�^���������݂܂��B
-----------------------------------------------------------------------------*/
//Kitao�X�V�Bv1.02�Ń��b�N�ƃA�����b�N�������ł��Ȃ��悤�ɂ������APC���ɂ���Ă͂��������̃A�����b�N�����Ȃ������Đ�����Ȃ��h���C�o������炵��(MSDN�k�B���[�U�[�̕�������񍐂�������)�̂ŁA�����Ń��b�N�ƃA�����b�N������Bv2.36
//			 _pAudioBuf��p�~���A����DirectSound�̃o�b�t�@�֏������ނ悤�ɂ��č������Bv2.36

//Kitao�X�V�B������PSG��p�B
static inline void
write_streaming_buffer_1(
	DWORD	dwOffset)
{
	buffer_lock_1();
	if (_bPlay) //Kitao�ǉ��B����Đ����̓o�b�t�@�S�̂Ԃ�̎��Ԃ��E�F�C�g����iPSG�L���[�ɒl���p�ӂ���鎞�Ԃ�҂j�悤�ɂ����B
		_pCallBack(1, (Sint16*)((DWORD)_LpvPtr1 + dwOffset), _DwBytes1/4); //Kitao�X�V�B1ch�ڂ����� ��/4=�u1�T���v����4�o�C�g�v�̈Ӗ�
	else
		ZeroMemory((LPVOID)((DWORD)_LpvPtr1 + dwOffset), _DwBytes1);
	buffer_unlock_1();
}

//Kitao�ǉ��B������ADPCM��p�B
static inline void
write_streaming_buffer_2(
	DWORD	dwOffset)
{
	buffer_lock_2();
	if (_bPlay)
		_pCallBack(2, (Sint16*)((DWORD)_LpvPtr2 + dwOffset), _DwBytes2/4);
	else
		ZeroMemory((LPVOID)((DWORD)_LpvPtr2 + dwOffset), _DwBytes2);
	buffer_unlock_2();
}

//Kitao�X�V�B������CDDA��p�B
static inline void
write_streaming_buffer_3(
	DWORD	dwOffset)
{
	buffer_lock_3();
	if (_bPlay)
		_pCallBack(3, (Sint16*)((DWORD)_LpvPtr3 + dwOffset), _DwBytes3/4);
	else
		ZeroMemory((LPVOID)((DWORD)_LpvPtr3 + dwOffset), _DwBytes3);
	buffer_unlock_3();
}


/*-----------------------------------------------------------------------------
	[playback_thread]
		�T�E���h�o�b�t�@�̍X�V���s�Ȃ��X���b�h�ł��B 
-----------------------------------------------------------------------------*/
static DWORD WINAPI
playback_thread(
	LPVOID	param)
{
	DWORD		n;
	DWORD		dwOffset = 0;

	CoInitializeEx(NULL, COINIT_MULTITHREADED); //v2.19�ǉ��B���ꂼ��̃X���b�h��CoInitializeEx���Ȃ��ƈ��肵�Ȃ��������邩������Ȃ��B(COINIT_MULTITHREADED�̏ꍇ�ACOM���g���X���b�h���ꂼ���CoInitializeEx���邱�Ƃ�MS������)

	while (!_bThreadEnd)
	{
		//PSG�`�����l���� notification ��҂� 
		n = WaitForMultipleObjects(AOUT9_BUFFERRATE+1, _hEvent1, FALSE, INFINITE);
		if (n != WAIT_OBJECT_0 + 0) //stop����Ȃ����
		{
			//�o�b�t�@�̕���_�i�擪�܂ށj��ʒm����C�x���g�����������ꍇ�̏��� 
			if (n == AOUT9_BUFFERRATE)
				dwOffset = 0;
			else
				dwOffset = n * _dwBufSize;
			if (AOUT_GetfpOutputWAV() != NULL) //Kiao�ǉ��BWAV�t�@�C���֏o�͎�
			{
				if (_bPlay)
					_pCallBack(1, _pAudioBuf1, _dwBufSize/4);
				else
					ZeroMemory(_pAudioBuf1, _dwBufSize);
				buffer_lock_1();
				CopyMemory((LPVOID)((DWORD)_LpvPtr1 + dwOffset), (LPBYTE)_pAudioBuf1, _DwBytes1);
				buffer_unlock_1();
			}
			else //�ʏ�
				write_streaming_buffer_1(dwOffset); //PSG�`�����l��
		}

		if (APP_GetCDGame()) //Hu�J�[�h�Q�[���̏������y������Bv2.36�ǉ�
		{
			//ADPCM�`�����l���� notification ��҂� 
			n = WaitForMultipleObjects(AOUT9_BUFFERRATE+1, _hEvent2, FALSE, INFINITE);
			if (n != WAIT_OBJECT_0 + 0) //stop����Ȃ����
			{
				//�o�b�t�@�̕���_�i�擪�܂ށj��ʒm����C�x���g�����������ꍇ�̏��� 
				if (n == AOUT9_BUFFERRATE)
					dwOffset = 0;
				else
					dwOffset = n * _dwBufSize;
				if (AOUT_GetfpOutputWAV() != NULL) //Kiao�ǉ��BWAV�t�@�C���֏o�͎�
				{
					if (_bPlay)
						_pCallBack(2, _pAudioBuf2, _dwBufSize/4);
					else
						ZeroMemory(_pAudioBuf2, _dwBufSize);
					buffer_lock_2();
					CopyMemory((LPVOID)((DWORD)_LpvPtr2 + dwOffset), (LPBYTE)_pAudioBuf2, _DwBytes2);
					buffer_unlock_2();
				}
				else //�ʏ�
					write_streaming_buffer_2(dwOffset); //ADPCM�`�����l��
			}

			//CDDA�`�����l���� notification ��҂� 
			n = WaitForMultipleObjects(AOUT9_BUFFERRATE+1, _hEvent3, FALSE, INFINITE);
			if (n != WAIT_OBJECT_0 + 0) //stop����Ȃ����
			{
				//�o�b�t�@�̕���_�i�擪�܂ށj��ʒm����C�x���g�����������ꍇ�̏��� 
				if (n == AOUT9_BUFFERRATE)
					dwOffset = 0;
				else
					dwOffset = n * _dwBufSize;
				if (AOUT_GetfpOutputWAV() != NULL) //Kiao�ǉ��BWAV�t�@�C���֏o�͎�
				{
					if (_bPlay)
						_pCallBack(3, _pAudioBuf3, _dwBufSize/4);
					else
						ZeroMemory(_pAudioBuf3, _dwBufSize);
					buffer_lock_3();
					CopyMemory((LPVOID)((DWORD)_LpvPtr3 + dwOffset), (LPBYTE)_pAudioBuf3, _DwBytes3);
					buffer_unlock_3();
				}
				else //�ʏ�
					write_streaming_buffer_3(dwOffset); //CDDA�`�����l��
			}
		}

		//Kitao�ǉ��BWAV�t�@�C���֏o�͏���
		if (AOUT_GetfpOutputWAV() != NULL)
			AOUT_OutputWavExecute(_dwBufSize, _pAudioBuf1, _pAudioBuf2, _pAudioBuf3);

		_bThreadStarted = TRUE; //v2.71�ǉ��BAudioOut�p�X���b�h���m���ɓ����o�������}�B
	}

	CoUninitialize(); //v2.19�ǉ�

	ExitThread(TRUE);
}


/*-----------------------------------------------------------------------------
	Deinit DirectSound

-----------------------------------------------------------------------------*/
#define SAFE_RELEASE(p)		{ if (p) {(p)->Release(); (p) = NULL;} }
static BOOL
d_deinit() 	//Kitao�X�V�B3ch�Ԃ�̃��\�[�X���J��
{
	int		i; //Kitao�ǉ�

	if (!_bAudioInit)
		return FALSE;

	_bPlay = FALSE;

	if (_hThread)
	{
		// �X���b�h�̏I����҂� 
		for (i = 0; i<AOUT9_BUFFERRATE; i++) //�X�g���[�~���O�o�b�t�@�𖳉��Ŗ��߂�
		{
			write_streaming_buffer_1(i*_dwBufSize);
			write_streaming_buffer_2(i*_dwBufSize);
			write_streaming_buffer_3(i*_dwBufSize);
		}
		_pDSB1->Play(0, 0, DSBPLAY_LOOPING);//�����Đ����Ă��Ȃ������ꍇ�́A_bThreadEnd���󂯕t���Ȃ��̂ł����ōĐ��B
		_pDSB2->Play(0, 0, DSBPLAY_LOOPING);
		_pDSB3->Play(0, 0, DSBPLAY_LOOPING);
		_bThreadEnd = TRUE;
		WaitForSingleObject(_hThread, INFINITE);
		_pDSB1->Stop();
		_pDSB2->Stop();
		_pDSB3->Stop();

		CloseHandle(_hThread);
		_hThread = NULL;
	}

	for (i = 0; i<=AOUT9_BUFFERRATE; i++)
	{
		if (_hEvent1[i]) CloseHandle(_hEvent1[i]);
		if (_hEvent2[i]) CloseHandle(_hEvent2[i]);
		if (_hEvent3[i]) CloseHandle(_hEvent3[i]);
		_hEvent1[i] = NULL;
		_hEvent2[i] = NULL;
		_hEvent3[i] = NULL;
	}

	SAFE_RELEASE(_LpDSN1);//Kitao�X�V
	SAFE_RELEASE(_LpDSN2);
	SAFE_RELEASE(_LpDSN3);

	SAFE_RELEASE(_pDSB1);
	SAFE_RELEASE(_pDSB2);
	SAFE_RELEASE(_pDSB3);
	SAFE_RELEASE(_pDSBP);
	SAFE_RELEASE(_pDS);

	GlobalFree(_pAudioBuf1);
	GlobalFree(_pAudioBuf2);
	GlobalFree(_pAudioBuf3);
	_pAudioBuf1 = NULL;
	_pAudioBuf2 = NULL;
	_pAudioBuf3 = NULL;
	AOUT_DeinitWavMixBuf(); //WAV�o�͗p�̃o�b�t�@���J��
	_dwBufSize = 0;

	return TRUE;
}


/*-----------------------------------------------------------------------------
	Initialize DirectSound

-----------------------------------------------------------------------------*/
static BOOL
d_init(
	Sint32	soundType, //Kitao�ǉ��B1�c�ʏ�(�\�t�g�o�b�t�@���~�L�V���O�BCPU�ɂ��~�L�V���O�ɂȂ�D���������̉����ɂȂ�)�B2�c�ÓI�o�b�t�@���\�t�g�~�L�V���O(�����炭�Â����������A�����W�������������BDirectSound�̃o�[�W�����ɂ���Ă̓p���`����������ꍇ��)�B
	HWND	hWnd,
	WORD	nChannels,
	WORD	nSamplesPerSec,
	WORD	wBitsPerSample,
	DWORD	dwBufSize)			// in bytes
{
	int 					i;//Kitao�ǉ�
	DSBUFFERDESC			dsbd;
	WAVEFORMATEX			waveFormat;//Kitao�X�V

	// Create IDirectSound 
	if (FAILED(DirectSoundCreate(NULL, &_pDS, NULL)))
	{
		MessageBox(WINMAIN_GetHwnd(), "ERROR: DIRECTSOUND::DirectSoundCreate() failed.    ", "Ootake", MB_OK); //Kitao�ǉ�
		return FALSE;
	}

	/*
	** Set coop level to DSSCL_PRIORITY
	**
	** �v���C�}���o�b�t�@�̃t�H�[�}�b�g��ݒ�ł���悤�A�v���C�}���������x��
	** ��ݒ肷��B�f�t�H���g�̃t�H�[�}�b�g�ɕύX�������Ȃ��ꍇ�A���͂�
	** �t�H�[�}�b�g�ɂ������Ȃ��A�o�͂� 8 �r�b�g�A22 kHz �t�H�[�}�b�g�ɂȂ�B
	** IDirectSoundBuffer::SetFormat �̌Ăяo�������s���Ă����͂Ȃ��_��
	** ���ӂ���BDirectSound �͒P���ɁA���p�ł��钆�ōł��߂��t�H�[�}�b�g��
	** �ݒ肷��B
	*/
	if (FAILED(_pDS->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
	{
		MessageBox(WINMAIN_GetHwnd(), "ERROR: DIRECTSOUND::SetCooperativeLevel() failed.    ", "Ootake", MB_OK); //Kitao�X�V
		return FALSE;
	}

	/*
	** Get the primary buffer.
	**
	** �v���C�}���o�b�t�@�̃t�H�[�}�b�g��ݒ肷��ɂ́A�ŏ���
	** DSBUFFERDESC �\���̂ł��̃t�H�[�}�b�g���L�q���A���ɂ��̋L�q��
	** IDirectSound::CreateSoundBuffer ���\�b�h�ɓn���B 
	*/
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize			= sizeof(DSBUFFERDESC);
	dsbd.dwFlags		= DSBCAPS_PRIMARYBUFFER;
	dsbd.dwBufferBytes	= 0;
	dsbd.lpwfxFormat	= NULL;

	if (FAILED(_pDS->CreateSoundBuffer(&dsbd, &_pDSBP, NULL))) //Kitao�X�V�Bv1.03�B�v���C�}���͍쐬�����シ���ɂ͊J�����Ȃ��悤�ɂ����B
	{
		MessageBox(WINMAIN_GetHwnd(), "ERROR: DIRECTSOUND::CreateSoundBuffer() failed.    ", "Ootake", MB_OK); //Kitao�X�V
		return FALSE;
	}

	/*
	** Set primary buffer to desired format.
	**
	** �v���C�}���o�b�t�@�I�u�W�F�N�g���擾������ŁA��]�̃E�F�[�u
	** �t�H�[�}�b�g���L�q���A���̋L�q�� IDirectSoundBuffer::SetFormat
	** ���\�b�h�ɓn���B
	*/
	ZeroMemory(&waveFormat, sizeof(WAVEFORMATEX));
	waveFormat.wFormatTag		= WAVE_FORMAT_PCM;
	waveFormat.nChannels		= nChannels; 
	waveFormat.wBitsPerSample	= wBitsPerSample;
	waveFormat.nBlockAlign		= waveFormat.nChannels * waveFormat.wBitsPerSample / 8;
	waveFormat.nSamplesPerSec	= nSamplesPerSec;
	waveFormat.nAvgBytesPerSec	= waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

	if (FAILED(_pDSBP->SetFormat(&waveFormat)))
	{
		MessageBox(WINMAIN_GetHwnd(), "ERROR: DIRECTSOUNDBUFFER::SetFormat() failed.    ", "Ootake", MB_OK); //Kitao�X�V
//		return FALSE;
	}

	// DSBUFFERDESC �\���̂�ݒ肷��B
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize	= sizeof(DSBUFFERDESC);
	switch (soundType) //Kitao�X�V�B�o�b�t�@�ݒ��I���ł���悤�ɂ����Bv1.03�Bv1.31����Q���ɍi�����B
	{
		case 2:
			//Kitao�X�V�B�o�b�t�@��DSBCAPS_STATIC�Ńn�[�h�������㈵���ɁB���̉𑜓x�͊m���ɏオ��Bv2.70���炱������f�t�H���g�ɁBDirectSound7�Ƒ����������B
			dsbd.dwFlags = DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GLOBALFOCUS | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE;
			break;
		default: //=1
			//Kitao�X�V�B�O���[�o���t�H�[�J�X�ɂ����B�\�t�g�~�L�V���O�B�D���������B
			dsbd.dwFlags = DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCSOFTWARE;
			break;
	}
	dsbd.dwBufferBytes	= dwBufSize * AOUT9_BUFFERRATE; //Kitao�X�V�BAOUT9_BUFFERRATE�{�Ԃ�p�ӂ���B
	dsbd.lpwfxFormat	= &waveFormat;

	// �Z�J���_���o�b�t�@���쐬���� Kitao�X�V�B3ch�Ԃ�쐬�B
	if (FAILED(_pDS->CreateSoundBuffer(&dsbd, &_pDSB1, NULL)))	
	{
		MessageBox(WINMAIN_GetHwnd(), "ERROR: AudioOut: Failed creating secondary buffer1.    ", "Ootake", MB_OK); //Kitao�X�V
		return FALSE;
	}
	if (FAILED(_pDS->CreateSoundBuffer(&dsbd, &_pDSB2, NULL)))	
	{
		MessageBox(WINMAIN_GetHwnd(), "ERROR: AudioOut: Failed creating secondary buffer2.    ", "Ootake", MB_OK); //Kitao�X�V
		return FALSE;
	}
	if (FAILED(_pDS->CreateSoundBuffer(&dsbd, &_pDSB3, NULL)))	
	{
		MessageBox(WINMAIN_GetHwnd(), "ERROR: AudioOut: Failed creating secondary buffer3.    ", "Ootake", MB_OK); //Kitao�X�V
		return FALSE;
	}

	//Kitao�X�V�B3ch�Ԃ�p�ӁB[0]��stop notification�Ƃ��A[1]�`[AOUT9_BUFFERRATE]�܂ł𕪊�_�C�x���g�Ƃ����B
	for (i =0; i<=AOUT9_BUFFERRATE; i++)
	{
		_hEvent1[i] = CreateEvent(NULL, FALSE, FALSE, NULL); //v2.36�X�V�B�������Z�b�g����悤�ɂ����B
		_hEvent2[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		_hEvent3[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
	}

	// DIRECTSOUNDNOTIFY �̃C���^�t�F�C�X�𓾂� 
	if (FAILED(_pDSB1->QueryInterface(IID_IDirectSoundNotify, (void**)&_LpDSN1)))	return FALSE;
	if (FAILED(_pDSB2->QueryInterface(IID_IDirectSoundNotify, (void**)&_LpDSN2)))	return FALSE;
	if (FAILED(_pDSB3->QueryInterface(IID_IDirectSoundNotify, (void**)&_LpDSN3)))	return FALSE;

	// Kitao�X�V�B�Đ�����~���ꂽ�Ƃ���[0]�ŏ������邱�Ƃɂ��āA[1]�`[AOUT9_BUFFERRATE]�Ԃ�܂ł����̕���_�ʒm�p�Ƃ����B
	// �Đ�����~���ꂽ�Ƃ��� notification �p 
	_PosNotify1[0].dwOffset = DSBPN_OFFSETSTOP;
	_PosNotify1[0].hEventNotify = _hEvent1[0];
	_PosNotify2[0].dwOffset = DSBPN_OFFSETSTOP;
	_PosNotify2[0].hEventNotify = _hEvent2[0];
	_PosNotify3[0].dwOffset = DSBPN_OFFSETSTOP;
	_PosNotify3[0].hEventNotify = _hEvent3[0];
	// Kitao�X�V�B�o�b�t�@�̕���_(�擪�܂�)�ʒm�p 
	for (i = 1; i<=AOUT9_BUFFERRATE; i++)
	{
		//_PosNotify1[i].dwOffset = (i-1)*dwBufSize;
		//v2.36�X�V�B�e�o�b�t�@�̐؂�ڂ�����O(�����̈ʒu)�ŃC�x���g���N�����悤�ɂ����B�������x���h���C�o�ł�����Ȃ�m���ŁA�����̈ʒu�Ȃ瑁������S�z���Ȃ��悤���B
		if (i == 1)
		{
			_PosNotify1[i].dwOffset = AOUT9_BUFFERRATE*dwBufSize - dwBufSize/2;
			_PosNotify2[i].dwOffset = AOUT9_BUFFERRATE*dwBufSize - dwBufSize/2;
			_PosNotify3[i].dwOffset = AOUT9_BUFFERRATE*dwBufSize - dwBufSize/2;
		}
		else
		{
			_PosNotify1[i].dwOffset = (i-1)*dwBufSize - dwBufSize/2;
			_PosNotify2[i].dwOffset = (i-1)*dwBufSize - dwBufSize/2;
			_PosNotify3[i].dwOffset = (i-1)*dwBufSize - dwBufSize/2;
		}
		_PosNotify1[i].hEventNotify = _hEvent1[i];
		_PosNotify2[i].hEventNotify = _hEvent2[i];
		_PosNotify3[i].hEventNotify = _hEvent3[i];
	}

	// notification ��ݒ肷�� 
	if (FAILED(_LpDSN1->SetNotificationPositions(AOUT9_BUFFERRATE+1, _PosNotify1)))	return FALSE;
	if (FAILED(_LpDSN2->SetNotificationPositions(AOUT9_BUFFERRATE+1, _PosNotify2)))	return FALSE;
	if (FAILED(_LpDSN3->SetNotificationPositions(AOUT9_BUFFERRATE+1, _PosNotify3)))	return FALSE;

	// �I�[�f�B�I�o�b�t�@���m�ۂ��� 
	_pAudioBuf1 = (Sint16*)GlobalAlloc(GMEM_FIXED, dwBufSize);
	_pAudioBuf2 = (Sint16*)GlobalAlloc(GMEM_FIXED, dwBufSize);
	_pAudioBuf3 = (Sint16*)GlobalAlloc(GMEM_FIXED, dwBufSize);
	if (_pAudioBuf1 == NULL)
	{
		d_deinit();
		return FALSE;
	}

	//WAV�o�͗p�̃o�b�t�@���m�ۂ���
	AOUT_InitWavMixBuf(dwBufSize);

	_dwBufSize = dwBufSize;
	_bPlay = FALSE;

	//�X���b�h���J�n����O�ɃI�[�f�B�I�����������t���O�����Ă�B
	//[2004.04.28] fixed
	_bAudioInit = TRUE;

	//�X���b�h���쐬�����s���� 
	_bThreadEnd = FALSE;
	_bThreadStarted = FALSE; //v2.71
	_hThread = CreateThread(NULL, 0, playback_thread, NULL, 0, &_dwThreadID);
	if (_hThread == NULL)
	{
		d_deinit();
		_bAudioInit = FALSE;
		return FALSE;
	}

	//�X���b�h�̗D�揇�ʂ��グ��Bv2.36�ǉ��B���ʂ������������߃J�b�g
	//OpenThread(THREAD_SET_INFORMATION, TRUE, _dwThreadID);
	//if (SetThreadPriority(_hThread, THREAD_PRIORITY_HIGHEST) == NULL)
	//	return FALSE;
		
	return TRUE;
}


/*-----------------------------------------------------------------------------
	[Init]
		
-----------------------------------------------------------------------------*/
BOOL
AOUT9_Init(
	Sint32		soundType,	//Kitao�ǉ�
	Uint32		bufSize,	// in samples 
	Uint32		sampleRate,
	void		(*pCallBack)(int ch, Sint16* pBuf, Sint32 nSamples)) //Kitao�X�V�Bch(�`�����l���i���o�[)��ǉ�
{
	if (d_init(soundType, WINMAIN_GetHwnd(), 2, (WORD)sampleRate, 16, (DWORD)bufSize*2*2))
	{
		_pCallBack = pCallBack;
		return TRUE;
	}

	return FALSE;
}


/*-----------------------------------------------------------------------------
	[Play]
		
-----------------------------------------------------------------------------*/
void
AOUT9_Play(
	BOOL	bPlay)
{
	if (!_bAudioInit)
		return;

	_bPlay = bPlay;
	if (_bPlay)
	{
		_pDSB1->Play(0, 0, DSBPLAY_LOOPING);
		_pDSB2->Play(0, 0, DSBPLAY_LOOPING);
		_pDSB3->Play(0, 0, DSBPLAY_LOOPING);
	}
/*  //�����ŉ���Stop����ƃo�b�t�@�Ɏc�����������̃Q�[�����J���Ƃ��Ȃǂɏo�Ă��܂��̂�Stop�����ɕ��u�ōs���B��XAudio2�̏ꍇ�A�t�Ɏ~�߂Ȃ��ƕ��׍����Ŋ��ɂ��듮��B
	else
	{	//v2.70�ǉ�
		_pDSB1->Stop();
		_pDSB2->Stop();
		_pDSB3->Stop();
	}
*/
}


/*-----------------------------------------------------------------------------
	[Deinit]
		
-----------------------------------------------------------------------------*/
void
AOUT9_Deinit()
{
	if (!_bAudioInit)
		return;

	d_deinit();

	_bAudioInit = FALSE;
}


//Kitao�ǉ�
void
AOUT9_SetPlayStart()
{
	int i;

	if (!_bAudioInit)
		return;

	// WAV�t�@�C���o�͗pBuffer�ɖ������������� 
	ZeroMemory(_pAudioBuf1, _dwBufSize);
	ZeroMemory(_pAudioBuf2, _dwBufSize);
	ZeroMemory(_pAudioBuf3, _dwBufSize);

	// �X�g���[�~���O�o�b�t�@�𖳉��Ŗ��߂�
	for (i = 0; i<AOUT9_BUFFERRATE; i++) //Kitao�ǉ�
	{
		write_streaming_buffer_1(i*_dwBufSize);
		write_streaming_buffer_2(i*_dwBufSize);
		write_streaming_buffer_3(i*_dwBufSize);
	}

	// �Đ��ʒu��0�ɂ���
	_pDSB1->SetCurrentPosition(0);
	_pDSB2->SetCurrentPosition(0);
	_pDSB3->SetCurrentPosition(0);
}

//Kitao�ǉ�
BOOL
AOUT9_GetPlay()
{
	return _bPlay;
}

//Kitao�ǉ�
BOOL
AOUT9_GetThreadStarted()
{
	if (!_bAudioInit)
		return TRUE;
	else
		return _bThreadStarted;
}

