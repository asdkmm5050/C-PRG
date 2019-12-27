#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;
class Money {
	public:
		int user_number, money;
		string character_name;
		int get_money(int, string);
		void save_money(int, string, int);
};