#include "graph.h"
#include "city.h"
#include "person.h"

#include <iostream>
#include <vector>

bool Graph::addCity(const std::string& city_name) {
  City *city = getCityWithName(city_name);

  // a NULL city means the city doesn't yet exist, so add it
  if (city == NULL) {
    std::cerr << "Added city " << city_name << std::endl;
    cities.push_back(new City(city_name));
    return true;
  } else { // the city was already exists
    std::cerr << "City " << city->getName() << " already exists." << std::endl;
    return false;
  }
}

// remove city if it already exists
bool Graph::removeCity(const std::string& city_name) {
  City *city = getCityWithName(city_name);

  if (city != NULL) { // city already exists, so remove it
    for (std::vector<City*>::iterator it = cities.begin(); it != cities.end(); it++) {
      if (*it == city) {
        std::cerr << "Deleting city " << city->getName() << std::endl;
        // delete all links to this city
        city->removeCityFromItsNeighbors();
        
        // remove the city from the vector of all cities
        cities.erase(it);

        // destory the city -- never to be seen again
        delete city;
        std::cerr << "City " << city->getName() << " is gone." << std::endl;

        return true;
      }
    }
  } else { // we can't remove a city that doesn't exist
    std::cerr << "Cannot remove " << city->getName() << ": it does not exist" << std::endl;
    return false;
  }

  std::cerr << "We should never get down here!" << std::cerr;
  return false;
}

// add links between the two cities
bool Graph::addLink(const std::string& city_name1, const std::string& city_name2) {
  City *city1 = getCityWithName(city_name1);
  City *city2 = getCityWithName(city_name2);

  bool city1_success= city1->addNeighbor(city2);
  bool city2_success = city2->addNeighbor(city1);

  return city1_success && city2_success;
}

// delete the links between the two cities
bool Graph::removeLink(const std::string& city_name1, const std::string& city_name2) {
  City *city1 = getCityWithName(city_name1);
  City *city2 = getCityWithName(city_name2);

  bool city1_success = city1->removeNeighbor(city2);
  bool city2_success = city2->removeNeighbor(city1);

  return city1_success && city2_success;
}

bool Graph::placePursuer(const std::string& person_name, const std::string& city_name) {
  // ensure the pursuer does not already exist
  for (int i = 0; i < pursuers.size(); i++) {
    if (pursuers[i]->getName() == person_name) {
      std::cerr << "Pursuer " << person_name << " already exists." << std::endl;
      return false;
    }
  }

  City *city = getCityWithName(city_name);
  // ensure the city exists
  if (city == NULL) {
    std::cerr << "Attempted to add pursuer " << person_name << " to " << city_name << 
      ", but " << city_name << " has not been realized as a nation." << std::endl;
    return false;
  }

  std::cerr << "Placing pursuer " << person_name << " at city " << city_name << std::endl;
  // pursuer does not exist, so add the pursuer to the list of pursuers
  pursuers.push_back(new Person(person_name, city));
}

bool Graph::placeEvader(const std::string& person_name, const std::string& city_name) {
  // ensure the evader does not already exist
  if (evader != NULL) {
    std::cerr << "An evader already resides at " << evader->getLocation() << std::endl;
    return false;
  }

  City *city = getCityWithName(city_name);
  // ensure the city exists
  if (city == NULL) {
    std::cerr << "Attempted to add evader " << person_name << " to " << city_name << 
      ", but " << city_name << " has not been realized as a nation." << std::endl;
    return false;
  }

  std::cerr << "Placing evader " << person_name << " at city " << city_name << std::endl;
  // create the evader
  evader = new Person(person_name, city);
}


City* Graph::getCityWithName(const std::string &name) const {
  for (int i = 0; i < cities.size(); i++)
    if (cities[i]->getName() == name)
      return cities[i];

  // didn't find the city
  return NULL;
}


/* For each city in the graph, output all of the cities that city is linked to.
 * Output the location of evaders and pursuers. */
std::ostream& operator<<(std::ostream &ostr, const Graph &city_graph)
{
  std::vector<City*> neighbors;
  for (int i = 0; i < city_graph.cities.size(); i++) {
    std::cout << "Cities " << city_graph.cities[i] << " are linked to:" << std::endl;
    neighbors = city_graph.cities[i]->getNeighbors();
    for (int j = 0; j < neighbors.size(); j++) {
      std::cout << neighbors[j] << std::endl;
    }
  }

  std::cout << "Evader " << city_graph.evader << " is at city " << city_graph.evader->getLocation();

  for (int i = 0; i < city_graph.pursuers.size(); i++) {
    std::cout << "Pursuer " << city_graph.pursuers[i]->getName() << 
      " is at city " << city_graph.pursuers[i]->getLocation() << std::endl;
  }
}

void Graph::destroy_graph()
{
  // delete the cities
  for (int i = 0; i < cities.size(); i++)
    delete cities[i];

  if ( evader )
    delete evader;

  for (int i = 0; i < pursuers.size(); i++)
    delete pursuers[i];
}
