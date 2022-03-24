#include <iostream>
#include "Item.h"
#include "weapon.h"
#include "LifeEntity.h"
#include "def.h"

using namespace std;

Weapon::Weapon(string inname, int initSize, int initWeight, int initID, int init_Attack, int money, int level) : Item(inname, initSize, initWeight, initID, money) {
	bonus_Attack = init_Attack;
	level_ = level;
}

int Weapon::getAttackbonus() {
	return bonus_Attack;
}

int Weapon::GetLevel()
{
	return level_;
}

void Weapon::AddLevel(int l)
{
	level_ += l;
}

void Weapon::SetLevel(int l)
{
	level_ = l;
}

void Weapon::beUsed(LifeEntity *le) {
	cout << "戰士使用武器" << getName() << ", ";
	cout << "攻擊力從原本 " << le->GetSP();
	le->AddSP(this->getAttackbonus() + level_ * 5);
	cout << "上升到 " << le->GetSP() << endl;
}

void Weapon::UnUsed(LifeEntity *le) {
	cout << "戰士 " << getName() << " ";
	cout << "攻擊力從原本 " << le->GetSP();
	le->DelSP(this->getAttackbonus() + level_ * 5);
	cout << "下降到 " << le->GetSP() << endl;
}

int Weapon::IsA() {
	return eweapon;
}

int Weapon::GetBonous()
{
	return bonus_Attack;
}