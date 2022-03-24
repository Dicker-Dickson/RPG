#include "adventurer.h"
#include <iostream>
#include "food.h"
#include "GlobalInfo.h"
#include "MapData.h"
#include "skill.h"

Adventurer::Adventurer()
{
	bag_ = new Bag();
}

Adventurer::~Adventurer()
{
}

int Adventurer::GetLucky()
{
	return defense_;
}

int Adventurer::Attack(LifeEntity * l)
{
	if (IsUseSkill(l))
	{
	}
	else {
		int damage = PhysicalDamage() - l->Defense();
		if (damage > l->GetHP())
			damage = l->GetHP();

		l->GetHurt(damage);

		if (damage > 0) {
			cout << this->GetName() << " 猛力一揮，造成 " << l->GetName() << " " << damage << " 血損失" << endl;
		}
		else {
			cout << this->GetName() << " 猛力一揮，但是 " << l->GetName() << " 強力一擋，因此沒有造成任何損失" << endl;
		}
		return (damage > 0 ? damage : 0);
	}
}

int Adventurer::Defense()
{
	return 	defense_;
}

void Adventurer::CaptureItem(Item *in_item)
{
	BagEntry *entry = bag_->item_lookup(in_item->IsA(), in_item->getID());
	if (!entry)
		bag_->item_insert(in_item);
	else
		entry->addNum(1);
	cout << this->GetName() << " 從地上撿起 " << in_item->getName() << endl;
}

vector<Item*> Adventurer::GetBagAllFood()
{
	return bag_->GetAllFood();
}

vector<Item*> Adventurer::GetBagAllWeapon()
{
	return bag_->GetAllWeapon();
}

vector<Item*> Adventurer::GetBagAllArmor()
{
	return bag_->GetAllArmor();
}

void Adventurer::PutItem(Item *in_item)
{
	BagEntry *entry = bag_->item_lookup(in_item->IsA(), in_item->getID());
	if (!entry)
	{
		bag_->item_insert(in_item);
	}
	else
	{
		entry->addNum(1);
	}
}

Item * Adventurer::GetItem(int no)
{
	BagEntry* ne = bag_->item_lookup(no);
	if (ne)
	{
		auto temp = ne->itm;
		ne->deleteNum(1);
		if (ne->getNum() == 0)
		{
			bag_->item_delete(ne);
		}
		return temp;
	}
	return nullptr;
}

vector<Item *> Adventurer::GetEquipment()
{
	equipment_.clear();
	if (this->GetWeapon())
	{
		equipment_.push_back((Item *) this->GetWeapon());
	}

	if (this->GetArmor())
	{
		equipment_.push_back((Item *) this->GetArmor());
	}
	return equipment_;
}

void Adventurer::BuyItem(Item * in_item)
{
	BagEntry *entry = bag_->item_lookup(in_item->IsA(), in_item->getID());
	if (!entry)
		bag_->item_insert(in_item);
	else
		entry->addNum(1);
	cout << this->GetName() << " 買入 " << in_item->getName() << endl;
}

bool Adventurer::SellItem(Item *in_item)
{
	BagEntry *entry = bag_->item_lookup(in_item->IsA(), in_item->getID());
	if (entry)
	{
		cout << "賣出" << in_item->getName() << endl;
		entry->deleteNum(1);
		if (entry->getNum() == 0)
		{
			bag_->item_delete(entry);
		}
		return true;
	}
	else
	{
		cout << "背包內沒有此物品" << endl;
		system("Pause");
		return false;
	}
}

void Adventurer::CaptureMoney(int money)
{
	bag_->AddMoeny(money);
	SaveMoney();
}

int Adventurer::ShowAllBagItems()
{
	return bag_->showAllItems();
}

void Adventurer::ShowMoney()
{
	bag_->ShowMoney();
}

bool Adventurer::UseBagItems(int no)
{
	BagEntry* ne = bag_->item_lookup(no);
	if (!ne) {
		return false;
	}
	if (!IsCareerSpecialEquipment(ne))
	{
		cout << "此職業無法裝配" << endl;
		system("Pause");
		return false;
	}
	if (ne->itm->IsA() == eweapon) {
		Weapon *cur_weapon = this->GetWeapon();
		if (cur_weapon != NULL) {
			Item *weapon_item = (Item *)cur_weapon;
			BagEntry *entry = bag_->item_lookup(weapon_item->IsA(), weapon_item->getID());
			if (!entry)
				bag_->item_insert(weapon_item);
			else
				entry->addNum(1);
			cout << this->GetName() << " 將手上武器 " << weapon_item->getName() << " 放回背包中" << endl;
			weapon_item->UnUsed(this);
		}
		this->SetWeapon((Weapon *)ne->itm);
	}
	else if (ne->itm->IsA() == armor) {
		Armor *cur_armor = this->GetArmor();
		if (cur_armor != NULL) {
			Item *armor_item = (Item *)cur_armor;
			BagEntry *entry = bag_->item_lookup(armor_item->IsA(), armor_item->getID());
			if (!entry)
				bag_->item_insert(armor_item);
			else
				entry->addNum(1);
			cout << this->GetName() << " 將手上盾牌 " << armor_item->getName() << " 放回背包中" << endl;
			armor_item->UnUsed(this);
		}
		this->SetArmor((Armor *)ne->itm);
	}

	if (ne->itm->getName() == "防禦藥水")
	{
		Food * food = (Food *)ne->itm;
		defense_skill_count = 3;
		AddDefense(food->GetBonous());
		ne->deleteNum();
		if (ne->getNum() == 0) {
			bag_->item_delete(ne);
		}
		this->ShowAllBagItems();
		return true;
	}
	else if (ne->itm->getName() == "攻擊藥水")
	{
		Food * food = (Food *)ne->itm;
		attack_skill_count = 3;
		attack_increase_value = food->GetBonous();
		ne->deleteNum();
		if (ne->getNum() == 0) {
			bag_->item_delete(ne);
		}
		this->ShowAllBagItems();
		return true;
	}
	else if (ne->itm->getName() == "藍色藥水")
	{
		AddMP(50);

		ne->deleteNum();
		if (ne->getNum() == 0) {
			bag_->item_delete(ne);
		}
		this->ShowAllBagItems();
		return true;
	}
	else if (ne->itm->getName() == "活力藥水")
	{
		AddMP(150);

		ne->deleteNum();
		if (ne->getNum() == 0) {
			bag_->item_delete(ne);
		}
		this->ShowAllBagItems();
		return true;
	}
	ne->itm->beUsed(this);
	ne->deleteNum();
	if (ne->getNum() == 0) {
		bag_->item_delete(ne);
	}
	this->ShowAllBagItems();
	return true;
}

int Adventurer::GoToNextCity(int next_dir)
{
	int NextCity = CGlobalInfo::map_data->NextCity(current_city_, next_dir);
	if (NextCity) {
		current_city_ = NextCity;
		return current_city_;
	}
	return 0;
}

int Adventurer::MoveCity(int city)
{
	if (city > 0 && city < 7)
	{
		current_city_ = city;
		return current_city_;
	}
	else
		return 0;
}

int Adventurer::GetCurrentCity()
{
	return current_city_;
}

int Adventurer::IsA()
{
	return adventurer;
}

void Adventurer::AddDefense(int value)
{
	defense_ = attribute_.defense + value;
}

void Adventurer::DefenseReset()
{
	defense_ = attribute_.defense;
}

void Adventurer::PrintDefenseCount()
{
	if (defense_skill_count > 0)
	{
		cout << "防禦力強化還剩下" << defense_skill_count << "回合" << endl;
	}
}

void Adventurer::DefenseCount()
{
	if (defense_skill_count == 1)
	{
		cout << "防禦加成效果消失，防禦力為:" << attribute_.defense << endl;
		DefenseReset();
		defense_skill_count = 0;
	}

	defense_skill_count <= 1 ? 0 : defense_skill_count--;
}

void Adventurer::AttackCount()
{
	if (attack_skill_count == 1)
	{
		cout << "攻擊加成效果消失" << endl;
		attack_increase_value = 0;
		attack_skill_count = 0;
	}

	attack_skill_count <= 1 ? 0 : attack_skill_count--;
}

void Adventurer::LevelUpWeapon()
{
	auto w = this->GetWeapon();
	w->AddLevel(1);
}

void Adventurer::LevelUpArmor()
{
	auto a = this->GetArmor();
	a->AddLevel(1);
}

void Adventurer::PrintAttackCount()
{
	if (attack_skill_count > 0)
	{
		cout << "攻擊力強化還剩下" << attack_skill_count << "回合" << endl;
	}
}

void Adventurer::ReadData()
{
	auto id = CGlobalInfo::adventurer_data->GetCurrentAdventurerId();
	auto attribute = CGlobalInfo::adventurer_data->GetAdventurerData(id - 1);

	attribute_ = attribute;
	SetInitSPHPMP(attribute_.max_hp, attribute_.max_sp, attribute_.max_mp);
	SetLevel(attribute.level);
	SetExp(attribute.exp);
	SetName(attribute_.name);
	defense_ = attribute_.defense;
	current_city_ = 1;
	bag_->SetMoney(attribute.money);

	auto item_data = CGlobalInfo::adventurer_data->GetBagItem(id - 1);
	for (int i = 0; i < item_data.size(); ++i)
	{
		BagEntry *entry = bag_->item_lookup(item_data[i]->IsA(), item_data[i]->getID());
		if (!entry)
			bag_->item_insert(item_data[i]);
		else
			entry->addNum(1);
	}

	auto skill = CGlobalInfo::adventurer_data->LoadSkill(to_string(id - 1));
	for (int i = 0; i < skill.size(); ++i)
	{
		LearnSkill(skill[i]);
	}

	auto equipment = CGlobalInfo::adventurer_data->LoadEquipment(to_string(id - 1));
	for (int i = 0; i < equipment.size(); ++i)
	{
		if (equipment[i]->IsA() == eweapon)
		{
			this->SetWeapon((Weapon*)equipment[i]);
		}
		else if (equipment[i]->IsA() == armor)
		{
			this->SetArmor((Armor*)equipment[i]);
		}
	}
}

AdventurerAttribute Adventurer::GetAttribute()
{
	attribute_.max_hp = GetMaxHP();
	attribute_.max_mp = GetMaxMP();
	attribute_.max_sp = GetMaxSP();
	attribute_.level = GetLevel();
	attribute_.exp = GetExp();

	return attribute_;
}

void Adventurer::SetAbilityPoints(int points)
{
	attribute_.ability_points = points;
}

int Adventurer::GetAbilityPoints()
{
	return attribute_.ability_points;
}

void Adventurer::SetSkillPoints(int p)
{
	attribute_.skill_points = p;
}

void Adventurer::AddSkillPoints(int p)
{
	attribute_.skill_points += p;
}

int Adventurer::GetSkillPoints()
{
	return attribute_.skill_points;
}

bool Adventurer::IsCareerSpecialEquipment(BagEntry* ne)
{
	auto weapon_name = ne->itm->getName();
	if (weapon_name == "武士刀" &&IsA() != warrior)
	{
		return false;
	}
	else if (weapon_name == "精靈短杖" &&IsA() != magician)
	{
		return false;
	}
	else if (weapon_name == "戰鬥弓"&& IsA() != archer)
	{
		return false;
	}
	else if (weapon_name == "飛影刃"&& IsA() != thief)
	{
		return false;
	}

	return true;
}

void Adventurer::SpendAbilityPoints()
{
	while (attribute_.ability_points != 0)
	{
		system("CLS");

		cout << "您目前屬性如下" << endl;
		cout << "力量 = " << attribute_.strength << endl;
		cout << "敏捷 = " << attribute_.dexterity << endl;
		cout << "智慧 = " << attribute_.intelligence << endl;
		cout << "幸運 = " << attribute_.lucky << endl;

		cout << "屬性點還剩下 = " << attribute_.ability_points << endl;
		cout << "加力量請輸入1，加敏捷請輸入2，加智慧請輸入3，加幸運請輸入4，要離開請輸入Q" << endl;
		string selection;
		cin >> selection;
		if (selection == "1")
		{
			attribute_.strength += 1;
			attribute_.ability_points -= 1;
		}
		else if (selection == "2")
		{
			attribute_.dexterity += 1;
			attribute_.ability_points -= 1;
		}
		else if (selection == "3")
		{
			attribute_.intelligence += 1;
			attribute_.ability_points -= 1;
		}
		else if (selection == "4")
		{
			attribute_.lucky += 1;
			attribute_.ability_points -= 1;
		}
		else if (selection == "Q" || selection == "q")
		{
			return;
		}
	}
}

void Adventurer::PrintAdventurerAttribute()
{
	cout << "姓名:" << attribute_.name << endl;
	cout << "等級:" << attribute_.level << endl;
	cout << "HP:" << GetHP() << "/" << attribute_.max_hp << endl;
	cout << "MP:" << GetMP() << "/" << attribute_.max_mp << endl;
	cout << "SP:" << attribute_.max_sp << endl;
	cout << "防禦力(未加防具前):" << attribute_.defense << endl;
	cout << "經驗值:" << attribute_.exp << "/" << (attribute_.level + 2) * 5 << endl;
	cout << "屬性點:" << attribute_.ability_points << endl;
	cout << "技能點:" << attribute_.skill_points << endl;
	cout << "力量 = " << attribute_.strength << endl;
	cout << "敏捷 = " << attribute_.dexterity << endl;
	cout << "智慧 = " << attribute_.intelligence << endl;
	cout << "幸運 = " << attribute_.lucky << endl;
}

void Adventurer::PrintEquipment()
{
	Weapon *cur_weapon = this->GetWeapon();
	if (cur_weapon)
		cout << "身上的武器為:" << cur_weapon->getName() << " 等級為:" << cur_weapon->GetLevel()
		<< "攻擊力為:" << cur_weapon->getAttackbonus() + cur_weapon->GetLevel() * 5 << endl;

	Armor * cur_armor = this->GetArmor();
	if (cur_armor)
		cout << "身上的盾牌:" << cur_armor->getName() << " 等級為:" << cur_armor->GetLevel() <<
		"防禦力為:" << cur_armor->GetDefenseBonus() + cur_armor->GetLevel() * 3 << endl;
}

void Adventurer::SaveMoney()
{
	attribute_.money = bag_->GetMoney();
}

void Adventurer::AddMoney(int money)
{
	bag_->AddMoeny(money);
	SaveMoney();
}

void Adventurer::MinusMoney(int money)
{
	bag_->MinusMoney(money);
	SaveMoney();
}

int Adventurer::GetMoney()
{
	return bag_->GetMoney();
}

void Adventurer::SetCareer(string career)
{
	attribute_.career = career;
}

void Adventurer::ShowSkill()
{
	cout << "初心者沒有技能" << endl;
}

bool Adventurer::IsUseSkill(LifeEntity *l)
{
	if (GetSkillNumber())
	{
		ShowSkill();
		cout << "不使用技能輸入0，使用技能輸入技能id" << endl;
		string t;
		cin >> t;

		if (t == "0")
			return false;
		else if (t == "1" || t == "2")
		{
			if (GetMP() < SkillUseMP(stoi(t) - 1))
			{
				cout << "MP不夠，使用一般攻擊" << endl;
				return false;
			}
			int use_mp = SkillUseMP(stoi(t) - 1);
			cout << "消耗MP:" << use_mp << " 目前MP:" << GetMP() << "/" << GetMaxMP() << endl;
			DelMP(use_mp);

			UseSkillById(l, stoi(t) - 1);
			return true;
		}
	}
}

int Adventurer::SkillUseMP(int id)
{
	return 0;
}

vector<Skill*> Adventurer::GetSkill()
{
	return vector<Skill*>();
}