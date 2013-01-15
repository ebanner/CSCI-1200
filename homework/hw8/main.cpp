#include <iostream>
#include <fstream>
#include <algorithm>

#include "person.h"
#include "city.h"
#include "graph.h"


int main(int argc, char* argv[]) {
  
  // Parse arguments
  if (argc != 4) {
    std::cout << "Wrong number of arguments to play game.\n";
    std::cout << "Usage:  " << argv[0] << 
      " <graph-file> <evader-strategy> <pursuer-strategy>" << std::endl;
    std::cout << "   <evader-strategy>  = NEVER_MOVES, MOVES_RANDOMLY, QUERY_USER, or MY_EVADER_STRATEGY" << std::endl;
    std::cout << "   <pursuer-strategy> = NEVER_MOVES, MOVES_RANDOMLY, QUERY_USER, or MY_PURSUER_STRATEGY" << std::endl;
    return 1;
  }

  // Open and check the input stream
  std::ifstream in_str(argv[1]);
  if (!in_str) {
    std::cout << "Bad file name\n";
    return 1;
  }

  // The main graph object
  Graph city_graph;

  std::string request, name1, name2;
  int count;
  
  // While there are more requests, determine the type of request and handle it. 
  while (in_str >> request) {
    if (request == "add-city") {
      in_str >> name1;
      if (city_graph.addCity(name1))
        std::cout << "Added city " << name1 << std::endl;
      else
        std::cout << "Error trying to add city " << name1 << std::endl;
    } else if (request == "remove-city") {
      in_str >> name1;
      if (city_graph.removeCity(name1))
        std::cout << "Removed city " << name1 << std::endl;
      else 
        std::cout << "Error trying to remove city " << name1 << std::endl;
    } else if (request == "add-link") {
      in_str >> name1 >> name2;
      if (city_graph.addLink(name1, name2)) 
        std::cout << "Linked cities " << name1 << " and " << name2 << std::endl;
      else
        std::cout << "Error trying to link cities " << name1 << " and " << name2 << std::endl;
    } else if (request == "remove-link") {
      in_str >> name1 >> name2;
      if (city_graph.removeLink(name1, name2))
        std::cout << "Removed link from cities " << name1 << " and " << name2 << std::endl;
      else
        std::cout << "Error trying to remove link from cities " << name1 << " and " << name2 << std::endl;
    } else if (request == "place-evader") {
      in_str >> name1 >> name2;
      if (city_graph.placeEvader(name1,name2))
        std::cout << "Placed evader " << name1 << " in city " << name2 << std::endl;
      else
        std::cout << "Error trying to place evader " << name1 << " in city " << name2 << std::endl;
    } else if (request == "place-pursuer") {
      in_str >> name1 >> name2;
      if (city_graph.placePursuer(name1,name2))
        std::cout << "Placed pursuer " << name1 << " in city " << name2 << std::endl;
      else 
        std::cout << "Error trying to place pursuer " << name1 << " in city " << name2 << std::endl;
    } else if (request == "print") {
      city_graph.sortCities();
      std::cout << city_graph;
    } else if (request == "tick") {
      in_str >> count;
      while (count > 0) {
        if (!city_graph.tick(argv[2],argv[3])) {
          std::cout << "Evader loses" << std::endl;
          return 0; // game over
        }
        count--;
      }
    } else {
      std::cout << "Illegal input: " << request << std::endl;
    }
  }

  if (city_graph.getEvader() != NULL) 
    std::cout << "Evader wins" << std::endl;
  else 
    std::cout << "No evader in graph to capture" << std::endl;

  // The memory allocated for the graph is deleted when it goes out of scope.
  return 0;
}
