#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <string>
#include "robot.h"


// The Board class stores the board dimensions, number of steps for
// each robot in the simulation, and prepares the output
class Board {
public:

  // CONSTRUCTOR
  Board(int c=0, int r=0, int n=0) : num_cols(c), num_rows(r), num_steps(n) {}  

  // ACCESSORS
  int numRows() const { return num_rows; }
  int numCols() const { return num_cols; }
  int numSteps() const { return num_steps; }

  // OUTPUT
  // given all the robots, construct an ascii art picture of the current board
  std::vector<std::string> print(const std::vector<Robot> &robots) const;
  
private:
                     
  // REPRESENTATION
  int num_cols;      
  int num_rows;
  int num_steps;
};


#endif
