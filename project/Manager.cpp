#include "Manager.h"

int Manager::getID()
{
	return ID;
}

string Manager::getPassword()
{
	return password;
}

void Manager::retrieve(int id, unordered_map<int, Members>& members)
{
	for (auto it = members.begin(); it != members.end(); it++)
	{
		if (it->first == id)
		{
			cout << "Name: " << it->second.getName();
			cout << "Date of birth: " << it->second.getDOB();
			cout << "Renewal date: "<< it->second.getRenewalDate();
			cout << "Joined classes: ";
			for (int i = 0; i < it->second.getJoinedClasses().size(); i++)
			{
				cout << "Class " << i + 1 << ": " << it->second.getJoinedClasses().at(i).name;
			}
			break;
		}
	}
}

void Manager::store(unordered_map<int, Members>& members)
{
	string name;
	string password;
	string dob;
	Subscription sub;
	char vipChoice;
	bool isVIP;
	int ID;
	int option;
	float price;
	int durationInMonths;

	cout << "Enter your name: ";
	cin >> name;
	cout << "Enter a password: ";
	cin >> password;
	cout << "Enter your date of birth: ";
	cin >> dob;
	cout << "Do you want to be a VIP Memebr ? (y/n) ";
	cin >> vipChoice;
	cout << "Enter subscription period: ";
	if (isVIP)
	{
		cout << "Subscription options:\n---------------- "
			<< "1) 1 month --->  1800 LE\n"
			<< "2) 3 months ---> 7200 LE\n"
			<< "3) 6 months ---> 9360 LE\n"
			<< "4) 1 year ---> 12816 LE\n";
		cin >> option;
		switch (option)
		{
		case 1:
			price = 1800;
			durationInMonths = 1;
			break;
		case 2:
			price = 7200;
			durationInMonths = 3;
			break;
		case 3:
			price = 9360;
			durationInMonths = 6;
			break;
		case 4:
			price = 12816;
			durationInMonths = 12;
			break;
		default:
			cout << "Invalid option.\n";
		}
	}
	else
	{
		cout << "Subscription options:\n---------------- "
			<< "1) 1 month ---> 1500 LE\n"
			<< "2) 3 months ---> 6000 LE\n"
			<< "3) 6 months ---> 7800 LE\n"
			<< "4) 1 year ---> 10680 LE\n";
		cin >> option;
		switch (option)
		{
		case 1:
			price = 1500;
			durationInMonths = 1;
			break;
		case 2:
			price = 6000;
			durationInMonths = 3;
			break;
		case 3:
			price = 7800;
			durationInMonths = 6;
			break;
		case 4:
			price = 10680;
			durationInMonths = 12;
			break;
		default:
			cout << "Invalid option.\n";
		}
	}

	cout << "Enter start date DD-MM-YYYY: ";
	string startDate;
	cin >> startDate;
	string d = startDate.substr(0, 2);
	string m = to_string((stoi(startDate.substr(3, 5)) + durationInMonths) % 12);
	string y = (stoi(startDate.substr(3, 5)) + durationInMonths) % 12 == 0 ? startDate.substr(6) : to_string(stoi(startDate.substr(6)) + 1);
	string endDate = d + "-" + m + "-" + y;
	Subscription sub(price, durationInMonths, startDate, endDate);
	ID = members.size() + 1;
	cout << "Your ID is " << ID;
	Members newMember(name, ID, password, dob, sub, isVIP);
	members.insert(make_pair(ID, newMember));
}

void Manager::managerMenu(unordered_map<int, Members>& members , unordered_map<int, ClassSessions>& classSession , unordered_map<int, Coaches>& coaches)
{
	int choice;
	cout << "Manager menu:" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "1- Retrive a Member's data\n 2- Store a New Member's data \ 3-Make a new Class and assign it to a Coach\n 4- Exit";
	cin >> choice;
	do {

		switch (choice)
		{
		case 1:
			int memberId;
			cout << "Enter the Member ID :";
			cin >> memberId;
			retrieve(memberId, members);
			break;
		case 2:
			store(members);
			break;
		case 3:
			assignClassToCoach(classSession,coaches);
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
		}
	} while (choice != 3);

}

void Manager::assignClassToCoach(unordered_map<int, ClassSessions>& classSession , unordered_map<int, Coaches>& coaches)
{
	int classID;
	string className;
	string coachName;
	int coachID;
	string classScheduleDate;
	cout << "Enter the class ID: ";
	cin >> classID;
	cout << "Enter the class name: ";
	cin >> className;
	cout << "Assign a coach for this class by Entering their name: ";
	cin >> coachName;
	cout << "Enter the coach ID: ";
	cin >> coachID;
	cout << "Enter class schedule date (DD-MM-YYYY) :";
	cin >> classScheduleDate;
	ClassSessions newClassToCoach(classID, className, coachName, coachID, classScheduleDate);
	for (auto it = coaches.begin(); it != coaches.end(); it++)
	{
		if (it->second.getCoachID() == coachID)
		{
			it->second.setAssignedClass(make_pair(classID, newClassToCoach));
		}
	}
	classSession.insert(make_pair(classID, newClassToCoach));

}

