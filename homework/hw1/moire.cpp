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
void draw_moire_isosceles_triangle(const string &pattern, const int height, ofstream &out_file);

/* Prints out a Moire pattern */
int main(int argc, char **argv)
{
    if (argc != 5) {
        usage();
        return 1;
    }

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

    // decide which shape to draw
    if (is_square(shape)) {
        draw_moire_square(pattern, height, out_file);

    } else if (is_right_triangle(shape)) {
        draw_moire_right_triangle(pattern, height, out_file);

    } else if (is_isosceles_triangle(shape)) {
        draw_moire_isosceles_triangle(pattern, height, out_file);

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
    int offset = 0; // offset into the pattern
    
    // print the beginning row of stars
    out_file << string(height, '*') << endl;

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
    out_file << string(height, '*') << endl;
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

    // print the ending row of stars
    cout << string(1+chars+1, '*') << endl;
}

void draw_moire_isosceles_triangle(const string &pattern, const int height, ofstream &out_file)
{
    int width = 2*height - 1;
    int mid, spaces;
    /* The middle offset is the same number as the number of leading spaces to 
     * start off. */
    mid = spaces = width / 2;
    // number of character from pattern on a row
    int chars = 1;
    // offset into `pattern' so we know which character to print
    int offset = 0;

    // print the first star all by itself
    for (int c = 0; c < spaces; c++)
        cout << ' ';
    // print leading star and newline
    cout << '*' << endl;

    // decrement the number of spaces for the next row
    spaces--;

    for (int r = 1; r <= height-2; r++) {
        // print the leading spaces
        for (int c = 0; c < spaces; c++)
            cout << ' ';
        // print the leading star
        cout << '*';

        // print the character on the current row
        for (int c = 0; c < chars; c++) {
            cout << pattern[offset];
            offset = (offset+1) % pattern.length();
        }
        // print the trailing star and newline
        cout << '*' << endl;

        // increment the number of character to print on the next row
        chars += 2;
        // decrement the number of spaces to print on the next row
        spaces--;
    }

    // print bottom row of stars
    cout << string(width, '*') << endl;
}
