#include <iostream>
#include <vector>

main()
{
  int rows = 5, columns = 5;


  std::vector<std::vector<bool> > board(rows);
  for (int r = 0; r < rows; r++)
    for (int c = 0; c < columns; c++)
      board[r].push_back(false);

}
