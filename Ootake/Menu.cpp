/******************************************************************************
Ootake
�EMENU_InsertItem�����������B
�EMENU_RemoveItem�����������B
�E�T�u���j���[�̌��o���ɂ�ID��t������悤�ɂ����B

Copyright(C)2006-2009 Kitao Nakamura.
	�����ŁE��p�ł����J�Ȃ���Ƃ��͕K���\�[�X�R�[�h��Y�t���Ă��������B
	���̍ۂɎ���ł��܂��܂���̂ŁA�ЂƂ��Ƃ��m�点����������ƍK���ł��B
	���I�ȗ��p�͋ւ��܂��B
	���Ƃ́uGNU General Public License(��ʌ��O���p�����_��)�v�ɏ����܂��B

*******************************************************************************
	[Menu.c]

		Implements the menu interface using Windows API.

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
#include <windows.h>
#include "Menu.h"
#include "WinMain.h"


/* returns the main menu */
HANDLE
MENU_Init()
{
	return (HANDLE)CreateMenu();
}


HANDLE
MENU_CreateSubMenu()
{
	return (HANDLE)CreatePopupMenu();
}


BOOL
MENU_AddItem(
	HANDLE			hMenu,
	HANDLE			hSubMenu,
	char*			pText,
	Uint32			id)
{
	MENUITEMINFO	mii;

	mii.cbSize = sizeof(mii);

	mii.fMask = MIIM_TYPE;
	if (hSubMenu)
		mii.fMask |= MIIM_SUBMENU;
	if (id)
		mii.fMask |= MIIM_ID; //Kitao�X�V�B�T�u���j���[�̌��o���ɂ�ID��t������悤�ɂ����Bv1.61

	mii.fType      = MFT_STRING;
	mii.hSubMenu   = (HMENU)hSubMenu;
	mii.wID        = id;
	mii.dwTypeData = TEXT(pText);

	return InsertMenuItem((HMENU)hMenu, 0, TRUE, &mii);
}


//Kitao�ǉ�
BOOL
MENU_InsertItem(
	HANDLE			hMenu,
	HANDLE			hSubMenu,
	char*			pText,
	Uint32			id,
	DWORD			pos) //pos�c�}������ʒu(ID)
{
	MENUITEMINFO	mii;

	mii.cbSize = sizeof(mii);

	if (hSubMenu)
		mii.fMask = MIIM_TYPE | MIIM_SUBMENU;
	else
		mii.fMask = MIIM_TYPE | MIIM_ID;

	mii.fType      = MFT_STRING;
	mii.hSubMenu   = (HMENU)hSubMenu;
	mii.wID        = id;
	mii.dwTypeData = TEXT(pText);

	return InsertMenuItem((HMENU)hMenu, pos, FALSE, &mii);
}


BOOL
MENU_ChangeItemText(
	HANDLE			hMenu,
	Uint32			id,
	char*			pText)
{
	MENUITEMINFO	mii;

	mii.cbSize = sizeof(mii);
	mii.fMask  = MIIM_TYPE | MIIM_ID;
	mii.fType  = MFT_STRING;
	mii.wID    = id;
	mii.dwTypeData = TEXT(pText);

	return SetMenuItemInfo((HMENU)hMenu, id, FALSE, &mii);
}


HANDLE
MENU_GetSubMenu(
	HANDLE			hMenu,
	Uint32			nPos)
{
	return (HANDLE)GetSubMenu((HMENU)hMenu, nPos);
}


//Kitao�X�V
BOOL
MENU_RemoveItem(
	HANDLE			hMenu,
	Uint32			id)
{
	BOOL	ret;

	ret = DeleteMenu((HMENU)hMenu, id, MF_BYCOMMAND);
	DrawMenuBar(WINMAIN_GetHwnd());
	
	return ret;
}


BOOL
MENU_RmoveSubItem()
{
	return FALSE;
}


BOOL
MENU_CheckItem(
	HANDLE		hMenu,
	Uint32		id,
	BOOL		bChecked)
{
	return CheckMenuItem((HMENU)hMenu, id, bChecked ? MF_CHECKED : MF_UNCHECKED) != -1;
}


BOOL
MENU_CheckRadioItem(
	HANDLE		hMenu,
	Uint32		idFrom,
	Uint32		idTo,
	Uint32		idRadio)
{
	return CheckMenuRadioItem((HMENU)hMenu, idFrom, idTo, idRadio, MF_BYCOMMAND);
}


BOOL
MENU_EnableItem(
	HANDLE			hMenu,
	Uint32			id,
	BOOL			bEnabled)
{
	return EnableMenuItem((HMENU)hMenu, id, MF_BYCOMMAND | (bEnabled ? MF_ENABLED : MF_GRAYED));
}


void
MENU_Deinit(
	HANDLE		hMenu)
{
	HANDLE		hSubMenu;
	Uint32		n = 0;

	while ((hSubMenu = MENU_GetSubMenu(hMenu, n++)) != NULL)
	{
		MENU_Deinit(hSubMenu);
	}

	DestroyMenu((HMENU)hMenu);
}

/* show the main menu */
void
MENU_Show(
	HANDLE		hMenu)
{
	SetMenu(WINMAIN_GetHwnd(), (HMENU)hMenu);
}


/* show the pop-up menu (on right-click, etc.) */
void
MENU_ShowSubMenu(
	HANDLE		hSubMenu,
	Uint32		x,
	Uint32		y)
{
	HWND		hWnd = WINMAIN_GetHwnd();
	POINT		pt;

	pt.x = x;
	pt.y = y;

	ClientToScreen(hWnd, &pt);
	TrackPopupMenu((HMENU)hSubMenu, TPM_LEFTALIGN, pt.x, pt.y, 0, hWnd, NULL);
}

