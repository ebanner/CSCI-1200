#ifndef _graph_h_
#define _graph_h_

#include <iostream>
#include <vector>
#include <string>

class Person;
class City;


// A Graph object holds a vector of pointers to City objects, the
// cities in the graph.  Objects of type Person may be added to the
// graph in the role of evader or pursuer.  There is at most one
// evader at a time.  Person objects move along the links in the
// graph, one step per time tick.  If the evader and a pursuer are in
// the same city at the end of a tick, the game is over.

class Graph {

public:
  Graph() : evader(NULL) { };
  ~Graph() { this->destroy_graph(); };

  // ACCESSORS
  Person* getEvader() const { return evader; }
  const std::vector<Person*>& getPursuers() const { return pursuers; }

  // MODIFIERS
  // each return true if command was successful
  bool addCity(const std::string& city_name);
  bool removeCity(const std::string& city_name);
  bool addLink(const std::string& city_name1, const std::string& city_name2);
  bool removeLink(const std::string& city_name1, const std::string& city_name2);
  bool placePursuer(const std::string& person_name, const std::string& city_name);
  bool placeEvader(const std::string& person_name, const std::string& city_name);

  // Move the evader & pursuers.  Return false if the evader has been caught.
  bool tick(const std::string &evader_arg, const std::string &pursuer_arg); 

  // OUTPUT
  friend std::ostream& operator<<(std::ostream &ostr, const Graph &city_graph);

 private:  

  // helper function
  City *getCityWithName(const std::string& name) const;
  void destroy_graph();

  // ==============
  // REPRESENTATION
  std::vector<City*> cities;
  Person *evader;
  std::vector<Person*> pursuers;
};


#endif
