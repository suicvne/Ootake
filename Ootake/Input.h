/******************************************************************************
	[Input.h]

		���͌n�̃C���^�t�F�C�X���`���܂��D

		Define input interface.

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
#ifndef INPUT_INTERFACE_H_INCLUDED
#define INPUT_INTERFACE_H_INCLUDED

#include <stdio.h>
#include <dinput.h>
#include "TypeDefs.h"

#define INPUT_NUM_BUTTON	24 //Kitao�X�V�B�n�b�g�X�C�b�`�{16�{�^���p�b�h�ɂ��Ή��B


enum KeyType
{
	INPUT_JOYSTICK_UP       = 0x00000001,
	INPUT_JOYSTICK_DOWN     = 0x00000002,
	INPUT_JOYSTICK_LEFT     = 0x00000004,
	INPUT_JOYSTICK_RIGHT    = 0x00000008,
	INPUT_JOYSTICK_POVUP    = 0x00000010,//Kitao�ǉ��B�n�b�g�X�C�b�`�ɂ��Ή��B
	INPUT_JOYSTICK_POVDOWN  = 0x00000020,//Kitao�ǉ�
	INPUT_JOYSTICK_POVLEFT  = 0x00000040,//Kitao�ǉ�
	INPUT_JOYSTICK_POVRIGHT = 0x00000080,//Kitao�ǉ�
	INPUT_JOYSTICK_BUTTON1  = 0x00000100,
	INPUT_JOYSTICK_BUTTON2  = 0x00000200,
	INPUT_JOYSTICK_BUTTON3  = 0x00000400,
	INPUT_JOYSTICK_BUTTON4  = 0x00000800,
	INPUT_JOYSTICK_BUTTON5  = 0x00001000,
	INPUT_JOYSTICK_BUTTON6  = 0x00002000,
	INPUT_JOYSTICK_BUTTON7  = 0x00004000,
	INPUT_JOYSTICK_BUTTON8  = 0x00008000,
	INPUT_JOYSTICK_BUTTON9  = 0x00010000,
	INPUT_JOYSTICK_BUTTON10 = 0x00020000,
	INPUT_JOYSTICK_BUTTON11 = 0x00040000,
	INPUT_JOYSTICK_BUTTON12 = 0x00080000,
	INPUT_JOYSTICK_BUTTON13 = 0x00100000,//Kitao�ǉ�
	INPUT_JOYSTICK_BUTTON14 = 0x00200000,//Kitao�ǉ�
	INPUT_JOYSTICK_BUTTON15 = 0x00400000,//Kitao�ǉ�
	INPUT_JOYSTICK_BUTTON16 = 0x00800000 //Kitao�ǉ�
};


//Kitao�ǉ��B���l���v���C�ł��L�[�{�[�h���g����悤�ɂ����B���̂��߂ɁA�ePCE�p�b�h�̐ݒ�ϐ���p�ӁB
typedef struct
{
	Sint16	buttonU; //��L�[�̐ݒ�B�A�X�L�[�R�[�h(1�`255)�B�W���C�p�b�h�P(300�`399�B100�{�^���܂őΉ�)�B�W���C�p�b�h�Q(400�`499)�B�ȉ��W���C�p�b�h�T�{�܂œ��l�B
	Sint16	buttonR; //�E�L�[�̐ݒ�
	Sint16	buttonD; //���L�[�̐ݒ�
	Sint16	buttonL; //���L�[�̐ݒ�
	Sint16	buttonSel; //Select�{�^���̐ݒ�
	Sint16	buttonRun; //Run�{�^���̐ݒ�
	Sint16	button1; //I�{�^���̐ݒ�
	Sint16	button2; //II�{�^���̐ݒ�
	Sint16	button3; //III�{�^���̐ݒ�
	Sint16	button4; //IV�{�^���̐ݒ�
	Sint16	button5; //V�{�^���̐ݒ�
	Sint16	button6; //VI�{�^���̐ݒ�
} PCEPAD;


BOOL	INPUT_Init();
void	INPUT_Deinit();

//Kitao�X�V
void
INPUT_UpdateState(
	BOOL	bRecord);

BOOL
INPUT_IsPressed(Sint32 padID, Sint32 userButtonID);

BOOL	INPUT_IsTriggered(Sint32 userButtonID);

//Kitao�X�V�BApp.c�œǂݍ���_PcePad[]���A������ɂ����f������֐��ɁB
void
INPUT_ConnectButton(
	Sint32	padID,
	PCEPAD*	pcepad);

void	INPUT_Record(BOOL bRecord);
void	INPUT_PlayRecord(BOOL bPlayrecord); //Kitao�X�V

Sint32	INPUT_GetNumJoystick();

BOOL	INPUT_WriteBuffer(FILE*	fp);
BOOL	INPUT_ReadBuffer(FILE* fp);

//Kitao�ǉ�
void
INPUT_Acquire();

//Kitao�ǉ�
BOOL
INPUT_CheckButtonState(
	Sint32	a);

//Kitao�ǉ��B�e�Q�[�����Ƃ̎�������ݒ�����Z�b�g(�I�t��)����B
void
INPUT_ResetGameSetting();

//Kitao�ǉ�
void
INPUT_SetKonamiStereo(
	BOOL	bKonamiStereo);

//Kitao�ǉ�
void
INPUT_SetGradiusII(
	BOOL	bGradiusII);

#endif // INPUT_INTERFACE_H_INCLUDED
