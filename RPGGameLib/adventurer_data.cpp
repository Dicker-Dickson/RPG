#include <iostream>
#include <fstream>
#include "adventurer_data.h"
#include "ItemData.h"
#include "Item.h"
#include "Bag.h"
#include "food.h"
#include "weapon.h"
#include "armor.h"

AdventurerData::AdventurerData() {
}

AdventurerData::~AdventurerData() {
}

AdventurerAttribute AdventurerData::GetAdventurerData(int id)
{
	return adventurer_data_[id];
}

void AdventurerData::Save(AdventurerAttribute attribute)
{
	string tmp = "./data/" + user_ + "/adventurerdata.txt";

	ofstream fout(tmp, ios::binary);
	if (!fout) {
		cout << "Ū�ɥ���: adventurerdata.txt" << endl;
		system("Pause");
		exit(0);
	}

	adventurer_data_[current_id_ - 1] = attribute;

	for (int i = 0; i < adventurer_data_.size(); ++i)
	{
		fout << adventurer_data_[i].id << "\t" << adventurer_data_[i].name << "\t" << adventurer_data_[i].career << "\t"
			<< adventurer_data_[i].max_hp << "\t" << adventurer_data_[i].max_mp << "\t" <<
			adventurer_data_[i].max_sp << "\t" << adventurer_data_[i].max_rough << "\t" << adventurer_data_[i].level << "\t"
			<< adventurer_data_[i].exp << "\t" << adventurer_data_[i].ability_points << "\t" << adventurer_data_[i].skill_points
			<< "\t" << adventurer_data_[i].defense << "\t" << adventurer_data_[i].dexterity << "\t" << adventurer_data_[i].strength << "\t"
			<< adventurer_data_[i].intelligence << "\t" << adventurer_data_[i].lucky << "\t" << adventurer_data_[i].money << "\n";
	}
#if 0
	for (vector<AdventurerAttribute *>::iterator it = adventurer_data_.begin(); it != adventurer_data_.end(); it++) {
		cout << (*it)->id << " " << (*it)->name << " " << (*it)->prefix_eng_name_ << " " << (*it)->max_hp << " " << (*it)->max_sp << " " << (*it)->max_rough << endl;
	}
#endif
	fout.close();
}

bool AdventurerData::NewData()
{
	if (adventurer_data_.size() < 3)
	{
		AdventurerAttribute tmp_type;

		cout << "�п�J����m�W = " << endl;
		cin >> tmp_type.name;
		tmp_type.id = adventurer_data_.size() + 1;
		tmp_type.career = "��ߪ�";
		tmp_type.max_hp = 50;
		tmp_type.max_mp = 10;
		tmp_type.max_sp = 15;
		tmp_type.max_rough = 3;
		tmp_type.level = 1;
		tmp_type.exp = 0;
		tmp_type.ability_points = 0;
		tmp_type.skill_points = 0;
		tmp_type.defense = 8;
		tmp_type.dexterity = 5;
		tmp_type.strength = 5;
		tmp_type.intelligence = 5;
		tmp_type.lucky = 5;
		tmp_type.money = 0;

		adventurer_data_.push_back(tmp_type);
		SetCurrentAdventurerId(tmp_type.id);

		Save();
		string tmp = "./data/" + user_ + "/bag_food_" + to_string(current_id_ - 1) + ".txt";
		ofstream fout(tmp, ios::binary);
		fout.close();

		tmp = "./data/" + user_ + "/bag_weapon_" + to_string(current_id_ - 1) + ".txt";
		ofstream fout2(tmp, ios::binary);
		fout2.close();

		tmp = "./data/" + user_ + "/skill_" + to_string(current_id_ - 1) + ".txt";
		ofstream fout3(tmp, ios::binary);
		fout3.close();

		return true;
	}
	else
	{
		cout << "�w�W�X�W���A�Х��R���}��" << endl;
		return false;
	}
}

void AdventurerData::ReadData(string user)
{
	user_ = user;
	adventurer_data_.clear();

	string tmp = "./data/" + user + "/adventurerdata.txt";
	ifstream fin(tmp, std::ios_base::binary);
	if (!fin) {
		cout << "Ū�ɥ���: adventurerdata.txt" << endl;
		system("Pause");
		exit(0);
	}

	int id;
	string tmp_name, tmp_career;
	int tmp_hp, tmp_mp, tmp_sp, tmp_rough, tmp_level, tmp_exp, tmp_ability_points, tmp_skill_points;
	int tmp_defense, tmp_dexterity, tmp_strength, tmp_intelligence, tmp_lucky, tmp_money;

	while (fin >> id >> tmp_name >> tmp_career >> tmp_hp >> tmp_mp >> tmp_sp >> tmp_rough >> tmp_level >> tmp_exp >> tmp_ability_points >> tmp_skill_points >> tmp_defense >> tmp_dexterity >> tmp_strength >> tmp_intelligence >> tmp_lucky >> tmp_money) {
		AdventurerAttribute tmp_type;
		tmp_type.id = id;
		tmp_type.name = tmp_name;
		tmp_type.career = tmp_career;
		tmp_type.max_hp = tmp_hp;
		tmp_type.max_mp = tmp_mp;
		tmp_type.max_sp = tmp_sp;
		tmp_type.max_rough = tmp_rough;
		tmp_type.level = tmp_level;
		tmp_type.exp = tmp_exp;
		tmp_type.ability_points = tmp_ability_points;
		tmp_type.skill_points = tmp_skill_points;
		tmp_type.defense = tmp_defense;
		tmp_type.dexterity = tmp_dexterity;
		tmp_type.strength = tmp_strength;
		tmp_type.intelligence = tmp_intelligence;
		tmp_type.lucky = tmp_lucky;
		tmp_type.money = tmp_money;

		adventurer_data_.push_back(tmp_type);

		cout << "��" << id << "�Ө���:" << tmp_name << " ¾�~:" << tmp_career << " HP:" << tmp_hp << " MP:" << tmp_mp << " SP:" << tmp_sp << " Rough:" << tmp_rough << " Level:" << tmp_level
			<< " �g���:" << tmp_exp << " �ݩ��I:" << tmp_ability_points << " �ޯ��I:" << tmp_skill_points << " ���m:" << tmp_defense << " �O�q" << tmp_strength
			<< " �ӱ�" << tmp_dexterity << " ���z" << tmp_intelligence << " ���B" << tmp_lucky << " ����" << tmp_money << endl;
	}

	fin.close();
}

void AdventurerData::SetUserName(string user)
{
	user_ = user;
}

void AdventurerData::DeleteAdventurer(int id)
{
	if (adventurer_data_.size() == 0)
	{
		cout << "�S���i�R��������A�зs�ب���" << endl;
		return;
	}

	for (int i = 0; i < adventurer_data_.size(); ++i)
	{
		if (adventurer_data_[i].id == id)
		{
			adventurer_data_.erase(adventurer_data_.begin() + i);
		}
	}

	for (int i = 0; i < adventurer_data_.size(); ++i)
	{
		adventurer_data_[i].id = i + 1;
	}

	Save();
}

void AdventurerData::SetCurrentAdventurerId(int id)
{
	current_id_ = id;
	current_career_ = adventurer_data_[id - 1].career;
}

int AdventurerData::GetCurrentAdventurerId()
{
	return current_id_;
}

void AdventurerData::PrintAdventurerData()
{
	for (int i = 0; i < adventurer_data_.size(); ++i)
	{
		cout << "��" << adventurer_data_[i].id << "�Ө���:" << adventurer_data_[i].name << "¾�~:" << adventurer_data_[i].career << " HP:" << adventurer_data_[i].max_hp <<
			" SP:" << adventurer_data_[i].max_sp << " Rough:" << adventurer_data_[i].max_rough << " Level:" << adventurer_data_[i].level
			<< " �g���:" << adventurer_data_[i].exp << " �ݩ��I:" << adventurer_data_[i].ability_points << " �ޯ��I:"
			<< adventurer_data_[i].skill_points << " ���m:" << adventurer_data_[i].defense
			<< " �O�q" << adventurer_data_[i].strength << " �ӱ�" << adventurer_data_[i].dexterity << " ���z" << adventurer_data_[i].intelligence << " ���B" << adventurer_data_[i].lucky << endl;
	}
}

void AdventurerData::Save()
{
	string tmp = "./data/" + user_ + "/adventurerdata.txt";

	ofstream fout(tmp, ios::binary);
	if (!fout) {
		cout << "Ū�ɥ���: adventurerdata.txt" << endl;
		system("Pause");
		exit(0);
	}

	for (int i = 0; i < adventurer_data_.size(); ++i)
	{
		fout << adventurer_data_[i].id << "\t" << adventurer_data_[i].name << "\t" << adventurer_data_[i].career
			<< "\t" << adventurer_data_[i].max_hp << "\t" << adventurer_data_[i].max_mp << "\t" <<
			adventurer_data_[i].max_sp << "\t" << adventurer_data_[i].max_rough << "\t" << adventurer_data_[i].level << "\t"
			<< adventurer_data_[i].exp << "\t" << adventurer_data_[i].ability_points << "\t" << adventurer_data_[i].skill_points
			<< "\t" << adventurer_data_[i].defense << "\t" << adventurer_data_[i].dexterity << "\t" << adventurer_data_[i].strength << "\t"
			<< adventurer_data_[i].intelligence << "\t" << adventurer_data_[i].lucky << "\t" << adventurer_data_[i].money << "\n";
	}

	fout.close();
}

void AdventurerData::SaveBagFood(vector<Item*> food)
{
	string tmp = "./data/" + user_ + "/bag_food_" + to_string(current_id_ - 1) + ".txt";

	ofstream fout(tmp, ios::binary);
	if (!fout) {
		cout << "Ū�ɥ���: bag_food.txt" << endl;
		system("Pause");
		exit(0);
	}

	for (int i = 0; i < food.size(); ++i)
	{
		fout << food[i]->getName() << "\n";
	}
	fout.close();
}

void AdventurerData::SaveBagWeapon(vector<Item*> weapon)
{
	string tmp = "./data/" + user_ + "/bag_weapon_" + to_string(current_id_ - 1) + ".txt";

	ofstream fout(tmp, ios::binary);
	if (!fout) {
		cout << "Ū�ɥ���: bag_weapon.txt" << endl;
		system("Pause");
		exit(0);
	}

	for (int i = 0; i < weapon.size(); ++i)
	{
		fout << weapon[i]->getName() << "\t" << weapon[i]->GetLevel() << "\n";
	}
	fout.close();
}

void AdventurerData::SaveBagArmor(vector<Item*>armor)
{
	string tmp = "./data/" + user_ + "/bag_armor_" + to_string(current_id_ - 1) + ".txt";

	ofstream fout(tmp, ios::binary);
	if (!fout) {
		cout << "Ū�ɥ���: bag_armor.txt" << endl;
		system("Pause");
		exit(0);
	}

	for (int i = 0; i < armor.size(); ++i)
	{
		fout << armor[i]->getName() << "\t" << armor[i]->GetLevel() << "\n";
	}
	fout.close();
}

void AdventurerData::LoadBagFood(string user, string id)
{
	string tmp = "./data/" + user + "/bag_food_" + id + ".txt";
	ifstream fin(tmp, std::ios_base::binary);
	if (!fin) {
		cout << "Ū�ɥ���: food.txt" << endl;
		return;
	}
	string name;

	auto food = CGlobalInfo::itm_data->GetFoodItem();
	while (fin >> name) {
		for (int i = 0; i < food.size(); ++i)
		{
			if (food[i]->getName() == name)
			{
				item_.push_back(food[i]);
				break;
			}
		}
	}
	fin.close();
}

void AdventurerData::LoadBagWeapon(string user, string id)
{
	string tmp = "./data/" + user + "/bag_weapon_" + id + ".txt";
	ifstream fin(tmp, std::ios_base::binary);
	if (!fin) {
		cout << "Ū�ɥ���: weapon.txt" << endl;
		return;
	}
	string name;
	int level;
	auto weapon = CGlobalInfo::itm_data->GetWeaponItem();
	while (fin >> name >> level) {
		for (int i = 0; i < weapon.size(); ++i)
		{
			if (weapon[i]->getName() == name)
			{
				weapon[i]->SetLevel(level);
				item_.push_back(weapon[i]);
				break;
			}
		}
	}
	fin.close();
}

void AdventurerData::LoadBagArmor(string user, string id)
{
	string tmp = "./data/" + user + "/bag_armor_" + id + ".txt";
	ifstream fin(tmp, std::ios_base::binary);
	if (!fin) {
		cout << "Ū�ɥ���: armor.txt" << endl;
		return;
	}
	string name;
	int level;
	auto armor = CGlobalInfo::itm_data->GetArmorItem();
	while (fin >> name >> level) {
		for (int i = 0; i < armor.size(); ++i)
		{
			if (armor[i]->getName() == name)
			{
				armor[i]->SetLevel(level);
				item_.push_back(armor[i]);
				break;
			}
		}
	}
	fin.close();
}

vector<Item*> AdventurerData::GetBagItem(int id)
{
	LoadBagFood(user_, to_string(id));
	LoadBagWeapon(user_, to_string(id));
	LoadBagArmor(user_, to_string(id));
	return item_;
}

string AdventurerData::GetCurrentAdventurerCareer()
{
	return current_career_;
}

vector<SkillAttribute> AdventurerData::LoadSkill(string id)
{
	string tmp = "./data/" + user_ + "/skill_" + id + ".txt";
	ifstream fin(tmp, std::ios_base::binary);
	if (!fin) {
		cout << "Ū�ɥ���: skill.txt" << endl;
		return skill_;
	}
	string name;
	int level;

	skill_.clear();

	auto skill = CGlobalInfo::skill_data->GenerateSkill();
	while (fin >> name >> level) {
		for (int i = 0; i < skill.size(); ++i)
		{
			if (skill[i].name == name)
			{
				SkillAttribute s = skill[i];
				s.level = level;
				skill_.push_back(s);
				break;
			}
		}
	}
	fin.close();
	return skill_;
}

vector<Item*> AdventurerData::LoadEquipment(string id)
{
	string tmp = "./data/" + user_ + "/equipment_" + id + ".txt";
	ifstream fin(tmp, std::ios_base::binary);
	if (!fin) {
		cout << "Ū�ɥ���: equipment.txt" << endl;
		return equipment_;
	}
	string name;
	int level;
	equipment_.clear();

	auto weapon = CGlobalInfo::itm_data->GetWeaponItem();
	auto armor = CGlobalInfo::itm_data->GetArmorItem();
	while (fin >> name >> level) {
		for (int i = 0; i < weapon.size(); ++i)
		{
			if (weapon[i]->getName() == name)
			{
				weapon[i]->SetLevel(level);
				equipment_.push_back(weapon[i]);
				break;
			}
		}
		for (int i = 0; i < armor.size(); ++i)
		{
			if (armor[i]->getName() == name)
			{
				armor[i]->SetLevel(level);
				equipment_.push_back(armor[i]);
				break;
			}
		}
	}
	fin.close();
	return equipment_;
}

void AdventurerData::SaveEquipment(vector<Item*> equipment)
{
	string tmp = "./data/" + user_ + "/equipment_" + to_string(current_id_ - 1) + ".txt";

	ofstream fout(tmp, ios::binary);
	if (!fout) {
		cout << "Ū�ɥ���: equipment.txt" << endl;
		system("Pause");
		exit(0);
	}

	for (int i = 0; i < equipment.size(); ++i)
	{
		fout << equipment[i]->getName() << "\t" << equipment[i]->GetLevel() << "\n";
	}
	fout.close();
}

void AdventurerData::SaveSkill(vector<Skill*>skill)
{
	string tmp = "./data/" + user_ + "/skill_" + to_string(current_id_ - 1) + ".txt";

	ofstream fout(tmp, ios::binary);
	if (!fout) {
		cout << "Ū�ɥ���: bag_weapon.txt" << endl;
		system("Pause");
		exit(0);
	}

	for (int i = 0; i < skill.size(); ++i)
	{
		fout << skill[i]->GetSkillName() << "\t" << skill[i]->GetLevel() - 1 << "\n";
	}
	fout.close();
}