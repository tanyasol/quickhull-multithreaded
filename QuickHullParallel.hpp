#ifndef QUICK_HULL_PARALLEL_HPP
#define QUICK_HULL_PARALLEL_HPP

#include "QuickHullSolver.hpp"
#include "ThreadPool.hpp"
#include <algorithm>
#include <mutex>
#include "Point.hpp"

class QuickHullParallel : public QuickHullSolver {
private:
    ThreadPool* pool;
    int numThreads;
    std::mutex hullMutex;
    
    std::vector<Point> hullAlgorithm();
    void findHullParallel(Point a, Point b, std::vector<Point>& set, std::vector<Point>& hull);
    
public:
    QuickHullParallel(const std::vector<Point>& pts, int threads = 0);
    ~QuickHullParallel();
    
    std::vector<Point> solve() override;
};

#endif