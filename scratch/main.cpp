#include <iostream>
#include "Foo.h"
#include "Foo.cpp"

using namespace std;

int main()
{
    Foo f;

    f.setBar(5);
    int b = f.getBar();

    cout << b << endl;
}
