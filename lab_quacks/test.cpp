#include <iostream>

bool test(){

  int i=0;
  while(i<10){
    std::cout << i << std::endl;
    //if(i==5)  return false;


    i++;
  }
  return i;
}


int main(){

  if(test()) std::cout << "this is test" << std::endl;
  



}
