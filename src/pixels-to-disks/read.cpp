#include <cassert>
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>  // Used in make_vect std::ifstream

#include "read.h"

void VectorArray::make_vect(std::string filename) {
    /*
    * Improved by Martin Thomas Horsch
    */
    // Read from image
    std::ifstream file(filename);
    file >> this->x_size >> this->y_size;

    // construct 2D vector where the outer vector has x elements, each of which is a vector with y elements
    std::vector<std::vector<int>> figure(this->y_size, std::vector<int>(this->x_size));

    // attention! there is a line break character that we need to get rid of
    char pixel;
    file.get(pixel);

    // read in file into the vector such that vector[x][y] contains the value of pixel (x, y) as 0 or 1
    // note that the file format contains the pixels in (y, x) ascending order
    //
    for (int j = 0; j < this->y_size; j++)
        for (int i = 0; i < this->x_size; i++) {
            assert(!file.eof());
            file.get(pixel);
            if (pixel) figure[j][i] = 1;
            else figure[j][i] = 0;
        }
    if (!file.eof()) {
        //std::cout << "remaining content of file:\n";
        while (!file.eof()) {
            file.get(pixel);
            //std::cout << "\t'" << pixel << "' (ASCII " << (unsigned)pixel % 256 << ")\n";
        }
    }

    file.close();
    this->image = figure;
} // make_vect

std::vector<std::vector<int>> VectorArray::make_mask(int r) {
    const int max_y = r + r + 1;
    const int center = r; // index counts from 0
    // Construct a 2D vector
    std::vector<std::vector<int>> mask(max_y, std::vector<int>(max_y));

    for (int y = 0; y < max_y; y++) {
        for (int x = 0; x < max_y; x++) {
            // Calculates if the square is inside a circle with radius r
            float dd = (x - center) * (x - center) + (y - center) * (y - center);
            if (r * r >= dd) mask[y][x] = 1;
            else mask[y][x] = 0;
        }
    }
    return mask;
}


bool VectorArray::overlap(int x, int y, int r) {

    assert(x >= 0);
    assert(x <= x_size);
    assert(y >= 0);
    assert(y <= y_size);
    assert(r >= 0);

    int x_min = -r;
    int x_max = r;
    int y_min = -r;
    int y_max = r;

    if (x <= r) x_min = -x;
    if ((this->x_size - 1 - x) <= r) x_max = this->x_size - x - 1;
    if (y <= r) y_min = -y;
    if ((this->y_size - 1 - y) <= r) y_max = this->y_size - y - 1;

    int tiles = 0;
    int matches = 0;
    for (int j = y_min; j <= y_max; j++) {
        for (int i = x_min; i <= x_max; i++) {
            // Calculates if the square is inside a circle with radius r
            float dd = (x+i - x) * (x+i - x) + (y+j - y) * (y+j - y);
            if (r * r >= dd) {
                tiles++;
                if(this->image[y+j][x+i] == 1) matches++;

            }
        }
    }

    if (matches/tiles > 0.9) return true;
    else return false;
}

void VectorArray::compress() {
    std::vector<std::vector<int>> figure(this->y_size, std::vector<int>(this->x_size));
    this->approximation = figure;

    int passes = 0;
    for (int y = 0; y <= this->y_size - 1; y++) {
        for (int x = 0; x <= this->x_size - 1; x++) {
            int r = 1;
            while (VectorArray::overlap(x, y, r)) {
                r++;
            }
            this->approximation[y][x] = r - 1;
        }
    }
}

void VectorArray::Clean_Approx(){
// Remove unnecessary points
    for (int y = 0; y <= this->y_size - 1; y++) {
        for (int x = 0; x <= this->x_size - 1; x++) {
            //std::cout << "Loop y, x = " << y << " " << x << std::endl;
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    // Avoids stepping outside the array
                    if(y-1 >= 0) if(x-1 >= 0) if(y+1 <= this->y_size-1) if(x+1 <= this->x_size-1){
                    if (this->approximation[y][x] < this->approximation[y + j][x + i]) {
                        this->approximation[y][x] = 0;
                    }} // if if
            }} // For j and i
    }} // For y and x
}
