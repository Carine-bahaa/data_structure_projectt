#include "Subscription.h"
Time t;
int nowDay = t.getDay();    // Get the current day
int nowMonth = t.getMonth(); // Get the current month
int nowYear = t.getYear(); // Get the current year

Subscription::Subscription(double price, int duration, string start, string end)
    : price(price), duration(duration), startDate(start), endDate(end) {}

Subscription::Subscription()
{
}

// Getters
string Subscription::getSubscriptionType() 
{
    return subscriptionType;
}
double Subscription::getPrice() 
{ 
    return price; 
}
int Subscription::getDuration() 
{
    return duration; 
}
string Subscription::getStartDate()
{
    return startDate; 
}
string Subscription::getEndDate() 
{ 
    return endDate; 
}

// Setters
void Subscription::setSubscriptionType(string type)
{ 
    subscriptionType = type; 
}
void Subscription::setPrice(double price) 
{
    this->price = price; 
}
void Subscription::setDuration(int duration)
{
    this->duration = duration;
}
void Subscription::setStartDate(string start)
{ 
  
        startDate = start;
  
}
void Subscription::setEndDate(string end) 
{ 
  
        endDate = end;
   
}


void Subscription::displayDetails() 
{
    cout << "Subscription Type: " << subscriptionType << endl;
    cout << "Price: " << price << endl;
    cout << "Duration: " << duration << " months" << endl;
    cout << "Start Date: " << startDate << endl;
    cout << "End Date: " << endDate << endl;
}

void Subscription::renewalNotification()
{
    // Today's date
    tm today = {};
    today.tm_year = nowYear - 1900;
    today.tm_mon = nowMonth - 1;
    today.tm_mday = nowDay;
    today.tm_hour = 0; today.tm_min = 0; today.tm_sec = 0;
    time_t today_time = mktime(&today);


    // Parse endDate ("dd-mm-yyyy") for comparision 
    int endDay, endMonth, endYear;
    char dash1, dash2;
    std::istringstream iss(endDate);
    iss >> endDay >> dash1 >> endMonth >> dash2 >> endYear;

    tm end_tm = {};
    end_tm.tm_year = endYear - 1900;
    end_tm.tm_mon = endMonth - 1;
    end_tm.tm_mday = endDay;
    end_tm.tm_hour = 0; end_tm.tm_min = 0; end_tm.tm_sec = 0;
    time_t end_time = mktime(&end_tm);

    // Calculate difference in days
    double diff_seconds = difftime(end_time, today_time);
    int diff_days = static_cast<int>(diff_seconds / (60 * 60 * 24));

    // Return true if end date is within the next 7 days (including today)
    return (diff_days >= 0 && diff_days <= 7);

}
