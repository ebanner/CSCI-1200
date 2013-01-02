#ifndef Point2D_h_
#define Point2D_h_

class Point2D {
    public:
        Point2D() : m_x(0), m_y(0) { }
        Point2D(float x, float y) : m_x(x), m_y(y) { }

        float x() const { return m_x; }
        float y() const { return m_y; }
        float set(float x, float y) { m_x = x; m_y = y; }
    private:
        float m_x, m_y;
};

inline bool operator== (const Point2D point1, const Point2D point2)
{
    return point1.x() == point2.x() &&
        point1.y() == point2.y();
}

#endif
