/* Your code here! */

#pragma once
#include <iostream>
#include <unordered_map>
#include <tuple>
#include <stack>
#include "dsets.h"
#include "cs225/PNG.h"

using cs225::PNG;
using cs225::HSLAPixel; 
class SquareMaze{

  public:
    SquareMaze();
    ~SquareMaze();
    void makeMaze(int,int);
    bool canTravel(int,int,int) const;
    void setWall(int,int,int,bool);
    std::vector<int> solveMaze();
    cs225::PNG* drawMaze() const;
    PNG* drawMazeWithSolution();

    void debug();
    void debug2();


  private:

    bool*** wall; 
    DisjointSets* forest;
    bool** visited;
    int** dist;
    std::pair<int,int>** pred;  //predecessor
    int _width;
    int _height;

    void clear_wall();
    void clear_forest();
    bool check_cycle();
    //bool canRemove(); //still have valid walls to be removed
    bool wallCanRemove(int,int,int); //check if a given wall can be removed 

    std::vector<int> solveMaze_(int,int); 
    void retrieve(std::vector<int>&,int,int);
    void DFS(int,int); 

    std::vector<int> soln;  //stores the maze solution
    int destination;
    //std::stack<std::pair<int,int>> stack;

    
    //std::unordered_map<int,std::tuple<int,int,int>> map; //map from removal_vec index to wall coord
    //std::vector<int> removal_vec; //pool for walls to be removed 

};
