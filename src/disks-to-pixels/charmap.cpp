#include "charmap.h"

using namespace diskgraphics;

Charmap::Charmap(const Charmap& orig)
{
   this->data = new unsigned char[orig.sizex*orig.sizey]();
   if(orig.data) std::copy(orig.data, orig.data + orig.sizex*orig.sizey, this->data);
}

Charmap& Charmap::operator=(const Charmap& rhs)
{
   if(&rhs == this) return *this;

   if(this->sizex*this->sizey != rhs.sizex*rhs.sizey)
   {
      if(this->data) delete[] this->data;
      this->data = new unsigned char[rhs.sizex*rhs.sizey]();
   }
   if(rhs.data) std::copy(rhs.data, rhs.data + rhs.sizex*rhs.sizey, this->data);
   return *this;
}

// create a pixel representation from a disk vector
Charmap::Charmap(const DiskVector& orig)
{
   this->sizex = orig.get_sizex();
   this->sizey = orig.get_sizey();
   this->data = new unsigned char[this->sizex*this->sizey]();
   
   for(int y = 0; y < this->sizey; y++)
      for(int x = 0; x < this->sizex; x++)
         this->set_pixel(x, y, orig.get_pixel(x, y));
}

// output, flag "num" controls whether we output chars or numbers
void Charmap::out(std::ostream* target, bool num) const
{
   *target << this->sizex << " " << this->sizey << "\n";
   if(!this->data) return;
   for(int y = 0; y < this->sizey; y++)
   {
      for(int x = 0; x < this->sizex; x++)
         if(num) *target << (unsigned)(this->get_pixel(x, y)) << "\t";
         else *target << this->get_pixel(x, y);
      if(num) *target << "\n";
   }
}

std::ostream& operator<<(std::ostream& os, const Charmap& cm)
{
   cm.out(&os, false);
   return os;
}
