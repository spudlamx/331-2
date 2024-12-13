//
//  adapter.hpp
//  Skeet
//
//  Created by Spencer Lamoreaux on 12/12/24.
//

#ifndef adapter_hpp
#define adapter_hpp

#include <stdio.h>
#include <string>
using namespace::std;
class Position;
class Velocity;

// Helper functions
Position rotate(const Position& origin, double x, double y, double rotation);
inline void glVertexPoint(const Position& point);
void drawDisk(const Position& center, double radius, double red, double green, double blue);
void drawLine(const Position& begin, const Position& end, double red, double green, double blue);
void drawDot(const Position& point, double radius, double red, double green, double blue);
void drawRectangle(const Position& pt, double angle = 0.0, double width = 10.0, double height = 100.0, double red = 1.0, double green = 1.0, double blue = 1.0);


// Birds
void drawStandard(Position pt, double radius);
void drawFloater(Position pt, double radius);
void drawCrazy(Position pt, double radius);
void drawSinker(Position pt, double radius);

// Bullets
void drawPellet(Position pt, double radius);
void drawBomb(Position pt, double radius);
void drawShrapnel(Position pt, double radius);
void drawMissile(Position pt, Velocity v, double radius);

// Effects
void drawFragment(Position pt, double size, double age);
void drawStreek(Position pt, Position ptEnd, double age);
void drawExhaust(Position pt, Position ptEnd, double age);

// Skeet
void drawBackground(Position dimensions, double redBack, double greenBack, double blueBack);
void drawTimer(Position dimensions, double percent, double redFore, double greenFore, double blueFore, double redBack, double greenBack, double blueBack);
void drawBullseye(Position dimensions, double angle);
void drawText(const Position& topLeft, const char* text);
void drawText(const Position & topLeft, const string & text);


#endif /* adapter_hpp */
