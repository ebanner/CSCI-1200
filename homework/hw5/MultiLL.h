#ifndef MULTILL_H_
#define MULTILL_H_

#include <cassert>
#include <cstdlib>

#include "Node.h"
#include "list_iterator.h"

template <class T>
class MultiLL {
  public:
    MultiLL() : chrono_head_(NULL), chrono_tail_(NULL), sorted_head_(NULL), sorted_tail_(NULL), random_head_(NULL), size_(0) { }
    MultiLL(const MultiLL<T>& old) { this->copy_list(old); }
    ~MultiLL() { this->destroy_list(); }
    MultiLL& operator= (const MultiLL<T>& old);

    unsigned int size() const { return size_; }
    bool empty() const { return chrono_head_ == NULL; }
    void clear() { this->destroy_list(); }

    typedef list_iterator<T> iterator;
    iterator add(const T &value);
    iterator erase(iterator itr);
    iterator insert(iterator itr, T const& v);
    iterator begin_chronological() { return iterator(chrono_head_); }
    iterator begin_sorted() { return iterator(sorted_head_); }
    iterator begin_random() { return iterator(random_head_); }
    iterator end_chronological() { return iterator(NULL); }
    iterator end_sorted() { return iterator(NULL); }

  private:
    void copy_list(MultiLL<T> const &old);
    void destroy_list();

    // -- REPRESENTATION -- \\
    
    // chronological (insertion) ordering
    Node<T>* chrono_head_;
    Node<T>* chrono_tail_;

    // sorted (alphabetic) ordering
    Node<T>* sorted_head_;
    Node<T>* sorted_tail_;

    // random ordering
    Node<T>* random_head_;
    Node<T>* random_tail_;

    // number of nodes in the list
    unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
MultiLL<T>& MultiLL<T>::operator= (const MultiLL<T>& old) {
  if (&old != this) {
    this->destroy_list();
    this->copy_list(old);
  }
  return *this;
}


template <class T> 
typename MultiLL<T>::iterator MultiLL<T>::erase(iterator itr) {
  assert (size_ > 0);
  --size_;
  iterator result(itr.ptr_ -> next_);
  // One node left in the list.  
  if (itr.ptr_ == head_ && head_ == tail_) {
    head_ = tail_ = 0;
  }
  // Removing the head in a list with at least two nodes
  else if (itr.ptr_ == head_) {
    head_ = head_ -> next_;
    head_ -> prev_ = 0;
  }
  // Removing the tail in a list with at least two nodes
  else if (itr.ptr_ == tail_) {
    tail_ = tail_ -> prev_;
    tail_ -> next_ = 0;
  }
  // Normal remove
  else {
    itr.ptr_ -> prev_ -> next_ = itr.ptr_ -> next_;
    itr.ptr_ -> next_ -> prev_ = itr.ptr_ -> prev_;
  }
  delete itr.ptr_;
  return result;
}


// insert BEFORE the node indicated by the iterator and return an iterator to the new node
template <class T> 
typename MultiLL<T>::iterator MultiLL<T>::insert(iterator itr, T const& v) {
  ++size_ ;
  Node<T>* p = new Node<T>(v);
  p -> prev_ = itr.ptr_ -> prev_;
  p -> next_ = itr.ptr_;
  itr.ptr_ -> prev_ = p;
  if (itr.ptr_ == head_)
    head_ = p;
  else
    p -> prev_ -> next_ = p;
  return iterator(p);
}


template <class T> 
void MultiLL<T>::copy_list(MultiLL<T> const & old) {
  size_ = old.size_;
  // Handle the special case of an empty list.
  if (size_ == NULL) {
    chrono_head_ = chrono_tail_ = sorted_head_ = sorted_tail_ = random_head_ = NULL;
    return;
  }
  // Create a new head node. 
  head_ = new Node<T>(old.head_ -> value_);
  // tail_ will point to the last node created and therefore will move
  // down the new list as it is built
  tail_ = head_;
  // old_p will point to the next node to be copied in the old list
  Node<T>* old_p = old.head_ -> next_;
  // copy the remainder of the old list, one node at a time
  while (old_p) {
    tail_ -> next_ = new Node<T>(old_p -> value_);
    tail_ -> next_ -> prev_ = tail_;
    tail_ = tail_ -> next_;
    old_p = old_p -> next_;
  }
}


template <class T> 
void MultiLL<T>::destroy_list() {

  if (size_ == 0) { // special case: empty list
    return; // do nothing
  }

  // there's at least one node in the list
  Node<T> *present, *next_node;
  for (present = chrono_head_, next_node = chrono_head_->next_; next_node != NULL; present = next_node, next_node = next_node->chrono_next_)
    delete present;

  /* We will still be pointing at the last node when `next_node' is NULL, so we 
   * still have to delete the present node. */
  delete present;

  // point all heads and tails to NULL
  chrono_head_ = chrono_tail_ = sorted_head_ = sorted_tail_ = random_head_ = NULL;

  // empty list
  size_ = 0;
}

#endif
