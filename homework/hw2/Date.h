class Date {
    public:
        // constructors
        Date();
        Date(int day, int month, int year);

        /* Accessors -- we won't be modifying any of the class's instance
         * variables. */
        int getDay() const;
        int getMonth() const;
        int getYear() const;

        /* Modifiers -- we cannot use the `const' keyword here because we are
         * going to be modifying the instance variables of the class. */
        void setDay(const int day);
        void setMonth(const int month);
        void setYear(const int year);

        // member functions that operate on `Date' objects
        bool isEqual(const Date &date) const;
        void print() const;

    private:
        int day;
        int month;
        int year;
};

bool sameDay(const Date &date1, const Date &date2);
bool operator< (const Date &date1, const Date &date2);
