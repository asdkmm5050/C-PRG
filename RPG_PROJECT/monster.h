#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<time.h>
#include<vector>
#include<windows.h>
using namespace std;
class Monster {
public:
	Monster(int, int, int, string, string);
	Monster();
	vector<Monster> create_monster(int);
	Monster choose_monster(vector<Monster>, int);
	void print_monster(vector<Monster>, int);
	int get_damage();
	int get_blood();
	void set_blood(int);
	void set_name(string);
	int monster_level, monster_damage, monster_blood;
	string monster_name, monster_skill;
};
