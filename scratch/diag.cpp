#include <iostream>
#include <string>

using namespace std;

main()
{
    string name;

    // prompt user for their name
    cout << "Enter your name: ";

    // get the user's name
    cin >> name;

    // print the top row of stars
    for (int i = 0; i < name.length()+4; i++)
        cout << '*';
    cout << endl; // newline

    int spaces = 1;
    for (int i = 0; i < name.length(); i++) {

        cout << '*'; // opening star
        for (int j = 0; j < spaces; j++) {
            // print the spaces before the letter
            cout << ' ';
        }
        // print out the letter
        cout << name[i];

        for (int j = 0; j < name.length()-spaces+1; j++) {
            // print the remaining spaces
            cout << ' ';
        }
        cout << '*'; // closing star
        
        // print the newline
        cout << endl;

        // increment the `spaces' counter
        spaces++;
    }
    
    // print the bottom row of stars
    for (int i = 0; i < name.length()+4; i++)
        cout << '*';
    cout << endl; // newline
}
