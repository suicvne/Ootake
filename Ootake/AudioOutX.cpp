/******************************************************************************
Ootake

	[AudioOutX.c]
		�I�[�f�B�I�C���^�t�F�C�X�� XAudio2 �𗘗p���Ď������܂��B

Copyright(C)2006-2013 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************/
#define _WIN32_DCOM //v2.19�ǉ�

#include <stdio.h>
#include <xaudio2.h>
#include "AudioOutX.h"
#include "AudioOut.h"
#include "WinMain.h"
#include "Printf.h"
#include "App.h"

//Kitao�X�V�B�\�t�g��PSG,ADPCM,CDDA���~�b�N�X���ĉ���炵���ꍇ�A�_�C�i�~�b�N�����W��1/3�ɉ����Ȃ��Ă͂����Ȃ��̂ŉ������傫�������Ă��܂��B���̂��ߊeCh��p�̃o�b�t�@�Ŗ炷�悤�ɂ����B
static	IXAudio2*				_pXA	= NULL;
static	IXAudio2MasteringVoice*	_pMV	= NULL; //�}�X�^�����O�{�C�X
static	IXAudio2SourceVoice*	_pSV1	= NULL; //PSG�Đ��p
static	IXAudio2SourceVoice*	_pSV2	= NULL; //ADPCM�Đ��p
static	IXAudio2SourceVoice*	_pSV3	= NULL; //CDDA�Đ��p
static	XAUDIO2_BUFFER			_SV1BUF = {0};
static	XAUDIO2_BUFFER			_SV2BUF = {0};
static	XAUDIO2_BUFFER			_SV3BUF = {0};
static	BYTE*					_pBuf1[AOUTX_BUFFERRATE]; //PSG�Đ��p�B�o�b�t�@�͓r�؂���N�����Ȃ����߂ɂR�Ԃ�ɕ����B
static	Sint32					_BufN1;
static	BYTE*					_pBuf2[AOUTX_BUFFERRATE]; //ADPCM�Đ��p
static	Sint32					_BufN2;
static	BYTE*					_pBuf3[AOUTX_BUFFERRATE]; //CDDA�Đ��p
static	Sint32					_BufN3;

class VoiceCallback: public IXAudio2VoiceCallback
{
	public:
		HANDLE hBufferEndEvent;
		VoiceCallback(): hBufferEndEvent(CreateEvent(NULL, FALSE, FALSE, NULL)){}
		~VoiceCallback(){CloseHandle(hBufferEndEvent);}
		STDMETHOD_(void, OnBufferEnd(void *)){SetEvent(hBufferEndEvent);}
		STDMETHOD_(void, OnStreamEnd)(){}
		STDMETHOD_(void, OnVoiceProcessingPassEnd)(){}
		STDMETHOD_(void, OnVoiceProcessingPassStart(UINT32)){}
		STDMETHOD_(void, OnBufferStart(void *)){}
		STDMETHOD_(void, OnLoopEnd(void *)){}
		STDMETHOD_(void, OnVoiceError(void *, HRESULT)){}
};
static	VoiceCallback		_VoiceCallback1;
static	VoiceCallback		_VoiceCallback2;
static	VoiceCallback		_VoiceCallback3;

static UINT32 OperationSetCounter = 0;
static UINT32 _OperationID = UINT32(InterlockedIncrement(LPLONG(&OperationSetCounter)));

static	DWORD				_dwBufSize;
static	HANDLE				_hThread;
static	DWORD				_dwThreadID;

static	volatile BOOL		_bPlay; //v2.05�X�V�Bvolatile�ɁB
static	volatile BOOL		_bThreadEnd; //Kitao�ǉ��B�X���b�h���I���������Ƃ�TRUE�ɂ��Ēm�点��B
static	volatile BOOL		_bThreadStarted; //v2.71�ǉ��B�X���b�h���m���ɓ����o������TRUE�ɁB

static 	void				(*_pCallBack)(int ch, Sint16* pBuf, Sint32 nSamples) = NULL; //Kitao�X�V�Bch(�`�����l���i���o�[)��ǉ�

static	BOOL				_bAudioInit = FALSE;


/*-----------------------------------------------------------------------------
	[write_streaming_buffer]
		XAudio2�̃o�b�t�@ �ɏo�͂��鉹���f�[�^���������݂܂��B
-----------------------------------------------------------------------------*/

//Kitao�X�V�B������PSG��p�B
static inline void
write_streaming_buffer_1()
{
	if (_bPlay) //�Đ����̂݃o�b�t�@�փL���[
	{
		_pCallBack(1, (Sint16*)(_pBuf1[_BufN1]), _dwBufSize/4); //1ch�ڂ����� ��/4=�u1�T���v����4�o�C�g�v�̈Ӗ�
		_SV1BUF.pAudioData = _pBuf1[_BufN1];
		_pSV1->SubmitSourceBuffer(&_SV1BUF, NULL); //���L���[��������A�o�b�t�@���̃f�[�^�͍Đ����I���܂Ŏc���Ȃ���΂Ȃ�Ȃ��B���̂���_pBuf1���z��Ƃ���3���K�v������B
		_BufN1++;
		_BufN1 %= AOUTX_BUFFERRATE;
	}
}

//Kitao�ǉ��B������ADPCM��p�B
static inline void
write_streaming_buffer_2()
{
	if (_bPlay)
	{
		_pCallBack(2, (Sint16*)(_pBuf2[_BufN2]), _dwBufSize/4); //1ch�ڂ����� ��/4=�u1�T���v����4�o�C�g�v�̈Ӗ�
		_SV2BUF.pAudioData = _pBuf2[_BufN2];
		_pSV2->SubmitSourceBuffer(&_SV2BUF);
		_BufN2++;
		_BufN2 %= AOUTX_BUFFERRATE;
	}
}

//Kitao�X�V�B������CDDA��p�B
static inline void
write_streaming_buffer_3()
{
	if (_bPlay)
	{
		_pCallBack(3, (Sint16*)(_pBuf3[_BufN3]), _dwBufSize/4); //1ch�ڂ����� ��/4=�u1�T���v����4�o�C�g�v�̈Ӗ�
		_SV3BUF.pAudioData = _pBuf3[_BufN3];
		_pSV3->SubmitSourceBuffer(&_SV3BUF);
		_BufN3++;
		_BufN3 %= AOUTX_BUFFERRATE;
	}
}


/*-----------------------------------------------------------------------------
	[playback_thread]
		�T�E���h�o�b�t�@�̍X�V���s�Ȃ��X���b�h�ł��B 
-----------------------------------------------------------------------------*/
static DWORD WINAPI
playback_thread(
	LPVOID	param)
{
	DWORD					dwOffset = 0;
	XAUDIO2_VOICE_STATE		state;
	Sint32					bn1, bn2, bn3;						

	CoInitializeEx(NULL, COINIT_MULTITHREADED); //v2.19�ǉ��B���ꂼ��̃X���b�h��CoInitializeEx���Ȃ��ƈ��肵�Ȃ��������邩������Ȃ��B(COINIT_MULTITHREADED�̏ꍇ�ACOM���g���X���b�h���ꂼ���CoInitializeEx���邱�Ƃ�MS������)

	while (!_bThreadEnd)
	{
		//PSG�`�����l���̃o�b�t�@���P�Ԃ�ȏ��ɂȂ�܂ő҂�
		while (_bPlay)
		{
			_pSV1->GetState(&state);
			if (state.BuffersQueued <= AOUTX_BUFFERRATE-1) break;
			WaitForSingleObject(_VoiceCallback1.hBufferEndEvent, INFINITE);
		}
		//�o�b�t�@�Ƀf�[�^�𑗂�
		write_streaming_buffer_1(); //PSG�`�����l��

		if (APP_GetCDGame()) //Hu�J�[�h�Q�[���̏������y������Bv2.36�ǉ�
		{
			//ADPCM�`�����l���̃o�b�t�@���P�Ԃ�ȏ��ɂȂ�܂ő҂B�����ōĂѓ������Ƃ�Ȃ���PSG�Ɗ��ݍ���Ȃ����Ƃ��������B
			while (_bPlay)
			{
				_pSV2->GetState(&state);
				if (state.BuffersQueued <= AOUTX_BUFFERRATE-1) break;
				WaitForSingleObject(_VoiceCallback2.hBufferEndEvent, INFINITE);
			}
			//�o�b�t�@�Ƀf�[�^�𑗂�
			write_streaming_buffer_2(); //ADPCM�`�����l��

			//CDDA�`�����l���̃o�b�t�@���P�Ԃ�ȏ��ɂȂ�܂ő҂�
			while (_bPlay)
			{
				_pSV3->GetState(&state);
				if (state.BuffersQueued <= AOUTX_BUFFERRATE-1) break;
				WaitForSingleObject(_VoiceCallback3.hBufferEndEvent, INFINITE);
			}
			//�o�b�t�@�Ƀf�[�^�𑗂�
			write_streaming_buffer_3(); //CDDA�`�����l��
		}

		//Kitao�ǉ��BWAV�t�@�C���֏o�͏���
		if (AOUT_GetfpOutputWAV() != NULL)
		{
			if (_bPlay)
			{
				if (_BufN1==0) bn1=AOUTX_BUFFERRATE-1; else bn1=_BufN1-1;
				if (_BufN2==0) bn2=AOUTX_BUFFERRATE-1; else bn2=_BufN2-1;
				if (_BufN3==0) bn3=AOUTX_BUFFERRATE-1; else bn3=_BufN3-1;
				AOUT_OutputWavExecute(_dwBufSize, (Sint16*)_pBuf1[bn1], (Sint16*)_pBuf2[bn2], (Sint16*)_pBuf3[bn3]);
			}
		}

		_bThreadStarted = TRUE; //v2.71�ǉ��BAudioOut�p�X���b�h���m���ɓ����o�������}�B
	}

	CoUninitialize(); //v2.19�ǉ�

	ExitThread(TRUE);
}


/*-----------------------------------------------------------------------------
	Deinit XAudio2

-----------------------------------------------------------------------------*/
static BOOL
x_deinit() 	//Kitao�X�V�B3ch�Ԃ�̃��\�[�X���J��
{
	int		i;

	if (!_bAudioInit)
		return FALSE;

	_bPlay = FALSE;

	if (_hThread)
	{
		//�X���b�h�̏I����҂� 
		_bThreadEnd = TRUE;
		SetEvent(_VoiceCallback1.hBufferEndEvent);//�o�b�t�@�`�F�b�N�̃��[�v���炷��������
		SetEvent(_VoiceCallback2.hBufferEndEvent);//
		SetEvent(_VoiceCallback3.hBufferEndEvent);//
		WaitForSingleObject(_hThread, INFINITE);

		CloseHandle(_hThread);
		_hThread = NULL;
	}

	_pSV1->DestroyVoice();
	_pSV2->DestroyVoice();
	_pSV3->DestroyVoice();
	_pSV1 = NULL;
	_pSV2 = NULL;
	_pSV3 = NULL;

	_pMV->DestroyVoice();
	_pMV = NULL;

	_pXA->Release();
	_pXA = NULL;

	for (i = 0; i<AOUTX_BUFFERRATE; i++)
	{
		GlobalFree(_pBuf1[i]);
		GlobalFree(_pBuf2[i]);
		GlobalFree(_pBuf3[i]);
		_pBuf1[i] = NULL;
		_pBuf2[i] = NULL;
		_pBuf3[i] = NULL;
	}
	AOUT_DeinitWavMixBuf(); //WAV�o�͗p�̃o�b�t�@���J��
	_dwBufSize = 0;

	return TRUE;
}


/*-----------------------------------------------------------------------------
	Initialize XAudio2

-----------------------------------------------------------------------------*/
static BOOL
x_init(
	Sint32	soundType, //DirectSound�p�BAudio2�ł͖����B
	HWND	hWnd,
	WORD	nChannels,
	WORD	nSamplesPerSec,
	WORD	wBitsPerSample,
	DWORD	dwBufSize)			// in bytes
{
	int				i;
	WAVEFORMATEX	waveFormat;//Kitao�X�V

	//XAudio2��������
	if (FAILED(XAudio2Create(&_pXA, 0, XAUDIO2_DEFAULT_PROCESSOR)))
	{
		MessageBox(WINMAIN_GetHwnd(), "ERROR: XAUDIO2::XAudio2Create() failed.    ", "Ootake", MB_OK);
		return FALSE;
	}

	//�}�X�^�����O�{�C�X���쐬
	if (FAILED(_pXA->CreateMasteringVoice(&_pMV, XAUDIO2_DEFAULT_CHANNELS, 44100, 0, 0, NULL)))
	{
		MessageBox(WINMAIN_GetHwnd(), "ERROR: XAUDIO2::CreateMasteringVoice() failed.    ", "Ootake", MB_OK);
		return FALSE;
	}

	//Wave�t�H�[�}�b�g��ݒ�
	ZeroMemory(&waveFormat, sizeof(WAVEFORMATEX));
	waveFormat.wFormatTag		= WAVE_FORMAT_PCM;
	waveFormat.nChannels		= nChannels; 
	waveFormat.wBitsPerSample	= wBitsPerSample;
	waveFormat.nBlockAlign		= waveFormat.nChannels * waveFormat.wBitsPerSample / 8;
	waveFormat.nSamplesPerSec	= nSamplesPerSec;
	waveFormat.nAvgBytesPerSec	= waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

	//�\�[�X�{�C�X���쐬�B3ch�Ԃ�쐬�B
	if (FAILED(_pXA->CreateSourceVoice(&_pSV1, &waveFormat, 0, XAUDIO2_DEFAULT_FREQ_RATIO, &_VoiceCallback1, NULL, NULL)))
	{
		MessageBox(WINMAIN_GetHwnd(), "ERROR: XAUDIO2::CreateSourceVoice() failed.    ", "Ootake", MB_OK);
		return FALSE;
	}
	if (FAILED(_pXA->CreateSourceVoice(&_pSV2, &waveFormat, 0, XAUDIO2_DEFAULT_FREQ_RATIO, &_VoiceCallback2, NULL, NULL)))
	{
		MessageBox(WINMAIN_GetHwnd(), "ERROR: XAUDIO2::CreateSourceVoice() failed.    ", "Ootake", MB_OK);
		return FALSE;
	}
	if (FAILED(_pXA->CreateSourceVoice(&_pSV3, &waveFormat, 0, XAUDIO2_DEFAULT_FREQ_RATIO, &_VoiceCallback3, NULL, NULL)))
	{
		MessageBox(WINMAIN_GetHwnd(), "ERROR: XAUDIO2::CreateSourceVoice() failed.    ", "Ootake", MB_OK);
		return FALSE;
	}

	//�o�b�t�@��ݒ�B3ch�Ԃ�쐬�B
	_dwBufSize = dwBufSize;
	_SV1BUF.AudioBytes	= _dwBufSize;
	_SV1BUF.Flags		= XAUDIO2_END_OF_STREAM;
	_SV2BUF.AudioBytes	= _dwBufSize;
	_SV2BUF.Flags		= XAUDIO2_END_OF_STREAM;
	_SV3BUF.AudioBytes	= _dwBufSize;
	_SV3BUF.Flags		= XAUDIO2_END_OF_STREAM;

	//�I�[�f�B�I�o�b�t�@���m�ۂ��� 
	for (i = 0; i<AOUTX_BUFFERRATE; i++)
	{
		_pBuf1[i] = (BYTE*)GlobalAlloc(GMEM_FIXED, _dwBufSize);
		_pBuf2[i] = (BYTE*)GlobalAlloc(GMEM_FIXED, _dwBufSize);
		_pBuf3[i] = (BYTE*)GlobalAlloc(GMEM_FIXED, _dwBufSize);
	}
	_BufN1 = 0;
	_BufN2 = 0;
	_BufN3 = 0;

	//WAV�o�͗p�̃o�b�t�@���m�ۂ���
	AOUT_InitWavMixBuf(_dwBufSize);

	_bPlay = FALSE;

	// �X���b�h���J�n����O�ɃI�[�f�B�I�����������t���O�����Ă�B
	// [2004.04.28] fixed
	_bAudioInit = TRUE;

	// �X���b�h���쐬�����s���� 
	_bThreadEnd = FALSE;
	_bThreadStarted = FALSE; //v2.71
	_hThread = CreateThread(NULL, 0, playback_thread, NULL, 0, &_dwThreadID);
	if (_hThread == NULL)
	{
		x_deinit();
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
AOUTX_Init(
	Sint32		soundType,	//Kitao�ǉ�
	Uint32		bufSize,	// in samples 
	Uint32		sampleRate,
	void		(*pCallBack)(int ch, Sint16* pBuf, Sint32 nSamples)) //Kitao�X�V�Bch(�`�����l���i���o�[)��ǉ�
{
	if (x_init(soundType, WINMAIN_GetHwnd(), 2, (WORD)sampleRate, 16, (DWORD)bufSize*2*2))
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
AOUTX_Play(
	BOOL	bPlay)
{
	if (!_bAudioInit)
		return;

	_bPlay = bPlay;
	if (_bPlay)
	{
		_pSV1->Start(0, _OperationID);
		_pSV2->Start(0, _OperationID);
		_pSV3->Start(0, _OperationID);
		_pXA->CommitChanges(_OperationID);
	}
	else
	{
		_pSV1->Stop(0, _OperationID);
		_pSV2->Stop(0, _OperationID);
		_pSV3->Stop(0, _OperationID);
		_pXA->CommitChanges(_OperationID);
	}
}


/*-----------------------------------------------------------------------------
	[Deinit]
		
-----------------------------------------------------------------------------*/
void
AOUTX_Deinit()
{
	if (!_bAudioInit)
		return;

	x_deinit();

	_bAudioInit = FALSE;
}


//Kitao�ǉ�
void
AOUTX_SetPlayStart()
{
	if (!_bAudioInit)
		return;

	// �Đ����o�b�t�@�̓��e���폜
	_pSV1->FlushSourceBuffers();
	_pSV2->FlushSourceBuffers();
	_pSV3->FlushSourceBuffers();

	_BufN1 = 0;
	_BufN2 = 0;
	_BufN3 = 0;
}


//Kitao�ǉ�
BOOL
AOUTX_GetPlay()
{
	return _bPlay;
}

//Kitao�ǉ�
BOOL
AOUTX_GetThreadStarted()
{
	if (!_bAudioInit)
		return TRUE;
	else
		return _bThreadStarted;
}

