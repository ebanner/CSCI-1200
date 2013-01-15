#include "city.h"

#include <iostream>
#include <vector>
#include <algorithm>

// add the city if if it's not already a neighbor
bool City::addNeighbor(City *city) {
  if (find(neighbors.begin(), neighbors.end(), city) != neighbors.end()) {
    //std::cerr << "Error: " << city->name << " is already a neighbor of " << this->name << std::endl;
    return false;
  }

  if (city->name == name) {
    //std::cerr << "City " << name << " cannot have " << city->name << " as its neighbor" << std::endl;
    return false;
  }

  //std::cerr << "Adding neighbor " << city->name << " to " << name << std::endl;
  // neighbor is not already a neighbor, so add them to the vector
  neighbors.push_back(city);
}

// remove the city from it's vector of neighbors
bool City::removeNeighbor(City *city) {
  std::vector<City*>::iterator it;
  if ((it = find(neighbors.begin(), neighbors.end(), city)) == neighbors.end()) {
    //std::cerr << "Error: " << city->name << " is not a neighbor of " << this->name << std::endl;
    return false;
  }

  //std::cerr << "Removing neighbor " << city->getName() << " from city " << name << std::endl;
  // this city is a neighbor, so we can remove it
  neighbors.erase(it);
}

// tell each neighboring city to remove us from their vecotr of neighbors
void City::removeCityFromItsNeighbors() {
  for (int i = 0; i < neighbors.size(); i++)
    neighbors[i]->removeNeighbor(this);
}

void City::sortNeighbors() {
  sort(neighbors.begin(), neighbors.end(), sort_by_name);
}

bool operator==(const City &city1, const City &city2) 
{
  return city1.getName() == city2.getName();
}

bool sort_by_name(const City *city1, const City *city2)
{
  return city1->getName() < city2->getName();
}
