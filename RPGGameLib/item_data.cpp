#include "item_data.h"
#include "item.h"
#include "food.h"
#include "weapon.h"
#include "armor.h"

ItemData::ItemData()
{
}

ItemData::~ItemData()
{
}

void ItemData::Initial()
{
	LoadFoodData();
	LoadWeaponData();
	LoadArmorData();
}

int ItemData::TotalSize() {
	return food_array_.size() + weapon_array_.size() + armor_array_.size();
}

Item *ItemData::GetRand() {
	unsigned int randnum = rand() % TotalSize();
	if (randnum < food_array_.size()) {
		return food_array_[randnum];
	}
	randnum -= food_array_.size();
	if (randnum < weapon_array_.size()) {
		return weapon_array_[randnum];
	}
	randnum -= weapon_array_.size();
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
	cout << left << setw(15) << "�ɵ��~" << left << setw(15) << "��_" << left << setw(15) << "����" << endl;
	for (int i = 0; i < food_array_.size(); ++i)
	{
		cout << left << setw(15) << food_array_[i]->GetName() << left << setw(15) << food_array_[i]->gethpbonus() << left << setw(15) << food_array_[i]->GetMoney() << endl;
	}
	cout << left << setw(15) << "�Z��:" << left << setw(15) << "�����O" << left << setw(15) << "����" << endl;
	for (int i = 0; i < weapon_array_.size(); ++i)
	{
		cout << left << setw(15) << weapon_array_[i]->GetName() << left << setw(15) << weapon_array_[i]->getAttackbonus() << setw(15) << weapon_array_[i]->GetMoney() << endl;
	}
	cout << left << setw(15) << "�޵P:" << left << setw(15) << "���m�O" << left << setw(15) << "����" << endl;
	for (int i = 0; i < armor_array_.size(); ++i)
	{
		cout << left << setw(15) << armor_array_[i]->GetName() << left << setw(15) << armor_array_[i]->GetDefenseBonus() << setw(15) << armor_array_[i]->GetMoney() << endl;
	}
}

void ItemData::ShowFood()
{
	cout << left << setw(15) << "�s��" << left << setw(15) << "�ɵ��~" << left << setw(15) << "��_" << left << setw(15) << "����" << endl;
	for (int i = 0; i < food_array_.size(); ++i)
	{
		cout << left << setw(15) << food_array_[i]->GetID() << left << setw(15) << food_array_[i]->GetName() << left << setw(15) << food_array_[i]->gethpbonus() << left << setw(15) << food_array_[i]->GetMoney() << endl;
	}
}

void ItemData::ShowWeapon()
{
	cout << left << setw(15) << "�s��" << left << setw(15) << "�Z��:" << left << setw(15) << "�����O" << left << setw(15) << "����" << setw(15) << "����" << endl;
	for (int i = 0; i < weapon_array_.size(); ++i)
	{
		cout << left << setw(15) << weapon_array_[i]->GetID() << left << setw(15) <<
			weapon_array_[i]->GetName() << left << setw(15) << weapon_array_[i]->getAttackbonus()
			<< setw(15) << weapon_array_[i]->GetMoney() << setw(15) << weapon_array_[i]->GetLevel() << endl;
	}
}

void ItemData::ShowArmor()
{
	cout << left << setw(15) << "�s��" << left << setw(15) << "�޵P:" << left << setw(15) << "���m�O" << left << setw(15) << "����" << setw(15) << "����" << endl;
	for (int i = 0; i < armor_array_.size(); ++i)
	{
		cout << left << setw(15) << armor_array_[i]->GetID() << left << setw(15) << armor_array_[i]->GetName() << left << setw(15) << armor_array_[i]->GetDefenseBonus() << setw(15) << armor_array_[i]->GetMoney() << setw(15) << armor_array_[i]->GetLevel() << endl;
	}
}

Item * ItemData::GetItemById(int id, int type)
{
	if (type == FOOD && id < food_array_.size())
	{
		return food_array_[id];
	}
	else if (type == WEAPON &&id < weapon_array_.size())
	{
		return weapon_array_[id];
	}
	else if (type == ARMOR && id < armor_array_.size())
	{
		return armor_array_[id];
	}
	return nullptr;
}

vector<Food*> ItemData::GetFoodItem()
{
	return food_array_;
}

vector<Weapon*> ItemData::GetWeaponItem()
{
	return weapon_array_;
}

vector<Armor*> ItemData::GetArmorItem()
{
	return armor_array_;
}

void ItemData::LoadFoodData() {
	ifstream fin("food.txt");
	if (!fin) {
		cout << "Ū�ɥ���: food.txt" << endl;
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
		CGlobalInfo::itm_data->food_array_.push_back(food);
	}
	fin.close();
}

void ItemData::LoadWeaponData() {
	ifstream fin("weapon.txt");
	if (!fin) {
		cout << "Ū�ɥ���: weapon.txt" << endl;
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
		CGlobalInfo::itm_data->weapon_array_.push_back(weapon);
	}
	fin.close();
}

void ItemData::LoadArmorData()
{
	ifstream fin("armor.txt");
	if (!fin) {
		cout << "Ū�ɥ���: armor.txt" << endl;
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