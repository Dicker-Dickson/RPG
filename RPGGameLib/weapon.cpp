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
	cout << "�Ԥh�ϥΪZ��" << getName() << ", ";
	cout << "�����O�q�쥻 " << le->GetSP();
	le->AddSP(this->getAttackbonus() + level_ * 5);
	cout << "�W�ɨ� " << le->GetSP() << endl;
}

void Weapon::UnUsed(LifeEntity *le) {
	cout << "�Ԥh " << getName() << " ";
	cout << "�����O�q�쥻 " << le->GetSP();
	le->DelSP(this->getAttackbonus() + level_ * 5);
	cout << "�U���� " << le->GetSP() << endl;
}

int Weapon::IsA() {
	return eweapon;
}

int Weapon::GetBonous()
{
	return bonus_Attack;
}