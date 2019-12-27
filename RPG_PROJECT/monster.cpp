#include"monster.h"
vector<Monster> Monster::create_monster(int number){//接收地圖怪物等級，產生怪物
	srand(time(NULL));
	ifstream fin("monster.txt");
	ifstream get_f("monster_status.txt");
	int level, damage, blood, choose, monster_number = 1;
	string name, skill,status;
	vector<Monster>monster_list;
	vector<string>status_list;
	while (!get_f.eof()) {
		get_f >> status;
		status_list.push_back(status);
	}
	while (!fin.eof()) {
		fin >> level >> damage >> blood >> name >> skill;
		for (int i = 0; i < rand() % 10 + 1; i++) {
			status = status_list[rand() % (status_list.size())] + name +to_string(i);
			Monster mr(level, damage, blood, status, skill);
			monster_list.push_back(mr);
		}
	}
	fin.close();
	for (int i = 0; i < monster_list.size(); i++) {
		if (number == monster_list[i].monster_level) {
			cout << monster_number++ << " LEVEL : " << monster_list[i].monster_level << " " << monster_list[i].monster_name << endl;
		}
	}
	return monster_list;
}
/*void Monster::print_monster(vector<Monster>monster_list,int number) {
	int monster_number = 1;
	for (int i = 0; i < monster_list.size(); i++) {
		if (number == monster_list[i].monster_level) {
			cout << monster_number++ << " LEVEL : " << monster_list[i].monster_level << " " << monster_list[i].monster_name << endl;
		}
	}
}*/
Monster Monster::choose_monster(vector<Monster>monster_list, int map_level) {
	int choose;
	int monster_number = 0;
	cout << "請輸入怪物編號 : ";
	cin >> choose;
	for (int i = 0; i < monster_list.size(); i++) {
		if (monster_list[i].monster_level == map_level) {
			monster_number++;
		}
		if (monster_number == choose) {
			cout << "你選擇了" << monster_list[i].monster_name << endl;
			Sleep(500);
			return monster_list[i];
		}
	}
	if (choose >= monster_number || choose <= 0) {
		return Monster::choose_monster(monster_list, map_level);
	}
}
int Monster::get_blood() {
	return monster_blood;
}
int Monster::get_damage() {
	return monster_damage;
}
void Monster::set_blood(int change_blood){
	monster_blood = change_blood;
}
void Monster::set_name(string name) {
	monster_name = name;
}
Monster::Monster(int level, int damage, int blood, string name, string skill) {
	monster_level = level;
	monster_damage = damage;
	monster_blood = blood;
	monster_name = name;
	monster_skill = skill;
}
Monster::Monster(){}