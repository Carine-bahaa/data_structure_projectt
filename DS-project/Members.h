#pragma once
#include<iostream>
#include<string>
#include"Account.h"
#include"Subscription.h"
#include"ClassSessions.h"
using namespace std;
class Members
{
	int ID;
	string password, name, dateOfBirth;
	Subscription membersSubscription;

public:
	Members(string name, int id, string password, string dateOfBirth, Subscription);
	string getPassword();
	int getID();
	string getName();
	string getDOB();
	Subscription getRenewalDate();
	void setSubscription(Subscription);
	ClassSessions Members::getJoinedClasses()
	void memberMenu();
};

