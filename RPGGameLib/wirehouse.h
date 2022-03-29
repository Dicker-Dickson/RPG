#ifndef WIREHOUSE_H
#define WIREHOUSE_H

#include <iostream>
#include "global_info.h"
#include <vector>
#include "item.h"

#include <fstream>

class Item;
class ItemData;
class Food;
class Weapon;

class WireHouse {
public:
	WireHouse();
	~WireHouse();
	void Load();
	void SetUser(string);
	void AddItem(Item*);
	void ShowWireHouseData();
	vector<Item*> GetWireHouseData();
	Item* GetItem(int);
	void Save();

private:
	vector<Item*> wire_house_data_;
	string user_;
};

#endif