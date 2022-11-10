#include <cassert>

#include "disk-vector.h"

using namespace diskgraphics;

void DiskVector::in(std::istream* source)
{
   *source >> this->px_size_x >> this->px_size_y;  // read figure size in px
   unsigned bg_num;
   *source >> bg_num;  // read background colour
   this->background = bg_num;
   
   int N;  // read number of disks
   *source >> N;
   
   for(int i = 0; i < N; i++)
   {
      Disk d;
      *source >> d;  // read disk parameters
      this->disks.push_back(d);
   }
}
std::istream& operator>>(std::istream& is, DiskVector& v) {
   v.in(&is);
   return is;
}
std::istream& operator>>(std::istream& is, Disk& d) {
   is >> d.x >> d.y >> d.r;
   unsigned clr;
   is >> clr;
   d.colour = clr;
   return is;
}

unsigned char DiskVector::get_pixel(int x, int y) const
{
   assert(x >= 0);
   assert(y >= 0);
   assert(x < this->px_size_x);
   assert(y < this->px_size_y);

   char colour = this->background;
   for(auto i = this->disks.begin(); i != this->disks.end(); i++)
   {
      float dd = (x - i->x)*(x - i->x) + (y - i->y)*(y - i->y);
      if(i->r * i->r >= dd) colour = i->colour;
   }
   return colour;
}
