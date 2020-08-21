#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
/*
DFS::DFS(const PNG & png, const Point & start, double tolerance) : png_(&png), 
  start_(start),
  tolerance_(tolerance)
*/
DFS::DFS(const PNG & png, const Point & start, double tolerance): ImageTraversal(png,start,tolerance) 
 {  
  /** @todo [Part 1] */
  stack.push(start_);
}


void DFS::clear(){


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

  //std::cout << "DFS clear finish" << std::endl;
}

DFS::~DFS(){
  //std::cout << "DFS dtor called" << std::endl;
  clear();
}

void DFS::test() {
/*
  std::cout << png_ -> width() << std::endl;
  std::cout << png_ -> height() << std::endl;
  std::cout << "boundary" << std::endl;
  std::cout << boundary_x << std::endl;
  std::cout << boundary_y << std::endl;
*/

  std::cout << "tol: " << tolerance_ << std::endl;
  std::cout << "pixels under tolerance_ is : " << count_pixels() << std::endl;
  //std::cout << count_pixels() << std::endl;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  //return ImageTraversal::Iterator();
  return ImageTraversal::Iterator(this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  unsigned x = point.x;
  unsigned y = point.y;

  Point p1(x+1,y);
  Point p2(x,y+1);
  Point p3(x-1,y);
  Point p4(x,y-1);
 
  //if(is_valid(p1) && !search(p1)) { std::cout << "find p1" << std::endl; stack.push(p1) ;};
  if(is_valid(p1) && !search(p1)) stack.push(p1); 
  if(is_valid(p2) && !search(p2)) stack.push(p2);
  if(is_valid(p3) && !search(p3)) stack.push(p3);
  if(is_valid(p4) && !search(p4)) stack.push(p4);

}


/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */

/*
  if(!stack.empty()){
    Point top = stack.top();
    stack.pop();
    return top;
  }
  return Point(0, 0);
*/

// this logic is buggy
// lets say in the last few iterations, the stack is like
// { a, b, c } where top is at tail c. Also if we assume a is already viewed while b and c are not
// If currently itertor itr is at c. after itr++,
// it will go to b, which is good. And after one more iter++,
// it will point to a. We know that at this point, we've viewed everything, so itr should be at end()
// even though next time when we itr++, curret logic will exclude a correctly, but remember that function body (*itr for example)
// is executed before ++itr in the for loop bracket... 
/*
  while(!stack.empty()){
    if(search(stack.top())){ 
      stack.pop();
      continue;
    }
    Point p = stack.top();
    stack.pop();
    //add this to map
    //map[p] = 1;
    vec.push_back(p);
    return  p;
  }
*/


  
  Point p(0,0);
  if(!stack.empty()){
    p = stack.top();
    stack.pop();
    //vec.push_back(p);
    arr[p.y][p.x] = 1;

  }
  while(!stack.empty()){
    if(search(stack.top()))
      stack.pop();
    else
      break; 
    }


  //return Point(0,0);
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
    
  if(!stack.empty()){
    Point top = stack.top();
    return top;
  }

  return Point(0, 0);
}



/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return stack.empty();
}

/*
void DFS::clear(){


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
*/
