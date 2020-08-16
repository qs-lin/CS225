#pragma once
	
#include "../binarytree.h"
#include "TreeTraversal.h"

#include <iterator>
#include <stack>

/**
 * A derived, templatized class for inorder traversal algorithms on trees.
 * 
 * Simulates an iterative traversal of a given tree using a stack
 * and a given root node.
 */
template <typename T>
class InorderTraversal2 : public TreeTraversal<T> {
  public: 
    /**
     * Initializes a Inorder TreeTraversal of a tree,
     * with the traversal storing the tree's root.
     * Hint: See lab handout for guidance
     *
     * @param root The root node of the tree
     */	
    InorderTraversal2(typename BinaryTree<T>::Node* root)
	    : root(root)
    {
      //stack.push(root);	
      // your code here
      //write_to_stack(root);
      while(root!=nullptr){
        stack.push(root);
        root = root->left;
      }
    }

    /**
     * Returns an iterator for the traversal starting at the root node.
     * Important for sake of looping through an iterator's contents.
     * 
     * @return The iterator object pointing to the first node in the traversal
     */	
    typename TreeTraversal<T>::Iterator begin() {
      return typename TreeTraversal<T>::Iterator(this, root);
    }

    /**
     * Returns an iterator for the traversal pointing to the
     * element one past the end of the traversal.
     * Important for the sake of looping through an iterator's contents
     * 
     * @return The iterator object pointing to the elemnt after the end of the traversal.
     */	
    typename TreeTraversal<T>::Iterator end() {
      return typename TreeTraversal<T>::Iterator();
    }

    /**
     * Given a node in the tree, add the next appropriate
     * nodes to the stack such that when popped, and inorder
     * traversal is simulated.
     * Hint: See lab handout for guidance
     * 
     * @param treeNode The subroot that determines what next nodes
     *        should be added to the traversal
     */	
    void add(typename BinaryTree<T>::Node * treeNode) {
      // your code here
      if(treeNode->right==nullptr)
        return;	
      typename BinaryTree<T>::Node* newNode = treeNode->right;
      while(newNode!=nullptr){
        stack.push(newNode);
        newNode = newNode->left;
      }
    }

    /**
     * Removes and returns the current node in the traversal.
     * 
     * @return The current node in the traversal
     */	
    typename BinaryTree<T>::Node* pop() {
      typename BinaryTree<T>::Node* topNode = stack.top();
      stack.pop();
      return topNode;
    }

    /**
     * Returns the current node in the traversal or
     * NULL if the stack is empty.
     * 
     * @return The current node in the traversal
     */	
    typename BinaryTree<T>::Node* peek() const {
      return empty() ? NULL : stack.top();
    }

    /**
     * Returns true if the traversal is empty.
     * 
     * @return true if the traversal is empty.
     */	
    bool empty() const {
      return stack.empty();
    }

  private:
    std::stack<typename BinaryTree<T>::Node*> stack;
    typename BinaryTree<T>::Node* root;
    void write_to_stack( typename BinaryTree<T>::Node* node){

      if(node->right!=nullptr)
        write_to_stack(node->right);

      stack.push(node);

      if(node->left!=nullptr)
        write_to_stack(node->left);



    }
};
