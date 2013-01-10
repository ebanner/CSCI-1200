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
 * I use the following notion to demonstrate the algorithm:
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
void permute_recurse(std::string permutation_in_progress, std::vector<char> chars)
{
  if (chars.size() == 0) {
    std::cout << permutation_in_progress << std::endl; // we've used all of the chars to build the permuation string
  } else { // there are still character we must use to build the complete permutation string

    /* If we could make a vector with an element removed on the fly, we
     * wouldn't need this temporary vector. */
    std::vector<char> copy; 

    for (int i = 0; i < chars.size(); i++) {
      copy = chars;
      copy.erase(std::find(copy.begin(), copy.end(), chars[i])); // erase the character from the vector
      permute_recurse(permutation_in_progress+chars[i], copy); // make the recursive call t
    }
  }
}

void permute(std::string permutee)
{
  std::vector<char> chars;
  for (int offset = 0; offset < permutee.length(); offset++)
    chars.push_back(permutee[offset]);

  permute_recurse(std::string(""), chars);
}

main()
{
  std::string permutee = "abc";

  permute(permutee);
}
