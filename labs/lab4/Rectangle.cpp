#include <iostream>
#include <vector>
#include <algorithm>
#include "Rectangle.h"

Rectangle::Rectangle( Point2D const& lower_left, Point2D const& upper_right ) :
    m_lower_left(lower_left), m_upper_right(upper_right) { }

bool Rectangle::is_point_within( Point2D const& p ) const
{
    return
        ( p.x() <= m_upper_right.x() && p.y() <= m_upper_right.y() ) &&
        ( p.x() >= m_lower_left.x() && p.y() >= m_lower_left.y() );
}

bool Rectangle::add_point( Point2D const &p )
{
    if (is_point_within(p) && std::find(m_points_contained.begin(), m_points_contained.end(), p) == m_points_contained.end()) {
        m_points_contained.push_back(p);
        return true;
    } else {
        return false;
    }
}

vector<Point2D> points_in_both( Rectangle const& r1, Rectangle const& r2 )
{
    //  The following access the vector of points in the two rectangles
    //  without copying these vectors.  Instead, r1_points and r2_points
    //  are references to the vectors of points, but since they are
    //  constants neither the vectors nor the points within them can be
    //  changed.
    const vector<Point2D> & r1_points = r1.points_contained();
    const vector<Point2D> & r2_points = r2.points_contained();

    /*
    vector<Point2D> points_in_both;
    for (int i = 0; i < r1_points.size(); i++)
        if (r2.is_point_within(r1_points[i]))
            points_in_both.push_back(r1_points[i]);
    for (int i = 0; i < r2_points.size(); i++)
        if (r1.is_point_within(r2_points[i]))
            points_in_both.push_back(r2_points[i]);

    return points_in_both;
    */
}


void print_rectangle( Rectangle const& r1 )
{
    // get all the points that are inside the rectangle
    const vector<Point2D> & r1_points = r1.points_contained();

    // print the rectangle coordinates
    std::cout << "Rectangle: " 
        << r1.lower_left_corner().x() << "," << 
        r1.lower_left_corner().y() << "--"
        << r1.upper_right_corner().x() << "," << 
        r1.lower_left_corner().y() << endl;

    // print points that are inside
    std::cout << "Points inside:" << endl;
    for( vector<Point2D>::size_type i = 0; i < r1_points.size(); ++i ) {
        std::cout << r1_points[i].x() << "," << r1_points[i].y() << std::endl;
    }
}
