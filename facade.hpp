//
//  facade.hpp
//  Lab03
//
//  Created by Spencer Lamoreaux on 12/11/24.
//

#ifndef facade_hpp
#define facade_hpp

#include <stdio.h>
#include "position.h"
#include <string>
#include <cmath>
//#include <algorithm>
#include <sstream>
using namespace std;

class ogstream : public std::ostringstream
{
public:
   // constructors
   ogstream(): pt(0, 0) {}
   ogstream(const Position& pt) : pt(pt) {}
   ~ogstream() { flush(); }
   
   // Methods
   void flush();
   void setPosition(const Position& pt) { flush(); this->pt = pt; }
   ogstream& operator = (const Position& pt)
   {
      setPosition(pt);
      return *this;
   }

   void drawRectangle(const Position& pt, double angle = 0.0, double width = 10.0,
                      double height = 100.0, double red = 1.0, double green = 1.0, double blue = 1.0);

   void drawLine(const Position & begin, const Position & end,
                         double red = 1.0, double green = 1.0, double blue = 1.0) const;
   
   void drawDot(const Position& point, double radius,
                double red, double green, double blue) const;
   void drawDisk(const Position& center, double radius,
                 double red, double green, double blue) const;
   void drawBackground(double redBack, double greenBack, double blueBack) const;
   void drawText(const Position & topLeft, const char * text) const;
   void drawTextStr(const Position & topLeft, const string & text)
   {
      drawText(topLeft, text.c_str());
   }
   void drawTimer(double percent, double redFore, double greenFore, double blueFore,
                  double redBack, double greenBack, double blueBack) const;
   
   
private:
   Position pt;
   Position rotate(const Position& origin, double x, double y, double rotation);
   
};
#endif /* facade_hpp */

