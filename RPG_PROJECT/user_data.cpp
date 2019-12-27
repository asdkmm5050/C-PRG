#include"user_data.h"
#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
using namespace std;
int log_in(){
    string name,password;
    cout << "帳號 : ";
    cin >> name;
    cout << "密碼 : ";
    cin >> password;
    vector<User_data> user_list;
    ifstream fin("user_data.txt");
    while(!fin.eof()){
        User_data ud;
        fin >> ud.user_id;
        fin >> ud.user_name;
        fin >> ud.password;
        user_list.push_back(ud);
    }
    fin.close();
    for(int i = 0 ; i < user_list.size(); i++){
        if(user_list[i].user_name == name && user_list[i].password == password){
            cout << "登入中...\n";
            Sleep(500);
            cout << "完成\n";
            Sleep(500);
            system("CLS");
            return user_list[i].user_id;
        }
    }
    cout << "..帳號或密碼錯誤..\n";
            return log_in();
}
int user_create(){
    string name,password;
    cout << "帳號 : ";
    cin >> name;
    cout << "密碼 : ";
    cin >> password; 
    vector<User_data>user_list;
    ifstream fin("user_data.txt");
    while(!fin.eof()){
        User_data ud;
        fin >> ud.user_id;
        fin >> ud.user_name;
        fin >> ud.password;
        user_list.push_back(ud);
    }
    for(int i = 0 ; i < user_list.size(); i++){
        if(name == user_list[i].user_name){
            cout << "..帳號已被使用..\n";
            Sleep(500);
            system("CLS");
            return user_create();
        }
    }
    static int userId = user_list[user_list.size()-1].user_id + 1;
    User_data ud(name, password, userId++);
    user_list.push_back(ud);
    ofstream fout("user_data.txt");
    for (int i = 0; i < user_list.size(); i++){
        fout << user_list[i].user_id <<" "<< user_list[i].user_name << " " << user_list[i].password;
        if(i != user_list.size()-1)
            fout << " ";
    }
    fout.close();
    return ud.user_id;
    }
void user_delete(){
    string name,password;
    cout << "帳號 : ";
    cin >> name;
    cout << "密碼 : ";
    cin >> password; 
    vector<User_data>user_list;
	vector<User_data>change_list;
    ifstream fin("user_data.txt");
    while(!fin.eof()){
        User_data ud;
        fin >> ud.user_id;
        fin >> ud.user_name;
        fin >> ud.password;
        user_list.push_back(ud);
    }
    ofstream fout("user_data.txt");
	for (int i = 0; i < user_list.size(); i++) {
		if (user_list[i].user_name != name && user_list[i].password != password) {
			change_list.push_back(user_list[i]);
		}
	}
    for (int i = 0; i < change_list.size(); i++){
            fout << change_list[i].user_id <<" "<< change_list[i].user_name << " " << change_list[i].password;
                if(i != change_list.size()-1)
                    fout << " ";
    }
    fout.close();
}
int log_function(){
    string number;
    cout << "\n(0)登入\n(1)註冊\n(2)註銷\n";
    cin >> number;
    if(number == "0")
        return log_in();
    if(number == "1"){
        user_create();
        return log_function();
    }
    if(number == "2"){
        user_delete();
        Sleep(500);
        system("CLS");
        return log_function();
    }
    else
        return log_function();
} 

User_data::User_data(string userName, string inputpassword, int id){
    user_name = userName;
    password = inputpassword;
    user_id = id;
}
User_data::User_data(){

}
