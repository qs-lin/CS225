/* Your code here! */
#pragma once
#include <iostream>
#include <vector>


class DisjointSets{

  public:
    DisjointSets();  
    ~DisjointSets();

    void addelements(int);
    int find(int);
    void setunion(int,int);
    int size(int);
    


  private:
    std::vector<int> vec;
    void clear();
    void print();    


};
