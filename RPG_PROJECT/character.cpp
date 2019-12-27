#include"character.h"
using namespace std;
Character Character::choose_character(int user_number){
	ifstream fin("character.txt");
	string name;
	int level, race, id;
	vector<Character>character_list;
	while (!fin.eof()) {
		fin >> id >> race >> level >> name;
		Character ch(name, level, id, race);
		character_list.push_back(ch);
	}
	fin.close();
	cout << "�п�J����W��\n";
	for (int i = 0; i < character_list.size(); i++) {
		if (user_number == character_list[i].belong_user) {
			cout  << "����W�� : " << character_list[i].character_name << endl;
			cout << "���� : " << character_list[i].character_level << endl << "�ر� : ";
			if (character_list[i].character_type == 1)cout << "�~�H" << endl;
			if (character_list[i].character_type == 2)cout << "�H��" << endl;
			if (character_list[i].character_type == 3)cout << "���F" << endl;
		}
	}
	cin >> name;
	for (int i = 0; i < character_list.size(); i++) {
		if (name == character_list[i].character_name && user_number == character_list[i].belong_user) {
			character_list[i].vecter_number = i;
			return character_list[i];
		}
	}
	return Character::choose_character(user_number);
}
void Character::delete_character(int number) {
	ifstream fin("character.txt");
	string name;
	int level, race, id;
	vector<Character>character_list;
	vector<Character>chanege_list;
	while (!fin.eof()) {
		fin >> id >> race >> level >> name;
		Character ch(name, level, id, race);
		character_list.push_back(ch);
	}
	fin.close();
	for (int i = 0; i < character_list.size(); i++) {
		if (number == character_list[i].belong_user) {
			cout << "����W�� : " << character_list[i].character_name << endl;
			cout << "���� : " << character_list[i].character_level << endl << "�ر� : \n";
			if (character_list[i].character_type == 1)cout << "�~�H" << endl;
			if (character_list[i].character_type == 2)cout << "�H��" << endl;
			if (character_list[i].character_type == 3)cout << "���F" << endl;
		}
	}
	cout << "�п�J���R������W�� : ";
	cin >> name;
	ofstream fout("character.txt");
	for (int i = 0; i < character_list.size(); i++) {
		if ((number == character_list[i].belong_user)&&name == character_list[i].character_name) {
			cout << "�R�����\\n";
		}
		else {
			chanege_list.push_back(character_list[i]);
		}
	}
	for (int i = 0; i < chanege_list.size(); i++) {
		fout << chanege_list[i].belong_user << " " << chanege_list[i].character_type << " " << chanege_list[i].character_level << " " << chanege_list[i].character_name;
		if (i != chanege_list.size() - 1) {
			fout << endl;
		}
	}
}
int Character::create_character(int number) {
	ifstream fin("character.txt");
	string name;
	int level, race, id,relist = 0;
	vector<Character>character_list;
	while (!fin.eof()) {
		fin >> id >> race >> level >> name;
		Character ch(name, level, id, race);
		character_list.push_back(ch);
	}
	fin.close();
	for (int i = 0; i < character_list.size(); i++) {
		if ((number == character_list[i].belong_user))relist++;
	}
	if (relist >= 3)return 0;
	cout << "�Ыب���\n�п�J�W�� : " << endl;
	cin >> name;
	for (int i = 0; i < character_list.size(); i++) {
		if ((number == character_list[i].belong_user)&&(name == character_list[i].character_name)) {
			cout << "���~--�W�٭���\n";
			return Character::create_character(number);
			break;
		}
	}
	cout << "(1)�~�H\n(2)�H��\n(3)���F\n�п�J�}��ر� : ";
	cin >> race;
	Character ch(name, 1, number, race);
	character_list.push_back(ch);
	ofstream fout("character.txt");
	for (int i = 0; i < character_list.size(); i++) {
		fout << character_list[i].belong_user << " " << character_list[i].character_type << " " << character_list[i].character_level << " " << character_list[i].character_name;
		if (i != character_list.size() - 1) {
			fout << endl;
		}
	}
	fout.close();
	return 1;
}
Character Character::character_function(int number) {
	cout << "(1)��ܨ���\n(2)�Ыب���\n(3)�R������\n";
	int choose_mode;
	cin >> choose_mode;
	if (choose_mode == 1)return Character::choose_character(number);
	if (choose_mode == 2) { 
		if (Character::create_character(number))return Character::character_function(number); 
		else {
			cout << "����ƶq�W�L����...\n";
			return Character::character_function(number);
		}
	}
	if (choose_mode == 3) {
		Character::delete_character(number);
		return Character::character_function(number); 
	}
	else return Character::character_function(number);
}
void Character::character_save(Character save){
	ifstream fin("character.txt");
	string name;
	int level, race, id, relist = 0;
	vector<Character>character_list;
	while (!fin.eof()) {
		fin >> id >> race >> level >> name;
		Character ch(name, level, id, race);
		character_list.push_back(ch);
	}
	fin.close();
	ofstream fout("character.txt");
	for (int i = 0; i < character_list.size(); i++) {
		if ((character_list[i].belong_user == save.belong_user) && (character_list[i].character_name == save.character_name)) {
			fout << save.belong_user << " " << save.character_type << " " << save.character_level << " " << save.character_name;
			if (i != character_list.size() - 1) {
				fout << endl;
			}
		}
		else {
			fout << character_list[i].belong_user << " " << character_list[i].character_type << " " << character_list[i].character_level << " " << character_list[i].character_name;
			if (i != character_list.size() - 1) {
				fout << endl;
			}
		}
	}
	fout.close();
}
int Character::get_level() {
	return character_level;
}
int Character::get_type() {
	return character_type;
}
void Character::set_level(int number) {
	character_level = number;
}
Character::Character(string name, int level, int userId, int type){
    character_name = name;
    character_level = level;
    belong_user = userId;
    character_type = type;
}
