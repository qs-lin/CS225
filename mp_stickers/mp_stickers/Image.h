/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"
#include <iostream>

class Image : public cs225::PNG {

  public:
    Image();
    Image(PNG const &);
    void lighten();
    void lighten(double);
    void darken();
    void darken(double);
    void saturate();
    void saturate(double);
    void desaturate();
    void desaturate(double);
    void greyscale();
    void illinify();
    void scale(double);
    void scale(unsigned, unsigned);
    //helpfer function of scale
    void _small(double);
    void _large(double);
    void rotateColor(double);
    

    

  private:



};

