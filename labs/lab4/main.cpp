#include <iostream>
#include <vector>
#include <algorithm>
#include "Rectangle.h"
#include "Point2D.h"

using namespace std;

int main()
{
    vector<Point2D> points;
    points.push_back(Point2D(3.0, 4.0));
    points.push_back(Point2D(4.0, 3.0));

    find(points.begin(), points.end(), Point2D(3.0, 4.0));

    return 0;
}
