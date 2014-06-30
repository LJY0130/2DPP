#include "Collision.h"


CollisionImpl::CollisionImpl()
{
}
CollisionImpl::~CollisionImpl()
{
}

// circle to circle;
bool CollisionImpl::operator ()(const Point& pt1, const LONG& r1, const Point& pt2, const LONG& r2)
{
   if ((r1 + r2)*(r1 + r2) >= (pt1 ^ pt2))
      return true;

   return false;
}
// rectangle to circle
bool CollisionImpl::operator ()(const Rect& rc, const Point& pt, const LONG& r)
{
   Point d = pt - rc.center();

   if (abs(d.x) > r + rc.width()/2 || abs(d.y) > r + rc.height()/2)
      return false;

   if (abs(d.x) <= rc.width()/2 || abs(d.y) <= rc.height()/2)
      return true;

   float dist = sqrt(float(d.x*d.x + d.y*d.y));

   return (dist <= r + rc.radius());
}
// rectangle to rectangle
bool CollisionImpl::operator ()(const Rect& rc1, const Rect& rc2)
{
   return !(rc1.left > rc2.right || rc1.right < rc2.left ||
            rc1.top > rc2.bottom || rc1.bottom < rc2.top);
}
