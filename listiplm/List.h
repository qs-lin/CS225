#pragma once
#include <iostream>

template <typename T>
class List{

  public:
    List():head_(nullptr){}
    ~List();
    void insertAtFront(const T&);
    T& operator[] (unsigned index); 
    void printReverse() const;
    //void myPrint();
    void myPrint() const;
    unsigned getCount();
    unsigned getCount() const;

    void insert(const T& Data, unsigned index); 
    T remove(unsigned index);
    


  private:
    class ListNode{
      public:  
        T Data;  
        ListNode* next_;
        ListNode(const T& data): Data(data),next_(nullptr) {}
    };

    ListNode* head_;
    void halt_(ListNode*);

    ListNode*& get_index_iter(unsigned index);
    ListNode* const & get_index_iter(unsigned index) const;

    ListNode*& get_index_recur(unsigned index);
    ListNode*& _index(unsigned index, ListNode*& node);
    void _printReverse(ListNode* node) const;
    unsigned _getCount(ListNode* node);

};


#include "List.hpp"
