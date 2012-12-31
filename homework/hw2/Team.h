#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <string>

using namespace std;

class Team {
    private:
        string name;
        int wins;
        int losses;
        int gamesPlayed;
    public:
        // constructors
        Team();
        Team(const string &name);
        Team(const string &name, const int wins, const int losses);

        // accessors
        string getName() const { return name; }
        int getWins() const { return wins; }
        int getLosses() const { return losses; }
        int getGamesPlayed() const { return gamesPlayed; }

        // modifiers
        void setName(const string &name) { this->name = name; }
        void setWins(const int wins) { this->wins = wins; }
        void setLosses(const int losses) { this->losses = losses; }
        void setGamesPlayed(const int gamesPlayed) { this->gamesPlayed = gamesPlayed; }
        void addWin() { wins++; gamesPlayed++; }
        void addLoss() { losses++; gamesPlayed++; }

        // table stuff
        float getWinningPercentage() const;
        void print(ofstream &output_file_str, int longest_name) const;
};

bool sortByWinningPercentage(const Team &team1, const Team &team2);
bool operator== (const Team &team1, const Team &team2);

#endif
