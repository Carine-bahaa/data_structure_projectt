#include "Time.h"

Time::Time()
{
    time(&now);
    localtime_s(&local_time, &now); // Safe version to convert to local time
}

int Time::getDay() const {
    return local_time.tm_mday; // Return the current day
}

int Time::getMonth() const {
    return local_time.tm_mon + 1; // Return the current month (0-11, so add 1)
}

int Time::getYear() const {
    return local_time.tm_year + 1900; // Return the current year (tm_year is years since 1900)
}

int Time::getHour() const
{
    return local_time.tm_hour + 1;
}
