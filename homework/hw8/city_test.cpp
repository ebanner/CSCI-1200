#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

#include "city.h"

int main()
{
  City city1("Potsdam");
  City city2("Canton");
  City city3("St. Lawrence");
  City city4("Ballston Lake");
  City city5("Clifton Park");

  assert (city1.getName() == "Potsdam");
  assert (city2.getName() == "Canton");
  assert (city3.getName() == "St. Lawrence");
  assert (city4.getName() == "Ballston Lake");
  assert (city5.getName() == "Clifton Park");

  city1.addNeighbor(&city2);
  city1.addNeighbor(&city3);
  city1.addNeighbor(&city4);
  // try to add a duplicate neighbor
  city1.addNeighbor(&city4);
  city1.addNeighbor(&city5);
  // add yourself as a neighbor
  city1.addNeighbor(&city5);

  std::vector<City*> cities;
  cities.push_back(&city2);
  cities.push_back(&city3);
  cities.push_back(&city4);
  cities.push_back(&city5);

  assert (city1.getNeighbors() == cities);

  city1.removeNeighbor(&city4);
  city1.removeNeighbor(&city4);
  std::vector<City*>::iterator it = find(cities.begin(), cities.end(), &city4);
  cities.erase(it);
  
  assert (city1.getNeighbors() == cities);

  city2.removeCityFromItsNeighbors();
  city3.removeCityFromItsNeighbors();
  city4.removeCityFromItsNeighbors();
  city5.removeCityFromItsNeighbors();

  for (it = cities.begin(); it == cities.end(); it++)
    cities.erase(it);

  assert (city1.getNeighbors() == cities);

  std::cout << "Successfully passed all tests. You should be proud!" << std::endl;
}
