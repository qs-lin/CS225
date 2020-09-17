/* Your code here! */
#include "dsets.h"

DisjointSets::DisjointSets(){
}

DisjointSets::~DisjointSets(){
  clear();
}

void DisjointSets::addelements(int num){
  for(int i=0;i<num;++i)
    vec.push_back(-1);
}

int DisjointSets::find(int num){

  if(vec[num]<0)
    return num;
  else{
    int root = find(vec[num]);
    //path compression. makes it effectively O(1) (iterative logn)
    vec[num] = root;
    return root;
  }

}

void DisjointSets::setunion(int a,int b){

  bool debug = false;
  
  int root1 = find(a);
  int root2 = find(b);
  int newSize = vec[root1] + vec[root2]; 
  if(vec[root1]<vec[root2]){
    vec[root2] = root1;
    vec[root1] = newSize;
  }else{
    vec[root1] = root2;
    vec[root2] = newSize;
  }

}

int DisjointSets::size(int elem){

  int root = find(elem);
  return -vec[root];

}

void DisjointSets::clear(){
  vec.clear();
}

void DisjointSets::print(){
  for(const int& a : vec)
    std::cout << a << " " ;
 
  std::cout << std::endl;
}
