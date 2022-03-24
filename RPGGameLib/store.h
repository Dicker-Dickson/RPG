#ifndef STORE_H
#define STORE_H

#include <vector>
#include "GlobalInfo.h"

class ItemData;
class Item;
class Bag;

using namespace std;
class Store
{
public:
	Store();
	~Store();
	void InsertItem(Item* item);
	void ShowAllItem();

private:
	vector<Item*> item_list_;
};

#endif