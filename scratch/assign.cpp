#include <iostream>
#include <string>

using namespace std;

main()
{
    string a = "Kim";
    string b = "Tom";

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    a[0] = b[0];

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    return 0;
}
