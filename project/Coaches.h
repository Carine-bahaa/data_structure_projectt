#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include <sstream>
#include "Time.h"
#include "ClassSessions.h"
#include "Members.h"

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
	void setAssignedClass(pair<int, ClassSessions> assignedClass);

	string getPassword();
	int getCoachID();

	void retrieve(int, unordered_map<int, Members>& members);
	void coachMenu(unordered_map<int, Members>& members);
	void reSchedulesEachMonth(char );
	void viewAssignedClasses();

};

