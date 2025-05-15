#pragma once
#include<iostream>
#include<string>
#include<unordered_set>
#include<queue>
#include<string>
#include "Coaches.h"
#include"Members.h"

using namespace std;

class ClassSessions
{
	const int capacity = 30;
	int classID;
	string className;
	queue<int> waitlist;
	unordered_set<int> joined;
	Coaches assignedCoach;
	string classScheduleDate;


public:
	ClassSessions(int classID, string className, string coachName, int coachID);
	bool isFull(); 
	void cancel(int);
	void joinClass(int);
	//class schedule
	void setClassSchedule(string date);
	string getClassSchedule();
};