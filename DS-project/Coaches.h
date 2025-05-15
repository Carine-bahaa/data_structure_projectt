#pragma once
#include<iostream>
#include<string>
#include "Members.h"
#include "Time.h"
using namespace std;
class Coaches
{
	int id;
	string password;
	string name;
	//assigned classes
    unordered_map<int, ClassSessions> assignedclassSessions;
public:
	Coaches(string name, int id, string password);
	Coaches();
	void setCoachName(string name);
	void setCoachID(int id);
	void retrieve(int, unordered_map<int, Members>* members);
	string getPassword();
	void coachMenu();
	void reSchedulesEachMonth();
	
};

