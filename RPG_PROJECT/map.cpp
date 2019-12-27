#include"map.h"
Map::Map(string data, int now, int last, int next, int monster_lv) {
	map_data = data;
	map_number = now;
	map_number_last = last;
	map_number_next = next;
	monster_level = monster_lv;
}
Map Map::map_load(int number) {
	ifstream fin("map.txt");
	string data;
	int now, last, next, monster_level;
	vector<Map>map_list;
	while (!fin.eof()) {
		fin >> now >> last >> next >> monster_level >> data;
		Map map_object(data, now, last, next,monster_level);
		map_list.push_back(map_object);
	}
	for (int i = 0; i < map_list.size(); i++) {
		if (number == map_list[i].map_number) {
			cout << "�@�@�@�@" << map_list[i].map_data << "�@�@�@�@" << endl;
			cout << "��e�a�ϵ��� : " << map_list[i].monster_level<<endl;
			cout << "�e�� : " << map_list[map_list[i].map_number_next-1].map_data << endl;
			return map_list[i];
		}
	}

}
Map Map::map_function(int number) {
	string choose;
	cout << "(1)�e�i (2)��h\n";
	choose = _getch();
	system("CLS");
	if (choose == "1")return Map::map_load(Map::map_number_next);
	if (choose == "2")return Map::map_load(Map::map_number_last);
	else {
		cout << "��ı�o���ض¶ª��A�٬O���n�L�h���n\n";
		return  Map::map_function(number);
	}
}
int Map::get_map_number() {
	return map_number;
}
int Map::get_monster_level() {
	return monster_level;
}