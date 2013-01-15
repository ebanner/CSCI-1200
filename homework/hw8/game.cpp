#include <cstdlib>
#include <cassert>
#include <iostream>
#include <vector>
#include <string>

#include "MersenneTwister.h"
#include "person.h"
#include "city.h"
#include "graph.h"


// These functions are defined in evader.cpp and pursuer.cpp 
City* MY_EVADER_STRATEGY(const Person& p, const Graph& city_graph);
City* MY_PURSUER_STRATEGY(const Person& p, const Graph& city_graph);



City* NEVER_MOVES(const Person& p, const Graph& city_graph) {
  return p.getLocation();
}


City* MOVES_RANDOMLY(const Person& p, const Graph& city_graph) {
  // seed a random number generate that is only used by this function
  static MTRand mtrand;
  assert (p.getLocation() != NULL);
  const std::vector<City*>& neighbors = p.getLocation()->getNeighbors();
  // select a random number
  int r = mtrand.randInt(neighbors.size());
  if (r == 0) return p.getLocation();
  assert (r >= 1 && (unsigned int)r <= neighbors.size());
  return neighbors[r-1];
}


City* QUERY_USER(const Person& p, const Graph& city_graph) {
  assert (p.getLocation() != NULL);
  // print selections on the screen
  std::cout << "Where should " << p.getName() << " go next?" << std::endl;
  const std::vector<City*>& neighbors = p.getLocation()->getNeighbors();
  std::cout << "  (0) stay in " << p.getLocation()->getName() << std::endl;
  unsigned int i;
  for (i = 0; i < neighbors.size(); i++) 
    std::cout << "  (" << i+1 << ") " << neighbors[i]->getName() << std::endl;
  do { std::cin >> i; } while (i < 0 || i > neighbors.size());
  // now go there
  if (i == 0) return p.getLocation();
  assert (i > 0 && i <= neighbors.size());
  return neighbors[i-1];
}


// dispatch to the correct helper function
City* which_strategy(std::string s, const Person& p, const Graph& city_graph) {
  if (s == "NEVER_MOVES")
    return NEVER_MOVES(p,city_graph);
  if (s == "MOVES_RANDOMLY")
    return MOVES_RANDOMLY(p,city_graph);
  if (s == "QUERY_USER")
    return QUERY_USER(p,city_graph);
  if (s == "MY_EVADER_STRATEGY")
    return MY_EVADER_STRATEGY(p,city_graph);
  if (s == "MY_PURSUER_STRATEGY")
    return MY_PURSUER_STRATEGY(p,city_graph);
  std::cout << "ERROR! Unknown strategy: " << s << std::endl;
  exit(1);
}


bool Graph::tick(const std::string &evader_arg, const std::string &pursuer_arg) {
  std::cout << "TICK" << std::endl;

  // make choices
  City* ec = NULL;
  if (evader != NULL) {
    ec = which_strategy(evader_arg, *evader,*this);
    assert (ec != NULL); 
  }

  std::vector<City*> pc(pursuers.size());
  unsigned int i;
  for (i = 0; i < pursuers.size(); i++) {
    pc[i] = which_strategy(pursuer_arg, *pursuers[i],*this);
    assert (pc[i] != NULL);
  }

  // move them & check to see if evader is caught
  if (evader != NULL) evader->Move(ec);
  for (i = 0; i < pursuers.size(); i++) {
    pursuers[i]->Move(pc[i]);
    if (evader != NULL && pursuers[i]->getLocation() == evader->getLocation()) {
      std::cout << pursuers[i]->getName() << " has caught " << evader->getName() << " in " 
           << pursuers[i]->getLocation()->getName() << std::endl;
      // evader has been caught
      return false;
    }
  }
  
  // evader safe for another turn
  return true;
}
