#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

// copy paste from first assignment

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  std::string dimentions = "";
  dimentions = std::to_string(width) + " " + std::to_string(height);

  std::string magic_num = "P3";
  std::string max_val = "255";

  // create and open file
  std::ofstream output(filename);
  if(!output) return false;

  output << magic_num << std::endl << dimentions << std::endl << max_val;
  output << std::endl;

  // write data from std::vector
  int size = width * height * num_channels;
  if(num_channels == 3){
    for(int it = 0; it < size; it += 3){
        output << std::to_string((int)data[it]) << " ";
        output << std::to_string((int)data[it + 1]) << " ";
        output << std::to_string((int)data[it + 2]) << " ";
        // make the print out match dim of file
        std::string delin = ((it % width) == (width - 1)) ? "\n" : "  ";
        output << delin;
    }
  } else{
    for(int it = 0; it < size; it++){
      output << std::to_string((int)data[it]) << " ";
      output << std::to_string((int)data[it]) << " ";
      output << std::to_string((int)data[it]) << " ";
      // make the print out match dim of file
      std::string delin = ((it % width) == (width - 1)) ? "\n" : " ";
      output << delin;
    }
  }

  if(!output) return false;

  return true;
  ////////////////////////////////////////////////////////////////////////////
}
