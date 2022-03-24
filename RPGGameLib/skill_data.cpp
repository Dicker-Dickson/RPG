#include "stdafx.h"
#include "skill_data.h"

SkillData::SkillData()
{
	Load();
}

SkillData::~SkillData()
{
}

void SkillData::Load()
{
	ifstream fin("skill.txt");
	if (!fin) {
		cout << "讀檔失敗: monsterdata.txt" << endl;
		exit(0);
	}

	string tmp_career, tmp_name, tmp_mp, tmp_method;
	int level_1, level_2, level_3, level_4, level_5, level_6, level_7, level_8, level_9, level_10;

	while (fin >> tmp_career >> tmp_name >> tmp_mp >> tmp_method >> level_1 >> level_2 >> level_3 >> level_4
		>> level_5 >> level_6 >> level_7 >> level_8 >> level_9 >> level_10) {
		SkillAttribute s;
		s.career = tmp_career;
		s.name = tmp_name;
		s.mp = tmp_mp;
		s.method = tmp_method;
		s.level = 0;
		s.value.push_back(level_1);
		s.value.push_back(level_2);
		s.value.push_back(level_3);
		s.value.push_back(level_4);
		s.value.push_back(level_5);
		s.value.push_back(level_6);
		s.value.push_back(level_7);
		s.value.push_back(level_8);
		s.value.push_back(level_9);
		s.value.push_back(level_10);

		skill_.push_back(s);
	}

	fin.close();
}

vector<SkillAttribute> SkillData::GenerateSkill()
{
	return skill_;
}

void SkillData::ShowSkillList()
{
	cout << "技能列表" << endl;
	for (int i = 0; i < skill_.size(); ++i)
	{
		cout << i + 1 << " 職業:" << skill_[i].career << " 技能名稱:" << skill_[i].name << " 效用:" << skill_[i].method << " 消耗魔力:" << skill_[i].mp << endl;
	}
}

void SkillData::ShowWarriorSkill()
{
	cout << "勇士技能列表" << endl;
	for (int i = 0; i < skill_.size(); ++i)
	{
		if (skill_[i].career == "劍士")
			cout << i + 1 << " 職業:" << skill_[i].career << " 技能名稱:" << skill_[i].name << " 效用:" << skill_[i].method << " 消耗魔力:" << skill_[i].mp << endl;
	}
}

void SkillData::ShowMagicianSkill()
{
	cout << "法師技能列表" << endl;
	for (int i = 0; i < skill_.size(); ++i)
	{
		if (skill_[i].career == "法師")
			cout << i + 1 << " 職業:" << skill_[i].career << " 技能名稱:" << skill_[i].name << " 效用:" << skill_[i].method << " 消耗魔力:" << skill_[i].mp << endl;
	}
}

void SkillData::ShowThiefSkill()
{
	cout << "盜賊技能列表" << endl;
	for (int i = 0; i < skill_.size(); ++i)
	{
		if (skill_[i].career == "盜賊")
			cout << i + 1 << " 職業:" << skill_[i].career << " 技能名稱:" << skill_[i].name << " 效用:" << skill_[i].method << " 消耗魔力:" << skill_[i].mp << endl;
	}
}

void SkillData::ShowArcherSkill()
{
	cout << "弓箭手技能列表" << endl;
	for (int i = 0; i < skill_.size(); ++i)
	{
		if (skill_[i].career == "弓箭手")
			cout << i + 1 << " 職業:" << skill_[i].career << " 技能名稱:" << skill_[i].name << " 效用:" << skill_[i].method << " 消耗魔力:" << skill_[i].mp << endl;
	}
}