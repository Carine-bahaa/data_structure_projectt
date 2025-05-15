#pragma once
#include<string>
#include<iostream>
#include "Members.h"
#include "ClassSessions.h"
using namespace std;
class Manager
{
	const int ID = 111;
	const string password = "Man_111";
public:
	int getID();
	string getPassword();
	void retrieve(int, unordered_map<int, Members>* members);
	void store(unordered_map<int, Members>* members);
	void managerMenu();
	//assigning classes to coaches
	void assignClassToCoach(unordered_map<int, ClassSessions>* classSession);
};