#ifndef CANVAS_H
#define CANVAS_H

#include <vector>

#include "Color.h"

class Canvas
{
public:
  Canvas(int w, int h): width(w), height(h), pixels{(size_t)w*h,Color(0,0,0)} 
  {
    
  }

  void write_pixel(int x, int y, Color col)
  {
    if (y < 0 || y > height || x < 0 || x > width) return;
    
    pixels[y*width+x] = col;
  }

  Color pixel_at(int x, int y)
  {
    return pixels[y*width+x];
  }

  std::string canvas_to_ppm(bool line_limit = true)
  {
    std::string ppm_file;
    ppm_file += "P3\n";
    ppm_file += std::to_string(width) + " " + std::to_string(height) + "\n";
    ppm_file += "255\n";

    for (int i = 0; i < height; ++i)
    {
      int line_count = 0;
      for (int j = 0; j < width; ++j)
      {
        Color c = pixels[i*width+j];
        int r = round(c.red() * 255) > 255 ? 255 : (round(255 * c.red()) < 0 ? 0 : round(c.red() * 255));
        std::string seg1 = std::to_string(r) + " ";
        // if (line_count + 1 + seg1.length() > 70)
        // {
        //   line_count = 0;
        //   ppm_file += "\n";
        // }
        // else
        // {
        //   ppm_file += seg1;
        //   line_count += seg1.length();
        // }
        int g = round(c.green() * 255) > 255 ? 255 : (round(255 * c.red()) < 0 ? 0 : round(c.green() * 255));
        std::string seg2 = std::to_string(g) + " ";
        // if (line_count + 1 + seg2.length() > 70)
        // {
        //   line_count = 0;
        //   ppm_file += "\n";
        // }
        // else
        // {
        //   ppm_file += seg2;
        //   line_count += seg2.length();
        // }
        int b = round(c.blue() * 255) > 255 ? 255 : (round(255 * c.blue()) < 0 ? 0 : round(c.blue() * 255));
        std::string seg3 = std::to_string(b) + " ";
        // if (line_count + 1 + seg3.length() > 70)
        // {
        //   line_count = 0;
        //   ppm_file += "\n";
        // }
        // else
        // {
        //   ppm_file += seg3;
        //   line_count += seg3.length();
        // }

        ppm_file += seg1 + "\n" + seg2 + "\n" + seg3 + "\n";
      }

      line_count = 0;
      ppm_file += "\n";
    }

    return ppm_file;
  }

  int width;
  int height;
  std::vector<Color> pixels;
};

#endif // CANVAS_H
