#include "Presenter.hpp"

Presenter::Presenter(int threads, int runs) 
    : threadCount(threads), runsPerTest(runs) 
{
    rng.seed(static_cast<unsigned int>(std::time(nullptr)));
}

int Presenter::getThreadCount() const {
    return threadCount;
}

double Presenter::Time(std::function<std::vector<Point>()> algorithm) {
    auto start = std::chrono::high_resolution_clock::now();
    algorithm();
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

double Presenter::AverageTime(std::function<std::vector<Point>()> algorithm) {
    std::vector<double> times;
    
    for (int i = 0; i < runsPerTest; i++) {
        times.push_back(Time(algorithm));
    }
    
    double sum = 0.0;
    for (unsigned int i = 0; i < (unsigned int)times.size(); i++) {
        sum += times[i];
    }
    return sum / (double)times.size();
}

void Presenter::saveDataFile(const std::string& testName) {
    std::ofstream dataFile(("data_" + testName + ".txt").c_str());
    if (!dataFile.is_open()) {
        throw FileError("Cannot open data file");
    }
    for (unsigned int i = 0; i < (unsigned int)currentPoints.size(); i++) {
        dataFile << currentPoints[i].x << " " << currentPoints[i].y << std::endl;
    }
    dataFile.close();
}

bool Presenter::validateResult(const std::vector<Point>& hull, const std::string& algorithmName) {
    Validator validator;
    validator.hullCorrect(hull);
    
    if (!validator.getCheck()) {
        std::cout << "  WARNING: " << algorithmName << " result is INCORRECT!" << std::endl;
        return false;
    }
    return true;
}

void Presenter::saveHullFile(const std::string& testName, const std::vector<Point>& hull) {
    std::ofstream hullFile(("hull_" + testName + ".txt").c_str());
    hullFile << hull.size() << std::endl;
    for (unsigned int i = 0; i < (unsigned int)hull.size(); i++) {
        hullFile << hull[i].x << " " << hull[i].y << std::endl;
    }
    hullFile.close();
}

void Presenter::runTests(const std::string& testName) {
    saveDataFile(testName);
    
    double avgSeqTime = AverageTime([this]() { return runSequential(); });
    std::vector<Point> seqResult = runSequential();
    bool seqValid = validateResult(seqResult, "Sequential");
    saveHullFile(testName + "_seq", seqResult);
    
    double avgParTime = AverageTime([this]() { return runParallel(); });
    std::vector<Point> parResult = runParallel();
    bool parValid = validateResult(parResult, "Parallel");
    saveHullFile(testName + "_par", parResult);
    
    double speedup = avgSeqTime / avgParTime;
    
    std::cout << "============" << testName << "============" << std::endl;
    std::cout << "Points: " << currentPoints.size() << std::endl;
    std::cout << "Sequential hull points: " << seqResult.size() << std::endl;
    std::cout << "Time: " << avgSeqTime << " ms";
    if (!seqValid) std::cout << " INVALID";
    std::cout << std::endl;
    
    std::cout << "Parallel hull points: " << parResult.size() << std::endl;
    std::cout << "Time: " << avgParTime << " ms";
    if (!parValid) std::cout << " INVALID";
    std::cout << std::endl;
    
    std::cout << "Difference: " << speedup << std::endl;
    std::cout << "============" << std::endl;
}

void Presenter::testCircle(int n) {
    currentPoints.clear();
    const double PI = std::acos(-1.0);
    for (int i = 0; i < n; i++) {
        double a = i * 2 * PI / n;
        currentPoints.push_back(Point(std::cos(a) * 100, std::sin(a) * 100));
    }
    
    runTests("circle");
}

void Presenter::testTriangle(int n) {
    currentPoints.clear();
    
    currentPoints.push_back(Point(0, 0));
    currentPoints.push_back(Point(1, 0));
    currentPoints.push_back(Point(0, 1));
    
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    
    for (int i = 3; i < n; i++) {
        double x = dist(rng);
        double y = dist(rng);
        
        if (x + y <= 1.0) {
            currentPoints.push_back(Point(x, y));
        }
        else {
            currentPoints.push_back(Point(1.0 - x, 1.0 - y));
        }
    }
    runTests("triangle");
}

void Presenter::createTest(int n) {
    currentPoints.clear();
    std::uniform_int_distribution<int> dist(0, 9999);
    
    for (int i = 0; i < n; i++) {
        currentPoints.push_back(Point(dist(rng), dist(rng)));
    }
    runTests("random");
}

std::vector<Point> Presenter::runSequential() {
    try {
        QuickHullSequential solver(currentPoints);
        return solver.solve();
    }
    catch (...) {
        return std::vector<Point>();
    }
}

std::vector<Point> Presenter::runParallel() {
    try {
        QuickHullParallel solver(currentPoints, threadCount);
        return solver.solve();
    }
    catch (...) {
        return std::vector<Point>();
    }
}