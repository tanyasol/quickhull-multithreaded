#ifndef PRESENTER_H
#define PRESENTER_H

#include <vector>
#include <chrono>
#include <functional>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <random>
#include "Point.hpp"
#include "Error.hpp"
#include "QuickHullSequential.hpp"
#include "QuickHullParallel.hpp"
#include "Validator.hpp"

class Presenter {
    private:
    int threadCount;
    int runsPerTest;
    std::vector<Point> currentPoints;
    std::mt19937 rng;
    
    double Time(std::function<std::vector<Point>()> algorithm);
    double AverageTime(std::function<std::vector<Point>()> algorithm);
    void saveDataFile(const std::string& testName);
    bool validateResult(const std::vector<Point>& hull, const std::string& algorithmName);
    void saveHullFile(const std::string& testName, const std::vector<Point>& hull);
    void runTests(const std::string& testName);


public:
    Presenter(int threads = 4, int runs = 10);
    int getThreadCount() const;
    void testCircle(int n);
    void testTriangle(int n);
    void createTest(int n);
    std::vector<Point> runSequential();
    std::vector<Point> runParallel();
};
#endif