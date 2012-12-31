#ifndef GAME_H
#define GAME_H

#include <string>
#include "Date.cpp"
#include "TeamSummary.cpp"

using namespace std;

class Game {
    public:
        // constructor
        Game();
        Game(const Date &date, const TeamSummary &visitorSummary, const TeamSummary &homeSummary);

        // accessors
        Date getDate() const { return date; }
        TeamSummary getVisitorSummary() const { return visitorSummary; }
        TeamSummary getHomeSummary() const { return homeSummary; }

        // modifiers
        void setDate(const Date date) {this->date = date; }
        void setVisitorSummary(const TeamSummary visitorSummary) { this->visitorSummary = visitorSummary; }
        void setHomeSummary(const TeamSummary homeSummary) { this->homeSummary = homeSummary; }

        // table stuff
        int getPointDifferential() const;
        int getTotalPoints() const;
        string getVisitorName() const { return visitorSummary.getName(); }
        string getHomeName() const { return homeSummary.getName(); }
        void print(ofstream &output_file_str, const int longestName[]) const;

    private:
        Date date;
        TeamSummary visitorSummary;
        TeamSummary homeSummary;
};

bool sortByPointDifferential(const Game &game1, const Game &game);

#endif
