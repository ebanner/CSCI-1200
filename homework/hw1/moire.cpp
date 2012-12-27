#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

bool is_square(const string &pattern);
bool is_right_triangle(const string &pattern);
bool is_isosceles_triangle(const string &pattern);
void usage();
void draw_moire_square(const string &pattern, const int height, ofstream &out_file);
void draw_moire_right_triangle(const string &pattern, const int height, ofstream &out_file);

/* Prints out a Moire pattern */
int main(int argc, char **argv)
{
    string pattern = argv[1];
    int height; 
    stringstream(argv[2]) >> height;
    string shape = argv[3];
    char *file = argv[4];
    ofstream out_file(file);

    if (! out_file.is_open()) {
        cerr << "Failed to open file" << endl;
        return 1;
    }

    if (is_square(shape)) {
        draw_moire_square(pattern, height, out_file);

    } else if (is_right_triangle(shape)) {
        draw_moire_right_triangle(pattern, height, out_file);

    } else if (is_isosceles_triangle(shape)) {
        //draw_moire_isosceles_triangle(pattern, height, out_file);

    } else {
        cerr << "Invalid shape: " << shape << endl;
        usage();

    }
    out_file.close();

    return 0;
}

bool is_square(const string &shape)
{
    return shape.compare("square") == 0;
}

bool is_right_triangle(const string &shape)
{
    return shape.compare("right_triangle") == 0;
}

bool is_isosceles_triangle(const string &shape)
{
    return shape.compare("isosceles_triangle") == 0;
}

void usage()
{
    cerr << "usage: moire pattern height (square|right_triangle|isosceles_triangle) out" << endl;
}

void draw_moire_square(const string &pattern, const int height, ofstream &out_file)
{
    string star_row(height, '*');
    int offset = 0; // offset into the pattern
    
    // print the beginning row of stars
    out_file << star_row << endl;

    for (int r = 1; r <= height-1; r++) {
        // print the leading star
        out_file << '*';

        for (int c = 1; c < height-1; c++) {
            // print the character at `offset'
            out_file << pattern[offset];
            // increment the offset or loop back to the beginning
            offset = (offset+1) % pattern.length();
        }

        // print the trailing star and newline
        out_file << '*' << endl;
    }
    // print the ending row of stars
    out_file << star_row << endl;
}

void draw_moire_right_triangle(const string &pattern, const int height, ofstream &out_file)
{
    // print the star on the first row
    cout << '*' << endl;

    // how many characters of the pattern to print on each line
    int chars = 0;
    // offset into `pattern' to print
    int offset = 0;

    for (int r = 1; r <= height-2; r++) {
        // print the leading star
        cout << '*';

        for (int c = 0; c < chars; c++) {
            cout << pattern[offset];
            /* Increment the character offset and loop back to the beginning if
             * you've reached the end. */
            offset = (offset+1) % pattern.length();
        }
        
        // print the trailing star and a newline
        cout << '*' << endl;

        /* Increment the number of characters to print on a line for the next 
         * iteration. */
        chars++;
    }

    string star_row(1+chars+1, '*');
    // print the ending row of stars
    cout << star_row << endl;
}
