#include <iostream>
#include "Point2D.h"
#include "Rectangle.h"

using namespace std;

int main()
{
    Point2D origin(0.0, 0.0), p(1.0, 1.0), q(2.0, 1.0), r(2.0, 2.0), s(1.0, 2.0), t(-1.0, -1.0), u(0.5, 0.5), v(-0.5, -0.5);

    Rectangle r1(origin, p), r2(p, r), r3(t, q); 

    cout << "is_point_within()" << endl;
    cout << "expected: " << 1 << " got: " << r1.is_point_within(u) << endl;
    cout << "expected: " << 0 << " got: " << r2.is_point_within(u) << endl;
    cout << "expected: " << 1 << " got: " << r3.is_point_within(v) << endl;
    cout << "expected: " << 0 << " got: " << r2.is_point_within(v) << endl;

    cout << endl;

    cout << "add_point" << endl;
    r1.add_point(origin);
    r1.add_point(p);
    r1.add_point(u);
    r1.add_point(v);
    vector<Point2D> points_in_r1 = r1.points_contained();
    cout << "expected: " << "(0,0) (1.0,1.0) (0.5,0.5)" << endl;
    cout << "got: ";
    for (int i = 0; i < points_in_r1.size(); i++)
        cout << '(' << points_in_r1[i].x() << ',' << points_in_r1[i].y() << ") ";
    cout << endl;

    return 0;
}
