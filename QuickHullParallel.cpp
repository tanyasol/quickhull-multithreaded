#include "QuickHullParallel.hpp"

QuickHullParallel::QuickHullParallel(const std::vector<Point>& pts, int threads)
    : QuickHullSolver(pts) 
{
    if (threads <= 0) {
        pool = new ThreadPool();
        numThreads = pool->size();
    }
    else {
        pool = new ThreadPool(threads);
        numThreads = threads;
    }
}

QuickHullParallel::~QuickHullParallel() {
    delete pool;
}

std::vector<Point> QuickHullParallel::solve() {
    if (points.size() < 3) return points;
    return hullAlgorithm();
}

std::vector<Point> QuickHullParallel::hullAlgorithm() {
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
    
    findHullParallel(minX, maxX, leftSet, hull);
    findHullParallel(maxX, minX, rightSet, hull);
    
    pool->wait();
    
    return hull;
}

void QuickHullParallel::findHullParallel(Point a, Point b, 
                                          std::vector<Point>& set, 
                                          std::vector<Point>& hull) 
{
    if (set.empty()) return;
    
    Point farthest = findFarthestPoint(set, a, b);
    
    {
        std::lock_guard<std::mutex> lock(hullMutex);
        std::vector<Point>::iterator it = std::find(hull.begin(), hull.end(), b);
        hull.insert(it, farthest);
    }
    
    std::vector<Point> leftSet1, leftSet2;
    for (unsigned int i = 0; i < (unsigned int)set.size(); i++) {
        if (Point::turn(a, farthest, set[i]) == 2) {
            leftSet1.push_back(set[i]);
        }
        if (Point::turn(farthest, b, set[i]) == 2) {
            leftSet2.push_back(set[i]);
        }
    }
    
    if (!leftSet1.empty()) {
        pool->submit([this, a, farthest, leftSet1, &hull]() {
            std::vector<Point> copy = leftSet1;
            findHullParallel(a, farthest, copy, hull);
        });
    }
    
    if (!leftSet2.empty()) {
        pool->submit([this, farthest, b, leftSet2, &hull]() {
            std::vector<Point> copy = leftSet2;
            findHullParallel(farthest, b, copy, hull);
        });
    }
}