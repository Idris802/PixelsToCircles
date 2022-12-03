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
    /*
     * Returns true if a circle with radius r fits on cell x, y
     */

    // Checking valid inputs
    assert(x >= 0);
    assert(x < x_size);
    assert(y >= 0);
    assert(y < y_size);
    assert(r >= 0);

    // Limiting search ranges
    int x_min = -r;
    int x_max = r;
    int y_min = -r;
    int y_max = r;

    if (x <= r) x_min = -x;
    if ((this->x_size - 1 - x) <= r) x_max = this->x_size - x - 1;
    if (y <= r) y_min = -y;
    if ((this->y_size - 1 - y) <= r) y_max = this->y_size - y - 1;

    int tiles = 0; // Number of tiles in the circle
    int matches = 0; // Number of lit up tiles
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
    // Checks if a percentage of the circle tiles are lit up
    if (matches/tiles > 0.9) return true;
    else return false;
}

void VectorArray::compress() {
    /*
     * Creates a map of the max radius for a circle that fits in each cell
     */

    // Creates a map of size y_size, x_size
    std::vector<std::vector<int>> figure(this->y_size, std::vector<int>(this->x_size));
    this->approximation = figure;

    // Tests which radius fits in each cell
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

void VectorArray::Clean_Approx(){
    /*
     * Remove unnecessary points from the approximation map
     */

    int r=1; // Radius around each cell we compare against
    // Iterates through each cell in the map
    for (int y = 0; y < this->y_size; y++) {
        for (int x = 0; x < this->x_size; x++) {
            // Checks each neighbor around in a square
            for (int j = -r; j <= r; j++) {
                for (int i = -r; i <= r; i++) {
                    // Avoids checking own cell
                    if((j!=0) || (i!=0)){
                        // Avoids stepping outside the array
                        if(y+j >= 0) if(x+i >= 0) if(y+j < this->y_size) if(x+i < this->x_size){
                            // Compares current cell with its neighbors
                            if (this->approximation[y][x] <= this->approximation[y + j][x + i]) {
                                this->approximation[y][x] = this->background_color;}
                    }} // if if
            }} // For j and i
    }} // For y and x
}


void VectorArray::PrintOut(std::ostream* target){
    /*
     * Prints out a vector representation of disks approximating the image
     */

    // Prints out:
    // x y
    // background color
    *target << this->x_size << " " << this->y_size << "\n" << this->background_color << "\n\n";

    // Creates a large vector array to hold the vector representation of the disks
    std::vector<std::vector<int>> figure(this->y_size, std::vector<int>(4));
    this->disks = figure;

    int index = 0;
    for (int y = 0; y < this->y_size; y++) {
        for (int x = 0; x < this->x_size; x++) {
            if(this->approximation[y][x] != this->background_color){
                // Disk {x_coordinate, y_coordinate, radius, color}
                this->disks[index] = {x, y, this->approximation[y][x], this->foreground_color};
                index++;
            }
        }
    }
    // Prints out number of disks
    *target << index <<"\n";

    // Iterates through each disk and prints out its contents
    for (int i = 0; i < index; i++){
        for (int element : this->disks[i]){
            *target << element << "\t";
        }
        *target << "\n";
    }
}

void VectorArray::vectorize(std::string input_filename, std::string output_filename){
    /*
     * A single function to convert a pixelmap to a vector representation of disks
     */

    VectorArray::make_vect(input_filename);
    VectorArray::compress();
    VectorArray::Clean_Approx();

    std::ofstream output(output_filename);
    VectorArray::PrintOut(&output);
    output.close();
}
