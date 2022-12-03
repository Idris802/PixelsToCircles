#ifndef PIXELSTOCIRCLES_READ_H
#define PIXELSTOCIRCLES_READ_H

#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>


class VectorArray{

private:

public:
    int x_size;
    int y_size;
    int background_color = 0;
    int foreground_color = 255;
    std::vector<std::vector<int>> image;
    std::vector<std::vector<int>> approximation;
    std::vector<std::vector<int>> disks;

    void make_vect(std::string filename);
    std::vector<std::vector<int>> make_mask(int r);
    bool overlap(int x, int y, int r);
    void compress();
    void Clean_Approx();
    void PrintOut(std::ostream* target);
    void vectorize(std::string input_filename, std::string output_filename);

};

#endif //PIXELSTOCIRCLES_READ_H
