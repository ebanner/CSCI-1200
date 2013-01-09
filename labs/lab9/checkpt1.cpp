#include <iostream>
#include <fstream>
#include <map>
#include <cmath>

int main(int argc, char **argv)
{
  if (argc != 2) {
    std::cerr << "usage: mode input_file" << std::endl;
    return 1;
  }

  // open up an input stream on argument 1
  std::ifstream input_file_str(argv[1]);

  if (! input_file_str) {
    std::cerr << "Bad input file: " << argv[1] << std::endl;
    return 1;
  }

  std::map<int, int> modes; // map to hold the number of times a number appears
  std::pair<std::map<int, int>::iterator, bool> status; // used to check if insert was successful
  int num, freq = 0;
  while (input_file_str >> num) {
    /* Pretend like it's the first time you've seen the number and try and 
     * insert it. */
    status = modes.insert(std::make_pair(num, 1));

    if (status.second == false) // the number has appeared in the sequence before
      status.first->second++; // increse the number of times we've seen the number

    freq = std::max(freq, status.first->second);
  }

  std::cout << "modes: ";
  for (std::map<int, int>::iterator it = modes.begin(); it != modes.end(); it++)
    if (it->second == freq)
      std::cout << it->first << ' ';
  std::cout << std::endl;
  
  return 0;
}
