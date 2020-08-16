/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include "TreeTraversals/TreeTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{

  mirror(root);
    //your code here
}

template <typename T>
void BinaryTree<T>::mirror(Node* node){

  if(node->left==nullptr && node->right==nullptr)
    return;

  Node* tmp = node->left;
  node->left = node->right;
  node->right = tmp;

 if(node->right != nullptr)
   mirror(node->right);
 if(node->left != nullptr)
   mirror(node->left);
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    InorderTraversal<T> iot(root);
    typename TreeTraversal<T>::Iterator ig = iot.begin();

    T start = (*ig)->elem;
    ++ig;
    //more than 1 element
    if(ig!=iot.end()){ 
      for(typename TreeTraversal<T>::Iterator it=ig; it!=iot.end(); ++it){
        if((*it)->elem < start)
          return false;
        else
          start = (*it)->elem; 
      }
    }
    //single element just return true
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    //return isOrderedRecursive(root);
    return isOrderedRecursive(root, INT_MAX, INT_MIN);
}

template <typename T>
T BinaryTree<T>::min(Node *node) const{
  while(node->left!=nullptr)
    //for BST, the min is on the left-most
    node = node->left;

  //return T();
  return node->elem; 
}

template <typename T>
T BinaryTree<T>::max(Node *node) const{
  while(node->right!=nullptr)
    //for BST, the max is on the right-most
    node = node->right;
  return node->elem;
}

// this was my 1st solution but I don't like it. You have to find the max/min of a subtree during each
// recursion and this is heavy duty 

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node *node) const
{
    // your code here
    if(node->right==nullptr && node->left==nullptr)
      return true;
    if(node->right!=nullptr && node->left==nullptr)
      //return ( (node->elem < node->right->elem) && isOrderedRecursive(node->right) );
      return ( (node->elem < min(node->right)) && isOrderedRecursive(node->right) );
    if(node->right==nullptr && node->left!=nullptr)
      //return ( (node->left->elem < node->elem) && isOrderedRecursive(node->left) );
      return ( (max(node->left)< node->elem) && isOrderedRecursive(node->left) );
    else
      //return ( (node->elem < node->right->elem) && isOrderedRecursive(node->right)  && (node->left->elem < node->elem) && isOrderedRecursive(node->left));
      return ( (node->elem < min(node->right)) && isOrderedRecursive(node->right) && (max(node->left)< node->elem) && isOrderedRecursive(node->left) );
    
}


template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node *node, T max, T min) const{

  if(node==nullptr)
    return true;

  //if node is on the left, then it should be smaller than its parent
  //if node is on the right, then it should be bigger than its parent
  if(node->elem < min || node->elem > max)
    return false;
    
    
  //make sure node is max of its left tree and min of its right tree
  return isOrderedRecursive(node->left, node->elem, min) && isOrderedRecursive(node->right, max, node->elem); 
  


}
