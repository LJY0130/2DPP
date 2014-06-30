#include "BaseType.h"

Point::Point()
{
	x = y = 0;
}
Point::Point(const LONG& _x, const LONG& _y)
{
	x = _x;
	y = _y;
}
Point Point::operator + (const Point& o) const
{
	return Point(x + o.x, y + o.y);
}
Point Point::operator - (const Point& o) const
{
	return Point(x - o.x, y - o.y);
}
LONG Point::operator ^ (const Point& o) const
{
	Point d = *this - o;
	return (d.x*d.x + d.y*d.y);
}
Point Point::ToClient(HWND hWnd) const
{
	Point tmp(*this);
	::ScreenToClient(hWnd, &tmp);
	return tmp;
}
Point Point::ToScreen(HWND hWnd) const
{
	Point tmp(*this);
	::ClientToScreen(hWnd, &tmp);
	return tmp;
}
bool Point::operator == (const Point& o) const
{
	return (x == o.x && y == o.y);
}
bool Point::operator != (const Point& o) const
{
	return (x != o.x || y != o.y);
}

Size::Size()
{
	cx = cy = 0;
}
Size::Size(const LONG& _cx, const LONG& _cy)
{
	cx = _cx;
	cy = _cy;
}
Rect::Rect()
{
	left = top = right = bottom = 0;
}
Rect::Rect(const LONG& l, const LONG& t, const LONG& r, const LONG& b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}
Rect::Rect(const Point& ct, const Size& cs)
{
	left = ct.x - cs.cx/2;
	top = ct.y - cs.cy/2;
	right = left + cs.cx;
	bottom = top + cs.cy;
}
Point Rect::lefttop() const
{
	return Point(left, top);
}
Point Rect::rightbottom() const
{
	return Point(right, bottom);
}
Point Rect::center() const
{
	return Point((left+right)/2, (top+bottom)/2);
}
LONG Rect::width() const
{
	return (right - left);
}
LONG Rect::height() const
{
	return (bottom - top);
}
float Rect::radius() const
{
   return sqrt(float(width()*width() + height()*height()))/2;
}
Vector::Vector()
: x(1.f), y(0.f)
{
}
Vector::Vector(const float& _x, const float& _y)
: x(_x), y(_y)
{
}
Vector::Vector(const Point& pt)
: x(float(pt.x)), y(float(pt.y))
{
}

float Vector::size() const
{
	return sqrt(x*x + y*y);
}
Vector Vector::normalize() const
{
	return Vector(x/size(), y/size());
}
Vector Vector::operator + (const Vector& o) const
{
	return Vector(x + o.x, y + o.y);
}
Vector Vector::operator - (const Vector& o) const
{
	return Vector(x - o.x, y - o.y);
}
Vector::operator Point ()
{
	return Point(LONG(x), LONG(y));
}
bool Vector::operator == (const Vector& o) const
{
	const float e = 1E1f;

	if (x - e < o.x && o.x < x + e &&
		y - e < o.y && o.y < y + e)
	{
		return true;
	}

	return false;
}
bool Vector::operator != (const Vector& o) const
{
	return !(*this == o);
}
