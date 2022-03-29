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
		cout << "請選擇功能選項 : " << endl;
		cout << "1. 人物屬性" << endl;
		cout << "2. 地圖 " << endl;
		cout << "3. 商店 " << endl;
		cout << "4. 背包/倉庫 " << endl;
		cout << "5. 轉職" << endl;
		cout << "6. 退出 " << endl;

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
				cout << "掰掰" << endl;
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

		cout << "戰鬥輸入Y,退出輸入Q，刷新地圖輸入任意內容，想去其他地方輸入指令ex: move 勇士之村, move (south, east....)" << endl;
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
		cout << "返回請輸入Q，配屬性點請輸入A，升級技能請輸入S" << endl;
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
			cout << "沒有屬性點" << endl;
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
			cout << "初心者沒有辦法習得技能" << endl;
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
			cout << "技能點剩下:" << skill_points << endl;

			cout << "返回請輸入Q，升級或習得技能請輸入ID" << endl;
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
				cout << "技能點不足" << endl;
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
		cout << "返回請輸入Q，購買請輸入B，賣出請輸入S，升級裝備請輸入L" << endl;
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
		cout << "返回請輸入Q,買補給品請輸入F，買武器請輸入W，買盾牌請輸入A" << endl;
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

		cout << "返回請輸入Q，請輸入補給品的ID" << endl;
		string t;
		cin >> t;
		if (t == "Q" || t == "q")
		{
			return;
		}
		if (t.size() > 2 || !isdigit(t[0]))
		{
			cout << "請輸入補給品的id" << endl;
			system("Pause");
			continue;
		}
		auto item = CGlobalInfo::itm_data->GetItemById(stoi(t) - 1, FOOD);
		if (!item)
		{
			cout << "請輸入補給品的id" << endl;
			system("Pause");
			continue;
		}
		int item_money = item->GetMoney();
		if (fighter_->GetMoney() < item_money)
		{
			cout << "錢不夠" << endl;
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

		cout << "返回請輸入Q，請輸入武器的ID" << endl;
		string t;
		cin >> t;
		if (t == "Q" || t == "q")
		{
			return;
		}

		if (t.size() > 2 || !isdigit(t[0]))
		{
			cout << "請輸入武器的id" << endl;
			system("Pause");
			continue;
		}
		auto item = CGlobalInfo::itm_data->GetItemById(stoi(t) - 1, WEAPON);
		if (!item)
		{
			cout << "請輸入武器的id" << endl;
			system("Pause");
			continue;
		}
		int item_money = item->GetMoney();
		if (fighter_->GetMoney() < item_money)
		{
			cout << "錢不夠" << endl;
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

		cout << "返回請輸入Q，請輸入盾牌的ID" << endl;
		string t;
		cin >> t;
		if (t == "Q" || t == "q")
		{
			return;
		}

		if (t.size() > 2 || !isdigit(t[0]))
		{
			cout << "請輸入盾牌的id" << endl;
			system("Pause");
			continue;
		}

		auto item = CGlobalInfo::itm_data->GetItemById(stoi(t) - 1, ARMOR);
		if (!item)
		{
			cout << "請輸入盾牌的id" << endl;
			system("Pause");
			continue;
		}

		int item_money = item->GetMoney();
		if (fighter_->GetMoney() < item_money)
		{
			cout << "錢不夠" << endl;
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
		cout << "返回請輸入Q,賣補給品請輸入F，賣武器請輸入W，賣盾牌請輸入A" << endl;
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

		cout << "返回請輸入Q，請輸入補給品的ID" << endl;
		string t;
		cin >> t;
		if (t == "Q" || t == "q")
		{
			return;
		}

		if (t.size() > 2 || !isdigit(t[0]))
		{
			cout << "請輸入補給品的id" << endl;
			system("Pause");
			continue;
		}
		auto item = CGlobalInfo::itm_data->GetItemById(stoi(t) - 1, FOOD);
		if (!item)
		{
			cout << "請輸入補給品的id" << endl;
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

		cout << "返回請輸入Q，請輸入武器的ID" << endl;
		string t;
		cin >> t;
		if (t == "Q" || t == "q")
		{
			return;
		}

		if (t.size() > 2 || !isdigit(t[0]))
		{
			cout << "請輸入武器的id" << endl;
			system("Pause");
			continue;
		}
		auto item = CGlobalInfo::itm_data->GetItemById(stoi(t) - 1, WEAPON);
		if (!item)
		{
			cout << "請輸入武器的id" << endl;
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

		cout << "返回請輸入Q，請輸入盾牌的ID" << endl;
		string t;
		cin >> t;
		if (t == "Q" || t == "q")
		{
			return;
		}
		if (t.size() > 2 || !isdigit(t[0]))
		{
			cout << "請輸入盾牌的id" << endl;
			system("Pause");
			continue;
		}
		auto item = CGlobalInfo::itm_data->GetItemById(stoi(t) - 1, ARMOR);
		if (!item)
		{
			cout << "請輸入盾牌的id" << endl;
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
		cout << "返回請輸入Q,升級武器請輸入W，升級盾牌請輸入A" << endl;
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
			cout << "目前武器為:" << w->GetName() << " 等級為:" << w->GetLevel() << endl;
			cout << "返回請輸入Q，升級一次需花費300楓幣，請輸入Y" << endl;
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
					cout << "錢不夠" << endl;
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
			cout << "沒有裝備武器" << endl;
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
			cout << "目前盾牌為:" << a->GetName() << " 等級為:" << a->GetLevel() << endl;
			cout << "返回請輸入Q，升級一次需花費300楓幣，請輸入Y" << endl;
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
					cout << "錢不夠" << endl;
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
			cout << "沒有裝備盾牌" << endl;
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

		cout << "返回請輸入Q，使用道具輸入Y，查看昌庫請輸入W" << endl;
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
			cout << fighter_->GetName() << " 需要使用背包物品嗎?\n0 --> No, Others --> Yes, 使用之物品編號: ";
			int selection;
			cin >> selection;
			if (selection) {
				if (!fighter_->UseBagItems(selection))
				{
					cout << "無此選項存在" << endl;
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

		cout << "返回請輸入Q，想把背包內的物品放入倉庫請輸入P，想拿倉庫的物品請輸入G" << endl;
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
		cout << "返回請輸入Q，背包的物品放入倉庫請輸入ID" << endl;
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
				cout << "背包沒有此物品" << endl;
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
		cout << "返回請輸入Q，從倉庫領取物品請輸入ID" << endl;
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
				cout << "倉庫沒有次物品" << endl;
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
			cout << "十等才能轉職" << endl;
			system("Pause");
			return;
		}
		else
		{
			cout << "返回請輸入Q，轉職劍士輸入1，轉職法師輸入2，轉職弓箭手輸入3，轉職盜賊輸入4" << endl;
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
				fighter_->SetCareer("劍士");
				CGlobalInfo::user->set_user((LifeEntity *)fighter_);

				auto attribute = fighter_->GetAttribute();
				CGlobalInfo::adventurer_data->Save(attribute);

				cout << "轉職為劍士" << endl;
				system("Pause");
				return;
			}
			else if (temp == "2")
			{
				AdventurerFactory* adventurer_factory = new MagicianFactory();
				fighter_ = adventurer_factory->CreateAdventure();
				fighter_->ReadData();
				fighter_->SetCareer("法師");
				CGlobalInfo::user->set_user((LifeEntity *)fighter_);

				auto attribute = fighter_->GetAttribute();
				CGlobalInfo::adventurer_data->Save(attribute);

				cout << "轉職為法師" << endl;
				system("Pause");
				return;
			}
			else if (temp == "3")
			{
				AdventurerFactory* adventurer_factory = new ArcherFactory();
				fighter_ = adventurer_factory->CreateAdventure();
				fighter_->ReadData();
				fighter_->SetCareer("弓箭手");
				CGlobalInfo::user->set_user((LifeEntity *)fighter_);

				auto attribute = fighter_->GetAttribute();
				CGlobalInfo::adventurer_data->Save(attribute);

				cout << "轉職為弓箭手" << endl;
				system("Pause");
				return;
			}
			else if (temp == "4")
			{
				AdventurerFactory* adventurer_factory = new ThiefFactory();
				fighter_ = adventurer_factory->CreateAdventure();
				fighter_->ReadData();
				fighter_->SetCareer("盜賊");
				CGlobalInfo::user->set_user((LifeEntity *)fighter_);

				auto attribute = fighter_->GetAttribute();
				CGlobalInfo::adventurer_data->Save(attribute);

				cout << "轉職為盜賊" << endl;
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
	if (career == "初心者")
	{
		adventurer_factory = new BeginnerFactory();
	}
	else if (career == "劍士")
	{
		adventurer_factory = new WarriorFactory();
	}
	else if (career == "法師")
	{
		adventurer_factory = new MagicianFactory();
	}
	else if (career == "弓箭手")
	{
		adventurer_factory = new ArcherFactory();
	}
	else if (career == "盜賊")
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
			cout << endl << endl << "戰鬥開始" << endl << endl;
			battle_scence->startfight(m, fighter_);
			delete m;

			cout << "繼續戰鬥嗎?戰鬥輸入Y,退出輸入Q" << endl;
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
			cout << "沒有怪物產生" << endl;
			system("Pause");
			return;
		}
	}
	cout << "您死了" << endl;
	system("Pause");
}

void SelectionMenu::SplitString(const string & s, vector<string>& v, const string & c)
{
}