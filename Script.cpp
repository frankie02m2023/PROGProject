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
            if (command == "open") {
             open();
             continue;
            }
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
     // applying h_mirror function to reference
     image1.h_mirror();
    }

}
