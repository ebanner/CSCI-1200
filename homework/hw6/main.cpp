#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>

#include "robot.h"
#include "board.h"

// ======================================================================================
// helper functions

void ReadInput(std::istream &istr, Board &board, std::vector<Robot> &robots);
void Run(const Board &board, std::vector<Robot> &robots);
void print_usage_message(std::string program_name) {
    std::cerr << "Usage:  " << program_name << " <input.txt> [ -find_all_solutions ] [ -verbose ] [ -allow_pushing ]" << std::endl;
}

// ======================================================================================

int main(int argc, char* argv[]) {

  // print usage information
  if (argc < 2) {
    print_usage_message(argv[0]);
    exit(1);
  }

  bool find_all_solutions = false;
  bool allow_pushing = false;
  bool verbose = false;

  // process the command line arguments
  for (int i = 2; i < argc; i++) {
    if (std::string(argv[i]) == "-find_all_solutions") {
      find_all_solutions = true;
    } else if (std::string(argv[i]) == "-allow_pushing") {
      allow_pushing = true;
    } else if (std::string(argv[i]) == "-verbose") {
      verbose = true;
    } else {
      std::cerr << "Unknown command line argument: " << argv[i] << std::endl; 
      print_usage_message(argv[0]);
      exit(1); 
    }
  }

  // open the input file
  std::ifstream istr(argv[1]);
  if (!istr) { 
    std::cerr << "Failed to open " << argv[1] << std::endl;
    exit(1);
  }

  // read the board & robot information
  Board board;
  std::vector<Robot> robots;
  ReadInput(istr,board,robots);



  // ASSIGNMENT: change as needed
  // for now, let's just run the commands in the order provided
  Run(board,robots);



}


// ======================================================================================

// Parse the input file
void ReadInput(std::istream &istr, Board &board, std::vector<Robot> &robots) {

  // read in the board dimensions
  std::string token;
  int cols, rows;
  istr >> token >> cols >> rows;
  assert (token == "board");
  assert (cols >= 1 && rows >= 1);
  int num_steps;
  istr >> token >> num_steps;
  assert (token == "num_steps");
  assert (num_steps >= 1);

  // create the board
  board = Board(cols,rows,num_steps);
  
  // read in the number of robots & number of program steps
  int num_robots;
  istr >> token >> num_robots;
  assert (token == "num_robots");
  assert (num_robots >= 1);
  
  for (int i = 0; i < num_robots; i++) {

    // read in each robot
    char symbol;
    istr >> token >> symbol;
    assert (token == "robot");
    int start_col, start_row;
    std::string direction;
    istr >> token >> start_col >> start_row >> direction;
    assert (token == "start");
    assert (start_col >= 0 && start_col < cols);
    assert (start_row >= 0 && start_row < rows);
    int goal_col, goal_row;
    istr >> token >> goal_col >> goal_row;
    assert (token == "goal");
    assert (goal_col >= 0 && goal_col < cols);
    assert (goal_row >= 0 && goal_row < rows);

    // read the commands into a list structure
    std::list<std::string> commands;
    for (int j = 0; j < num_steps; j++) {
      istr >> token;
      commands.push_back(token);      
    }

    // create a new robot and add to the rowlection
    Robot robot(symbol,&board,Position(start_col,start_row),direction,Position(goal_col,goal_row),commands);
    robots.push_back(robot);
  }
}

// ======================================================================================

// This function runs the programs stored in each robot on the shared board

// ASSIGNMENT: This function shows you how to use the provided code,
// but you'll need to change / rewrite this in order to rearrange the
// commands in each robot to find all solutions to the problem

void Run(const Board &board, std::vector<Robot> &robots) {
  
  // store all the ascii boards in a vector so we can print them out in a neat row
  std::vector< std::vector<std::string> > boards;

  // the starting point
  boards.push_back(board.print(robots));

  // loop through each step
  for (int i = 0; i < board.numSteps(); i++) {
    // move each robot
    for (unsigned int j = 0; j < robots.size(); j++) {
      robots[j].move();
    }
    // add the current state to the vector
    boards.push_back(board.print(robots));
  }  

  // print out a row of all the boards in a row
  for (unsigned int j = 0; j < boards[0].size(); j++) {
    for (unsigned int i = 0; i < boards.size(); i++) {
      std::cout << boards[i][j] << "   ";
    }
    std::cout << std::endl;
  }
}

// ======================================================================================



