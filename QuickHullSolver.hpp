#ifndef QUICK_HULL_SOLVER_HPP
#define QUICK_HULL_SOLVER_HPP

#include <vector>
#include "Point.hpp"

class QuickHullSolver {
protected:
    std::vector<Point> points;
    std::vector<Point> result;
    
public:
    QuickHullSolver(const std::vector<Point>& pts);
    virtual ~QuickHullSolver();
    
    virtual std::vector<Point> solve() = 0;
    
    static double distanceFromLine(Point p, Point a, Point b);
    static Point findFarthestPoint(const std::vector<Point>& pts, Point a, Point b);
};

#endif