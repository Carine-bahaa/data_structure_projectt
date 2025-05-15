#include <iostream>
#include <string>
#include"Time.h"
#include <sstream>
#include <cctype>
using namespace std;

class Subscription 
{
private:
    string subscriptionType;
    double price;
    int duration;
    string startDate;
    string endDate;

public:
    Subscription(double price, int duration, string start, string end);
    Subscription();
    // Getters
    string getSubscriptionType();
    double getPrice();
    int getDuration();
    string getStartDate();
    string getEndDate();

    // Setters
    void setSubscriptionType(string type);
    void setPrice(double price);
    void setDuration(int duration);
    void setStartDate(string start);
    void setEndDate(string end);

    void displayDetails();
    bool renewalNotification();
    
};
