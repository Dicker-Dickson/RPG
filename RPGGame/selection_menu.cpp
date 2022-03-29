#include "selection_menu.h"

SelectionMenu::SelectionMenu()
{
	Initialize();
	InitialCareer();
}

SelectionMenu::~SelectionMenu()
{
}

void SelectionMenu::ShowSelectionMenu()
{
	while (1)
	{
		system("CLS");
		cout << "�п�ܥ\��ﶵ : " << endl;
		cout << "1. �H���ݩ�" << endl;
		cout << "2. �a�� " << endl;
		cout << "3. �ө� " << endl;
		cout << "4. �I�]/�ܮw " << endl;
		cout << "5. ��¾" << endl;
		cout << "6. �h�X " << endl;

		string temp = "";
		cin >> temp;

		if (isdigit(temp[0]) && temp.size() == 1)
		{
			auto i = std::stoi(temp);
			switch (i) {
			case 1:
				ShowAttribute();
				break;
			case 2:
				system("CLS");
				ShowMap();
				break;
			case 3:
				ShowStore();
				break;
			case 4:
				ShowBackPackAndWireHouse();
				break;
			case 5:
				ShowTransfer();
				break;
			case 6:
				cout << "�T�T" << endl;
				system("Pause");
				exit(0);
			default:
				break;
			}
		}
	}
}

void SelectionMenu::ShowMap()
{
	int current_place_id = CGlobalInfo::user->get_current_city();
	CGlobalInfo::map_data->ShowDescription(current_place_id);
	while (CGlobalInfo::parser->Query() >= 0)
	{
		int current_city = CGlobalInfo::user->get_current_city();
		CGlobalInfo::map_data->GenrateMonstersInPlace(current_city);

		cout << "�԰���JY,�h�X��JQ�A��s�a�Ͽ�J���N���e�A�Q�h��L�a���J���Oex: move �i�h����, move (south, east....)" << endl;
		string temp = "";
		cin >> temp;
		if (temp == "Y" || temp == "y")
		{
			system("CLS");
			GoBattle();
		}
		else if (temp == "Q" || temp == "q")
		{
			system("CLS");
			return;
		}
		system("CLS");
	}
}

void SelectionMenu::ShowAttribute()
{
	while (1)
	{
		system("CLS");
		fighter_->ShowCareer();
		fighter_->PrintAdventurerAttribute();
		fighter_->PrintEquipment();
		fighter_->ShowSkill();
		cout << endl;
		cout << "��^�п�JQ�A�t�ݩ��I�п�JA�A�ɯŧޯ�п�JS" << endl;
		string temp;
		cin >> temp;
		if (temp == "Q" || temp == "q")
		{
			return;
		}
		else if (temp == "S" || temp == "s")
		{
			ShowLearnSkill();
		}
		else if (temp == "A" || temp == "a")
		{
			ShowAddAbility();
		}
	}
}

void SelectionMenu::ShowAddAbility()
{
	while (1)
	{
		system("CLS");

		auto ability_point = fighter_->GetAbilityPoints();
		if (ability_point)
		{
			fighter_->SpendAbilityPoints();
			CGlobalInfo::adventurer_data->Save(fighter_->GetAttribute());
		}
		else
		{
			cout << "�S���ݩ��I" << endl;
			system("Pause");
			return;
		}
	}
}

void SelectionMenu::ShowLearnSkill()
{
	while (1)
	{
		system("CLS");
		auto career = fighter_->IsA();
		if (career == BEGINNER)
		{
			cout << "��ߪ̨S����k�߱o�ޯ�" << endl;
			system("Pause");
			return;
		}
		else if (career == WARRIOR || career == MAGICIAN || career == THIEF || career == ARCHER)
		{
			if (career == WARRIOR)
			{
				CGlobalInfo::skill_data->ShowWarriorSkill();
			}
			else if (career == MAGICIAN)
			{
				CGlobalInfo::skill_data->ShowMagicianSkill();
			}
			else if (career == THIEF)
			{
				CGlobalInfo::skill_data->ShowThiefSkill();
			}
			else if (career == ARCHER)
			{
				CGlobalInfo::skill_data->ShowArcherSkill();
			}
			fighter_->ShowSkill();
			auto skill_points = fighter_->GetSkillPoints();
			cout << "�ޯ��I�ѤU:" << skill_points << endl;

			cout << "��^�п�JQ�A�ɯũβ߱o�ޯ�п�JID" << endl;
			string t;
			cin >> t;

			if (t == "Q" || t == "q")
			{
				return;
			}

			if (skill_points > 0)
			{
				fighter_->LearnSkill(stoi(t));
				auto skill = fighter_->GetSkill();
				CGlobalInfo::adventurer_data->SaveSkill(skill);
			}
			else
			{
				cout << "�ޯ��I����" << endl;
				system("Pause");
			}
		}
	}
}

void SelectionMenu::ShowStore()
{
	while (1)
	{
		system("CLS");
		CGlobalInfo::store->ShowAllItem();
		cout << endl;
		fighter_->ShowMoney();
		fighter_->ShowAllBagItems();
		cout << endl;
		cout << "��^�п�JQ�A�ʶR�п�JB�A��X�п�JS�A�ɯŸ˳ƽп�JL" << endl;
		string temp;
		cin >> temp;
		if (temp == "Q" || temp == "q")
		{
			return;
		}
		if (temp == "B" || temp == "b")
		{
			ShowBuyMenu();
		}
		if (temp == "S" || temp == "s")
		{
			ShowSellMenu();
		}
		if (temp == "L" || temp == "l")
		{
			ShowLevelUpMenu();
		}
	}
}

void SelectionMenu::ShowBuyMenu()
{
	while (1)
	{
		system("CLS");
		cout << "��^�п�JQ,�R�ɵ��~�п�JF�A�R�Z���п�JW�A�R�޵P�п�JA" << endl;
		string temp;
		cin >> temp;
		if (temp == "Q" || temp == "q")
		{
			return;
		}
		else if (temp == "F" || temp == "f")
		{
			ShowBuyFoodMenu();
		}
		else if (temp == "W" || temp == "w")
		{
			ShowBuyWeaponMenu();
		}
		else if (temp == "A" || temp == "a")
		{
			ShowBuyArmorMenu();
		}
	}
}

void SelectionMenu::ShowBuyFoodMenu()
{
	while (1)
	{
		system("CLS");
		CGlobalInfo::itm_data->ShowFood();
		cout << endl;
		fighter_->ShowMoney();
		fighter_->ShowAllBagItems();

		cout << "��^�п�JQ�A�п�J�ɵ��~��ID" << endl;
		string t;
		cin >> t;
		if (t == "Q" || t == "q")
		{
			return;
		}
		if (t.size() > 2 || !isdigit(t[0]))
		{
			cout << "�п�J�ɵ��~��id" << endl;
			system("Pause");
			continue;
		}
		auto item = CGlobalInfo::itm_data->GetItemById(stoi(t) - 1, FOOD);
		if (!item)
		{
			cout << "�п�J�ɵ��~��id" << endl;
			system("Pause");
			continue;
		}
		int item_money = item->GetMoney();
		if (fighter_->GetMoney() < item_money)
		{
			cout << "������" << endl;
			system("Pause");
			break;
		}
		fighter_->MinusMoney(item_money);
		fighter_->BuyItem(item);

		auto attribute = fighter_->GetAttribute();
		CGlobalInfo::adventurer_data->Save(attribute);
		auto food = fighter_->GetBagAllFood();
		CGlobalInfo::adventurer_data->SaveBagFood(food);
	}
}

void SelectionMenu::ShowBuyWeaponMenu()
{
	while (1)
	{
		system("CLS");

		CGlobalInfo::itm_data->ShowWeapon();

		cout << endl;
		fighter_->ShowMoney();
		fighter_->ShowAllBagItems();

		cout << "��^�п�JQ�A�п�J�Z����ID" << endl;
		string t;
		cin >> t;
		if (t == "Q" || t == "q")
		{
			return;
		}

		if (t.size() > 2 || !isdigit(t[0]))
		{
			cout << "�п�J�Z����id" << endl;
			system("Pause");
			continue;
		}
		auto item = CGlobalInfo::itm_data->GetItemById(stoi(t) - 1, WEAPON);
		if (!item)
		{
			cout << "�п�J�Z����id" << endl;
			system("Pause");
			continue;
		}
		int item_money = item->GetMoney();
		if (fighter_->GetMoney() < item_money)
		{
			cout << "������" << endl;
			system("Pause");
			break;
		}
		fighter_->MinusMoney(item_money);
		fighter_->BuyItem(item);
		auto attribute = fighter_->GetAttribute();
		CGlobalInfo::adventurer_data->Save(attribute);
		auto weapon = fighter_->GetBagAllWeapon();
		CGlobalInfo::adventurer_data->SaveBagWeapon(weapon);
	}
}

void SelectionMenu::ShowBuyArmorMenu()
{
	while (1)
	{
		system("CLS");

		CGlobalInfo::itm_data->ShowArmor();

		cout << endl;
		fighter_->ShowMoney();
		fighter_->ShowAllBagItems();

		cout << "��^�п�JQ�A�п�J�޵P��ID" << endl;
		string t;
		cin >> t;
		if (t == "Q" || t == "q")
		{
			return;
		}

		if (t.size() > 2 || !isdigit(t[0]))
		{
			cout << "�п�J�޵P��id" << endl;
			system("Pause");
			continue;
		}

		auto item = CGlobalInfo::itm_data->GetItemById(stoi(t) - 1, ARMOR);
		if (!item)
		{
			cout << "�п�J�޵P��id" << endl;
			system("Pause");
			continue;
		}

		int item_money = item->GetMoney();
		if (fighter_->GetMoney() < item_money)
		{
			cout << "������" << endl;
			system("Pause");
			break;
		}
		fighter_->MinusMoney(item_money);
		fighter_->BuyItem(item);
		auto attribute = fighter_->GetAttribute();
		CGlobalInfo::adventurer_data->Save(attribute);
		auto armor = fighter_->GetBagAllArmor();
		CGlobalInfo::adventurer_data->SaveBagArmor(armor);
	}
}

void SelectionMenu::ShowSellMenu()
{
	while (1)
	{
		system("CLS");
		cout << "��^�п�JQ,��ɵ��~�п�JF�A��Z���п�JW�A��޵P�п�JA" << endl;
		string temp;
		cin >> temp;
		if (temp == "Q" || temp == "q")
		{
			return;
		}
		else if (temp == "F" || temp == "f")
		{
			ShowSellFoodMenu();
		}
		else if (temp == "W" || temp == "w")
		{
			ShowSellWeaponMenu();
		}
		else if (temp == "A" || temp == "a")
		{
			ShowSellArmorMenu();
		}
	}
}

void SelectionMenu::ShowSellFoodMenu()
{
	while (1)
	{
		system("CLS");
		CGlobalInfo::itm_data->ShowFood();
		cout << endl;
		fighter_->ShowMoney();
		fighter_->ShowAllBagItems();

		cout << "��^�п�JQ�A�п�J�ɵ��~��ID" << endl;
		string t;
		cin >> t;
		if (t == "Q" || t == "q")
		{
			return;
		}

		if (t.size() > 2 || !isdigit(t[0]))
		{
			cout << "�п�J�ɵ��~��id" << endl;
			system("Pause");
			continue;
		}
		auto item = CGlobalInfo::itm_data->GetItemById(stoi(t) - 1, FOOD);
		if (!item)
		{
			cout << "�п�J�ɵ��~��id" << endl;
			system("Pause");
			continue;
		}
		int item_money = item->GetMoney();

		if (fighter_->SellItem(item))
		{
			fighter_->PlusMoney(item_money);

			auto attribute = fighter_->GetAttribute();
			CGlobalInfo::adventurer_data->Save(attribute);
			auto food = fighter_->GetBagAllFood();
			CGlobalInfo::adventurer_data->SaveBagFood(food);
		}
	}
}

void SelectionMenu::ShowSellWeaponMenu()
{
	while (1)
	{
		system("CLS");
		CGlobalInfo::itm_data->ShowWeapon();
		cout << endl;
		fighter_->ShowMoney();
		fighter_->ShowAllBagItems();

		cout << "��^�п�JQ�A�п�J�Z����ID" << endl;
		string t;
		cin >> t;
		if (t == "Q" || t == "q")
		{
			return;
		}

		if (t.size() > 2 || !isdigit(t[0]))
		{
			cout << "�п�J�Z����id" << endl;
			system("Pause");
			continue;
		}
		auto item = CGlobalInfo::itm_data->GetItemById(stoi(t) - 1, WEAPON);
		if (!item)
		{
			cout << "�п�J�Z����id" << endl;
			system("Pause");
			continue;
		}
		int item_money = item->GetMoney();

		if (fighter_->SellItem(item))
		{
			fighter_->PlusMoney(item_money);

			auto attribute = fighter_->GetAttribute();
			CGlobalInfo::adventurer_data->Save(attribute);
			auto weapon = fighter_->GetBagAllWeapon();
			CGlobalInfo::adventurer_data->SaveBagWeapon(weapon);
		}
	}
}

void SelectionMenu::ShowSellArmorMenu()
{
	while (1)
	{
		system("CLS");
		CGlobalInfo::itm_data->ShowArmor();
		cout << endl;
		fighter_->ShowMoney();
		fighter_->ShowAllBagItems();

		cout << "��^�п�JQ�A�п�J�޵P��ID" << endl;
		string t;
		cin >> t;
		if (t == "Q" || t == "q")
		{
			return;
		}
		if (t.size() > 2 || !isdigit(t[0]))
		{
			cout << "�п�J�޵P��id" << endl;
			system("Pause");
			continue;
		}
		auto item = CGlobalInfo::itm_data->GetItemById(stoi(t) - 1, ARMOR);
		if (!item)
		{
			cout << "�п�J�޵P��id" << endl;
			system("Pause");
			continue;
		}
		int item_money = item->GetMoney();

		if (fighter_->SellItem(item))
		{
			fighter_->PlusMoney(item_money);

			auto attribute = fighter_->GetAttribute();
			CGlobalInfo::adventurer_data->Save(attribute);
			auto armor = fighter_->GetBagAllArmor();
			CGlobalInfo::adventurer_data->SaveBagArmor(armor);
		}
	}
}

void SelectionMenu::ShowLevelUpMenu()
{
	while (1)
	{
		system("CLS");
		cout << "��^�п�JQ,�ɯŪZ���п�JW�A�ɯŬ޵P�п�JA" << endl;
		string temp;
		cin >> temp;
		if (temp == "Q" || temp == "q")
		{
			return;
		}
		else if (temp == "W" || temp == "w")
		{
			ShowLevelUpWeaponMenu();
		}
		else if (temp == "A" || temp == "a")
		{
			ShowLevelUpArmorMenu();
		}
	}
}

void SelectionMenu::ShowLevelUpWeaponMenu()
{
	while (1)
	{
		system("CLS");
		fighter_->ShowMoney();

		auto w = fighter_->GetWeapon();
		if (w)
		{
			cout << "�ثe�Z����:" << w->GetName() << " ���Ŭ�:" << w->GetLevel() << endl;
			cout << "��^�п�JQ�A�ɯŤ@���ݪ�O300�����A�п�JY" << endl;
			string t;
			cin >> t;
			if (t == "Q" || t == "q")
			{
				return;
			}

			else if (t == "Y" || t == "y")
			{
				if (fighter_->GetMoney() < 300)
				{
					cout << "������" << endl;
					system("Pause");
					break;
				}
				fighter_->MinusMoney(300);
				fighter_->LevelUpWeapon();

				auto attribute = fighter_->GetAttribute();
				CGlobalInfo::adventurer_data->Save(attribute);
				auto armor = fighter_->GetBagAllWeapon();
				CGlobalInfo::adventurer_data->SaveBagWeapon(armor);

				auto equipment = fighter_->GetEquipment();
				CGlobalInfo::adventurer_data->SaveEquipment(equipment);
			}
		}
		else
		{
			cout << "�S���˳ƪZ��" << endl;
			system("Pause");
			return;
		}
	}
}

void SelectionMenu::ShowLevelUpArmorMenu()
{
	while (1)
	{
		system("CLS");
		fighter_->ShowMoney();

		auto a = fighter_->GetArmor();
		if (a)
		{
			cout << "�ثe�޵P��:" << a->GetName() << " ���Ŭ�:" << a->GetLevel() << endl;
			cout << "��^�п�JQ�A�ɯŤ@���ݪ�O300�����A�п�JY" << endl;
			string t;
			cin >> t;
			if (t == "Q" || t == "q")
			{
				return;
			}

			else if (t == "Y" || t == "y")
			{
				if (fighter_->GetMoney() < 300)
				{
					cout << "������" << endl;
					system("Pause");
					break;
				}
				fighter_->MinusMoney(300);
				fighter_->LevelUpArmor();

				auto attribute = fighter_->GetAttribute();
				CGlobalInfo::adventurer_data->Save(attribute);
				auto armor = fighter_->GetBagAllArmor();
				CGlobalInfo::adventurer_data->SaveBagArmor(armor);

				auto equipment = fighter_->GetEquipment();
				CGlobalInfo::adventurer_data->SaveEquipment(equipment);
			}
		}
		else
		{
			cout << "�S���˳Ƭ޵P" << endl;
			system("Pause");
			return;
		}
	}
}

void SelectionMenu::ShowBackPackAndWireHouse()
{
	while (1)
	{
		system("CLS");
		fighter_->ShowMoney();
		fighter_->ShowAllBagItems();
		fighter_->PrintEquipment();

		cout << "��^�п�JQ�A�ϥιD���JY�A�d�ݩ��w�п�JW" << endl;
		string temp;
		cin >> temp;
		if (temp == "Q" || temp == "q")
		{
			return;
		}
		else if (temp == "Y" || temp == "y")
		{
			system("CLS");
			fighter_->ShowMoney();
			int num = fighter_->ShowAllBagItems();
			fighter_->PrintEquipment();
			if (num == 0)
				return;
			cout << fighter_->GetName() << " �ݭn�ϥέI�]���~��?\n0 --> No, Others --> Yes, �ϥΤ����~�s��: ";
			int selection;
			cin >> selection;
			if (selection) {
				if (!fighter_->UseBagItems(selection))
				{
					cout << "�L���ﶵ�s�b" << endl;
				}
				auto equipment = fighter_->GetEquipment();
				CGlobalInfo::adventurer_data->SaveEquipment(equipment);
				auto weapon = fighter_->GetBagAllWeapon();
				CGlobalInfo::adventurer_data->SaveBagWeapon(weapon);
				auto food = fighter_->GetBagAllFood();
				CGlobalInfo::adventurer_data->SaveBagFood(food);
				auto armor = fighter_->GetBagAllArmor();
				CGlobalInfo::adventurer_data->SaveBagArmor(armor);
			}
		}
		else if (temp == "W" || temp == "w")
		{
			ShowWireHouse();
		}
	}
}

void SelectionMenu::ShowWireHouse()
{
	while (1)
	{
		system("CLS");
		fighter_->ShowAllBagItems();
		CGlobalInfo::wire_house->ShowWireHouseData();

		cout << "��^�п�JQ�A�Q��I�]�������~��J�ܮw�п�JP�A�Q���ܮw�����~�п�JG" << endl;
		string temp;
		cin >> temp;
		if (temp == "Q" || temp == "q")
		{
			return;
		}
		if (temp == "P" || temp == "p")
		{
			ShowWireHousePut();
		}
		else if (temp == "G" || temp == "g")
		{
			ShowWireHouseGet();
		}
	}
}

void SelectionMenu::ShowWireHousePut()
{
	while (1)
	{
		system("CLS");
		fighter_->ShowAllBagItems();
		CGlobalInfo::wire_house->ShowWireHouseData();
		cout << "��^�п�JQ�A�I�]�����~��J�ܮw�п�JID" << endl;
		string t;
		cin >> t;
		if (t == "Q" || t == "q")
		{
			return;
		}
		else
		{
			auto item = fighter_->GetItem(stoi(t));
			if (item)
			{
				CGlobalInfo::wire_house->AddItem(item);
			}
			else
			{
				cout << "�I�]�S�������~" << endl;
				system("Pause");
			}
			CGlobalInfo::wire_house->Save();
			auto weapon = fighter_->GetBagAllWeapon();
			CGlobalInfo::adventurer_data->SaveBagWeapon(weapon);
			auto armor = fighter_->GetBagAllArmor();
			CGlobalInfo::adventurer_data->SaveBagArmor(armor);
			auto food = fighter_->GetBagAllFood();
			CGlobalInfo::adventurer_data->SaveBagFood(food);
		}
	}
}

void SelectionMenu::ShowWireHouseGet()
{
	while (1)
	{
		system("CLS");
		fighter_->ShowAllBagItems();
		CGlobalInfo::wire_house->ShowWireHouseData();
		cout << "��^�п�JQ�A�q�ܮw������~�п�JID" << endl;
		string t;
		cin >> t;
		if (t == "Q" || t == "q")
		{
			return;
		}
		else
		{
			auto item = CGlobalInfo::wire_house->GetItem(stoi(t) - 1);
			if (item)
			{
				fighter_->PutItem(item);
			}
			else
			{
				cout << "�ܮw�S�������~" << endl;
				system("Pause");
			}
			CGlobalInfo::wire_house->Save();
			auto weapon = fighter_->GetBagAllWeapon();
			CGlobalInfo::adventurer_data->SaveBagWeapon(weapon);
			auto food = fighter_->GetBagAllFood();
			CGlobalInfo::adventurer_data->SaveBagFood(food);
			auto armor = fighter_->GetBagAllArmor();
			CGlobalInfo::adventurer_data->SaveBagArmor(armor);
		}
	}
}

void SelectionMenu::ShowTransfer()
{
	while (1)
	{
		system("CLS");
		if (fighter_->GetLevel() < 10)
		{
			cout << "�Q���~����¾" << endl;
			system("Pause");
			return;
		}
		else
		{
			cout << "��^�п�JQ�A��¾�C�h��J1�A��¾�k�v��J2�A��¾�}�b���J3�A��¾�s���J4" << endl;
			string temp;
			cin >> temp;
			if (temp == "Q" || temp == "q")
			{
				return;
			}
			else if (temp == "1")
			{
				AdventurerFactory* adventurer_factory = new WarriorFactory();
				fighter_ = adventurer_factory->CreateAdventure();
				fighter_->ReadData();
				fighter_->SetCareer("�C�h");
				CGlobalInfo::user->set_user((LifeEntity *)fighter_);

				auto attribute = fighter_->GetAttribute();
				CGlobalInfo::adventurer_data->Save(attribute);

				cout << "��¾���C�h" << endl;
				system("Pause");
				return;
			}
			else if (temp == "2")
			{
				AdventurerFactory* adventurer_factory = new MagicianFactory();
				fighter_ = adventurer_factory->CreateAdventure();
				fighter_->ReadData();
				fighter_->SetCareer("�k�v");
				CGlobalInfo::user->set_user((LifeEntity *)fighter_);

				auto attribute = fighter_->GetAttribute();
				CGlobalInfo::adventurer_data->Save(attribute);

				cout << "��¾���k�v" << endl;
				system("Pause");
				return;
			}
			else if (temp == "3")
			{
				AdventurerFactory* adventurer_factory = new ArcherFactory();
				fighter_ = adventurer_factory->CreateAdventure();
				fighter_->ReadData();
				fighter_->SetCareer("�}�b��");
				CGlobalInfo::user->set_user((LifeEntity *)fighter_);

				auto attribute = fighter_->GetAttribute();
				CGlobalInfo::adventurer_data->Save(attribute);

				cout << "��¾���}�b��" << endl;
				system("Pause");
				return;
			}
			else if (temp == "4")
			{
				AdventurerFactory* adventurer_factory = new ThiefFactory();
				fighter_ = adventurer_factory->CreateAdventure();
				fighter_->ReadData();
				fighter_->SetCareer("�s��");
				CGlobalInfo::user->set_user((LifeEntity *)fighter_);

				auto attribute = fighter_->GetAttribute();
				CGlobalInfo::adventurer_data->Save(attribute);

				cout << "��¾���s��" << endl;
				system("Pause");
				return;
			}
		}
	}
}

void SelectionMenu::Initialize() {
	srand((unsigned int)time(NULL));
	battle_scence = new BattleScence();
}

void SelectionMenu::InitialCareer()
{
	auto career = CGlobalInfo::adventurer_data->GetCurrentAdventurerCareer();
	AdventurerFactory* adventurer_factory;
	if (career == "��ߪ�")
	{
		adventurer_factory = new BeginnerFactory();
	}
	else if (career == "�C�h")
	{
		adventurer_factory = new WarriorFactory();
	}
	else if (career == "�k�v")
	{
		adventurer_factory = new MagicianFactory();
	}
	else if (career == "�}�b��")
	{
		adventurer_factory = new ArcherFactory();
	}
	else if (career == "�s��")
	{
		adventurer_factory = new ThiefFactory();
	}

	fighter_ = adventurer_factory->CreateAdventure();
	fighter_->ReadData();
	CGlobalInfo::user->set_user((LifeEntity *)fighter_);
}

void SelectionMenu::GoBattle()
{
	while (!fighter_->IsDead()) {
		Monster *m = battle_scence->MonsterSelection(fighter_);
		if (m) {
			battle_scence->FightStatus(m, fighter_);
			cout << endl << endl << "�԰��}�l" << endl << endl;
			battle_scence->startfight(m, fighter_);
			delete m;

			cout << "�~��԰���?�԰���JY,�h�X��JQ" << endl;
			string temp = "";
			cin >> temp;
			if (temp != "Y" || temp != "y")
			{
				system("CLS");
				return;
			}
		}
		else
		{
			cout << "�S���Ǫ�����" << endl;
			system("Pause");
			return;
		}
	}
	cout << "�z���F" << endl;
	system("Pause");
}

void SelectionMenu::SplitString(const string & s, vector<string>& v, const string & c)
{
}