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

void Coaches::setAssignedClass(pair<int, ClassSessions> assignedClass)
{
    assignedclassSessions.insert(assignedClass);
}

void Coaches::retrieve(int id, unordered_map<int, Members>& members)
{
    for (auto it = members.begin(); it != members.end(); it++)
    {
        if (it->first == id)
        {
            cout << "Name: " << it->second.getName();
            cout << "Date of birth: " << it->second.getDOB();
            cout << "Renewal date: " << it->second.getRenewalDate();
            cout << "Joined classes: " << endl;
            for (auto& joinedClass : it->second.getJoinedClasses()) {
                cout << "\n  Class ID: " << joinedClass.classID
                    << ", Name: " << joinedClass.name
                    << ", Schedule Date: " << joinedClass.classScheduleDate;
            }
            
            break;
        }
    }
}
string Coaches::getPassword()
{
    return password;
}

int Coaches::getCoachID()
{
    return id;
}

void Coaches::reSchedulesEachMonth(char choice)
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
        // Parse session date for comparison 
        int day, month, year;
        char dash1, dash2;
        istringstream iss(it->second.getClassSchedule());
        iss >> day >> dash1 >> month >> dash2 >> year;


        // Only reschedule if the session is in the current month
        if (month == nowMonth && year == nowYear) {

           
            if (choice == 'y' ) {
                cout << "Enter new date (dd-mm-yyyy): ";
                string newDate;
                cin >> newDate;
                it->second.setClassSchedule(newDate);
                continue; 
            }
            // If not rescheduled, check if 7 or fewer days left
            tm sessionDate = {};
            sessionDate.tm_year = year - 1900;
            sessionDate.tm_mon = month - 1;
            sessionDate.tm_mday = day;
            sessionDate.tm_hour = 0; sessionDate.tm_min = 0; sessionDate.tm_sec = 0;
            time_t session_time = mktime(&sessionDate);

            double secondsDiff = difftime(session_time, today_time);
            int daysDiff = static_cast<int>(secondsDiff / (60 * 60 * 24));

            if (daysDiff > 0 && daysDiff <= 7) {
                // Auto-reschedule to next month
                int newMonth = month + 1;
                int newYear = year;
                if (newMonth > 12) {
                    newMonth = 1;
                    newYear++;
                }
                string newDate = (day < 10 ? "0" : "") + to_string(day) + "-" +
                    (newMonth < 10 ? "0" : "") + to_string(newMonth) + "-" +
                    to_string(newYear);
                cout << "Class session \"" << it->first << "\" is being automatically rescheduled to " << newDate << ".\n";
                it->second.setClassSchedule(newDate);
            }
        
        }
    }
}

void Coaches::viewAssignedClasses()
{
    for (auto it = assignedclassSessions.begin(); it != assignedclassSessions.end(); it++) {
        cout << "Class Name: " << it->second.getclassName() << "   " << "Class Schedule: " << it->second.getClassSchedule();
    }

}

void Coaches::coachMenu(unordered_map<int, Members>& members)
{
    int menuchoice;
    cout << "Coach Menu:" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "1-Retrive a Member's ID \n 2- Reschedule classes\n 3- View assigned classes\n 4- Exit " << endl;
    cin >> menuchoice;
    do {

        switch (menuchoice)
        {
        case 1:
            int memberId;
            cout << "Enter the Member ID :";
            cin >> memberId;
            retrieve(memberId, members);
            break;
        case 2:
            char choice = 'y';
            reSchedulesEachMonth(choice);
            break;
        case 3:
            viewAssignedClasses();
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (menuchoice != 4);

}


