#include<iostream>
#include "Account.h"
#include "Receptionists.h"
#include "Manager.h"
#include"SystemManager.h"
using namespace std;

void Account::login(unordered_map<int, Members>* members, unordered_map<int, Coaches>* coaches, int id, string password, string role)
{
    if (role == "Member")
    {
        for (auto it = (*members).begin(); it != (*members).end(); it++)
        {
            if (it->first == id && it->second.getPassword() == password)
            {
				//renewalNotification
                if (it->second.getRenewalDate().renewalNotification())
                {
                    cout << "Your subscription ends soon!!!\n";
                }
                else
                {
					cout << "Your subscription is still valid\n";
                }
                it->second.memberMenu();
                break;
            }
            else
            {
                cout << "Invalid ID or Password";
            }
        }
    }
    else if (role == "Staff")
    {
        Manager m;
        Receptionists r;
        bool found = false;
        if (id == m.getID() && password == m.getPassword())
        {
            m.managerMenu();
            found = true;
        }
        else if (id == r.getID() && password == r.getPassword())
        {
            r.receptionistMenu();
            found = true;
        }
        else if (!found)
        {
            for (auto it = (*coaches).begin(); it != (*coaches).end(); it++)
            {
                if (it->first == id && it->second.getPassword() == password)
                {
                    it->second.coachMenu();
                    found = true;
                    break;
                }
            }
        }
       if (!found)
       {
            cout << "Invalid username or password";
       }
    }
}
bool Account::validation(int, string)
{


    return false;
}
