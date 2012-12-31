#ifndef GAME_CPP
#define GAME_CPP

#include <cmath>
#include <string>
#include "Game.h"

Game::Game() : date(), visitorSummary(), homeSummary() {
    // initialzie instance variables with default constructors
}

Game::Game(const Date &date, const TeamSummary &visitorSummary, const TeamSummary &homeSummary) {
    this->date = date;
    this->visitorSummary = visitorSummary;
    this->homeSummary = homeSummary;
}

int Game::getPointDifferential() const {
    return abs(visitorSummary.getScore() -
            homeSummary.getScore());
}

int Game::getTotalPoints() const {
    return visitorSummary.getScore() + homeSummary.getScore();
}

void Game::print(ofstream &output_file_str, const int longestName[]) const {
    string outcome;
    if (visitorSummary.getScore() > homeSummary.getScore())
        outcome = " defeated ";
    else if (visitorSummary.getScore() < homeSummary.getScore())
        outcome = " lost to ";
    else
        outcome = " tied ";
    output_file_str << setw(longestName[0]+5) << left << visitorSummary.getName() <<
        setw(11) << left << outcome << setw(longestName[1]+5) << left <<
        homeSummary.getName() << setw(2) << right << visitorSummary.getScore()
        << " - " << setw(2) << right << homeSummary.getScore() << endl;
}

bool sortByPointDifferential(const Game &game1, const Game &game2) {
    if (game1.getPointDifferential() < game2.getPointDifferential())
        return true;
    else if (game1.getPointDifferential() > game2.getPointDifferential())
        return false;

    // point differentials are the same
    
    if (game1.getTotalPoints() > game2.getTotalPoints())
        return true;
    else if (game1.getTotalPoints() < game2.getTotalPoints())
        return false;

    // point differentials are the same

    if (game1.getVisitorName() < game2.getVisitorName())
        return true;
    else if (game1.getVisitorName() > game2.getVisitorName())
        return false;

    // visitor team name is the same
    
    if (game1.getHomeName() < game2.getHomeName())
        return true;
    else if (game1.getHomeName() > game2.getHomeName())
        return false;

    // home team is the same
    
    /* This won't happen unless we have repeat games. So just return true and
     * see what happens. */
    return true;
}

#endif
