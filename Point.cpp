#include "Point.hpp"

Point::Point() : x(0), y(0) {}

Point::Point(double x1, double y1) : x(x1), y(y1) {}

double Point::distance(Point p) const {
    return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}

bool Point::operator==(Point p) const {
    return x == p.x && y == p.y;
}

int Point::turn(Point a, Point b, Point c) {
    double val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (fabs(val) < 1e-9) return 0;
    return (val > 0) ? 1 : 2;
}

void Point::print(std::ofstream& out) const {
    out << x << " " << y << std::endl;
}