#pragma once

#include <windows.h>
#include <tchar.h>
#include "BaseType.h"
#include "Utility.hpp"

class DoubleBuffer : public singleton<DoubleBuffer>
{
	friend class singleton<DoubleBuffer>;

	typedef DoubleBuffer Me;
private :
	DoubleBuffer();
	~DoubleBuffer();

public :
	void Attach(HWND hWnd);
	void Detach();

	void Draw();

	Me& operator << (const COLORREF& clr);
	operator HDC ();

private :
	HWND hOwner;

	HDC hMainDC;
	HDC hMemDC;
	HBITMAP hMemBitmap;
	HBITMAP hOldMemBitmap;
	Rect rcClient;
};

#define backbuffer DoubleBuffer::GetReference()