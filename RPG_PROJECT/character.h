#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;
class Character{
    public:
        Character(string, int, int, int);
        Character choose_character(int);
		void delete_character(int);
		int create_character(int);
		Character character_function(int);
		void character_save(Character);
		int get_level();
		int get_type();
		void set_level(int);
        string character_name;
        int character_level ,belong_user,character_type,vecter_number;
};
