// Partial implementation of binary-tree based set class similar to std::set.  
// The iterator increment & decrement operations have been omitted.
#ifndef ds_set_h_
#define ds_set_h_
#include <iostream>
#include <utility>
#include <list>

// -------------------------------------------------------------------
// TREE NODE CLASS 
template <class T>
class TreeNode {
public:
  TreeNode() : left(NULL), right(NULL) {}
  TreeNode(const T& init) : value(init), left(NULL), right(NULL) {}
  T value;
  TreeNode* left;
  TreeNode* right;
};

template <class T> class ds_set;

// -------------------------------------------------------------------
// TREE NODE ITERATOR CLASS
template <class T>
class tree_iterator {
public:
  tree_iterator() : ptr_(NULL) {}
  tree_iterator(TreeNode<T>* p) : ptr_(p) {}
  tree_iterator(const tree_iterator& old) : ptr_(old.ptr_) {}
  ~tree_iterator() {}
  tree_iterator& operator=(const tree_iterator& old) { ptr_ = old.ptr_;  return *this; }
  // operator* gives constant access to the value at the pointer
  const T& operator*() const { return ptr_->value; }
  // comparions operators are straightforward
  friend bool operator== (const tree_iterator& lft, const tree_iterator& rgt) { return lft.ptr_ == rgt.ptr_; }
  friend bool operator!= (const tree_iterator& lft, const tree_iterator& rgt) { return lft.ptr_ != rgt.ptr_; }
  // increment & decrement will be discussed in Lecture 17 and Lab 11

private:
  // representation
  TreeNode<T>* ptr_;
};

// -------------------------------------------------------------------
// CS2 SET CLASS
template <class T>
class ds_set {
public:
  ds_set() : root_(NULL), size_(0) {}
  ds_set(const ds_set<T>& old) : size_(old.size_) { 
    root_ = this->copy_tree(old.root_); }
  ~ds_set() { this->destroy_tree(root_);  root_ = NULL; }
  ds_set& operator=(const ds_set<T>& old) {
    if (&old != this) {
      this->destroy_tree(root_);
      root_ = this->copy_tree(old.root_);
      size_ = old.size_;
    }
    return *this;
  }

  typedef tree_iterator<T> iterator;

  int size() const { return size_; }
  bool operator==(const ds_set<T>& old) const { return (old.root_ == this->root_); }

  // FIND, INSERT & ERASE
  iterator find(const T& key_value) { return find(key_value, root_); }
  std::pair< iterator, bool > insert(T const& key_value) { return insert(key_value, root_); }
  int erase(T const& key_value) { return erase(key_value, root_); }
  
  // OUTPUT & PRINTING
  friend std::ostream& operator<< (std::ostream& ostr, const ds_set<T>& s) {
    s.print_in_order(ostr, s.root_);
    return ostr;
  }
  void print_as_sideways_tree(std::ostream& ostr) const {
    print_as_sideways_tree(ostr, root_, 0); }

  // ITERATORS
  iterator begin() const { 
    if (!root_) return iterator(NULL);
    TreeNode<T>* p = root_;
    while (p->left) p = p->left;
    return iterator(p);
  }
  iterator end() const { return iterator(NULL); }

private:
  // REPRESENTATION
  TreeNode<T>* root_;
  int size_;

  // PRIVATE HELPER FUNCTIONS
  TreeNode<T>* copy_tree(TreeNode<T>* old_node) {
    if (old_node == NULL) {
      return NULL;
    } else {
      // create a copy of the current node
      TreeNode<T> *new_node = new TreeNode<T>(old_node->value);

      // make copies of all of the nodes to the left and link
      new_node->left = copy_tree(old_node->left);
      // make copies of all of the nodes to the right and link
      new_node->right = copy_tree(old_node->right);

      /* Remember, YOU (new_node) are a node that someone is counting on! You
       * must return a reference to yourself (new_node), so you can be
       * someone's left or right (or in the case of the root, you're returning
       * a pointer to the root node). */
      return new_node;
    }
  }

  void destroy_tree(TreeNode<T>* p) { /* Implemented in Lecture 17 */  }

  /*
  iterator find(const T& key_value, TreeNode<T>* p) {
    if (!p) return iterator(NULL);
    if (p->value > key_value)
      return find(key_value, p->left);
    else if (p->value < key_value)
      return find(key_value, p->right);
    else
      return iterator(p);
  }
  */

  /* Breadth-first iterative `find()' implementation. */
  iterator find(const T &key_value, TreeNode<T> *root) {
    /*
    std::list<TreeNode<T> *> nodes;
    std::list<TreeNode<T> *> temp_nodes;

    // special case: root node hold the value
    if (root->value == key_value)
      return iterator(root);

    /* 
    // in our breadth-first search, the root is the first node searched
    nodes.push_back(root);

    typename std::list<TreeNode<T> *>::iterator it;
    while (nodes.size() > 0) {
      for (it = nodes.begin(); it != nodes.end(); it++) {
        // We haven't found the node with the value yet, so add all the
        // children of current nodes to the vector to check.
        if ((*it)->left != NULL)
          temp_nodes.push_back((*it)->left);
        if ((*it)->right != NULL)
          temp_nodes.push_back((*it)->right);
      }

      nodes = temp_nodes;
      temp_nodes.clear();

      // check to see if any of the children have the value
      for (it = nodes.begin(); it != nodes.end(); it++)
        if ((*it)->value == key_value)
          return iterator(*it);
    }

    return iterator(NULL);
    */

    TreeNode<T> *present_node = root;

    while (present_node != NULL) {
      if (present_node->value == key_value) { // found the node
        return iterator(present_node);
      } else { // check to see which child to check next
        if (present_node->value < key_value) {
          present_node = present_node->right; // the value has to be down the left side
        } else {
          assert (key_value < present_node->value);
          present_node = present_node->left; // the value has to be down the right side
        }
      }
    }

    // didn't find the value
    return iterator(NULL);
  }

  std::pair<iterator,bool> insert(const T& key_value, TreeNode<T>*& p) {
    if (!p) {
      p = new TreeNode<T>(key_value);
      this->size_++;
      return std::pair<iterator,bool>(iterator(p), true);
    }
    else if (key_value < p->value)
      return insert(key_value, p->left);
    else if (key_value > p->value)
      return insert(key_value, p->right);
    else
      return std::pair<iterator,bool>(iterator(p), false);
  }
  
  int erase(T const& key_value, TreeNode<T>* &p) {  /* Implemented in Lecture 17 */  }

  void print_in_order(std::ostream& ostr, const TreeNode<T>* p) const {
    if (p) {
      print_in_order(ostr, p->left);
      ostr << p->value << "\n";
      print_in_order(ostr, p->right);
    }
  }

  void print_as_sideways_tree(std::ostream& ostr, const TreeNode<T>* p, int depth) const {
    if (p) {
      print_as_sideways_tree(ostr, p->right, depth+1);
      for (int i=0; i<depth; ++i) ostr << "    ";
      ostr << p->value << "\n";
      print_as_sideways_tree(ostr, p->left, depth+1);
    }
  }
};

#endif
