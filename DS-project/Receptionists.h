#pragma once
#include<string>
#include<iostream>
#include "Members.h"
#include "Subscription.h"

using namespace std;
class Receptionists
{
	const int rID = 100;
	const string rPassword = "Rec_100";
	unordered_map<int, Members>* members;
public:
	int getID();
	string getPassword();
	void receptionistMenu();
	void retrieve(int, unordered_map<int, Members>* members);
	void store(unordered_map<int, Members>* members);
};

