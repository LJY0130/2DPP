#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;
	static DWORD update_dt = 0;
	static DWORD update_delay = 10;

	static HBITMAP hBlock[3] = {0};
	static std::list<HBITMAP> blocklist;
	static int index = 0;
	static int current = 0;

	static HDC hMainDC = NULL;
	static HDC hMemDC = NULL;
	static HBITMAP hMemBitmap = NULL;
	static HBITMAP hOldMemBitmap = NULL;

	static int addy = 0;	//y축 ++
	int BlockSize = 64;		//블록 지름

	static Image sidebar;	//사이드바
	static Image map;		//맵

	static Animation Bblock;//파란 블럭
	static Animation Rblock;//빨간 블럭
	static Animation Gblock;//초록 블럭

	static int j= rand()%8;	//블록 x축 랜덤
	static int i= rand()%2;	//블록 색깔 랜덤

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		backbuffer.Attach(hWnd);

		// TODO
		sidebar.Load(_T("SideBars.bmp"));
		map.Load(_T("Environment.bmp"));

		Image* pBblockImg = new Image;
		pBblockImg->Load(_T("BlockSheet01b.bmp"), Rect(16, 0, 32, 16));
		pBblockImg->SetTransparent(RGB(255,255,255));
		Bblock.AddShot(pBblockImg);

		Image* pRblockImg = new Image;
		pRblockImg->Load(_T("BlockSheet01b.bmp"), Rect(16, 16, 32, 32));
		pRblockImg->SetTransparent(RGB(255,255,255));
		Rblock.AddShot(pRblockImg);

		Image* pGblockImg = new Image;
		pGblockImg->Load(_T("BlockSheet01b.bmp"), Rect(16, 32, 32, 48));
		pGblockImg->SetTransparent(RGB(255,255,255));
		Gblock.AddShot(pGblockImg);

		blocklist.push_back(hBlock[index++%3]);

		st = ::GetTickCount();
		::SetTimer(hWnd, 0, 10, NULL);
		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		// TODO
		::KillTimer(hWnd, 0);

		backbuffer.Detach();

		::PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_PAINT)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		backbuffer << RGB(0, 0, 0);

		// TODO
		sidebar.SetRect(Rect(0, 0, 1280, 800));
		sidebar.SetTransparent(RGB(255, 255, 255));
		sidebar.Draw(backbuffer);

		int mapOleft = rc.left+232;
		int mapOtop = rc.top+16;
		int mapOright = rc.right-232;
		int mapObottom = rc.bottom-16;
		map.SetRect(Rect(mapOleft, mapOtop, mapOright, mapObottom));
		map.SetTransparent(RGB(255, 255, 255));
		map.Draw(backbuffer);

		int mapIleft = rc.left+384;
		int mapItop = rc.top+16;
		int mapIright = rc.right-384;
		int mapIbottom = rc.bottom-144;
		if(i==0)
		{
			Bblock.SetRect(Rect(mapIleft+64*j, mapItop+addy, 
				mapIleft+64*j+BlockSize, mapItop+BlockSize+addy));
			Bblock.Draw(backbuffer);
		}
		if(i==1)
		{
			Rblock.SetRect(Rect(mapIleft+64*j, mapItop+addy, 
				mapIleft+64*j+BlockSize, mapItop+BlockSize+addy));
			Rblock.Draw(backbuffer);
		}
		if(i==2)
		{
			Gblock.SetRect(Rect(mapIleft+64*j, mapItop+addy, 
				mapIleft+64*j+BlockSize, mapItop+BlockSize+addy));
			Gblock.Draw(backbuffer);
		}

		backbuffer.Draw();

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_KEYDOWN)
	{
		if ((::GetAsyncKeyState(VK_ADD) & 0x8000) == 0x8000)
		{
			blocklist.push_back(hBlock[i]);
		}

		// redraw
		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);
		return 0;
	}
	else if (uMsg == WM_ERASEBKGND)
	{
		return 1;
	}
	else if (uMsg == WM_TIMER)
	{	
		Rect rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		// TODO

		if(addy < 48)
			addy++;

		if(addy < 576)
		{
			int add = addy;
			add *= 5.11;
			addy=add/5;
		}

		dt = ::GetTickCount() - st;
		st = ::GetTickCount();

		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}

