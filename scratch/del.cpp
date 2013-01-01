#include <iostream>

int main()
{
    int *p = new int;
    int x;
    *p = 42;

    std::cout << *p << std::endl;

    delete p;

    std::cout << *p << std::endl;

    p = &x;
    *p = 52;

    std::cout << *p << std::endl;

    return 0;
}
