#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>

class loc {
  public:
    // constructor
    loc(int x, int y) { this->x = x; this->y = y; }

    int x; // x coordinate
    int y; // y coordinate
};

bool operator==(const loc &loc1, const loc &loc2)
{
  return loc1.x == loc2.x && loc1.y == loc2.y;
}

int num_paths_recurse(std::vector<loc> path, loc pos, int max_dist)
{
  if (pos.x == 0 && pos.y == 0) { // you've made it back to the origin
    return 1;
  } else if (abs(pos.x)+abs(pos.y) <= max_dist && std::find(path.begin(), path.end(), pos) == path.end()) {
    /* Distance did not increase and we haven't been on this location before.
     *
     * Add the current location to the path. */
    path.push_back(pos);

    return num_paths_recurse(path, loc(pos.x, pos.y-1), max_dist) +
      num_paths_recurse(path, loc(pos.x+1, pos.y), max_dist) +
      num_paths_recurse(path, loc(pos.x, pos.y+1), max_dist) +
      num_paths_recurse(path, loc(pos.x-1, pos.y), max_dist);
  } else { // not a legal location
    return 0;
  }
}

int num_paths(int x, int y)
{
  std::vector<loc> path;

  return num_paths_recurse(path, loc(x,y), abs(x)+abs(y));
}

/* Prints out the number of paths to the origin with no walls. */
int main(int argc, char **argv)
{
  if (argc != 3) {
    std::cerr << "usage: path_count x_coor y_coor" << std::endl;
    return 1;
  }

  int x = atoi(argv[1]);
  int y = atoi(argv[2]);

  std::cout << "Number of paths from (" << x << ',' << y << ") to origin: " << num_paths(x,y) << std::endl;

  return 0;
}
