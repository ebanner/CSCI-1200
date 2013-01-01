#include <iostream>

using namespace std;

int main()
{
    int n = 5;
    int *a = new int[n];

    cout << "a[n], a[n+1], ..., a[2*(n-1)]" << endl;
    for (int i = n; i < 2*n; i++)
        cout << a[i] << ", ";
    cout << endl;

    // let's double the size of our array

    int *temp = new int[2*n];
    cout << "temp[n], temp[n+1], ..., temp[2*(n-1)]" << endl;
    for (int i = n; i < 2*n; i++)
        cout << temp[i] << ", ";
    cout << endl;

    for (int i = 0; i < n; i++)
        temp[i] = a[i];

    delete [] a;

    a = temp;

    cout << "a[n], a[n+1], ..., a[2*(n-1)]" << endl;
    for (int i = n; i < 2*n; i++)
        cout << a[i] << ", ";
    cout << endl;

    return 0;
}
