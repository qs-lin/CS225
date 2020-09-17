#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    cout << "Add your own tests here! Modify main.cpp" << endl;



  SquareMaze maze;
  int dim = 15;
  maze.makeMaze(dim,dim);


  //maze.setWall(1,7,0,0);
  //maze.DFS(0,0);
  std::vector<int> vec = maze.solveMaze();

  //maze.debug();
  //maze.debug2();

  //std::cout << std::endl;
  //std::cout << vec.size() << std::endl;

/*
  DisjointSets f;
  f.addelements(10);
  std::cout << f.find(0) << std::endl;
  std::cout << f.find(1) << std::endl;
*/

/*
  std::vector<int> vec;
  for(size_t i=0;i<1000000; ++i)
    vec.push_back(i);

  while(vec.size()>0){
    int ith = rand()%vec.size();
    std::vector<int>::iterator it = vec.begin();
    vec.erase(it+ith);


  }
*/

  return 0;
}
