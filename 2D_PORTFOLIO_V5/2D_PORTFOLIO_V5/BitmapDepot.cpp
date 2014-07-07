#include "BitmapDepot.h"

BitmapManager::BitmapManager()
{
}
BitmapManager::~BitmapManager()
{
	DepotType::iterator it;
	for (it = depot.begin(); it != depot.end();)
	{
		::DeleteObject(it->second);
		it = depot.erase(it);
	}
}
void BitmapManager::push(const KeyType& key, const DataType& data)
{
	DepotType::iterator it = depot.find(key);
	if (it == depot.end())
	{
		depot.insert(std::make_pair(key,data));
	}
}
BitmapManager::DataType BitmapManager::get(const KeyType& key)
{
	DepotType::iterator it = depot.find(key);
	if (it == depot.end())
	{
		return NULL;
	}

	return it->second;
}
