#include "beginner.h"

Beginner::Beginner()
{
}

Beginner::~Beginner()
{
}

bool Beginner::IsLevelUp()
{
	auto level = GetLevel();
	auto exp = GetExp();

	for (int i = 1; i < 100; ++i)
	{
		if (level == i  && exp > 5 * (i + 2))
		{
			AddMaxHP(10);
			AddMaxMP(5);
			AddMaxSP(2);
			attribute_.defense++;
			AddHP(GetMaxHP());
			AddMP(GetMaxMP());
			return true;
		}
	}

	return false;
}

int Beginner::PhysicalDamage()
{
	int damage = attribute_.strength + GetSP();
	return rand() % damage + attack_increase_value;
}

void Beginner::ShowCareer()
{
	cout << "職業為初心者" << endl;
}

void Beginner::LearnSkill(int id)
{
	return;
}

int Beginner::IsA()
{
	return BEGINNER;
}

int Beginner::GetSkillNumber()
{
	return 0;
}

void Beginner::UseSkillById(LifeEntity * l, int id)
{
	return;
}

int Beginner::SkillUseMP(int id)
{
	return 0;
}

void Beginner::LearnSkill(SkillAttribute skill)
{
	return;
}