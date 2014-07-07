#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;
	static DWORD update_dt = 0;
	static DWORD update_delay = 10;

	static Sound BGM;

	static Image sidebar;			// 사이드바
	static Image map;				// 맵

	static Point AllBlock[8][10];	// 전체 맵(좌표정보);

	static const int BlockSize = 64;

	static Block StartBlock[16];	// 시작 블록
	static Block DropBlock;			// 드랍 블록

	static bool BrockDrop = false;	// 떨어지는 중인 블록 체크
	static int j= rand()%8;			// 블록 x좌표 랜덤

	int a=0;	// 반복문
	int b=0;	// 반복문

	static Character Ninja;

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
		
		//전체 맵에 좌표 정보 입력
		for(int c= 0; c<8; c++)
		{
			for(int d= 0; d<10; d++)
			{
				AllBlock[c][d].x = 384+(BlockSize/2)+BlockSize*c;
				AllBlock[c][d].y = rc.top+656-(BlockSize/2)-BlockSize*d;
			}
		}

		Ninja.SetPosition(Point(rc.width()/2, rc.bottom/2+128-32));

		ObjectDepot.Attach(hWnd);

		st = ::GetTickCount();
		::SetTimer(hWnd, 0, 10, NULL);
		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		// TODO
		::KillTimer(hWnd, 0);

		backbuffer.Detach();

		ObjectDepot.clear();

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
			if(a<8)
				StartBlock[a].SetPosition(AllBlock[a][0]);
			else
				StartBlock[a].SetPosition(AllBlock[a-8][1]);
			StartBlock[a].Draw(backbuffer);
		}

		DropBlock.SetPosition(AllBlock[j][9]);
		DropBlock.Draw(backbuffer);
		
		Ninja.Draw(backbuffer);

		std::wostringstream oss;
		oss << _T("x : ") << AllBlock[3][5].x << _T("\n");
		oss << _T("y : ") << AllBlock[3][5].y << _T("\n");

		::DrawText(backbuffer, oss.str().c_str(), -1, &rc, DT_TOP);


		backbuffer.Draw();
		ObjectDepot.Draw(hdc);

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
		Ninja.Input(dt);
		Ninja.Update(dt);

		DropBlock.Update(dt);

		dt = ::GetTickCount() - st;
		st = ::GetTickCount();
		
		ObjectDepot.Input(dt);
		ObjectDepot.Update(dt);

		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}

