#pragma once
#include <iostream>

class cube{

  public:
    cube();
    cube(int);
    cube(const cube&);
    ~cube();
    //cube& operator = (const cube&);

    const cube& operator = (const cube&) ;
    //cube& operator = (const cube&) ;


    void getLength();
    void getLength() const;
    int length_;
    int* test_;

    void changeLength( int );
 
  private:
    void copy_( const cube&);
    void clear_();

};
