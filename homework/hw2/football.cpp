#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "TeamSummary.cpp"
#include "Game.cpp"
#include "Team.cpp"

using namespace std;

void usage();
int get_month(const string &month);
vector<Team> populate_teams(vector<Game> &games);

int main(int argc, char **argv)
{
    if (argc != 3) {
        usage();
        return 1;
    }

    // get the input and output files
    string ifile = argv[1];
    string ofile = argv[2];

    // open up and input stream on `ifile'
    ifstream input_file_str(ifile.c_str());
    if (! input_file_str) {
        cerr << "Couldn't open input file " << ifile << endl;
        return 1;
    }

    // open up output stream on `ofile'
    ofstream output_file_str(ofile.c_str());
    if (! output_file_str) {
        cerr << "Couldn't open output file " << ofile << endl;
        return 1;
    }

    // variable to capture date and the scores of two teams
    string weekday, month_s, team[2];
    int day, month, year, Q1[2], Q2[2], Q3[2], Q4[2], OT[2], score[2], longest_name[2];
    Date date;
    TeamSummary teamSummary[2];
    vector<Game> games;

    while (input_file_str >> weekday >> month_s >> day >> year) {
        /* Testing */
        /*
        cout << setw(11) << left << weekday << ' ' << month_s << ' ' << day << ' ' << year << endl;
        */

        month = get_month(month_s);
        // capture the `Date' data
        date = Date(day, month, year, weekday);

        // reset the longest name
        longest_name[0] = longest_name[1] = 0;

        for (int i = 0; i < 2; i++) {
            // get the home and visitor team information
            input_file_str >> team[i] >> Q1[i] >> Q2[i] >> Q3[i] >> Q4[i] >> OT[i] >> score[i];
            
            // keep track of the longest name seen so far
            longest_name[i] = max(longest_name[i], int(team[i].size()));

            /* Testing */
            /*
            cout << team[i] << ' ' << Q1[i] << ' ' << Q2[i] << ' ' << Q3[i] << ' ' << Q4[i] << 
                ' ' << OT[i] << ' ' << score[i] << endl;
            */

            /* Create the `TeamSummary' objects so we can create a `Game' after
             * this. */
            teamSummary[i] = TeamSummary(team[i], Q1[i], Q2[i], Q3[i], Q4[i], OT[i], score[i]);
        }

        // decide winner of the game
        teamSummary[0].setVictor(score[0] > score[1]);
        teamSummary[1].setVictor(score[1] > score[0]);

        // add the `Game' to the vector of games
        games.push_back(Game(date, teamSummary[0], teamSummary[1]));
    }

    // games have all been added -- time to sort them
    sort(games.begin(), games.end(), sortByPointDifferential);

    // print out the differentials
    cout << "ALL GAMES, SORTED BY POINT DIFFERENTIAL:" << endl;
    for (int i = 0; i < games.size(); i++)
        games[i].print(longest_name); 

    // translate the summaries for each game into a vector of teams
    vector<Team> teams = populate_teams(games);
    
    for (int i = 0; i < teams.size(); i++)
        teams[i].print();

    return 0;
}

vector<Team> populate_teams(vector<Game> &games)
{
    Team visitor_team, home_team;
    TeamSummary visitor_summary, home_summary;
    // create a container to hold the teams
    vector<Team> teams;
    vector<Team>::iterator it;
    // create the `Team' object from the `Game' objects
    for (int i = 0; i < games.size(); i++) {
        // get the summaries of each of the teams
        visitor_summary = games[i].getVisitorSummary();
        home_summary = games[i].getHomeSummary();

        // get the names of the teams
        string visitor_name = games[i].getVisitorName();
        string home_name = games[i].getHomeName();

        /* Create the `Teams' for the sole purpose of checking if they are a
         * team we've already added to the `Team' vector. */
        visitor_team = Team(visitor_name);
        home_team = Team(home_name);

        // check to see if the visitor is already in there
        if ((it = find(teams.begin(), teams.end(), visitor_team)) != teams.end()) {
            // Visitor is already in the vector -- just increment win or loss
            if (visitor_summary.isVictor()) {
                it->addWin();
            } else {
                it->addLoss();
            }
        } else {
            /* Visitor is not in the vector -- add it to the vector with a win 
             * or loss. */
            teams.push_back(Team(visitor_name, visitor_summary.isVictor() ? 1 : 0, visitor_summary.isVictor() ? 0 : 1));
        }
    }

    return teams;
}


int get_month(const string &month)
{
    if (month == "January")
        return 1;
    else if (month == "February")
        return 2;
    else if (month == "March")
        return 3;
    else if (month == "April")
        return 4;
    else if (month == "May")
        return 5;
    else if (month == "June")
        return 6;
    else if (month == "July")
        return 7;
    else if (month == "August")
        return 8;
    else if (month == "September")
        return 9;
    else if (month == "October")
        return 10;
    else if (month == "November")
        return 11;
    else if (month == "December")
        return 12;
    else
        return -1;
}


void usage()
{
    cerr << "football ifile ofile" << endl;
}
