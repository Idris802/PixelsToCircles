#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "read.h"

std::vector<std::vector<int>> get_vect(std::string filename) {
    // Read from image
    std::ifstream file(filename);
    int x; // Size in x dim
    int y; // Size in y dim
    file >> x >> y;

    std::cout << x << "\t" << y << std::endl;

    // construct 2D vector where the outer vector has x elements, each of which is a vector with y elements
    std::vector<std::vector<int>> figure(x, std::vector<int>(y));

    // attention! there is a line break character that we need to get rid of
    char pixel;
    file.get(pixel);

    // read in file into the vector such that vector[x][y] contains the value of pixel (x, y) as 0 or 1
    // note that the file format contains the pixels in (y, x) ascending order
    //
    for(int j = 0; j < y; j++)
       for(int i = 0; i < x; i++)
       {
          assert(!file.eof());
          file.get(pixel);
          if(pixel) figure[j][i] = 1;
          else figure[j][i] = 0;
       }

   file.close();
   return figure;
} // get_vect
