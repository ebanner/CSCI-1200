#include <iostream>

using namespace std;

int main()
{
    int n = 1;

    for (int *p = new int[n], *q = p; p < q+n; p++) {
        cout << "p: " << p << " p+n: " << p+n << endl;
        cout << "Enter an integer: ";
        cin >> *p;
    }

    return 0;
}
