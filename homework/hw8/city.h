#ifndef city_h_
#define city_h_

#include <vector>
#include <string>


// A City object stores its name and a vector of pointers to other
// City objects that it is linked to.  The links are bidirectional,
// which means that if city A is linked to city B then city B should
// also be linked to city A.

class City {

public:
  City(const std::string& n) : name(n) {}
  
  // ACCESSORS
  const std::string& getName() const { return name; }
  const std::vector<City*>& getNeighbors() const { return neighbors; }
  bool isNeighbor(City *city) const;

  // MODIFIERS
  bool addNeighbor(City *city);
  bool removeNeighbor(City *city);

  // Tell the neighboring cities to remove this City* from its vector of neighbors.
  void removeCityFromItsNeighbors();

  void sortNeighbors();

private: 

  // REPRESENTATION
  std::string name;
  std::vector<City*> neighbors;
};

bool operator==(const City &city1, const City &city2);

bool sort_by_name(const City *city1, const City *city2);

#endif
