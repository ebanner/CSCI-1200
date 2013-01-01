#include <iostream>
#include <cstdlib>

using namespace std;

bool is_prime(unsigned int i)
{
    if (i == 0 || i == 1)
        return false;

    for (int d = 2; d < i; d++) {
        if (i % d == 0)
            return false;
    }

    return true;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;

    int n = atoi(argv[1]);
    if (n <= 0)
        return 1;

    int prime_count = 0;

    /* Create and initialize a dynamically allocated array to keep track of
     * whether the numbers 1 to n are prime. */
    int *a = new int[n];

    for (int i = 0; i < n; i++) // populate the list
        a[i] = i;

    // 0 and 1 are not prime
    a[0] = a[1] = 0;

    for (int i = 2; i < n; i++) {
        // check to see if the number is prime
        if (is_prime(i)) {
            // mark off all multiples of i
            for (int j = i+i; j < n; j+=i)
                a[j] = 0;
        } else {
            continue;
        }
    }

    for (int i = 0; i < n; i++)
        if (a[i] != 0)
            cout << a[i] << ' ';
    cout << endl;

    // free the memory from the heap!
    delete [] a;

    return 0;
}
