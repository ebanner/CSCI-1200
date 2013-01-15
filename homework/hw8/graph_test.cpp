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
  g.addCity("Albany");

  g.addLink("Ballston Lake", "Clifton Park");
  g.addLink("Potsdam", "Austin");
  g.addLink("Brooklyn", "Austin");

  std::cout << g << std::endl;

  g.removeLink("Austin", "Potsdam");

  std::cout << g << std::endl;

  g.placePursuer("Edward", "Potsdam");
  g.placePursuer("Noor", "Clifton Park");
  g.placeEvader("Xiaohu", "Albany");

  std::cout << g << std::endl;
}
