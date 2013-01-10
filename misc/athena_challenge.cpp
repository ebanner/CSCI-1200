#include <iostream>
#include <vector>
#include <vector>
#include <algorithm>
#include <cstdlib>

class loc {
  public:
    // constructor
    loc(int r, int c) { this->r = r; this->c = c; }

    int r;
    int c;
};

int num_paths_recursive(std::vector<std::vector<bool> > board, loc pos, int num_moves,  int rows, int columns)
{
  if (pos.r == rows-1 && pos.c == 0) { // base case: you're in the bottom left corner
    if (num_moves == rows*columns) {
      return 1; // visited every square
    } else {
      return 0; // didn't visit every square
    }
  } else if ((0 <= pos.r && pos.r <= rows-1) && (0 <= pos.c && pos.c <= columns-1) && ! board[pos.r][pos.c]) { 
    /* Legal r & c coordinates and this location has not yet been visited.
     *
     * Mark this position as being visited. */
    board[pos.r][pos.c] = true;

    return num_paths_recursive(board, loc(pos.r-1,pos.c), num_moves+1, rows, columns) +
           num_paths_recursive(board, loc(pos.r,pos.c+1), num_moves+1, rows, columns) +
           num_paths_recursive(board, loc(pos.r+1,pos.c), num_moves+1, rows, columns) +
           num_paths_recursive(board, loc(pos.r,pos.c-1), num_moves+1, rows, columns);

  } else { // this location is not legal
    return 0;
  }
}

int num_paths(int rows, int columns)
{
  std::vector<std::vector<bool> > board(rows);
  for (int r = 0; r < rows; r++)
    for (int c = 0; c < columns; c++)
      board[r].push_back(false); // populate the entire board as every position not with positions not yet visited

  /* Find the number of paths to the bottom right corner starting at row 0,
   * column 0, having already moved once (to get to the first coordinate. */
  return num_paths_recursive(board, loc(0,0), 1, rows, columns);
}

int main(int argc, char **argv)
{
  if (argc != 3)
    return 1;

  int columns = atoi(argv[1]);
  int rows = atoi(argv[2]);

  std::cout << num_paths(rows,columns) << std::endl;

  return 0;
}
  
bool operator==(const loc &pos1, const loc &pos2)
{
  return pos1.r == pos2.r && pos1.c == pos2.c;
}
