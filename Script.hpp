#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include "Image.hpp"

namespace prog
{
  class Script
  {
  public: 
    Script(const std::string &filename);
    ~Script();
    void run();
  private:
    // Current image.
    Image *image;
    // Input stream for reading script commands.
    std::ifstream input;
  private:
    // Private functions
    void clear_image_if_any();
    void open();
    void blank();
    void save();
    void invert();
    void to_gray_scale();
    void replace(const rgb_value& red, const rgb_value& green, const rgb_value& blue, const rgb_value& red_replace, const rgb_value& green_replace, const rgb_value& blue_replace);
    void v_mirror();
    void h_mirror();
    void add(const std::string& file, const rgb_value& red, const rgb_value& green, const rgb_value& blue, int x, int y);
    void fill(int x, int y, int width, int height, const rgb_value& redfill, const rgb_value& greenfill, const rgb_value& bluefill);
    void crop(int x, int y, int width, int height);
    void rotate_left();
    void rotate_right();
    void median_filter(const int window_size);
    void xpm2_open(const std::string& file);
  };
}
#endif
