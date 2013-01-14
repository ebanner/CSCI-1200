#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

/* Explanation of the algorithm:
 *
 * Base case: If the vector of characters is empty, then our job is done
 * because we've used all of the characters in the vector to build our
 * permutation string.
 *
 * Recursive case: There are still characters in the vector. Since there are
 * still characters in the vector, it means our permutation string is
 * incomplete. Why? Because if our permutation string was complete, then it
 * would have used all of the characters from the vector. So here's what we do:
 * For every character in the vector, we make a recursive call with the
 * following arguments: (1) the current character in the vector appended to the
 * permutation string and (2) the current character removed from the vector of
 * characters.
 *
 * I use the following notation to demonstrate the algorithm:
 *
 *            ``permute_recurse("A", ['B', 'C'])" == ``(A) [BC]"
 *
 * Example of the string ``ABC" permuted:
 *
 *                                     () [ABC]
 *
 *   |        (A) [BC]        |        (B) [AC]         |        (C) [AB]        |
 *
 *   | (AB) [C] -|- (AC) [B]  |  (BA) [C] -|- (BC) [A]  |  (CA) [B] -|- (CB) [A] |
 *
 *   | (ABC) [] -|- (ACB) []  |  (BAC) [] -|- (BCA) []  |  (CAB) [] -|- (CBA) [] |
 */
void permute_recurse(std::vector<std::string> permutation_in_progress, std::vector<std::string> commands, std::vector<std::vector<std::string> > &permutations)
{
  if (commands.size() == 0) {
    // add the permutation to the list of permutations
    permutations.push_back(permutation_in_progress);
  } else { // there are still characters we must use to build the complete permutation string

    /* If we could make a create vector with an element removed on the fly, we
     * wouldn't need this temporary vector. */
    std::vector<std::string> copy; 
    std::vector<std::string> temp;

    for (int i = 0; i < commands.size(); i++) {
      copy = commands;
      copy.erase(std::find(copy.begin(), copy.end(), commands[i])); // erase the character from the vector
      temp = permutation_in_progress;
      temp.push_back(commands[i]);
      permute_recurse(temp, copy, permutations); // make the recursive call
    }
  }
}

/* Wrapper function for `permute_recurse'. */
void permute(std::vector<std::string> commands, std::vector<std::vector<std::string> > &permutations)
{
  std::vector<std::string> permutation_in_progress;

  permute_recurse(permutation_in_progress, commands, permutations);
}

main()
{
  std::vector<std::string> commands;
  std::vector<std::vector<std::string> > permutations;

  commands.push_back("forward_1");
  commands.push_back("u_turn");
  commands.push_back("backward_2");
  commands.push_back("do_nothing");
  commands.push_back("forward_3");

  permute(commands, permutations);

  for (int i = 0; i < permutations.size(); i++) {
    for (int j = 0; j < permutations[0].size(); j++) {
      std::cout << permutations[i][j] << ' ';
    }
    std::cout << std::endl;
  }
}
