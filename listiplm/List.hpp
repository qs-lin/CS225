#include "List.h"

template <typename T>
List<T>::~List(){

  halt_(head_);

}

template <typename T>
void List<T>::halt_(ListNode* node){

  if(node!=nullptr){
    halt_(node->next_);
    delete node;
    }
}


template <typename T>
void List<T>::insertAtFront(const T& data){

  ListNode* newNode =  new ListNode(data);
  newNode->next_ = head_;
  head_ = newNode;

}

template <typename T>
typename List<T>::ListNode*& List<T>::get_index_iter(unsigned index){

  ListNode* node = head_;  
  if(index==0)
    return head_;        

  for(unsigned i=0; i<index-1; i++){ 
    node = node->next_;
  }

  return node->next_;
}

template <typename T>
typename List<T>::ListNode* const & List<T>::get_index_iter(unsigned index) const{

  ListNode* node = head_;
  if(index==0)
    return head_;

  for(unsigned i=0; i<index-1; i++){
    node = node->next_;
  }

  return node->next_;

}

template <typename T>
void List<T>::myPrint() const{

  unsigned size = getCount();

  ListNode* const  node = get_index_iter(2);
  for(unsigned index=size-1;index>=0;index--){
    ListNode* const  node = get_index_iter(index);
    std::cout << node->Data << std::endl;
    if(index==0) break;
  }
}

template <typename T>
T& List<T>::operator[] (unsigned index){

  //ListNode*& node = get_index_iter(index);
  ListNode*& node = get_index_recur(index);
  return node->Data;

}

template <typename T>
typename List<T>::ListNode*& List<T>::get_index_recur(unsigned index){

  return _index(index,head_);

}

template <typename T>
typename List<T>::ListNode*& List<T>::_index(unsigned index, ListNode*& node){

  if(index==0) return node;
  else 
    return _index(index-1,node->next_); 

}

template <typename T>
void List<T>::printReverse() const{

  _printReverse(head_);

}

template <typename T>
void List<T>::_printReverse(ListNode* node) const{

  if(node!=nullptr){  
    _printReverse(node->next_);
    std::cout << node->Data << std::endl;
  }  
}

/*
void List<T>::myPrint(){

  unsigned size = getCount();
  for(unsigned i=(size-1);i>=0;i--){
    ListNode*& node = get_index_recur(i); 
    std::cout << node->Data << std::endl;
    if(i==0) break;
    //for unsigned i=0; i-- is still positive
  }

}
*/


template <typename T>
unsigned List<T>::getCount(){

  std::cout << "calling getCount() " << std::endl;
  return _getCount(head_);

}


template <typename T>
unsigned List<T>::getCount() const{

  std::cout << "calling getCount() const" << std::endl;
  unsigned count = 0;
  ListNode* node = head_;
  while(node!=nullptr){
    node = node->next_;
    count++;
  }
  return count;; 

}


template <typename T>
unsigned List<T>::_getCount(ListNode* node){

  unsigned count = 0;

  while(node!=nullptr){  
    node = node->next_;
    count++;
  }
  
  return count;
}

template <typename T>
void List<T>::insert( const T& data, unsigned index ){

  ListNode* node  = new ListNode(data);
  ListNode*& curr = get_index_recur(index);
  node->next_ = curr;
  curr = node;

}


template <typename T>
T List<T>::remove(unsigned index){

  ListNode*& curr = get_index_recur(index);
  ListNode* tmp = curr;
  curr = curr->next_;
  T Data = tmp->Data;
  delete tmp;
  return Data; 
  
}

