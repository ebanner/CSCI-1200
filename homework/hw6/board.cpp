#include <iostream>
#include <cassert>
#include "board.h"




// Prepare an ascii art representation of the current state of the board
std::vector<std::string> Board::print(const std::vector<Robot> &robots) const {

  // Prepare the return value
  std::vector<std::string> answer(num_rows*4+1, std::string(num_cols*4+1,' '));

  // Draw the outer border
  for (int i = 0; i < num_rows*4+1; i++) {
    answer[i][0] = '|';
    answer[i][num_cols*4] = '|';
  }
  for (int i = 0; i < num_cols*4+1; i++) {
    answer[0][i] = '-';
    answer[num_rows*4][i] = '-';
  }
  
  // Put tick marks at the corners of all grid cells
  for (int i = 0; i < num_cols*4+1; i+=4) {
    for (int j = 0; j < num_rows*4+1; j+=4) {
      answer[j][i] = '+';
    }
  }

  // draw each robot
  for (unsigned int i = 0; i < robots.size(); i++) {
    // grab the current position & direction
    Position p = robots[i].getCurrentPosition();
    std::string direction = robots[i].getCurrentDirection();
    // calcuate the coordinate (flip the vertical axis)
    int r = (num_rows-1-p.row)*4+2;
    int c = p.col*4+2;
    // verify that no other robot is here
    assert (answer[r][c] == ' ');
    // draw the letter
    answer[r][c] = robots[i].getSymbol();
    // draw the robot direction indicator
    if (direction == "north") {
      answer[r-1][c] = '^';
    } else if (direction == "east") {
      answer[r][c+1] = '>';
    } else if (direction == "south") {
      answer[r+1][c] = 'v';
    } else {
      assert (direction == "west");
      answer[r][c-1] = '<';
    }
  }

  return answer;
}

