#include <iostream>
#include "Bag.h"
#include "ItemData.h"
#include "food.h"
#include "weapon.h"
#include "armor.h"
#include <vector>

using namespace std;

BagEntry::BagEntry(Item *in_item, int in_num) {
	itm = in_item;
	number = in_num;
}

Bag::Bag() {
	LIST_INIT(&listhead);
}

Bag::~Bag() {
	BagEntry* ne = listhead.lh_first;
	BagEntry* tmp = NULL;
	while (ne) {
		tmp = ne->next_link.le_next;
		LIST_REMOVE(ne, next_link);
		ne = tmp;
	}
}

void Bag::item_insert(Item *in_item) {
	BagEntry* new_entry = new BagEntry(in_item);
	LIST_INSERT_HEAD(&listhead, new_entry, next_link);
}

BagEntry* Bag::item_lookup(int type, int id) {
	BagEntry* ne = listhead.lh_first;
	for (; ne; ne = ne->next_link.le_next) {
		if (ne->itm->IsA() == type && ne->itm->getID() == id)
			break;
	}
	return ne;
}

BagEntry* Bag::item_lookup(int no) {
	BagEntry* ne = listhead.lh_first;
	int countnum = 1;
	for (; ne; ne = ne->next_link.le_next) {
		if (no == countnum) {
			break;
		}
		countnum++;
	}
	return ne;
}

void Bag::item_delete(BagEntry* be) {
	LIST_REMOVE(be, next_link);
}

int Bag::showAllItems() {
	BagEntry* ne = listhead.lh_first;
	Item *tmp;
	int countnum = 0;
	if (ne)
		cout << "背包內容如下所示：" << endl;
	for (; ne; ne = ne->next_link.le_next) {
		tmp = ne->itm;
		cout << ++countnum << ". " << tmp->getName() << ", 數量-> " << ne->number << endl;
	}
	return countnum;
}

void Bag::AddMoeny(int m)
{
	money_ += m;
}

void Bag::ShowMoney()
{
	cout << "背包內有:" << money_ << "楓幣" << endl;
}

int Bag::GetMoney()
{
	return money_;
}

void Bag::MinusMoney(int m)
{
	money_ -= m;
}

void Bag::SetMoney(int money)
{
	money_ = money;
}

vector<Item*> Bag::GetAllFood()
{
	item_food_.clear();
	BagEntry* ne = listhead.lh_first;
	Item *tmp;
	if (ne)
		for (; ne; ne = ne->next_link.le_next) {
			tmp = ne->itm;
			auto food_list = CGlobalInfo::itm_data->GetFoodItem();
			for (int i = 0; i < food_list.size(); ++i)
			{
				if (food_list[i]->getName() == tmp->getName())
				{
					item_food_.push_back(tmp);
				}
			}
		}

	return item_food_;
}

vector<Item*> Bag::GetAllWeapon()
{
	item_weapon_.clear();
	BagEntry* ne = listhead.lh_first;
	Item *tmp;
	if (ne)
		for (; ne; ne = ne->next_link.le_next) {
			tmp = ne->itm;
			auto weapon_list = CGlobalInfo::itm_data->GetWeaponItem();
			for (int i = 0; i < weapon_list.size(); ++i)
			{
				if (weapon_list[i]->getName() == tmp->getName())
				{
					item_weapon_.push_back(tmp);
				}
			}
		}

	return item_weapon_;
}

vector<Item*> Bag::GetAllArmor()
{
	item_armor_.clear();
	BagEntry* ne = listhead.lh_first;
	Item *tmp;
	if (ne)
		for (; ne; ne = ne->next_link.le_next) {
			tmp = ne->itm;
			auto armor_list = CGlobalInfo::itm_data->GetArmorItem();
			for (int i = 0; i < armor_list.size(); ++i)
			{
				if (armor_list[i]->getName() == tmp->getName())
				{
					item_armor_.push_back(tmp);
				}
			}
		}

	return item_armor_;
}