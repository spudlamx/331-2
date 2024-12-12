/***********************************************************************
 * Header File:
 *    GUN
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The gun at the bottom of the screen
 ************************************************************************/

#pragma once
#include "position.h"
#include "time.h"
#include "uiInteract.h"
#include "bullet.h"
#include <list>


/*********************************************
 * GUN
 * The gun at the bottom of the screen
 *********************************************/
class Gun
{
public:
   Gun(const Position & pt) : angle(0.78 /* 45 degrees */), pt(pt) {}  // 45 degrees initially
   void display() const;
   void interact(int clockwise, int counterclockwise);
   double getAngle() const { return angle; }

private:
   double angle;
   Position pt;
};

// THIS IS FOR THE PROXY GUN INTERFACE METHOD
//class Gun
//{
//public:
//   Gun(const Position & pt, std::list<Bullet*>* bullets) : angle(0.78 /* 45 degrees */), pt(pt), bullets(bullets) {}  // 45 degrees initially
//   virtual void display() const = 0;
//   virtual void interact(int clockwise, int counterclockwise) = 0;
//   virtual double getAngle() const = 0;
//   virtual void setGun(int level) = 0;
//   virtual void shoot(UserInput ui) = 0;
//   
//protected:
//   double angle;
//   Position pt;
//   std::list<Bullet*>* bullets;
//};
//
//
//
//class RealGun : public Gun
//{
//private:
//   int level;
//public:
//   RealGun(const Position & pt, int level, std::list<Bullet*>* bullets):Gun(pt, bullets), level(level){}
//   
//   virtual void display() const override;
//   virtual void interact(int clockwise, int counterclockwise) override;
//   virtual void setGun(int level) override{ level = level;}
//   virtual double getAngle() const override { return angle; }
//   virtual void shoot(UserInput ui) override
//   {
//      Bullet* p = nullptr;
//      if (ui.isSpace())
//         p = new Pellet(getAngle());
//      // missiles can be shot at level 2 and higher
//      else if (ui.isM() && level > 1)
//         p = new Missile(getAngle());
//      // bombs can be shot at level 3 and higher
//      else if (ui.isB() && level > 2)
//         p = new Bomb(getAngle());
//      
//      if (nullptr != p)
//         bullets->push_back(p);
//   }
//};
//
//class ProxyGun : public Gun
//{
//public:
//   ProxyGun(const Position & pt, std::list<Bullet*>* bullets):Gun(pt, bullets), real(nullptr){}
//   virtual double getAngle() const override
//   {
//      if (real) return real->getAngle();
//      return NULL;
//   };
//   virtual void display() const override
//   {
//      if (real) real->display();
//   }
//   virtual void interact(int clockwise, int counterclockwise) override
//   {
//      if (real) real->interact(clockwise, counterclockwise);
//   }
//   virtual void shoot(UserInput ui) override
//   {
//      if (real) real->shoot(ui);
//   }
//   virtual void setGun(int level) override
//   {
//      if (1 <= level)
//      {
//         if (!real)
//            real = new RealGun(this->pt, level, bullets);
//         else
//            real->setGun(level);
//      }
//      else
//      {
//         delete real;
//         real = nullptr;
//      }
//   };
//private:
//   RealGun* real = nullptr;
//};


