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
	cout << "¾�~���k�v" << endl;
}

void Magician::LearnSkill(int id)
{
	auto skill_attribute = CGlobalInfo::skill_data->GenerateSkill();
	if (id < 0 || id >skill_attribute.size() || skill_attribute[id - 1].career != "�k�v")
	{
		cout << "�k�v�L�k�߱o���ޯ�" << endl;
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
		cout << "�|���߱o�ޯ�" << endl;
		return;
	}
	cout << "�k�v�߱o�ޯ঳:" << endl;
	for (int i = 0; i < skill_.size(); ++i)
	{
		cout << i + 1 << " �ޯ�W��:" << skill_[i]->GetSkillName() << " �ثe����:"
			<< skill_[i]->GetLevel() << " �����]�O:" << skill_[i]->GetMP() << " �ĥ�:"
			<< skill_[i]->GetMethod() << skill_[i]->GetValue()[skill_[i]->GetLevel() - 1] << endl;
	}
}

int Magician::IsA()
{
	return magician;
}

int Magician::GetSkillNumber()
{
	return skill_.size();
}

void Magician::UseSkillById(LifeEntity * l, int id)
{
	if (skill_[id]->GetSkillName() == "�]�O��")
	{
		int damage = 1.2 * attribute_.lucky + 1.5 * attribute_.intelligence + 0.1*attribute_.max_mp + GetSP();
		damage = (rand() % damage)*0.01*skill_[id]->GetSkillValue() + attack_increase_value;

		damage = damage - l->Defense();
		if (damage > l->GetHP())
			damage = l->GetHP();

		l->GetHurt(damage);

		if (damage > 0) {
			cout << this->GetName() << " �ϥX�ޯ�[�]�O��]�A�y�� " << l->GetName() << " " << damage << " ��l��" << endl;
		}
		else {
			cout << this->GetName() << " �ϥX�ޯ�[�]�O��]�A���O " << l->GetName() << " �j�O�@�סA�]���S���y������l��" << endl;
		}
	}
	else if (skill_[id]->GetSkillName() == "�]�O����")
	{
		defense_skill_count = 3;
		AddDefense(skill_[id]->GetSkillValue());
		cout << this->GetName() << " �ϥX�ޯ�[�]�O����] " << "���m����" << skill_[id]->GetSkillValue() << "�A�@3�^�X" << endl;
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