#pragma once
#include<iostream>
#include<string>
#include"Account.h"
#include"Subscription.h"
#include"ClassSessions.h"
#include <algorithm>
#include <stack>
#include <sstream>
#include <Time.h>
using namespace std;
struct JoinedClassInfo {
	int classID;
	string classScheduleDate;
};
class Members
{
	int ID;
	string password, name, dateOfBirth;
	Subscription membersSubscription;
	vector<JoinedClassInfo> joinedClasses;
	bool isVIP ;
	

public:
	Members(string name, int id, string password, string dateOfBirth, Subscription s, bool isVIP = false);
	string getPassword();
	int getID();
	string getName();
	string getDOB();
	string getRenewalDate();
	bool getVIP();
	void setVIP(bool);
	void setSubscription(Subscription); 
	vector<JoinedClassInfo> getJoinedClasses();
	time_t parseDate(const string& dateStr)
    void WorkoutHistory(const unordered_map<int, ClassSessions>& allClasses);
	void memberMenu(unordered_map<int, ClassSessions>& allClasses, Paddle& paddle);

};

