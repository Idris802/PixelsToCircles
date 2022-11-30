#include <cassert>
#include <iostream>
#include <vector>
#include <iterator>

#include "read.h"



std::vector<std::vector<int>> VectorArray::get_vect(std::string filename) {
    /*
    * Improved by Martin Thomas Horsch
    */
    // Read from image
    std::ifstream file(filename);
    int x; // Size in x dim
    int y; // Size in y dim
    file >> x >> y;
    this->x_size = x;
    this->y_size = y;

    // construct 2D vector where the outer vector has x elements, each of which is a vector with y elements
    std::vector<std::vector<int>> figure(y_size, std::vector<int>(x_size));

    // attention! there is a line break character that we need to get rid of
    char pixel;
    file.get(pixel);

    // read in file into the vector such that vector[x][y] contains the value of pixel (x, y) as 0 or 1
    // note that the file format contains the pixels in (y, x) ascending order
    //
    for(int j = 0; j < y_size; j++)
       for(int i = 0; i < x_size; i++)
       {
          assert(!file.eof());
          file.get(pixel);
          if(pixel) figure[j][i] = 1;
          else figure[j][i] = 0;
       }
   if(!file.eof())
   {
      //std::cout << "remaining content of file:\n";
      while(!file.eof())
      {
         file.get(pixel);
         //std::cout << "\t'" << pixel << "' (ASCII " << (unsigned)pixel % 256 << ")\n";
      }
   }

   file.close();
   return figure;
} // get_vect

std::vector<std::vector<int>> VectorArray::make_mask(int r){
    const int max_y = r+r+1;
    const int center = r; // index counts from 0
    // Construct a 2D vector
    std::vector<std::vector<int>> mask(max_y, std::vector<int>(max_y));

    for(int y=0; y<max_y; y++){
        for(int x=0; x<max_y; x++){
            // Calculates if the square is inside a circle with radius r
            float dd = (x - center) * (x - center) + (y - center) * (y - center);
            if (r * r >= dd) mask[y][x] = 1;
            else mask[y][x] = 0;
        }
    }
    return mask;
}
