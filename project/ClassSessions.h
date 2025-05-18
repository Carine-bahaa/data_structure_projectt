#pragma once
#include<iostream>
#include<string>
#include<unordered_set>
#include<queue>
#include<string>
#include"Members.h"
#include "Coaches.h"

using namespace std;
class ClassSessions
{
	const int capacity = 30;
	int classID;
	string className;
	int assignedCoachID;
	string assignedCoachName;
	queue<int> waitlist;
	unordered_set<int> joined;
	string classScheduleDate;
	queue<int> VIPwaitlist;


public:
	ClassSessions();
	ClassSessions(int classID, string className, string coachName, int coachID, string classScheduleDate);
	bool isFull();
	void cancel(int, bool);
	void joinClass(int, bool);
	//class schedule
	void setClassSchedule(string date);
	string getclassName();
	string getClassSchedule();
};