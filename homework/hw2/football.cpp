#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
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
    int day, month, year, Q1[2], Q2[2], Q3[2], Q4[2], OT[2], score[2];
    Date date;
    TeamSummary teamSummary[2];
    vector<Game> games;

    while (input_file_str >> weekday >> month >> day >> year) {
        /* Testing */
        cout << weekday << endl;
        cout << month << endl;
        cout << day << endl;
        cout << year << endl;

        month = get_month(month_s);
        // capture the `Date' data
        date = Date(day, month, year, weekday);

        for (int i = 0; i < 2; i++) {
            // get the home and visitor team information
            input_file_str >> team[i] >> Q1[i] >> Q2[i] >> Q3[i] >> Q4[i] >> OT[i] >> score[i];

            /* Testing */
            cout << team[i] << endl;
            cout << Q1[i] << endl;
            cout << Q2[i] << endl;
            cout << Q3[i] << endl;
            cout << Q4[i] << endl;
            cout << OT[i] << endl;
            cout << score[i] << endl;

            /* Create the `TeamSummary' objects so we can create a `Game' after
             * this. */
            teamSummary[i] = TeamSummary(team[i], Q1[i], Q2[i], Q3[i], Q4[i], OT[i], score[i]);
        }

        // add the `Game' to the vector of games
        games.push_back(Game(date, teamSummary[0], teamSummary[1]));
    }

    return 0;
}

int get_month(const string &month)
{
    if (month == "September")
        return 1;
    else if (month == "October")
        return 2;

    return 3;
}


void usage()
{
    cerr << "football ifile ofile" << endl;
}
