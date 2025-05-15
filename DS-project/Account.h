#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include"Members.h"
#include"Coaches.h"
#include"SystemManager.h"

using namespace std;
class Account
{
	int id;
	string password;
	unordered_map<int, Members>* members;
	unordered_map<int, Coaches>* coaches;
	
public:
	void login(unordered_map<int, Members>* members, unordered_map<int, Coaches>* coaches, int, string, string);
	bool validation(int, string);
};

