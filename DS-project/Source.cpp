#include<iostream>
#include<string>
#include<unordered_map>
#include"Members.h"
#include"Coaches.h"
#include"Account.h"
using namespace std;

unordered_map<int, Members> members;
unordered_map<int, Coaches> coaches;
void loadMembers(int& memberCount);			//name, id, password, date of birth, subscription
void loadMembersData(int memberCount);		//workout history (class sessions/paddle courts), joined classes, waitlist
void loadCoachData();						//coach name, id, password, assigned class
void loadClassSessionsData();				//class name, class id, assigned coach, waitlist, joined members
void paddleData();
void loadSubscriptionData();


int main()
{
	int memberCount = 0;


	return 0;
}