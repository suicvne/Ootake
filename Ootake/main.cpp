/******************************************************************************
Ootake
�E��d�N��������Ɩ�肪�N����ꍇ������̂ŁA��d�N���͖h�~����悤�ɂ����B
�ECOM�̏������ƊJ���������ł��悤�ɂ����BVista�Ńt�@�C���_�C�A���O�g�p����
  ���������Ă����Ȃ��ƕs���肾�����Bv1.05
�E�}���`���f�B�A�^�C�}�̐��x�������ŏグ�Ă����悤�ɂ����Bv1.55

Copyright(C)2006-2010 Kitao Nakamura.
    Attach the source code when you open the remodeling version and the
    succession version to the public. and, please contact me by E-mail.
    Business use is prohibited.
	Additionally, it applies to "GNU General Public License". 
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[main]
		�{�v���W�F�N�g�̃��C���֐��ł��D

		The main function of the project.

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

#define _WIN32_DCOM //v2.17�X�V

#include <objbase.h>
#include "App.h"

// gcc �� main ����`����Ă����
// WinMain ������� main ���Ă�ł��܂��炵���D�D�D
// __main__ �Ƃ����̂͂��� workaround.
int
__main__(
	int			argc,
	char**		argv)
{
	HANDLE		hMutex;
	TIMECAPS	tc;

	//Kitao�ǉ��B��d�N����h�~
	hMutex = CreateMutex(NULL, TRUE, "Ootake Emulator"); //�~���[�e�b�N�X�̍쐬
	if (GetLastError() == ERROR_ALREADY_EXISTS) //���ł�Ootake���N�����Ă�����
		return 0; //�N�������ɏI��

	CoInitializeEx(NULL, COINIT_MULTITHREADED); //Kitao�ǉ��Bv2.17�X�V�B�Q�l�F�A�p�[�g�����g(COINIT_APARTMENTTHREADED)���Ɖ��������d�������ɂȂ�(�����炭����MTA���STA�̂ق��������Ԋu������)�Bv2.19�L
	timeGetDevCaps(&tc, sizeof(tc));
	timeBeginPeriod(tc.wPeriodMin); //Kitao�ǉ��B�^�C�}���x�������ŏグ�Ă����悤�ɂ����B

	if (!APP_Init(argc, argv))
		return -1;

	while (APP_ProcessEvents() != APP_QUIT);

	APP_Deinit();

	timeEndPeriod(tc.wPeriodMin); //Kitao�ǉ�
	CoUninitialize(); //Kitao�ǉ�

	return 0;
}
