#ifndef LIST_ITERATOR_H_
#define LIST_ITERATOR_H_

#include <cstdlib>

#include "MultiLL.h"

enum type_t {chrono_, random_, sorted_};

// A "forward declaration" of this class is needed
template <class T> class MultiLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
  public:
    // constructors
    list_iterator() : ptr_(NULL) { }
    list_iterator(type_t t) : ptr_(NULL), type_(t) { }
    list_iterator(Node<T>* p, type_t t) : ptr_(p), type_(t) { }

    // copy constructor
    list_iterator(list_iterator<T> const& old) : ptr_(old.ptr_), type_(old.type_) { }

    // destructor
    ~list_iterator() { }

    // equal operator
    list_iterator<T> & operator=(const list_iterator<T> & old) 
    { ptr_ = old.ptr_; type_ = old.type_; return *this; }

    // dereferencing operator gives access to the value at the pointer
    T& operator*()  { return ptr_->value_;  }

    // increment & decrement operators
    list_iterator<T> & operator++() { // ++iterator
      if (type_ == chrono_)
        ptr_ = ptr_->chrono_next_; 
      else if (type_ == sorted_)
        ptr_ = ptr_->sorted_next_;
      else // type == random
        ptr_ = ptr_->random_next_;

      return *this;
    }

    list_iterator<T> operator++(int) { // iterator++
      // save the current iterator so we can return it later
      list_iterator<T> temp(*this);

      // advance to the next node depending on what type the iterator is
      if (type_ == chrono_)
        ptr_ = ptr_->chrono_next_; 
      else if (type_ == sorted_)
        ptr_ = ptr_->sorted_next_;
      else // type == random
        ptr_ = ptr_->random_next_;

      return temp;
    }

    list_iterator<T> & operator--() { // --iterator

      // we can only decrement chonological and sorted iterators
      assert(type_ == chrono_ || type_ == sorted_);
      
      if (type_ == chrono_)
        ptr_ = ptr_->chrono_prev_; 
      else // type_ == sorted_
        ptr_ = ptr_->sorted_prev_;

      return *this;
    }

    list_iterator<T> operator--(int) { // iterator--
      
      // we can only decrement chronological and sorted iterators
      assert(type_ == chrono_ || type_ == sorted_);

      // save the current iterator so we can return it later
      list_iterator<T> temp(*this);

      if (type_ == chrono_)
        ptr_ = ptr_->chrono_prev_; 
      else // type_ == sorted_
        ptr_ = ptr_->sorted_prev_;

      return temp;
    }

    friend class MultiLL<T>;

    // Compare the pointer and the type
    friend bool operator==(const list_iterator<T>& l, const list_iterator<T>& r)
      { return l.ptr_ == r.ptr_ && l.type_ == r.type_; }
    friend bool operator!=(const list_iterator<T>& l, const list_iterator<T>& r)
      { return l.ptr_ != r.ptr_ || l.type_ != r.type_; }

  private:
    // -- REPRESENTATION -- \\

    Node<T>* ptr_;    // ptr to node in the list

    // defines the iterator type (chrono, random, or sorted)
    type_t type_;

};

#endif
