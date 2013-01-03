#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <assert.h>
#include "jagged_array.h"

using namespace std;

//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD ONLY CONTAIN CHANGES TO MoreTests()
//

// helper testing functions
void SimpleTest();
void MoreTests();
void BatchTest(const char* filename, int num);

//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD CONTAIN NO CHANGES TO main()
//
int main(int argc, char* argv[]) {
  if (argc == 1) {
    SimpleTest();
    cout << "Simple test completed." << endl;
    MoreTests();
    cout << "More tests completed." << endl;    
  } else {
    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " <filename> <num_iters>" << endl;
      exit(1);
    }
    BatchTest(argv[1],atoi(argv[2]));
    cout << "Batch test completed." << endl;
  }
}


//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD CONTAIN NO CHANGES TO SimpleTest()
//
void SimpleTest() {

  JaggedArray<char> ja(7);

  assert (ja.numBins() == 7);
  assert (ja.numElements() == 0);
  assert (ja.isPacked() == false);

  // intialize the values in the JaggedArray
  ja.addElement(1,'a');
  ja.addElement(1,'b');
  ja.addElement(1,'c');
  ja.addElement(3,'d');
  ja.addElement(3,'e');
  ja.addElement(6,'f');

  // verify data is correct
  std::cout << "STARTS UNPACKED" << std::endl;
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 6);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 3);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 2);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 1);
  assert (ja.getElement(1,0) == 'a');
  assert (ja.getElement(1,1) == 'b');
  assert (ja.getElement(1,2) == 'c');
  assert (ja.getElement(3,0) == 'd');
  assert (ja.getElement(3,1) == 'e');
  assert (ja.getElement(6,0) == 'f');

  // pack the structure and verify data is correct
  ja.pack();
  std::cout << "CONVERT TO PACKED" << std::endl;
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 6);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 3);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 2);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 1);
  assert (ja.getElement(1,0) == 'a');
  assert (ja.getElement(1,1) == 'b');
  assert (ja.getElement(1,2) == 'c');
  assert (ja.getElement(3,0) == 'd');
  assert (ja.getElement(3,1) == 'e');
  assert (ja.getElement(6,0) == 'f');

  // unpack the structure and verify data is correct
  ja.unpack();
  std::cout << "CONVERT BACK TO UNPACKED" << std::endl;
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 6);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 3);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 2);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 1);
  assert (ja.getElement(1,0) == 'a');
  assert (ja.getElement(1,1) == 'b');
  assert (ja.getElement(1,2) == 'c');
  assert (ja.getElement(3,0) == 'd');
  assert (ja.getElement(3,1) == 'e');
  assert (ja.getElement(6,0) == 'f');

  // add 'g' and verify
  ja.addElement(3,'g');
  std::cout << "ADDED G" << std::endl;
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 7);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 3);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 3);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 1);
  assert (ja.getElement(1,0) == 'a');
  assert (ja.getElement(1,1) == 'b');
  assert (ja.getElement(1,2) == 'c');
  assert (ja.getElement(3,0) == 'd');
  assert (ja.getElement(3,1) == 'e');
  assert (ja.getElement(3,2) == 'g');
  assert (ja.getElement(6,0) == 'f');

  // remove 'b' and verify
  ja.removeElement(1,1);
  std::cout << "REMOVED B" << std::endl;
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 6);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 2);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 3);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 1);
  assert (ja.getElement(1,0) == 'a');
  assert (ja.getElement(1,1) == 'c');
  assert (ja.getElement(3,0) == 'd');
  assert (ja.getElement(3,1) == 'e');
  assert (ja.getElement(3,2) == 'g');
  assert (ja.getElement(6,0) == 'f');

  // clear
  ja.clear();
  std::cout << "CLEARED" << std::endl;
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 0);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 0);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 0);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 0);

  // note...  the JaggedArray destructor is implicitly called for the
  // variable 't' when we leave the function and it goes out of scope
}



//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD ONLY CONTAIN CHANGES TO MoreTests()
//
void MoreTests() {

  //
  // you should add your own test cases here.  
  // be sure to test:
  //   * jagged arrays that store types other than char
  //   * copy constructor
  //   * assignment operator
  //   * delete operator
  //

}



//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD NOT CONTAIN CHANGES TO BatchTest()
//

// Batch test will repeatedly load & process a file with JaggedArray
// operations.  If the program's working memory does not grow when the
// program is run many, many times on a large test case, the data
// structure is probably free of memory leaks.
void BatchTest(const char* filename, int iters) {

  if (iters <= 0) {
    std::cerr << "ERROR: iters should be > 0" << endl;
    exit(1);
  }

  while (iters > 0) {
    iters--;

    // open the file stream for reading
    ifstream istr(filename);
    if (!istr) {
      std::cerr << "ERROR: cannot open file " << filename << endl;
      exit(1);
    }

    string token;
    char c;
    int b,i;

    // create the initial JaggedArray
    istr >> token >> b;
    assert (token == "create");
    // note: here we explicitly allocate memory for the JaggedArray object
    JaggedArray<char> *ja = new JaggedArray<char>(b);

    // read in and perform various operations on the array
    while (istr >> token) {
      if (token == "addElement") {
        istr >> b >> c;
        ja->addElement(b,c);
      } else if (token == "getElement") {
        istr >> b >> i >> c;
        char c2 = ja->getElement(b,i);
        assert (c == c2);
      } else if (token == "removeElement") {
        istr >> b >> i >> c;
	char c2 = ja->getElement(b,i);
        assert (c == c2);
	ja->removeElement(b,i);
      } else if (token == "pack") {
        ja->pack();
      } else if (token == "unpack") {
        ja->unpack();
      } else if (token == "clear") {
        ja->clear();
      } else {
        std::cerr << "ERROR: unknown token " << token << endl;
        exit(1);
      }
    }

    // print out the jagged array contents at the end of the last iteration
    if (iters == 0) {
      if (ja->isPacked()) {
	ja->unpack();
      }
      ja->print();
      ja->pack();
      ja->print();
    }

    // Because the JaggedArray memory was allocated explicitly (using new)
    // we need to explicitly deallocate the memory (using delete)
    delete ja;
  }

}
