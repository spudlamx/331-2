/***********************************************************************
 * Source File:
 *    Bullet
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Stuff that kills other things
 ************************************************************************/

#include "bullet.h"
#include "facade.hpp"

/*********************************************
 * BULLET constructor
 *********************************************/
Bullet::Bullet(double angle, double speed, double radius, int value) :
   dead(false), radius(radius), value(value)
{
   // set the initial position
   pt.setX(dimensions.getX() - 1.0);
   pt.setY(1.0);
   assert(pt.getX() > 100.0);

   // set the initial velocity
   v.setDx(-speed * cos(angle));
   v.setDy(speed * sin(angle));
   assert(v.getDx() <= 0.0);
   assert(v.getDy() >= 0.0);
}

/*********************************************
 * BOMB DEATH
 * Bombs have a tendency to explode!
 *********************************************/
void Bomb::death(std::list<Bullet*>& bullets)
{
   for (int i = 0; i < 20; i++)
      bullets.push_back(new Shrapnel(*this));
}

 /***************************************************************/
 /***************************************************************/
 /*                             MOVE                            */
 /***************************************************************/
 /***************************************************************/

/*********************************************
 * BULLET MOVE
 * Move the bullet along by one time period
 *********************************************/
void Bullet::move(std::list<Effect*> & effects)
{
   // inertia
   pt.add(v);

   // out of bounds checker
   if (isOutOfBounds())
      kill();
}

/*********************************************
 * BOMB MOVE
 * Move the bomb along by one time period
 *********************************************/
void Bomb::move(std::list<Effect*> & effects)
{
    // kill if it has been around too long
    timeToDie--;
    if (!timeToDie)
        kill();

    // do the inertia thing
    Bullet::move(effects);
}

/*********************************************
 * MISSILE MOVE
 * Move the missile along by one time period
 *********************************************/
void Missile::move(std::list<Effect*> & effects)
{
    // kill if it has been around too long
   effects.push_back(new Exhaust(pt, v));

    // do the inertia thing
    Bullet::move(effects);
}

/*********************************************
 * SHRAPNEL MOVE
 * Move the shrapnel along by one time period
 *********************************************/
void Shrapnel::move(std::list<Effect*> & effects)
{
    // kill if it has been around too long
    timeToDie--;
    if (!timeToDie)
        kill();

    // add a streek
    effects.push_back(new Streek(pt, v));
    
    // do the usual bullet stuff (like inertia)
    Bullet::move(effects);
}

/***************************************************************/
/***************************************************************/
/*                            OUTPUT                           */
/***************************************************************/
/***************************************************************/


/*********************************************
 * PELLET OUTPUT
 * Draw a pellet - just a 3-pixel dot
 *********************************************/
void Pellet::output(ogstream* gout)
{
   if (!isDead())
      gout->drawDot(pt, 3.0, 1.0, 1.0, 0.0);
}

/*********************************************
 * BOMB OUTPUT
 * Draw a bomb - many dots to make it have a soft edge
 *********************************************/
void Bomb::output(ogstream* gout)
{
   if (!isDead())
   {
       // Bomb actually has a gradient to cut out the harsh edges
      gout->drawDot(pt, radius + 2.0, 0.50, 0.50, 0.00);
      gout->drawDot(pt, radius + 1.0, 0.75, 0.75, 0.00);
      gout->drawDot(pt, radius + 0.0, 0.87, 0.87, 0.00);
      gout->drawDot(pt, radius - 1.0, 1.00, 1.00, 0.00);
   }
}

/*********************************************
 * SHRAPNEL OUTPUT
 * Draw a fragment - a bright yellow dot
 *********************************************/
void Shrapnel::output(ogstream* gout)
{
    if (!isDead())
       gout->drawDot(pt, radius, 1.0, 1.0, 0.0);
}

/*********************************************
 * MISSILE OUTPUT
 * Draw a missile - a line and a dot for the fins
 *********************************************/
void Missile::output(ogstream* gout)
{
    if (!isDead())
    {
        // missile is a line with a dot at the end so it looks like fins.
        Position ptNext(pt);
        ptNext.add(v);
        gout->drawLine(pt, ptNext, 1.0, 1.0, 0.0);
        gout->drawDot(pt, 3.0, 1.0, 1.0, 1.0);
    }
}

/***************************************************************/
/***************************************************************/
/*                             MISC.                           */
/***************************************************************/
/***************************************************************/

/******************************************************************
 * RANDOM
 * This function generates a random number.
 ****************************************************************/
int Bullet::random(int min, int max)
{
   assert(min < max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);
   return num;
}
double Bullet::random(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   assert(min <= num && num <= max);
   return num;
}
