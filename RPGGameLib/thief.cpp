#include "stdafx.h"
#include "thief.h"
#include "skill.h"

Thief::Thief()
{
}

Thief::~Thief()
{
}

bool Thief::IsLevelUp()
{
	auto level = GetLevel();
	auto exp = GetExp();

	for (int i = 10; i < 100; ++i)
	{
		if (level == i  && exp > 5 * (i + 2))
		{
			AddMaxHP(15);
			AddMaxMP(10);
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

int Thief::PhysicalDamage()
{
	int damage = 1.4 * attribute_.lucky + 1.2 * attribute_.dexterity + 0.1*attribute_.max_hp + GetSP();
	return rand() % damage + attack_increase_value;
}

void Thief::ShowCareer()
{
	cout << "¾�~���s��" << endl;
}

void Thief::LearnSkill(int id)
{
	auto skill_attribute = CGlobalInfo::skill_data->GenerateSkill();
	if (id < 0 || id >skill_attribute.size() || skill_attribute[id - 1].career != "�s��")
	{
		cout << "�s��L�k�߱o���ޯ�" << endl;
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

void Thief::LearnSkill(SkillAttribute skill)
{
	Skill* s = new Skill(skill);
	skill_.push_back(s);
}

void Thief::ShowSkill()
{
	if (skill_.size() == 0)
	{
		cout << "�|���߱o�ޯ�" << endl;
		return;
	}
	cout << "�s��߱o�ޯ঳:" << endl;
	for (int i = 0; i < skill_.size(); ++i)
	{
		cout << i + 1 << " �ޯ�W��:" << skill_[i]->GetSkillName() << " �ثe����:"
			<< skill_[i]->GetLevel() << " �����]�O:" << skill_[i]->GetMP() << " �ĥ�:"
			<< skill_[i]->GetMethod() << skill_[i]->GetValue()[skill_[i]->GetLevel() - 1] << endl;
	}
}

int Thief::IsA()
{
	return THIEF;
}

int Thief::GetSkillNumber()
{
	return skill_.size();
}

void Thief::UseSkillById(LifeEntity *l, int id)
{
	if (skill_[id]->GetSkillName() == "������")
	{
		int damage = 0;
		damage = damage = 1.4 * attribute_.lucky + 1.2 * attribute_.dexterity + 0.1*attribute_.max_hp + GetSP();
		damage = (rand() % damage)*0.01*skill_[id]->GetSkillValue() + attack_increase_value;

		damage = damage - l->Defense();
		if (damage > l->GetHP())
			damage = l->GetHP();

		l->GetHurt(damage);

		if (damage > 0) {
			cout << this->GetName() << " �ϥX�ޯ�[������]�A�y�� " << l->GetName() << " " << damage << " ��l��" << endl;
		}
		else {
			cout << this->GetName() << " �ϥX�ޯ�[������]�A���O " << l->GetName() << " �j�O�@�סA�]���S���y������l��" << endl;
		}
	}
	else if (skill_[id]->GetSkillName() == "�v���N")
	{
		defense_skill_count = 3;
		AddDefense(skill_[id]->GetSkillValue());
		cout << this->GetName() << " �ϥX�ޯ�[�v���N] " << "���m����" << skill_[id]->GetSkillValue() << "�A�@3�^�X" << endl;
	}
}

int Thief::SkillUseMP(int id)
{
	return skill_[id]->GetMP();
}

vector<Skill*> Thief::GetSkill()
{
	return skill_;
}