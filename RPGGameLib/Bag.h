#ifndef BAG_H
#define BAG_H

#include <iostream>
#include "bsd-list.h"
#include "GlobalInfo.h"
#include <vector>
#include "Item.h"
#include "def.h"

class Item;
class ItemData;
class Food;
class Weapon;
class Armor;

class BagEntry {
	friend class Bag;
	friend class Adventurer;
	friend class CFighter;
public:
	BagEntry(Item *in_item = NULL, int in_num = 1);
	void addNum(int adds = 1) { number += adds; };
	void deleteNum(int dels = 1) { number -= dels; };
	int getNum() { return number; };
private:
	LIST_ENTRY(BagEntry) next_link;
	Item *itm;
	int number;
};

LIST_HEAD(bag_itemlist, BagEntry);

class Bag {
public:
	Bag();
	~Bag();
	void item_insert(Item *);
	BagEntry* item_lookup(int type, int id);
	BagEntry* item_lookup(int no);
	void item_delete(BagEntry*);
	int showAllItems();
	void AddMoeny(int);
	void ShowMoney();
	int GetMoney();
	void MinusMoney(int);
	void SetMoney(int);

	vector<Item*> GetAllFood();
	vector<Item*> GetAllWeapon();
	vector<Item*> GetAllArmor();

private:
	vector<Item*> item_food_;
	vector<Item*> item_weapon_;
	vector<Item*> item_armor_;

	bag_itemlist listhead;
	int money_;
};

#endif