// Partial implementation of binary-tree based set class similar to std::set.  
// The iterator increment & decrement operations have been omitted.
#ifndef ds_set_h_
#define ds_set_h_
#include <iostream>
#include <utility>
#include <cassert>

// -------------------------------------------------------------------
// TREE NODE CLASS 
template <class T>
class TreeNode {
public:
  TreeNode() : left(NULL), right(NULL), parent(NULL) {}
  TreeNode(const T& init) : value(init), left(NULL), right(NULL), parent(NULL) {}
  T value;
  TreeNode* left;
  TreeNode* right;
  TreeNode* parent; // to allow implementation of iterator increment & decrement
};

template <class T> class ds_set;

// -------------------------------------------------------------------
// TREE NODE ITERATOR CLASS
template <class T>
class tree_iterator {
public:
  tree_iterator() : ptr_(NULL), set_(NULL), at_the_end_(false) {}
  tree_iterator(TreeNode<T>* p, const ds_set<T> * s) : ptr_(p), set_(s), at_the_end_(false) {}
  tree_iterator(TreeNode<T>* p, const ds_set<T> * s, bool at_the_end) : ptr_(p), set_(s), at_the_end_(true) {}
  tree_iterator(const tree_iterator& old) : ptr_(old.ptr_), set_(old.set_), at_the_end_(false) {}
  ~tree_iterator() {}
  tree_iterator& operator=(const tree_iterator& old) { 
    ptr_ = old.ptr_; set_ = old.set_; at_the_end_ = old.at_the_end_; return *this;
  }
  // operator* gives constant access to the value at the pointer
  const T& operator*() const { return ptr_->value; }
  // comparions operators are straightforward
  friend bool operator== (const tree_iterator& lft, const tree_iterator& rgt)
  { return (lft.set_ == rgt.set_ && lft.ptr_ == rgt.ptr_); }
  friend bool operator!= (const tree_iterator& lft, const tree_iterator& rgt)
  { return (lft.set_ != rgt.set_ || lft.ptr_ != rgt.ptr_); }

  // increment & decrement operators
  tree_iterator<T> & operator++() { 
    if (ptr_->right != NULL) { // find the leftmost child of the right node
      ptr_ = ptr_->right;
      while (ptr_->left != NULL) { ptr_ = ptr_->left; }
    } else { // go upwards along right branches...  stop after the first left
      while (ptr_->parent != NULL && ptr_->parent->right == ptr_) { ptr_ = ptr_->parent; }
      ptr_ = ptr_->parent;
    }
    return *this;
  }
  tree_iterator<T> operator++(int) {
    tree_iterator<T> temp(*this);
    ++(*this);
    return temp;
  }
  tree_iterator<T> & operator--() { 
    if (at_the_end_) { // got here from calling `end()' -- simulate `--' behaviour
      if (set_->root_ == NULL)
        return *this;
      // go to the last element of the BST
      TreeNode<T> *p = set_->root_;
      while (p->right != NULL)
        p = p->right;
      at_the_end_ = false;
      ptr_ = p;

      return *this;
      
    } else {

      if (ptr_->left != NULL) { // find the rightmost child of the left node
        ptr_ = ptr_->left;
        while (ptr_->right != NULL) { ptr_ = ptr_->right; }
      } else { // go upwards along the left branches... stop after the first right
        while (ptr_->parent != NULL && ptr_->parent->left == ptr_) { ptr_ = ptr_->parent; }
        ptr_ = ptr_->parent;
      }

    }
    return *this;
  }

  tree_iterator<T> operator--(int) {
    tree_iterator<T> temp(*this);
    --(*this);
    return temp;
  }

private:
  // representation
  TreeNode<T>* ptr_;
  const ds_set<T>* set_;
  bool at_the_end_; // for mimicking `--' behavior from a call to `end()'
};

// -------------------------------------------------------------------
// DS_ SET CLASS
template <class T>
class ds_set {
public:
  ds_set() : root_(NULL), size_(0) {}
  ds_set(const ds_set<T>& old) : size_(old.size_) { 
    root_ = this->copy_tree(old.root_,NULL); }
  ~ds_set() {
    this->destroy_tree(root_);
    root_ = NULL;
  }
  ds_set& operator=(const ds_set<T>& old) {
    if (&old != this) {
      this->destroy_tree(root_);
      root_ = this->copy_tree(old.root_,NULL);
      size_ = old.size_;
    }
    return *this;
  }

  typedef tree_iterator<T> iterator;
  friend class tree_iterator<T>;

  int size() const { return size_; }
  bool operator==(const ds_set<T>& old) const { return (old.root_ == this->root_); }

  // FIND, INSERT & ERASE
  iterator find(const T& key_value) { return find(key_value, root_); }
  std::pair< iterator, bool > insert(T const& key_value) { return insert(key_value, root_, NULL); }
  int erase(T const& key_value) { return erase(key_value, root_); }
  
  // OUTPUT & PRINTING
  friend std::ostream& operator<< (std::ostream& ostr, const ds_set<T>& s) {
    s.print_in_order(ostr, s.root_);
    return ostr;
  }
  void print_as_sideways_tree(std::ostream& ostr) const {
    print_as_sideways_tree(ostr, root_, 0);
  }

  // ITERATORS
  iterator begin() const { 
    if (! root_) return iterator(NULL,this);
    TreeNode<T>* p = root_;
    while (p->left) p = p->left;
    return iterator(p,this);
  }

  iterator end() const { 
    /* The `true' parameter tells the iterator not to dereference the NULL
     * pointer if `--' is called on it. */
    return iterator(NULL,this,true);
  }

  bool sanity_check() const {
    if (root_ == NULL) return true;
    if (root_->parent != NULL) {
      return false;
    }
    return sanity_check(root_);
  }

  void accumulate(T &initial_value) {
    for (iterator it = this->begin(); it != this->end(); it++)
      initial_value += *it;
  }

private:
  // REPRESENTATION
  TreeNode<T>* root_;
  int size_;

  // PRIVATE HELPER FUNCTIONS
  TreeNode<T>*  copy_tree(TreeNode<T>* old_root, TreeNode<T>* the_parent) {
    if (old_root == NULL) 
      return NULL;
    TreeNode<T> *answer = new TreeNode<T>();
    answer->value = old_root->value;
    answer->left = copy_tree(old_root->left,answer);
    answer->right = copy_tree(old_root->right,answer);
    answer->parent = the_parent;
    return answer;
  }

  void destroy_tree(TreeNode<T>* p) {
    if (!p) return;
    destroy_tree(p->right);
    destroy_tree(p->left);
    delete p;
  }

  iterator find(const T& key_value, TreeNode<T>* p) {
    if (!p) return iterator(NULL,this);
    if (p->value > key_value)
      return find(key_value, p->left);
    else if (p->value < key_value)
      return find(key_value, p->right);
    else
      return iterator(p,this);
  }

  std::pair<iterator,bool> insert(const T& key_value, TreeNode<T>*& p, TreeNode<T>* the_parent) {
    if (!p) {
      p = new TreeNode<T>(key_value);
      p->parent = the_parent;
      this->size_++;
      return std::pair<iterator,bool>(iterator(p,this), true);
    }
    else if (key_value < p->value)
      return insert(key_value, p->left, p);
    else if (key_value > p->value)
      return insert(key_value, p->right, p);
    else
      return std::pair<iterator,bool>(iterator(p,this), false);
  }
  
  int erase(T const& key_value, TreeNode<T>* &p) {
    if (!p) return 0;
 
    // look left & right
   if (p->value < key_value)
      return erase(key_value, p->right);
    else if (p->value > key_value)
      return erase(key_value, p->left);

    // Found the node.  Let's delete it
    assert (p->value == key_value);
    if (!p->left && !p->right) { // leaf
      delete p; 
      p=NULL;       
      this->size_--;    
    } else if (!p->left) { // no left child
      TreeNode<T>* q = p; 
      p=p->right; 
      assert (p->parent == q);
      p->parent = q->parent;
      delete q; 
      this->size_--;    
    } else if (!p->right) { // no right child
      TreeNode<T>* q = p; 
      p=p->left;
      assert (p->parent == q);
      p->parent = q->parent;
      delete q; 
      this->size_--;
    } else { // Find rightmost node in left subtree
      TreeNode<T>* q = p->left;
      while (q->right) q = q->right;
      p->value = q->value;
      // recursively remove the value from the left subtree
      int check = erase(q->value, p->left);
      assert (check == 1);
    }
    return 1;
  }

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

  bool sanity_check(TreeNode<T>* p) const {
    if (p == NULL) return true;
    if (p->left != NULL && p->left->parent != p) {
      return false;
    }
    if (p->right != NULL && p->right->parent != p) {
      return false;
    }
    return sanity_check(p->left) && sanity_check(p->right);
  }



};

#endif
