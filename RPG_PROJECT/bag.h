#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<time.h>
using namespace std;
class Item {
	public:
		string item_name, character_name;
		int item_number, user_number, item_attack, item_type;
		Item get_item(int, string);
		void save_item(vector<Item>, string, int);
		void print_bag(vector<Item>, int, int, int);
		vector<Item> open_bag(int, string);
		vector<Item> delet_item(vector<Item>);
};