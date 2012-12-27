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

int Date::setDay(const int day) {
    this->day = day;
}

int Date::setMonth(const int month) {
    this->month = month;
}

int Date::setYear(const int year) {
    this->year = year;
}

void Date::increment() {
    // day
    if (isLastDayInMonth())
        day = 1;
    else
        day++;

    // month
    if (month == 12)
        month = 1;
    else
        month++;

    // year
    year++;
}

void Date::addDays(unsigned int num_days_to_add) {
    for (int i = 0; i < num_days_to_add; i++)
        increment();
}

bool Date::isEqual(const Date &date) const {
    return date.day == day &&
        date.month == month &&
        date.year == year;
}

bool Date::isLeapYear() const {
    return (year % 4 == 0 && year % 100 != 0) ||
        year % 400 == 0;
}

bool 
