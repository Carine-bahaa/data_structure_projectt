#pragma once
#include<string>
#include<iostream>
#include<unordered_map>
#include "Subscription.h"

using namespace std;
class Members;
class Receptionists
{
	const int rID = 100;
	const string rPassword = "Rec_100";
public:
	int getID();
	string getPassword();
	void receptionistMenu(unordered_map<int, Members>& members);
	void retrieve(int, unordered_map<int, Members>& members);
	void store(unordered_map<int, Members>& members);
};

