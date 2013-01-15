#include "person.h"
#include "city.h"

#include <iostream>
#include <vector>

void Person::Move(City *city) {
  // ensure that this city is not NULL
  if (! city) {
    std::cerr << "Attempted to move person " << name << " to a NULL city" << std::endl;
    return;
  }

  // ensure that this city is a neighbor of the city the pursuer is currently at
  std::vector<City*>::const_iterator it;
  for (it = location->getNeighbors().begin(); it != location->getNeighbors().end(); it++) {
    if (*it == city) {
      location = city;
      std::cerr << "Successfully moved person " << name << " to location " << city->getName() << std::endl;
      return;
    }
  }

  // the city is not a neighbor of the pursuer's current location
  std::cerr << city->getName() << " is not a neighbor of pursuer " << name << 
    "'s current location " << location->getName() << std::endl;
}
