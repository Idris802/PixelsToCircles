#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

namespace project {
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
       if(!file.eof())
       {
          std::cout << "remaining content of file:\n";
          while(!file.eof())
          {
             file.get(pixel);
             std::cout << "\t'" << pixel << "' (ASCII " << (unsigned)pixel % 256 << ")\n";
          }
       }
       
       file.close();
       return figure;
    } // get_vect
} // namespace


int main(int argc, char** argv) {
    auto source = std::ifstream();
    auto columns = project::get_vect(argv[1]);

    std::cout << "\n-----\n-----\n-----\n";
    // Print out image
    //
    // you are printing it out in order of columns: note that this turns the picture around graphically!
    // but I left it as is, it's clearly what you were intending to do
    //
    for(std::vector<int> v : columns){

        for (int n : v){
            std::cout << n;
        } // for n in vector
        std::cout << "\n";
    } // for vector in columns

    std::cout << "\nsize of image = " << columns.size() << "x" << columns[0].capacity() << std::endl;
    return 0;
}
