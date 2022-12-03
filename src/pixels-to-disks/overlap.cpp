#include "read.h"
#include <iostream>


int main() {
    VectorArray VArray;

    VArray.make_vect("../benchmark.0032.pxl");

    VArray.compress();

    for(std::vector<int> v : VArray.approximation){
        for (int n : v){
            std::cout << n;
        } // for n in vector
        std::cout << "\n";
    } // for vector in columns
    std::cout << "Approximation clear" << std::endl;

    VArray.Clean_Approx();
    for(std::vector<int> v : VArray.approximation){
        for (int n : v){
            std::cout << n;
        } // for n in vector
        std::cout << "\n";
    } // for vector in columns
    return 0;
}