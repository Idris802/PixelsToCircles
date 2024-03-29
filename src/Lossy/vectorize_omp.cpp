#include "read_omp.h"
#include <omp.h>
#include <chrono>
#include <cmath>

int main(int argc, char** argv) {
    // argv[1] = input filename
    // argv[2] = output filename
    // argv[3] = num_threads

    auto t0 = std::chrono::high_resolution_clock::now();

    if(argc < 3) return EXIT_FAILURE;

    // Initiating the class
    VectorArray VArray;

    // Determining and setting number of threads
    if (argc == 4) VArray.num_threads = std::atoi(argv[3]);
    omp_set_num_threads(VArray.num_threads);

    // Executing the program
    VArray.vectorize(argv[1], argv[2]);

    auto t1 = std::chrono::high_resolution_clock::now();

    auto total_time = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0).count()/std::pow(10,6);
    std::cout << "finished with " << total_time << " ms elapsed" << std::endl;

    return 0;
}