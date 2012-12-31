#ifndef TEAM_CPP
#define TEAM_CPP

#include <string>
#include "Team.h"

using namespace std;

Team::Team() {
    name = "N/A";
    wins = 0;
    losses = 0;
    gamesPlayed = 0;
}

Team::Team(const string &name) {
    this->name = name;
    this->wins = 0;
    this->losses = 0;
    this->gamesPlayed = 0;
}

Team::Team(const string &name, const int wins, const int losses) {
    this->name = name;
    this->wins = wins;
    this->losses = losses;
    this->gamesPlayed = 1;
}

float Team::getWinningPercentage() const {
    return float(wins) / float(gamesPlayed);
}

void Team::print(ofstream &output_file_str, int longest_name) const {
    output_file_str << setw(longest_name+5) << left << name << setw(2) << right << wins << " win(s) - " <<
        setw(2) << right << losses << " loss(es)  " << setprecision(2) << getWinningPercentage() << endl;
}

bool sortByWinningPercentage(const Team &team1, const Team &team2) {
    if (team1.getWinningPercentage() > team2.getWinningPercentage())
        return true;
    else if (team1.getWinningPercentage() < team2.getWinningPercentage())
        return false;

    // winning percentages are equal
    
    if (team1.getGamesPlayed() > team2.getGamesPlayed())
        return true;
    else if (team1.getGamesPlayed() < team2.getGamesPlayed())
        return false;

    // games played are equal
    
    if (team1.getName() < team2.getName())
        return true;
    else if (team1.getName() > team2.getName())
        return false;

    // Teams are the same. Impossible! But return true anyway;
    return true;
}

bool operator== (const Team &team1, const Team &team2) {
    return team1.getName() == team2.getName();
}

#endif
