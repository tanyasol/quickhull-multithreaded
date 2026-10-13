#include "Presenter.hpp"

int main() {
    try {
        unsigned int cores = std::thread::hardware_concurrency();
        std::cout << "Number of cores: " << cores << std::endl;
        int numRuns = 15;

        Presenter presenter(15, numRuns);
        
        std::cout << "Threads: " << presenter.getThreadCount() << std::endl;
        std::cout << std::endl;
        
        presenter.testCircle(10000);
        presenter.testTriangle(100000);
        presenter.createTest(100000);
        
       
        
        std::cout << std::endl;
        
    } 
    catch (Error& e) {
        e.handleError();  
        return 1;
    }
    return 0;
}