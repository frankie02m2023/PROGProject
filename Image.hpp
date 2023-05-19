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
      // implementing member functions and constructors
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
      void crop(int x, int y, int width, int height);
      void rotate_left();
      void rotate_right();
      void median_filter(int window_size);
      void neighbourhood_vector(const std::vector<std::vector<Color>>& image,const int window_size, int row_index, int col_index, std::vector<rgb_value>& neighbourhood_vector_red, std::vector<rgb_value>& neighbourhood_vector_green, std::vector<rgb_value>& neighbourhood_vector_blue);
  };
}
#endif
