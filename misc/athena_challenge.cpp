#include <iostream>
#include <vector>
#include <vector>
#include <algorithm>
#include <cstdlib>

class loc {
  public:
    // constructor
    loc(int x, int y) { this->x = x; this->y = y; }

    int x;
    int y;
};

int num_paths_recursive(std::vector<loc> path, std::vector<loc> every_square, loc pos, int width, int height)
{
  if (pos.x == 0 && pos.y == height-1) {
    // base case: you're in the bottom right corner
    if (every_square.size() == 1) {
      return 1; // visited every square
    } else {
      return 0; // didn't visit every square
    }
  } else if ((0 <= pos.x && pos.x <= width-1) && (0 <= pos.y && pos.y <= height-1) && // legal x & y coordinates
             std::find(path.begin(), path.end(), pos) == path.end()) { // no repeat coordinates
    // add the current posation to the path
    path.push_back(pos);
    // check off the current square
    std::vector<loc>::iterator it = find(every_square.begin(), every_square.end(), pos);
    every_square.erase(it);

    return num_paths_recursive(path, every_square, loc(pos.x, pos.y-1), width, height) +
      num_paths_recursive(path, every_square, loc(pos.x+1, pos.y), width, height) +
      num_paths_recursive(path, every_square, loc(pos.x, pos.y+1), width, height) +
      num_paths_recursive(path, every_square, loc(pos.x-1, pos.y), width, height);
  } else { // this location is not legal
    return 0;
  }
}

int num_paths(int width, int height)
{
  std::vector<loc> path;
  std::vector<loc> every_square;
  for (int x = 0; x < width; x++)
    for (int y = 0; y < height; y++)
      every_square.push_back(loc(x, y)); // populate the vector with every coordinate

  return num_paths_recursive(path, every_square, loc(0, 0), width, height);
}

int main(int argc, char **argv)
{
  if (argc != 3)
    return 1;

  int width = atoi(argv[1]);
  int height = atoi(argv[2]);

  std::cout << num_paths(width, height) << std::endl;

  return 0;
}
  
bool operator==(const loc &loc1, const loc &loc2)
{
  return loc1.x == loc2.x && loc1.y == loc2.y;
}
