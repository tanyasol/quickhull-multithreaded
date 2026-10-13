#include "Error.hpp"

// ===== InvalidInputError =====
InvalidInputError::InvalidInputError(const std::string& file)
    : name("InvalidInputError"), filename(file) {}

void InvalidInputError::handleError() {
    std::cerr << "Error: " << name << " in file " << filename 
              << " - invalid input data" << std::endl;
}

// ===== MemoryError =====
MemoryError::MemoryError(const std::string& file)
    : name("MemoryError"), filename(file) {}

void MemoryError::handleError() {
    std::cerr << "Error: " << name << " in file " << filename 
              << " - insufficient memory" << std::endl;
}

// ===== ThreadError =====
ThreadError::ThreadError(const std::string& file)
    : name("ThreadError"), filename(file) {}

void ThreadError::handleError() {
    std::cerr << "Error: " << name << " in file " << filename 
              << " - thread operation error" << std::endl;
}

// ===== FileError =====
FileError::FileError(const std::string& file)
    : name("FileError"), filename(file) {}

void FileError::handleError() {
    std::cerr << "Error: " << name << " in file " << filename 
              << " - file operation error" << std::endl;
}

// ===== AlgorithmError =====
AlgorithmError::AlgorithmError(const std::string& file)
    : name("AlgorithmError"), filename(file) {}

void AlgorithmError::handleError() {
    std::cerr << "Error: " << name << " in file " << filename 
              << " - algorithm error" << std::endl;
}