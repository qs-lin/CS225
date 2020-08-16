#pragma once

#include "../binarytree.h"
#include "TreeTraversal.h"

#include <iterator>
#include <queue>

/**
 * A derived, templatized class for preorder traversal algorithms on trees.
 * 
 * Simulates an iterative traversal of a given tree using a queue
 * and a given root node.
 */
template <typename T>
class LevelTraversal : public TreeTraversal<T> {
    public: 
        /**
         * Initializes a Preorder TreeTraversal of a tree,
         * with the traversal storing the tree's root.
         * 
         * @param root The root node of the tree
         */
        LevelTraversal(typename BinaryTree<T>::Node* root)
            : root(root)
        { 
            queue.push(root); 
        }

        /**
         * Returns an iterator for the traversal starting at the root node.
         * Important for the sake of looping through an iterator's contents.
         * 
         * @return The iterator object pointing to the first node in the traversal
         */
        typename TreeTraversal<T>::Iterator begin() {
            return typename TreeTraversal<T>::Iterator(this, root);
        }

        /**
         * Returns an iterator for the traversal one past the end of the traversal.
         * Important for the sake of looping through an iterator's contents.
         * 
         * @return The iterator object pointing to the element after the end of the traversal.
         */
        typename TreeTraversal<T>::Iterator end() {
            return typename TreeTraversal<T>::Iterator();
        }

        /**
         * Adds the children of the given node to the queue to be processed later
         * The right child is added before the left child to ensure that the left
         * is popped before the right, thus following the rules of preorder traversals.
         * 
         * @param treeNode The subroot whose children should be added
         */
        void add(typename BinaryTree<T>::Node * treeNode) {
            if (treeNode->left != NULL) { 
                queue.push(treeNode->left);
            }
            if (treeNode->right != NULL) {
                queue.push(treeNode->right);
            }	
        }

        /**
         * Removes and returns the current node in the traversal
         * 
         * @return The current node in the traversal
         */
        typename BinaryTree<T>::Node* pop() {
            typename BinaryTree<T>::Node* p = queue.front();
            queue.pop();
            return p;
        }

        /**
         * Returns the current node in the traversal or
         * NULL if the queue is empty.
         * 
         * @return The current node in the traversal
         */
        typename BinaryTree<T>::Node* peek() const {
            return empty() ? NULL : queue.front();
        }

        /**
         * Returns true if the traversal is empty.
         * 
         * @return true if the traversal is empty.
         */
        bool empty() const {
            return queue.empty();
        }

    private:
        std::queue<typename BinaryTree<T>::Node*> queue;
        typename BinaryTree<T>::Node* root;
};