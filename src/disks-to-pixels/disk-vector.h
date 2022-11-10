#ifndef DISK_VECTOR_GRAPHICS_H
#define DISK_VECTOR_GRAPHICS_H

#include <iostream>
#include <vector>

namespace diskgraphics
{
   struct Disk
   {
      float x = 0;  // x coordinate of the centre
      float y = 0;  // y coordinate of the centre
      float r = 0;  // radius
      unsigned char colour = 0;  // 0 is black, 255 is white
   };

   class DiskVector
   {
   public:
      void in(std::istream* source);  // read from *source
      
      int get_sizex() const { return this->px_size_x; }
      int get_sizey() const { return this->px_size_y; }
      unsigned char get_pixel(int x, int y) const;  // get pixel value at (x, y)
   
   private:
      int px_size_x = 0;  // how many pixels are we representing in x direction?
      int px_size_y = 0;  // how many pixels are we representing in y direction?
      unsigned char background = 127;
   
      std::vector<Disk> disks;
   };
}

std::istream& operator>>(std::istream& is, diskgraphics::Disk& d);
std::istream& operator>>(std::istream& is, diskgraphics::DiskVector& v);

#endif

