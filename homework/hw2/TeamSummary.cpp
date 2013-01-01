#include "TeamSummary.h"

TeamSummary::TeamSummary() {
    name = "N/A";
    for (int i = 0; i < sizeof(quarters)/sizeof(quarters[0]); i++)
        quarters[i] = 0;
    score = 0;
    won = false;
}

TeamSummary::TeamSummary(const string name, const int quarters[], const int score) {
    this->name = name;
    memcpy(this->quarters, quarters, sizeof(this->quarters));
    this->score = score;
    this->won = false;
}
TeamSummary::TeamSummary(const string name, 
                const int Q1, const int Q2, const int Q3, const int Q4, 
             const int OT, const int score) {
    this->name = name;
    this->quarters[0] = Q1;
    this->quarters[1] = Q2;
    this->quarters[2] = Q3;
    this->quarters[3] = Q4;
    this->quarters[4] = OT;
    this->score = score;
    this->won = false;
}
