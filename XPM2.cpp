#include "XPM2.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;


namespace prog {
 // function that converts 8 bit hexadecimal values into rgb_values
 rgb_value hexadecimal_to_int(string hexadecimal){
  rgb_value value;
  map<char,rgb_value> matches = {{'0',0},{'1',1},{'2',2},{'3',3},{'4',4},{'5',5},{'6',6},{'7',7},{'8',8},{'9',9},{'a',10},{'b',11},{'c',12},{'d',13},{'e',14},{'f',15}};
  hexadecimal[0] = tolower(hexadecimal[0]);
  hexadecimal[1] = tolower(hexadecimal[1]);
  rgb_value value1 = matches[hexadecimal[0]];
  rgb_value value2 = matches[hexadecimal[1]];
  value = value1*16 + value2;
  return value;
}
string rgb2hex(rgb_value red, rgb_value green, rgb_value blue){
 stringstream ss; 
 stringstream sred;
 stringstream sgreen;
 stringstream sblue;
 sred << hex << int(red);
 sgreen << hex << int(green);
 sblue << hex << int(blue);
 string hexred = sred.str();
 string hexgreen = sgreen.str();
 string hexblue = sblue.str();

 //making sure it has 2 digits each by adding a 0 if it only has one digit
 if (hexred.size() == 1){
  hexred = "0" + hexred;
 }
 if (hexgreen.size() == 1){
  hexgreen = "0" + hexgreen;
 } 
 if (hexblue.size() == 1){
  hexblue = "0" + hexblue;
 } 
 ss  << hexred << hexgreen << hexblue;
 return ss.str();
}

Image* loadFromXPM2(const std::string& file) {
 Color initial_color;
 ifstream in(file);
 int counter = 0;
 // red,blue and green are strings of length two that contain hexadecimal representations of rgb_values from 0 to 255
 string line,opening_line,red,blue,green;
 vector<string> lines;
 int width,height,num_of_colors,char_per_color;
 map<char,Color> colors;
 // using ifstream object to skip the first line of the file(that contains two strings separted by a space)
 in >> opening_line;
 in >> opening_line;
 // using ifstream object to save the width,height,number of colors and number of characters present in the second line of the file per color in int variables
 in >> width;
 in >> height;
 in >> num_of_colors;
 in >> char_per_color;
 // creating an image object using dynamic memory allocation and creating a pointer to such image
 Image* ptr_image = new Image(width,height,initial_color);
 // creating a reference to the content of the pointer to the new image object
 Image& image = *ptr_image;
 // saving the lines of the file that map the characters to the color they represent in a vector of strings
 while(getline(in,line) && counter < num_of_colors + 1){
  lines.push_back(line);
  counter++;
 }
 // creating a map object to match the characters that appear in the file to the color they represent
 for(long unsigned int i = 1; i < lines.size(); i++){
  // assigning symbol to the first character in each line
  char symbol = lines[i][0];
  // using red,green and blue strings to turn the hexadecimal code for the color into three different rgb_values that compose a given color
  red.push_back(lines[i][5]);
  red.push_back(lines[i][6]);
  rgb_value red_value = hexadecimal_to_int(red);
  green.push_back(lines[i][7]);
  green.push_back(lines[i][8]);
  rgb_value green_value = hexadecimal_to_int(green);
  blue.push_back(lines[i][9]);
  blue.push_back(lines[i][10]);
  rgb_value blue_value = hexadecimal_to_int(blue);
  Color color(red_value,green_value,blue_value);
  // mapping the symbol in each line to their repective color
  colors.insert({symbol,color});
  // clearing red,green and blue strings so they can be used in the next line
  red.clear();
  green.clear();
  blue.clear();
 }
 // assigning 0 to counter to more easily use it to check if we have arrived at a relevant line of the file 
 counter = 0;
 // int variable that is used to loop through the lines of the file that can be used to represent the newly created image
 int index = 0;
 // creating new ifstream object to loop through all the lines of the file
 ifstream in1(file);
 // looping through all the lines of the file
 while(getline(in1,line)){
  // checking if the line we are in already represents a line of pixels in a png image by checking if we have already looped through the lines that map colours to symbols 
  if(counter > num_of_colors + 1){
   // looping through the rows of each line of the file and assigning the pixel in the corresponding position in the png position to the color value of their respective symbol in the xpm2 file
   for(int i = 0; i < width; i++){
     image.at(i,index) = colors[line[i]];
   }
   // incrementing the line counter
   index++;
  }
  // incrementing counter used to check if we have arrived at a relevant line of the file
  counter++;
 }
 // returning the pointer to the image created using dynamic memory allocation
 in.close();
 return ptr_image;
}

void saveToXPM2(const string& file, Image* image) {
 int h = image->height();
 int w = image->width();
 //storing the colors
 vector<Color> colors;
 bool isIn = false; 
 //getting the numbers of colors
 for (int i = 0; i < h; i++){
  for (int j = 0; j < w; j++){
   isIn = false;
   Color c = image -> at(j, i);
   for (Color vect : colors){
    if ((vect.red() == c.red()) & (vect.blue() == c.blue()) & (vect.green() == c.green())){
     isIn = true;
    }
   }
   if (isIn == false){
    colors.push_back(c);
   }
  }
 }   
 int charnum = 34; //variable to assign each color an ascii character ofset by 34 (")
 //writing to the filename
 ofstream myfile;
 myfile.open(file.c_str());
 myfile << "! XPM2" << "\n";
 myfile << w << " " << h << " " << colors.size() << " 1" << "\n";
 //assigning each color a character
 for (Color vect : colors){
  myfile << char(charnum) << " " << "c #" << (rgb2hex(vect.red(),vect.green(),vect.blue())) << "\n";
  charnum += 1;
 }
 charnum = 34; //resetting the variable so it corresponds to the first color

 //going over each pixel on the image
 for (int i = 0; i < h; i++){
  for (int j = 0; j < w; j++){
   Color c = image -> at(j, i);
   //getting the position of the color in the vector colors so it can write the corresponding character
   for (long unsigned int pos = 0; pos < colors.size(); pos++){
    if ((colors[pos].red() == c.red()) & (colors[pos].blue() == c.blue()) & (colors[pos].green() == c.green())){
     myfile << char(charnum + pos);
    }
   }
  }
  myfile << "\n";
 }
 //closing the file
 myfile.close();
 }
}
