#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;
	static DWORD update_dt = 0;
	static DWORD update_delay = 10;

	static Image sidebar;	//사이드바
	static Image map;		//맵

	static Block StartBlock[16];//시작 블록
	static Block block;		//블록

	static int j= rand()%8;	//블록 x좌표 랜덤
	static int i= rand()%3;	//블록 색깔 랜덤*/
	static const int BlockSize = 64;

	static Point DropStart;
	static bool BrockDrop = false;	//떨어지는 중인 블록 체크

	int a=0;	//반복문

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);
		backbuffer.Attach(hWnd);

		// TODO
		sidebar.Load(_T("SideBars.bmp"));
		map.Load(_T("Environment.bmp"));

		DropStart.x = 384+(BlockSize/2)+(BlockSize*j);
		DropStart.y = 16+(BlockSize/2);

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

		block.SetPosition(DropStart);
		block.Draw(backbuffer);

		backbuffer.Draw();

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_KEYDOWN)
	{
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

		// TODO
		block.Update(dt);

		dt = ::GetTickCount() - st;
		st = ::GetTickCount();

		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}

