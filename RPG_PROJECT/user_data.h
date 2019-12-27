#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;
class User_data{
    public:
        User_data(string, string, int);
        User_data();
        string user_name,password;
        int user_id;
};
int log_function();