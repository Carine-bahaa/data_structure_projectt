#pragma once
#include<iostream>
#include "Account.h"
#include "Receptionists.h"
#include "Manager.h"
using namespace std;
class SystemManager
{
public:
	unordered_map<int, Members> members;
	unordered_map<int, Coaches> coaches;
};

