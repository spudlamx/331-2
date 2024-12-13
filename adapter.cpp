//
//  adapter.cpp
//  Skeet
//
//  Created by Spencer Lamoreaux on 12/12/24.
//

#include "adapter.hpp"

#include "position.h"
#include <cassert>
#include <sstream>
using namespace std;

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_18
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied
#define _USE_MATH_DEFINES
#include <math.h>
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // _WIN32



/***************************************************************/
/***************************************************************/
/*                             DRAW                            */
/***************************************************************/
/***************************************************************/

/************************************************************************
 * DRAW Disk
 * Draw a filled circule at [center] with size [radius]
 *************************************************************************/
void drawDisk(const Position& center, double radius,
              double red, double green, double blue)
{
   assert(radius > 1.0);
   const double increment = M_PI / radius;  // bigger the circle, the more increments

   // begin drawing
   glBegin(GL_TRIANGLES);
   glColor3f((GLfloat)red /* red % */, (GLfloat)green /* green % */, (GLfloat)blue /* blue % */);

   // three points: center, pt1, pt2
   Position pt1;
   pt1.setX(center.getX() + (radius * cos(0.0)));
   pt1.setY(center.getY() + (radius * sin(0.0)));
   Position pt2(pt1);

   // go around the circle
   for (double radians = increment;
      radians <= M_PI * 2.0 + .5;
      radians += increment)
   {
      pt2.setX(center.getX() + (radius * cos(radians)));
      pt2.setY(center.getY() + (radius * sin(radians)));

      glVertex2f((GLfloat)center.getX(), (GLfloat)center.getY());
      glVertex2f((GLfloat)pt1.getX(), (GLfloat)pt1.getY());
      glVertex2f((GLfloat)pt2.getX(), (GLfloat)pt2.getY());

      pt1 = pt2;
   }

   // complete drawing
   glEnd();
}

/*********************************************
 * STANDARD DRAW
 * Draw a standard bird: blue center and white outline
 *********************************************/
void drawStandard(Position pt, double radius)
{
   drawDisk(pt, radius - 0.0, 1.0, 1.0, 1.0); // white outline
   drawDisk(pt, radius - 3.0, 0.0, 0.0, 1.0); // blue center
}

/*********************************************
 * FLOATER DRAW
 * Draw a floating bird: white center and blue outline
 *********************************************/
void drawFloater(Position pt, double radius)
{
   drawDisk(pt, radius - 0.0, 0.0, 0.0, 1.0); // blue outline
   drawDisk(pt, radius - 4.0, 1.0, 1.0, 1.0); // white center
}

/*********************************************
 * CRAZY DRAW
 * Draw a crazy bird: concentric circles in a course gradient
 *********************************************/
void drawCrazy(Position pt, double radius)
{
   drawDisk(pt, radius * 1.0, 0.0, 0.0, 1.0); // bright blue outside
   drawDisk(pt, radius * 0.8, 0.2, 0.2, 1.0);
   drawDisk(pt, radius * 0.6, 0.4, 0.4, 1.0);
   drawDisk(pt, radius * 0.4, 0.6, 0.6, 1.0);
   drawDisk(pt, radius * 0.2, 0.8, 0.8, 1.0); // almost white inside

}

/*********************************************
 * SINKER DRAW
 * Draw a sinker bird: black center and dark blue outline
 *********************************************/
void drawSinker(Position pt, double radius)
{
   drawDisk(pt, radius - 0.0, 0.0, 0.0, 0.8);
   drawDisk(pt, radius - 4.0, 0.0, 0.0, 0.0);
}


/*************************************************************************
 * GL VERTEXT POINT
 * Just a more convenient format of glVertext2f
 *************************************************************************/
inline void glVertexPoint(const Position& point)
{
   glVertex2f((GLfloat)point.getX(), (GLfloat)point.getY());
}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void drawLine(const Position& begin, const Position& end,
                      double red, double green, double blue)
{
   // Get ready...
   glBegin(GL_LINES);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

   // Draw the actual line
   glVertexPoint(begin);
   glVertexPoint(end);

   // Complete drawing
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW DOT
 * Draw a single point (square actually on the screen, r pixels by r pixels
 *************************************************************************/
void drawDot(const Position& point, double radius,
                     double red, double green, double blue)
{
   // Get ready, get set...
   glBegin(GL_TRIANGLE_FAN);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);
   double r = radius / 2.0;

   // Go...
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() + r));
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() + r));

   // Done!  OK, that was a bit too dramatic
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/*********************************************
 * PELLET draw
 * Draw a pellet - just a 3-pixel dot
 *********************************************/
void drawPellet(Position pt, double radius)
{
      drawDot(pt, 3.0, 1.0, 1.0, 0.0);
}

/*********************************************
 * BOMB draw
 * Draw a bomb - many dots to make it have a soft edge
 *********************************************/
void drawBomb(Position pt, double radius)
{
   // Bomb actually has a gradient to cut out the harsh edges
   drawDot(pt, radius + 2.0, 0.50, 0.50, 0.00);
   drawDot(pt, radius + 1.0, 0.75, 0.75, 0.00);
   drawDot(pt, radius + 0.0, 0.87, 0.87, 0.00);
   drawDot(pt, radius - 1.0, 1.00, 1.00, 0.00);
}

/*********************************************
 * SHRAPNEL draw
 * Draw a fragment - a bright yellow dot
 *********************************************/
void drawShrapnel(Position pt, double radius)
{
       drawDot(pt, radius, 1.0, 1.0, 0.0);
}

/*********************************************
 * MISSILE draw
 * Draw a missile - a line and a dot for the fins
 *********************************************/
void drawMissile(Position pt, Velocity v, double radius)
{
   // missile is a line with a dot at the end so it looks like fins.
   Position ptNext(pt);
   ptNext.add(v);
   drawLine(pt, ptNext, 1.0, 1.0, 0.0);
   drawDot(pt, 3.0, 1.0, 1.0, 1.0);
}

/************************************************************************
 * FRAGMENT draw
 * Draw the fragment on the screen
 *************************************************************************/
void drawFragment(Position pt, double size, double age)
{
    // Draw this sucker
    glBegin(GL_TRIANGLE_FAN);
    
    // the color is a function of age - fading to black
    glColor3f((GLfloat)age, (GLfloat)age, (GLfloat)age);
    
    // draw the fragment
    glVertex2f((GLfloat)(pt.getX() - size), (GLfloat)(pt.getY() - size));
    glVertex2f((GLfloat)(pt.getX() + size), (GLfloat)(pt.getY() - size));
    glVertex2f((GLfloat)(pt.getX() + size), (GLfloat)(pt.getY() + size));
    glVertex2f((GLfloat)(pt.getX() - size), (GLfloat)(pt.getY() + size));
    glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
    glEnd();
}

/************************************************************************
 * STREEK draw
 * Draw the shrapnel streek on the screen
 *************************************************************************/
void drawStreek(Position pt, Position ptEnd, double age)
{
    // Draw this sucker
    glBegin(GL_LINES);
    glColor3f((GLfloat)age, (GLfloat)age, (GLfloat)age);

    // Draw the actual line
    glVertex2f((GLfloat)pt.getX(), (GLfloat)pt.getY());
    glVertex2f((GLfloat)ptEnd.getX(), (GLfloat)ptEnd.getY());

    glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
    glEnd();
}

/************************************************************************
 * EXHAUST draw
 * Draw a missile exhaust on the screen
 *************************************************************************/
void drawExhaust(Position pt, Position ptEnd, double age)
{
   // Draw this sucker
   glBegin(GL_LINES);
   glColor3f((GLfloat)age, (GLfloat)age, (GLfloat)age);

   // Draw the actual line
   glVertex2f((GLfloat)pt.getX(), (GLfloat)pt.getY());
   glVertex2f((GLfloat)ptEnd.getX(), (GLfloat)ptEnd.getY());

   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

void drawBackground(Position dimensions, double redBack, double greenBack, double blueBack)
{
   glBegin(GL_TRIANGLE_FAN);

   // two rectangles is the fastest way to fill the screen.
   glColor3f((GLfloat)redBack /* red % */, (GLfloat)greenBack /* green % */, (GLfloat)blueBack /* blue % */);
   glVertex2f((GLfloat)0.0, (GLfloat)0.0);
   glVertex2f((GLfloat)dimensions.getX(), (GLfloat)0.0);
   glVertex2f((GLfloat)dimensions.getX(), (GLfloat)dimensions.getY());
   glVertex2f((GLfloat)0.0, (GLfloat)dimensions.getY());

   glEnd();
}

/************************************************************************
 * DRAW Timer
 * Draw a large timer on the screen
 *  INPUT percent     Amount of time left
 *        Foreground  Foreground color
 *        Background  Background color
 *************************************************************************/
void drawTimer(Position dimensions, double percent,
                     double redFore, double greenFore, double blueFore,
                     double redBack, double greenBack, double blueBack)
{
   double radians;

   GLfloat length = (GLfloat)dimensions.getX();
   GLfloat half = length / (GLfloat)2.0;

   // do the background stuff
   drawBackground(dimensions, redBack, greenBack, blueBack);

   // foreground stuff
   radians = percent * M_PI * 2.0;
   GLfloat x_extent = half + length * (GLfloat)sin(radians);
   GLfloat y_extent = half + length * (GLfloat)cos(radians);

   // get read to draw the triangles
   glBegin(GL_TRIANGLE_FAN);
   glColor3f((GLfloat)redFore /* red % */, (GLfloat)greenFore /* green % */, (GLfloat)blueFore /* blue % */);
   glVertex2f(half, half);

   // fill in the triangles, one eight at a time
   switch ((int)(percent * 8.0))
   {
   case 7: // 315 - 360
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(0.0, 0.0);
      glVertex2f(0.0, length);
      break;
   case 6: // 270 - 315
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(0.0, 0.0);
      glVertex2f(0.0, half);
      break;
   case 5: // 225 - 270
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(0.0, 0.0);
      break;
   case 4: // 180 - 225
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(half, 0.0);
      break;
   case 3: // 135 - 180
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, half);
      glVertex2f(length, 0.0);
      break;
   case 2: // 90 - 135 degrees
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, half);
      break;
   case 1: // 45 - 90 degrees
      glVertex2f(half, length);
      glVertex2f(length, length);
      break;
   case 0: // 0 - 45 degrees
      glVertex2f(half, length);
      break;
   }
   glVertex2f(x_extent, y_extent);

   // complete drawing
   glEnd();

   // draw the red line now
   glBegin(GL_LINES);
   glColor3f((GLfloat)0.6, (GLfloat)0.0, (GLfloat)0.0);
   glVertex2f(half, half);
   glVertex2f(x_extent, y_extent);
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************
 * DRAW BULLSEYE
 * Put a bullseye on the screen
 ************************/
void drawBullseye(Position dimensions, double angle)
{
   // find where we are pointing
   double distance = dimensions.getX();
   GLfloat x = dimensions.getX() - distance * cos(angle);
   GLfloat y = distance * sin(angle);

   // draw the crosshairs
   glBegin(GL_LINES);
   glColor3f((GLfloat)0.6, (GLfloat)0.6, (GLfloat)0.6);

   // Draw the actual lines
   glVertex2f(x - 10.0, y);
   glVertex2f(x + 10.0, y);

   glVertex2f(x, y - 10.0);
   glVertex2f(x, y + 10.0);

   glColor3f((GLfloat)0.2, (GLfloat)0.2, (GLfloat)0.2);
   glVertex2f(dimensions.getX(), 0.0);
   glVertex2f(x, y);

   // Complete drawing
   glEnd();
}

/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text
 *          text      The text to be displayed
 ************************************************************************/
void drawText(const Position& topLeft, const char* text)
{
   void* pFont = GLUT_TEXT;
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);

   // prepare to output the text from the top-left corner
   glRasterPos2f((GLfloat)topLeft.getX(), (GLfloat)topLeft.getY());

   // loop through the text
   for (const char* p = text; *p; p++)
      glutBitmapCharacter(pFont, *p);
}
void drawText(const Position & topLeft, const string & text)
{
   drawText(topLeft, text.c_str());
}

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  origin   The center point we will rotate around
 *           x,y      Offset from center that we will be rotating
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
Position rotate(const Position& origin,
  double x, double y, double rotation)
{
  // because sine and cosine are expensive, we want to call them only once
  double cosA = cos(rotation);
  double sinA = sin(rotation);

  // start with our original point
  Position ptReturn(origin);

  // find the new values
  ptReturn.addX(x * cosA - y * sinA);
  ptReturn.addY(y * cosA + x * sinA /*center of rotation*/);

  return ptReturn;
}

/************************************************************************
* DRAW RECTANGLE
* Draw a rectangle on the screen from the beginning to the end.
*************************************************************************/
void drawRectangle(const Position& pt,
                  double angle,
                  double width,
                  double height,
                  double red,
                  double green,
                  double blue)
{
  // Get ready...
  glBegin(GL_QUADS);
  glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

  // Draw the actual line
  glVertexPoint(rotate(pt,  width / 2.0,  height / 2.0, angle));
  glVertexPoint(rotate(pt,  width / 2.0, -height / 2.0, angle));
  glVertexPoint(rotate(pt, -width / 2.0, -height / 2.0, angle));
  glVertexPoint(rotate(pt, -width / 2.0,  height / 2.0, angle));
  glVertexPoint(rotate(pt,  width / 2.0,  height / 2.0, angle));

  // Complete drawing
  glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
  glEnd();
}
