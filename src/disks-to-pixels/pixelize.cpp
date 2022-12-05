
#include <cassert>
#include <fstream>
#include <iostream>

#include "charmap.h"
std::vector<std::vector<int>> make_vect(std::string filename) {
    /*
    * Based on code by Martin Thomas Horsch
    */
    // Read from start of file
    std::ifstream file(filename);
    int x_size;
    int y_size;
    file >> x_size >> y_size;

    // construct 2D vector where the outer vector has y elements, each of which is a vector with x elements
    std::vector<std::vector<int>> figure(y_size, std::vector<int>(x_size));

    // attention! there is a line break character that we need to get rid of
    char pixel;
    file.get(pixel);

    // Reads in from file
    for (int j = 0; j < y_size; j++)
        for (int i = 0; i < x_size; i++) {
            assert(!file.eof());
            file.get(pixel);
            if (pixel) figure[j][i] = 1;
            else figure[j][i] = 0;
        }

    file.close();
    return figure;
} // make_vect

int main(int argc, char** argv)
{
   assert(argc >= 3);
   
   diskgraphics::DiskVector dv;
   std::ifstream input(argv[1]);
   input >> dv;
   input.close();
   
   diskgraphics::Charmap cm(dv);
   //cm.out(&std::cout, true);
   
   std::ofstream output(argv[2]);
   output << cm;
   output.close();

    std::vector<std::vector<int>> our_image = make_vect(argv[2]);
    std::cout << "Our image \n";
    for (std::vector<int> v : our_image){
        for (int n : v){
            std::cout << n;
        }
        std::cout << std::endl;
    }
}
