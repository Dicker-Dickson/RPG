#include "start_menu.h"

StartMenu::StartMenu()
{
	ifstream fin("userdata.txt", ios::in);
	if (!fin) {
		cout << "Ū�ɥ���: userdata.txt" << endl;
		system("Pause");
		exit(0);
	}

	string tmp_name;
	string tmp_password;

	UserData data;
	while (fin >> tmp_name >> tmp_password) {
		UserData data;
		data.name = tmp_name;
		data.password = tmp_password;
		user_data_.push_back(data);
	}

	fin.close();
	user_name_ = tmp_name;
}

StartMenu::~StartMenu()
{
}

void StartMenu::ShowMainMenu()
{
	while (1)
	{
		system("CLS");
		cout << "�w��Ө췬����" << endl;
		cout << "���U��J0\n�n�J��J1" << endl;
		string sentense;
		getline(cin, sentense);

		if (sentense == "0")
		{
			SignUp();
			CGlobalInfo::wire_house->SetUser(user_name_);
			CGlobalInfo::wire_house->Load();
			return;
		}
		else if (sentense == "1")
		{
			LogIn();
			ChoiseAdventurer();
			CGlobalInfo::wire_house->SetUser(user_name_);
			CGlobalInfo::wire_house->Load();
			return;
		}
		else
		{
			cout << "��J���~" << endl;
			system("Pause");
		}
	}
}

void StartMenu::SignUp()
{
	ofstream fout("userdata.txt", ios::app);
	if (!fout) {
		cout << "Ū�ɥ���: userdata.txt" << endl;
		system("Pause");
		exit(0);
	}

	string tmp_name;
	string tmp_password;
	string confirm_password;

	do {
		cout << "�п�J�ϥΪ̱b��" << endl;
		cin >> tmp_name;
		cout << "�п�J�ϥΪ̱K�X" << endl;
		cin >> tmp_password;
		cout << "�ЦA����J�ϥΪ̱K�X" << endl;
		cin >> confirm_password;
	} while (confirm_password != tmp_password);

	UserData data;
	fout << tmp_name << "\t" << tmp_password << "\n";

	fout.close();

	NewFolder(tmp_name);

	CGlobalInfo::adventurer_data->SetUserName(tmp_name);
	CGlobalInfo::adventurer_data->NewData();
}

void StartMenu::LogIn()
{
	while (1)
	{
		string tmp_name;
		string tmp_password;
		cout << "�п�J�ϥΪ̱b��" << endl;
		getline(cin, tmp_name);
		cout << "�п�J�ϥΪ̱K�X" << endl;
		getline(cin, tmp_password);

		for (int i = 0; i < user_data_.size(); ++i)
		{
			if (user_data_[i].name == tmp_name && user_data_[i].password == tmp_password)
			{
				CGlobalInfo::adventurer_data->ReadData(tmp_name);
				user_name_ = tmp_name;
				return;
			}
		}

		cout << "�n�J����" << endl;
		system("Pause");
		system("CLS");
	}
}

void StartMenu::ChoiseAdventurer()
{
	while (1)
	{
		cout << "��J���⸹�X(1~3)�i�J����A�s�ب���п�Jn�A�Y�n�R���п�Jd" << endl;
		string sentence;
		getline(cin, sentence);
		if (sentence == "d")
		{
			cout << "��J�n�R��������id" << endl;
			string delete_id;
			getline(cin, delete_id);

			CGlobalInfo::adventurer_data->SetUserName(user_name_);
			if (!isdigit(delete_id[0]) && delete_id.length() > 1)
			{
				cout << "��J���~" << endl;
				system("Pause");
				exit(0);
			}
			else
			{
				CGlobalInfo::adventurer_data->DeleteAdventurer(std::stoi(delete_id));
				CGlobalInfo::adventurer_data->ReadData(user_name_);
			}
		}
		else if (sentence == "n")
		{
			if (CGlobalInfo::adventurer_data->NewData())
			{
				break;
			}
			else
			{
			}
		}
		else if (sentence == "1" || sentence == "2" || sentence == "3")
		{
			user_id_ = std::stoi(sentence);
			CGlobalInfo::adventurer_data->SetCurrentAdventurerId(user_id_);
			break;
		}
	}
}

void StartMenu::NewFolder(string path)
{
	_mkdir("./data");

	string p = "./data/" + path;

	_mkdir(p.c_str());

	string new_wirehouse = "./data/" + path + "/wirehouse.txt";
	ofstream fout(new_wirehouse, ios::binary);
}

string StartMenu::GetUser()
{
	return user_name_;
}

int StartMenu::GetUserId()
{
	return user_id_;
}