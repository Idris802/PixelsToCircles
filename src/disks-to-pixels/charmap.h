#ifndef CHARMAP_H
#define CHARMAP_H

#include <cassert>

#include "disk-vector.h"

namespace diskgraphics
{
   class Charmap
   {
   public:
      Charmap() {}
      ~Charmap() { if(this->data) delete[] this->data; }
      
      Charmap(const Charmap& orig);
      Charmap& operator=(const Charmap& rhs);
      
      Charmap(const DiskVector& orig);  // create from disk vector
      
      unsigned char get_pixel(int x, int y) const {
         assert(x >= 0); assert(y >= 0); assert(x < this->sizex); assert(y < this->sizey); assert(data);
         return this->data[y*this->sizex + x];
      }
      void set_pixel(int x, int y, unsigned char colour)
      {
         assert(x >= 0); assert(y >= 0); assert(x < this->sizex); assert(y < this->sizey); assert(data);
         this->data[y*this->sizex + x] = colour;
      }
      
      void out(std::ostream* target, bool num) const;
      
   private:
      int sizex = 0;  // pixels in x direction
      int sizey = 0;  // pixels in y direction
      unsigned char* data = nullptr;
   };
}

std::ostream& operator<<(std::ostream& os, const diskgraphics::Charmap& cm);

#endif
