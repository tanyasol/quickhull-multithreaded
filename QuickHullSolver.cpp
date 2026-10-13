#include "QuickHullSolver.hpp"
#include <cmath>

QuickHullSolver::QuickHullSolver(const std::vector<Point>& pts) 
    : points(pts) {}

QuickHullSolver::~QuickHullSolver() {}

double QuickHullSolver::distanceFromLine(Point p, Point a, Point b) {
    return fabs((b.y - a.y) * p.x - (b.x - a.x) * p.y + b.x * a.y - b.y * a.x);
}

Point QuickHullSolver::findFarthestPoint(const std::vector<Point>& pts, Point a, Point b) {
    double maxDist = -1;
    Point farthest = pts[0];
    
    for (unsigned int i = 0; i < (unsigned int)pts.size(); i++) {
        double dist = distanceFromLine(pts[i], a, b);
        if (dist > maxDist) {
            maxDist = dist;
            farthest = pts[i];
        }
    }
    return farthest;
}