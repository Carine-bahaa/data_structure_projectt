#include "Receptionists.h"
#include "Members.h"
Time t;
int nowDay = t.getDay();    // Get the current day
int nowMonth = t.getMonth(); // Get the current month
int nowYear = t.getYear();
int Receptionists::getID()
{
	return rID;
}

string Receptionists::getPassword()
{
	return rPassword;
}

void Receptionists::retrieve(int id, unordered_map<int, Members>& members)
{
	for (auto it = members.begin(); it != members.end(); it++)
	{
		if (it->first == id)
		{
			cout << "Name: " << it->second.getName();
			cout << "Date of birth: " << it->second.getDOB();
			cout << "Renewal date: " << it->second.getRenewalDate();
			cout << "Joined classes: ";
			for (int i = 0; i < it->second.getJoinedClasses().size(); i++)
			{
				cout << "Class " << i + 1 << ": " << it->second.getJoinedClasses().at(i).name;
			}
			break;
		}
	}
}

void Receptionists::store(unordered_map<int, Members>& members)
{
	string name;
	string password;
	string dob;
	bool VIPstatus;
	char vipChoice;
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
	if (vipChoice == 'y' || vipChoice == 'Y')
	{
		VIPstatus = true;
	}
	else if (vipChoice == 'n' || vipChoice == 'N')
	{
		VIPstatus = false;
	}
	else
	{
		cout << "Invalid choice. Defaulting to non-VIP status.\n";
		VIPstatus = false;
	}
	if (VIPstatus)
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
	Members newMember(name, ID, password, dob, sub, VIPstatus);
	members.insert(make_pair(ID, newMember));
}

void Receptionists::receptionistMenu(unordered_map<int, Members>& members)
{
	int choice;
	cout << "Receptionist menu:" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "1- Retrive a Member's data\n 2- Store a New Member's data \ 3-Exit";
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
		default:
			cout << "Invalid choice. Please try again.\n";
		}
	} while (choice != 3);

}
