#ifndef NODE_H_
#define NODE_H_

#include <cstdlib>

template <class T>
class Node {
  public:
    // -- CONSTRUCTORS -- \\

    Node() : chrono_next_(NULL), chrono_prev_(NULL), sorted_next_(NULL), sorted_prev_(NULL), random_next_(NULL) { }
    Node(const T& v) : value_(v), chrono_prev_(NULL), sorted_next_(NULL), sorted_prev_(NULL), random_next_(NULL) { }

    // -- REPRESENTATION --\\

    T value_;

    // chronological (insertion)
    Node<T> *chrono_next_;
    Node<T> *chrono_prev_;

    // sorted (alphabetical)
    Node<T> *sorted_next_;
    Node<T> *sorted_prev_;

    // random
    Node<T> *random_next_;

};

#endif
