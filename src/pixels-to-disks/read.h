#ifndef PIXELSTOCIRCLES_READ_H
#define PIXELSTOCIRCLES_READ_H

#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

#include "read.cpp"

class VectorArray{
public:
    int x_size;
    int y_size;
    std::vector<std::vector<int>> get_vect(std::string filename);
    std::vector<std::vector<int>> make_mask(int r);
private:

};


#endif //PIXELSTOCIRCLES_READ_H
