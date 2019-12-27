#include"bag.h"
Item Item::get_item(int user_number, string character_name) {
	ifstream fin("bag_item.txt");
	vector<Item>item_list;
	int monster_drop;
	while (!fin.eof()) {
		Item it;
		fin >> it.item_number >> it.item_type >> it.item_name >> it.item_attack;
		it.character_name = character_name;
		it.user_number = user_number;
		item_list.push_back(it);
	}
	monster_drop = rand() % item_list.size();
	fin.close();
	return item_list[monster_drop];
}
void Item::save_item(vector<Item>item_list, string character_name, int user_number) {
	ifstream fin("in_bag_item.txt");
	vector<Item>other_item_list;
	while (!fin.eof()) {
		Item it;
		fin >> it.item_number >> it.item_type >> it.item_name >> it.item_attack >> it.character_name >> it.user_number;
		other_item_list.push_back(it);
	}
	fin.close();
	ofstream fout("in_bag_item.txt");
	for (int i = 0; i < other_item_list.size(); i++) {
		if (other_item_list[i].item_name != character_name && other_item_list[i].user_number != user_number) {
			fout << other_item_list[i].item_number << " " << other_item_list[i].item_type << " " << other_item_list[i].item_name << " " << other_item_list[i].item_attack << " " << other_item_list[i].character_name << " " << other_item_list[i].user_number << endl;
		}
	}
	for (int i = 0; i < item_list.size(); i++) {
		fout << item_list[i].item_number << " " << item_list[i].item_type << " " << item_list[i].item_name << " " << item_list[i].item_attack << " " << item_list[i].character_name << " " << item_list[i].user_number ;
		if (i != item_list.size() - 1) {
			fout << endl;
		}
	}

}
vector<Item> Item::open_bag(int user_number, string character_name) {//回傳當前選擇角色之背包物品vecoter
	ifstream fin("in_bag_item.txt");
	vector<Item>item_list;
	vector<Item>bag_list;
	while (!fin.eof()) {
		Item it;
		fin >> it.item_number >> it.item_type >> it.item_name >> it.item_attack >> it.character_name >> it.user_number;
		item_list.push_back(it);
	}
	fin.close();
	for (int i = 0; i < item_list.size(); i++) {
		if (item_list[i].character_name == character_name && item_list[i].user_number == user_number) {
			bag_list.push_back(item_list[i]);
		}
	}
	return bag_list;
}
void Item::print_bag(vector<Item> item_list, int using_item, int using_bag_number, int body_item_number) {
	for (int i = 0; i < item_list.size(); i++) {
		if(i!=using_item&&i!= using_bag_number&&i!=body_item_number)
			cout << item_list[i].item_name << endl;
	}
}
vector<Item> Item::delet_item(vector<Item>item_list) {
	int only_one = 0;
	string item_name;
	vector<Item>change_list;
	cout << "請輸入物品:";
	cin >> item_name;
	for (int i = 0; i < item_list.size(); i++) {
		if ((item_list[i].item_name == item_name)&&only_one == 0) {
			only_one = 1;
		}
		else {
			change_list.push_back(item_list[i]);
		}
	}
	return change_list;
}