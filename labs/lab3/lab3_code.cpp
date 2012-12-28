#include <stdio.h>
#include <iostream>
#include <cassert>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

// For this lab we'll use "uintptr_t", a specially defined integer
// type that is the same size in memory as a pointer.  We'll use this
// type everywhere, instead of "int".  On 32 bit machines/compilers,
// this type is probably 4 bytes, and on 64 bit machines/compilers,
// this is probably 8 bytes.

// ==============================================================================

// This function takes two stack memory addresses (bottom and top) and
// prints out the contents of the memory between and including those
// addresses.
//
// To make the output more readable, the function assumes that
// "values" will be between 0 & 1000 and addresses will be within +/-
// 1000*4 (or *8) bytes from the range of the stack we are examining.
// Anything else is assumed to be "garbage"
//
void print_stack(uintptr_t* bottom, uintptr_t* top) {

  // double check that my uintptr_t is actually the size of a pointer
  assert (sizeof(uintptr_t) == sizeof(void*));

  // double check that the start and end address are aligned 
  assert ((((uintptr_t)bottom) & (sizeof(uintptr_t)-1)) == 0);
  assert ((((uintptr_t)top) & (sizeof(uintptr_t)-1)) == 0);

  // we assume that the top address is greater than the value on
  // bottom address.  
  assert (bottom <= top);

  cout << "-----------------------------------------" << endl;

  for (uintptr_t* address = top; address >= bottom; address--) {
    // this location might store a value (we assume all values are integers)
    uintptr_t value = *address;

    // or it might store an address (so we cast it to a pointer)
    uintptr_t* if_address = (uintptr_t*)value;

    cout << "location: " << address;

    // if it's a value
    if (value < 1000) 
      cout << "  VALUE:   " << value << endl;

    // if it's an address
    else if (if_address >= bottom-1000 && if_address <= top+1000)
      cout << "  POINTER: " << if_address << endl;

    // otherwise it's probably garbage
    else 
      cout << "  garbage? " << endl;
  }
  cout << "-----------------------------------------" << endl;
}

// ==============================================================================
/*
int main() {

  // ------------------------------
  // Example code using print_stack
  // ------------------------------
  cout << "size of uintptr_t: " << sizeof(uintptr_t) << endl;
  uintptr_t x = 72;
  uintptr_t a[5] = {10, 11, 12, 13, 14};
  uintptr_t *y = &x;
  uintptr_t z = 98;
  cout << "x address: " << &x << endl;
  cout << "a address: " << &a << endl;
  cout << "y address: " << &y << endl;
  cout << "z address: " << &z << endl;
  uintptr_t* bottom_address = 
min(&x,min(&a[0],min(&a[4],min((uintptr_t*)&y,&z))));
  uintptr_t* top_address = 
max(&x,max(&a[0],max(&a[4],max((uintptr_t*)&y,&z))));
  print_stack(bottom_address,top_address);

}
*/
