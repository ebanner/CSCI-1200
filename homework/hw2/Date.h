#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
    public:
        // constructors
        Date();
        Date(const int day, const int month,
                const int year, const string weekday);

        /* Accessors -- we won't be modifying any of the class's instance
         * variables. */
        int getDay() const { return day; }
        int getMonth() const { return month; }
        int getYear() const { return year; }
        string getWeekday() const { return weekday; }

        /* Modifiers -- we cannot use the `const' keyword here because we are
         * going to be modifying the instance variables of the class. */
        void setDay(const int day) { this->day = day; }
        void setMonth(const int month) { this->month = month; }
        void setYear(const int year) { this->year = year; }
        void setWeekday(const string weekday) { this->weekday = weekday; }

        // member functions that operate on `Date' objects
        bool isEqual(const Date &date) const;
        void print() const;

    private:
        int day;
        int month;
        int year;
        string weekday;
};

bool sameDay(const Date &date1, const Date &date2);
bool operator< (const Date &date1, const Date &date2);

#endif
