#include "cube.h"

cube::cube() : length_(0), test_(NULL) {
  std::cout << "default ctor invoked" << std::endl;
}

cube::cube(int length) : length_(length){
  test_ = new int(length);
  std::cout << "parameter ctor invoked" << std::endl;
}

cube::cube(const cube& other){
  copy_(other);
}



//not that we modify the lhs through clear() and copy(). 
//the return type has nothing to do with lhs
//return ref is because we don't have to make a copy at "return *this" so it's more efficient
//eg, when we call c2 = c1, we change the lhs (c2) and return a const ref to c2. If you have to 
//assign this returned value to some cube else, then use c3 = (c2 = c1). So *this is returned to c3
//
//so whether we return a ref or const ref will only affect c3, not c1 or c2.
const cube& cube::operator = (const cube& rhs){

  std::cout << "assignment oprator invoked" << std::endl;
  clear_();
  copy_(rhs);
  return *this;

}



cube::~cube(){
  clear_();
}

void cube::getLength(){

  std::cout << "length_: " << length_ << std::endl;
  std::cout << "*test_: " << *test_ << std::endl;

}

void cube::getLength() const{

  std::cout << "length_: " << length_ << std::endl;
  std::cout << "*test_: " << *test_ << std::endl;

}

void cube::copy_( const cube& other) { 
  std::cout << "copy ctor invoked" << std::endl;
  length_ = other.length_;
  if(other.test_ == NULL)
    test_ = NULL;
  else  //deep copy
    test_ = new int(*other.test_);    
 
}

void cube::clear_(){

  if(test_ != NULL){
    delete test_;
    test_ = NULL;
  }
  std::cout << "default dtor invoked" << std::endl;  

}

void cube::changeLength( int newLength){

  length_ = newLength;
  int* tmp = test_;
  test_ = new int(newLength);
  delete tmp;
}




