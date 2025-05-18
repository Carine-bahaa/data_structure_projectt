#include "Account.h"

void Account::login(unordered_map<int, Members>& members, unordered_map<int, Coaches>& coaches, unordered_map<int, ClassSessions>& allClasses, Paddle& paddle, int id, string pass, int role)
{
    if (role == 1)
    {
        for (auto it = members.begin(); it != members.end(); it++)
        {
            if (it->first == id && it->second.getPassword() == password)
            {
                Members& m = it->second;
                if (it->second.getSubscription().renewalNotification())
                {
                    cout << "Your subscription ends soon!!!\n";
                }
                else
                {
                    cout << "Your subscription is still valid\n";
                }
				it->second.memberMenu(allClasses, paddle);
                break;
            }
            else
            {
                cout << "Invalid ID or Password";
            }
        }
    }
    else if (role == 2)
    {
        Manager m;
        Receptionists r;
        bool found = false;
        if (id == m.getID() && password == m.getPassword())
        {
            m.managerMenu(members,allClasses);
            
            found = true;
        }
        else if (id == r.getID() && password == r.getPassword())
        {
            r.receptionistMenu(members);
            found = true;
        }
        else if (!found)
        {
            for (auto it = coaches.begin(); it != coaches.end(); it++)
            {
                if (it->first == id && it->second.getPassword() == password)
                {
                    it->second.coachMenu(members);
                    
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
