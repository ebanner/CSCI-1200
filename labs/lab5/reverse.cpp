#include <iostream>
#include "Vec.h"

using namespace std;

void swap(int &a, int&b)
{
    int temp = a;
    a = b;
    b = temp;
}

void my_reverse(Vec<int> &v)
{
    for (int i = 0; i < v.size()/2; i++)
        swap(v[i], v[int(v.size()-i-1)]);
}

void printv(const Vec<int> &v)
{
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << ' ';
    cout << endl;
}

int main()
{
    Vec<int> v;

    for (int i = 0; i < 5; i++)
        v.push_back(i);

    printv(v);
    v.reverse();
    printv(v);

    return 0;
}
