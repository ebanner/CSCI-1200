#include <iostream>
#include <list>

using namespace std;

void my_reverse(list<double> &dl)
{
    double temp;
    list<double>::iterator a = dl.begin();
    list<double>::iterator z = dl.end();
    z--;

    for (int i = 0; i < dl.size()/2; i++, a++, z++) {
        temp = *a;
        *a = *z;
        *z = temp;
    }
}

void complicated_reverse(list<double> &dl)
{
    double t1, t2;
    list<double>::iterator a = dl.begin();
    list<double>::iterator z = dl.end();
    z--;

    for (int i = 0; i < dl.size()/2; i++, a++, z++) {
        t1 = *a;
        t2 = *z;

        // erase the leftmost value
        a = dl.erase(a);
        // insert the rightmost value into the leftmost value
        dl.insert(a, t2);

        // erase the rightmost value
        z = dl.erase(z);
        // insert the leftmost value into the rightmost value
        dl.insert(z, t1);
    }
}

void my_print(list<double> &dl)
{
    for (list<double>::iterator itr = dl.begin(); itr != dl.end(); itr++)
        cout << *itr << ' ';
    cout << endl;
}

int main()
{
    list<double> dl;
    
    dl.push_back(42.0);
    dl.push_front(69.0);
    dl.push_back(71.5);

    my_print(dl);
    my_reverse(dl);
    my_print(dl);
    complicated_reverse(dl);
    my_print(dl);

    return 0;
}
