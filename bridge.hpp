//
//  bridge.hpp
//  Skeet
//
//  Created by Spencer Lamoreaux on 12/11/24.
//

#ifndef bridge_hpp
#define bridge_hpp

#include <stdio.h>
#include "position.h"

class Flyer
{
protected:
   Position pt;               // position of the bullet
   Velocity v;                // velocity of the bullet
   double radius;             // the size (radius) of the bullet
   bool dead;                 // is this bullet dead?
public:
   Flyer() : dead(false) {}
   Flyer(double radius) : dead(false), radius(radius) {}
   Flyer(Position pt) : dead(false), pt(pt) {}
   Position getPosition()     const { return pt;     }
   Velocity getVelocity()     const { return v;      }
   double getRadius()      const { return radius; }
   virtual void draw() = 0;
   virtual void move() = 0;
   void kill()                      { dead = true; }
   bool isDead()           const { return dead;   }
   
};

#endif /* bridge_hpp */
