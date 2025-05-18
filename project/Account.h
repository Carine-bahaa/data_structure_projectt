#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include"Members.h"
#include"Coaches.h"
#include "Manager.h"
#include"Receptionists.h"
#include "ClassSessions.h"
#include "Paddle.h"

using namespace std;
class Account
{
	int id;
	string password;
public:
	void login(unordered_map<int, Members>& members, unordered_map<int, Coaches>& coaches, unordered_map<int, ClassSessions>& allClasses, Paddle& paddle,int id, string pass, int role);
	bool validation(int, string);
};

