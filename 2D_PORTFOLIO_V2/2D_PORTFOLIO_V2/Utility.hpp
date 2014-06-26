#pragma once

template<typename GDIObject>
GDIObject Select(HDC hdc, GDIObject obj)
{
	return (GDIObject)::SelectObject(hdc, obj);
}

template<typename T>
class singleton
{
protected :
	singleton(){}
	virtual ~singleton(){}

public :
	static T& GetReference()
	{
		static T instance;
		return instance;
	}
};