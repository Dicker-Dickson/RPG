//Bag is to save Item like as food, weapon, armor. It connect Adventurer and BagEntry.
//How to use:
//Bag* bag_ = new Bag();
//Item* in_item;
//1.Inset Item
//bag_->InsertItem(in_item);
//2. Delete Item
//BagEntry* ne = bag_->LookUpItem(no);
//bag_->DeleteItem(ne);
//3. Plus/Minus/Set Money
//bag_->PlusMoeny(money);
//bag_->MinusMoney(attribute.money);
//bag_->SetMoney(attribute.money);

//The BagEntry is a kind of data structure and build for singly-linked lists(bsd-list.h).
//It saves Item.
//How to use:
//1. Insert new Item into BagEntry
//Item* in_item;
//BagEntry* new_entry = new BagEntry(in_item);
//LIST_INSERT_HEAD(&list_head_, new_entry, next_link_);
//2. Delete Item from BagEntry
//BagEntry* item_deletion;
//LIST_REMOVE(item_deletion, next_link_);

#ifndef BAG_H
#define BAG_H

#include <iostream>
#include <vector>

#include "bsd-list.h"
#include "global_info.h"
#include "item.h"
#include "definition.h"

class Item;
class ItemData;
class Food;
class Weapon;
class Armor;

class BagEntry {
	friend class Bag;
	friend class Adventurer;
public:
	BagEntry(Item *in_item = NULL, int in_num = 1);

	/// <summary> Add item number </summary>
	/// <param name="adds"> int type, input: add item number </param>
	/// <returns> void type</returns>
	void AddNumber(int adds = 1);

	/// <summary> Delete item number </summary>
	/// <param name="adds"> int type, input: delete item number </param>
	/// <returns> void type</returns>
	void DeleteNumber(int dels = 1);

	/// <summary> Get item number </summary>
	/// <returns> int type, return is item number</returns>
	int GetNumber();
private:
	LIST_ENTRY(BagEntry) next_link_;
	Item *item_;
	int number_;
};

LIST_HEAD(bag_itemlist, BagEntry);

class Bag {
public:
	Bag();
	~Bag();

	/// <summary> Add item into BagEntry</summary>
	/// <param name="item"> Item* type, input: Item </param>
	/// <returns> void type</returns>
	void InsertItem(Item * in_item);

	/// <summary> Look up BagEntry</summary>
	/// <param name="type"> int type, input: item type </param>
	/// <param name="id"> int type, input: item id</param>
	/// <returns> BagEntry* type, return is BagEntry(pointer)</returns>
	BagEntry* LookUpItem(int type, int id);

	/// <summary> Look up BagEntry</summary>
	/// <param name="bag_entry_id"> int type, input: item id of bag entry </param>
	/// <returns> BagEntry* type, return is BagEntry(pointer)</returns>
	BagEntry* LookUpItem(int bag_entry_id);

	/// <summary> Delete Item</summary>
	/// <param name="bag_entry"> BagEntry* type, input: bag entry </param>
	/// <returns> void type</returns>
	void DeleteItem(BagEntry* bag_entry);

	/// <summary> Show all items</summary>
	/// <returns> int type, return is total items number</returns>
	int ShowAllItems();

	/// <summary> Add money</summary>
	/// <param name="money"> int type, input: money </param>
	/// <returns> void type</returns>
	void PlusMoeny(int money);

	/// <summary> Show money</summary>
	/// <returns> void type</returns>
	void ShowMoney();

	/// <summary> Get money</summary>
	/// <returns> void type</returns>
	int GetMoney();

	/// <summary> Minus money</summary>
	/// <param name="money"> int type, input: money </param>
	/// <returns> void type</returns>
	void MinusMoney(int money);

	/// <summary> Set money</summary>
	/// <param name="money"> int type, input: money </param>
	/// <returns> void type</returns>
	void SetMoney(int money);

	/// <summary> Get all food in the bagentry</summary>
	/// <returns> vector&lt;Item*&gt; type</returns>
	vector<Item*> GetAllFood();

	/// <summary> Get all weapon in the bagentry</summary>
	/// <returns> vector&lt;Item*&gt; type</returns>
	vector<Item*> GetAllWeapon();

	/// <summary> Get all armor in the bagentry</summary>
	/// <returns> vector&lt;Item*&gt; type</returns>
	vector<Item*> GetAllArmor();

private:
	vector<Item*> item_food_;
	vector<Item*> item_weapon_;
	vector<Item*> item_armor_;
	bag_itemlist list_head_;
	int money_;
};
#endif