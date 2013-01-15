#ifndef _person_h_
#define _person_h_
 
#include <string>

class City;


// A Person object stores its name and a pointer to the city where it is 
// currently located.

class Person {

public:
  
  // CONSTRUCTOR
  Person(const std::string& n, City *c) :  name(n), location(c) {}

  // ACCESSORS
  const std::string& getName() const { return name; }
  City* getLocation() const { return location; }

  // MODIFIER
  // move the person to the specified city
  void Move(City *city);

private:
  // REPRESENTATION
  std::string name;
  City* location;
};


#endif
