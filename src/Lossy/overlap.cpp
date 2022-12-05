#include "read.h"
#include <chrono>
#include <cmath>

int main(int argc, char** argv) {
    auto t0 = std::chrono::high_resolution_clock::now();

    if(argc < 2) return EXIT_FAILURE;

    VectorArray VArray;


    // "../benchmark.0032.pxl"
    // "../Disk_Benchmark.0032.dat"

    VArray.vectorize(argv[1], argv[2]);


    auto t1 = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0).count()/std::pow(10,6);
    std::cout << "finished with " << ms << " ms elapsed" << std::endl;

    return 0;
}