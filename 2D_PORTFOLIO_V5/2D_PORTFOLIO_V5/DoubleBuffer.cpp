#include "DoubleBuffer.h"

DoubleBuffer::DoubleBuffer()
: hOwner(NULL)
, hMainDC(NULL), hMemDC(NULL)
, hMemBitmap(NULL)
, hOldMemBitmap(NULL)
{
}
DoubleBuffer::~DoubleBuffer()
{
	Detach();
}

void DoubleBuffer::Attach(HWND hWnd)
{
	if (hWnd == NULL) return;
	if (hOwner)
		Detach();

	hOwner = hWnd;
	::GetClientRect(hOwner, &rcClient);

	hMainDC = ::GetDC(hOwner);
	hMemDC = ::CreateCompatibleDC(hMainDC);
	hMemBitmap = ::CreateCompatibleBitmap(hMainDC, rcClient.width(), rcClient.height());
	hOldMemBitmap = ::Select(hMemDC, hMemBitmap);
}
void DoubleBuffer::Detach()
{
	if (hMemBitmap)
	{
		::Select(hMemDC, hOldMemBitmap);
		::DeleteObject(hMemBitmap);
		hMemBitmap = NULL;
	}
	if (hMemDC)
	{
		::DeleteDC(hMemDC);
		hMemDC = NULL;
	}
	if (hMainDC)
	{
		::ReleaseDC(hOwner, hMainDC);
		hMainDC = NULL;
		hOwner = NULL;
	}
}

void DoubleBuffer::Draw()
{
	if (hMemDC == NULL) return;

	::BitBlt(hMainDC, rcClient.left, rcClient.top, 
		rcClient.width(), rcClient.height(),
		hMemDC, 0, 0, SRCCOPY);
}

DoubleBuffer& DoubleBuffer::operator << (const COLORREF& clr)
{
	COLORREF old = ::SetDCBrushColor(hMemDC, clr);
	::FillRect(hMemDC, &rcClient, (HBRUSH)::GetStockObject(DC_BRUSH));
	::SetDCBrushColor(hMemDC, old);

	return *this;
}
DoubleBuffer::operator HDC ()
{
	return hMemDC;
}
