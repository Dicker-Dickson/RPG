#include "warrior.h"
#include "skill.h"

Warrior::Warrior()
{
}

Warrior::~Warrior()
{
}

bool Warrior::IsLevelUp()
{
	auto level = GetLevel();
	auto exp = GetExp();

	for (int i = 10; i < 100; ++i)
	{
		if (level == i  && exp > 5 * (i + 2))
		{
			AddMaxHP(20);
			AddMaxMP(10);
			AddMaxSP(3);
			attribute_.defense += 2;
			AddHP(GetMaxHP());
			AddMP(GetMaxMP());
			attribute_.skill_points++;
			return true;
		}
	}
	return false;
}

int Warrior::PhysicalDamage()
{
	int damage = 1.5 * attribute_.strength + 1.2 * attribute_.defense + 0.1*attribute_.max_hp + GetSP();
	return rand() % damage + attack_increase_value;
}

void Warrior::ShowCareer()
{
	cout << "¾�~���C�h" << endl;
}

void Warrior::LearnSkill(int id)
{
	auto skill_attribute = CGlobalInfo::skill_data->GenerateSkill();
	if (id < 0 || id >skill_attribute.size() || skill_attribute[id - 1].career != "�C�h")
	{
		cout << "�C�h�L�k�߱o���ޯ�" << endl;
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

void Warrior::LearnSkill(SkillAttribute skill)
{
	Skill* s = new Skill(skill);
	skill_.push_back(s);
}

void Warrior::ShowSkill()
{
	if (skill_.size() == 0)
	{
		cout << "�|���߱o�ޯ�" << endl;
		return;
	}
	cout << "�C�h�߱o�ޯ঳:" << endl;
	for (int i = 0; i < skill_.size(); ++i)
	{
		cout << i + 1 << " �ޯ�W��:" << skill_[i]->GetSkillName() << " �ثe����:"
			<< skill_[i]->GetLevel() << " �����]�O:" << skill_[i]->GetMP() << " �ĥ�:"
			<< skill_[i]->GetMethod() << skill_[i]->GetValue()[skill_[i]->GetLevel() - 1] << endl;
	}
}

int Warrior::IsA()
{
	return warrior;
}

int Warrior::GetSkillNumber()
{
	return skill_.size();
}

void Warrior::UseSkillById(LifeEntity *l, int id)
{
	if (skill_[id]->GetSkillName() == "���Ѥ@��")
	{
		int damage = 0;
		damage = 1.5 * attribute_.strength + 1.2 * attribute_.defense + 0.1*attribute_.max_hp + GetSP();
		damage = (rand() % damage)*0.01*skill_[id]->GetSkillValue() + attack_increase_value;

		damage = damage - l->Defense();
		if (damage > l->GetHP())
			damage = l->GetHP();

		l->GetHurt(damage);

		if (damage > 0) {
			cout << this->GetName() << " �ϥX�ޯ�[���Ѥ@��]�A�y�� " << l->GetName() << " " << damage << " ��l��" << endl;
		}
		else {
			cout << this->GetName() << " �ϥX�ޯ�[���Ѥ@��]�A���O " << l->GetName() << " �j�O�@�סA�]���S���y������l��" << endl;
		}
	}
	else if (skill_[id]->GetSkillName() == "�ͩR��_")
	{
		AddHP(skill_[id]->GetSkillValue());
		cout << this->GetName() << " �ϥX�ޯ�[�ͩR��_] " << "��_HP:" << skill_[id]->GetSkillValue() << endl;
	}
}

int Warrior::SkillUseMP(int id)
{
	return skill_[id]->GetMP();
}

vector<Skill*> Warrior::GetSkill()
{
	return skill_;
}