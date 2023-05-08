#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        vector<string> commands;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            /*if (command == "open") {
             open();
             continue;
            }*/
            if (command == "blank") {
             blank();
             continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
             save();
             continue;
            } 
            if (command == "invert") {
             invert();
             continue;
            }
            if (command == "to_gray_scale"){
             to_gray_scale();
             continue;
            }
            if (command == "replace"){
             commands.push_back("replace");
             continue;
            }
            if(commands.size() > 0){
             // checking if the first command in the command sequence is replace
             if(commands[0] == "replace"){
              // storing replace arguments in a string vector
              commands.push_back(command);
              // checking if all replace arguments have appended to the vector
              if(commands.size() == 7){
               vector<int> values;
               for(long unsigned int i = 1; i < commands.size(); i++){
                // converting arguments in string form to int using stringstream and appending them to an int vector
                stringstream ss(commands[i]);
                int value;
                while(ss >> value){
                 values.push_back(value);
                }
               }
               // assigning values of the vector elements to function arguments
               rgb_value red = values[0];
               rgb_value green = values[1];
               rgb_value blue = values[2];
               rgb_value red_replace = values[3];
               rgb_value green_replace = values[4];
               rgb_value blue_replace = values[5];
               // calling replace
               replace(red,green,blue,red_replace,green_replace,blue_replace);
               // emptying the commands vector
               commands.clear();
              }
              continue;
             }
            }
            if (command == "v_mirror"){
             v_mirror();
             continue;
            }
            if (command == "h_mirror"){
             h_mirror();
             continue;
            }

             if (command == "add"){
             commands.push_back("add");
             continue;
            }
            if(commands.size() > 0){
             // checking if the first command in the command sequence is add
             if(commands[0] == "add"){
              // storing add arguments in a string vector
              commands.push_back(command);
              // checking if all add arguments have appended to the vector
              if(commands.size() == 7){
               // assigning values to function arguments, using stoi to convert the values to int as necessary
               std::string file = commands[1];
               rgb_value red = stoi(commands[2]);
               rgb_value green = stoi(commands[3]);
               rgb_value blue = stoi(commands[4]);
               int x = stoi(commands[5]);
               int y = stoi(commands[6]);
               // calling add
               add(file,red,green,blue,x, y);
               // emptying the commands vector
               commands.clear();
              }
              continue;
             }
            }
            if (command == "fill"){
             //appending "fill" in the command sequence
             commands.push_back("fill");
             continue;
            }
            if(commands.size() > 0){
             // checking if the first command in the command sequence is fill
             if(commands[0] == "fill"){
              // storing fill arguments in a string vector
              commands.push_back(command);
              // checking if all fill arguments have appended to the vector
              if(commands.size() == 8){  
               //assigning the values to the arguments using stoi to convert the values to int
               int x = stoi(commands[1]);
               int y = stoi(commands[2]);
               int width = stoi(commands[3]);
               int height = stoi(commands[4]);
               rgb_value redfill = stoi(commands[5]);
               rgb_value greenfill = stoi(commands[6]);
               rgb_value bluefill = stoi(commands[7]);
               // calling fill
               fill(x,y,width,height,redfill,greenfill,bluefill);
               // emptying the commands vector
               commands.clear();
              }
              continue;
             }
            }
            if(command == "crop"){
             commands.push_back("crop");
             continue;
            }
            if(commands.size() > 0){
             // checking if the first command in the command sequence is crop
             if(commands[0] == "crop"){
              // storing fill arguments in a string vector
              commands.push_back(command);
              // checking if all fill arguments have appended to the vector
              if(commands.size() == 5){  
               //assigning the values to the arguments using stoi to convert the values to int
               int x = stoi(commands[1]);
               int y = stoi(commands[2]);
               int width = stoi(commands[3]);
               int height = stoi(commands[4]);
               // calling crop
               crop(x,y,width,height);
               // emptying the commands vector
               commands.clear();
              }
              continue;
             }
            }
            if(command == "rotate_left"){
             rotate_left();
             continue;
            }
            if(command == "rotate_right"){
             rotate_right();
             continue;
            }
            if(command == "median_filter"){
             commands.push_back("median_filter");
             continue;
            }
            if(commands.size() > 0){
             // checking if the first command in the command sequence is median_filter
             if(commands[0] == "median_filter"){
              // storing median filter arguments in a string vector
              commands.push_back(command);
              // checking if all median filter arguments have appended to the vector
              if(commands.size() == 2){  
               //assigning the values to the arguments using stoi to convert the values to int
               int window_size = stoi(commands[1]);
               // calling median filter
               median_filter(window_size);
               // emptying the commands vector
               commands.clear();
              }
             }
             continue;
            }
            if(command == "xpm2_open"){
             commands.push_back("xpm2_open");
             continue;
            }
            if(commands.size() > 0){
             // checking if the first command in the command sequence is xpm2_open
             if(commands[0] == "xpm2_open"){
              // storing xpm2_open arguments in a string vector
              commands.push_back(command);
              // checking if all xpm2_open arguments have appended to the vector
              if(commands.size() == 2){  
               //assigning the values to the arguments
               std::string filename = commands[1];
               // calling xpm2_open
               xpm2_open(filename);
               // emptying the commands vector
               commands.clear();
              }
             }
             continue;
            }

        }

            // TODO ...     
        }

    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }

    void Script::invert() {
     // creating reference to content of pointer to image
     Image& image1 = *image;
     // applying invert function to reference
     image1.invert();
    }

    void Script::to_gray_scale(){
     // creating reference to content of pointer to image
     Image& image1 = *image;
     // applying to_gray_scale function to reference
     image1.to_gray_scale();
    }

    void Script::replace(const rgb_value& red, const rgb_value& green, const rgb_value& blue, const rgb_value& red_replace, const rgb_value& green_replace, const rgb_value& blue_replace){
      // creating reference to content of pointer to image
     Image& image1 = *image;
     // applying replace function to reference
     image1.replace(red,green,blue,red_replace,green_replace,blue_replace);
    }

    void Script::v_mirror(){
     // creating reference to content of pointer to image
     Image& image1 = *image;
     image1.v_mirror();
    }

    void Script::h_mirror(){
     // creating reference to content of pointer to image
     Image& image1 = *image;
     // applying h_mirror funct->image_[i][j].red();->image_[i][j].red();ion to reference
     image1.h_mirror();
    }

    void Script::add(const std::string& file, const rgb_value& red, const rgb_value& green, const rgb_value& blue, int x, int y){
      // creating reference to content of pointer to image
     Image& image1 = *image;
     // applying add function to reference
     image1.add(file,red,green,blue,x,y);
    }
    
    void Script::fill(int x, int y, int width, int height, const rgb_value& redfill, const rgb_value& greenfill, const rgb_value& bluefill){
     Image& image1 = *image;
     // applying fill function to reference
     image1.fill(x,y,width,height,redfill,greenfill,bluefill);
    }

    void Script::crop(int x, int y, int width, int height){
     Image& image1 = *image;
     // applying crop function to reference
     image1.crop(x,y,width,height);
    }

    void Script::rotate_left(){
     Image& image1 = *image;
     // applying rotate_left function to reference
     image1.rotate_left();
    }

    void Script::rotate_right(){
     Image& image1 = *image;
     // applying rotate_left function to reference
     image1.rotate_right();
    }

    void Script::median_filter(const int window_size){
     Image& image1 = *image;
     // applying median_filter function to reference
     image1.median_filter(window_size);
    }

    void Script::xpm2_open(const std::string& file) {
        this->image = new Image(20, 15, {255, 255, 255});
    }
}
