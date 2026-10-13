#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>
#include <vector>
#include <fstream>

class Point {
public:
    double x, y;
    
    Point();
    Point(double x1, double y1);
    
    double distance(Point p) const;
    bool operator==(Point p) const;
    
    static int turn(Point a, Point b, Point c);
    
    void print(std::ofstream& out) const;
};

#endif