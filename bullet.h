/***********************************************************************
 * Header File:
 *    Bullet
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Stuff that kills other things
 ************************************************************************/

#pragma once
#include "position.h"
#include "effect.h"
#include "bridge.hpp"
#include <list>
#include <cassert>

/*********************************************
 * BULLET
 * Something to shoot something else
 *********************************************/
class Bullet: public Flyer
{
protected:
   static Position dimensions;   // size of the screen
   int value;                 // how many points does this cost?
    
public:
   Bullet(double angle = 0.0, double speed = 30.0, double radius = 5.0, int value = 1);
   
   // setters
   void setValue(int newValue)   { value = newValue; }
   void move() override;
   
   // getters
   int getValue()          const { return value;  }

   // special functions
   virtual void death(std::list<Bullet *> & bullets, std::list<Effect*> * effect) {}
   virtual void input(bool isUp, bool isDown, bool isB) {}

protected:
   bool isOutOfBounds() const
   {
      return (pt.getX() < -radius || pt.getX() >= dimensions.getX() + radius ||
         pt.getY() < -radius || pt.getY() >= dimensions.getY() + radius);
   }
   void drawLine(const Position& begin, const Position& end,
                 double red = 1.0, double green = 1.0, double blue = 1.0) const;

   void drawDot(const Position& point, double radius = 2.0,
                double red = 1.0, double green = 1.0, double blue = 1.0) const;
   int    random(int    min, int    max);
   double random(double min, double max);
};

/*********************
 * PELLET
 * Small little bullet
 **********************/
class Pellet : public Bullet
{
public:
   Pellet(double angle, double speed = 15.0) : Bullet(angle, speed, 1.0, 1) {}
   
   void draw() override;
};

/*********************
 * BOMB
 * Things that go "boom"
 **********************/
class Bomb : public Bullet
{
private:
   int timeToDie;
public:
   Bomb(double angle, double speed = 10.0) : Bullet(angle, speed, 4.0, 4), timeToDie(60) {}
   
   void draw() override;
   void move() override;
   void death(std::list<Bullet *> & bullets, std::list<Effect*> * effect) override;
};

/*********************
 * Shrapnel
 * A piece that broke off of a bomb
 **********************/
class Shrapnel : public Bullet
{
private:
   int timeToDie;
   std::list<Effect*> * effects;
public:
   Shrapnel(const Bomb & bomb, std::list<Effect*> * effects) : effects(effects)
   {
      // how long will this one live?
      timeToDie = random(5, 15);
      
      // The speed and direction is random
      v.set(random(0.0, 6.2), random(10.0, 15.0));
      pt = bomb.getPosition();

      value = 0;
      
      radius = 3.0;
   }
   
   void draw() override;
   void move() override;
};


/*********************
 * MISSILE
 * Guided missiles
 **********************/
class Missile : public Bullet
{
private:
   std::list<Effect*> * effects;
public:
   Missile(double angle, std::list<Effect*>* effect, double speed = 10.0 ) : Bullet(angle, speed, 1.0, 3), effects(effect) {}
   
   void draw() override;
   void input(bool isUp, bool isDown, bool isB) override
   {
      if (isUp)
         v.turn(0.04);
      if (isDown)
         v.turn(-0.04);
   }
   void move() override;
};
