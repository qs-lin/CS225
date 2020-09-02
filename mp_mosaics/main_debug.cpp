#include <iostream>
#include <set>
#include <vector>

#include "cs225/PNG.h"
#include "maptiles.h"
#include "mosaiccanvas.h"
#include "sourceimage.h"
#include "util/util.h"

using namespace std;
using namespace util;
using namespace cs225;

void makePhotoMosaic(const string& inFile, const string& tileDir, int numTiles,
                     int pixelsPerTile, const string& outFile);
vector<TileImage> getTiles(string tileDir);
bool hasImageExtension(const string& fileName);

int ceil(int a);


namespace opts
{
    bool help = false;
}

int main(int argc, const char** argv) {

/*
  Point<3> a(1, 2, 3);
  Point<3> b(3, 2, 1);

  std::vector<Point<3>> vec;
  vec.push_back(a);
  vec.push_back(b);

*/
/*
  cout << tree.smallerDimVal(a, b, 0) << endl;
  cout << tree.smallerDimVal(a, b, 1) << endl;
  cout << tree.smallerDimVal(a, b, 2) << endl;

  std::cout << sqrt(4+4) << std::endl;
  std::cout << tree.distance(a,b) << std::endl;

  Point<3> target        (1, 13, 57);
  Point<3> currentBest1  (10, 23, 62);
  Point<3> possibleBest1 (12, 43, 44);
  Point<3> currentBest2  (14, 13, 64);
  Point<3> possibleBest2 (25, 4, 14);
  Point<3> currentBest3  (70, 42, 24);
  Point<3> possibleBest3 (27, 45, 36);

  vec.push_back(target);
  vec.push_back(currentBest1);
  vec.push_back(currentBest2);
  vec.push_back(currentBest3);
  vec.push_back(possibleBest1);
  vec.push_back(possibleBest2);
  vec.push_back(possibleBest3);
  //std::cout << "size: " << vec.size() << std::endl;
  //std::cout << "ceil: " << ceil(10+vec.size()) << std::endl;
  
  std::vector<Point<3>> vec1;
  vec1.push_back(possibleBest3);
  vec1.push_back(possibleBest2);
 
*/
/*
  for(auto& i : vec){
    i.print();
    std::cout << std::endl;
  }
*/
/*
  KDTree<3> tree(vec);

  KDTree<3> tree3(vec1);
  //tree.printTree();

  KDTree<3> tree2(tree);
  //tree2.debug();
  tree2.printTree();
  tree.printTree();
  tree2 = tree3;
  tree2.printTree();
*/
/*

  Point<3> query(70, 42, 24);
  tree.findNearestNeighbor(currentBest1).print();
  std::cout << std::endl;
  tree.findNearestNeighbor(query).print();
  std::cout << std::endl;

*/
/*
  cout << tree.shouldReplace(target, currentBest1, possibleBest1) << endl; // should print true
  cout << tree.shouldReplace(target, currentBest2, possibleBest2) << endl; // should print false
  cout << tree.shouldReplace(target, currentBest3, possibleBest3) << endl; // based on operator<, this should be false!!!
*/

  //Point<3> p = tree.findMedian(vec,0,vec.size()-1,ceil(vec.size()),0);
  //Point<3> p = tree.findMedian(vec,0,vec.size()-1,5,0);
  //Point<3> p = tree.findMedian(vec,0,vec.size()-1,0);
  //size_t median = tree.findMedian(vec,0,vec.size()-1,(vec.size()-1)/2,0);

/*
  std::cout << "LINE: " << __LINE__ << std::endl;
  size_t median = tree.findMedian(vec1,0,vec1.size()-1,(vec1.size()-1)/2,0);
  vec1[median].print();
  //p.print();
  std::cout << std::endl;
  std::cout << "------" << std::endl;
  for(auto& i : vec1){
    i.print();
    std::cout << std::endl;
  }
*/

  //vector<Point<3>> pts;
  //KDTree<3> tree(pts);
  //Point<3> a(1, 2, 3);
  //Point<3> b(3, 2, 1);

/*
    double coords[10][2] = {
      {-8, 7}, {-6, 4}, {-5, 6}, {-3, 5}, {0, 7},
      //                ^NN
      {2, -7}, {3, 0},  {5, -4}, {6, -3}, {7, -6}
      //^M     ^M       ^M       ^M       ^M
    };
    double targetCoords[2] = {-7, 5};
    double expectedCoords[2] = {-6, 4};

    // Using MinePoint to FAIL for bad paths
    vector<Point<2>> points;

    Point<2> target(targetCoords);
    Point<2> expected(expectedCoords);

    for (int i = 0; i < 10; ++i)
        points.push_back(coords[i]);
    KDTree<2> tree(points);
    tree.printTree();

    std::cout << std::endl;
    tree.findNearestNeighbor(target).print();
*/

  double coords[14][3] = {{0, 0, 100},   // mine
                          {0, 100, 100}, // mine
                          {0, 50, 50},   // mine
                          {0, 0, 50},    // mine
                          {100, 0, 100}, // mine
                          {100, 100, 0},
                          {0, 0, 0},
                          {0, 50, 0},    // mine
                          {50, 0, 0},    // mine
                          {50, 0, 50},   // mine
                          {100, 0, 0},   // mine
                          {50, 50, 0},
                          {0, 100, 0},   // mine
                          {50, 50, 50}};
  bool isMine[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  double targetCoords[3] = {50, 100, 0};
  double expectedCoords[3] = {0, 100, 0};
  double targetCoords2[3] = {14, 17, 20};
  double expectedCoords2[3] = {0, 0, 0};

  vector<Point<3>> points;
  for (int i = 0; i < 14; ++i)
      //points.push_back(Point<3>(coords[i], isMine[i], &action));
      points.push_back(coords[i]);
  Point<3> target(targetCoords);
  Point<3> expected(expectedCoords);
  Point<3> target2(targetCoords2);
  Point<3> expected2(expectedCoords2);

  KDTree<3> tree(points);

  tree.findNearestNeighbor(target).print();
  std::cout << std::endl;

return 0;
}

int ceil( int a ){
 
  
  std::cout << " a: " << a << std::endl;
  if(a%2==0){
    std::cout << "even" << std::endl;
    std::cout << "half: " << a/2 << std::endl;
    return a/2;
  }
  else{
    std::cout << "odd" << std::endl;
    std::cout << "half: " << (a+1)/2 << std::endl;
    return (a+1)/2;
  }
}
