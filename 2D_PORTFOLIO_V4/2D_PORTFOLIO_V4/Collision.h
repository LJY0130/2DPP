#pragma once

#include "BaseType.h"
#include "Utility.hpp"

class CollisionImpl : public singleton<CollisionImpl>
{
   friend class singleton<CollisionImpl>;
private :
   CollisionImpl();
   virtual ~CollisionImpl();

public :
   // circle to circle;
   bool operator ()(const Point& pt1, const LONG& r1, const Point& pt2, const LONG& r2);
   // rectangle to circle
   bool operator ()(const Rect& rc, const Point& pt, const LONG& r);
   // rectangle to rectangle
   bool operator ()(const Rect& rc1, const Rect& rc2);
};

#define Collision CollisionImpl::GetReference()