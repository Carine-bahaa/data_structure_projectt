#include "Coaches.h"
Time t;
int nowDay = t.getDay();    // Get the current day
int nowMonth = t.getMonth(); // Get the current month
int nowYear = t.getYear();

Coaches::Coaches(string name, int id, string password)
{
	this->id = id;
	this->name = name;
	this->password = password;
}

Coaches::Coaches()
{
	this->name = "";
	this->id = 0;
}

void Coaches::setCoachName(string name)
{
	this->name = name;
}

void Coaches::setCoachID(int id)
{
	this->id = id;
}

void Coaches::retrieve(int id, unordered_map<int, Members>* members)
{
	for (auto it = members->begin(); it != members->end(); it++)
	{
		if (it->first == id)
		{
			cout << "Name: " << it->second.getName();
			cout << "Date of birth: " << it->second.getDOB();
			cout << "Renewal date: " << it->second.getRenewalDate();
			cout << "Joined classes: "<< it->second.getJoinedClasses();
			break;
		}
	}
}
string Coaches::getPassword()
{
    return password;
}

void Coaches::reSchedulesEachMonth()
{
    // Today's date
    tm today = {};
    today.tm_year = nowYear - 1900;
    today.tm_mon = nowMonth - 1;
    today.tm_mday = nowDay;
    today.tm_hour = 0; today.tm_min = 0; today.tm_sec = 0;
    time_t today_time = mktime(&today);

    // Loop through all class sessions and reschedule them for the next month
    for (auto it = assignedclassSessions.begin(); it != assignedclassSessions.end(); it++) 
    {
        // Parse session date for comparision 
        int day, month, year;
        char dash1, dash2;
        istringstream iss(it->second.getClassSchedule());
        iss >> day >> dash1 >> month >> dash2 >> year;


        // Only reschedule if the session is in the current month
        if (month == nowMonth && year == nowYear) {
           
            int newMonth = month + 1;
            int newYear = year;
            if (newMonth > 12) {
                newMonth = 1;
                newYear++;
            }
            // Format new date
            string newDate =(day < 10 ? "0" : "") + to_string(day) + "-" + (newMonth < 10 ? "0" : "") + to_string(newMonth) + "-" + to_string(newYear);
            it->second.setClassSchedule(newDate);
                
        }// if there are still 7 days before the schedule ends, let the coach choose to reschedule it by hand
    else
    {
        // Parse the session date into a tm struct
        tm sessionDate = {};
        sessionDate.tm_year = year - 1900;
        sessionDate.tm_mon = month - 1;
        sessionDate.tm_mday = day;
        sessionDate.tm_hour = 0; sessionDate.tm_min = 0; sessionDate.tm_sec = 0;
        time_t session_time = mktime(&sessionDate);

		//diffrence between today and the session date
        double secondsDiff = difftime(session_time, today_time);
        int daysDiff = static_cast<int>(secondsDiff / (60 * 60 * 24));

        if (daysDiff > 0 && daysDiff <= 7) {
            cout << "Class session  \"" << it->first << "\"  rescheduling is within 7 days.\n";
            cout << "Do you want to reschedule it manually? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                cout << "Enter new date (dd-mm-yyyy): ";
                string newDate;
                cin >> newDate;
                it->second.setClassSchedule(newDate);
            }
        }
    }
    }
}

