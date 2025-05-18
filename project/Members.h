#pragma once
#include<iostream>
#include<string>
#include"Account.h"
#include"Subscription.h"
#include <algorithm>
#include <stack>
#include <sstream>
#include <Time.h>
#include "Paddle.h"
using namespace std;
class ClassSessions;
struct JoinedClassInfo {
	int classID;
	string name;
	string classScheduleDate;
};
class Members
{
	int ID;
	string password, name, dateOfBirth;
	Subscription membersSubscription;
	vector<JoinedClassInfo> joinedClasses;
	bool isVIP;


public:
	
	Members(string name, int id, string password, string dateOfBirth, Subscription s, bool isVIP);
	string getPassword();
	int getID();
	string getName();
	string getDOB();
	string getRenewalDate();
	bool getVIP();
	void setVIP(bool);
	Subscription getSubscription();
	void setSubscription(Subscription);
	vector<JoinedClassInfo> getJoinedClasses();
	static time_t parseDate(const string& dateStr);
	void WorkoutHistory( unordered_map<int, ClassSessions>& allClasses);
	void memberMenu(unordered_map<int, ClassSessions>& allClasses, Paddle& paddle);
	//howa ehh lazmet el parameters dol? msh elmafrood el member menu yeb2a leha options en el member yeshoof el workout history wel kalam da?
	//asdy kol member yeb2a leeh el all classes beta3to w mateb2ash unordered map passed by reference
	//w 7etet el paddle msh fahmaha
};

