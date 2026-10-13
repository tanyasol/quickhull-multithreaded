#ifndef QUICK_HULL_SEQUENTIAL_HPP
#define QUICK_HULL_SEQUENTIAL_HPP

#include "Error.hpp"
#include "QuickHullSolver.hpp"
#include <algorithm>

class QuickHullSequential : public QuickHullSolver {
public:
    QuickHullSequential(const std::vector<Point>& pts);
    
    std::vector<Point> solve() override;
    
private:
    std::vector<Point> hullAlgorithm();
    void findHull(Point a, Point b, std::vector<Point>& set, std::vector<Point>& hull);
};

#endif