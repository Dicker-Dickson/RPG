#ifndef ITEMDATA_H
#define ITEMDATA_H

#include <vector>
#include <iomanip>

class Food;
class Weapon;
class Item;
class Armor;

class ItemData {
public:
	ItemData() {};
	~ItemData();
	void Initialize();
	int totalsize();
	Item *getRand();
	vector <Food *> food_array;
	vector <Weapon *> weapon_array;
	vector<Armor*> armor_array_;
	int GenerateRandomMoney();
	void ShowAllItem();
	void ShowFood();
	void ShowWeapon();
	void ShowArmor();
	Item* GetItemById(int id, int);

	vector<Food*> GetFoodItem();
	vector<Weapon*> GetWeaponItem();
	vector<Armor*> GetArmorItem();

private:
	void LoadFoodData();
	void LoadWeaponData();
	void LoadArmorData();
};

#endif