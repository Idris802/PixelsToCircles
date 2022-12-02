#include "read.h"
#include <iostream>


int main() {
    VectorArray VArray;

    VArray.make_vect("../benchmark.0032.pxl");
    std::vector<std::vector<int>> mask = VArray.make_mask(2);
    std::cout << "Mask clear" << std::endl;

    bool boolian = VArray.overlap(29,30,2);

    std::cout << "Overlap clear " << boolian << std::endl;


    VArray.compress();

    for(std::vector<int> v : VArray.approximation){
        for (int n : v){
            std::cout << n;
        } // for n in vector
        std::cout << "\n";
    } // for vector in columns
    std::cout << "Approximation clear" << std::endl;

    VArray.Clean_Approx();
    std::cout << "Clean Approx clear" << std::endl;
    for(std::vector<int> v : VArray.approximation){
        for (int n : v){
            std::cout << n;
        } // for n in vector
        std::cout << "\n";
    } // for vector in columns
    return 0;
}