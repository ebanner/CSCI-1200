#include <iostream>

#include "graph.h"

int main()
{
  Graph g;

  g.addCity("Ballston Lake");
  g.addCity("Clifton Park");
  g.addCity("Brooklyn");
  g.addCity("Potsdam");
  g.addCity("Austin");

  g.addLink("Ballston Lake", "Clifton Park");
  g.addLink("Potsdam", "Austin");
  g.addLink("Brooklyn", "Austin");

  std::cout << g << std::endl;
}
