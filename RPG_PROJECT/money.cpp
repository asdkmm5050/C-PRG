#include"money.h"
int Money::get_money(int user_number, string charater_name) {
	ifstream fin("money.txt");
	while (!fin.eof()) {
		Money money;
		fin >> money.user_number >> money.character_name >> money.money;
		if (money.user_number == user_number && money.character_name == money.character_name) {
			return money.money;
		}
	}
	return 0;
}
void Money::save_money(int user_number, string character_name, int new_money) {
	ifstream fin("money.txt");
	vector<Money>money_list;
	Money money;
	while (!fin.eof()) {
		Money money;
		fin >> money.user_number >> money.character_name >> money.money;
		if(money.user_number!=user_number&&money.character_name!=character_name)money_list.push_back(money);
	}
	fin.close();
	ofstream fout("money.txt");
	for (int i = 0; i < money_list.size(); i++) {
		fout << money_list[i].user_number << " " << money_list[i].character_name << " " << money_list[i].money << endl;
	}
	fout << user_number << " " << character_name << " " << new_money;
	fout.close();
}