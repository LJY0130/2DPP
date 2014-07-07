#pragma once

#include <windows.h>
#include "Utility.hpp"
#include <string>
#include <map>

class BitmapManager : public singleton<BitmapManager>
{
	friend class singleton<BitmapManager>;
public :
	typedef std::wstring KeyType;
	typedef HBITMAP DataType;
	typedef std::map<KeyType,DataType> DepotType;
private :
	BitmapManager();
	~BitmapManager();
public :
	void push(const KeyType& key, const DataType& data);
	DataType get(const KeyType& key);
private :
	DepotType depot;
};

#define BitmapDepot BitmapManager::GetReference()