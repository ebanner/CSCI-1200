#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

Date::Date() {
    day = 1;
    month = 1;
    year = 1900;
}

Date::Date(int day, int month, int year, string weekday) {
    this->day = day;
    this->month = month;
    this->year = year;
    this->weekday = weekday;
}

bool Date::isEqual(const Date &date) const {
    return date.day == day &&
         date.month == month &&
       date.year == year &&
      date.weekday == weekday;
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

    // same year
    
    if (date1.getMonth() < date2.getMonth())
        return true;
    else if (date1.getYear() > date2.getYear())
        return false;

    // same month

    if (date1.getDay() < date2.getDay())
        return true;
    else // date1 >= date2
        return false;
}
