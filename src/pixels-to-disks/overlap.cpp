#include "read.h"


int main(int argc, char** argv) {
    VectorArray image;
    auto array = image.get_vect(argv[1]);
    const int input = std::stoi(argv[2]);
    auto mask = image.make_mask(input);



    return 0;
}