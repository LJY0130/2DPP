#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;
	static DWORD update_dt = 0;
	static DWORD update_delay = 10;

	static HDC hMainDC = NULL;
	static HDC hMemDC = NULL;
	static HBITMAP hMemBitmap = NULL;
	static HBITMAP hOldMemBitmap = NULL;

	static int addy = 0; //y축 ++
	int BlockSize = 64;

	static Animation sidebar;
	static Animation map;
	static Animation block;

	static int j= rand()%8; //블록 x축 랜덤
	static int i= rand()%2; //블록 색깔 랜덤

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		backbuffer.Attach(hWnd);

		// TODO
		Image* psideImg = new Image;
		psideImg->Load(_T("SideBars.bmp"), Rect(0, 0, 1280, 800));
		psideImg->SetTransparent(RGB(255,255,255));
		sidebar.AddShot(psideImg);

		Image* pmapImg = new Image;
		pmapImg->Load(_T("Environment.bmp"), Rect(0, 0, 204, 192));
		pmapImg->SetTransparent(RGB(255,255,255));
		map.AddShot(pmapImg);

		Image* pblockImg = new Image;

		pblockImg->Load(_T("BlockSheet01b.bmp"), Rect(16, 16*i, 32, (16*i)+16));


		pblockImg->SetTransparent(RGB(255,255,255));
		block.AddShot(pblockImg);
		
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
		sidebar.SetRect(Rect(rc.left, rc.top, rc.right, rc.bottom));
		sidebar.Draw(backbuffer);

		int mapOleft = rc.left+232;
		int mapOtop = rc.top+16;
		int mapOright = rc.right-232;
		int mapObottom = rc.bottom-16;

		map.SetRect(Rect(mapOleft, mapOtop, mapOright, mapObottom));
		map.Draw(backbuffer);

		int mapIleft = rc.left+384;
		int mapItop = rc.top+16;
		int mapIright = rc.right-384;
		int mapIbottom = rc.bottom-144;


		block.SetRect(Rect(mapIleft+64*j, mapItop+addy, 
			mapIleft+64*j+BlockSize, mapItop+BlockSize+addy));
		block.Draw(backbuffer);

		backbuffer.Draw();

		::EndPaint(hWnd, &ps);
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

