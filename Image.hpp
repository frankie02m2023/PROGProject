#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"
#include <vector>
#include <string>

namespace prog
{
  class Image
  {
  private:
    int height_;
    int width_;
    std::vector<std::vector<Color>> image_;
  public:
    Image(int w, int h, const Color &fill = {255, 255, 255});
    ~Image();
    int width() const;
    int height() const;
    Color &at(int x, int y);
    const Color &at(int x, int y) const;
    void invert();
    void to_gray_scale();
    void replace(const rgb_value& red, const rgb_value& green, const rgb_value& blue, const rgb_value& red_replace, const rgb_value& green_replace, const rgb_value& blue_replace);
    void v_mirror();
    void h_mirror();
    void add(const std::string& file, const rgb_value& red, const rgb_value& green, const rgb_value& blue, int x, int y);
    void fill(int x, int y, int width, int height, const rgb_value& redfill, const rgb_value& greenfill, const rgb_value& bluefill);
  };
}
#endif
