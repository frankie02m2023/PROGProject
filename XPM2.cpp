#include "XPM2.hpp"
#include <sstream>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <fstream>

namespace prog {
    Image* loadFromXPM2(const std::string& file){
        //create variables to save the information needed to create the image
        int width, height, numberOfColors, charactersPerPixel, hexValue, trash;
        char colorReplacement, type;
        std::string row;
        rgb_value red;
        rgb_value green;
        rgb_value blue;
        std::map<char, Color> colorKey;
        std::ifstream myfile;
        myfile.open(file);

        //discard "! XPM2"
        
        myfile >> trash;
        myfile >> trash;

        //save information in variables
        myfile >> width;
        myfile >> height;
        myfile >> numberOfColors;
        myfile >> charactersPerPixel;

        std::cout << "hello!";


        //create a new image with the width and height required
        Image *convertedImage =  new Image(width, height, {255, 255, 255});

        //create a for loop that will save in a map where the keys will be the characters that will be replaced and the values will be their respective colors in RGB values
        for (int i = 0; i <= numberOfColors; i++) {
            myfile >> colorReplacement;
            myfile >> type;
            myfile >> hexValue;
            //converts the hexadecimal values into RGB values
            red = ((hexValue >> 16) & 0xFF) / 255.0;
            green = ((hexValue >> 8) & 0xFF) / 255.0;
            blue = ((hexValue) & 0xFF) / 255.0; 
            colorKey[colorReplacement] = Color(red,green,blue);
        }

        std::cout << "hello";
        
        //create variable that will allow the for loop to acces the different lines
        int rowNumber = 0;
        //create while loop that will run through all the lines of the reamining text in the XPM2 file and changes the Image created above accordingly
        while(std::getline(myfile, row)) {
            
            for(int i = 0; i < int(row.size()); i++) {
                Color color = colorKey[row[i]];
                convertedImage->fill(rowNumber,i,1,1,color.red(),color.green(),color.blue());
            }
            rowNumber++;

        }

        myfile.close();
        //returns the image
        return convertedImage;
    }

    void saveToXPM2(const std::string& file, const Image* image) {

    }
}
