#include "city.h"

#include <iostream>
#include <vector>
#include <algorithm>

// add the city if if it's not already a neighbor
bool City::addNeighbor(City *city) {
  if (find(neighbors.begin(), neighbors.end(), city) != neighbors.end()) {
    std::cerr << "Error: " << city->name << " is already a neighbor of " << this->name << std::endl;
    return false;
  }

  // neighbor is not already a neighbor, so add them to the vector
  neighbors.push_back(city);
}

// remove the city from it's vector of neighbors
bool City::removeNeighbor(City *city) {
  std::vector<City*>::iterator it;
  if ((it = find(neighbors.begin(), neighbors.end(), city)) == neighbors.end()) {
    std::cerr << "Error: " << city->name << " is not a neighbor of " << this->name << std::endl;
    return false;
  }

  // this city is a neighbor, so we can remove it
  neighbors.erase(it);
}

// tell each neighboring city to remove us from their vecotr of neighbors
void City::removeCityFromItsNeighbors() {
  for (int i = 0; i < neighbors.size(); i++)
    neighbors[i]->removeNeighbor(this);
}


bool operator==(const City &city1, const City &city2)
{
  return city1.getName() == city2.getName();
}
