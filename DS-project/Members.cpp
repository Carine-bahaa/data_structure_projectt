#include "Members.h"
Time t;
int nowDay = t.getDay();    // Get the current day
int nowMonth = t.getMonth(); // Get the current month
int nowYear = t.getYear(); // Get the current year

Members::Members(string name, int id, string password, string dateOfBirth, Subscription s , bool isVIP)
{
    this->name = name;
    this->ID = id;
    this->password = password;
    this->dateOfBirth = dateOfBirth;
    this->membersSubscription = s;
}

// Getters
string Members::getPassword()
{
    return password;
}

int Members::getID()
{
    return ID;
}

string Members::getName()
{
    return name;
}

string Members::getDOB()
{
    return dateOfBirth;
}

string Members::getRenewalDate()
{
    return membersSubscription.getEndDate();
}

bool Members::getVIP()
{
    return isVIP;
}

void Members::setVIP(bool vip)
{
    isVIP = vip;
}


vector<JoinedClassInfo> Members::getJoinedClasses()
{
    return joinedClasses;
}

time_t Members::parseDate(const string& dateStr) {
    int day, month, year;
    char dash1, dash2;
    istringstream iss(dateStr);
    iss >> day >> dash1 >> month >> dash2 >> year;
    tm date = {};
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;
    date.tm_hour = 0; date.tm_min = 0; date.tm_sec = 0;
    return mktime(&date);
}

void Members::WorkoutHistory(const unordered_map<int, ClassSessions>& allClasses)
{
    //Sort joinedClasses from oldest to newest
     vector<JoinedClassInfo> sortedClasses = joinedClasses;
      sort(sortedClasses.begin(), sortedClasses.end(), [](const JoinedClassInfo& a, const JoinedClassInfo& b) {
        return parseDate(a.classScheduleDate) < parseDate(b.classScheduleDate);
        });

    //Push sorted classes onto a stack 
     stack<JoinedClassInfo> workoutStack;
    for (const auto& jc : sortedClasses) {
        workoutStack.push(jc);
    }

    //  Display from newest to oldest
    if (workoutStack.empty()) {
        cout << "No workout history.\n";
        return;
    }
    cout << "Workout history :\n";
    while (!workoutStack.empty()) {
        const auto& jc = workoutStack.top();
        auto it = allClasses.find(jc.classID);
        string className = (it != allClasses.end()) ? it->second.getClassName() : "Unknown";
        cout << "Class: " << className << ", Date: " << jc.classScheduleDate << endl;
        workoutStack.pop();
    }
    

}

void Members::setSubscription(Subscription memS)
{
    membersSubscription = memS;
}

void Members::memberMenu(unordered_map<int, ClassSessions>& allClasses , Paddle& paddle)
{
    int choice;
    do{
    cout << "1- View Subscription.\n 2- Book a Padel Court.\n 3- Cancle Padel Court.\n 4- Track Workout History.\n 5- Join class.\n 6- Cancle class.\n 7- Exit";
    cin >> choice;
    switch (choice) {
    case 1:
        membersSubscription.displayDetails();
        break;
    case 2:
		paddle.bookingCourt(paddle.locations ,this-> isVIP);
        break;
    case 3:
        int BookingID;
        cout << "Enter your Booking ID:";
        cin >> BookingID;
        paddle.cancelBookingByID(BookingID, this->isVIP);
        break;
    case 4:
		WorkoutHistory(allClasses);

        break;
	case 5:
        cout << "Available Classes:\n";
		for (auto it = allClasses.begin(); it != allClasses.end(); it++)
		{
			cout << "Class ID: " << it->first << ", Class Name: " << it->second.getClassName() << endl;
		}
		int classID;
		cout << "Enter the class ID you want to join: ";
		cin >> classID;
      
        auto it = allClasses.find(classID);
        if (it == allClasses.end()) {
            cout << "Invalid class ID." << endl;
            break;
        }
       string classDate = it->second.getClassSchedule();

        // Check if already joined this class on this date
        bool alreadyJoined = false;
        for (const auto& jc : joinedClasses) {
            if (jc.classID == classID && jc.classScheduleDate == classDate) {
                alreadyJoined = true;
                break;
            }
        }
        if (alreadyJoined) {
            cout << "You have already joined this class ." << endl;
            break;
        }
        it->second.joinClass(this->ID , this->isVIP);
        joinedClasses.push_back({ classID, classDate });
        break;
    case 6:
        cout << "Your joined classes:\n";
        for (const auto& jc : joinedClasses) {
            cout << "Class ID: " << jc.classID << ", Date: " << jc.classScheduleDate << endl;
        }

        cout << "Enter the Class ID to cancel: ";
        int cancelClassID;
        cin >> cancelClassID;
        cout << "Enter the class date (dd-mm-yyyy): ";
        string cancelDate;
        cin >> cancelDate;

        
        auto it = allClasses.find(cancelClassID);
        if (it == allClasses.end()) {
            cout << "Invalid class ID." << endl;
            break;
        }

        bool found = false;
        for (auto jc = joinedClasses.begin(); jc != joinedClasses.end(); ++jc) {
            if (jc->classID == cancelClassID && jc->classScheduleDate == cancelDate) {
				it->second.cancel(this->ID, this->isVIP);
                joinedClasses.erase(jc);
                found = true;
                cout << "Class canceled successfully.\n"
                break;
            }
        }
        if (!found) {
            cout << "You have not joined this class on the specified date.\n";
            break;
        }
        break;
	default:
        break;
    }
	} while (choice != 7 );
}


