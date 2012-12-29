#include <iostream>
#include "Date.h"

using namespace std;

Date::Date() {
    day = 1;
    month = 1;
    year = 1900;
}

Date::Date(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

void Date::setDay(const int day) {
    this->day = day;
}

void Date::setMonth(const int month) {
    this->month = month;
}

void Date::setYear(const int year) {
    this->year = year;
}

bool Date::isEqual(const Date &date) const {
    return date.day == day &&
        date.month == month &&
     date.year == year;
}

void Date::print() const {
    cout << day << " " << month << " " << year << endl;
}

bool sameDay(const Date &date1, const Date &date2) {
    return date1.getDay() == date2.getDay() &&
        date1.getMonth() == date2.getMonth() &&
     date1.getYear() == date2.getYear();
}

bool operator< (const Date &date1, const Date &date2) {
    if (date1.getYear() < date2.getYear())
        return true;
    else if (date1.getYear() > date2.getYear())
        return false;

    // date1.year == date2.year
    
    if (date1.getMonth() < date2.getMonth())
        return true;
    else if (date1.getYear() > date2.getYear())
        return false;

    // date1.month == date2.month

    if (date1.getDay() < date2.getDay())
        return true;
    else // date1 >= date2
        return false;
}
