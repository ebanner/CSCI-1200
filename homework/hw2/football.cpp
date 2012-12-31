#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "TeamSummary.cpp"
#include "Game.cpp"

using namespace std;

void usage();
int get_month(const string &month);

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

        // add the `Game' to the vector of games
        games.push_back(Game(date, teamSummary[0], teamSummary[1]));
    }

    // games have all been added -- time to sort them
    sort(games.begin(), games.end(), sortByPointDifferential);

    // print out the differentials
    cout << "ALL GAMES, SORTED BY POINT DIFFERENTIAL:" << endl;
    for (int i = 0; i < games.size(); i++)
        games[i].print(longest_name); 

    return 0;
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
