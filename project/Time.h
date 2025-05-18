#pragma once
#include<ctime>
#include<iostream>
using namespace std;
class Time
{
    time_t now;
    struct tm local_time;
public:
    Time();
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    int getHour() const;
};

