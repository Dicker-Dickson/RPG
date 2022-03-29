#include "stdafx.h"
#include "magician.h"
#include "skill.h"

Magician::Magician()
{
}

Magician::~Magician()
{
}

bool Magician::IsLevelUp()
{
	auto level = GetLevel();
	auto exp = GetExp();

	for (int i = 10; i < 100; ++i)
	{
		if (level == i  && exp > 5 * (i + 2))
		{
			AddMaxHP(10);
			AddMaxMP(20);
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

int Magician::PhysicalDamage()
{
	int damage = 1.2 * attribute_.lucky + 1.5 * attribute_.intelligence + 0.1*attribute_.max_mp + GetSP();
	return rand() % damage + attack_increase_value;
}

void Magician::ShowCareer()
{
	cout << "戮穨猭畍" << endl;
}

void Magician::LearnSkill(int id)
{
	auto skill_attribute = CGlobalInfo::skill_data->GenerateSkill();
	if (id < 0 || id >skill_attribute.size() || skill_attribute[id - 1].career != "猭畍")
	{
		cout << "猭畍礚猭策眔м" << endl;
		system("Pause");
		return;
	}

	SetSkillPoints(GetSkillPoints() - 1);

	Skill* s = new Skill(skill_attribute[id - 1]);
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

void Magician::LearnSkill(SkillAttribute skill)
{
	Skill* s = new Skill(skill);
	skill_.push_back(s);
}

void Magician::ShowSkill()
{
	if (skill_.size() == 0)
	{
		cout << "﹟ゼ策眔м" << endl;
		return;
	}
	cout << "猭畍策眔мΤ:" << endl;
	for (int i = 0; i < skill_.size(); ++i)
	{
		cout << i + 1 << " м嘿:" << skill_[i]->GetSkillName() << " ヘ玡单:"
			<< skill_[i]->GetLevel() << " 臸:" << skill_[i]->GetMP() << " ノ:"
			<< skill_[i]->GetMethod() << skill_[i]->GetValue()[skill_[i]->GetLevel() - 1] << endl;
	}
}

int Magician::IsA()
{
	return MAGICIAN;
}

int Magician::GetSkillNumber()
{
	return skill_.size();
}

void Magician::UseSkillById(LifeEntity * l, int id)
{
	if (skill_[id]->GetSkillName() == "臸")
	{
		int damage = 1.2 * attribute_.lucky + 1.5 * attribute_.intelligence + 0.1*attribute_.max_mp + GetSP();
		damage = (rand() % damage)*0.01*skill_[id]->GetSkillValue() + attack_increase_value;

		damage = damage - l->Defense();
		if (damage > l->GetHP())
			damage = l->GetHP();

		l->GetHurt(damage);

		if (damage > 0) {
			cout << this->GetName() << " ㄏм[臸]硑Θ " << l->GetName() << " " << damage << " ﹀穕ア" << endl;
		}
		else {
			cout << this->GetName() << " ㄏм[臸]琌 " << l->GetName() << " 眏咀⊿Τ硑Θヴ穕ア" << endl;
		}
	}
	else if (skill_[id]->GetSkillName() == "臸ぇ")
	{
		defense_skill_count = 3;
		AddDefense(skill_[id]->GetSkillValue());
		cout << this->GetName() << " ㄏм[臸ぇ] " << "ň縨矗ど" << skill_[id]->GetSkillValue() << "3" << endl;
	}
}

int Magician::SkillUseMP(int id)
{
	return skill_[id]->GetMP();
}

vector<Skill*> Magician::GetSkill()
{
	return skill_;
}