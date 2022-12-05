#include "read_omp.h"
#include <omp.h>
#include <chrono>

int main(int argc, char** argv) {
    // argv[1] = input filename
    // argv[2] = output filename
    // argv[3] = num_threads

    auto t0 = std::chrono::high_resolution_clock::now();

    if(argc < 3) return EXIT_FAILURE;

    VectorArray VArray;

    if (argc == 4) VArray.num_threads = std::atoi(argv[3]);

    VArray.vectorize(argv[1], argv[2]);

    auto t1 = std::chrono::high_resolution_clock::now();

    auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0).count()/std::pow(10,6);
    std::cout << "finished with " << ms << " ms elapsed";

    return 0;
}