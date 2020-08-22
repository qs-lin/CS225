#include <iostream>
#include "cube.h" 



int main(){

  std::cout << "1st cube" << std::endl;
  cube c(10);
  c.getLength(); 

  std::cout << std::endl;
  std::cout << std::endl;
 
  std::cout << "2nd cube" << std::endl;
  cube c2(c);
  c2.getLength();

  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "3rd cube" << std::endl;
  cube c3(30);

  const cube& c4 = (c3=c2);
  //cube& c5 = (c3=c2);
  c3.getLength();
  //for c4, since c4 is a const, that means this for c4 is const. so we have to then define 
  //a getLength() const
  c4.getLength();
  //c5.getLength();

  std::cout << std::endl;
  std::cout << std::endl;


  return 0;
}
