#include <iostream>

#include "dslist.h"

using namespace std;

void my_print(dslist<int> &dlist)
{
  for (dslist<int>::iterator itr = dlist.begin(); itr != dlist.end(); itr++)
    cout << *itr << ' ';
  cout << endl;
}

int main()
{
  dslist<int> dlist;
  cout << "dlist: ";
  my_print(dlist);
  cout << endl;

  dlist.push_back(42);
  dlist.push_front(67);

  dslist<int> elist(dlist);
  
  cout << "elist: ";
  my_print(elist);
  elist.clear();
  cout << "clearning elist..." << endl;
  cout << "elist: ";
  my_print(elist);

  cout << "dlist: ";
  my_print(dlist);

  dlist.pop_front();
  dlist.pop_front();
  //dlist.pop_back();

  my_print(dlist);

  return 0;
}
