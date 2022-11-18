#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


namespace project {
    void in(std::istream *source) {
        int x;
        int y;
        int str4;
        *source >> x >> y >> str4;
        int first_str;
        int str2;
        int str3;
        *source >> first_str;  // read first element
        *source >> str2;
        *source >> str3;

        std::cout << x << " " << y << "\t" << str4 << "\n"
        << first_str << "\t" << str2 << "\t" << str3 << "\n";
    }

    void get_vect(std::string filename) {
        std::ifstream file(filename);
        int x;
        int y;
        file >> x >> y;

        std::cout << x << "\t" << y << "\n\n";

        std::vector<std::vector<int>> columns;
        std::string eachrow;

        while (std::getline(file, eachrow)) {
            std::vector<int> row;
            row.reserve(x);

            for (char x: eachrow) {
                row.push_back(int(x));
            }
            columns.push_back(row);
            std::cout << row.size() << std::endl;
        }

        for (std::vector<int> v: columns) {
            for (int i: v) {
                std::cout << i << " ";
            }
            std::cout << '\n' << std::endl;
        }
    }

}


int main() {
    auto source = std::ifstream();
    project::get_vect("../benchmark.0032.pxl");
    //project::in(&source);
    return 0;
}