#include <iostream>
#include <cmath>
#include <list>

using std::cout;
using std::endl;

#include "MultiLL.h"

int main() {

  // =======================================
  // CHECKPOINT 1

  // create a list of the sqrt of the first 10 integers
  MultiLL<double> a;
  for (int i = 0; i < 10; ++i)
    a.push_back(sqrt(i));


  // print out details of the list
  cout << "a.size() = " << a.size() << " --- should be 10" << endl;
  cout << "a.front() = " << a.front() << " --- should be 0.0 " << endl;
  cout << "a.back() = " << a.back() << " --- should be 3.0" << endl;
  MultiLL<double>::iterator itr;
  cout << "Elements = ";
  for (itr = a.begin(); itr != a.end(); ++itr)
    cout << " " << *itr;
  cout << endl;


  // clear out the list
  a.clear();


  // =======================================
  // CHECKPOINT 2


  // USING STL LIST
  std::list<int> b;
  for (int i = 0; i < 5; i++) {
    b.push_back(i);
  }

  // iterate backwards
  cout << "elements: ";
  std::list<int>::iterator itr2 = b.end();
  while (itr2 != b.begin()) {
    itr2--;
    cout << " " << *itr2;
  }
  cout << endl;



  // USING MultiLL
  MultiLL<int> c;
  for (int i = 0; i < 5; i++) {
    c.push_back(i);
  }

  // iterate backwards
  cout << "elements: ";
  MultiLL<int>::iterator itr3 = c.end();
  while (itr3 != c.begin()) {
    itr3--;
    cout << " " << *itr3;
  }
  cout << endl;


  return 0;
}
