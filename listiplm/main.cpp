#include <iostream>
#include "List.h"

int main(){

  List<int> list;
  std::cout << "Inserting element 3 at front:" << std::endl; 
  list.insertAtFront(3);
  list.insertAtFront(30);
  list.insertAtFront(300);
  std::cout << list[0] << std::endl;
  std::cout << list[1] << std::endl;
  std::cout << list[2] << std::endl;
  //list.printReverse();
  //std::cout << list.getCount() << std::endl;
  list.myPrint();

  std::cout << "Inserting 42 at [0], 43 at [1], 44 at [3]:" << std::endl; 
  list.insert(42, 0);
  list.insert(43, 1);
  list.insert(44, 3);

  std::cout << "list[0]: " << list[0] << std::endl;
  std::cout << "list[1]: " << list[1] << std::endl;
  std::cout << "list[2]: " << list[2] << std::endl;
  std::cout << "list[3]: " << list[3] << std::endl;
  std::cout << "list[4]: " << list[4] << std::endl;

  std::cout << "Removing [0](data=42) then [2](data=44):" << std::endl; 
  list.remove(0);
  list.remove(2);
  std::cout << "list[0]: " << list[0] << std::endl;
  std::cout << "list[1]: " << list[1] << std::endl;
  std::cout << "list[2]: " << list[2] << std::endl;

  return 0;

}
