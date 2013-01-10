#include <iostream>
#include <cassert>
#include <cstdlib>

#include "robot.h"
#include "board.h"


// CONSTRUCTOR
Robot::Robot(char symbol_, Board *board_, 
             const Position &start_position_, const std::string &start_direction_, 
             const Position &goal_position_, const std::list<std::string> &commands_) :
  symbol(symbol_), board(board_),
  start_position(start_position_), start_direction(start_direction_), 
  goal_position(goal_position_), commands(commands_) 
{
  // ASSIGNMENT: EDIT AS NEEDED

  // for now just use the commands in the provided order
  for (std::list<std::string>::iterator itr = commands.begin(); itr != commands.end(); itr++) {
    program.push_back(*itr);
  }

  // initialize the current position & direction variables
  current_step = 0;
  current_position = start_position;
  current_direction = start_direction;
}

// advance the robot one action forward in its program, updating the
// position, direction and step counter
void Robot::move() {

  assert (0 <= current_step && current_step < (int) program.size());

  if (program[current_step] == "rotate_right") {
    if (current_direction == "north") { current_direction = "east"; } 
    else if (current_direction == "east") { current_direction = "south"; } 
    else if (current_direction == "south") { current_direction = "west"; } 
    else { assert (current_direction == "west"); current_direction = "north"; } 
  }
  else if (program[current_step] == "rotate_left") {
    if (current_direction == "north") { current_direction = "west"; } 
    else if (current_direction == "east") { current_direction = "north"; } 
    else if (current_direction == "south") { current_direction = "east"; } 
    else { assert (current_direction == "west"); current_direction = "south"; } 
  }
  else if (program[current_step] == "forward_1") {
    if (current_direction == "north") { current_position = Position(current_position.col,current_position.row+1); }
    else if (current_direction == "east") { current_position = Position(current_position.col+1,current_position.row); }
    else if (current_direction == "south") { current_position = Position(current_position.col,current_position.row-1); }
    else { assert (current_direction == "west"); current_position = Position(current_position.col-1,current_position.row); }
  } 
  else if (program[current_step] == "forward_2") {
    if (current_direction == "north") { current_position = Position(current_position.col,current_position.row+2); }
    else if (current_direction == "east") { current_position = Position(current_position.col+2,current_position.row); }
    else if (current_direction == "south") { current_position = Position(current_position.col,current_position.row-2); }
    else { assert (current_direction == "west"); current_position = Position(current_position.col-2,current_position.row); }
  } 
  else if (program[current_step] == "forward_3") {
    if (current_direction == "north") { current_position = Position(current_position.col,current_position.row+3); }
    else if (current_direction == "east") { current_position = Position(current_position.col+3,current_position.row); }
    else if (current_direction == "south") { current_position = Position(current_position.col,current_position.row-3); }
    else { assert (current_direction == "west"); current_position = Position(current_position.col-3,current_position.row); }
  } 
  else if (program[current_step] == "backward_1") {
    if (current_direction == "north") { current_position = Position(current_position.col,current_position.row-1); }
    else if (current_direction == "east") { current_position = Position(current_position.col-1,current_position.row); }
    else if (current_direction == "south") { current_position = Position(current_position.col,current_position.row+1); }
    else { assert (current_direction == "west"); current_position = Position(current_position.col+1,current_position.row); }
  } 
  else if (program[current_step] == "backward_2") {
    if (current_direction == "north") { current_position = Position(current_position.col,current_position.row-2); }
    else if (current_direction == "east") { current_position = Position(current_position.col-2,current_position.row); }
    else if (current_direction == "south") { current_position = Position(current_position.col,current_position.row+2); }
    else { assert (current_direction == "west"); current_position = Position(current_position.col+2,current_position.row); }
  } 
  else if (program[current_step] == "backward_3") {
    if (current_direction == "north") { current_position = Position(current_position.col,current_position.row-3); }
    else if (current_direction == "east") { current_position = Position(current_position.col-3,current_position.row); }
    else if (current_direction == "south") { current_position = Position(current_position.col,current_position.row+3); }
    else { assert (current_direction == "west"); current_position = Position(current_position.col+3,current_position.row); }
  } 
  else if (program[current_step] == "u_turn") {
    if (current_direction == "north") { current_direction = "south"; }
    else if (current_direction == "east") { current_direction = "west"; }
    else if (current_direction == "south") { current_direction = "north"; }
    else { assert (current_direction == "west"); current_direction = "east"; }
  }
  else if (program[current_step] == "do_nothing") {
    // do nothing
  }
  else {
    std::cerr << "unknown command " << program[current_step] << std::endl;
    exit(1);
  }

  current_step++;

  // ASSIGNMENT: Also, you'll need to check for collisions between the
  // robot, the walls, and other robots.
}
