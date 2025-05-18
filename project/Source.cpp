#include<iostream>
#include<string>
#include<unordered_map>
#include"Members.h"
#include"Coaches.h"
#include"Account.h"
using namespace std;

unordered_map<int, Members> members;
unordered_map<int, Coaches> coaches;
unordered_map<int, ClassSessions> allClasses;
Paddle paddle;
void loadMembers(int& memberCount);			//name, id, password, date of birth, subscription
void loadMembersData(int memberCount);		//workout history (class sessions/paddle courts), joined classes, waitlist
void loadCoachData();						//coach name, id, password, assigned class
void loadClassSessionsData();				//class name, class id, assigned coach, waitlist, joined members
void paddleData();
void loadSubscriptionData();


int main()
{
    int memberCount = 0;
    Account acc;
    while (true)
    {
        cout << "\n==== GYM AND PADDLE SYSTEM LOGIN ====\n";
        cout << "Are you a Member or Staff? (1: Member, 2: Staff, 3: Exit): ";
        int role;
        cin >> role;
        if (role == 3) break;

        int id;
        string pass;
        cout << "Enter Member ID: ";
        cin >> id;
        cout << "Enter password: ";
        cin >> pass;
        acc.login(members, coaches,allClasses,paddle,id, pass, role);
    }

    return 0;
}