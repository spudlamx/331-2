/***********************************************************************
 * Source File:
 *    RealGun
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The gun at the bottom of the screen
 ************************************************************************/

#include "gun.h"
#include "adapter.hpp"



 /*********************************************
  * GUN : DISPLAY
  * Display the gun on the screen
  *********************************************/
void Gun::display() const
{
   drawRectangle(pt, M_PI_2 - angle, 10.0, 100.0, 1.0, 1.0, 1.0);
}

/*********************************************
 * Gun : INTERACT
 * Move the Gun
 *********************************************/
void Gun::interact(int clockwise, int counterclockwise)
{
   // move it
   if (clockwise > 0)
   {
      angle += (clockwise > 10) ? 0.06 : 0.025;
      if (angle > M_PI_2)
         angle = M_PI_2;
   }
   if (counterclockwise > 0)
   {
      angle -= (clockwise > 10) ? 0.06 : 0.025;
      if (angle < 0.0)
         angle = 0.0;
   }
}
