#include <stdio.h>
#include <iostream>
#include <cassert>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

void compute_squares(uintptr_t *a, uintptr_t *b, uintptr_t n);
extern void print_stack(uintptr_t* bottom, uintptr_t* top);

int main()
{
    uintptr_t a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    uintptr_t b[] = { 0, 0, 0, 0, 0                 };
    uintptr_t n = 10;

    uintptr_t *bottom_address = 
        min(&a[0], min(&a[9], min(&b[0], min(&b[9], &n))));
    uintptr_t *top_address = 
        max(&a[0], max(&a[9], max(&b[0], max(&b[9], &n))));

    print_stack(bottom_address, top_address);
    
    compute_squares(a, b, n);

    print_stack(bottom_address, top_address);

    /*
    cout << "a: ";
    for (uintptr_t i = 0; i < n; i++)
        cout << a[i] << ' ';

    cout << endl;

    cout << "b: ";
    for (uintptr_t i = 0; i < n; i++)
        cout << b[i] << ' ';

    cout << endl;
    */

    return 0;
}

void compute_squares(uintptr_t *a, uintptr_t *b, uintptr_t n)
{
    for (uintptr_t i = 0; i < n; i++)
        *(b+i) = *(a+i) * *(a+i);
}
