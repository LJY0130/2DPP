#pragma once

#include "BaseType.h"
#include "Image.h"
#include <list>

class Animation
{
	typedef std::list<Image*> ShotType;
public :
	Animation();
	~Animation();

	void Update(DWORD tick);
	void Draw(HDC hdc);

	void AddShot(Image* img);

	void SetRect(const Rect& rc);

	void SetDelay(const DWORD& delay);
	void SetLoop(bool _bLoop = true);
	
	void Reset();

	bool IsPlaying() const;

private :
	ShotType shotlist;

	DWORD update_dt;
	DWORD update_delay;

	Rect rcDest;

	bool bLoop;

	unsigned int index;

	bool bDoNotDraw;
};
