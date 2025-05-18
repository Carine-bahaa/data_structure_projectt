#include "ClassSessions.h"

ClassSessions::ClassSessions(int classID, string className, string coachName, int coachID, string classScheduleDate)
{
	this->classID = classID;
	this->className = className;
	this->assignedCoachName=coachName;
	this->assignedCoachID=coachID;
	this->classScheduleDate = classScheduleDate;
}

bool ClassSessions::isFull()
{
	return capacity == joined.size();
}

void ClassSessions::cancel(int id, bool isVIP)
{
	for (auto it = joined.begin(); it != joined.end(); it++)
	{
		if (id == *it)
		{
			joined.erase(id);
			if (isVIP && !VIPwaitlist.empty())
			{
				joined.insert(id);
				VIPwaitlist.pop();
			}
			else if (!waitlist.empty())
			{
				joined.insert(id);
				waitlist.pop();
			}
			break;
		}
		else
		{
			cout << "This member isn't joined in this class\n";
		}
	}
}

void ClassSessions::joinClass(int id, bool isVIP)
{
	if (!isFull()) {
		joined.insert(id);
		cout << "You have successfully joined the class " << endl;
	}

	else {
		if (isVIP) {

			VIPwaitlist.push(id);
		}
		else {
			waitlist.push(id);
		}


		cout << "The class is full. You have been added to the waitlist." << endl;
	}

}

void ClassSessions::setClassSchedule(string date)
{
	classScheduleDate = date;
}

string ClassSessions::getclassName()
{
	return className;
}

string ClassSessions::getClassSchedule()
{
	return classScheduleDate;
}
