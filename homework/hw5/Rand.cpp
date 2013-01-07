#include <algorithm>
#include <vector>

#include "MersenneTwister.h"

using namespace std;

void my_print(const vector<int> &random_nums)
{
  for (int i = 0; i < random_nums.size(); i++)
    cout << random_nums[i] << ' ';
  cout << endl;
}

int main()
{
  int n = 10;
  // create a vector of n numbers
  vector<int> ordered_nums;
  for (int i = 0; i < n; i++) {
    // populate the list with digits 0 to n-1
    ordered_nums.push_back(i);
  }

  int rand_num;
  // create the random number generator
  MTRand mt_rand;
  // create another vector to hold the numbers in random order
  vector<int> random_nums;
  for (int i = 0; i < n; i++) {
    /* Pick a random number from the remaining ordered number list and push it
     * back onto the random number list. */
    rand_num = mt_rand.randInt((int) ordered_nums.size()-1);
    random_nums.push_back(ordered_nums[rand_num]);
    ordered_nums.erase(find(ordered_nums.begin(), ordered_nums.end(), ordered_nums[rand_num]));
  }

  my_print(random_nums);

  return 0;
}
