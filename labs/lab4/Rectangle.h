#ifndef Rectangle_h_
#define Rectangle_h_

#include <vector>

using namespace std;

#include "Point2D.h"

class Rectangle {
    public:
        //  Constructor based on the corners of the rectangle.
        Rectangle( Point2D const& lower_left, Point2D const& upper_right );

        //  Access the corners of the rectangle and the points stored in the rectangle.
        Point2D upper_right_corner() const { return m_upper_right; }
        Point2D lower_left_corner() const { return m_lower_left; }
        vector<Point2D> const& points_contained() const { return m_points_contained; }

        //  Return true if the point is within the bounds of the rectangle
        bool is_point_within( Point2D const& p ) const;

        //  If a point is within the bounds of the rectangle and not already
        //  stored with the rectangle then add it.  Return true if the point
        //  was added and false otherwise.
        bool add_point( Point2D const &p );

    private:
        vector<Point2D> m_points_contained;
        Point2D m_upper_right, m_lower_left;
};

vector<Point2D> points_in_both( Rectangle const& r1, Rectangle const& r2 );

void print_rectangle( Rectangle const& r1 );

#endif
