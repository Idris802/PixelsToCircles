
#include <cassert>
#include <fstream>
#include <iostream>

#include "charmap.h"

int main(int argc, char** argv)
{
   assert(argc >= 3);
   
   diskgraphics::DiskVector dv;
   std::ifstream input(argv[1]);
   input >> dv;
   input.close();
   
   diskgraphics::Charmap cm(dv);
   cm.out(&std::cout, true);
   
   std::ofstream output(argv[2]);
   output << cm;
   output.close();
}
