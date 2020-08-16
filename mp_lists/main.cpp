#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "List.h"
#include <sstream>

int main() {
  List<int> list;
  List<int> list1;
  List<int> list2;

  //test insertatBack
  //for (unsigned i = 7; i > 0; i--) { list.insertFront(i); }

  //test insertatBack
  list1.insertBack(1);
  list1.insertBack(3);
  list1.insertBack(4);
  list1.insertBack(6);

  list2.insertBack(2);
  list2.insertBack(5);
  list2.insertBack(7);


  stringstream s;
  stringstream b;
  stringstream n;
  stringstream m;
  list1.print(s);
  list2.print(b);
  std::cout << s.str() << std::endl;
  std::cout << b.str() << std::endl;

  list1.mergeWith(list2);
  list1.print(m);
  list2.print(n);
  std::cout << m.str() << std::endl;
  std::cout << n.str() << std::endl;

  std::cout << "now print in order and reversely" << std::endl;
  list1.printReverse();
  list2.printReverse();

  std::cout << "now reverse entire list" << std::endl;
  list1.reverse();
  list1.printReverse();

  std::cout << "now reverse it back" << std::endl;
  list1.reverse();
  s.str("");
  list1.print(s);
  std::cout << s.str() << std::endl;

  std::cout << "now test reverse longer than length" << std::endl;
  list1.reverseNth(100);
  s.str("");
  list1.print(s);
  std::cout << s.str() << std::endl;


/*
  std::cout << "now test reverse 2" << std::endl;
  list1.reverse();
  list1.reverseNth(2);
  s.str("");
  list1.print(s);
  std::cout << s.str() << std::endl;
*/
  std::cout << "now test reverse 5" << std::endl;
  list1.reverse();
  list1.reverseNth(5);
  s.str("");
  list1.print(s);
  std::cout << s.str() << std::endl;

  std::cout << "now test merge with empty list" << std::endl;
  list1.mergeWith(list);
  s.str("");
  list1.print(s);
  std::cout << s.str() << std::endl;

  std::cout << "now test merge sort" << std::endl;
  list.insertBack(5);
  list.insertBack(7);
  list.sort();
  s.str("");
  list.print(s);
  std::cout << s.str() << std::endl;


  std::cout << "test iterators: -----------------" << std::endl;


  for(List<int>::ListIterator it=list.begin(); it!=list.end(); ++it){
    std::cout << *it << std::endl;
  }



  for( int  a : list)
    std::cout << a << std::endl;

  for( const int& a : list)
    std::cout << a << std::endl;

  for( auto & a : list)
    std::cout << a << std::endl;

  for( const auto & a : list)
    std::cout << a << std::endl;

  for( auto const & a : list)
    std::cout << a << std::endl;

  for( int const & a : list)
    std::cout << a << std::endl;


  //the following is not gonna work
  //because the deference of iterator will return a const T& (List-ListIterator.hpp: line58)
  //this is because of line 60 of List.h. You have to drop those two const.
  //It has nothing to do with Iterator begin() const. You can drop that const
/*
  for( int&  a : list)
    std::cout << a << std::endl;
*/




  //list.tripleRotate();

/*
  list.print(b);
  std::cout << b.str() << std::endl;
*/


/*
  for(List<int>::ListIterator it=list.begin(); it!=list.end(); ++it){
    std::cout << *it << std::endl;
  }
  
  std::cout << "reverse: " << std::endl;
  list.printReverse();
*/
  return 0;
}
