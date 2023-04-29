#include "Image.hpp"
#include <iostream>

namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    height_ = h;
    width_ = w;
    for(int i = 0; i < w; i++){
      std::vector<Color> line;
      for(int j = 0; j < h; j++){
       line.push_back(fill);
      }
      image_.push_back(line);
    }
  }
  Image::~Image()
  {
  }
  int Image::width() const
  {
    return width_;
  }
  int Image::height() const
  {
    return height_;
  }

  Color& Image::at(int x, int y)
  {
     return image_[x][y];
  }

  const Color& Image::at(int x, int y) const
  {
     return image_[x][y];
  }

  void Image::invert(){
    for(int i = 0; i < width_; i++){
      for(int j = 0; j < height_; j++){
        image_[i][j].red() = 255 - image_[i][j].red();
        image_[i][j].green() = 255 - image_[i][j].green();
        image_[i][j].blue() = 255 - image_[i][j].blue();
      }
    }
  }

  void Image::to_gray_scale(){
    rgb_value average;
    for(int i = 0; i < width_; i++){
      for(int j = 0; j < height_; j++){
        average = (image_[i][j].red() + image_[i][j].green() + image_[i][j].blue()) / 3;
        image_[i][j].red() = average;
        image_[i][j].green() = average;
        image_[i][j].blue() = average;
      }
    }
  }

  void Image::replace(const rgb_value& red, const rgb_value& green, const rgb_value& blue, const rgb_value& red_replace, const rgb_value& green_replace, const rgb_value& blue_replace){
   for(int i = 0; i < width_; i++){
      for(int j = 0; j < height_; j++){
       if(image_[i][j].red() == red && image_[i][j].green() == green && image_[i][j].blue() == blue){
         image_[i][j].red() = red_replace;
         image_[i][j].green() = green_replace;
         image_[i][j].blue() = blue_replace;
       }
      }
    }
  }

  void Image::v_mirror(){
   Color tmp;
   for(int i = 0; i < width_; i++){
      for(int j = 0; j <= (height_ - 1) / 2; j++){
       tmp = image_[i][j];
       image_[i][j] = image_[i][height_ - 1 - j];
       image_[i][height_ - 1 - j] = tmp;
       }
      }
  }

  void Image::h_mirror(){
    Color tmp;
    for(int i = 0; i <= (width_ - 1) / 2; i++){
      for(int j = 0; j < height_; j++){
       tmp = image_[i][j];
       image_[i][j] = image_[width_ - 1 - i][j];
       image_[width_ - 1 - i][j] = tmp;
       }
      }
  }

}

