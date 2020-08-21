#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */

ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance) : png_(&png),
start_(start),
//arr( new int*[png.height()]),
tolerance_(tolerance){

  boundary_x = png.width();
  boundary_y = png.height();


  arr = new int*[boundary_y];
  for(unsigned row = 0; row < boundary_y; ++row)
    arr[row] = new int[boundary_x]; 


  for(unsigned x=0; x<boundary_x; x++){
    for(unsigned y=0; y<boundary_y; y++){
      arr[y][x] = 0;
    }
  }

}

void ImageTraversal::clear(){

  for(unsigned i=0; i<boundary_y; i++){
    if(arr[i]!=nullptr){
      delete[] arr[i];
      arr[i] = nullptr;
    }
  }
  if(arr!=nullptr){
    delete[] arr;
    arr = nullptr;
  }
}


ImageTraversal::~ImageTraversal(){

  //clear();    
  //std::cout << "Image class dtor called" << std::endl;
}

double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() : traversal(nullptr) {
  /** @todo [Part 1] */
  curr = Point(0,0); 

}

ImageTraversal::Iterator::Iterator(ImageTraversal* the_traversal) : traversal(the_traversal){

  curr = traversal->peek();
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //std::cout << "line: " << __LINE__ << std::endl;
  Point current = traversal->pop();
  //only care about the key
  //map[current] = 1;
  //std::cout << "line: " << __LINE__ << std::endl;
  traversal->add(current);
  //std::cout << "line: " << __LINE__ << std::endl;
  current = traversal->peek();

  curr = current;
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */

  return curr;

  //return Point(0, 0);
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */

  bool this_empty = false;
  bool that_empty = false;

  if(traversal==nullptr) this_empty = true;
  if(other.traversal==nullptr) that_empty = true;

  if(!this_empty) this_empty = traversal->empty();
  if(!that_empty) that_empty = other.traversal->empty();

  if(this_empty && that_empty) return false;  //both empty, so they are equal, so not equal function is false
  else if( (!this_empty)&&(!that_empty)) return (traversal != other.traversal);
  else return true;

}

bool ImageTraversal::is_valid(const Point& p){


  unsigned x = p.x;
  unsigned y = p.y;

  if(x<0 || x>= boundary_x) return false;
  if(y<0 || y>= boundary_y) return false;

  HSLAPixel start_pixel = png_->getPixel(start_.x, start_.y);
  HSLAPixel curr_pixel = png_->getPixel(x,y);

  //double diff = ImageTraversal::calculateDelta(start_pixel, curr_pixel);
  double diff = calculateDelta(start_pixel, curr_pixel);
  //std::cout << "debug : tol   " << tolerance_ << std::endl;
  //std::cout << "debug : diff " << diff << std::endl;
  if(diff>=tolerance_)
    return false;


  return true;
}

bool ImageTraversal::search(const Point& p){

  //auto result = map.find(p);
  //if(result!=map.end()) return true;

/*
  auto result = std::find(vec.begin(),vec.end(),p);
  if(result!=vec.end()) return true;
  else return false;
*/

  return(arr[p.y][p.x]==1);

}

unsigned ImageTraversal::count_pixels() {

  unsigned cnt = 0;
  //std::cout << start_ << std::endl;
  const HSLAPixel pix2 = png_->getPixel(start_.x,start_.y);

  for(unsigned x=0; x<png_->width(); x++){
    for(unsigned y=0; y<png_->height(); y++){

      HSLAPixel pix  = png_->getPixel(x,y);
      if( calculateDelta(pix2, pix) < tolerance_ )
        ++cnt;
 
    }
  }

  return cnt;
}
