#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <string>
#include <vector>
#include <list>
#include "position.h"


// "Prototype" for the Board class so a Robot can store a pointer to the shared Board
class Board;

// The Robot class stores information about a single robot.  This
// includes the start & end position, the actions that are available
// for that robot.  The robot also stores a specific ordering of those
// actions, and the current position, orientation, and timestep in
// simulation of that program.  The Robot stores a pointer to the
// shared Board class.
class Robot {

public:

  // CONSTRUCTOR
  Robot(char symbol_, Board *board_, 
        const Position &start_position_, const std::string &start_direction_, 
        const Position &goal_position_, const std::list<std::string> &commands_);
  
  // ACCESSORS
  char getSymbol() const { return symbol; }
  const Position& getCurrentPosition() const { return current_position; }
  const std::string& getCurrentDirection() const { return current_direction; }
  const std::vector<std::string>& getProgram() const { return program; }
  const std::list<std::string>& getCommands() const { return commands; }

  // MODIFIERS
  void move();


private:

  // REPRESENTATION
  char symbol;

  // a pointer to the Board object
  Board *board;

  // information on the 'game rules' for this robot
  Position start_position;
  std::string start_direction;
  Position goal_position;

  // all of the actions that must be used by this robot
  std::list<std::string> commands;
  
  // the sequence of actions (current program) for this robot
  std::vector<std::string> program;

  // current state of the robot
  int current_step;
  Position current_position;
  std::string current_direction;
};


#endif
