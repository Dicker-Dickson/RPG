#include "battle_scene.h"
#include "MonsterData.h"

BattleScence::BattleScence()
{
}

BattleScence::~BattleScence()
{
}

void BattleScence::askforbaglist(Adventurer *f) {
	system("CLS");

	cout << "�ثe����:" << f->GetLevel() << endl;
	cout << "�g���:" << f->GetExp() << "/" << (f->GetLevel() + 2) * 5 << endl;;
	cout << "�ثeHP: " << f->GetHP() << "/" << f->GetMaxHP() << endl;
	cout << "�ثeMP:" << f->GetMP() << "/" << f->GetMaxMP() << endl;
	f->PrintEquipment();
	f->PrintDefenseCount();
	f->PrintAttackCount();
	f->ShowMoney();
	int num = f->ShowAllBagItems();
	if (num == 0)
		return;
	cout << f->GetName() << " �ݭn�ϥέI�]���~��?\n0 --> No, Others --> Yes, �ϥΤ����~�s��: ";
	string selection;
	cin >> selection;
	if (selection.size() <= 2 && isdigit(selection[0]))
	{
		if (!f->UseBagItems(stoi(selection)))
			cout << "�L���ﶵ�s�b" << endl;
	}
}

Monster* BattleScence::MonsterSelection(Adventurer *f) {
	int current_city = CGlobalInfo::user->get_current_city();
	int monster_id = CGlobalInfo::map_data->GetRandomMonsterFromCity(current_city);
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
	//��ܫi�̩m�W�M����
	cout << endl << f->GetName() << " ���� = " << f->GetLevel() << endl;

	//��ܦ���e��
	BloodBarShow(f->GetMaxHP(), f->GetHP());

	//��ܩǪ��W��
	cout << m->GetName() << " ���� = " << m->GetLevel() << endl;

	//��ܦ���e��
	BloodBarShow(m->GetMaxHP(), m->GetHP());

	cout << endl;
}

void BattleScence::fightshow(Monster *m, Adventurer *f) {
	FightStatus(m, f);
	cout << "�z�ѤU " << f->GetHP() << "�w��" << endl;
	Sleep(1000);
}

void BattleScence::startfight(Monster *m, Adventurer *f) {
	int f_damage = 0, s_damage = 0;
	LifeEntity *first, *second;
	int whofirst;
	while (!m->IsDead() && !f->IsDead()) {
		whofirst = rand() % 2;
		if (whofirst == 0) {
			cout << "�Ǫ��m�o�����A���X��ˤH" << endl;
			first = (LifeEntity *)m;
			second = (LifeEntity *)f;
		}
		else {
			cout << "�A�m�o�����A���X��ˤH" << endl;
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
		cout << " �Ǫ��w���A��o�g��� = " << e << endl;
		f->AddExp(e);
		cout << "�ثe�g��� = " << f->GetExp() << endl;

		if (f->IsLevelUp())
		{
			cout << "�i�̵��Ŵ���" << endl;
			f->SetExp(0);
			f->SetLevel(f->GetLevel() + 1);
			f->SetAbilityPoints(f->GetAbilityPoints() + 5);

			cout << "�n���t�I�ƶ�?��J0���n�A��J1�n" << endl;
			string selection;
			cin >> selection;
			if (selection == "1")
			{
				f->SpendAbilityPoints();
			}
		}

		cout << "�q�Ǫ����W���U�_��" << endl;
		ItemData *id = CGlobalInfo::itm_data;
		f->CaptureItem(id->getRand());
		cout << "�q�Ǫ����W���U����" << endl;
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