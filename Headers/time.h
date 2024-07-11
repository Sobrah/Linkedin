#ifndef TIME_H
#define TIME_H

#include <QDateTime>

class Time : public QDateTime
{
public:
    // Setters
    void setDay(int);
    void setMonth(int);
    void setYear(int);
    void setHour(int);
    void setMinute(int);
    void setSecond(int);

    // Getters
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

private:
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;
};

#endif // TIME_H
