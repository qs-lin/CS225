/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {

  HSLAPixel::HSLAPixel(){
    h = 100.;
    s = 1.;
    l = 1.;
    a = 1.;
  }


  HSLAPixel::HSLAPixel(double hue, double satuaration, double luminance){
    h = hue;
    s = satuaration;
    l = luminance; 
    a = 1.;
  }

  HSLAPixel::HSLAPixel(double hue, double satuaration, double luminance, double alpha){
    h = hue;
    s = satuaration;
    l = luminance; 
    a = alpha;
  }


}
