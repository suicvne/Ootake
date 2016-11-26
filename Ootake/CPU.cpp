/******************************************************************************
Ootake
�E���荞�ݗv�����󂯕t�����Ƃ��ɁA�������荞�ݗv�����N���A����悤�ɂ����B
�E���荞�ݗv�����󂯕t�����Ƃ��ɁA���荞�݋֎~���ǂ������`�F�b�N����悤�ɂ���
  �֎~�������ꍇ�����荞�ݗv���͂��̂܂܂ɂ��Ă���(����ȍ~���荞�߂�)�悤�ɂ�
  ���Bv0.64
�E���X�^���荞�݃^�C�~���O(IRQ1)���ŏd�����邽�߁A���荞�݂̗D�揇�ʂ��t���Ƃ�
  ���B
�ED�t���O�������Ă���Ƃ���ADC���Z�ŁA���܂��l��������Ă��Ȃ������s����C��
  �����B
�ECSH,CSL���߂̓��������������B�iCSL�̓��X�^���荞�ݏ����̎��ԑ҂��Ɏg���邱
  �Ƃ�����j
�E�^�C�}�[�J�E���^�͂����ł͐i�߂���CPU�Ƃ͖��֌W�Ői�߂�悤�ɂ����B
�E�]�����ߒ��ɂ��ACPU�ȊO�̓��삪���񓮍�ł���悤�ɂ����B
�ECPU�̏���T�C�N�����ꕔ�ύX�����B
�E���荞�ݏ������̏���T�C�N������8(HuC6280��BRK�Ɠ���)�ɕύX�����B(���@���m�F)
�ECPU�̏���T�C�N����S����1�����ɂ��郂�[�h�i�^�[�{�T�C�N�����[�h�j��t�����B
  v1.61����I�[�o�[�N���b�N���j���[�Ɠ������A�����̎�ނ𑝂₵���B
�EPSG�������V���v���ɂ�������_ClockUpCount��s�v�Ƃ����B
�E�X�e�[�g�Z�[�u����_ClockCount��_ClockElapsed���Z�[�u����悤�ɂ����B
�E�킩��ɂ����Ȃ�Ȃ��͈͓��ŃT�u���[�`�����������炵�č����������Bv0.93
�Eread(),write()�֐����}�N�������邱�Ƃō����������Bv1.07
�E�ϐ��ւ̑���������ł��邾�����炷���Ƃō����������Bv1.08
�E�[���y�[�W�������ւ̃A�N�Z�X���K�����C��������($F8�o���N)�Ɍ���Ȃ�(Ki����
  ��̏��)���Ƃ֑Ή������Bv1.29
�E�悭�g���閽�ߌQ���ɋL�q���邱�Ƃō����������Bv1.30
�E����N���b�N�ŁA�]�����߂�TIA��TAI�݂̂�6�T�C�N��(�l�b�g��̎����ł悭������
  �l�Ă���)�Ƃ����B�O�L�Q���߂����������V���v����TII,TDD,TIN��5�T�C�N��(VDC
  �̃A�N�Z�X�E�F�C�g�������6�T�C�N��)�Ƃ����B���@�ł̑���͂��Ă��Ȃ����A�Q
  �[���̓���������Ƃ��̎��������@�ɍł��߂��������Bv1.30
�E���荞�ݏ����̍ۂɁAIF�̏�Ԃ͖��ߎ��s�O�̏��(prevIF)������悤�ɂ����B�W��
  �b�N�j�N���E�X�S���t(Hu�J�[�h��)�ŁA��ʍ��������X����Ă�����肪���������B
  v1.61

Copyright(C)2006-2013 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[CPU.c]

		Implements a HuC6280 Emulator.

	Copyright (C) 2004-2005 Ki

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
******************************************************************************/
#include "CPU.h"
#include "MainBoard.h"
#include "Printf.h"
#include "Debug.h"
#include "App.h"

Sint32 gCPU_ClockCount = 0; //v2.00�ǉ��B�������̂��߃J�E���^���O���[�o�����B
Sint32 gCPU_Transfer;		//v2.31�X�V�B�������̂��߃J�E���^���O���[�o�����B

static Uint8		_A;
static Uint8		_X;
static Uint8		_Y;
static Uint8		_S;
static Uint8		_P;
static Uint16		_PC;

static Uint8		_CF;
static Uint8		_ZF;
static Uint8		_IF;
static Uint8		_PrevIF; //Kitao�ǉ��B���ߊJ�n�O��I�t���O��ۊǂ��Ă����B���ߌ�̊��荞�ݏ��������邩�ǂ����̔��f�ɂ͂���(���ߎ��s�O�̏��)���g����Bv1.61
static Uint8		_DF;
static Uint8		_BF;
static Uint8		_TF;
static Uint8		_VF;
static Uint8		_NF;

static Uint32		_MPR[8];

static Sint32		_ClockElapsed; //v1.61����N���b�N����p�Ƃ��Ă͔�g�p�B�f�o�b�O���Ɍ��݂̖��ߏ���T�C�N���������ϐ��Ƃ��Ďg�p�B
static BOOL			_bSpeedLow; //Kitao�ǉ��BLowSpeed���[�h�iCSL���ߌ�j�̂Ƃ���TRUE�B

static Uint16		_TransferSrcAddr; //Kitao�ǉ�
static Uint16		_TransferDstAddr; //Kitao�ǉ�
static Uint16		_TransferLength; //Kitao�ǉ�
static BOOL			_TransferIncDec; //Kitao�ǉ��BTRUE�Ȃ�C���N�������g

static BOOL			_bRDY;		// DMA�v�� 
static BOOL			_bNMI;
static BOOL			_bIRQ1;
static BOOL			_bIRQ2;
static BOOL			_bTIRQ;
static BOOL			_bPrevIRQ1; //Kitao�ǉ��BPrevIF�Ƌ���IRQ�̏�Ԃ��A���ߊJ�n�O�̏�Ԃ��g����̂ŁA�����ۊǂ��Ă����Bv1.61
static BOOL			_bPrevIRQ2; //
static BOOL			_bPrevTIRQ; //
static Uint8		_IntDisable; //Kitao�ǉ�
static Uint8		_PrevIntDisable; //Kitao�ǉ��BPrevIF�Ƌ��Ɋ��荞�݂̋֎~��Ԃ��A���ߊJ�n�O�̏�Ԃ��g����̂ŁA�����ۊǂ��Ă����Bv1.61

static Sint32		_SelectVDC; //Kitao�ǉ��B�X�[�p�[�O���t�B�b�N�X�p

static BOOL			_bDebug = FALSE; //Kitao�ǉ��Bv1.07
static Uint32		_OpCode = 0; //Kitao�ǉ��Bv1.07
static Uint16		_PrevPC = 0; //Kitao�ǉ��Bv1.07
static Uint8		_PrevFlags = 0; //Kitao�ǉ��Bv1.07


// �ǂݏo���֐� 
static Uint8 (*ReadMem)(Uint32 mpr, Uint32 addr); //Kitao�X�V�Bv1.47

// �������݊֐� 
static void (*WriteMem)(Uint32 mpr, Uint32 addr, Uint8 data); //Kitao�X�V�Bv1.47


static Sint32	_CycleTableBase[256] =
{
//Kitao�X�V
//  PLP(28),PLA(68)��4�T�C�N������ɂ����B�l�N���X��OP�f�������@�Ɠ����^�C�~���O�ɂȂ�B�_�u���h���S��II��OP�f���ŕK�v�Bv1.61,v2.51�X�V
//  PHP(08)��4�T�C�N������ɂ����B�l�N���X��OP�f�������@�Ɠ����^�C�~���O�ɂȂ�B�T�U���A�C�YOP�������@�ɋ߂��Bv2.07�X�V
//  �T�C�N���ύX�����ӏ��͎��@�ł����l���͖��m�F�ł��B
//	0 1 2  3 4 5 6 7 8 9 A B C D E F ��Lo��Hi
	8,7,3, 4,6,4,6,7,4,2,2,2,7,5,7,6, //0
	2,7,7, 4,6,4,6,7,2,5,2,2,7,5,7,6, //1
	7,7,3, 4,4,4,6,7,4,2,2,2,5,5,7,6, //2
	2,7,7, 2,4,4,6,7,2,5,2,2,5,5,7,6, //3
	7,7,3, 4,7,4,6,7,3,2,2,2,4,5,7,6, //4  Kitao�X�V�B�R�[�h44(BSR)�̒l��ύX�B�W�����v���̃T�C�N���ƍ��킹��ƍ��v7�ɁB
	2,7,7, 5,2,4,6,7,2,5,3,2,2,5,7,6, //5  Kitao�X�V�B�R�[�h53(TAMi)�̒l��ύX�B�I�[�����N�G�X�g�̃^�C�g����ʂŕK�v�B�R�[�h54(CSL)�̒l��ύX�BKi���񂩂�̊m���Ȏ������ɂ��High��Low�̂Ƃ���9�T�C�N��(7.159090MHz���Z)�BLow��Low�̏ꍇ������̂ł����ł�2�T�C�N���̒l�ɂ��Ă����B�o�C�I�����g�\���W���[OK�B
	7,7,2, 2,4,4,6,7,4,2,2,2,7,5,7,6, //6
	2,7,7,17,4,4,6,7,2,5,4,2,7,5,7,6, //7  Kitao�ǋL�B�R�[�h7A(PLY)��3�ɂ���ƁA�_�u���h���S���Q��OP�f���ł����p�N������Ȃ��Bv2.55
	4,7,2, 7,4,4,4,7,2,2,2,2,5,5,5,6, //8  Kitao�X�V�B�R�[�h80(BRA)�̒l��ύX�B�W�����v���̃T�C�N���ƍ��킹��ƍ��v4�ɁB3���ƃ{���o�[�}��'93�̃X�^�[�g�f���łP�t���[������B
	2,7,7, 8,4,4,4,7,2,5,2,2,5,5,5,6, //9
	2,7,2, 7,4,4,4,7,2,2,2,2,5,5,5,6, //A
	2,7,7, 8,4,4,4,7,2,5,2,2,5,5,5,6, //B
	2,7,2,17,4,4,6,7,2,2,2,2,5,5,7,6, //C
	2,7,7,17,2,4,6,7,2,5,3,2,2,5,7,6, //D  Kitao�X�V�B�R�[�hD4(CSH)�̒l��ύX�BKi���񂩂�̊m���Ȏ������ɂ��Low��High�̂Ƃ���6�T�C�N��(7.159090MHz���Z)�BHigh��High�̏ꍇ������̂ł����ł�2�T�C�N���̒l�ɂ��Ă����B�o�C�I�����g�\���W���[OK�B
	2,7,2,17,4,4,6,7,2,2,2,2,5,5,7,6, //E
	2,7,7,17,2,4,6,7,2,5,3,2,2,5,7,6  //F  Kitao�ǋL�B�R�[�hFA(PLX)��4�ɂ���ƁA���[�h�����i�[(�p�b�N�C���r�f�I��)�X�^�[�g���ɂ������Bv2.51
};
static Sint32	_CycleTableSlow[256];
static Sint32	_CycleTableTurbo1[256];
static Sint32	_CycleTableTurbo2[256];
static Sint32*	_pCycleTable; //v1.61�X�V


//Kitao�ǉ��Bv1.61
//�ᑬ���샂�[�h(CLS����)�̐ݒ������B�ᑬ�ɐ؂�ւ���Ȃ�TRUE�C�ʏ퍂�����[�h�ɖ߂��Ȃ�FALSE�ŌĂԁB
static inline void
SetSpeedLow(
	BOOL	bSpeedLow)
{
	_bSpeedLow = bSpeedLow;
	if (VDC_GetOverClockType() < 100) //�^�[�{�T�C�N�����[�h�̂Ƃ��͂��̂܂܁B����ȊO�̃��[�h�Ȃ�
	{
		if (_bSpeedLow)
			_pCycleTable = &_CycleTableSlow[0]; //LowSpeed���[�h�iCSL���ߌ�j�̂Ƃ��͂S�{�̃T�C�N�������|����
		else//�ʏ퍂�����[�h��
			_pCycleTable = &_CycleTableBase[0];
	}
}

//Kitao�ǉ��Bv1.61
void
CPU_SetTurboCycle(
	Sint32	n)
{
	switch (n)
	{
		case 100: _pCycleTable = &_CycleTableTurbo1[0]; break; //�^�[�{�P�{
		case 200: _pCycleTable = &_CycleTableTurbo2[0]; break; //�^�[�{�Q�{
		case 300: _pCycleTable = &_CycleTableTurbo2[0]; break; //�^�[�{�R�{�B�Q�{�Ɠ��������A����ɉ�����VDC.c�ŃI�[�o�[�N���b�N����B
		default: //0
			SetSpeedLow(_bSpeedLow);
	}
}


//Kitao�ǉ��BPrevIF(���ߎ��s�O�̃t���O��ԂŎ��ۂ̔��f�Ɏg����l)���X�V����Bv1.61
static inline void
refreshPrevIF()
{
	_PrevIF = _IF;
	_bPrevIRQ1 = _bIRQ1;
	_bPrevIRQ2 = _bIRQ2;
	_bPrevTIRQ = _bTIRQ;
	_PrevIntDisable = _IntDisable;
}


/*-----------------------------------------------------------------------------
** Implement memory read/write stages
**---------------------------------------------------------------------------*/
//Kitao�X�V�Bread()��write()�֐����A�������̂��߃T�u���[�`���łȂ��}�N���������Bv1.07
//			 ���}�N����`�Ȃ̂�READ(),WRITE(),READZP(),WRITEZP()�ȊO�̊֐�(READINC()�Ȃ�)�́A�J�b�R���≉�Z�����ɂ͋L�q�ł��Ȃ��B
//			 ���}�N����`�Ȃ̂ň�����addr�ɏd���Ȃ�֐��≉�Z�q�͏����Ȃ��悤�ɂ���B
#define READ(addr)		ReadMem(_MPR[(addr) >> 13], ((addr) & 0x1FFF))
#define READINC(addr)	ReadMem(_MPR[(addr) >> 13], ((addr) & 0x1FFF)); addr++ //�C���N�������g�p
#define READINC_X(addr)	ReadMem(_MPR[(addr) >> 13], ((addr) & 0x1FFF)) + _X; addr++ //+_X���C���N�������g�p
#define READINC_Y(addr)	ReadMem(_MPR[(addr) >> 13], ((addr) & 0x1FFF)) + _Y; addr++ //+_Y���C���N�������g�p
#define READDEC(addr)	ReadMem(_MPR[(addr) >> 13], ((addr) & 0x1FFF)); addr-- //�f�N�������g�p�B�]�����ߎ��Ɏg�p�B
#define READZP(addr)	ReadMem(_MPR[1], addr) //�[���y�[�W�p
#define WRITE(addr,data)	WriteMem(_MPR[(addr) >> 13], ((addr) & 0x1FFF), data)
#define WRITEINC(addr,data)	WriteMem(_MPR[(addr) >> 13], ((addr) & 0x1FFF), data); addr++ //�C���N�������g�p
#define WRITEDEC(addr,data)	WriteMem(_MPR[(addr) >> 13], ((addr) & 0x1FFF), data); addr-- //�f�N�������g�p
#define WRITEZP(addr,data)	WriteMem(_MPR[1], addr, data) //�[���y�[�W�p


/*-----------------------------------------------------------------------------
** ($ZP)
*/
//Kitao�X�V�B�[���y�[�W�A�N�Z�X�̍ۂɁAMPR1�̒l�ɂ����$F8(���C��RAM)�ȊO�̃o���N�ɂ��A�N�Z�X�ł���悤�ɂ����B
//			 Ki���񂩂�������������܂����Bv1.29
static inline Uint16
fetchZpIndirect()
{
	Uint8	zpAddress;
	Uint16	low;

	zpAddress = ReadMem(_MPR[_PC >> 13], (_PC & 0x1FFF));
	_PC++;
	low = ReadMem(_MPR[1], zpAddress++);
	return ((READZP(zpAddress) << 8) | low);
}

/*-----------------------------------------------------------------------------
** ($ZP,X)
*/
//Kitao�X�V�Bv1.29
static inline Uint16
fetchZpIndexIndirect()
{
	Uint8	zpAddress;
	Uint16	low;

	zpAddress = ReadMem(_MPR[_PC >> 13], (_PC & 0x1FFF)) + _X;
	_PC++;
	low = ReadMem(_MPR[1], zpAddress++);
	return ((READZP(zpAddress) << 8) | low);
}

/*-----------------------------------------------------------------------------
** ($ZP),Y
*/
//Kitao�X�V�Bv1.29
static inline Uint16
fetchZpIndirectIndex()
{
	Uint8	zpAddress;
	Uint16	low;

	zpAddress = ReadMem(_MPR[_PC >> 13], (_PC & 0x1FFF));
	_PC++;
	low = ReadMem(_MPR[1], zpAddress++);
	return ((READZP(zpAddress) << 8) | low) + _Y;
}

/*-----------------------------------------------------------------------------
** $ABS
*/
//Kitao�X�V�Bv1.07
static inline Uint16
fetchAbs()
{
	Uint16	low;
	Uint16	high;

	low = ReadMem(_MPR[_PC >> 13], (_PC & 0x1FFF));
	_PC++;
	high = ReadMem(_MPR[_PC >> 13], (_PC & 0x1FFF));
	_PC++;
	return ((high << 8) | low);
}

/*-----------------------------------------------------------------------------
** $ABS,X
*/
//Kitao�X�V�Bv1.07
static inline Uint16
fetchAbsX()
{
	Uint16	low;
	Uint16	high;

	low = ReadMem(_MPR[_PC >> 13], (_PC & 0x1FFF));
	_PC++;
	high = ReadMem(_MPR[_PC >> 13], (_PC & 0x1FFF));
	_PC++;
	return ((high << 8) | low) + _X;
}

/*-----------------------------------------------------------------------------
** $ABS,Y
*/
//Kitao�X�V�Bv1.07
static inline Uint16
fetchAbsY()
{
	Uint16	low;
	Uint16	high;

	low = ReadMem(_MPR[_PC >> 13], (_PC & 0x1FFF));
	_PC++;
	high = ReadMem(_MPR[_PC >> 13], (_PC & 0x1FFF));
	_PC++;
	return ((high << 8) | low) + _Y;
}

/*-----------------------------------------------------------------------------
** ($ABS)
*/
//Kitao�X�V�Bv1.08
static inline Uint16
fetchAbsIndirect()
{
	Uint16	absAddr = fetchAbs();
	Uint16	low  = READINC(absAddr);
	return ((READ(absAddr) << 8) | low);
}

/*-----------------------------------------------------------------------------
** ($ABS,X)
*/
//Kitao�X�V�Bv1.08
static inline Uint16
fetchAbsIndirectX()
{
	Uint16	absAddr = fetchAbs() + _X;
	Uint16	low  = READINC(absAddr);
	return ((READ(absAddr) << 8) | low);
}


/*-----------------------------------------------------------------------------
** Implement stack operations
**---------------------------------------------------------------------------*/
static inline void
push(
	Uint8	reg8)
{
	WriteMem(_MPR[1], (0x100 | (_S--)), reg8);
}

static inline Uint8
pull()
{
	return ReadMem(_MPR[1], (0x100 | (++_S)));
}


/*-----------------------------------------------------------------------------
** Implement flag operations
** The idea is taken from nes6502.c by Matthew Conte.
**
** CF --- use CPU_CF (D0)
** ZF --- use 8-bit value
** IF --- use CPU_IF (D2)
** DF --- use CPU_DF (D3)
** BF --- use CPU_BF (D4)
** TF --- use CPU_TF (D5)
** VF --- use CPU_VF (D6)
** NF --- use 8-bit value
**---------------------------------------------------------------------------*/
static inline void
updateFlagZN(
	Uint8	val)
{
	_NF = _ZF = val;
}

static inline void
separateFlags(
	Uint8	p)
{
	_CF = p & CPU_CF;
	_ZF = ~(p >> 1) & 1;
	_IF = p & CPU_IF;
	_DF = p & CPU_DF;
	_BF = p & CPU_BF;
	_TF = p & CPU_TF;
	_VF = p;
	_NF = p;
}

static inline Uint8
gatherFlags()
{
	return _CF | ((_ZF==0)<<1) | _IF | _DF | _BF | _TF | (_VF&CPU_VF) | (_NF&CPU_NF);
}


/*-----------------------------------------------------------------------------
** Implement instruction execute stages
**---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
** BIT
*/
static inline void
bit(Uint8		val)
{
	_ZF = _A & val;
	_VF = _NF = val;
}

/*-----------------------------------------------------------------------------
** ADC
*/
static inline void
adc(Uint8		val)
{
	Uint32	lo;
	Uint32	hi;
	Uint32	sum;

	if (_DF)
	{
		//Kitao�X�V�B�l�����܂�������Ȃ����Ƃ��������s����C�������B�p���[���[�O�R�̃z�[�����������Ŕ����B
		lo = (_A & 0x0F) + (val & 0x0F) + _CF;
		hi = (_A & 0xF0) + (val & 0xF0);
		if (lo > 0x09)
		{
			hi += 0x10;
			lo += 0x06;
		}
		_VF = (Uint8)((~(_A^val) & (_A^hi) & CPU_NF) >> 1);
		if (hi > 0x90)
			hi += 0x60;
		_CF = (Uint8)((hi & 0x100) >> 8);
		updateFlagZN(_A = (Uint8)((lo & 0x0F) + (hi & 0xF0))); //Kitao�X�V�B�[���t���O���l�K�e�B�u�t���O���X�V����B
		gCPU_ClockCount--;
	}
	else
	{
		sum = _A + val + _CF;
		_VF = (Uint8)((~(_A^val) & (_A^sum) & CPU_NF) >> 1);
		_CF = (Uint8)((sum & 0x100) >> 8);
		updateFlagZN(_A = (Uint8)sum);
	}
}

/*-----------------------------------------------------------------------------
** ADC with T-flag set
*/
static inline void
adc_t(Uint8		val)
{
	Uint8	M = READZP(_X);
	Uint32	lo;
	Uint32	hi;
	Uint32	sum;

	if (_DF)
	{
		//Kitao�X�V�B�l�����܂�������Ȃ����Ƃ��������s����C�������B�p���[���[�O�R�̃z�[�����������Ŕ����B
		lo = (M & 0x0F) + (val & 0x0F) + _CF;
		hi = (M & 0xF0) + (val & 0xF0);
		if (lo > 0x09)
		{
			hi += 0x10;
			lo += 0x06;
		}
		_VF = (Uint8)((~(M^val) & (M^hi) & CPU_NF) >> 1);
		if (hi > 0x90)
			hi += 0x60;
		_CF = (Uint8)((hi & 0x100) >> 8);
		updateFlagZN(M = (Uint8)((lo & 0x0F) + (hi & 0xF0))); //Kitao�X�V�B�[���t���O���l�K�e�B�u�t���O���X�V����B
		gCPU_ClockCount -= 4; //v0.83�X�V�B3�T�C�N������(Ki���񂩂�m���Ȏ������)�B-1��D�t���O�Ԃ�
	}
	else
	{
		sum = M + val + _CF;
		_VF = (Uint8)((~(M^val) & (M^sum) & CPU_NF) >> 1);
		_CF = (Uint8)((sum & 0x100) >> 8);
		updateFlagZN(M = (Uint8)sum);
		gCPU_ClockCount -= 3; //v0.83�X�V�B3�T�C�N������(Ki���񂩂�m���Ȏ������)�B
	}
	WRITEZP(_X, M);
}

/*-----------------------------------------------------------------------------
** SBC
*/
static inline void
sbc(Uint8		val)
{
	Uint32	flagC = (~_CF) & CPU_CF; // D0  v1.67�X�VUint32��(�����炭�킸���ɍ�����)�B
	Uint32	temp = _A - val - flagC;
	Uint32	lo;
	Uint32	hi;

	if (_DF)
	{
		lo = (_A & 0x0F) - (val & 0x0F) - flagC;
		hi = (_A >> 4) - (val >> 4) - ((lo & 0x10) == 0x10);
		if (lo & 0x10)
			lo -= 6;
		if (hi & 0x10)
			hi -= 6;
		_CF = (Uint8)((~hi & 0x10) >> 4);
		_VF = (Uint8)(((_A ^ temp) & (_A ^ val) & CPU_NF) >> 1);
		updateFlagZN(_A = (Uint8)((lo & 0x0F) | (hi << 4)));
		gCPU_ClockCount--;
	}
	else
	{
		_CF = (Uint8)((~temp & 0x100) >> 8);
		_VF = (Uint8)(((_A ^ temp) & (_A ^ val) & CPU_NF) >> 1);
		updateFlagZN(_A = (Uint8)temp);
	}
}

/*-----------------------------------------------------------------------------
** AND
*/
static inline void
and(Uint8		val)
{
	_A &= val;
	updateFlagZN(_A);
}

/*-----------------------------------------------------------------------------
** AND with T-flag set
*/
static inline void
and_t(Uint8		val)
{
	Uint8 M = READZP(_X) & val;
	updateFlagZN(M);
	WRITEZP(_X, M);
	gCPU_ClockCount -= 3; //v0.83�X�V�B3�T�C�N������(Ki���񂩂�m���Ȏ������)�B
}

/*-----------------------------------------------------------------------------
** ASL
*/
static inline Uint8
asl(Uint8		val)
{
	_CF = val >> 7; //Kitao�X�V�Bv1.07
	updateFlagZN(val = val << 1); //Kitao�X�V�Bv1.07
	return val;
}

/*-----------------------------------------------------------------------------
** LSR
*/
static inline Uint8
lsr(Uint8		val)
{
	_CF = val & CPU_CF;	// bit0
	updateFlagZN(val = val >> 1); //Kitao�X�V�Bv1.07
	return val;
}

/*-----------------------------------------------------------------------------
** ROL
*/
static inline Uint8
rol(Uint8		val)
{
	Uint8 oldFlagC = _CF; // bit0
	_CF = val >> 7; //Kitao�X�V�Bv1.07
	updateFlagZN(val = (val << 1) | oldFlagC);
	return val;
}

/*-----------------------------------------------------------------------------
** ROR
*/
static inline Uint8
ror(Uint8		val)
{
	Uint8 oldFlagC = _CF << 7;
	_CF = val & CPU_CF;
	updateFlagZN(val = (val >> 1) | oldFlagC);
	return val;
}

/*-----------------------------------------------------------------------------
** CMP
*/
static inline void
cmp(Uint8		val)
{
	Uint32 temp = _A - val;

	updateFlagZN((Uint8)temp);
	_CF = (Uint8)((~temp & 0x100) >> 8);
}

/*-----------------------------------------------------------------------------
** CPX
*/
static inline void
cpx(Uint8		val)
{
	Uint32 temp = _X - val;

	updateFlagZN((Uint8)temp);
	_CF = (Uint8)((~temp & 0x100) >> 8);
}

/*-----------------------------------------------------------------------------
** CPY
*/
static inline void
cpy(Uint8		val)
{
	Uint32 temp = _Y - val;

	updateFlagZN((Uint8)temp);
	_CF = (Uint8)((~temp & 0x100) >> 8);
}

/*-----------------------------------------------------------------------------
** EOR
*/
static inline void
eor(Uint8		val)
{
	_A ^= val;
	updateFlagZN(_A);
}

/*-----------------------------------------------------------------------------
** EOR with T-flag set
*/
static inline void
eor_t(Uint8		val)
{
	Uint8 M = READZP(_X) ^ val;
	updateFlagZN(M);
	WRITEZP(_X, M);
	gCPU_ClockCount -= 3; //v0.83�X�V�B3�T�C�N������(Ki���񂩂�m���Ȏ������)�B
}

/*-----------------------------------------------------------------------------
** ORA
*/
static inline void
ora(Uint8		val)
{
	_A |= val;
	updateFlagZN(_A);
}

/*-----------------------------------------------------------------------------
** ORA with T-flag set
*/
static inline void
ora_t(Uint8		val)
{
	Uint8 M = READZP(_X) | val;
	updateFlagZN(M);
	WRITEZP(_X, M);
	gCPU_ClockCount -= 3; //v0.83�X�V�B3�T�C�N������(Ki���񂩂�m���Ȏ������)�B
}

/*-----------------------------------------------------------------------------
** LDA
*/
static inline void
lda(Uint8		val)
{
	_A = _NF = _ZF = val; //v1.47�X�V
}

/*-----------------------------------------------------------------------------
** LDX
*/
static inline void
ldx(Uint8		val)
{
	_X = _NF = _ZF = val; //v1.47�X�V
}

/*-----------------------------------------------------------------------------
** LDY
*/
static inline void
ldy(Uint8		val)
{
	_Y = _NF = _ZF = val; //v1.47�X�V
}

/*-----------------------------------------------------------------------------
** TAX
*/
static inline void
tax()
{
	_X = _A;
	updateFlagZN(_X);
}

/*-----------------------------------------------------------------------------
** TAY
*/
static inline void
tay()
{
	_Y = _A;
	updateFlagZN(_Y);
}

/*-----------------------------------------------------------------------------
** TXA
*/
static inline void
txa()
{
	_A = _X;
	updateFlagZN(_A);
}

/*-----------------------------------------------------------------------------
** TYA
*/
static inline void
tya()
{
	_A = _Y;
	updateFlagZN(_A);
}

/*-----------------------------------------------------------------------------
** TSX
*/
static inline void
tsx()
{
	_X = _S;
	updateFlagZN(_X);
}

/*-----------------------------------------------------------------------------
** BBRi (Branch on Bit Reset)
*/
static inline void
BBRi(const Uint8 bit)
{
	Uint8 addr8;
	Sint8 rel8;

	addr8 = READINC(_PC);
	rel8 = (Sint8)READINC(_PC);
	if ((READZP(addr8) & bit) == 0) //v1.29�X�V
	{
		gCPU_ClockCount--;
		gCPU_ClockCount--;
		_PC += (Sint16)rel8;
	}
}

/*-----------------------------------------------------------------------------
** BBSi (Branch on Bit Set)
*/
static inline void
BBSi(const Uint8 bit)
{
	Uint8 addr8;
	Sint8 rel8;

	addr8 = READINC(_PC);
	rel8 = (Sint8)READINC(_PC);
	if (READZP(addr8) & bit) //v1.29�X�V
	{
		gCPU_ClockCount--;
		gCPU_ClockCount--;
		_PC += (Sint16)rel8;
	}
}

/*-----------------------------------------------------------------------------
** TRB
*/
static inline Uint8
trb(Uint8		val)
{
	Uint8	M = ~_A & val;

	_VF = _NF = val;
	_ZF = M;
	return M;
}

/*-----------------------------------------------------------------------------
** TSB
*/
static inline Uint8
tsb(Uint8		val)
{
	Uint8	M = _A | val;

	_VF = _NF = val;
	_ZF = M;
	return M;
}

/*-----------------------------------------------------------------------------
** TST
*/
static inline void
tst(Uint8 imm, Uint8 M)
{
	_VF = _NF = M;
	_ZF = M & imm;
}

/*-----------------------------------------------------------------------------
** RMBi (Reset Memory Bit)
*/
static inline void
RMBi(Uint8 zp, Uint8 bit)
{
	WRITEZP(zp, READZP(zp) & (~bit));
}

/*-----------------------------------------------------------------------------
** SMBi (Set Memory Bit)
*/
static inline void
SMBi(Uint8 zp, Uint8 bit)
{
	WRITEZP(zp, READZP(zp) | bit);
}


/*-----------------------------------------------------------------------------
** Check for pending NMI / TIMER / IRQ1 / IRQ2
*/
//Kitao�X�V�B���X�^���荞�݃^�C�~���O(IRQ1)���d�����邽�߁A���荞�݂̗D�揇�ʂ��t���Ƃ����B
static inline void
fetchInterrupt()
{
	if (_PrevIF == 0) //v1.61�X�V�B���ߌ�̊��荞�ݏ��������邩�ǂ����̔��f�́A���ߎ��s�O��I�t���O�̏�Ԃ��g����B
	{
		if ((_bPrevIRQ2)&&((_PrevIntDisable & INTCTRL_IRQ2) == 0)) //v1.61�X�V�BPrevIF���l�ɁA���ߎ��s�O�̊��荞�݋֎~��Ԃ��g����B
		{
			INTCTRL_Cancel(INTCTRL_IRQ2); //Kitao�ǉ�

			push(_PC >> 8);
			push(_PC & 0xFF);

			_BF = 0;
			push(gatherFlags());

			_IF = CPU_IF;
			refreshPrevIF(); //v1.61�ǉ�
			_TF = _DF = 0;
			_PC  = READ(CPU_IRQ2VECTOR);
			_PC |= READ(CPU_IRQ2VECTOR + 1) << 8;
			gCPU_ClockCount -= 8; //Kitao�X�V�BHuC6280��BRK�ɍ��킹��8�T�C�N���Ƃ����B
			return; //Kitao�ǉ�
		}
		
		if ((_bPrevIRQ1)&&((_PrevIntDisable & INTCTRL_IRQ1) == 0))
		{
			INTCTRL_Cancel(INTCTRL_IRQ1); //Kitao�ǉ�

			push(_PC >> 8);
			push(_PC & 0xFF);

			_BF = 0;
			push(gatherFlags());

			_IF = CPU_IF;
			refreshPrevIF(); //v1.61�ǉ�
			_TF = _DF = 0;
			_PC  = READ(CPU_IRQ1VECTOR);
			_PC |= READ(CPU_IRQ1VECTOR + 1) << 8;
			gCPU_ClockCount -= 8; //Kitao�X�V�BHuC6280��BRK�ɍ��킹��8�T�C�N���Ƃ����B
			return; //Kitao�ǉ�
		}
		
		if ((_bPrevTIRQ)&&((_PrevIntDisable & INTCTRL_TIRQ) == 0))
		{
			INTCTRL_Cancel(INTCTRL_TIRQ); //Kitao�ǉ��B�N���X���C�o�[�ŕK�v�B

			push(_PC >> 8);
			push(_PC & 0xFF);

			_BF = 0;
			push(gatherFlags());

			_IF = CPU_IF;
			refreshPrevIF(); //v1.61�ǉ�
			_TF = _DF = 0;
			_PC  = READ(CPU_TIMERVECTOR);
			_PC |= READ(CPU_TIMERVECTOR + 1) << 8;
			gCPU_ClockCount -= 8; //Kitao�X�V�BHuC6280��BRK�ɍ��킹��8�T�C�N���Ƃ����B
			return; //Kitao�ǉ�
		}
	}

/*	if (_bNMI) //Kitao�X�V�B���݃G�~�����[�^��ł͖��g�p
	{
		push(_PC >> 8);
		push(_PC & 0xFF);

		// B �t���O�̓N���A���ꂽ��ɃX�^�b�N�֑ޔ������B
		_BF = 0;
		push(gatherFlags());

		_IF = CPU_IF;
		refreshPrevIF(); //v1.61�ǉ�
		_TF = _DF = 0;
		_PC  = READ(CPU_NMIVECTOR);
		_PC |= READ(CPU_NMIVECTOR + 1) << 8;
		gCPU_ClockCount -= 8; //Kitao�X�V�BHuC6280��BRK�ɍ��킹��8�T�C�N���Ƃ����B
	}
*/
}


/******************************************************************************
**							   ���O�����J�֐�
******************************************************************************/


/*-----------------------------------------------------------------------------
** [CPU_SetReadFunction]
**	 �o���N���Ƃ̃��[�h�֐���o�^���܂��B(�K�{)
**---------------------------------------------------------------------------*/
void
CPU_SetReadFunction(Uint8 (*RdFunc)(Uint32, Uint32)) //Kitao�X�V�B�}�b�s���O���W�X�^�ƃA�h���X���ʂɎ󂯎��悤�ɂ��č������Bv1.47
{
	ReadMem = RdFunc;
}

/*-----------------------------------------------------------------------------
** [CPU_SetWriteFunction]
**	 �o���N���Ƃ̃��C�g�֐���o�^���܂��B(�K�{)
**---------------------------------------------------------------------------*/
void
CPU_SetWriteFunction(void (*WrFunc)(Uint32, Uint32, Uint8)) //Kitao�X�V�B�}�b�s���O���W�X�^�ƃA�h���X���ʂɎ󂯎��悤�ɂ��č������Bv1.47
{
	WriteMem = WrFunc;
}


/*-----------------------------------------------------------------------------
** [Reset]
** �b�o�t�R�A�����Z�b�g���܂��B����N���b�N����Ԃ��܂��B
**---------------------------------------------------------------------------*/
Sint32
CPU_Reset()
{
	int		i;

	for (i=0; i<256; i++)
	{
		_CycleTableSlow[i] = _CycleTableBase[i] << 2; //LowSpeed���[�h�iCSL���ߌ�j�̂Ƃ��͂S�{�̃T�C�N�������|����
		_CycleTableTurbo1[i] = 2; //Ootake�Ǝ���Turbo���[�h1�̂Ƃ��͑S�Ă̖��ߎ��s��2�T�C�N���Ƃ���B
		_CycleTableTurbo2[i] = 1; //Ootake�Ǝ���Turbo���[�h2�̂Ƃ��͑S�Ă̖��ߎ��s��1�T�C�N���Ƃ���(v1.60�ȑO�̃^�[�{�T�C�N��)�B
	}
	SetSpeedLow(FALSE); //Kitao�ǉ�
	gCPU_Transfer = 0; //Kitao�ǉ�

	//Kitao�ǉ�
	_bRDY = FALSE;
	_bIRQ1 = FALSE;
	_bIRQ2 = FALSE;
	_bTIRQ = FALSE;
	_bNMI = FALSE;
	_IntDisable = 0;

	//Kitao�ǉ��B�O�̂��߂ɓd���ē������͑S�t���O��������
	_CF = 0;
	_ZF = 0;
	_IF = CPU_IF; //v1.61�X�V
	refreshPrevIF(); //v1.61�ǉ��B_bPrevIRQx,_PrevIntDisable���X�V�����B
	_DF = 0;
	_BF = 0;
	_TF = 0;
	_VF = 0;
	_NF = 0;

	ZeroMemory(_MPR, sizeof(_MPR)); //Kitao�X�V�B�O�̂��߂ɓd���ē������̓}�b�s���O���W�X�^���S�ď������B

	//Kitao�ǉ��B�O�̂��߂ɓd���ē������͑S�t���O��������
	_A = 0;
	_X = 0;
	_Y = 0;
	_S = 0;
	_P = 0;
	_PC = READ(CPU_RESETVECTOR);
	_PC |= READ(CPU_RESETVECTOR + 1) << 8;

	//Kitao�ǉ��B�X�[�p�[�O���t�B�b�N�X�p
	_SelectVDC = 0;

	gCPU_ClockCount = -6;
	_ClockElapsed = 0;

	return 6;
}


/*-----------------------------------------------------------------------------
** [CPU_ActivateRDY]
**	 �c�l�`�v�����q�c�x���A�N�e�B�u�ɂ��܂��B
**---------------------------------------------------------------------------*/
void
CPU_ActivateRDY()
{
	_bRDY = TRUE;
}

/*-----------------------------------------------------------------------------
** [CPU_ActivateNMI]
**	 �����ݓ��͐��m�l�h���A�N�e�B�u�ɂ��܂��B
**---------------------------------------------------------------------------*/
void
CPU_ActivateNMI()
{
	_bNMI = TRUE;
}

/*-----------------------------------------------------------------------------
** [CPU_ActivateTIMER]
**	 �^�C�}�[�����ݗv�����s�h�l�d�q���A�N�e�B�u�ɂ��܂��B
**---------------------------------------------------------------------------*/
void
CPU_ActivateTIMER()
{
	_bTIRQ = TRUE;
}

/*-----------------------------------------------------------------------------
** [CPU_ActivateIRQ1]
**	 �����ݓ��͐��h�q�p�P���A�N�e�B�u�ɂ��܂��B
**---------------------------------------------------------------------------*/
void
CPU_ActivateIRQ1()
{
	_bIRQ1 = TRUE;
}

/*-----------------------------------------------------------------------------
** [CPU_ActivateIRQ2]
**	 �����ݓ��͐��h�q�p�Q���A�N�e�B�u�ɂ��܂��B
**---------------------------------------------------------------------------*/
void
CPU_ActivateIRQ2()
{
	_bIRQ2 = TRUE;
}

/*-----------------------------------------------------------------------------
** [CPU_InactivateRDY]
**	 �c�l�`�v�����q�c�x�𖳌��ɂ��܂��B
**---------------------------------------------------------------------------*/
void
CPU_InactivateRDY()
{
	_bRDY = FALSE;
}

/*-----------------------------------------------------------------------------
** [CPU_InactivateNMI]
**	 �����ݓ��͐��m�l�h�𖳌��ɂ��܂��B
**---------------------------------------------------------------------------*/
void
CPU_InactivateNMI()
{
	_bNMI = FALSE;
}

/*-----------------------------------------------------------------------------
** [CPU_InactivateTIMER]
**	 �^�C�}�[�����ݗv�����s�h�l�d�q�𖳌��ɂ��܂��B
**---------------------------------------------------------------------------*/
void
CPU_InactivateTIMER()
{
	_bTIRQ = FALSE;
}

/*-----------------------------------------------------------------------------
** [CPU_InactivateIRQ1]
**	 �����ݓ��͐��h�q�p�P�𖳌��ɂ��܂��B
**---------------------------------------------------------------------------*/
void
CPU_InactivateIRQ1()
{
	_bIRQ1 = FALSE;
}

/*-----------------------------------------------------------------------------
** [CPU_InactivateIRQ2]
**	 �����ݓ��͐��h�q�p�Q�𖳌��ɂ��܂��B
**---------------------------------------------------------------------------*/
void
CPU_InactivateIRQ2()
{
	_bIRQ2 = FALSE;
}


/*-----------------------------------------------------------------------------
** [CPU_Setxx]
**	 ���W�X�^�̒l��ݒ肵�܂��B 
**---------------------------------------------------------------------------*/
void CPU_SetA(Uint8 A) { _A = A; }
void CPU_SetX(Uint8 X) { _X = X; }
void CPU_SetY(Uint8 Y) { _Y = Y; }
void CPU_SetS(Uint8 S) { _S = S; }
void CPU_SetP(Uint8 P) { _P = P; separateFlags(P); }
void CPU_SetPC(Uint16 PC) { _PC = PC; }
void CPU_SetMPR(Sint32 i, Uint32 mpr) { _MPR[i] = mpr; }


/*-----------------------------------------------------------------------------
** [CPU_Getxx]
**	 ���W�X�^�̒l���擾���܂��B 
**---------------------------------------------------------------------------*/
Uint8 CPU_GetA() { return _A; }
Uint8 CPU_GetX() { return _X; }
Uint8 CPU_GetY() { return _Y; }
Uint8 CPU_GetS() { return _S; }
Uint8 CPU_GetP() { _P = gatherFlags(); return _P; }
Uint16 CPU_GetPC() { return _PC; }
Uint32 CPU_GetMPR(Sint32 i) { return _MPR[i]; }


//Kitao�ǉ�
void
CPU_WriteMemory(
	Uint32	addr,
	Uint8	data)
{
	WRITE(addr, data);
}

//Kitao�ǉ�
void
CPU_WriteMemoryZero(
	Uint8	addr,
	Uint8	data)
{
	WRITEZP(addr, data);
}

//Kitao�ǉ�
void
CPU_WriteMemoryMpr(
	Uint32	mpr,
	Uint32	addr,
	Uint8	data,
	BOOL	bContinuous) //���t���[���A�l���X�V��������Ȃ�bContinuous��TRUE�ŌĂԁBv2.39
{
	mpr  &= 0xFF;

	if (APP_GetCDGame())
	{
		if (mpr <= 0x3F)
			MAINBOARD_WriteROM(mpr, (addr & 0x1FFF), data); //ROM�̈�̏ꍇ
		else
			WriteMem(mpr, (addr & 0x1FFF), data);
	}
	else
	{
		if (mpr <= 0x7F)
			MAINBOARD_WriteROM(mpr, (addr & 0x1FFF), data); //ROM�̈�̏ꍇ
		else
			WriteMem(mpr, (addr & 0x1FFF), data);
	}
	
	MAINBOARD_SetContinuousWriteValue(bContinuous, mpr,addr,data); //�������ł�addr���ۂߍ���(&0x1FFF)�O�̂��̂܂܂̃A�h���X�������n��
}


//Kitao�ǉ��B���荞�݋֎~�̐ݒ�
void
CPU_SetIntDisable(
	Uint8	intDisable)
{
	_IntDisable = intDisable;
}


//Kitao�ǉ��B�X�[�p�[�O���t�B�b�N�X�p�BST0,ST1,ST2���߂��ǂ����VDC���A�N�Z�X�Ώۂɂ��邩��ݒ�B
void
CPU_SelectVDC(
	Sint32	selectVDC)	//selectVDC�c0��1
{
	_SelectVDC = selectVDC;
}


//Kitao�ǉ��B�f�o�b�O���[�h�̐ݒ�Bv1.07
void
CPU_SetDebug(
	BOOL	debug)
{
	_bDebug = debug;
}

//Kitao�ǉ��B���ݎ��s���̖��߃R�[�h��Ԃ��B�f�o�b�O�p�Bv1.07
Uint32
CPU_GetOpCode()
{
	return _OpCode;
}

//Kitao�ǉ��B�f�o�b�O�p�Bv1.07
Uint8
CPU_ReadCode(
	Uint16	pc)
{
	return READ(pc);
}

//Kitao�ǉ��B���ݎ��s���̖��߂�_PC��Ԃ��B�f�o�b�O�p�Bv1.07
Uint16
CPU_GetPrevPC()
{
	return _PrevPC;
}

//Kitao�ǉ��B�f�o�b�O�p�Bv1.07
Uint8
CPU_GetPrevFlags()
{
	return _PrevFlags;
}

//Kitao�ǉ��B���ݎ��s���̖��߂̏���N���b�N����Ԃ��BVDC�A�N�Z�X���ɃE�F�C�g�����邩�ǂ����̔��f�Ŏg�p�B�����ݔ�g�p
Sint32
CPU_GetClockElapsed()
{
	return _ClockElapsed;
}


//Kitao�X�V�B�^�C�~���O�����@�ɋ߂Â��邽�߂ɁACSL���߂̎����Ɗ��荞�݊֘A���ύX�����B
//			 ���荞�݃t���O������ʒu��ύX�BCPU_AdvanceClock()����������inline�ɂ��č������Bv1.61�B
void  //v0.94�L�B���ɂ����Ǝv�����傫������Ƃ����inline���Ȃ��ق���PC�̃L���b�V���Ɏ��܂��Ĉ��肵��������ۂĂĂ����B
CPU_ExecuteOperation()
{
	Uint8	ureg8;
	Uint8	addr8;
	Sint8	rel8;
	Uint16	addr16;

	//Kitao�ǉ��B���@�̃^�C�~���O�ɍ��킹�邽�߁A�u���b�N�]����VDC���ƕ���ɓ��삳���悤�ɂ����B
	switch (gCPU_Transfer) //gCPU_Transfer�c1=TII,2=TDD,3=TIN,4=TIA,5=TAI  v1.14�X�V�BgCPU_Transfer�̔�����P�ɂ��č������B
	{
	case 0: //�]�����ߒ��ł͂Ȃ��ʏ�̏ꍇ
		if (_bDebug)
		{	//v1.07�ǉ��B�f�o�b�O�E�B���h�E�\�����Ȃ�
			while (DEBUG_GetPause()) //�f�o�b�O�E�B���h�E�Œ�~�ݒ蒆�Ȃ���������܂ő҂�
				Sleep(1);
			if (DEBUG_GetPauseLong()) //�ꎞ�I�ȉ����̏ꍇ
				DEBUG_SetPause(TRUE); //�P���ߎ��s��܂��|�[�Y
			
			fetchInterrupt();
			refreshPrevIF();
			_PrevPC = _PC;
			_PrevFlags = gatherFlags();
		}
		else //�ʏ�
		{
			//Kitao�X�V�B���߂����s����O�Ɋ��荞�ݏ������s���悤�ɂ����Bv1.61�X�V
			//			 ���荞�ݏ󋵂̃`�F�b�N�́A�ЂƂO�̖��ߊJ�n����I�t���O�����荞�ݐM����Ԃ��Q�Ƃ���B
			//			 �W���b�N�j�N���E�X�S���t(Hu�J�[�h��)�ŃV���b�g����ʗ��ꂪ�����B�X�g�Q�f�ŋH�ɂP�t���[������邱�Ƃ������B
			//			 �t�H�[���[�V�����T�b�J�['90�̃G���f�B���O�ŕK�v�BI�t���O�Ɗ��荞�݋֎~�����łȂ�IRQ��PrevIRQ�Ō��邱�Ƃ����^���G���W�F���ŕK�v�B
			fetchInterrupt();
			refreshPrevIF(); //����̊��荞�ݏ����p��_PrevIF,_PrevIRQx,_PrevIntDisable�Ɍ��݂̏󋵂�ۊǁBv1.61�ǉ�
		}

		_OpCode = READINC(_PC);
		gCPU_ClockCount -= _pCycleTable[_OpCode]; //v1.61�X�V�B����͒���gCPU_ClockCount�������悤�ɂ����B�������B
		//gCPU_ClockCount -= (_ClockElapsed = _pCycleTable[_OpCode]); //�������̂��ߌ��ݔ�g�p�B�f�o�b�O�p

		//Kitao�X�V�B�悭�g���閽�߂��Ɏ����Ă��č����������Bv1.30�B���[�v���Ŏg��ꂻ���Ȗ��߂��ɁBv1.63�X�V�B
		switch (_OpCode)
		{
			/*-------------------------------------------------------------------**
			** register data transfer instructions
			**-------------------------------------------------------------------*/
			/*---- LDA ----------------------------------------------------------*/
			case CPU_INST_LDA_IMM:
				ureg8 = READINC(_PC);
				lda(ureg8);
				break;

			case CPU_INST_LDA_ZP:
				addr8 = READINC(_PC);
				lda(READZP(addr8));
				break;

			case CPU_INST_LDA_ZP_X:
				addr8 = READINC_X(_PC);
				lda(READZP(addr8));
				break;

			case CPU_INST_LDA_IND:
				addr16 = fetchZpIndirect();
				lda(READ(addr16));
				break;

			case CPU_INST_LDA_IND_X:
				addr16 = fetchZpIndexIndirect();
				lda(READ(addr16));
				break;

			case CPU_INST_LDA_IND_Y:
				addr16 = fetchZpIndirectIndex();
				lda(READ(addr16));
				break;

			case CPU_INST_LDA_ABS:
				addr16 = fetchAbs();
				lda(READ(addr16));
				break;

			case CPU_INST_LDA_ABS_X:
				addr16 = fetchAbsX();
				lda(READ(addr16));
				break;

			case CPU_INST_LDA_ABS_Y:
				addr16 = fetchAbsY();
				lda(READ(addr16));
				break;

			/*---- LDX ----------------------------------------------------------*/
			case CPU_INST_LDX_IMM:
				ureg8 = READINC(_PC);
				ldx(ureg8);
				break;

			case CPU_INST_LDX_ZP:
				addr8 = READINC(_PC);
				ldx(READZP(addr8));
				break;

			case CPU_INST_LDX_ZP_Y:
				addr8 = READINC_Y(_PC);
				ldx(READZP(addr8));
				break;

			case CPU_INST_LDX_ABS:
				addr16 = fetchAbs();
				ldx(READ(addr16));
				break;

			case CPU_INST_LDX_ABS_Y:
				addr16 = fetchAbsY();
				ldx(READ(addr16));
				break;

			/*---- LDY ----------------------------------------------------------*/
			case CPU_INST_LDY_IMM:
				ureg8 = READINC(_PC);
				ldy(ureg8);
				break;

			case CPU_INST_LDY_ZP:
				addr8 = READINC(_PC);
				ldy(READZP(addr8));
				break;

			case CPU_INST_LDY_ZP_X:
				addr8 = READINC_X(_PC);
				ldy(READZP(addr8));
				break;

			case CPU_INST_LDY_ABS:
				addr16 = fetchAbs();
				ldy(READ(addr16));
				break;

			case CPU_INST_LDY_ABS_X:
				addr16 = fetchAbsX();
				ldy(READ(addr16));
				break;

			/*---- STA ----------------------------------------------------------*/
			case CPU_INST_STA_ZP:
				addr8 = READINC(_PC);
				WRITEZP(addr8, _A);
				break;

			case CPU_INST_STA_ZP_X:
				addr8 = READINC_X(_PC);
				WRITEZP(addr8, _A);
				break;

			case CPU_INST_STA_IND:
				addr16 = fetchZpIndirect();
				WRITE(addr16, _A);
				break;

			case CPU_INST_STA_IND_X:
				addr16 = fetchZpIndexIndirect();
				WRITE(addr16, _A);
				break;

			case CPU_INST_STA_IND_Y:
				addr16 = fetchZpIndirectIndex();
				WRITE(addr16, _A);
				break;

			case CPU_INST_STA_ABS:
				addr16 = fetchAbs();
				WRITE(addr16, _A);
				break;

			case CPU_INST_STA_ABS_X:
				addr16 = fetchAbsX();
				WRITE(addr16, _A);
				break;

			case CPU_INST_STA_ABS_Y:
				addr16 = fetchAbsY();
				WRITE(addr16, _A);
				break;

			/*---- STX ----------------------------------------------------------*/
			case CPU_INST_STX_ZP:
				addr8 = READINC(_PC);
				WRITEZP(addr8, _X);
				break;

			case CPU_INST_STX_ZP_Y:
				addr8 = READINC_Y(_PC);
				WRITEZP(addr8, _X);
				break;

			case CPU_INST_STX_ABS:
				addr16 = fetchAbs();
				WRITE(addr16, _X);
				break;

			/*---- STY ----------------------------------------------------------*/
			case CPU_INST_STY_ZP:
				addr8 = READINC(_PC);
				WRITEZP(addr8, _Y);
				break;

			case CPU_INST_STY_ZP_X:
				addr8 = READINC_X(_PC);
				WRITEZP(addr8, _Y);
				break;

			case CPU_INST_STY_ABS:
				addr16 = fetchAbs();
				WRITE(addr16, _Y);
				break;

			/*---- ST0 ----------------------------------------------------------*/
			case CPU_INST_ST0_IMM:
				ureg8 = READINC(_PC);
				if (_SelectVDC == 0) //Kitao�X�V�B�X�[�p�[�O���t�B�b�N�X�p
					WriteMem(0xFF, 0x0000, ureg8);
				else
					WriteMem(0xFF, 0x0010, ureg8);
				break;

			/*---- ST1 ----------------------------------------------------------*/
			case CPU_INST_ST1_IMM:
				ureg8 = READINC(_PC);
				if (_SelectVDC == 0) //Kitao�X�V�B�X�[�p�[�O���t�B�b�N�X�p
					WriteMem(0xFF, 0x0002, ureg8);
				else
					WriteMem(0xFF, 0x0012, ureg8);
				break;

			/*---- ST2 ----------------------------------------------------------*/
			case CPU_INST_ST2_IMM:
				ureg8 = READINC(_PC);
				if (_SelectVDC == 0) //Kitao�X�V�B�X�[�p�[�O���t�B�b�N�X�p
					WriteMem(0xFF, 0x0003, ureg8);
				else
					WriteMem(0xFF, 0x0013, ureg8);
				break;

			/*---- STZ ----------------------------------------------------------*/
			case CPU_INST_STZ_ZP:
				addr8 = READINC(_PC);
				WRITEZP(addr8, 0);
				break;

			case CPU_INST_STZ_ZP_X:
				addr8 = READINC_X(_PC);
				WRITEZP(addr8, 0);
				break;

			case CPU_INST_STZ_ABS:
				addr16 = fetchAbs();
				WRITE(addr16, 0);
				break;

			case CPU_INST_STZ_ABS_X:
				addr16 = fetchAbsX();
				WRITE(addr16, 0);
				break;

			/*-------------------------------------------------------------------**
			** flag instructions
			**-------------------------------------------------------------------*/
			/*---- CLC ----------------------------------------------------------*/
			case CPU_INST_CLC:
				_CF = 0;
				break;

			/*---- CLD ----------------------------------------------------------*/
			case CPU_INST_CLD:
				_DF = 0;
				break;

			/*---- CLI ----------------------------------------------------------*/
			case CPU_INST_CLI:
				//Kitao�X�V�BI�t���O�N���A�����IRQ �̃t�F�b�`���s�Ȃ��B�l�N���X�̗v�ǂ̃I�[�v�j���O�Ńt���[�Y���Ȃ����߂ɕK�v�B
				//			 ���荞�ݓ�����V���v���ɂ����̂ŁA�W���b�L�[�`�F�������Ȃ��N���B
				_IF = 0;
				break;

			/*---- CLV ----------------------------------------------------------*/
			case CPU_INST_CLV:
				_VF = 0;
				break;

			/*---- SEC ----------------------------------------------------------*/
			case CPU_INST_SEC:
				_CF = CPU_CF;
				break;

			/*---- SED ----------------------------------------------------------*/
			case CPU_INST_SED:
				_DF = CPU_DF;
				break;

			/*---- SEI ----------------------------------------------------------*/
			case CPU_INST_SEI:
				//Kitao�ǋL�B�Q�l�FI�t���O�Z�b�g�O�Ɋ��荞�݃t�F�b�`���s���ƁA�t�@�C���[�v�����X�����O�ŉ�ʉ������N����B
				_IF = CPU_IF;
				break;

			/*---- SET ----------------------------------------------------------*/
			case CPU_INST_SET:
				_TF = CPU_TF;
				return; // T�t���O�����Z�b�g�����Ɏ��̖��߂�

			/*-------------------------------------------------------------------**
			** ALU instructions
			**-------------------------------------------------------------------*/
			/*---- ADC ----------------------------------------------------------*/
			case CPU_INST_ADC_IMM:
				ureg8 = READINC(_PC);
				if (_TF)
					adc_t(ureg8);
				else
					adc(ureg8);
				break;

			case CPU_INST_ADC_ZP:
				ureg8 = READINC(_PC);
				if (_TF)
					adc_t(READZP(ureg8));
				else
					adc(READZP(ureg8));
				break;

			case CPU_INST_ADC_ZP_X:
				ureg8 = READINC_X(_PC);
				if (_TF)
					adc_t(READZP(ureg8));
				else
					adc(READZP(ureg8));
				break;

			case CPU_INST_ADC_IND:
				addr16 = fetchZpIndirect();
				if (_TF)
					adc_t(READ(addr16)); //Kitao�X�V�Bureg8�ւ̑�����ȗ����č������B�ȉ��̖��߂����l�ɍX�V�Bv1.08
				else
					adc(READ(addr16));
				break;

			case CPU_INST_ADC_IND_X:
				addr16 = fetchZpIndexIndirect();
				if (_TF)
					adc_t(READ(addr16));
				else
					adc(READ(addr16));
				break;

			case CPU_INST_ADC_IND_Y:
				addr16 = fetchZpIndirectIndex();
				if (_TF)
					adc_t(READ(addr16));
				else
					adc(READ(addr16));
				break;

			case CPU_INST_ADC_ABS:
				addr16 = fetchAbs();
				if (_TF)
					adc_t(READ(addr16));
				else
					adc(READ(addr16));
				break;

			case CPU_INST_ADC_ABS_X:
				addr16 = fetchAbsX();
				if (_TF)
					adc_t(READ(addr16));
				else
					adc(READ(addr16));
				break;

			case CPU_INST_ADC_ABS_Y:
				addr16 = fetchAbsY();
				if (_TF)
					adc_t(READ(addr16));
				else
					adc(READ(addr16));
				break;

			/*---- SBC ----------------------------------------------------------*/
			case CPU_INST_SBC_IMM:
				ureg8 = READINC(_PC);
				sbc(ureg8);
				break;

			case CPU_INST_SBC_ZP:
				ureg8 = READINC(_PC);
				sbc(READZP(ureg8));
				break;

			case CPU_INST_SBC_ZP_X:
				ureg8 = READINC_X(_PC);
				sbc(READZP(ureg8));
				break;

			case CPU_INST_SBC_IND:
				addr16 = fetchZpIndirect();
				sbc(READ(addr16));
				break;

			case CPU_INST_SBC_IND_X:
				addr16 = fetchZpIndexIndirect();
				sbc(READ(addr16));
				break;

			case CPU_INST_SBC_IND_Y:
				addr16 = fetchZpIndirectIndex();
				sbc(READ(addr16));
				break;

			case CPU_INST_SBC_ABS:
				addr16 = fetchAbs();
				sbc(READ(addr16));
				break;

			case CPU_INST_SBC_ABS_X:
				addr16 = fetchAbsX();
				sbc(READ(addr16));
				break;

			case CPU_INST_SBC_ABS_Y:
				addr16 = fetchAbsY();
				sbc(READ(addr16));
				break;

			/*---- AND ----------------------------------------------------------*/
			case CPU_INST_AND_IMM:
				ureg8 = READINC(_PC);
				if (_TF)
					and_t(ureg8);
				else
					and(ureg8);
				break;

			case CPU_INST_AND_ZP:
				ureg8 = READINC(_PC);
				if (_TF)
					and_t(READZP(ureg8));
				else
					and(READZP(ureg8));
				break;

			case CPU_INST_AND_ZP_X:
				ureg8 = READINC_X(_PC);
				if (_TF)
					and_t(READZP(ureg8));
				else
					and(READZP(ureg8));
				break;

			case CPU_INST_AND_IND:
				addr16 = fetchZpIndirect();
				if (_TF)
					and_t(READ(addr16));
				else
					and(READ(addr16));
				break;

			case CPU_INST_AND_IND_X:
				addr16 = fetchZpIndexIndirect();
				if (_TF)
					and_t(READ(addr16));
				else
					and(READ(addr16));
				break;

			case CPU_INST_AND_IND_Y:
				addr16 = fetchZpIndirectIndex();
				if (_TF)
					and_t(READ(addr16));
				else
					and(READ(addr16));
				break;

			case CPU_INST_AND_ABS:
				addr16 = fetchAbs();
				if (_TF)
					and_t(READ(addr16));
				else
					and(READ(addr16));
				break;

			case CPU_INST_AND_ABS_X:
				addr16 = fetchAbsX();
				if (_TF)
					and_t(READ(addr16));
				else
					and(READ(addr16));
				break;

			case CPU_INST_AND_ABS_Y:
				addr16 = fetchAbsY();
				if (_TF)
					and_t(READ(addr16));
				else
					and(READ(addr16));
				break;

			/*---- ORA ----------------------------------------------------------*/
			case CPU_INST_ORA_IMM:
				ureg8 = READINC(_PC);
				if (_TF)
					ora_t(ureg8);
				else
					ora(ureg8);
				break;

			case CPU_INST_ORA_ZP:
				ureg8 = READINC(_PC);
				if (_TF)
					ora_t(READZP(ureg8));
				else
					ora(READZP(ureg8));
				break;

			case CPU_INST_ORA_ZP_X:
				ureg8 = READINC_X(_PC);
				if (_TF)
					ora_t(READZP(ureg8));
				else
					ora(READZP(ureg8));
				break;

			case CPU_INST_ORA_IND:
				addr16 = fetchZpIndirect();
				if (_TF)
					ora_t(READ(addr16));
				else
					ora(READ(addr16));
				break;

			case CPU_INST_ORA_IND_X:
				addr16 = fetchZpIndexIndirect();
				if (_TF)
					ora_t(READ(addr16));
				else
					ora(READ(addr16));
				break;

			case CPU_INST_ORA_IND_Y:
				addr16 = fetchZpIndirectIndex();
				if (_TF)
					ora_t(READ(addr16));
				else
					ora(READ(addr16));
				break;

			case CPU_INST_ORA_ABS:
				addr16 = fetchAbs();
				if (_TF)
					ora_t(READ(addr16));
				else
					ora(READ(addr16));
				break;

			case CPU_INST_ORA_ABS_X:
				addr16 = fetchAbsX();
				if (_TF)
					ora_t(READ(addr16));
				else
					ora(READ(addr16));
				break;

			case CPU_INST_ORA_ABS_Y:
				addr16 = fetchAbsY();
				if (_TF)
					ora_t(READ(addr16));
				else
					ora(READ(addr16));
				break;

			/*---- EOR ----------------------------------------------------------*/
			case CPU_INST_EOR_IMM:
				ureg8 = READINC(_PC);
				if (_TF)
					eor_t(ureg8);
				else
					eor(ureg8);
				break;

			case CPU_INST_EOR_ZP:
				ureg8 = READINC(_PC);
				if (_TF)
					eor_t(READZP(ureg8));
				else
					eor(READZP(ureg8));
				break;

			case CPU_INST_EOR_ZP_X:
				ureg8 = READINC_X(_PC);
				if (_TF)
					eor_t(READZP(ureg8));
				else
					eor(READZP(ureg8));
				break;

			case CPU_INST_EOR_IND:
				addr16 = fetchZpIndirect();
				if (_TF)
					eor_t(READ(addr16));
				else
					eor(READ(addr16));
				break;

			case CPU_INST_EOR_IND_X:
				addr16 = fetchZpIndexIndirect();
				if (_TF)
					eor_t(READ(addr16));
				else
					eor(READ(addr16));
				break;

			case CPU_INST_EOR_IND_Y:
				addr16 = fetchZpIndirectIndex();
				if (_TF)
					eor_t(READ(addr16));
				else
					eor(READ(addr16));
				break;

			case CPU_INST_EOR_ABS:
				addr16 = fetchAbs();
				if (_TF)
					eor_t(READ(addr16));
				else
					eor(READ(addr16));
				break;

			case CPU_INST_EOR_ABS_X:
				addr16 = fetchAbsX();
				if (_TF)
					eor_t(READ(addr16));
				else
					eor(READ(addr16));
				break;

			case CPU_INST_EOR_ABS_Y:
				addr16 = fetchAbsY();
				if (_TF)
					eor_t(READ(addr16));
				else
					eor(READ(addr16));
				break;

			/*---- INC ----------------------------------------------------------*/
			case CPU_INST_INC_ACCUM:
				updateFlagZN(++_A);
				break;

			case CPU_INST_INC_ZP:
				addr8 = READINC(_PC);
				ureg8 = READZP(addr8);
				updateFlagZN(++ureg8);
				WRITEZP(addr8, ureg8);
				break;

			case CPU_INST_INC_ZP_X:
				addr8 = READINC_X(_PC);
				ureg8 = READZP(addr8);
				updateFlagZN(++ureg8);
				WRITEZP(addr8, ureg8);
				break;

			case CPU_INST_INC_ABS:
				addr16 = fetchAbs();
				ureg8 = READ(addr16);
				updateFlagZN(++ureg8);
				WRITE(addr16, ureg8);
				break;

			case CPU_INST_INC_ABS_X:
				addr16 = fetchAbsX();
				ureg8 = READ(addr16);
				updateFlagZN(++ureg8);
				WRITE(addr16, ureg8);
				break;

			/*---- INX ----------------------------------------------------------*/
			case CPU_INST_INX:
				updateFlagZN(++_X);
				break;

			/*---- INY ----------------------------------------------------------*/
			case CPU_INST_INY:
				updateFlagZN(++_Y);
				break;

			/*---- DEC ----------------------------------------------------------*/
			case CPU_INST_DEC_ACCUM:
				updateFlagZN(--_A);
				break;

			case CPU_INST_DEC_ZP:
				addr8 = READINC(_PC);
				ureg8 = READZP(addr8);
				updateFlagZN(--ureg8);
				WRITEZP(addr8, ureg8);
				break;

			case CPU_INST_DEC_ZP_X:
				addr8 = READINC_X(_PC);
				ureg8 = READZP(addr8);
				updateFlagZN(--ureg8);
				WRITEZP(addr8, ureg8);
				break;

			case CPU_INST_DEC_ABS:
				addr16 = fetchAbs();
				ureg8 = READ(addr16);
				updateFlagZN(--ureg8);
				WRITE(addr16, ureg8);
				break;

			case CPU_INST_DEC_ABS_X:
				addr16 = fetchAbsX();
				ureg8 = READ(addr16);
				updateFlagZN(--ureg8);
				WRITE(addr16, ureg8);
				break;

			/*---- DEX ----------------------------------------------------------*/
			case CPU_INST_DEX:
				updateFlagZN(--_X);
				break;
					
			/*---- DEY ----------------------------------------------------------*/
			case CPU_INST_DEY:
				updateFlagZN(--_Y);
				break;

			/*---- CMP ----------------------------------------------------------*/
			case CPU_INST_CMP_IMM:
				ureg8 = READINC(_PC);
				cmp(ureg8);
				break;

			case CPU_INST_CMP_ZP:
				ureg8 = READINC(_PC);
				cmp(READZP(ureg8));
				break;

			case CPU_INST_CMP_ZP_X:
				ureg8 = READINC_X(_PC);
				cmp(READZP(ureg8));
				break;

			case CPU_INST_CMP_IND:
				addr16 = fetchZpIndirect();
				cmp(READ(addr16));
				break;

			case CPU_INST_CMP_IND_X:
				addr16 = fetchZpIndexIndirect();
				cmp(READ(addr16));
				break;

			case CPU_INST_CMP_IND_Y:
				addr16 = fetchZpIndirectIndex();
				cmp(READ(addr16));
				break;

			case CPU_INST_CMP_ABS:
				addr16 = fetchAbs();
				cmp(READ(addr16));
				break;

			case CPU_INST_CMP_ABS_X:
				addr16 = fetchAbsX();
				cmp(READ(addr16));
				break;

			case CPU_INST_CMP_ABS_Y:
				addr16 = fetchAbsY();
				cmp(READ(addr16));
				break;

			/*---- CPX ----------------------------------------------------------*/
			case CPU_INST_CPX_IMM:
				ureg8 = READINC(_PC);
				cpx(ureg8);
				break;

			case CPU_INST_CPX_ZP:
				ureg8 = READINC(_PC);
				cpx(READZP(ureg8));
				break;
			
			case CPU_INST_CPX_ABS:
				addr16 = fetchAbs();
				cpx(READ(addr16));
				break;

			/*---- CPY ----------------------------------------------------------*/
			case CPU_INST_CPY_IMM:
				ureg8 = READINC(_PC);
				cpy(ureg8);
				break;

			case CPU_INST_CPY_ZP:
				ureg8 = READINC(_PC);
				cpy(READZP(ureg8));
				break;
			
			case CPU_INST_CPY_ABS:
				addr16 = fetchAbs();
				cpy(READ(addr16));
				break;

			/*---- ASL ----------------------------------------------------------*/
			case CPU_INST_ASL_ACCUM:
				_A = asl(_A);
				break;

			case CPU_INST_ASL_ZP:
				addr8 = READINC(_PC);
				WRITEZP(addr8, asl(READZP(addr8)));
				break;

			case CPU_INST_ASL_ZP_X:
				addr8 = READINC_X(_PC);
				WRITEZP(addr8, asl(READZP(addr8)));
				break;

			case CPU_INST_ASL_ABS:
				addr16 = fetchAbs();
				WRITE(addr16, asl(READ(addr16)));
				break;
			
			case CPU_INST_ASL_ABS_X:
				addr16 = fetchAbsX();
				WRITE(addr16, asl(READ(addr16)));
				break;

			/*---- LSR ----------------------------------------------------------*/
			case CPU_INST_LSR_ACCUM:
				_A = lsr(_A);
				break;

			case CPU_INST_LSR_ZP:
				addr8 = READINC(_PC);
				WRITEZP(addr8, lsr(READZP(addr8)));
				break;

			case CPU_INST_LSR_ZP_X:
				addr8 = READINC_X(_PC);
				WRITEZP(addr8, lsr(READZP(addr8)));
				break;

			case CPU_INST_LSR_ABS:
				addr16 = fetchAbs();
				WRITE(addr16, lsr(READ(addr16)));
				break;
			
			case CPU_INST_LSR_ABS_X:
				addr16 = fetchAbsX();
				WRITE(addr16, lsr(READ(addr16)));
				break;

			/*---- ROL ----------------------------------------------------------*/
			case CPU_INST_ROL_ACCUM:
				_A = rol(_A);
				break;

			case CPU_INST_ROL_ZP:
				addr8 = READINC(_PC);
				WRITEZP(addr8, rol(READZP(addr8)));
				break;

			case CPU_INST_ROL_ZP_X:
				addr8 = READINC_X(_PC);
				WRITEZP(addr8, rol(READZP(addr8)));
				break;

			case CPU_INST_ROL_ABS:
				addr16 = fetchAbs();
				WRITE(addr16, rol(READ(addr16)));
				break;
			
			case CPU_INST_ROL_ABS_X:
				addr16 = fetchAbsX();
				WRITE(addr16, rol(READ(addr16)));
				break;

			/*---- ROR ----------------------------------------------------------*/
			case CPU_INST_ROR_ACCUM:
				_A = ror(_A);
				break;

			case CPU_INST_ROR_ZP:
				addr8 = READINC(_PC);
				WRITEZP(addr8, ror(READZP(addr8)));
				break;

			case CPU_INST_ROR_ZP_X:
				addr8 = READINC_X(_PC);
				WRITEZP(addr8, ror(READZP(addr8)));
				break;

			case CPU_INST_ROR_ABS:
				addr16 = fetchAbs();
				WRITE(addr16, ror(READ(addr16)));
				break;

			case CPU_INST_ROR_ABS_X:
				addr16 = fetchAbsX();
				WRITE(addr16, ror(READ(addr16)));
				break;

			/*---- CLA ----------------------------------------------------------*/
			case CPU_INST_CLA:
				_A = 0;
				break;

			/*---- CLX ----------------------------------------------------------*/
			case CPU_INST_CLX:
				_X = 0;
				break;

			/*---- CLY ----------------------------------------------------------*/
			case CPU_INST_CLY:
				_Y = 0;
				break;

			/*---- TAX ----------------------------------------------------------*/
			case CPU_INST_TAX:
				tax();
				break;

			/*---- TAY ----------------------------------------------------------*/
			case CPU_INST_TAY:
				tay();
				break;

			/*---- TSX ----------------------------------------------------------*/
			case CPU_INST_TSX:
				tsx();
				break;

			/*---- TXA ----------------------------------------------------------*/
			case CPU_INST_TXA:
				txa();
				break;

			/*---- TXS ----------------------------------------------------------*/
			case CPU_INST_TXS:
				_S = _X;
				break;

			/*---- TYA ----------------------------------------------------------*/
			case CPU_INST_TYA:
				tya();
				break;

			/*---- SAX ----------------------------------------------------------*/
			case CPU_INST_SAX:
				ureg8 = _A;
				_A = _X;
				_X = ureg8;
				break;

			/*---- SAY ----------------------------------------------------------*/
			case CPU_INST_SAY:
				ureg8 = _A;
				_A = _Y;
				_Y = ureg8;
				break;

			/*---- SXY ----------------------------------------------------------*/
			case CPU_INST_SXY:
				ureg8 = _X;
				_X = _Y;
				_Y = ureg8;
				break;

			/*-------------------------------------------------------------------**
			** test instructions
			**-------------------------------------------------------------------*/
			/*---- BIT ----------------------------------------------------------*/
			case CPU_INST_BIT_IMM:
				ureg8 = READINC(_PC);
				bit(ureg8);
				break;

			case CPU_INST_BIT_ZP:
				addr8 = READINC(_PC);
				bit(READZP(addr8));
				break;

			case CPU_INST_BIT_ZP_X:
				addr8 = READINC_X(_PC);
				bit(READZP(addr8));
				break;

			case CPU_INST_BIT_ABS:
				addr16 = fetchAbs();
				bit(READ(addr16));
				break;

			case CPU_INST_BIT_ABS_X:
				addr16 = fetchAbsX();
				bit(READ(addr16));
				break;

			/*---- TRB ----------------------------------------------------------*/
			case CPU_INST_TRB_ZP:
				addr8 = READINC(_PC);
				WRITEZP(addr8, trb(READZP(addr8)));
				break;

			case CPU_INST_TRB_ABS:
				addr16 = fetchAbs();
				WRITE(addr16, trb(READ(addr16)));
				break;

			/*---- TSB ----------------------------------------------------------*/
			case CPU_INST_TSB_ZP:
				addr8 = READINC(_PC);
				WRITEZP(addr8, tsb(READZP(addr8)));
				break;

			case CPU_INST_TSB_ABS:
				addr16 = fetchAbs();
				WRITE(addr16, tsb(READ(addr16)));
				break;

			/*---- TST ----------------------------------------------------------*/
			case CPU_INST_TST_IMM_ZP:
				ureg8 = READINC(_PC);
				addr8 = READINC(_PC);
				tst(ureg8, READZP(addr8));
				break;

			case CPU_INST_TST_IMM_ZP_X:
				ureg8 = READINC(_PC);
				addr8 = READINC_X(_PC);
				tst(ureg8, READZP(addr8));
				break;

			case CPU_INST_TST_IMM_ABS:
				ureg8 = READINC(_PC);
				addr16 = fetchAbs();
				tst(ureg8, READ(addr16));
				break;

			case CPU_INST_TST_IMM_ABS_X:
				ureg8 = READINC(_PC);
				addr16 = fetchAbsX();
				tst(ureg8, READ(addr16));
				break;

			/*-------------------------------------------------------------------**
			** branch / jump instructions
			**-------------------------------------------------------------------*/
			/*---- BCC ----------------------------------------------------------*/
			case CPU_INST_BCC_REL:
				rel8 = (Sint8)READINC(_PC);
				if (_CF == 0)
				{
					gCPU_ClockCount--;
					gCPU_ClockCount--;
					_PC += (Sint16)rel8;
				}
				break;

			/*---- BNE ----------------------------------------------------------*/
			case CPU_INST_BNE_REL:
				rel8 = (Sint8)READINC(_PC);
				if (_ZF) //ZF��0�̏ꍇ���^(�[��)
				{
					gCPU_ClockCount--;
					gCPU_ClockCount--;
					_PC += (Sint16)rel8;
				}
				break;

			/*---- BVC ----------------------------------------------------------*/
			case CPU_INST_BVC_REL:
				rel8 = (Sint8)READINC(_PC);
				if ((_VF & CPU_VF) == 0)
				{
					gCPU_ClockCount--;
					gCPU_ClockCount--;
					_PC += (Sint16)rel8;
				}
				break;

			/*---- BPL ----------------------------------------------------------*/
			case CPU_INST_BPL_REL:
				rel8 = (Sint8)READINC(_PC);
				if ((_NF & CPU_NF) == 0)
				{
					gCPU_ClockCount--;
					gCPU_ClockCount--;
					_PC += (Sint16)rel8;
				}
				break;

			/*---- BCS ----------------------------------------------------------*/
			case CPU_INST_BCS_REL:
				rel8 = (Sint8)READINC(_PC);
				if (_CF)
				{
					gCPU_ClockCount--;
					gCPU_ClockCount--;
					_PC += (Sint16)rel8;
				}
				break;

			/*---- BEQ ----------------------------------------------------------*/
			case CPU_INST_BEQ_REL:
				rel8 = (Sint8)READINC(_PC);
				if (_ZF == 0) //ZF��0�̏ꍇ���^(�[��)
				{
					gCPU_ClockCount--;
					gCPU_ClockCount--;
					_PC += (Sint16)rel8;
				}
				break;

			/*---- BVS ----------------------------------------------------------*/
			case CPU_INST_BVS_REL:
				rel8 = (Sint8)READINC(_PC);
				if (_VF & CPU_VF)
				{
					gCPU_ClockCount--;
					gCPU_ClockCount--;
					_PC += (Sint16)rel8;
				}
				break;

			/*---- BMI ----------------------------------------------------------*/
			case CPU_INST_BMI_REL:
				rel8 = (Sint8)READINC(_PC);
				if (_NF & CPU_NF)
				{
					gCPU_ClockCount--;
					gCPU_ClockCount--;
					_PC += (Sint16)rel8;
				}
				break;

			/*---- BRA ----------------------------------------------------------*/
			case CPU_INST_BRA_REL:
				rel8 = (Sint8)READINC(_PC);
				_PC += (Sint16)rel8;
				break;

			/*---- JMP ----------------------------------------------------------*/
			case CPU_INST_JMP_ABS:
				_PC = fetchAbs();
				break;

			case CPU_INST_JMP_INDIR:
				_PC = fetchAbsIndirect();
				break;

			case CPU_INST_JMP_INDIRX:
				_PC = fetchAbsIndirectX();
				break;

			/*---- BBRi ---------------------------------------------------------*/
			case CPU_INST_BBR0_ZP_REL:
				BBRi(0x01);
				break;

			case CPU_INST_BBR1_ZP_REL:
				BBRi(0x02);
				break;

			case CPU_INST_BBR2_ZP_REL:
				BBRi(0x04);
				break;

			case CPU_INST_BBR3_ZP_REL:
				BBRi(0x08);
				break;

			case CPU_INST_BBR4_ZP_REL:
				BBRi(0x10);
				break;

			case CPU_INST_BBR5_ZP_REL:
				BBRi(0x20);
				break;

			case CPU_INST_BBR6_ZP_REL:
				BBRi(0x40);
				break;

			case CPU_INST_BBR7_ZP_REL:
				BBRi(0x80);
				break;

			/*---- BBSi ---------------------------------------------------------*/
			case CPU_INST_BBS0_ZP_REL:
				BBSi(0x01);
				break;

			case CPU_INST_BBS1_ZP_REL:
				BBSi(0x02);
				break;

			case CPU_INST_BBS2_ZP_REL:
				BBSi(0x04);
				break;

			case CPU_INST_BBS3_ZP_REL:
				BBSi(0x08);
				break;

			case CPU_INST_BBS4_ZP_REL:
				BBSi(0x10);
				break;

			case CPU_INST_BBS5_ZP_REL:
				BBSi(0x20);
				break;

			case CPU_INST_BBS6_ZP_REL:
				BBSi(0x40);
				break;

			case CPU_INST_BBS7_ZP_REL:
				BBSi(0x80);
				break;

			/*-------------------------------------------------------------------**
			** subroutine instructions
			**-------------------------------------------------------------------*/
			/*---- BSR ----------------------------------------------------------*/
			case CPU_INST_BSR_REL: //v1.59�X�V
				push(_PC >> 8);
				push(_PC & 0xFF);
				rel8 = (Sint8)READINC(_PC);
				_PC += (Sint16)rel8;
				break;

			/*---- JSR ----------------------------------------------------------*/
			case CPU_INST_JSR_ABS: //v1.59�X�V
				++_PC;
				push(_PC >> 8);
				push(_PC & 0xFF);
				--_PC;
				_PC = fetchAbs();
				break;

			/*---- PHA ----------------------------------------------------------*/
			case CPU_INST_PHA:
				push(_A);
				break;

			/*---- PHP ----------------------------------------------------------*/
			case CPU_INST_PHP:
				_TF = 0;
				push(gatherFlags());
				break;

			/*---- PHX ----------------------------------------------------------*/
			case CPU_INST_PHX:
				push(_X);
				break;

			/*---- PHY ----------------------------------------------------------*/
			case CPU_INST_PHY:
				push(_Y);
				break;

			/*---- PLA ----------------------------------------------------------*/
			case CPU_INST_PLA:
				_A = pull();
				updateFlagZN(_A);
				break;

			/*---- PLP ----------------------------------------------------------*/
			// PLP ���ߎ��s����́F
			// - T �t���O�����Z�b�g���Ȃ� 
			case CPU_INST_PLP:
				separateFlags(pull());
				_BF = CPU_BF; //v1.61�ǉ��BThanks Aladar's information.
				refreshPrevIF(); //v1.61�ǉ��B�����炭RTI�Ɠ����@�\�B
				return;

			/*---- PLX ----------------------------------------------------------*/
			case CPU_INST_PLX:
				_X = pull();
				updateFlagZN(_X);
				break;

			/*---- PLY ----------------------------------------------------------*/
			case CPU_INST_PLY:
				_Y = pull();
				updateFlagZN(_Y);
				break;

			/*---- RTI ----------------------------------------------------------*/
			// RTI ���ߎ��s�����
			// - T �t���O�����Z�b�g���Ȃ� 
			// Kitao�ǋL - ������I�t���O(IF)�����A�����Ƃ���PrevIF��IF�Ɠ��l�ɂȂ�Bpull����IF��0�Ȃ�΁A���̌シ�����荞�ݏ������N����B
			//			   Ki���񂩂炢�����������(CLI���ߎ��ɂ͂P���ߒx��Ċ��荞�݂��N���邪�ARTI�͂����Ɋ��荞�݂��N����)�̓���Ɉ�v�����Bv1.61
			case CPU_INST_RTI:
				separateFlags(pull());
				_BF = CPU_BF; //v1.61�ǉ��BThanks Aladar's information.
				refreshPrevIF(); //v1.61�ǉ�
				_PC = pull();
				_PC |= pull() << 8;
				return;

			/*---- RTS ----------------------------------------------------------*/
			case CPU_INST_RTS:
				_PC = pull();
				_PC |= pull() << 8;
				++_PC;
				break;

			/*-------------------------------------------------------------------**
			** block data transfer instructions
			**-------------------------------------------------------------------*/
			/*---- TII ----------------------------------------------------------*/
			case CPU_INST_TII:
				_TransferSrcAddr = fetchAbs();
				_TransferDstAddr = fetchAbs();
				_TransferLength	= fetchAbs();
				gCPU_Transfer = 1; //Kitao�ǉ��B1=TII���ߓ]���J�n�̍��}�B
				return;

			/*---- TDD ----------------------------------------------------------*/
			case CPU_INST_TDD:
				_TransferSrcAddr = fetchAbs();
				_TransferDstAddr = fetchAbs();
				_TransferLength	= fetchAbs();
				gCPU_Transfer = 2; //Kitao�ǉ��B2=TDD���ߓ]���J�n�̍��}�B
				return;

			/*---- TIN ----------------------------------------------------------*/
			case CPU_INST_TIN:
				_TransferSrcAddr = fetchAbs();
				_TransferDstAddr = fetchAbs();
				_TransferLength	= fetchAbs();
				gCPU_Transfer = 3; //Kitao�ǉ��B3=TIN���ߓ]���J�n�̍��}�B
				return;

			/*---- TIA ----------------------------------------------------------*/
			case CPU_INST_TIA:
				_TransferSrcAddr = fetchAbs();
				_TransferDstAddr = fetchAbs();
				_TransferLength	= fetchAbs();
				_TransferIncDec = TRUE;
				gCPU_Transfer = 4; //Kitao�ǉ��B4=TIA���ߓ]���J�n�̍��}�B
				return;

			/*---- TAI ----------------------------------------------------------*/
			case CPU_INST_TAI:
				_TransferSrcAddr = fetchAbs();
				_TransferDstAddr = fetchAbs();
				_TransferLength	= fetchAbs();
				_TransferIncDec = TRUE;
				gCPU_Transfer = 5; //Kitao�ǉ��B5=TAI���ߓ]���J�n�̍��}�B
				return;

			/*-------------------------------------------------------------------**
			** mapper instructions
			**-------------------------------------------------------------------*/
			/*---- TAMi ---------------------------------------------------------*/
			case CPU_INST_TAM:
				ureg8 = READINC(_PC);
//if ((ureg8 != 0x01)&&(ureg8 != 0x02)&&(ureg8 != 0x04)&&(ureg8 != 0x08)&&(ureg8 != 0x10)&&(ureg8 != 0x20)&&(ureg8 != 0x40)&&(ureg8 != 0x80))
//PRINTF("TAM %d",ureg8);//test
				if (ureg8 & 0x01) _MPR[0] = _A; //Kitao�X�V�BMPR�͍�13��V�t�g�����AA���W�X�^�̒l�̂܂ܕێ�����悤�ɂ����B�������Bv1.47
				if (ureg8 & 0x02) _MPR[1] = _A;
				if (ureg8 & 0x04) _MPR[2] = _A;
				if (ureg8 & 0x08) _MPR[3] = _A;
				if (ureg8 & 0x10) _MPR[4] = _A;
				if (ureg8 & 0x20) _MPR[5] = _A;
				if (ureg8 & 0x40) _MPR[6] = _A;
				if (ureg8 & 0x80) _MPR[7] = _A;
				//Kitao�ǋL�Bureg8�̕�����bit�������Ă����ꍇ�ǂ��Ȃ邩�B����͑S�Ă��Z�b�g����悤�ɂ����B�����Ȃ��\�t�g�̋����Ɗ֌W���邩���B�v�e�X�g�B
				break;

			/*---- TMAi ---------------------------------------------------------*/
			case CPU_INST_TMA:
				ureg8 = READINC(_PC);
//if ((ureg8 != 0x01)&&(ureg8 != 0x02)&&(ureg8 != 0x04)&&(ureg8 != 0x08)&&(ureg8 != 0x10)&&(ureg8 != 0x20)&&(ureg8 != 0x40)&&(ureg8 != 0x80))
//PRINTF("TMA %d",ureg8);//test
				if (ureg8 & 0x80) { _A = (Uint8)_MPR[7]; break; }
				if (ureg8 & 0x40) { _A = (Uint8)_MPR[6]; break; }
				if (ureg8 & 0x20) { _A = (Uint8)_MPR[5]; break; }
				if (ureg8 & 0x10) { _A = (Uint8)_MPR[4]; break; }
				if (ureg8 & 0x08) { _A = (Uint8)_MPR[3]; break; }
				if (ureg8 & 0x04) { _A = (Uint8)_MPR[2]; break; }
				if (ureg8 & 0x02) { _A = (Uint8)_MPR[1]; break; }
				if (ureg8 & 0x01) { _A = (Uint8)_MPR[0]; break; }
				//Kitao�ǋL�Bureg8�̕�����bit�������Ă����ꍇ�ǂ��Ȃ邩�Bv1.59���獂���r�b�g�����ŏI�I�Ɏc�肻���Ȃ̂ŁA�����r�b�g��D�悷��悤�ɂ����B
				break;

			/*-------------------------------------------------------------------**
			** control instructions
			**-------------------------------------------------------------------*/
			/*---- CSL ----------------------------------------------------------*/
			case CPU_INST_CSL: //Kitao�ǉ��B���ԑ҂��ȂǂŎg����ꍇ������B
				if (_bSpeedLow == FALSE) //v0.85�ǉ��BHigh��Low�ɂȂ�Ƃ��͎��s���ɃN���b�N���ς��̂ŏ���N���b�N���ϑ��I�ɂȂ�
				{
					gCPU_ClockCount -= 9;
					SetSpeedLow(TRUE);
				}
				break;

			/*---- CSH ----------------------------------------------------------*/
			case CPU_INST_CSH: //Kitao�ǉ��B���ԑ҂��ȂǂŎg����ꍇ������B
				if (_bSpeedLow) //v0.85�ǉ��BLow��High�ɂȂ�Ƃ��͎��s���ɃN���b�N���ς��̂ŏ���N���b�N���ϑ��I�ɂȂ�
				{
					gCPU_ClockCount -= 6;
					SetSpeedLow(FALSE);
				}
				break;

			/*---- BRK ----------------------------------------------------------*/
			case CPU_INST_BRK:
				_PC++;
				push(_PC >> 8);
				push(_PC & 0xFF);
				_TF = 0; //Kitao�X�V�BT�t���O���N���A���Ă���push�Bv1.07
				_BF = CPU_BF;
				push(gatherFlags());
				_IF = CPU_IF;
				refreshPrevIF(); //v1.61�ǉ�
				_DF = 0;
				_PC  = READ(CPU_IRQ2VECTOR);
				_PC |= READ(CPU_IRQ2VECTOR + 1) << 8;
				break;

			/*---- NOP ----------------------------------------------------------*/
			case CPU_INST_NOP:
				break;

			/*---- RMBi ---------------------------------------------------------*/
			case CPU_INST_RMB0_ZP:
				ureg8 = READINC(_PC);
				RMBi(ureg8, 0x01);
				break;

			case CPU_INST_RMB1_ZP:
				ureg8 = READINC(_PC);
				RMBi(ureg8, 0x02);
				break;

			case CPU_INST_RMB2_ZP:
				ureg8 = READINC(_PC);
				RMBi(ureg8, 0x04);
				break;

			case CPU_INST_RMB3_ZP:
				ureg8 = READINC(_PC);
				RMBi(ureg8, 0x08);
				break;

			case CPU_INST_RMB4_ZP:
				ureg8 = READINC(_PC);
				RMBi(ureg8, 0x10);
				break;

			case CPU_INST_RMB5_ZP:
				ureg8 = READINC(_PC);
				RMBi(ureg8, 0x20);
				break;

			case CPU_INST_RMB6_ZP:
				ureg8 = READINC(_PC);
				RMBi(ureg8, 0x40);
				break;

			case CPU_INST_RMB7_ZP:
				ureg8 = READINC(_PC);
				RMBi(ureg8, 0x80);
				break;

			/*---- SMBi ---------------------------------------------------------*/
			case CPU_INST_SMB0_ZP:
				ureg8 = READINC(_PC);
				SMBi(ureg8, 0x01);
				break;

			case CPU_INST_SMB1_ZP:
				ureg8 = READINC(_PC);
				SMBi(ureg8, 0x02);
				break;

			case CPU_INST_SMB2_ZP:
				ureg8 = READINC(_PC);
				SMBi(ureg8, 0x04);
				break;

			case CPU_INST_SMB3_ZP:
				ureg8 = READINC(_PC);
				SMBi(ureg8, 0x08);
				break;

			case CPU_INST_SMB4_ZP:
				ureg8 = READINC(_PC);
				SMBi(ureg8, 0x10);
				break;

			case CPU_INST_SMB5_ZP:
				ureg8 = READINC(_PC);
				SMBi(ureg8, 0x20);
				break;

			case CPU_INST_SMB6_ZP:
				ureg8 = READINC(_PC);
				SMBi(ureg8, 0x40);
				break;

			case CPU_INST_SMB7_ZP:
				ureg8 = READINC(_PC);
				SMBi(ureg8, 0x80);
				break;

			/*------------------------------------------------------------------**
			** invalid instructions
			**------------------------------------------------------------------*/
			default:
				//PRINTF("CPU ERROR::invalid instructions"); //Kitao�ǉ��Bv1.07
				break;
		}
		_TF = 0;
		return;

	case 1: //TII
		gCPU_ClockCount -= 5; //�l�N���X�̗v�ǂ�OP�f��OK�B�Q���W�ʐM��������OK�B�_�u���h���S��II��OP�f��OK�B
		ureg8 = READINC(_TransferSrcAddr);
		WRITEINC(_TransferDstAddr, ureg8);
		if (--_TransferLength <= 0) //�]����S�ďI�����Ȃ�
		{
			gCPU_Transfer = 0;
			_TF = 0;
			refreshPrevIF(); //v1.62�ǉ�
		}
		return;
	case 2: //TDD
		gCPU_ClockCount -= 5;
		ureg8 = READDEC(_TransferSrcAddr);
		WRITEDEC(_TransferDstAddr, ureg8);
		if (--_TransferLength <= 0) //�]����S�ďI�����Ȃ�
		{
			gCPU_Transfer = 0;
			_TF = 0;
			refreshPrevIF(); //v1.62�ǉ�
		}
		return;
	case 3: //TIN
		gCPU_ClockCount -= 5;
		ureg8 = READINC(_TransferSrcAddr);
		WRITE(_TransferDstAddr, ureg8);
		if (--_TransferLength <= 0) //�]����S�ďI�����Ȃ�
		{
			gCPU_Transfer = 0;
			_TF = 0;
			refreshPrevIF(); //v1.62�ǉ�
		}
		return;
	case 4: //TIA
		ureg8 = READINC(_TransferSrcAddr);
		if (_TransferIncDec)
		{
			gCPU_ClockCount -= 5; //������6���ƃ����_�[�����ŗ���
			WRITEINC(_TransferDstAddr, ureg8);
			_TransferIncDec = FALSE;
		}
		else
		{
			gCPU_ClockCount -= 6; ///���[�X�^'91�~�[�g����6�ȏオ�K�v�B6�Ń����_�[����OK�B���[�h�X����LII�̃G���f�B���O��6�ȏオ�K�v(5�ł�VCE�E�F�C�g�������OK)�Bv1.61�X�V
								  //"Write�A�h���X"��INC��DEC�̔��f�{������TII�����x���H(���@������)
			WRITEDEC(_TransferDstAddr, ureg8);
			_TransferIncDec = TRUE;
		}
		if (--_TransferLength <= 0) //�]����S�ďI�����Ȃ�
		{
			gCPU_Transfer = 0;
			_TF = 0;
			refreshPrevIF(); //v1.62�ǉ��B�����ōX�V���Ȃ��ƃ��b�N�I���Œe���o�Ȃ��B�����炭���@�����l�̓����ŁA�]�����߂͂Q���ߕ��ȏ�ɂȂ邽�߂��̎��ԂŐM��(�t���O)���X�V�����B
		}
		return;
	case 5: //TAI
		if (_TransferIncDec)
		{
			gCPU_ClockCount -= 5;
			_TransferIncDec = FALSE;
			ureg8 = READINC(_TransferSrcAddr);
		}
		else
		{
			gCPU_ClockCount -= 6; //6�ŃT�U���A�C�Y��OP�ŉ������s�b�^���B5,7���Ɨd�������L�̃M�����u����ʂŗ���B7�ȏゾ��SUPER���S�Q�̃^�C�g����ʂŏ�ӗ���Bv1.62�X�V
								  //"Read�A�h���X"��INC��DEC�̔��f�{������TII�����x���H(���@������)
			_TransferIncDec = TRUE;
			ureg8 = READDEC(_TransferSrcAddr);
		}
		WRITEINC(_TransferDstAddr, ureg8);
		if (--_TransferLength <= 0) //�]����S�ďI�����Ȃ�
		{
			gCPU_Transfer = 0;
			_TF = 0;
			refreshPrevIF(); //v1.62�ǉ�
		}
		return;
	}
}


// save variable
#define SAVE_V(V)	if (fwrite(&V, sizeof(V), 1, p) != 1)	return FALSE
#define LOAD_V(V)	if (fread(&V, sizeof(V), 1, p) != 1)	return FALSE
// save array
#define SAVE_A(A)	if (fwrite(A, sizeof(A), 1, p) != 1)	return FALSE
#define LOAD_A(A)	if (fread(A, sizeof(A), 1, p) != 1)		return FALSE
/*-----------------------------------------------------------------------------
	[SaveState]
		�b�o�t�̏�Ԃ��t�@�C���ɕۑ����܂��B 
-----------------------------------------------------------------------------*/
BOOL
CPU_SaveState(
	FILE*		p)
{
	BOOL	bTurboCycle = FALSE;

	if (p == NULL)
		return FALSE;

	SAVE_V(_A);
	SAVE_V(_X);
	SAVE_V(_Y);
	SAVE_V(_S);
	SAVE_V(_P);
	SAVE_V(_CF);
	SAVE_V(_ZF);
	SAVE_V(_IF);
	SAVE_V(_PrevIF); //v1.61�ǉ�
	SAVE_V(_DF);
	SAVE_V(_BF);
	SAVE_V(_TF);
	SAVE_V(_VF);
	SAVE_V(_NF);
	SAVE_V(_PC);
	SAVE_A(_MPR);

	SAVE_V(_bRDY);
	SAVE_V(_bIRQ1);
	SAVE_V(_bIRQ2);
	SAVE_V(_bNMI);
	SAVE_V(_bTIRQ);
	SAVE_V(_IntDisable); //v0.64�ǉ�
	SAVE_V(_bPrevIRQ1); //v1.61�ǉ�
	SAVE_V(_bPrevIRQ2); //v1.61�ǉ�
	SAVE_V(_bPrevTIRQ); //v1.61�ǉ�
	SAVE_V(_PrevIntDisable); //v1.61�ǉ�

	SAVE_V(gCPU_Transfer); //Kitao�ǉ�
	SAVE_V(_TransferSrcAddr); //Kitao�ǉ�
	SAVE_V(_TransferDstAddr); //Kitao�ǉ�
	SAVE_V(_TransferLength); //Kitao�ǉ�
	SAVE_V(_TransferIncDec); //Kitao�ǉ�

	SAVE_V(gCPU_ClockCount); //Kitao�ǉ�
	SAVE_V(_ClockElapsed); //Kitao�ǉ�
	SAVE_V(_bSpeedLow); //Kitao�ǉ�
	SAVE_V(bTurboCycle); //Kitao�ǉ��Bv1.61�����g�p�ɁB

	SAVE_V(_SelectVDC); //v0.89�ǉ�

	return TRUE;
}

/*-----------------------------------------------------------------------------
	[LoadState]
		�b�o�t�̏�Ԃ��t�@�C������ǂݍ��݂܂��B 
-----------------------------------------------------------------------------*/
BOOL
CPU_LoadState(
	FILE*		p)
{
	int		i;
	BOOL	bTurboCycle;

	if (p == NULL)
		return FALSE;

	LOAD_V(_A);
	LOAD_V(_X);
	LOAD_V(_Y);
	LOAD_V(_S);
	LOAD_V(_P);
	LOAD_V(_CF);
	LOAD_V(_ZF);
	LOAD_V(_IF);
	if (MAINBOARD_GetStateVersion() >= 34) //v1.61beta�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_PrevIF);
	}
	else //���o�[�W�����̃X�e�[�g��ǂ񂾏ꍇ
		_PrevIF = _IF;
	LOAD_V(_DF);
	LOAD_V(_BF);
	LOAD_V(_TF);
	LOAD_V(_VF);
	LOAD_V(_NF);
	LOAD_V(_PC);
	LOAD_A(_MPR);
	for (i=0; i<8; i++)
		if (_MPR[i] > 0xFF)
			_MPR[i] >>= 13; //v1.47���O�̃Z�[�u�f�[�^�������ꍇ�AMPR���V�t�g����Ă���̂�߂��B

	LOAD_V(_bRDY);
	LOAD_V(_bIRQ1);
	LOAD_V(_bIRQ2);
	LOAD_V(_bNMI);
	LOAD_V(_bTIRQ);
	if (MAINBOARD_GetStateVersion() >= 8) //Kitao�ǉ��Bv0.64�ȍ~�̃Z�[�u�t�@�C���Ȃ�
		LOAD_V(_IntDisable); //���o�[�W�����X�e�[�g�̏ꍇ��IntCtrl.c ����_IntDisable���ݒ肳���B
	if (MAINBOARD_GetStateVersion() >= 35) //v1.61�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_bPrevIRQ1);
		LOAD_V(_bPrevIRQ2);
		LOAD_V(_bPrevTIRQ);
	}
	else //���o�[�W�����̃X�e�[�g��ǂ񂾏ꍇ
	{
		_bPrevIRQ1 = _bIRQ1;
		_bPrevIRQ2 = _bIRQ2;
		_bPrevTIRQ = _bTIRQ;
	}
	if (MAINBOARD_GetStateVersion() >= 34) //v1.61beta�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_PrevIntDisable);
	}
	else //���o�[�W�����̃X�e�[�g��ǂ񂾏ꍇ
		_PrevIntDisable = _IntDisable;

	LOAD_V(gCPU_Transfer); //Kitao�ǉ�
	LOAD_V(_TransferSrcAddr); //Kitao�ǉ�
	LOAD_V(_TransferDstAddr); //Kitao�ǉ�
	LOAD_V(_TransferLength); //Kitao�ǉ�
	LOAD_V(_TransferIncDec); //Kitao�ǉ�

	LOAD_V(gCPU_ClockCount); //Kitao�ǉ�
	LOAD_V(_ClockElapsed); //Kitao�ǉ�
	if (MAINBOARD_GetStateVersion() < 34) //v1.61beta���O�̃Z�[�u�t�@�C���Ȃ�
		gCPU_ClockCount -= _ClockElapsed;//v1.61����f�o�b�O�ȊO��g�p�ɁB���o�[�W�����X�e�[�g�̏ꍇ�A�����ŗ��܂��Ă������������B
	LOAD_V(_bSpeedLow); //Kitao�ǉ�
	LOAD_V(bTurboCycle); //Kitao�ǉ��Bv1.61�����g�p�ɁB
	CPU_SetTurboCycle(0); //�^�[�{�T�C�N�����I�t�ɂ��A���݂̑��x��(_bSpeedLow)�ɍ��킹�ď���T�C�N�����Z�b�g�Bv1.61�ǉ�

	if (MAINBOARD_GetStateVersion() >= 17) //Kitao�ǉ��Bv0.89�ȍ~�̃Z�[�u�t�@�C���Ȃ�
	{
		LOAD_V(_SelectVDC);
	}
	else
		_SelectVDC = 0;

	return TRUE;
}

#undef SAVE_V
#undef SAVE_A
#undef LOAD_V
#undef LOAD_A

