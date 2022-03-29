#include "bag.h"
#include "item_data.h"
#include "food.h"
#include "weapon.h"
#include "armor.h"

using namespace std;

BagEntry::BagEntry(Item *in_item, int in_num) {
	item_ = in_item;
	number_ = in_num;
}

void BagEntry::AddNumber(int adds)
{
	number_ += adds;
}

void BagEntry::DeleteNumber(int dels)
{
	number_ -= dels;
}

int BagEntry::GetNumber()
{
	return number_;
}

Bag::Bag() {
	LIST_INIT(&list_head_);
}

Bag::~Bag() {
	BagEntry* ne = list_head_.lh_first;
	BagEntry* tmp = NULL;
	while (ne) {
		tmp = ne->next_link_.le_next;
		LIST_REMOVE(ne, next_link_);
		ne = tmp;
	}
}

void Bag::InsertItem(Item *in_item) {
	BagEntry* new_entry = new BagEntry(in_item);
	LIST_INSERT_HEAD(&list_head_, new_entry, next_link_);
}

BagEntry* Bag::LookUpItem(int type, int id) {
	BagEntry* ne = list_head_.lh_first;
	for (; ne; ne = ne->next_link_.le_next) {
		if (ne->item_->IsA() == type && ne->item_->GetID() == id)
			break;
	}
	return ne;
}

BagEntry* Bag::LookUpItem(int bag_entry_id) {
	BagEntry* ne = list_head_.lh_first;
	int countnum = 1;
	for (; ne; ne = ne->next_link_.le_next) {
		if (bag_entry_id == countnum) {
			break;
		}
		countnum++;
	}
	return ne;
}

void Bag::DeleteItem(BagEntry* bag_entry) {
	LIST_REMOVE(bag_entry, next_link_);
}

int Bag::ShowAllItems() {
	BagEntry* ne = list_head_.lh_first;
	Item *tmp;
	int countnum = 0;
	if (ne)
		cout << "背包內容如下所示：" << endl;
	for (; ne; ne = ne->next_link_.le_next) {
		tmp = ne->item_;
		cout << ++countnum << ". " << tmp->GetName() << ", 數量-> " << ne->number_ << endl;
	}
	return countnum;
}

void Bag::PlusMoeny(int money)
{
	money_ += money;
}

void Bag::ShowMoney()
{
	cout << "背包內有:" << money_ << "楓幣" << endl;
}

int Bag::GetMoney()
{
	return money_;
}

void Bag::MinusMoney(int money)
{
	money_ - money >= 0 ? money_ -= money : 0;
}

void Bag::SetMoney(int money)
{
	money >= 0 ? money_ = money : 0;
}

vector<Item*> Bag::GetAllFood()
{
	item_food_.clear();
	BagEntry* ne = list_head_.lh_first;
	Item *tmp;
	if (ne)
		for (; ne; ne = ne->next_link_.le_next) {
			tmp = ne->item_;
			auto food_list = CGlobalInfo::itm_data->GetFoodItem();
			for (int i = 0; i < food_list.size(); ++i)
			{
				if (food_list[i]->GetName() == tmp->GetName())
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
	BagEntry* ne = list_head_.lh_first;
	Item *tmp;
	if (ne)
		for (; ne; ne = ne->next_link_.le_next) {
			tmp = ne->item_;
			auto weapon_list = CGlobalInfo::itm_data->GetWeaponItem();
			for (int i = 0; i < weapon_list.size(); ++i)
			{
				if (weapon_list[i]->GetName() == tmp->GetName())
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
	BagEntry* ne = list_head_.lh_first;
	Item *tmp;
	if (ne)
		for (; ne; ne = ne->next_link_.le_next) {
			tmp = ne->item_;
			auto armor_list = CGlobalInfo::itm_data->GetArmorItem();
			for (int i = 0; i < armor_list.size(); ++i)
			{
				if (armor_list[i]->GetName() == tmp->GetName())
				{
					item_armor_.push_back(tmp);
				}
			}
		}

	return item_armor_;
}