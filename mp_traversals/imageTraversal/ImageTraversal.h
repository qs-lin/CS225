/**
 * @file ImageTraversal.h
 */
#pragma once

#include <iterator>
#include <vector>
#include <map>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

using namespace cs225;

/**
 * A base class for traversal algorithms on images.
 *
 * BFS and DFS will inherit from this class
 * 
 * Each derived class must maintain an ordering of points on an image,
 * through calls to the virtual member functions `add` and `pop`.
 * 
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */
class ImageTraversal {
public:
  /**
   * A forward iterator through an ImageTraversal.
   */
  ImageTraversal(const PNG & png, const Point & start, double tolerance);
  virtual ~ImageTraversal(); 

  class Iterator : std::iterator<std::forward_iterator_tag, Point> {

  //virtual ~ImageTraversal();
  public:
    Iterator();
    Iterator(ImageTraversal*);

    Iterator & operator++();
    Point operator*();
    bool operator!=(const Iterator &other);

    /** @todo [Part 1] */
    /** add member functions if neccesary*/

  private:
    /** @todo [Part 1] */
    /** add private members here if neccesary*/
      Point curr;

      //note that a nested class does not have direct access to its enclosing class's function
      //unless that function is static so you can call it without instantiation. so we need this
      //traversal* to the obj
      ImageTraversal* traversal;

  };

  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator begin() = 0;

  /**
   * The end of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator end() = 0;

  /**
   * Add new point to the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual void add(const Point & t) = 0;
  /**
   * Remove and return the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point pop() = 0;
  /**
   * Return but not remove the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point peek() const = 0;
  /**
   * To see if the traversal has no points left
   * Virtual function. Derived class need to implement this
   */
  virtual bool empty() const = 0;
  
  //static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);  


//accessed by derived classes
protected:

  const PNG* png_;
  Point start_;
  double tolerance_;
  unsigned boundary_x;
  unsigned boundary_y;

  //location valid; tolerance satisfied
  bool is_valid(const Point&);

  //will check if points already been traversed by looking for it in the map
  bool search(const Point&);
  //will add points already been traversed into this map
  //std::map<Point,int> map;
  std::vector<Point> vec;
  //count how many pixels under tolerance
  unsigned count_pixels() ;

  //int arr[500][500] = {{0}};
  int** arr;


private:
  static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);  
  //double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);  


  void clear();
};
