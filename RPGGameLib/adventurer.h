#ifndef ADVENTURER_H
#define ADVENTURER_H

#include "LifeEntity.h"
#include "adventurer_data.h"
#include "string"
#include "bag.h"
#include "def.h"

#define FIGHTER_MAXHP 100
#define FIGHTER_MAXSP 100
#define FIGHTER_MAXdefense_ 20

class Food;
class Bag;
class Item;
class Skill;

class Adventurer : public LifeEntity
{
public:
	Adventurer();
	~Adventurer();
	int GetLucky();
	virtual int PhysicalDamage() = 0;
	virtual int Attack(LifeEntity *l) override;
	virtual int Defense() override;
	void CaptureItem(Item *);
	vector<Item*> GetBagAllFood();
	vector<Item*> GetBagAllWeapon();
	vector<Item*> GetBagAllArmor();

	void PutItem(Item *);
	Item* GetItem(int);
	vector<Item*> GetEquipment();
	void BuyItem(Item *);
	bool SellItem(Item *);
	void CaptureMoney(int);
	int ShowAllBagItems();
	void ShowMoney();
	bool UseBagItems(int no);
	int GoToNextCity(int next_dir);
	int MoveCity(int city);
	int GetCurrentCity();
	virtual int IsA() override;
	virtual bool IsLevelUp() = 0;
	void AddDefense(int value);
	void DefenseReset();
	void PrintDefenseCount();
	void DefenseCount();
	void AttackCount();
	void LevelUpWeapon();
	void LevelUpArmor();
	void PrintAttackCount();

	void ReadData();
	AdventurerAttribute GetAttribute();
	void SetAbilityPoints(int points);
	int GetAbilityPoints();
	void SetSkillPoints(int p);
	void AddSkillPoints(int p);
	int GetSkillPoints();
	bool IsCareerSpecialEquipment(BagEntry*);
	void SpendAbilityPoints();
	void PrintAdventurerAttribute();
	void PrintEquipment();
	void SaveMoney();
	void AddMoney(int money);
	void MinusMoney(int money);
	int GetMoney();

	virtual void ShowCareer() = 0;
	void SetCareer(string);

	virtual void LearnSkill(int) = 0;
	virtual void LearnSkill(SkillAttribute) = 0;
	virtual void ShowSkill();
	bool IsUseSkill(LifeEntity *);
	virtual int GetSkillNumber() = 0;
	virtual void UseSkillById(LifeEntity *, int id) = 0;
	virtual int SkillUseMP(int id);
	virtual vector<Skill*> GetSkill();

protected:
	AdventurerAttribute attribute_;
	int defense_skill_count;
	int attack_skill_count;
	int attack_increase_value;
private:
	int current_city_;
	int defense_;
	vector<Item*> equipment_;
	Bag *bag_;
};

#endif