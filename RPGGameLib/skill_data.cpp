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
		cout << "Ū�ɥ���: monsterdata.txt" << endl;
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
	cout << "�ޯ�C��" << endl;
	for (int i = 0; i < skill_.size(); ++i)
	{
		cout << i + 1 << " ¾�~:" << skill_[i].career << " �ޯ�W��:" << skill_[i].name << " �ĥ�:" << skill_[i].method << " �����]�O:" << skill_[i].mp << endl;
	}
}

void SkillData::ShowWarriorSkill()
{
	cout << "�i�h�ޯ�C��" << endl;
	for (int i = 0; i < skill_.size(); ++i)
	{
		if (skill_[i].career == "�C�h")
			cout << i + 1 << " ¾�~:" << skill_[i].career << " �ޯ�W��:" << skill_[i].name << " �ĥ�:" << skill_[i].method << " �����]�O:" << skill_[i].mp << endl;
	}
}

void SkillData::ShowMagicianSkill()
{
	cout << "�k�v�ޯ�C��" << endl;
	for (int i = 0; i < skill_.size(); ++i)
	{
		if (skill_[i].career == "�k�v")
			cout << i + 1 << " ¾�~:" << skill_[i].career << " �ޯ�W��:" << skill_[i].name << " �ĥ�:" << skill_[i].method << " �����]�O:" << skill_[i].mp << endl;
	}
}

void SkillData::ShowThiefSkill()
{
	cout << "�s��ޯ�C��" << endl;
	for (int i = 0; i < skill_.size(); ++i)
	{
		if (skill_[i].career == "�s��")
			cout << i + 1 << " ¾�~:" << skill_[i].career << " �ޯ�W��:" << skill_[i].name << " �ĥ�:" << skill_[i].method << " �����]�O:" << skill_[i].mp << endl;
	}
}

void SkillData::ShowArcherSkill()
{
	cout << "�}�b��ޯ�C��" << endl;
	for (int i = 0; i < skill_.size(); ++i)
	{
		if (skill_[i].career == "�}�b��")
			cout << i + 1 << " ¾�~:" << skill_[i].career << " �ޯ�W��:" << skill_[i].name << " �ĥ�:" << skill_[i].method << " �����]�O:" << skill_[i].mp << endl;
	}
}