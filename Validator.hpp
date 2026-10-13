#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <vector>
#include "Point.hpp"

class Validator {
private:
    bool correct;
    
public:
    Validator();
    
    void hullCorrect(const std::vector<Point>& hull);
    bool getCheck() const;
};

#endif