#include "Validator.hpp"

Validator::Validator() : correct(true) {}

void Validator::hullCorrect(const std::vector<Point>& hull) {
    if (hull.size() < 3) {
        correct = false;
        return;
    }
    
    int firstTurn = 0;
    
    for (unsigned int i = 0; i < hull.size(); i++) {
        Point a = hull[i];
        Point b = hull[(i + 1) % hull.size()];
        Point c = hull[(i + 2) % hull.size()];
        
        int turn = Point::turn(a, b, c);
        
        if (turn != 0) {
            if (firstTurn == 0) {
                firstTurn = turn;
            }
            if (turn != firstTurn) {
                correct = false;
                return;
            }
        }
    }
    
    correct = true;
}

bool Validator::getCheck() const {
    return correct;
}