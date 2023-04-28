#include "Image.hpp"

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
        // Creating reference to the color of the pixel in the image and then changing the value of that reference
        image_[i][j].red() = 255 - image_[i][j].red();
        image_[i][j].green() = 255 - image_[i][j].green();
        image_[i][j].blue() = 255 - image_[i][j].blue();
      }
    }
  }
}
