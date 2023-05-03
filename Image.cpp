#include "Image.hpp"
#include "PNG.hpp"
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

  void Image::add(const std::string& file, const rgb_value& red, const rgb_value& green, const rgb_value& blue, int x, int y) {
    //Loading the PNG file and converting it into an image
    Image* loadedImage = loadFromPNG(file);
    //Loop that will run through the loadedImage
    for(int i = 0; i < loadedImage->width_; i++){
      for(int j = 0; j < loadedImage->height_; j++){
        //if the pixel has the "neutral" color, the loop will not do anything
        if (loadedImage->image_[i][j].red() == red && loadedImage->image_[i][j].green() == green && loadedImage->image_[i][j].blue() == blue) {
         continue;
        }
        //if it's any color besides the "neutral" color, it will copy that pixel to the image we are given
        else {
          image_[i + x][j + y].red() = loadedImage->image_[i][j].red();
          image_[i + x][j + y].green() = loadedImage->image_[i][j].green();
          image_[i + x][j + y].blue() = loadedImage->image_[i][j].blue();
        }
      
      }
    }
    //loadFromPNG creates new Image, needs to be deleted or else it leads to a "Memory Leak"
  delete loadedImage;
}
  void Image::fill(int x, int y, int width, int height, const rgb_value& redfill, const rgb_value& greenfill, const rgb_value& bluefill){
    //loop for every pixel in the bounds setted by width and weight
    for (int i = 0; i < width; i++){
      for (int j = 0; j < height; j++){
        //offsetting every pixel by the x and y values and turning them into the fill values
        image_[i + x][j + y].red() = redfill;
        image_[i + x][j + y].green() = greenfill;
        image_[i + x][j + y].blue() = bluefill;  
      }
    }
  }

  void Image::crop(int x, int y, int width, int height){
   // creating copy of image 
   std::vector<std::vector<Color>> image1 = image_;
   // changing image dimensions
   width_ = width;
   height_ = height;
   // looping through image with new dimensions and using copy to assign pixel values to new image starting at position(0,0)
   for(int i = 0; i < width_; i++){
    for(int j = 0; j < height_; j++){
     image_[i][j] = image1[x + i][y + j];
    }
   }
  }

  void Image::rotate_left(){
   Color tmp;
   // switching image dimensions
   int width = width_;
   int height = height_;
   width_ = height;
   height_ = width;
   // creating pixel matrix with inverted dimensions
   std::vector<std::vector<Color>> image1(width_,std::vector<Color>(height_));
   // turning image1 matrix into the transpose of image_ matrix
    for(int i = 0; i < width_; i++){
     for(int j = 0; j < height_; j++){
      image1[i][j] = image_[j][i];
     }
    }
    // using vector copy constructor to assign image1 to image_
    image_ = image1;
    // inverting the rows of the image pixel matrix to compute the counterclockwise rotation of the image
    for(int i = 0; i < width_; i++){
     for(int j = 0; j < height_ / 2; j++ ){
      tmp = image_[i][j];
      image_[i][j] = image_[i][height_ - 1 - j];
      image_[i][height_ - 1 - j] = tmp;
     }
    }
   }

   void Image::rotate_right(){
   Color tmp;
   // switching image dimensions
   int width = width_;
   int height = height_;
   width_ = height;
   height_ = width;
   // creating pixel matrix with inverted dimensions
   std::vector<std::vector<Color>> image1(width_,std::vector<Color>(height_));
   // turning image1 matrix into the transpose of the image_ matrix
    for(int i = 0; i < width_; i++){
     for(int j = 0; j < height_; j++){
      image1[i][j] = image_[j][i];
     }
    }
    // using vector copy constructor to assign image1 to image_
    image_ = image1;
    // inverting the columns of pixel matrix image_ to compute the clockwise rotation of the image
    for(int i = 0; i < width_ / 2; i++){
     for(int j = 0; j < height_; j++ ){
      tmp = image_[i][j];
      image_[i][j] = image_[width_ - 1 - i][j];
      image_[width_ - 1 - i][j] = tmp;
     }
    }
   }
  }

