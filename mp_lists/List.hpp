#include "List.h"
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() : head_(nullptr), tail_(nullptr), length_(0) { 
  // @TODO: graded in MP3.1
/*
    ListNode* head_ = NULL;
    ListNode* tail_ = NULL;
*/
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
//typename List<T>::ListIterator List<T>::begin() const {
typename List<T>::ListIterator List<T>::begin() {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
//typename List<T>::ListIterator List<T>::end() const {
typename List<T>::ListIterator List<T>::end() {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1

  if(length_ == 0) return;

  ListNode* curr = head_; 

  while(curr!=nullptr){
    ListNode* tmp = curr;
    curr = curr->next;
    delete tmp;
  }
  
  head_ = nullptr;
  tail_ = nullptr;
  length_ = 0;

}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;

  if(tail_==nullptr)
    tail_ = newNode;

  if (head_ != NULL) {
    head_ -> prev = newNode;
  }

  head_ = newNode;
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1

  ListNode *node = new ListNode(ndata);

  node->next = nullptr;
  node->prev = tail_;

  if(tail_ != nullptr)
    tail_->next = node;

  if(head_ == nullptr)
    head_ = node;

  tail_ = node;
  length_ ++;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
  //for (int i = 0; i < splitPoint; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */

//I will solve this iteratively, 3 elements by 3 elements
//eg, 123 456 789 I will call rotate3() 3 times
//first time: 231, 456, 789
//second time: 231, 564, 789
//third time: 231, 564, 897
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1

  unsigned rounds = length_/3;
  if(rounds<1) return;

  ListNode* node = rotate3(head_);
  for(unsigned i=1; i<rounds; i++){
    node = rotate3(node->prev->next);
  }

  //1,2,3 after rotation is 2,3,1. We need to change tail_ from 3 to 1
  if(length_%3==0)
    tail_ = tail_->next;   

/*
  ListNode* curr = head_;
  while (curr != NULL) {
    std::cout <<" " << curr->data;
    curr = curr->next;
  }
  std::cout << std::endl;
*/
}

//if we only rotate 1,2,3 to get 2,3,1
template <typename T>
//void List<T>::rotate3(ListNode*& start){
//typename List<T>::ListNode*& List<T>::rotate3(ListNode*& start){
typename List<T>::ListNode* List<T>::rotate3(ListNode*& start){

  //make a copy of 1
  ListNode* tmp = start;
  //now start from 2
  start = tmp->next;
  //set the prev of 2
  start->prev = tmp->prev;
  //get the next of 3
  ListNode*& node = start->next->next;
  //make a copy of that first
  ListNode* tmp2 = node;
  //3->next == 1 now
  node = tmp;
  //set 1->prev = 3
  node->prev = start->next; //LHS is 1->prev, RHS is 2->next (which is 3)
/*
  if(tmp2!=nullptr){
    node->prev = tmp2->prev;
    node->next->prev = tmp;
  }
*/
    
  //set 1->next, doesn't matter if tmp2 is null or not
  node->next = tmp2;
  //if 4 exists after 3, we need to set 4->prev = 1
  if(node->next!=nullptr)
    node->next->prev = tmp;  

//before: ->1->2->3
//now: ->2->3->1
//to rotate ->4->5->6, we need the "->" before 4, which is "->" after 1, i.e., the 1->next.
  return node->next;
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2

  if(startPoint==nullptr || endPoint==nullptr) return;

  ListNode* node = startPoint->next;
  if(node==nullptr) return;
  
  //lets say we are reversing 1,2,3,4
  //node left to 1
  ListNode *left  = startPoint->prev;
  //node 2 
  ListNode *node2 = startPoint->next;
  //node 3 
  ListNode *node3 = endPoint->prev;
  //node left to 4
  ListNode *right = endPoint->next;

  while(node!=endPoint){
    //swap prev and next for intermediate nodos
    //std::cout << "data: " << node->data << std::endl;
    ListNode* tmp = node->next;
    node->next = node->prev;
    node->prev = tmp;
    //node = node->next;  // wrong. next has been changed 
    /*
    std::cout << "data: " << node->data << std::endl;
    std::cout << "next: " << node->next->data << std::endl;
    std::cout << "prev: " << node->prev->data << std::endl;
    std::cout << "--------------" << std::endl;
    */
    node = tmp;  //proceed to next 
  }


  //swapping start and end
  //s->4 e->1
  ListNode *tmp_s = startPoint;
  startPoint = endPoint;
  endPoint = tmp_s;

  //now we take care of start and end points
  //set their next and prev correctly
  startPoint->next = node3;
  startPoint->prev = left;
  endPoint->next   = right;
  endPoint->prev   = node2;

  //now we take care of the boundaries
  if(left!=nullptr)
    left->next  = startPoint;
  if(right!=nullptr)
    right->prev = endPoint;
/*
  startPoint->next = tmp_e->prev;
  startPoint->prev = tmp_s->prev;
  endPoint->next = tmp_e -> next;
  endPoint->prev = tmp_s -> next;
*/  

/*
  if(tmp_e->next != nullptr)
    tmp_e->next->prev = tmp_s;
  if(tmp_s->prev != nullptr)
    tmp_s->prev->next = tmp_e; 
*/

/*
  std::cout << "data tmp_s: " << tmp_s->data << std::endl;
  std::cout << "data tmp_e: " << tmp_e->data << std::endl;

  std::cout << "data s: " << startPoint->data << std::endl;
  std::cout << "data e: " << endPoint->data << std::endl;
*/

  

  

/*
  startPoint->next = tmp_s->next;
  startPoint->prev = tmp_s->prev;
  endPoint->next = tmp_e->next;
  endPoint->prev = tmp_e->prev;
  // start: <-1-> ; end: <-8->
*/
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  
  if(n>=length_){
    reverse();  
    return;
  }

  unsigned rounds = length_%n==0 ? length_/n : length_/n + 1;
  unsigned index = 0;
  
  ListNode* start = head_;
  ListNode* end = head_; 

  ListNode* m_head = head_;
  ListNode* m_tail = tail_;
 

  //for(unsigned ir=0; ir<1; ir++){
  for(unsigned ir=0; ir<rounds; ir++){
    index=0;
    while((int)index<(n-1) && end->next != nullptr){
      end = end ->next;
      ++index;
    } 
    reverse(start,end);
    
    //the start of the 1st block should be the global head_
    if(ir==0)
      m_head = start;
    //the end of the last block should be the global tail_ 
    if(ir==(rounds-1))
      m_tail = end;

    start = end->next;
    end = end->next;
    
  }

  head_ = m_head;
  tail_ = m_tail;
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

  if(first==nullptr)
    return second;
  else if(second==nullptr)
    return first;

  ListNode* bigger  = (first->data) < (second->data) ? second : first; 
  ListNode* smaller = (bigger==first) ? second : first; 

  ListNode* b = bigger;
  ListNode* s = smaller;
 
  while(true){

    bool change = false;
    if(s->next==nullptr)
      change = true;
    else if( b->data < s->next->data)
      change = true;

    //if( b->data < s->next->data){
    if(change){
      ListNode* tmp = s->next;
      s->next = b;
      b->prev = s;
      s = b;
      b = tmp;
    }else{
      s = s->next;  
    } 

    //nothing left on the smaller line
    if(b==nullptr)
      break;
  }
  return smaller;

}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2

  if(chainLength<=1)
    return start;

  int half = chainLength/2;
  //start of the 2nd half
  ListNode* start2 = start;
  for(int i=0; i<half; i++){
    start2 = start2->next;
  }
  
  //don't forget to make two halves independent
  start2->prev->next = nullptr;
    
  ListNode* first = mergesort(start, half);
  ListNode* second = mergesort(start2, chainLength-half); 
 
  return merge(first,second); 

}

template <typename T>
void List<T>::printReverse(){

  List<T>::ListIterator it(tail_);
  List<T>::ListIterator null(nullptr);
  
  while(it!=null){
    std::cout << *it << std::endl;
    --it;
  } 

  List<T>::ListIterator ig(head_);
  while(ig!=null){
    std::cout << *ig << std::endl;
    ++ig;
  }
}
