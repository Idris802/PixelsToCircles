#include <iostream>
#include <fstream>

namespace project {
    void in(std::istream *source) {
        int x;
        int y;
        *source >> x >> y;
        unsigned first_str;
        unsigned str2;
        unsigned str3;
        *source >> first_str;  // read first str
        *source >> str2;  // read background colour
        *source >> str3;  // read background colour

        std::cout << x << " " << y << "\n"
        << first_str << "\t" << str2 << "\t" << str3 << "\n";
    }

}


int main() {
    auto source = std::ifstream("../benchmark.0032.pxl");
    project::in(&source);
    return 0;
}