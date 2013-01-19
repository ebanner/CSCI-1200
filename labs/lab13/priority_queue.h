#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>
using namespace std;


template <class T>
class priority_queue {
private:
  vector<T> m_heap;

  void swap(int child, int parent) {
    T temp = m_heap[parent];

    m_heap[parent] = m_heap[child];
    m_heap[child] = temp;
  }

public:
  priority_queue() {}

  priority_queue( vector<T> const& values ) {
  }

  const T& top() const {
    assert (! m_heap.empty());
    return m_heap[0]; 
  }

  void push( const T& entry ) {
    m_heap.push_back(entry); // add a new leaf
    percolate_up(m_heap.size()-1); // percolate the new leaf up
  }

  void percolate_up(int child) {
    int parent = (child-1) / 2;

    while (parent >= 0) { // while the child still has a parent
      if (m_heap[child] < m_heap[parent]) { // swap the nodes
        swap(parent, child);
        child = parent;
      } else break; // the heap is all in order
    }
  }

  void pop() {
    assert( !m_heap.empty() );
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }

  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap() {
    return this->check_heap(m_heap, 0);
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap(vector<T> &possible_heap) {
    return this->check_heap(possible_heap, 0);
  }

  bool check_heap(vector<T> &possible_heap, int node) {
    int left_child = 2*node + 1;
    int right_child = 2*node + 2;

    if (left_child >= m_heap.size() && right_child >= m_heap.size()) // no children
      return true;
    else if (right_child >= m_heap.size()) // left child, but no right
      return check_heap(possible_heap, left_child);
    else if (left_child >= m_heap.size()) // right child, but no left
      return check_heap(possible_heap, right_child);
    else { // two children -- check them both
      bool left_check = check_heap(possible_heap, left_child);
      bool right_check = check_heap(possible_heap, right_child);

      return left_check && right_check;
    }
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << endl;
  }
  
};


template <class T>
void heap_sort( vector<T> & v )
{
}

#endif
