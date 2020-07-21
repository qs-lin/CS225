/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {

  class HSLAPixel{

    public:
      HSLAPixel();
      HSLAPixel(double hue, double satuaration, double luminance);
      HSLAPixel(double hue, double satuaration, double luminance, double alpha);

      double h;
      double s;
      double l;
      double a;

  };

}
