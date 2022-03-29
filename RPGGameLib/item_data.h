//ItemData is to import item data like as food, weapon and armor.
//All list save in the food_array_, weapon_array_, armor_array_
//How to use:
//1. Initial all kinds of item by Constructer and it is a global class
//2. Total item size
//auto size = CGlobalInfo::itm_data->TotalSize();
//3. Get random item
//auto item = CGlobalInfo::itm_data->GetRand();
//4. Get random money
//auto money = CGlobalInfo::itm_data->GenerateRandomMoney()
//5. Show all item/food/weapon/armor
//CGlobalInfo::itm_data->ShowAllItem();
//CGlobalInfo::itm_data->ShowFoodItem();
//CGlobalInfo::itm_data->ShowWeaponItem();
//CGlobalInfo::itm_data->ShowArmorItem();
//6. Get item by id
//auto item = CGlobalInfo::itm_data->GetItemById(0);
//7. Get food/weapon/armor item
//auto food = CGlobalInfo::itm_data->GetFoodItem();
//auto weapon = CGlobalInfo::itm_data->GetWeaponItem();
//auto armor = CGlobalInfo::itm_data->GetArmorItem();

#ifndef ITEMDATA_H
#define ITEMDATA_H

#include <vector>
#include <iomanip>

#include "global_info.h"
#include "definition.h"
#include <fstream>
#include <iostream>

using namespace std;

class Food;
class Weapon;
class Item;
class Armor;

class ItemData {
public:
	ItemData();
	~ItemData();

	/// <summary> Initial </summary>
	/// <returns> void type</returns>
	void Initial();

	/// <summary> Size of total data </summary>
	/// <returns> int type, return is size of total data</returns>
	int TotalSize();

	/// <summary> Get random item </summary>
	/// <returns> Item* type, return is item</returns>
	Item *GetRand();

	/// <summary> Generate random money </summary>
	/// <returns> int type, return random money</returns>
	int GenerateRandomMoney();

	/// <summary> Show all items </summary>
	/// <returns> void type</returns>
	void ShowAllItem();

	/// <summary> Show food information </summary>
	/// <returns> void type</returns>
	void ShowFood();

	/// <summary> Show weapon information </summary>
	/// <returns> void type</returns>
	void ShowWeapon();

	/// <summary> Show armor information </summary>
	/// <returns> void type</returns>
	void ShowArmor();

	/// <summary> Get item by id </summary>
	/// <param name="id"> int type, input: item id </param>
	/// <param name="type"> int type, input: item type(definition) </param>
	/// <returns> Item* type, return is item</returns>
	Item* GetItemById(int id, int type);

	/// <summary> Get food items </summary>
	/// <returns> vector&lt;food*&gt; type</returns>
	vector<Food*> GetFoodItem();

	/// <summary> Get weapon items </summary>
	/// <returns> vector&lt;weapon*&gt; type</returns>
	vector<Weapon*> GetWeaponItem();

	/// <summary> Get armor items </summary>
	/// <returns> vector&lt;armor*&gt; type</returns>
	vector<Armor*> GetArmorItem();

private:
	void LoadFoodData();
	void LoadWeaponData();
	void LoadArmorData();
	vector <Food *> food_array_;
	vector <Weapon *> weapon_array_;
	vector<Armor*> armor_array_;
};

#endif