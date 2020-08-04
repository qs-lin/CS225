#include <iostream>

int main(){


  ////////ptr to a const var
/*
  //can change prt itself but not the object it points to
  const int m=5;
  const int* ptr = &m;   
  // *ptr = 10;  // not ok
  int n(10); ptr = &n;  //ok
  std::cout << *ptr << std::endl;

*/

 ////////const prt to a var
/*
 //can change the var it points to but not ptr itself which is a const
  int m =5;
  int n =10;
  int* const ptr = &m;
  // ptr = &n; //not ok since ptr is a const
  *ptr = 10;
  std::cout << *ptr << std::endl; //ok. since m is not a const
*/  


  ////////const ptr to a const var
/*
  //nothing can be changed
  const int m = 10;
  int n = 10;
  const int* const ptr = &m;
  // ptr = &n;  //not ok. ptr is a const
  // *ptr = 10;   //not ok. *ptr = m is also a const
*/  


  ////////const reference
/*
  int m = 10;
  int n = 5;
  const int& j = m; //it's ok even if m is not a const
                    //here j is a ref to a const, so we cannot change m via j.
  //int& const j = m; // not ok. There is no "const ref". A const ref is a ref to a const
  //note that when we alias a ref to a var, there is no de-alias. when you change the ref, you
  //are simply changing the object

  m = n;  //ok since m is not a const
  //j = n;  //not ok. we cannot change m via j
  std::cout << "m: " << m << std::endl;
  std::cout << "j: " << j << std::endl;
*/


  int m = 10;
  int n = 5;
  
  ////////////////////////////////////
  ////////// ref to a normal ptr /////////////
  ////////// this is OK //////////////
  //int* ptr  = &m; //
  //int*& ref = ptr; //
  
  ////////////////////////////////////
  ////////// ref to a ptr to const /////////////
  ////////// this is OK //////////////
  //const int* ptr  = &m; //ptr to a const 
  //const int*& ref = ptr; //ok, ref to a ptr to a const

  ////////////////////////////////////
  ////////// ref to a ptr to const /////////////
  ////////// this is Not OK //////////////
  //int* ptr = &m;
  //const int*& ref = ptr;
  //ptr and ref are pointing to the same obj. from ptr we know this object is not read-only 
  //but from ref we know it is read-only so it's contradictory  

  
/*
  ////////////////////////////////////
  //////////// const ref to a normal ptr /////////////
  //////////// this is OK //////////////
  int* ptr = &m;
  int* const &ref = ptr; //ref is an alias to a int* which is a const
  ptr = &n; //this is ok since ptr itself is not const
  //ref = &n; // this is not OK since ref is a cosnt
*/

  int* ptr = &m;
  const int* tmp = new int(*ptr);
  const int*& ref = tmp; 

  std::cout << *ptr << std::endl;
  std::cout << *ref << std::endl;

  return 0;
}

