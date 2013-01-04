#include <iostream>
using std::cout;
using std::endl;


// a link in our linked list
class Node {
public:
  int value;
  Node* ptr;
};


// adds a new link with this value to the back of the list
void push_back(Node* &head, int v) {
  if (head == NULL) {
    head = new Node();
    head->value = v;
    head->ptr = NULL;
  } else {
    Node* temp;
    for (temp = head; temp->ptr != NULL; temp = temp->ptr) {}
    // temp is now pointing to the last node
    temp->ptr = new Node();
    temp->ptr->value = v;
    temp->ptr->ptr = NULL;  
  }
}


// print out the contents of the list
void print(Node* &head) {
  Node* temp;
  cout << "contents: ";
  for (temp = head; temp != NULL; temp = temp->ptr) {
    cout << " " << temp->value;
  }  
  cout << endl;
}



int main() {

  // testing push_back and print
  Node* lst = NULL; 
  push_back(lst,10);
  push_back(lst,11);
  push_back(lst,12);
  push_back(lst,13);
  push_back(lst,14);
  push_back(lst,15);
  push_back(lst,16);
  push_back(lst,17);
  push_back(lst,18);
  print(lst);

}
