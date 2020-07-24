#include <iostream>

int main(){

/*
  int* a = new int(5);
  std::cout << *a << std::endl;
  delete a;
  delete a;
*/

  std::cout << sizeof(int) << std::endl;

  int dim = 5;
  int* a = new int[dim];
  int* b = new int[dim];
  std::cout << a << std::endl;
  std::cout << b << std::endl;

  for(int i=0;i<dim; i++){
    a[i] = i;
    b[i] = i;
  }

  for(int i=0;i<dim; i++){
    std::cout << "-----" << std::endl;
    std::cout << &a[i] << std::endl; 
    std::cout << &b[i] << std::endl; 
  }

  delete a;
  delete b;


}
