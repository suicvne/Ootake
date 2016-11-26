/******************************************************************************
Ootake
�EPSG,ADPCM,CDDA���ꂼ���DirectSound�o�b�t�@��p�ӂ��邱�ƂŁA�e�T�E���h�̃_�C
  �i�~�b�N�����W���ő���Ɏ��A���������コ�����B
�E�o�b�t�@�̃u���b�N���S�ɕ����邱�ƂŁA���̒x���ƃp�\�R���ւ̕��ׂ��y������
  ���B
�E�}�X�^�[�{�����[���̒�����100%����Ƃ��i��݂̂Ƃ����B(��������)
�E����̍Đ����ɂ̓E�F�C�g�����邱�ƂŁA����Đ��ɋN����m�C�Y�����������B
�E����͍Đ��T���v�����[�g��44.1KHz�Œ�Ƃ����B(CD-DA�Đ����̑��x�A�b�v�̂���)
�E�N���e�B�J���Z�N�V�����͕K�v�Ȃ�(�������݂������ɍs����킯�ł͂Ȃ�)�悤��
  �̂ŁA�ȗ��������������Bv1.09

Copyright(C)2006-2010 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[APU.c]
		�`�o�t���������܂��B

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
#include <math.h>
#include "APU.h"
#include "AudioOut.h"
#include "PSG.h"
#include "ADPCM.h"
#include "CDROM.h"
#include "App.h"
#include "MainBoard.h"
#include "PRINTF.h"


static Sint32			_SampleRate = 44100;	// [Hz]
static Sint32			_BufSize = 1664; //Kitao�X�V�B���̒l��DirectX�ň�x�ɍĐ�(�]��)����T�C�Y�B���S���y�����邽�߁��x�������Ȃ����邽�߂ɁA���̑傫����AOUT_BUFFERRATE(����4�ɂ���)�{�̃o�b�t�@��p�ӂ���DirectX���ɂ��̕���������n�������ɂ���B�P��[sample]
static Sint32			_BufSizeAll = 1664*AOUT_BUFFERRATE; //Kitao�ǉ��B�S�Ẵu���b�N�̃o�b�t�@�e�ʁB�������̂��ߗp�ӁBv0.92�B
static Sint32			_nSamplesPerFrame;

static Sint16*			_pMixBuf1 = NULL; //Kitao�X�V�BPSG��p�o�b�t�@�BPSG,ADPCM,CDDA���ꂼ��Ƀo�b�t�@��p�ӂ��ă_�C�i�~�b�N�����W���ő���Ɏ��B(�����啝�A�b�v)
static Sint16*			_pMixBuf2 = NULL; //Kitao�X�V�BADPCM��p�o�b�t�@
static Sint16*			_pMixBuf3 = NULL; //Kitao�X�V�BCDDA��p�o�b�t�@
static volatile Sint32	_MixBufPos1; //Kitao�X�V�BPSG�BPSG�̏ꍇ�A�^�C�~���O����邽�߂Ƀ��C���X���b�h������Q�Ƃ���̂�volatile�ɁB
static volatile Sint32	_MixBufPos2; //Kitao�X�V�BADPCM�BADPCM���ׂ₩�ȃ^�C�~���O��K�v�Ƃ���\�t�g������(�h���S���X���C���[�p�Y�`���̃h�����Ȃ�)�̂ŁAPSG�Ɠ��l�̏���������Bv2.18
static Sint32			_MixBufPos3; //Kitao�X�V�BCDDA
static volatile double	_MixBufEndPos1; //Kitao�X�V�BPSG
static volatile double	_MixBufEndPos2; //Kitao�X�V�BADPCM
static Sint32			_MixBufEndPos3; //Kitao�X�V�BCDDA�BCDDA�ׂ͍����^�C�~���O�����K�v�������̂Ő������Z��OK�Bv2.29�X�V
static volatile Sint32	_NextPlayPos1; //Kitao�ǉ��BPSG�p�B���ɍĐ�(DirectSound�ɓ]��)����ʒu�B0��BufSize*n�B
static volatile Sint32	_NextPlayPos2; //Kitao�ǉ��BADPCM�p
static Sint32			_NextPlayPos3; //Kitao�ǉ��BCDDA�p
static volatile BOOL	_bPosStop1 = FALSE; //Kitao�ǉ��B�o�b�t�@�����t�̂Ƃ�TRUE�ɁB
static volatile BOOL	_bPosStop2 = FALSE; //Kitao�ǉ��B�o�b�t�@�����t�̂Ƃ�TRUE�ɁB

static Uint32		_ClockCount;
static Sint32		_Volume; // APU volume (0-65535) Kitao�X�V�B�����D��̂��߂����ł̓{�����[���_�E���݂̂��s���B

static HANDLE	_hMutex; //v2.18
static volatile BOOL	_bApuBusy = FALSE; //Kitao�ǉ�


/*-----------------------------------------------------------------------------
	[callback_mixer]
		���̊֐��� AudioInterface �̃R�[���o�b�N�Ƃ��ēo�^�����B
	���̊֐����Ăяo����邽�тɁA���ꂼ��̃`���l���̏o�͂�
	Sint16 �ɕϊ����� pDst �ɏ����o���B�`���l���̏o�́i�T���v���j
	������Ȃ��ꍇ�́A���̕�������[����B
-----------------------------------------------------------------------------*/
//Kitao�ǋL�F������AudioOut.c�̉��Đ���p�X���b�h��Ŏ��s�����B
static void
callback_mixer(
	int 			ch,					// Kitao�ǉ��B1=PSG, 2=ADPCM, 3=CDDA
	Sint16*			pDst,				// �o�͐�o�b�t�@ //Kitao�X�V�B�e�`�����l����p�o�b�t�@�ɕ���������Sint16�ɁB
	Sint32			nSamples)			// �����o���T���v���� 
{
	Sint32			n, n2;
	Sint32			a;
	Sint16*			pSrc; //Kitao�X�V�BSint16�ɁB
	int				i;

	_bApuBusy = TRUE;

	WaitForSingleObject(_hMutex, INFINITE); //���C���X���b�h����������ɋ��L�ϐ���������������\��������̂ŁA�r�������Bv2.18
	switch (ch)
	{
		case 1: //PSG
			pSrc = _pMixBuf1 + (_NextPlayPos1 << 1);
			
			//Kitao�X�V�BMixBuf��AOUT_BUFFERRATE�{���悤�ɂ����Ba���o�b�t�@�ɗ��܂��Ă���T���v����
			if ((!_bPosStop1)&&(_MixBufPos1 >= _NextPlayPos1))
				a = _MixBufPos1 - _NextPlayPos1;
			else
				a = _BufSizeAll - _NextPlayPos1 + _MixBufPos1;
			
			if (a < nSamples) //���܂��Ă���T���v����������Ȃ��ꍇ
			{
				// ����Ȃ������[����B
				n = nSamples - a;
				PSG_Mix(_pMixBuf1+(_MixBufPos1 << 1), n);
				_MixBufPos1 += n;
				if (_MixBufPos1 >= _BufSizeAll)
					_MixBufPos1 -= _BufSizeAll;
				_MixBufEndPos1 = _MixBufPos1;
			}
			break;
			
		case 2: //ADPCM
			pSrc = _pMixBuf2 + (_NextPlayPos2 << 1);
			
			//Kitao�X�V�BMixBuf��AOUT_BUFFERRATE�{���悤�ɂ����Ba���o�b�t�@�ɗ��܂��Ă���T���v����
			if ((!_bPosStop2)&&(_MixBufPos2 >= _NextPlayPos2))
				a = _MixBufPos2 - _NextPlayPos2;
			else
				a = _BufSizeAll - _NextPlayPos2 + _MixBufPos2;
			
			if (a < nSamples) //���܂��Ă���T���v����������Ȃ��ꍇ
			{
				// ����Ȃ������[����B
				n = nSamples - a;
				ADPCM_Mix(_pMixBuf2+(_MixBufPos2 << 1), n);
				_MixBufPos2 += n;
				if (_MixBufPos2 >= _BufSizeAll)
					_MixBufPos2 -= _BufSizeAll;
				_MixBufEndPos2 = _MixBufPos2;
			}
			break;
		
		case 3: //CDDA
			pSrc = _pMixBuf3 + (_NextPlayPos3 << 1);
			
			//Kitao�X�V�BMixBuf��AOUT_BUFFERRATE�{���悤�ɂ����Ba���o�b�t�@�ɗ��܂��Ă���T���v����
			if (_MixBufPos3 >= _NextPlayPos3)
				a = _MixBufPos3 - _NextPlayPos3;
			else
				a = _BufSizeAll - _NextPlayPos3 + _MixBufPos3;
			
			if (a < nSamples) //���܂��Ă���T���v����������Ȃ��ꍇ
			{
				// ����Ȃ������[����B
				n = nSamples - a;
				CDROM_Mix(_pMixBuf3+(_MixBufPos3 << 1), n);
				_MixBufPos3 += n;
				if (_MixBufPos3 >= _BufSizeAll)
					_MixBufPos3 -= _BufSizeAll;
				_MixBufEndPos3 = _MixBufPos3;
			}
			break;
		default:
			pSrc = 0; //�R���p�C���G���[�����
	}
	ReleaseMutex(_hMutex); //v2.18�B�r������

	//DirectSound�̃o�b�t�@�ɏ�������
	//Kitao�X�V�B�����ł̓{�����[���_�E���̂ݍs���悤�ɂ������߃T�`�����[�V�����`�F�b�N�͕s�v�ɁB
	for (i = 0; i < nSamples; i++)
	{
		*pDst++ = (Sint16)((Sint32)(*pSrc) * _Volume / 65535); //Kitao�X�V�BpSrc�̂ق���Sint16�ɂ����̂ł��̂܂܏������ށB
		*pSrc++ = 0; //�g���I������o�b�t�@��0�ɃN���A���Ă���
		*pDst++ = (Sint16)((Sint32)(*pSrc) * _Volume / 65535);
		*pSrc++ = 0; //�g���I������o�b�t�@��0�ɃN���A���Ă���
	}

	//Kitao�ǉ��B���̂P�o�b�t�@�����܂�Ԃ�܂Ńo�b�t�@�f�[�^���[���Ă����Bv2.17�X�V
	//			 �����ōs�����ƂŁA���O��DirectSound�ւ̏������ݒ��ɗ��܂����o�b�t�@���g���邱�ƂɂȂ�A�o�b�t�@�����Ȃ��ݒ肵�Ă��������ۂĂ�B
	//			 �܂��APSG�̉��𑜓x���オ��(���DirectSound�̃o�b�t�@�������ݏ������Ƀ��C���X���b�h��CPU����PSG���W�X�^����������邱�Ƃ����X����̂�)�A�r�u���[�g�����Ȃǂ����@�̉��ɋ߂Â��B
	//				   CPU�G�~�����[�g�̓����4�u���b�N�ɕ����čs���Ă���(MainBorad.cpp��)���R�́A������ő���ɐ��������߁B(�������ЂƂ̗��R�̓W���C�p�b�h���͂̂P�t���[���x���폜)
	//				   �o�b�t�@�̗ʂɂ���čČ������኱�ς������A���������܂�ɑ���PC�ɂȂ����Ƃ��ɂ͂��̌��ʂ��o�ɂ����Ȃ�\��������̂ŁA�������̃^�C�~���O���������������Bv2.17�L
	WaitForSingleObject(_hMutex, INFINITE); //���C���X���b�h����������ɋ��L�ϐ���������������\��������̂ŁA�r�������Bv2.18
	switch (ch)
	{
		case 1: //PSG
			_NextPlayPos1 += _BufSize;
			if (_NextPlayPos1 == _BufSizeAll) _NextPlayPos1 = 0;
			//���̂P�o�b�t�@�����܂�Ԃ�܂ŕ�[
			if ((_MixBufPos1 >= _NextPlayPos1))
				a = _MixBufPos1 - _NextPlayPos1;
			else
				a = _BufSizeAll - _NextPlayPos1 + _MixBufPos1;
			n = nSamples - a;// n������Ȃ����Ba���o�b�t�@�ɗ��܂��Ă���T���v�����B
			if (n > 0) //���܂��Ă���T���v����������Ȃ��ꍇ
			{
				// ����Ȃ������[����B
				if (_MixBufPos1 + n > _BufSizeAll) //�o�b�t�@�Ō�����炠�ӂ�Ă��܂��ꍇ�́A�܂��o�b�t�@�Ō���܂�Mix���Ďc���擪����Mix�B
				{
					n2 = _BufSizeAll - _MixBufPos1;
					PSG_Mix(_pMixBuf1+(_MixBufPos1 << 1), n2);
					_MixBufPos1 = 0;
					n -= n2;
				}
				PSG_Mix(_pMixBuf1+(_MixBufPos1 << 1), n);
				_MixBufPos1 += n;
				if (_MixBufPos1 >= _BufSizeAll)
					_MixBufPos1 -= _BufSizeAll;
				_MixBufEndPos1 = _MixBufPos1;
			}
			_bPosStop1 = FALSE;
			break;
			
		case 2: //ADPCM
			_NextPlayPos2 += _BufSize;
			if (_NextPlayPos2 == _BufSizeAll) _NextPlayPos2 = 0;
			//���̂P�o�b�t�@�����܂�Ԃ�܂ŕ�[
			if ((_MixBufPos2 >= _NextPlayPos2))
				a = _MixBufPos2 - _NextPlayPos2;
			else
				a = _BufSizeAll - _NextPlayPos2 + _MixBufPos2;
			n = nSamples - a;// n������Ȃ����Ba���o�b�t�@�ɗ��܂��Ă���T���v�����B
			if (n > 0) //���܂��Ă���T���v����������Ȃ��ꍇ
			{
				// ����Ȃ������[����B
				if (_MixBufPos2 + n > _BufSizeAll) //�o�b�t�@�Ō�����炠�ӂ�Ă��܂��ꍇ�́A�܂��o�b�t�@�Ō���܂�Mix���Ďc���擪����Mix�B
				{
					n2 = _BufSizeAll - _MixBufPos2;
					ADPCM_Mix(_pMixBuf2+(_MixBufPos2 << 1), n2);
					_MixBufPos2 = 0;
					n -= n2;
				}
				ADPCM_Mix(_pMixBuf2+(_MixBufPos2 << 1), n);
				_MixBufPos2 += n;
				if (_MixBufPos2 >= _BufSizeAll)
					_MixBufPos2 -= _BufSizeAll;
				_MixBufEndPos2 = _MixBufPos2;
			}
			_bPosStop2 = FALSE;
			break;
		
		case 3: //CDDA
			_NextPlayPos3 += _BufSize;
			if (_NextPlayPos3 == _BufSizeAll) _NextPlayPos3 = 0;
			//���̂P�o�b�t�@�����܂�Ԃ�܂ŕ�[
			if ((_MixBufPos3 >= _NextPlayPos3))
				a = _MixBufPos3 - _NextPlayPos3;
			else
				a = _BufSizeAll - _NextPlayPos3 + _MixBufPos3;
			n = nSamples - a;// n������Ȃ����Ba���o�b�t�@�ɗ��܂��Ă���T���v�����B
			if (n > 0) //���܂��Ă���T���v����������Ȃ��ꍇ
			{
				// ����Ȃ������[����B
				if (_MixBufPos3 + n > _BufSizeAll) //�o�b�t�@�Ō�����炠�ӂ�Ă��܂��ꍇ�́A�܂��o�b�t�@�Ō���܂�Mix���Ďc���擪����Mix�B
				{
					n2 = _BufSizeAll - _MixBufPos3;
					CDROM_Mix(_pMixBuf3+(_MixBufPos3 << 1), n2);
					_MixBufPos3 = 0;
					n -= n2;
				}
				CDROM_Mix(_pMixBuf3+(_MixBufPos3 << 1), n);
				_MixBufPos3 += n;
				if (_MixBufPos3 >= _BufSizeAll)
					_MixBufPos3 -= _BufSizeAll;
				_MixBufEndPos3 = _MixBufPos3;
			}
			break;
	}
	ReleaseMutex(_hMutex); //v2.18�B�r������

	_bApuBusy = FALSE; //Kitao�ǉ�
}


//Kitao�ǉ��B�R�[���o�b�N�X���b�h�����s���Ȃ�TRUE��Ԃ��B�X�e�[�g�Z�[�u����ۂɎg�p�B
BOOL
APU_GetApuBusy()
{
	return _bApuBusy;
}


/*-----------------------------------------------------------------------------
	[Init]
		APU�����������܂��B
-----------------------------------------------------------------------------*/
BOOL
APU_Init(
	Uint32		sampleRate,
	Uint32		bufSize)		// in samples
{
	_hMutex = CreateMutex(NULL,FALSE,NULL); //v2.18

	_Volume				= 65535;

	_SampleRate			= sampleRate;
	_nSamplesPerFrame	= _SampleRate / 60;

	//�o�b�t�@��������
	if (!APU_SetBufferSize(bufSize))
		return FALSE;

	PSG_Init(sampleRate);
	ADPCM_Init();

	return TRUE;
}


void
APU_Pause(
	BOOL		bPause)
{
	if (bPause)
		AOUT_Play(FALSE);
	else
		AOUT_Play(TRUE);
}


void
APU_Deinit()
{
	AOUT_Deinit(); //���̌Ăяo����AOUT�̃X���b�h�͏I������B
	PSG_Deinit();
	ADPCM_Deinit();
	if (_pMixBuf1 != NULL)
		free(_pMixBuf1);
	if (_pMixBuf2 != NULL)
		free(_pMixBuf2);
	if (_pMixBuf3 != NULL)
		free(_pMixBuf3);
	_pMixBuf1 = NULL;
	_pMixBuf2 = NULL;
	_pMixBuf3 = NULL;
	CloseHandle(_hMutex); //v2.18
}


BOOL
APU_Reset()
{
	//Kitao�X�V�BAPU�֘A�̕ϐ������������K�v�i���������Ȃ��ƃo�b�t�@�̃|�C���^���r������n�܂�̂ŉ����x���ꍇ������j
	APU_Deinit();
	return APU_Init(_SampleRate, _BufSize);
}


/*-----------------------------------------------------------------------------
	[SetSampleRate]
-----------------------------------------------------------------------------*/
BOOL
APU_SetSampleRate(
	Uint32		sampleRate)
{
	AOUT_Deinit();

	ZeroMemory(_pMixBuf1, _BufSize*sizeof(Sint16)*2*AOUT_BUFFERRATE); //Kitao�X�V�BPSG�p�B�����o�b�t�@��AOUT_BUFFERRATE�{�Ԃ�p�ӁB
	ZeroMemory(_pMixBuf2, _BufSize*sizeof(Sint16)*2*AOUT_BUFFERRATE); //Kitao�X�V�BADPCM�p
	ZeroMemory(_pMixBuf3, _BufSize*sizeof(Sint16)*2*AOUT_BUFFERRATE); //Kitao�X�V�BCDDA�p

	if (!AOUT_Init(APP_GetSoundType(), _BufSize, sampleRate, callback_mixer))
	{
		// ���̐ݒ�ɖ߂� 
		if (!AOUT_Init(APP_GetSoundType(), _BufSize, _SampleRate, callback_mixer))
			return FALSE;	// ����ł��_���Ȃ炠����߂�B
	}
	_SampleRate = sampleRate;
	_nSamplesPerFrame = _SampleRate / 60;

	PSG_SetSampleRate(sampleRate);

	return TRUE;
}


/*-----------------------------------------------------------------------------
	[SetBufferSize]
-----------------------------------------------------------------------------*/
//Kitao�X�V�B�ʏ편�s���邱�Ƃ͂Ȃ��̂ŃV���v���ɂ����B
BOOL
APU_SetBufferSize(
	Uint32		bufSize)
{
	AOUT_Deinit();

	//if (APP_GetSoundMethod() == 20)
	//	_BufSize = bufSize/2 + bufSize/4; //XAudio2���p���͒x�����傫���̂�DirectSound���p�����o�b�t�@�����Ȃ߂Ɏ��悤�ɂ����B�ݒ�l��75%�ŁB�����ݕۗ�
	//else //DirectSound��
	_BufSize = bufSize;

	if (_pMixBuf1 != NULL)
		free(_pMixBuf1);
	if (_pMixBuf2 != NULL)
		free(_pMixBuf2);
	if (_pMixBuf3 != NULL)
		free(_pMixBuf3);

	// 8 [byte/sample] for Sint32 stereo buffer 
	if ((_pMixBuf1 = (Sint16*)malloc(_BufSize*sizeof(Sint16)*2*AOUT_BUFFERRATE)) == NULL) //Kitao�X�V�BPSG�p�B�����o�b�t�@��AOUT_BUFFERRATE�{�Ԃ�p�ӁB
		return FALSE;
	if ((_pMixBuf2 = (Sint16*)malloc(_BufSize*sizeof(Sint16)*2*AOUT_BUFFERRATE)) == NULL) //Kitao�X�V�BADPCM�p
		return FALSE;
	if ((_pMixBuf3 = (Sint16*)malloc(_BufSize*sizeof(Sint16)*2*AOUT_BUFFERRATE)) == NULL) //Kitao�X�V�BCDDA�p
		return FALSE;

	ZeroMemory(_pMixBuf1, _BufSize*sizeof(Sint16)*2*AOUT_BUFFERRATE); //Kitao�X�V�BPSG�p�B�����o�b�t�@��AOUT_BUFFERRATE�{�Ԃ�p�ӁB
	ZeroMemory(_pMixBuf2, _BufSize*sizeof(Sint16)*2*AOUT_BUFFERRATE); //Kitao�X�V�BADPCM�p
	ZeroMemory(_pMixBuf3, _BufSize*sizeof(Sint16)*2*AOUT_BUFFERRATE); //Kitao�X�V�BCDDA�p

	if (!AOUT_Init(APP_GetSoundType(), _BufSize, _SampleRate, callback_mixer))
		return FALSE;

	_BufSizeAll		= _BufSize * AOUT_BUFFERRATE; //Kitao�ǉ�
	_ClockCount		= 0;
	_MixBufPos1		= 0;
	_MixBufEndPos1	= 0.0;
	_NextPlayPos1	= 0; //Kitao�ǉ�
	_bPosStop1		= FALSE; //Kitao�ǉ�
	_bPosStop2		= FALSE; //Kitao�ǉ�
	_MixBufPos2		= 0;
	_MixBufEndPos2	= 0.0;
	_NextPlayPos2	= 0; //Kitao�ǉ�
	_MixBufPos3		= 0;
	_MixBufEndPos3	= 0;
	_NextPlayPos3	= 0; //Kitao�ǉ�
	AOUT_SetPlayStart(); //Kitao�ǉ��B����Đ��̍��}��ݒ肷��B������͂܂��o�b�t�@�ɂ���ޗ��iPSG�L���[���j�����܂��Ă��Ȃ�����AOUT�̂ق��ŃE�F�C�g����悤�ɂ����B

	return TRUE;
}


void
APU_SetVolume(
	Uint32		volume)		// 0 - 65535
{
	_Volume = volume;
}


#define DIV				256.0
#define DELTA_POS		44100.0 / 60.0 / DIV //Kitao�ǉ��B�萔�ɂ����B
#define DELTA_CLOCK		(Sint32)(2.0 * PSG_FRQ / 60.0 / DIV - 3.0) //Kitao�ǉ��B�萔�ɂ����B���r�؂�̃v�`�m�C�Y��h�����߂�-3.0�iDELTA_POS�̐؂�グ�l�Ԃ�B�傫������������ƘA�����͗ǂ��Ȃ邪�̂��؂肵�����ɂȂ�j�Bv1.09�X�V

//Kitao�X�V�Bv2.32
void
APU_AdvanceClock()
{
	Sint32		nSamples;
	Sint32		nSamples2;//Kitao�ǉ�
//	Sint32		deltaClock; //Kitao�X�V�B�萔�ɂ��đ��x�A�b�v�B
//	double		deltaPos; //Kitao�X�V�B�����44100Hz�Œ�̂��ߒ萔�ɂ��đ��x�A�b�v�B

	ADPCM_AdvanceFadeClock();
	CDROM_AdvanceFadeClock(); //Kitao�ǉ�

	if (++_ClockCount < DELTA_CLOCK)
		return;

	//WriteBuffer����
	//  Kitao�X�V�B�o�b�t�@���S�ɕ����ăo�b�t�@�ɓr�؂��ʒu���Ȃ��悤�ɂ����B�x���͂��̂܂܂Ńo�b�t�@���������߂���悤�ɂȂ茋�ʓI�ɉ������オ�����B
	//			   �i�߂�N���b�N����1�N���b�N�Œ�ɂ����B�߂�l�͔p�~�����B
	//			   v2.17�X�V�B�����ł�PSG�`�����l���݂̂�Mix���邱�Ƃɂ����BCD-ROM�̓X�g���[���Ȃ̂ł����ׂ̍����^�C�~���O��Mix����K�v���Ȃ����߁B�������B

	_ClockCount = 0;

	WaitForSingleObject(_hMutex, INFINITE); //�I�[�f�B�I�X���b�h����������ɋ��L�ϐ���������������\��������̂ŁA�r�������Bv2.18

	// Kitao�X�V�BPSG, ADPCM, CDDA ���ꂼ���ʃo�b�t�@�ōĐ�����悤�ɂ����B
	//�i�\�t�g��PSG,ADPCM,CDDA���~�b�N�X���ĉ���炵���ꍇ�A�_�C�i�~�b�N�����W��1/3�ɉ����Ȃ��Ă͂����Ȃ��̂ŉ������傫�������Ă��܂����߁j

	// PSG�`�����l��
	if (!_bPosStop1)
	{
		_MixBufEndPos1 += DELTA_POS;
		nSamples = (Sint32)(_MixBufEndPos1 + 0.5) - _MixBufPos1; //�����_�ȉ��͎l�̌ܓ��BPSG�̏ꍇ�AMix����^�C�~���O�����m�ȂقǁA�؂�̂āE�؂�グ�����������ǂ��Ȃ�B
		if (_MixBufPos1 + nSamples >= _BufSizeAll) //�ŏI�_���߂���Ȃ�
		{
			nSamples2 = _BufSizeAll - _MixBufPos1;
			//���E�_�܂ŏ�������
			PSG_Mix(_pMixBuf1 + (_MixBufPos1 << 1), nSamples2);// �X�e���I������ _MixBufPos*2
			_MixBufPos1 = 0;
			if (_NextPlayPos1 != 0) //���̍Đ����擪���炶��Ȃ��ꍇ
			{
				//�c���擪���珑������
				nSamples -=	nSamples2;
				PSG_Mix(_pMixBuf1 + (_MixBufPos1 << 1), nSamples);// �X�e���I������ _MixBufPos*2 
				_MixBufPos1 = nSamples;
				_MixBufEndPos1 -= (double)_BufSizeAll;
			}
			else
			{
				//�o�b�t�@�̌��E�܂ŏ������񂾁B�o�b�t�@���g����܂Ŏ���̓o�b�t�@�ɒǉ����Ȃ��B
				_MixBufEndPos1 = 0.0;
				_bPosStop1 = TRUE;
			}
		}
		else if	((_MixBufPos1 < _NextPlayPos1)&&(_MixBufPos1 + nSamples >= _NextPlayPos1)) //���ݕ���_�O�ŁA�����ƕ���_���߂���Ȃ�
		{
			nSamples = _NextPlayPos1 - _MixBufPos1;
			//���E�_�܂ŏ�������
			PSG_Mix(_pMixBuf1 + (_MixBufPos1 << 1), nSamples);// �X�e���I������ _MixBufPos*2 
			//�o�b�t�@�̌��E�܂ŏ������񂾁B�o�b�t�@���g����܂Ŏ���̓o�b�t�@�ɒǉ����Ȃ��B
			_MixBufPos1 = _NextPlayPos1;
			_MixBufEndPos1 = _MixBufPos1;
			_bPosStop1 = TRUE;
		}
		else //�ʏ�
		{
			PSG_Mix(_pMixBuf1 + (_MixBufPos1 << 1), nSamples);// �X�e���I������ _MixBufPos*2 
			_MixBufPos1 += nSamples;
		}
	}

	// ADPCM�`�����l��
	if (!_bPosStop2)
	{
		_MixBufEndPos2 += DELTA_POS;
		nSamples = (Sint32)(_MixBufEndPos2 + 0.5) - _MixBufPos2; //�����_�ȉ��͎l�̌ܓ��B�h���S���X���C���[�p�Y�`���̃h�������ōׂ��ȃ^�C�~���O��v������邱�Ƃ�����̂ŁA�؎̂Đ؂�グ�łȂ��l�̌ܓ��Ƃ����B
		if (_MixBufPos2 + nSamples >= _BufSizeAll) //�ŏI�_���߂���Ȃ�
		{
			nSamples2 = _BufSizeAll - _MixBufPos2;
			//���E�_�܂ŏ�������
			ADPCM_Mix(_pMixBuf2 + (_MixBufPos2 << 1), nSamples2);// �X�e���I������ _MixBufPos*2
			_MixBufPos2 = 0;
			if (_NextPlayPos2 != 0) //���̍Đ����擪���炶��Ȃ��ꍇ
			{
				//�c���擪���珑������
				nSamples -=	nSamples2;
				ADPCM_Mix(_pMixBuf2 + (_MixBufPos2 << 1), nSamples);// �X�e���I������ _MixBufPos*2 
				_MixBufPos2 = nSamples;
				_MixBufEndPos2 -= (double)_BufSizeAll;
			}
			else
			{
				//�o�b�t�@�̌��E�܂ŏ������񂾁B�o�b�t�@���g����܂Ŏ���̓o�b�t�@�ɒǉ����Ȃ��B
				_MixBufEndPos2 = 0.0;
				_bPosStop2 = TRUE;
			}
		}
		else if	((_MixBufPos2 < _NextPlayPos2)&&(_MixBufPos2 + nSamples >= _NextPlayPos2)) //���ݕ���_�O�ŁA�����ƕ���_���߂���Ȃ�
		{
			nSamples = _NextPlayPos2 - _MixBufPos2;
			//���E�_�܂ŏ�������
			ADPCM_Mix(_pMixBuf2 + (_MixBufPos2 << 1), nSamples);// �X�e���I������ _MixBufPos*2 
			//�o�b�t�@�̌��E�܂ŏ������񂾁B�o�b�t�@���g����܂Ŏ���̓o�b�t�@�ɒǉ����Ȃ��B
			_MixBufPos2 = _NextPlayPos2;
			_MixBufEndPos2 = _MixBufPos2;
			_bPosStop2 = TRUE;
		}
		else //�ʏ�
		{
			ADPCM_Mix(_pMixBuf2 + (_MixBufPos2 << 1), nSamples);// �X�e���I������ _MixBufPos*2 
			_MixBufPos2 += nSamples;
		}
	}

	ReleaseMutex(_hMutex); //v2.18�B�r������
}


// save variable
#define SAVE_V(V)	if (fwrite(&V, sizeof(V), 1, p) != 1)	return FALSE
#define LOAD_V(V)	if (fread(&V, sizeof(V), 1, p) != 1)	return FALSE
/*-----------------------------------------------------------------------------
	[SaveState]
		��Ԃ��t�@�C���ɕۑ����܂��B 
-----------------------------------------------------------------------------*/
BOOL
APU_SaveState(
	FILE*		p)
{
	BOOL	ret;
	Sint32	windowsVolume;

	if (p == NULL)
		return FALSE;

	SAVE_V(_ClockCount);
	windowsVolume = APP_GetWindowsVolume();
	SAVE_V(windowsVolume); //v1.61�ǉ��B�Q�[�����̃{�����[�������l�B���W���[�����[�h�̂Ƃ��̂ݗL���B�񃌃W���[�����ɂ�SAVE�͂��Ă����B

	ret =  PSG_SaveState(p);
	ret |= ADPCM_SaveState(p);
	
	return ret;
}


/*-----------------------------------------------------------------------------
	[LoadState]
		��Ԃ��t�@�C������ǂݍ��݂܂��B 
-----------------------------------------------------------------------------*/
BOOL
APU_LoadState(
	FILE*		p)
{
	BOOL	ret;
	Sint32	windowsVolume;

	if (p == NULL)
		return FALSE;

	LOAD_V(_ClockCount);
	if (MAINBOARD_GetStateVersion() >= 33) //Kitao�ǉ��Bv1.61beta�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(windowsVolume);
		APP_ResumeWindowsVolume(windowsVolume); //���W���[���t�@�C����ǂݏo�����ꍇ�̂݁A���ʂ𕜌�����B
	}

	ret =  PSG_LoadState(p);
	ret |= ADPCM_LoadState(p);

	return TRUE;
}

#undef SAVE_V
#undef LOAD_V
