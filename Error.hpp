#ifndef ERROR_HPP
#define ERROR_HPP

#include <iostream>
#include <string>

class Error {
public:
    virtual void handleError() = 0;
    virtual ~Error() {}
};

class InvalidInputError : public Error {
public:
    std::string name;
    std::string filename;
    
    InvalidInputError(const std::string& file = "");
    void handleError() override;
};

class MemoryError : public Error {
public:
    std::string name;
    std::string filename;
    
    MemoryError(const std::string& file = "");
    void handleError() override;
};

class ThreadError : public Error {
public:
    std::string name;
    std::string filename;
    
    ThreadError(const std::string& file = "");
    void handleError() override;
};

class FileError : public Error {
public:
    std::string name;
    std::string filename;
    
    FileError(const std::string& file = "");
    void handleError() override;
};

class AlgorithmError : public Error {
public:
    std::string name;
    std::string filename;
    
    AlgorithmError(const std::string& file = "");
    void handleError() override;
};

#endif