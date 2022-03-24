#include <iostream>
#include <string>
#include "Monster.h"
#include "MonsterData.h"
#include "def.h"

using namespace std;
Monster::Monster(int initHP, int initSP, int initMP, int initrough, string init_name, string init_eng_name_) : LifeEntity(initHP, initSP, initMP, init_name), rough_degree_(initrough), eng_name_(init_eng_name_) {
	counter_for_monster_id_++;
	cout << "one monster called " << init_name << " (" << init_eng_name_ << ") is created with <hp_,mp_, sp_, rough, level, exp> = <"
		<< initHP << ", " << initMP << ",　" << initSP << ", " << initrough << ">" << ", " << endl;
}

Monster::Monster(const MonsterType *type) :
	LifeEntity((type->max_hp*0.9) + 0.2*(rand() % type->max_hp), ((type->max_sp*0.9)) + 0.2*(rand() % type->max_sp), 1, type->name, type->level, type->exp),
	rough_degree_(type->max_rough) {
	counter_for_monster_id_++;

	eng_name_ = type->prefix_eng_name + to_string((long double)counter_for_monster_id_);
	cout << type->name << "/ 等級=" << type->level << " HP=" << this->GetHP() << " SP=" << this->GetSP() << " Rough=" << this->GetRough() << endl;
	id_ = type->id;
}

int Monster::GetRough() {
	return rough_degree_;
}

int Monster::PhysicalDamage() {
	return (rand() % GetSP() + GetRough());
}

int Monster::Attack(LifeEntity *l) {
	int damage = PhysicalDamage() - l->Defense();
	if (damage > l->GetHP())
		damage = l->GetHP();

	l->GetHurt(damage);

	if (damage > 0) {
		cout << this->GetName() << " 突襲而來，造成 " << l->GetName() << " " << damage << " 血損失" << endl;
	}
	else {
		cout << this->GetName() << " 突襲而來，但是 " << l->GetName() << " 異常幸運，因此躲避了攻擊" << endl;
	}
	return (damage);
}

int Monster::Defense() {
	return 0;
}

int Monster::IsA() {
	return emonster;
}

string Monster::GetBasicData() {
	string output = this->GetName() + string("(") + this->eng_name_ + string(") <hp_, sp_, rough> = <") + to_string((long double)this->GetHP()) + string(", ") + to_string((long double)this->GetSP()) + string(", ") + to_string((long double)this->GetRough()) + string(">");
	return output;
}

int Monster::GetMonsterId()
{
	return id_;
}