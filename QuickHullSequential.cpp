#include "QuickHullSequential.hpp"

QuickHullSequential::QuickHullSequential(const std::vector<Point>& pts) 
    : QuickHullSolver(pts) {}

std::vector<Point> QuickHullSequential::solve() {
    if (points.size() < 3) return points;
    return hullAlgorithm();
}

std::vector<Point> QuickHullSequential::hullAlgorithm() {
    if (points.empty()) {
        throw InvalidInputError("No points provided");
    }
    
    std::vector<Point> hull;
    
    Point minX = points[0], maxX = points[0];
    for (unsigned int i = 0; i < (unsigned int)points.size(); i++) {
        if (points[i].x < minX.x) minX = points[i];
        if (points[i].x > maxX.x) maxX = points[i];
    }
    
    hull.push_back(minX);
    hull.push_back(maxX);
    
    std::vector<Point> leftSet, rightSet;
    for (unsigned int i = 0; i < (unsigned int)points.size(); i++) {
        int fl = Point::turn(minX, maxX, points[i]);
        if (fl == 2) leftSet.push_back(points[i]);
        else if (fl == 1) rightSet.push_back(points[i]);
    }
    
    findHull(minX, maxX, leftSet, hull);
    findHull(maxX, minX, rightSet, hull);
    
    return hull;
}

void QuickHullSequential::findHull(Point a, Point b, std::vector<Point>& set, std::vector<Point>& hull) {
    if (set.empty()) return;
    
    Point farthest = findFarthestPoint(set, a, b);
    
    std::vector<Point>::iterator it = std::find(hull.begin(), hull.end(), b);
    hull.insert(it, farthest);
    
    std::vector<Point> leftSet1, leftSet2;
    for (unsigned int i = 0; i < (unsigned int)set.size(); i++) {
        if (Point::turn(a, farthest, set[i]) == 2) {
            leftSet1.push_back(set[i]);
        }
        if (Point::turn(farthest, b, set[i]) == 2) {
            leftSet2.push_back(set[i]);
        }
    }
    
    findHull(a, farthest, leftSet1, hull);
    findHull(farthest, b, leftSet2, hull);
}