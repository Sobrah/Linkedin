#include <Logics>

void Time::setDay(int day)
{
    this->day = day;
}

void Time::setMonth(int month)
{
    this->month = month;
}

void Time::setYear(int year)
{
    this->year = year;
}

void Time::setHour(int hour)
{
    this->hour = hour;
}

void Time::setMinute(int minute)
{
    this->minute = minute;
}

void Time::setSecond(int second)
{
    this->second = second;
}

int Time::getDay() const
{
    return day;
}

int Time::getMonth() const
{
    return month;
}

int Time::getYear() const
{
    return year;
}

int Time::getHour() const
{
    return hour;
}

int Time::getMinute() const
{
    return minute;
}

int Time::getSecond() const
{
    return second;
}
