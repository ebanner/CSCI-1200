#ifndef MYTIME_H
#define MYTIME_H

class MyTime {
    public:
        MyTime();
        MyTime(const int seconds, const int minutes, const int hours);

        // accessors
        int getSeconds() const;
        int getMinutes() const;
        int getHours() const;

        // modifiers
        void setSeconds(const unsigned int seconds);
        void setMinutes(const unsigned int minutes);
        void setHours(const unsigned int hours);
        void setTime(const unsigned int seconds, 
                const unsigned int minutes,
            const unsigned int hours);

        void incrementSeconds();
        void incrementMinutes();
        void incrementHours();

        void addSeconds(const unsigned int seconds);
        void addMinutes(const unsigned int minutes);
        void addHours(const unsigned int hours);

        void reset();
        void print() const;
        void printAMPM() const;

    private:
        unsigned int seconds;
        unsigned int minutes;
        unsigned int hours;
};

#endif
