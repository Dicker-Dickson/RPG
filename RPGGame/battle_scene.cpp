#include "battle_scene.h"
#include "monster_data.h"

BattleScence::BattleScence()
{
}

BattleScence::~BattleScence()
{
}

void BattleScence::askforbaglist(Adventurer *f) {
	system("CLS");

	cout << "目前等級:" << f->GetLevel() << endl;
	cout << "經驗值:" << f->GetExp() << "/" << (f->GetLevel() + 2) * 5 << endl;;
	cout << "目前HP: " << f->GetHP() << "/" << f->GetMaxHP() << endl;
	cout << "目前MP:" << f->GetMP() << "/" << f->GetMaxMP() << endl;
	f->PrintEquipment();
	f->PrintDefenseCount();
	f->PrintAttackCount();
	f->ShowMoney();
	int num = f->ShowAllBagItems();
	if (num == 0)
		return;
	cout << f->GetName() << " 需要使用背包物品嗎?\n0 --> No, Others --> Yes, 使用之物品編號: ";
	string selection;
	cin >> selection;
	if (selection.size() <= 2 && isdigit(selection[0]))
	{
		if (!f->UseBagItems(stoi(selection)))
			cout << "無此選項存在" << endl;
	}
}

Monster* BattleScence::MonsterSelection(Adventurer *f) {
	int current_city = CGlobalInfo::user->get_current_city();
	int monster_id = CGlobalInfo::map_data->GetBattleMonsters(current_city);
	if (monster_id == -1)
	{
		Monster* m = nullptr;
		return m;
	}
	askforbaglist(f);
	f->DefenseCount();
	f->AttackCount();
	Monster *m = new Monster(CGlobalInfo::monster_data->GetMonstertypeById(monster_id));
	system("CLS");
	return m;
}

void BattleScence::BloodBarShow(int maxhp, int hp) {
	cout << "hp     |";
	float hpslotlen = (float)maxhp / MAXBARLEN;
	int numhp = (int)ceil(hp / hpslotlen);
	for (int i = 0; i < numhp; i++) {
		cout << "#";
	}
	numhp = (int)floor((maxhp - hp) / hpslotlen);
	for (int i = 0; i < numhp; i++) {
		cout << " ";
	}
	cout << "|" << endl;
}

void BattleScence::FightStatus(Monster *m, Adventurer *f) {
	//顯示勇者姓名和等級
	cout << endl << f->GetName() << " 等級 = " << f->GetLevel() << endl;

	//顯示扣血畫面
	BloodBarShow(f->GetMaxHP(), f->GetHP());

	//顯示怪物名稱
	cout << m->GetName() << " 等級 = " << m->GetLevel() << endl;

	//顯示扣血畫面
	BloodBarShow(m->GetMaxHP(), m->GetHP());

	cout << endl;
}

void BattleScence::fightshow(Monster *m, Adventurer *f) {
	FightStatus(m, f);
	cout << "您剩下 " << f->GetHP() << "滴血" << endl;
	Sleep(1000);
}

void BattleScence::startfight(Monster *m, Adventurer *f) {
	int f_damage = 0, s_damage = 0;
	LifeEntity *first, *second;
	int whofirst;
	while (!m->IsDead() && !f->IsDead()) {
		whofirst = rand() % 2;
		if (whofirst == 0) {
			cout << "怪物搶得先機，先出手傷人" << endl;
			first = (LifeEntity *)m;
			second = (LifeEntity *)f;
		}
		else {
			cout << "你搶得先機，先出手傷人" << endl;
			first = (LifeEntity *)f;
			second = (LifeEntity *)m;
		}

		s_damage = first->Attack(second);
		if (second->IsDead()) {
			whofirst == 0 ? fightshow((Monster *)first, (Adventurer *)second) : fightshow((Monster *)second, (Adventurer *)first);
			break;
		}

		f_damage = second->Attack(first);
		whofirst == 0 ? fightshow((Monster *)first, (Adventurer *)second) : fightshow((Monster *)second, (Adventurer *)first);
	}
	if (m->IsDead() && !f->IsDead()) {
		auto e = m->GetExp();
		cout << " 怪物已死，獲得經驗值 = " << e << endl;
		f->AddExp(e);
		cout << "目前經驗值 = " << f->GetExp() << endl;

		if (f->IsLevelUp())
		{
			cout << "勇者等級提升" << endl;
			f->SetExp(0);
			f->SetLevel(f->GetLevel() + 1);
			f->SetAbilityPoints(f->GetAbilityPoints() + 5);

			cout << "要分配點數嗎?輸入0不要，輸入1要" << endl;
			string selection;
			cin >> selection;
			if (selection == "1")
			{
				f->SpendAbilityPoints();
			}
		}

		cout << "從怪物身上掉下寶物" << endl;
		ItemData *id = CGlobalInfo::itm_data;
		f->CaptureItem(id->GetRand());
		cout << "從怪物身上掉下金錢" << endl;
		int money = CGlobalInfo::itm_data->GenerateRandomMoney();
		cout << money << endl;
		f->CaptureMoney(money);

		CGlobalInfo::adventurer_data->Save(f->GetAttribute());
		auto food = f->GetBagAllFood();
		CGlobalInfo::adventurer_data->SaveBagFood(food);
		auto weapon = f->GetBagAllWeapon();
		CGlobalInfo::adventurer_data->SaveBagWeapon(weapon);
		auto equipment = f->GetEquipment();
		CGlobalInfo::adventurer_data->SaveEquipment(equipment);
	}
}