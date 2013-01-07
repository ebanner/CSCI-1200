#ifndef MULTILL_H_
#define MULTILL_H_

#include <cassert>
#include <cstdlib>

#include "Node.h"
#include "list_iterator.h"

template <class T>
class MultiLL {
  public:
    // constructor
    MultiLL() : chrono_head_(NULL), chrono_tail_(NULL), sorted_head_(NULL), sorted_tail_(NULL), random_head_(NULL), size_(0) { }
    MultiLL(const MultiLL<T>& old) { this->copy_list(old); }
    ~MultiLL() { this->destroy_list(); }
    MultiLL& operator= (const MultiLL<T>& old);

    unsigned int size() const { return size_; }
    bool empty() const { return chrono_head_ == NULL; }
    void clear() { this->destroy_list(); }

    typedef list_iterator<T> iterator;
    void add(const T &value);
    iterator erase(iterator itr);

    // return iterator to the beginning of the list
    iterator begin_chronological() { return iterator( chrono_head_, chrono_ ); }
    iterator begin_sorted() { return iterator( sorted_head_, sorted_ ); }
    iterator begin_random() { return iterator( random_head_, random_ ); }

    // return an iterator pointing to NULL, but the correct type
    iterator end_chronological() { return iterator(chrono_); }
    iterator end_sorted() { return iterator(sorted_); }

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

  // save an iterator to the next node to return
  iterator temp(itr);
  temp++;

  if (itr.ptr_ == chrono_head_ && chrono_head_ == chrono_tail_) {
    // special case: only one node in the list
    chrono_head_ = chrono_tail_ = NULL;
  } else { // general case: more than one node in the list 

    // -- Fix chronological links --
    if (itr.ptr_ == chrono_head_) { // removing the chronological head
      // point the chronological head to the next node
      chrono_head_ = chrono_head_ -> chrono_next_;
      chrono_head_ -> chrono_prev_ = NULL;
    } else if (itr.ptr_ == chrono_tail_) { // removing the chronological tail
      // point the chronological tail to the next-to-last node
      chrono_tail_ = chrono_tail_ -> chrono_prev_;
      chrono_tail_ -> chrono_next_ = NULL;
    } else { // easy case: just fix the chronological links
      itr.ptr_ -> chrono_prev_ -> chrono_next_ = itr.ptr_ -> chrono_next_;
      itr.ptr_ -> chrono_next_ -> chrono_prev_ = itr.ptr_ -> chrono_prev_;
    }
  }

  // -- Fix sorted links --
  if (itr.ptr_ == sorted_head_ && sorted_head_ == sorted_tail_) { 
    sorted_head_ = sorted_tail_ = NULL; // special case: just one node
  } else { // more than one node in the list
      if (itr.ptr_ == sorted_head_) { // removing the sorted head
        // move the sorted head up one node
        sorted_head_ = sorted_head_ -> sorted_next_;
        sorted_head_ -> sorted_prev_ = NULL;
      } else if (itr.ptr_ == sorted_tail_) { // removing the sorted tail
        // move the sorted tail back one node
        sorted_tail_ = sorted_tail_ -> sorted_prev_;
        sorted_tail_ -> sorted_next_ = NULL;
      } else { // general case -- just fix the sorted links
        itr.ptr_ -> sorted_prev_ -> sorted_next_ = itr.ptr_ -> sorted_next_;
        itr.ptr_ -> sorted_next_ -> sorted_prev_ = itr.ptr_ -> sorted_prev_;
      }
  }

  // -- Fixed random links --
  if (itr.ptr_ == random_head_) // one element in the list -- just move the random head up
    random_head_ = random_head_ -> random_next_;
  } else { // two or more nodes

    /* Our plan in to get the node just before the node we wish to remove. Then
     * we will link that node to the node after the one we wish to remove. */
    Node<T> *present, *next;
    present = random_head_;
    next = present->random_next_;  
    for ( ; next != itr.ptr_; present = next, next = next->random_next_)
      ; // ride along until you get one before the node you want to remove

    /* Have the node before the one we wish to remove point to the node after
     * the node we wish to remove. */
    present->random_next_ = next->random_next_;

  }

  delete itr.ptr_;

  return temp;
}

template <class T>
void MultiLL<T>::add(const T &value) {
  // create the node we wish to add
  Node<T>* new_node = new Node<T>(v);

  if (size_ == 0) { // empty list
    // point everything to the new new_node
    chrono_head_ = chrono_tail_ = new_node;
    sorted_head_ = sorted_tail_ = new_node;
    random_head_ = new_node;
    size_++;

    return; // we're done -- easy!

  } else { // at least one new_node in the list -- hard...
    // The new node becomes the new chronological tail node
    new_node->chrono_prev_ = chrono_tail;
    chrono_tail_->chrono_next_ = new_node;
    chrono_tail_ = new_node;
    
    /* The strategy for inserting our new node in sorted order is as follows:
     * Start at the sorted head node and work our way down the sorted nodes,
     * comparing each node's value to the value of the node we are trying to
     * insert. The second we get to a node such that the value of our new node
     * is <= the value of that node, then we will insert our new node BEFORE
     * this node.
     *
     * This process is complicated by the fact that if we are adding a node
     * that is goes at the end of the sorted list, then the value of our new
     * node will never be <= the value of any node. This is the reason for the
     * obfuscated if-else purgatory below. */
    Node<T>* temp_node = sorted_head_;
    for (temp_node = sorted_head_; temp_node != sorted_tail_; temp_node = temp_node->next_sorted_) {
      // ride along until we get to a node we're <= to
      if (temp_node->value_ <= temp_node)
        break;
    }

    /* At this point, our new node's value is <= `temp_node' OR we got all the
     * way to sorted end. */
    if (temp_node == sorted_head_ && temp_node == sorted_tail_) { // special case: size 1
      // compare against lone node, insert node, and fix head and tail
      if (value <= sorted_head_->value) {
        // insert node before the head and fix the sorted head pointer
        new_node->sorted_next_ = sorted_head_;
        sorted_head_->sorted_prev_ = new_node;
        sorted_head_ = new_node;
      } else { // value > head node -- insert after sorted head node and fix sorted tail node
        new_node->sorted_prev_ = sorted_tail_;
        sorted_tail->sorted_next_ = new_node;
        sorted_tail_ = new_node;
      }
    } else if (temp_node == sorted_head) {
        /* New node must go before the head pointer becuase the new pointer's
         * value <= head node's value AND there is more than one node in the
         * list. Insert node before the sorted head and fix `sorted_head_'
         * pointer. */
        new_node->sorted_next_ = sorted_head_;
        sorted_head_->sorted_prev_ = new_node;
        sorted_head_ = new_node;
    } else if (temp_node == sorted_tail) {
      /* We need to check whether the new node should go before the sorted tail
       * or after the sorted tail (and become the new sorted tail). */
      if (value <= sorted_tail_->value) { 
        /* Insert before the tail node -- no need to fix the sorted tail
         * pointer.
         * 
         * Fix the new node's links. */
        new_node->sorted_prev_ = sorted_tail_->sorted_prev_;
        new_node->sorted_next_ = sorted_tail_;
        // Fix the neighbors of the new node.
        sorted_tail_->sorted_prev_->sorted_next_ = new_node;
        sorted_tail_->sorted_prev = new_node;
      } else { // value > sorted tail -- new node becomes new sorted tail
        new_node->sorted_prev_ = sorted_tail_;
        sorted_tail->sorted_next_ = new_node;
        sorted_tail_ = new_node;
      }
    } else { // no heads nor tails involved -- just fix sorted links
      /* Recall--`temp_node' is pointing to the node that the new node needs
       * to be inserted before. 
       *
       * Fix the new node's links. */
      new_node->sorted_prev_ = temp_node->sorted_prev_;
      new_node->sorted_next_ = temp_node;
      // Fix the neighbors' links
      temp_node->sorted_prev_->sorted_next_ = new_node;
      temp_node->sorted_prev_ = new_node;
    }
  }
}

/*
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
*/

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
