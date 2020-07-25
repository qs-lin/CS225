#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2

  cs225::PNG png;
  if(!png.readFromFile(inputFile)){
    std::cout << "file not exists" << std::endl;
    return;
  }
  int width  = png.width();
  int height = png.height();

  cs225::PNG output(width,height);

  //std::cout << width << std::endl;
  //std::cout << height << std::endl;

  for(int y=0; y<height; y++){
    for(int x=0; x<width; x++){

      cs225::HSLAPixel &my_pixel = output.getPixel(x,y);
      my_pixel = png.getPixel(width-1-x, height-1-y);

    }//end of x loop
  }//end of y loop

  output.writeToFile( outputFile);


}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  std::cout << " my art " << std::endl;
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      cs225::HSLAPixel& pixel = png.getPixel(x, y);
      if (x< 1./5. *png.width()){
        pixel.h=111.;
        pixel.s=0.373;
        pixel.l=0.1;
        pixel.a=0.15;
      } else if (x >=1./5.*png.width() && x<= 2./5. *png.width()){
        pixel.h=173.;
        pixel.s=0.73;
        pixel.l=0.738;
        pixel.a=0.8373;
      } else {
        pixel.h=213.;
        pixel.s=1.;
        pixel.l=0.172;
        pixel.a=1.;
      }
    }
  }

  return png;

  return png;
}
