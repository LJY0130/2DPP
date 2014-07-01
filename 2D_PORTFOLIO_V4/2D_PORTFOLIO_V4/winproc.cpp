#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;
	static DWORD update_dt = 0;
	static DWORD update_delay = 10;

	static Image sidebar;		// 사이드바
	static Image map;			// 맵

	static Point AllBlock[72];	// 전체좌표

	static Block StartBlock[16];// 시작 블록
	static Point BaseBlock[16];	// 좌표

	static Block block;			// 드랍 블록
	static Point DropStart;		// 좌표

	static const int BlockSize = 64;

	static bool BrockDrop = false;	// 떨어지는 중인 블록 체크

	static int j= rand()%8;		// 블록 x좌표 랜덤
	static int i= rand()%3;		// 블록 색깔 랜덤

	int a=0;	// 반복문
	int b=0;	// 반복문

	static Sound BGM;


	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);
		backbuffer.Attach(hWnd);

		BGM.Load("sound63.mp3");
		BGM.SetLoop(true);
		BGM.SetLoopRange(8000, 20000);
		BGM.Play();

		// TODO
		sidebar.Load(_T("SideBars.bmp"));
		map.Load(_T("Environment.bmp"));
		
		for(a=0; a<8; a++)
		{
			if(b=1)
			{
				BaseBlock[a].x = 384+(BlockSize/2)+(BlockSize*a);
				BaseBlock[a].y = rc.top+656-(BlockSize/2);
			}
			if(b=2)
			{
				BaseBlock[a+8].x = 384+(BlockSize/2)+(BlockSize*a);
				BaseBlock[a+8].y = rc.top+656-(BlockSize/2)-BlockSize;
			}
		}

		if(!BrockDrop)
		{
			DropStart.x = 384+(BlockSize/2)+(BlockSize*j);
			DropStart.y = 16+(BlockSize/2);
			
			BrockDrop=true;
		}

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

		for(a=0; a<16; a++)
		{
			StartBlock[a].SetPosition(BaseBlock[a]);
			StartBlock[a].Draw(backbuffer);
		}

		if(BrockDrop)
		{
			block.SetPosition(DropStart);
			block.Draw(backbuffer);
		}

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
			
		if(BrockDrop)
			block.Update(dt);

		if(DropStart.y > 400)
			BrockDrop=false;


		dt = ::GetTickCount() - st;
		st = ::GetTickCount();

		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}

