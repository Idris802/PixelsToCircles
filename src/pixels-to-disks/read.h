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
    int bg_color = 0;
    std::vector<std::vector<int>> image;
    std::vector<std::vector<int>> approximation;

    void make_vect(std::string filename);
    std::vector<std::vector<int>> make_mask(int r);
    bool overlap(int x, int y, int r);
    bool overlap2(int x, int y, int r);
    void compress();
    void Clean_Approx();
    void Clean_Approx2();
    void PrintOut(std::ostream* target);

};

#endif //PIXELSTOCIRCLES_READ_H
