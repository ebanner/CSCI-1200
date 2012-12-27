// Program:  Moire
// Author:   Prof. Barb Cutler
// Purpose:  Solution to HW 1

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

// This function returns a string for the "interior" of a line of output 
// of length num_digits.  The index variable is modified to keep track of
// where we are in the pattern string. 
std::string construct_line(std::string pattern, int &index, int num_digits) {
  std::string answer;
  for (int i = 0; i < num_digits; i++) {
    answer +=  pattern[index];
    index++;
    index %= pattern.length();
  }
  return answer;
}


// Form and output the SQUARE moire image
void output_square(const std::string& pattern, int height, std::ofstream &out_str) {

  // this variable keep track of where we are in the pattern string
  int index = 0;

  // the first line
  out_str << std::string(height,'*') << std::endl; 

  // all the lines in the middle
  for (int i = 1; i < height-1; i++) {
    out_str << '*' << construct_line(pattern,index,height-2) << '*' << std::endl;
  }

  // the last line
  if (height > 1)
    out_str << std::string(height,'*') << std::endl; 
}


// Form and output the RIGHT TRIANGLE moire image
void output_right_triangle(const std::string& pattern, int height, std::ofstream &out_str) {

  // this variable keep track of where we are in the pattern string
  int index = 0;

  // the first line
  out_str << "*" << std::endl;

  // all the lines in the middle
  for (int i = 1; i < height-1; i++) {
    out_str << '*' << construct_line(pattern,index,i-1) << '*' << std::endl;
  }

  // the last line
  if (height > 1)
    out_str << std::string(height,'*') << std::endl; 
}


// Form and output the ISOSCELES TRIANGLE moire image
void output_isosceles_triangle(const std::string& pattern, int height, std::ofstream &out_str) {

  // this variable keep track of where we are in the pattern string
  int index = 0;

  // the first line
  out_str << std::string(height-1,' ') << "*" << std::endl;

  // all the lines in the middle
  for (int i = 1; i < height-1; i++) {
    out_str << std::string(height-i-1,' ') << '*' << construct_line(pattern,index,i*2-1) << '*' << std::endl;
  }

  // the last line
  if (height > 1)
    out_str << std::string(height*2-1,'*') << std::endl; 
}


// handle the args & open the file streams
int main( int argc, char* argv[] ) {

  // Check the number of arguments.
  if (argc != 5) {
    std::cerr << "Usage:\n  " << argv[0] << " pattern height shape outfile\n";
    return 1;
  }

  // Check the validity of the string argument
  if (std::string(argv[1]).size() == 0) {
    std::cerr << "ERROR: empty string" << std::endl;
    return 1;
  }

  // Convert from string to integer and check validity of height argument
  int height = atoi(argv[2]);
  if (height < 1) {
      std::cerr << "ERROR: cannot draw shape with height < 1" << std::endl;
    return 1;
  }

  // Open the output file
  std::ofstream out_str(argv[4]);
  if (!out_str) {
    std::cerr << "Could not open " << argv[4] << " to write\n";
    return 1;
  }

  // Output the appropriate image
  // (also checking the validity of the shape argument)
  if (argv[3] == std::string("square")) {
    output_square(argv[1],height,out_str);
  } else if (argv[3] == std::string("right_triangle")) {
    output_right_triangle(argv[1],height,out_str);
  } else if (argv[3] == std::string("isosceles_triangle")) {
    output_isosceles_triangle(argv[1],height,out_str);
  } else {
    std::cerr << "Unknown shape " << argv[3] << std::endl;
    return 1;
  }
  
  return 0;
}
