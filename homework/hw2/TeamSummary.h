#ifndef TEAMSUMMARY_H
#define TEAMSUMMARY_H

#include <string>
#include <string.h>

using namespace std;

class TeamSummary {
    public:
        // constructor
        TeamSummary();
        TeamSummary(const string team, const int quarters[], const int score);
        TeamSummary(const string team, 
                const int Q1, const int Q2, const int Q3, const int Q4, 
             const int OT, const int score);

        // accessors
        string getName() const { return name; }
        int getQ1() const { return quarters[0]; }
        int getQ2() const { return quarters[1]; }
        int getQ3() const { return quarters[2]; }
        int getQ4() const { return quarters[3]; }
        int getOT() const { return quarters[4]; }
        const int *getQuarters() const { return quarters; }
        int getScore() const { return score; }
        bool isVictor() const { return won; }

        // modifiers
        void setName(const string name) {this->name = name; }
        void setQ1(const int Q1) {this->quarters[0] = Q1; }
        void setQ2(const int Q2) {this->quarters[1] = Q2; }
        void setQ3(const int Q3) {this->quarters[2] = Q3; }
        void setQ4(const int Q4) {this->quarters[3] = Q4; }
        void setOT(const int OT) {this->quarters[4] = OT; }
        void setQuarters(const int quarters[]) { memcpy(this->quarters, quarters, sizeof(this->quarters)); }
        void setScore(const int score) {this->score = score; }
        void setVictor(const bool won) {this->won = won; }

    private:
        string name;
        int quarters[5]; // haha, not really `quarters'
        int score;
        bool won;
};

#endif
