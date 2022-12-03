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

    for (int y = 0; y < this->y_size; y++) {
        for (int x = 0; x < this->x_size; x++) {
            int r = 1;
            while (VectorArray::overlap(x, y, r)) {
                r++;
            }
            this->approximation[y][x] = r - 1;
        }
    }
}

void VectorArray::Clean_Approx2(){
// Remove unnecessary points
    for (int y = 0; y < this->y_size; y++) {
        for (int x = 0; x < this->x_size; x++) {
            //std::cout << "Loop y, x = " << y << " " << x << std::endl;
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    // Avoids stepping outside the array
                    if(y+j >= 0) if(x+i >= 0) if(y+j < this->y_size) if(x+i < this->x_size){
                    if (this->approximation[y][x] < this->approximation[y + j][x + i]) {
                        this->approximation[y][x] = 0;
                    }} // if if
            }} // For j and i
    }} // For y and x
}

void VectorArray::Clean_Approx(){
// Remove unnecessary points
int r=2;
    for (int y = 0; y < this->y_size; y++) {
        for (int x = 0; x < this->x_size; x++) {
            //std::cout << "Loop y, x = " << y << " " << x << std::endl;
            for (int j = -r; j <= r; j++) {
                for (int i = -r; i <= r; i++) {
                    // Avoids checking own cell
                    if((j!=0) || (i!=0)){
                        // Avoids stepping outside the array
                        if(y+j >= 0) if(x+i >= 0) if(y+j < this->y_size) if(x+i < this->x_size){
                            if (this->approximation[y][x] <= this->approximation[y + j][x + i]) {
                                this->approximation[y][x] = 0;}
                    }} // if if
            }} // For j and i
    }} // For y and x
}

/*
void VectorArray::PrintOut(std::ostream* target){
    *target << this->x_size << " " << this->y_size << "\n";
    if(!this->data) return;
    for(int y = 0; y < this->y_size; y++)
    {
        for(int x = 0; x < this->x_size; x++)
            if(num) *target << (unsigned)(this->get_pixel(x, y)) << "\t";
            else *target << this->get_pixel(x, y);
        if(num) *target << "\n";
    }
}
*/