#include<iostream>
#include"user_data.h"
#include"character.h"
#include"map.h"
#include"monster.h"
#include"bag.h"
#include"money.h"
#include<windows.h>
using namespace std;
//txt檔案請勿更動，除非新增
//ch.get_level()取得等級，ch.set_level(int)存回等級
//mp.map_function(mp.get_map_number()) 取得地圖物件
//mp.get_monster_level()取得當前地圖怪物等級
//剩餘 技能、商店
//戰鬥回傳直 你勝利1 怪物勝利0
string call_command() {
	string choose;
	cout << "(1)戰鬥\n(2)背包\n(3)商店\n(4)角色數值\n(5)登出\n其他 : 移動\n";
	return choose = _getch();
}
int get_exp(string cname, int unumber){
	ifstream fin("exp.txt");
	string name;
	int number, exp = 0;
	while (!fin.eof()) {
		fin >> number >> name >> exp;
		if (cname == name && unumber == number) {
			break;
		}
	}
	return exp;
}
void set_exp(string cname, int unumber, int cexp) {
	ifstream fin("exp.txt");
	string name = cname;
	int number = unumber, exp = cexp;
	vector<int> number_list, exp_list;
	vector<string> name_list;
	while (!fin.eof()) {
		fin >> number >> name >> exp;
		if (cname == name && unumber == number) {
			number_list.push_back(unumber);
			name_list.push_back(cname);
			exp_list.push_back(cexp);
		}
		else {
			number_list.push_back(number);
			name_list.push_back(name);
			exp_list.push_back(exp);
		}
	}
	fin.close();
	ofstream fout("exp.txt");
	for (int i = 0; i < exp_list.size(); i++) {
		fout << number_list[i] << " " << name_list[i] << " " << exp_list[i];
		if (i != exp_list.size() - 1) {
			cout << endl;
		}
	}
	fout.close();
}
int fight(Monster monster, int blood, int attack, int using_item, int body_item) {
	int character_blood = blood + body_item, character_attack = attack + using_item, skill_frequency = 0;
	if (rand() % 2) {
		cout << "由你先攻\n";
		while (1) {
			if (rand() % 3||skill_frequency > 5) {
				monster.monster_blood -= character_attack;
				cout << "你造成了 " << character_attack << " 點傷害\n";
			}
			else {
				monster.monster_blood -= character_attack * 2;
				cout << "你使用技能造成了 " << character_attack * 2 << " 點傷害\n";
				skill_frequency++;
			}
			if (monster.monster_blood <= 0) {
				cout << "怪物死亡了\n";
				Sleep(2000);
				return 1;
			}
			cout << monster.monster_name << " 剩下 " << monster.monster_blood << "點血量\n\n\n";
			Sleep(500);
			if (rand() % 3) {
				character_blood -= monster.monster_damage;
				cout << monster.monster_name << " 造成了 " << monster.monster_damage << "點傷害\n";
			}
			else {
				character_blood -= monster.monster_damage*2;
				cout << monster.monster_name << " 使用 " << monster.monster_skill << " 造成了 " << monster.monster_damage << "點傷害\n";
			}
			if (character_blood <= 0) {
				cout << "你死亡了\n";
				Sleep(2000);
				return 0;
			}
			cout << " 你還剩下 " << character_blood << " 點血量\n\n\n";
			Sleep(500);
		}
	}
	else {
		cout << "怪物先攻\n";
		while (1) {
			if (rand() % 3) {
				character_blood -= monster.monster_damage;
				cout << monster.monster_name << " 造成了 " << monster.monster_damage << "點傷害\n";
			}
			else {
				character_blood -= monster.monster_damage * 2;
				cout << monster.monster_name << " 使用 " << monster.monster_skill << " 造成了 " << monster.monster_damage << "點傷害\n";
			}
			if (character_blood <= 0) {
				cout << "你死亡了\n但路過的牧師拯救了你!!";
				Sleep(2000);
				return 0;
			}
			cout << "你還剩下 " << character_blood << " 點血量\n\n\n";
			Sleep(500);
			if (rand() % 3 || skill_frequency > 5) {
				monster.monster_blood -= character_attack;
				cout << "你造成了 " << character_attack << " 點傷害\n";
			}
			else {
				monster.monster_blood -= character_attack * 2;
				cout << "你使用技能造成了 " << character_attack * 2 << " 點傷害\n";
				skill_frequency++;
			}
			if (monster.monster_blood <= 0) {
				cout << "怪物死亡了\n";
				Sleep(2000);
				return 1;
			}
			cout << monster.monster_name << " 剩下 " << monster.monster_blood << "點血量\n\n\n";
			Sleep(500);
		}
	}
}
int main() {
	system("CLS");
	int user_number, level = 1, blood = 0, attack = 0, bag_size = 40, using_item = 0, using_item_number = 1000, using_bag_number = 1000, using_bag = 40, exp = 0, in_bag_value = 0, body_item = 0, body_item_number = 1000, money = 0;
	string command, itname;
	vector<Monster> monster_list;
	user_number = log_function();
	Character ch = ch.Character::character_function(user_number);
	level = ch.get_level();
	Map mp = mp.map_load(1);
	Monster monster;
	monster_list = monster.create_monster(mp.get_monster_level());
	Item it;
	vector<Item>item_list = it.open_bag(user_number, ch.character_name);
	Money my;
	money = my.get_money(user_number, ch.character_name);
	exp = get_exp(ch.character_name, user_number);
		while (1) {
			while (1) {
				if (ch.get_type() == 1) {
					blood = ch.get_level() * 30;
					attack = ch.get_level() * 1;
				}
				if (ch.get_type() == 2) {
					blood = ch.get_level() * 15;
					attack = ch.get_level() * 2;
				}
				if (ch.get_type() == 3) {
					blood = ch.get_level() * 10;
					attack = ch.get_level() * 3;
				}
				if (exp >= 5 * ch.character_level) {
					exp -= 5 * ch.character_level;
					cout << "升級啦" << endl;
					ch.character_level += 1;
				}
				else if (exp < 5 * ch.character_level)break;
			}
			system("CLS");
			mp = mp.map_load(mp.get_map_number());
			monster_list = monster.create_monster(mp.get_monster_level());
			command = call_command();
			if (command == "1") {//戰鬥
				monster = monster.choose_monster(monster_list, mp.get_monster_level());
				int fight_result = fight(monster, blood, attack, using_item, body_item);
				string choose;
				if (fight_result) {
					exp += monster.monster_level;
					money += 2 * monster.monster_level;
					it = it.get_item(user_number, ch.character_name);
					cout << "你獲得了" << monster.monster_level << "點經驗值" << endl;
					cout << "你獲得了" << 2 * monster.monster_level << "元"<< endl;
					cout << "掉落了" << it.item_name;
					while (1) {
						in_bag_value = 0;
						for (int i = 0; i < item_list.size(); i++) {
							if(i!=using_bag_number && i!=using_item_number && i!=body_item_number)in_bag_value += item_list[i].item_attack / 10;
						}
						if ((in_bag_value + it.item_attack / 10) <= using_bag) {
							item_list.push_back(it);
							break;
						}
						else {
							cout << "背包滿啦!!\n";
							string choose_bag;
							//system("CLS");
							it.print_bag(item_list, using_item_number, using_bag_number, body_item_number);
							cout << "(1)使用\n(2)刪除\n其他:放棄掉落物\n";
							cin >> choose_bag;
							if (choose_bag == "1") {
								cout << "請輸入要使用物品名稱 : ";
								cin >> itname;
								for (int i = 0; i < item_list.size(); i++) {
									if ((itname == item_list[i].item_name) && (item_list[i].item_type != ch.character_type && item_list[i].item_type != 0)) {
										cout << "職業錯誤!!" << endl;
										Sleep(1000);
									}
									if ((itname == item_list[i].item_name) && (item_list[i].item_type == 0 || item_list[i].item_type == ch.character_type) && item_list[i].item_number > 11) {
										//same with the attack function, add the item value to the character blood. 
										cout << "\n血量:" << body_item + blood;
										body_item = item_list[i].item_attack;
										cout << "->" << body_item + blood;
										body_item_number = i;
										Sleep(2000);
										break;
									}
									else if ((itname == item_list[i].item_name) && (item_list[i].item_type == 0 || item_list[i].item_type == ch.character_type)) {
										if (itname == "背包") {
											using_bag = 40;
											using_bag_number = i;
											cout << "\n當前背包空間為" << using_bag;
											Sleep(2000);
											break;
										}
										else if (itname == "中背包") {
											using_bag = 80;
											using_bag_number = i;
											cout << "\n當前背包空間為" << using_bag;
											Sleep(2000);
											break;
										}
										else if (itname == "大背包") {
											using_bag = 150;
											using_bag_number = i;
											cout << "\n當前背包空間為" << using_bag;
											Sleep(2000);
											break;
										}
										else {
											cout << "\n攻擊力:" << using_item + attack;
											using_item = item_list[i].item_attack;
											cout << "->" << using_item + attack;
											using_item_number = i;
											Sleep(2000);
											break;
										}
									}
								}
							}
							else if (choose_bag == "2") {
								item_list = it.delet_item(item_list);
							}
							else {
								break;
							}
						}
					}
					Sleep(2000);
				}
			}
			else if (command == "2") {
				string choose_bag;
				system("CLS");
				it.print_bag(item_list, using_item_number, using_bag_number, body_item_number);
				in_bag_value = 0;
				for (int i = 0; i < item_list.size(); i++) {
					if (i != using_bag_number && i != using_item_number && i != body_item_number)in_bag_value += item_list[i].item_attack / 10;
				}
				cout << "(1)使用\n(2)刪除\n其他:離開\n當前背包容量為:" << using_bag << "\n當前背包中物品占用容量為:"<< in_bag_value <<endl;
				cin >> choose_bag;
				if (choose_bag == "1") {
					cout << "請輸入要使用物品名稱 : ";
					cin >> itname;
					for (int i = 0; i < item_list.size(); i++) {
						if ((itname == item_list[i].item_name)&&(item_list[i].item_type != ch.character_type && item_list[i].item_type!=0)) {
							cout << "職業錯誤!!" << endl;
							Sleep(1000);
						}
						if ((itname == item_list[i].item_name) && (item_list[i].item_type == 0 || item_list[i].item_type == ch.character_type)&& item_list[i].item_number > 11) {
							//same with the attack function, add the item value to the character blood. 
							cout << "\n血量:" << body_item + blood;
							body_item = item_list[i].item_attack;
							cout << "->" << body_item + blood;
							body_item_number = i;
							Sleep(2000);
							break;
						}
						else if ((itname == item_list[i].item_name)&&(item_list[i].item_type == 0||item_list[i].item_type == ch.character_type)) {
							if (itname == "背包") {
								using_bag = 40;
								using_bag_number = i;
								cout << "\n當前背包空間為" << using_bag;
								Sleep(2000);
								break;
							}
							else if (itname == "中背包") {
								using_bag = 80;
								using_bag_number = i;
								cout << "\n當前背包空間為" << using_bag;
								Sleep(2000);
								break;
							}
							else if (itname == "大背包") {
								using_bag = 150;
								using_bag_number = i;
								cout << "\n當前背包空間為" << using_bag;
								Sleep(2000);
								break;
							}
							else {
								cout << "\n攻擊力:" << using_item + attack;
								using_item = item_list[i].item_attack;
								cout << "->" << using_item + attack;
								using_item_number = i;
								Sleep(2000);
								break;
							}
						}
					}

				}
				if (choose_bag == "2") {
					item_list = it.delet_item(item_list);
				}

			}
			else if (command == "3") {//open the store object function, not finish yet.<-finish
				vector<Item> store_list;
				string choose_store;
				int pay;
				for (int i = 0; i < 10; i++) {
					it = it.get_item(user_number, ch.character_name);
					store_list.push_back(it);
				}
				while (1) {
					system("CLS");
					for (int i = 0; i < store_list.size(); i++) {
						cout << store_list[i].item_name << " 價錢:" << store_list[i].item_attack << endl;
					}
					cout << "(1)購買\n(2)販賣\n其他:離開!!\n";
					cout << "你有:" << money << "元" << endl;
					cin >> choose_store;
					if (choose_store == "1") {
						cout << "請輸入商品名稱:";
						cin >> choose_store;
						for (int j = 0; j < store_list.size(); j++) {
							if (choose_store == store_list[j].item_name) {
								while (1) {
									in_bag_value = 0;
									for (int i = 0; i < item_list.size(); i++) {
										if (i != using_bag_number && i != using_item_number && i != body_item_number)in_bag_value += item_list[i].item_attack / 10;
									}
									if ((in_bag_value + it.item_attack / 10) <= using_bag) {
										if (money >= store_list[j].item_attack) {
											item_list.push_back(store_list[j]);
											money -= store_list[j].item_attack;
										}
										else cout << "金錢不足!!!" << endl;
										break;
									}
									else {
										cout << "背包滿啦!!\n";
										string choose_bag;
										//system("CLS");
										it.print_bag(item_list, using_item_number, using_bag_number, body_item_number);
										cout << "(1)使用\n(2)刪除\n其他:放棄購買\n";
										cin >> choose_bag;
										if (choose_bag == "1") {
											cout << "請輸入要使用物品名稱 : ";
											cin >> itname;
											for (int i = 0; i < item_list.size(); i++) {
												if ((itname == item_list[i].item_name) && (item_list[i].item_type != ch.character_type && item_list[i].item_type != 0)) {
													cout << "職業錯誤!!" << endl;
													Sleep(1000);
												}
												if ((itname == item_list[i].item_name) && (item_list[i].item_type == 0 || item_list[i].item_type == ch.character_type) && item_list[i].item_number > 11) {
													//same with the attack function, add the item value to the character blood. 
													cout << "\n血量:" << body_item + blood;
													body_item = item_list[i].item_attack;
													cout << "->" << body_item + blood;
													body_item_number = i;
													Sleep(2000);
													break;
												}
												else if ((itname == item_list[i].item_name) && (item_list[i].item_type == 0 || item_list[i].item_type == ch.character_type)) {
													if (itname == "背包") {
														using_bag = 40;
														using_bag_number = i;
														cout << "\n當前背包空間為" << using_bag;
														Sleep(2000);
														break;
													}
													else if (itname == "中背包") {
														using_bag = 80;
														using_bag_number = i;
														cout << "\n當前背包空間為" << using_bag;
														Sleep(2000);
														break;
													}
													else if (itname == "大背包") {
														using_bag = 150;
														using_bag_number = i;
														cout << "\n當前背包空間為" << using_bag;
														Sleep(2000);
														break;
													}
													else {
														cout << "\n攻擊力:" << using_item + attack;
														using_item = item_list[i].item_attack;
														cout << "->" << using_item + attack;
														using_item_number = i;
														Sleep(2000);
														break;
													}
												}
											}
										}
										else if (choose_bag == "2") {
											item_list = it.delet_item(item_list);
										}
										else {
											break;
										}
									}
								}
								break;
							}
						}
					}
					else if (choose_store == "2") {
						system("CLS");
						it.print_bag(item_list, using_item_number, using_bag_number, body_item_number);
						item_list = it.delet_item(item_list);
						pay = rand() % 10;
						money += pay;
						cout << "你獲得了:" << pay << "元" << endl;
					}
					else break;
				}

			}
			else if (command == "4") {
				system("CLS");
				cout << "角色名稱:" <<ch.character_name << endl;
				cout << "等級:" << ch.character_level << endl;
				if (ch.character_type == 1)cout << "種族:獸人\n";
				if (ch.character_type == 2)cout << "種族:人類\n";
				if (ch.character_type == 3)cout << "種族:精靈\n";
				cout << "血量:" << blood << endl << "攻擊力:" << attack+using_item <<endl;
				cout << "金錢:" << money << endl;
				if(using_item_number!=1000)cout << "裝備中武器:" << item_list[using_item_number].item_name << endl;
				if(body_item_number!= 1000)cout << "裝備中防具:" << item_list[body_item_number].item_name << endl;
				system("pause");
			}
			else if (command == "5")break;
			else {
				mp = mp.map_function(mp.get_map_number());//用來移動
				monster_list = monster.create_monster(mp.get_monster_level());
			}
		}
		set_exp(ch.character_name, user_number, exp);
		my.save_money(user_number, ch.character_name, money);
	ch.set_level(ch.character_level);
	ch.character_save(ch);
	it.save_item(item_list, ch.character_name, user_number);
	system("pause");
	return 0;
}