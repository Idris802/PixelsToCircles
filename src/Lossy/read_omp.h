#ifndef PIXELSTOCIRCLES_READ_OMP_H
#define PIXELSTOCIRCLES_READ_OMP_H

#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cmath>
#include <chrono>

#include <omp.h>

class VectorArray{

private:
    // omp parameters
    int split;
    int num_disks = 0;

    int x_size;
    int y_size;
    int background_color = 0;
    int foreground_color = 255;
    std::vector<std::vector<int>> image;
    std::vector<std::vector<int>> approximation;
    std::vector<std::vector<int>> disks;

    void make_vect(std::string filename);
    bool overlap(int x, int y, int r);
    void compress();
    void Clean_Approx();
    void PrintOut(std::ostream* target);

public:
    // OpenMP parameters
    int num_threads = 1;
    void vectorize(std::string input_filename, std::string output_filename);
};

#endif //PIXELSTOCIRCLES_READ_OMP_H
