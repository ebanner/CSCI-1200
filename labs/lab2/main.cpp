#include "MyTime.h"
#include "MyTime.cpp"

int main() 
{
    MyTime t1;
    MyTime t2(0, 30, 12);

    t1.print();
    t2.print();

    t1.printAMPM();
    t2.printAMPM();

    return 0;
}
