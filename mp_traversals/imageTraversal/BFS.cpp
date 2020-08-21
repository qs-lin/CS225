#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
//BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
BFS::BFS(const PNG & png, const Point & start, double tolerance): ImageTraversal(png,start,tolerance){

  queue.push(start);
  /** @todo [Part 1] */
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */

  unsigned x = point.x;
  unsigned y = point.y;

  Point p1(x+1,y);
  Point p2(x,y+1);
  Point p3(x-1,y);
  Point p4(x,y-1);

  if(is_valid(p1) && !search(p1)) queue.push(p1);
  if(is_valid(p2) && !search(p2)) queue.push(p2);
  if(is_valid(p3) && !search(p3)) queue.push(p3);
  if(is_valid(p4) && !search(p4)) queue.push(p4);

}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */

  Point p(0,0);
  if(!queue.empty()){
    p = queue.front();
    queue.pop();

    arr[p.y][p.x] = 1;
  }
  while(!queue.empty()){
    if(search(queue.front()))
      queue.pop();
    else
      break;
    }


  return p; 
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */

  if(!queue.empty()){
    Point top = queue.front();
    return top;
  }

  return Point(0, 0);
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return queue.empty();
}

void BFS::clear(){


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

  //std::cout << "BFS clear finish" << std::endl;
}

BFS::~BFS(){
  //std::cout << "BFS dtor called" << std::endl;
  clear();
}
