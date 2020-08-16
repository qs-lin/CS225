#include <iostream>

using std::cout;

int main(){


  int x = 10;
  int a = ++x;

  int y = 10;
  int b = y++;

  std::cout << "pre-increment" << std::endl;
  std::cout << "x: " << x << std::endl;
  std::cout << "a: " << a << std::endl;

  std::cout << "post-increment" << std::endl;
  std::cout << "y: " << y << std::endl;
  std::cout << "b: " << b << std::endl;


/*
    int x = 10, a; 
  
    a = x++; 
  
    cout << "Post Increment Operation"; 
  
    // Value of a will not change 
    cout << "\na = " << a; 
    
    // Value of x change after execution of a=x++; 
    cout << "\nx = " << x; 
    //                 
    return 0; 
*/

}
