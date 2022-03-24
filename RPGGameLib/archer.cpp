#include "stdafx.h"
#include "archer.h"
#include "skill.h"

Archer::Archer()
{
}

Archer::~Archer()
{
}

bool Archer::IsLevelUp()
{
	auto level = GetLevel();
	auto exp = GetExp();

	for (int i = 10; i < 100; ++i)
	{
		if (level == i  && exp > 5 * (i + 2))
		{
			AddMaxHP(15);
			AddMaxMP(15);
			AddMaxSP(3);
			attribute_.defense++;
			AddHP(GetMaxHP());
			AddMP(GetMaxMP());
			attribute_.skill_points++;
			return true;
		}
	}
	return false;
}

int Archer::PhysicalDamage()
{
	int damage = 1.2 * attribute_.strength + 1.6 * attribute_.dexterity + 0.1*attribute_.max_hp + GetSP();
	return rand() % damage + attack_increase_value;
}

void Archer::ShowCareer()
{
	cout << "職業為弓箭手" << endl;
}

void Archer::LearnSkill(int id)
{
	auto skill_attribute = CGlobalInfo::skill_data->GenerateSkill();
	if (id < 0 || id >skill_attribute.size() || skill_attribute[id - 1].career != "弓箭手")
	{
		cout << "弓箭手無法習得此技能" << endl;
		system("Pause");
		return;
	}
	Skill* s = new Skill(skill_attribute[id - 1]);

	SetSkillPoints(GetSkillPoints() - 1);

	for (int i = 0; i < skill_.size(); ++i)
	{
		if (skill_[i]->GetSkillName() == s->GetSkillName())
		{
			skill_[i]->AddLevel(1);
			return;
		}
	}
	skill_.push_back(s);
}

void Archer::LearnSkill(SkillAttribute skill)
{
	Skill* s = new Skill(skill);
	skill_.push_back(s);
}

void Archer::ShowSkill()
{
	if (skill_.size() == 0)
	{
		cout << "尚未習得技能" << endl;
		return;
	}
	cout << "弓箭手習得技能有:" << endl;
	for (int i = 0; i < skill_.size(); ++i)
	{
		cout << i + 1 << " 技能名稱:" << skill_[i]->GetSkillName() << " 目前等級:"
			<< skill_[i]->GetLevel() << " 消耗魔力:" << skill_[i]->GetMP() << " 效用:"
			<< skill_[i]->GetMethod() << skill_[i]->GetValue()[skill_[i]->GetLevel() - 1] << endl;
	}
}

int Archer::GetSkillNumber()
{
	return skill_.size();
}

void Archer::UseSkillById(LifeEntity * l, int id)
{
	if (skill_[id]->GetSkillName() == "霸王箭")
	{
		int damage = 1.2 * attribute_.strength + 1.6 * attribute_.dexterity + 0.1*attribute_.max_hp + GetSP();
		damage = (rand() % damage)*0.01*skill_[id]->GetSkillValue() + attack_increase_value;

		damage = damage - l->Defense();
		if (damage > l->GetHP())
			damage = l->GetHP();

		l->GetHurt(damage);

		if (damage > 0) {
			cout << this->GetName() << " 使出技能[霸王箭]，造成 " << l->GetName() << " " << damage << " 血損失" << endl;
		}
		else {
			cout << this->GetName() << " 使出技能[霸王箭]，但是 " << l->GetName() << " 強力一擋，因此沒有造成任何損失" << endl;
		}
	}
	else if (skill_[id]->GetSkillName() == "集中術")
	{
		defense_skill_count = 3;
		AddDefense(skill_[id]->GetSkillValue());
		cout << this->GetName() << " 使出技能[集中術] " << "防禦提升" << skill_[id]->GetSkillValue() << "，共3回合" << endl;
	}
}

int Archer::SkillUseMP(int id)
{
	return skill_[id]->GetMP();
}

vector<Skill*> Archer::GetSkill()
{
	return skill_;
}

int Archer::IsA()
{
	return archer;
}