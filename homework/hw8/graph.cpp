#include <vector>
#include <algorithm>

bool Graph::addCity(const std::string& city_name) {
  City *city = getCityWithName(city_name);



bool removeCity(const std::string& city_name);
bool addLink(const std::string& city_name1, const std::string& city_name2);
bool removeLink(const std::string& city_name1, const std::string& city_name2);
bool placePursuer(const std::string& person_name, const std::string& city_name);
bool placeEvader(const std::string& person_name, const std::string& city_name);


City* City::getCityWithName(const std::string &name) const {
  for (int i = 0; i < cities.size(); i++)
    if (cities[i]->getName() == name)
      return cities[i];

  // didn't find the city
  return NULL;
}

