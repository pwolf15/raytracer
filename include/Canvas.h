#ifndef CANVAS_H
#define CANVAS_H

#include <vector>

#include "Color.h"

class Canvas
{
public:
  Canvas(int w, int h): width(w), height(h), pixels{w*h,Color(0,0,0)} 
  {
    
  }

  void write_pixel(int r, int c, Color col)
  {
    pixels[r*width+c] = col;
  }

  Color pixel_at(int r, int c)
  {
    return pixels[r*width+c];
  }

  int width;
  int height;
  std::vector<Color> pixels;
};

#endif // CANVAS_H