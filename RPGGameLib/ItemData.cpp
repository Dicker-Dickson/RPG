#include <fstream>
#include <iostream>
#include "Item.h"
#include "food.h"
#include "weapon.h"
#include "armor.h"
#include "ItemData.h"
#include "GlobalInfo.h"
#include "def.h"
using namespace std;

void ItemData::Initialize() {
	LoadFoodData();
	LoadWeaponData();
	LoadArmorData();
}

int ItemData::totalsize() {
	return food_array.size() + weapon_array.size() + armor_array_.size();
}

Item *ItemData::getRand() {
	unsigned int randnum = rand() % totalsize();
	if (randnum < food_array.size()) {
		return food_array[randnum];
	}
	randnum -= food_array.size();
	if (randnum < weapon_array.size()) {
		return weapon_array[randnum];
	}
	randnum -= weapon_array.size();
	if (randnum < armor_array_.size()) {
		return armor_array_[randnum];
	}
	return NULL;
}

int ItemData::GenerateRandomMoney()
{
	return rand() % 100;
}

void ItemData::ShowAllItem()
{
	cout << left << setw(15) << "補給品" << left << setw(15) << "恢復" << left << setw(15) << "價格" << endl;
	for (int i = 0; i < food_array.size(); ++i)
	{
		cout << left << setw(15) << food_array[i]->getName() << left << setw(15) << food_array[i]->gethpbonus() << left << setw(15) << food_array[i]->GetMoney() << endl;
	}
	cout << left << setw(15) << "武器:" << left << setw(15) << "攻擊力" << left << setw(15) << "價格" << endl;
	for (int i = 0; i < weapon_array.size(); ++i)
	{
		cout << left << setw(15) << weapon_array[i]->getName() << left << setw(15) << weapon_array[i]->getAttackbonus() << setw(15) << weapon_array[i]->GetMoney() << endl;
	}
	cout << left << setw(15) << "盾牌:" << left << setw(15) << "防禦力" << left << setw(15) << "價格" << endl;
	for (int i = 0; i < armor_array_.size(); ++i)
	{
		cout << left << setw(15) << armor_array_[i]->getName() << left << setw(15) << armor_array_[i]->GetDefenseBonus() << setw(15) << armor_array_[i]->GetMoney() << endl;
	}
}

void ItemData::ShowFood()
{
	cout << left << setw(15) << "編號" << left << setw(15) << "補給品" << left << setw(15) << "恢復" << left << setw(15) << "價格" << endl;
	for (int i = 0; i < food_array.size(); ++i)
	{
		cout << left << setw(15) << food_array[i]->getID() << left << setw(15) << food_array[i]->getName() << left << setw(15) << food_array[i]->gethpbonus() << left << setw(15) << food_array[i]->GetMoney() << endl;
	}
}

void ItemData::ShowWeapon()
{
	cout << left << setw(15) << "編號" << left << setw(15) << "武器:" << left << setw(15) << "攻擊力" << left << setw(15) << "價格" << setw(15) << "等級" << endl;
	for (int i = 0; i < weapon_array.size(); ++i)
	{
		cout << left << setw(15) << weapon_array[i]->getID() << left << setw(15) <<
			weapon_array[i]->getName() << left << setw(15) << weapon_array[i]->getAttackbonus()
			<< setw(15) << weapon_array[i]->GetMoney() << setw(15) << weapon_array[i]->GetLevel() << endl;
	}
}

void ItemData::ShowArmor()
{
	cout << left << setw(15) << "編號" << left << setw(15) << "盾牌:" << left << setw(15) << "防禦力" << left << setw(15) << "價格" << setw(15) << "等級" << endl;
	for (int i = 0; i < armor_array_.size(); ++i)
	{
		cout << left << setw(15) << armor_array_[i]->getID() << left << setw(15) << armor_array_[i]->getName() << left << setw(15) << armor_array_[i]->GetDefenseBonus() << setw(15) << armor_array_[i]->GetMoney() << setw(15) << armor_array_[i]->GetLevel() << endl;
	}
}

Item * ItemData::GetItemById(int id, int type)
{
	if (type == efood && id < food_array.size())
	{
		return food_array[id];
	}
	else if (type == eweapon &&id < weapon_array.size())
	{
		return weapon_array[id];
	}
	else if (type == armor && id < armor_array_.size())
	{
		return armor_array_[id];
	}
	return nullptr;
}

vector<Food*> ItemData::GetFoodItem()
{
	return food_array;
}

vector<Weapon*> ItemData::GetWeaponItem()
{
	return weapon_array;
}

vector<Armor*> ItemData::GetArmorItem()
{
	return armor_array_;
}

void ItemData::LoadFoodData() {
	ifstream fin("food.txt");
	if (!fin) {
		cout << "讀檔失敗: food.txt" << endl;
		return;
	}
	string name;
	int hp_bonus;
	int inID;
	int money;
	Food *food;
	while (!fin.eof()) {
		fin >> inID >> name >> hp_bonus >> money;
		food = new Food(name, 0, 0, inID, hp_bonus, money);
		CGlobalInfo::itm_data->food_array.push_back(food);
		//cout << name << " " << hp_bonus << endl;
	}
	fin.close();
}

void ItemData::LoadWeaponData() {
	ifstream fin("weapon.txt");
	if (!fin) {
		cout << "讀檔失敗: weapon.txt" << endl;
		return;
	}
	string name;
	int Attack_bonus;
	int inID;
	int money;
	int level;
	Weapon *weapon;
	while (!fin.eof()) {
		fin >> inID >> name >> Attack_bonus >> money >> level;
		weapon = new Weapon(name, 0, 0, inID, Attack_bonus, money, level);
		CGlobalInfo::itm_data->weapon_array.push_back(weapon);
		//cout << name << " " << hp_bonus << endl;
	}
	fin.close();
}

void ItemData::LoadArmorData()
{
	ifstream fin("armor.txt");
	if (!fin) {
		cout << "讀檔失敗: armor.txt" << endl;
		return;
	}
	string name;
	int defense_bonus;
	int inID;
	int money;
	int level;
	Armor *armor;
	while (!fin.eof()) {
		fin >> inID >> name >> defense_bonus >> money >> level;
		armor = new Armor(name, 0, 0, inID, defense_bonus, money, level);
		CGlobalInfo::itm_data->armor_array_.push_back(armor);
	}
	fin.close();
}