#include "read.h"

std::vector<std::vector<int>> get_mask(int r){
    const int max_y = r+r+1;
    const int center = r; // index counts from 0
    // Construct 2D vector
    std::vector<std::vector<int>> mask(max_y, std::vector<int>(max_y));

    for(int y=0; y<max_y; y++){
        for(int x=0; x<max_y; x++){
            float dd = (x - center) * (x - center) + (y - center) * (y - center);
            if (r * r >= dd) mask[y][x] = 1;
            else mask[y][x] = 0;
        }
    }
    return mask;
}



int main(int argc, char** argv) {
    const int input = argc[1];
    auto columns = get_mask(input);


    for(std::vector<int> v : columns){

        for (int n : v){
            std::cout << n;
        } // for n in vector
        std::cout << "\n";
    } // for vector in columns

    std::cout << "\nsize of image = " << columns.size() << "x" << columns[0].capacity() << std::endl;
    return 0;
}