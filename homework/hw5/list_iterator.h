#ifndef LIST_ITERATOR_H_
#define LIST_ITERATOR_H_

#include <cstdlib>

#include "MultiLL.h"
#include "common.h"

// A "forward declaration" of this class is needed
template <class T> class MultiLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
  public:
    list_iterator() : ptr_(NULL) {}
    list_iterator(Node<T>* p) : ptr_(p) {}
    list_iterator(list_iterator<T> const& old) : ptr_(old.ptr_) {}
    ~list_iterator() {}

    // functions to use to invoke constructors with the correct enum type
    type_t random() { return random_; }
    type_t chrono() { return chrono_; }
    type_t sorted() { return sorted_; }

    list_iterator<T> & operator=(const list_iterator<T> & old) { 
      ptr_ = old.ptr_;  return *this; }

    // dereferencing operator gives access to the value at the pointer
    T& operator*()  { return ptr_->value_;  }

    // increment & decrement operators
    list_iterator<T> & operator++() { 
      ptr_ = ptr_->next_; 
      return *this;
    }
    list_iterator<T> operator++(int) {
      list_iterator<T> temp(*this);
      ptr_ = ptr_->next_;
      return temp;
    }
    list_iterator<T> & operator--() {
      ptr_ = ptr_->prev_;
      return *this;
    }
    list_iterator<T> operator--(int) {
      list_iterator<T> temp(*this);
      ptr_ = ptr_->prev_;
      return temp;
    }

    friend class MultiLL<T>;

    // Comparions operators are straightforward
    friend bool operator==(const list_iterator<T>& l, const list_iterator<T>& r) {
      return l.ptr_ == r.ptr_; }
    friend bool operator!=(const list_iterator<T>& l, const list_iterator<T>& r) {
      return l.ptr_ != r.ptr_; }

  private:
    // -- REPRESENTATION -- \\

    Node<T>* ptr_;    // ptr to node in the list

    // defines the iterator type (chrono, random, or sorted)
    type_t type;

};

#endif
