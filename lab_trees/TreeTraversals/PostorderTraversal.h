#pragma once
#include "../binarytree.h"
#include "TreeTraversal.h"

#include <iterator>
#include <stack>

template <typename T>
class PostorderTraversal : public TreeTraversal<T> {

  
  public:

  //ctor
  PostorderTraversal(typename BinaryTree<T>::Node* treeNode) : root(treeNode){

/*
    while(treeNode->left != NULL){
      stack.push(treeNode);
      treeNode=treeNode->left;
    }
*/
    add(treeNode);

  }

  PostorderTraversal():root(NULL){}

  typename TreeTraversal<T>::Iterator begin(){

    return typename TreeTraversal<T>::Iterator(this,root); 
  }

  typename TreeTraversal<T>::Iterator end(){

    return typename TreeTraversal<T>::Iterator(); 
  }

  void add(typename BinaryTree<T>::Node* node){
/*
    if(treeNode->right==nullptr)
      return;
    typename BinaryTree<T>::Node* node = treeNode->right;
    while(node!=nullptr){
      stack.push(node);
      node = node->left;
    }
*/


  if(node==nullptr)
    return;

  //keep going to the left
  while(node->left!=nullptr){
    stack.push(node);
    node = node->left;
  }

  stack.push(node);

  //when we hit the left-most, we turn to the right since this is post-order.
  if(node->right!=nullptr){
    node = node->right;  
    add(node);
  }
}

  typename BinaryTree<T>::Node* pop(){
    typename BinaryTree<T>::Node* node = stack.top();
    stack.pop();
    //for{r,TL,TR}, now we are done with TL
    //we need add TR before r 
    //if(node == stack.top()->right || stack.empty())
    if(stack.empty()){
      return nullptr;
    }else{
      if(node == stack.top()->right)
        return nullptr;
      else
        return stack.top()->right; 
    }
  }

  typename BinaryTree<T>::Node* peek() const{
    //typename BinaryTree<T>::Node* node = stack.top();
    //if(stack.top()==NULL)
      //stack.pop();

    return empty() ? NULL : stack.top(); 
  }

  bool  empty() const{
    return stack.empty();
  }

  void print() {
    
    std::stack< typename BinaryTree<T>::Node* > stack1 = stack;    
    while(!stack1.empty()){
      std::cout << stack1.top()->elem << std::endl;
      stack1.pop();
    }
  }

  private:
    std::stack< typename BinaryTree<T>::Node* > stack;    
    typename BinaryTree<T>::Node* root; 




};
