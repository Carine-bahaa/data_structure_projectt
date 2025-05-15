#include "Members.h"

Members::Members(string name, int id, string password, string dateOfBirth, Subscription s)
{
    this->name = name;
    this->ID = id;
    this->password = password;
    this->dateOfBirth = dateOfBirth;
    this->membersSubscription = s;
}

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

Subscription Members::getRenewalDate()
{
    return Subscription();
}

ClassSessions Members::getJoinedClasses()
{
	return ClassSessions();
}

void Members::setSubscription(Subscription memS)
{
    membersSubscription = memS;
}

void Members::memberMenu()
{
    cout << "1- Subscribe to training programs.\n2- Book Padel courts.\n3- Track workout histories.\"n";
}


