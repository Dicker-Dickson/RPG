#include "wirehouse.h"
#include "food.h"
#include "weapon.h"
#include "ItemData.h"
#include "Item.h"

WireHouse::WireHouse()
{
}

WireHouse::~WireHouse()
{
}

void WireHouse::Load()
{
	string tmp = "./data/" + user_ + "/wirehouse.txt";
	ifstream fin(tmp, std::ios_base::binary);
	if (!fin) {
		cout << "讀檔失敗: food.txt" << endl;
		return;
	}
	string name;
	int hp_bonus;
	int inID;
	int money;

	auto food = CGlobalInfo::itm_data->GetFoodItem();

	auto weapon = CGlobalInfo::itm_data->GetWeaponItem();

	while (fin >> name) {
		for (int i = 0; i < food.size(); ++i)
		{
			if (food[i]->getName() == name)
			{
				wire_house_data_.push_back(food[i]);
				break;
			}
		}
		for (int i = 0; i < weapon.size(); ++i)
		{
			if (weapon[i]->getName() == name)
			{
				wire_house_data_.push_back(weapon[i]);
				break;
			}
		}
	}
	fin.close();
}

void WireHouse::SetUser(string user)
{
	user_ = user;
}

void WireHouse::AddItem(Item *item)
{
	wire_house_data_.push_back(item);
}

void WireHouse::ShowWireHouseData()
{
	cout << "倉庫有的物品" << endl;
	for (int i = 0; i < wire_house_data_.size(); ++i)
	{
		cout << i + 1 << "\t" << wire_house_data_[i]->getName() << endl;
	}
}

vector<Item*> WireHouse::GetWireHouseData()
{
	return wire_house_data_;
}

Item * WireHouse::GetItem(int id)
{
	if (wire_house_data_.size() > id)
	{
		auto temp = wire_house_data_[id];
		wire_house_data_.erase(wire_house_data_.begin() + id);
		return temp;
	}

	return nullptr;
}

void WireHouse::Save()
{
	string tmp = "./data/" + user_ + "/wirehouse.txt";

	ofstream fout(tmp, ios::binary);
	if (!fout) {
		cout << "讀檔失敗: bag_weapon.txt" << endl;
		system("Pause");
		exit(0);
	}

	for (int i = 0; i < wire_house_data_.size(); ++i)
	{
		fout << wire_house_data_[i]->getName() << "\n";
	}
	fout.close();
}