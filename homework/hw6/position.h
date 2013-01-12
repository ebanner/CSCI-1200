#ifndef _POSITION_H_
#define _POSITION_H_

#include <iostream>

// The Position class stores the coordinates of a Robot on a Board
class Position {
public:
  Position(int c=0, int r=0) : col(c), row(r) {}
  int col;
  int row;
};


// helper functions for Position objects
// Note: the inline keyword allows you to implement a non member function 
// in a .h file without compile errors about "multiple redefinition"
inline bool operator==(const Position &a, const Position &b) { 
  return (a.row == b.row && a.col == b.col); }
inline std::ostream& operator<<(std::ostream &ostr, const Position &a) { 
  ostr << "(" << a.row << "," << a.col << ")" << std::endl; return ostr; }

#endif
