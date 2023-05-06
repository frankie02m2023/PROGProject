#include "XPM2.hpp"
#include <sstream>
#include <vector>
#include <map>
#include <iostream>

namespace prog {
    Image* loadFromXPM2(const std::string& file){
        int width, height, numberOfColors, charactersPerPixel, hexValue;
        char colorReplacement, type;
        rgb_value red;
        rgb_value green;
        rgb_value blue;
        std::map<char, Color> colorKey;
        std::stringstream ss(file);

        ss.ignore(256, '/n');

        ss >> width;
        ss >> height;
        ss >> numberOfColors;
        ss >> charactersPerPixel;

        std::vector<std::vector<Color>> convertedImage(width,std::vector<Color>(height));

        for (int i = 0; i <= numberOfColors; i++) {
            ss >> colorReplacement;
            ss >> type;
            ss >> hexValue;
            red = ((hexValue >> 16) & 0xFF) / 255.0;
            green = ((hexValue >> 8) & 0xFF) / 255.0;
            blue = ((hexValue) & 0xFF) / 255.0; 
            colorKey[colorReplacement] = Color(red,green,blue);
        }

        std::string row;
        while (ss >> row){
            std::cout << row;
        }
        

    }

    void saveToXPM2(const std::string& file, const Image* image) {

    }
}
