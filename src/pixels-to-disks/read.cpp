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

        std::vector<std::vector<int>> columns;
        std::string image;

        while (std::getline(file, image)) {
            int num = 0;
            std::vector<int> row;
            row.reserve(x);

            for (int bit: image) {
                if (num % x == 0) {
                    std::cout << std::endl;
                    //std::vector<int> row;
                    //row.reserve(x);
                    row.clear(); // Removes all elements from the vector
                }
                if (bit == -1) {
                    row[num % x] = -bit;
                }
                else{
                    row[num % x] = bit;
                }

                // This is the one that prints current bit
                //std::cout << row[num % x];

                if (num % x == (x-1)){
                    // Print out row
                    for (int j=0; j<row.capacity(); j++){std::cout << row[j];}
                    // Append row to columns
                    //columns.push_back(row);
                    //columns[((num+1)/x) - 1] = row;
                    //std::copy(row.begin(), row.end(), std::back_inserter(columns));
                    std::vector<int> v2;
                    v2.assign(row.begin(), row.end());
                    columns.push_back(v2);
                }
                num++;
            } // for bit in image

        } // while

        return columns;
    } // get_vect

} // namespace


int main() {
    auto source = std::ifstream();
    std::vector<std::vector<int>> columns = project::get_vect("../benchmark.0032.pxl");
    //project::in(&source);

    std::cout << "\n-----\n-----\n-----\n";
    // Print out image
    for(std::vector<int> v : columns){
        std::cout << "\n";
        for (int n : v){
            std::cout << n;
        } // for n in vector

    } // for vector in columns
    std::cout << "\nsize of image = " << columns.size() << "x" << columns[0].capacity() << std::endl;
    return 0;
}