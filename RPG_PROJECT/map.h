#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<conio.h>
using namespace std;
class Map{
    public:
        Map(string, int, int, int, int);
		Map();
		Map map_load(int);
		Map map_function(int);
		int get_map_number();
		int get_monster_level();
	private:
		string map_data;
		int map_number, map_number_last, map_number_next,monster_level;
};