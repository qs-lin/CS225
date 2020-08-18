/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& node)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* t = node;
    Node* x = t->right;

    t->right = x->left;
    x->left  = t; 
    node = x; 
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& node)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    
    Node* t = node;
    Node* x = node->left;

    t->left = x->right;
    x->right = t;
    node = x;
    // your code here
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
    // your code here
}

template <class K, class V>
int AVLTree<K,V>::balance(const Node* node) const{

    //std::cout << "balance function called" << std::endl;
    return heightOrNeg1(node->right) - heightOrNeg1(node->left);

} 

template <class K, class V>
void AVLTree<K,V>::updateHeight(Node*& node){

/*
    std::cout << "node V: " << node->value << std::endl;
    std::cout << "height before: " << node->height << " balance before: " << balance(node) << std::endl;
*/
    node->height = std::max(heightOrNeg1(node->left),heightOrNeg1(node->right)) + 1;
    //std::cout << "height after: " << node->height << " balance after: " << balance(node) << std::endl; 

}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& node) 
{

  //lets update this node first
  //since we could've inserted or deleted a node in its downstream

  if(node==nullptr)
    return;

  updateHeight(node);
  int bal = balance(node);

  if(bal>=2){
    Node* right = node->right;
    //left rotation
    if(balance(right)==1){

      rotateLeft(node);
      //rotation is local. only affect node and its left sub
      updateHeight(node->left); 
      updateHeight(node); 

    //right-left rotation
    }else if(balance(right)==-1){
    
      rotateRightLeft(node);
      //rotation is local. only affect node and its both sub
      updateHeight(node->left); 
      updateHeight(node->right); 
      updateHeight(node); 

    } 

  }else if(bal<=-2){
    Node* left = node->left;
    //left rotation
    if(balance(left)==-1){
    
      rotateRight(node);
      updateHeight(node->right); 
      updateHeight(node); 
    
    }else if(balance(left)==1){ 

      rotateLeftRight(node);
      updateHeight(node->left);
      updateHeight(node->right);
      updateHeight(node);

    }

  }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    //std::cout << "debug --------------------------" << std::endl;
    insert(root, key, value);
}

template <class K, class V>
typename AVLTree<K,V>::Node*& AVLTree<K,V>::_find(Node*& node, const K& key) const{

  if(node==nullptr)
    return node;
    //node = new Node(key,value); 
  else{
    if(key<node->key)
      return _find(node->left, key);
    else if(key==node->key)
      return node;
    else
      return _find(node->right, key);

   } 
 
}

/*
template <class K, class V>
void AVLTree<K,V>::test(){

  const K& key = root->left->left->right->key;
  Node*& node = _findIOP(key);
  //std::cout << "iop: " << node->value << std::endl;
  //std::cout << "iop:" << std::endl;
  std::cout << node->key << std::endl;

}


template <class K, class V>
typename AVLTree<K,V>::Node*& AVLTree<K,V>::_findIOP(const K& key) {

  std::stack<typename AVLTree<K,V>::Node*> stack;
  return _findIOP(stack,root,key);

}

template <class K, class V>
typename AVLTree<K,V>::Node*& AVLTree<K,V>::_findIOP(std::stack<typename AVLTree<K,V>::Node*>& stack, Node*& node, const K& key) {


  if(node->left!=nullptr)
    _findIOP(stack,node->left,key);
    stack.push(node);
  if(node->right!=nullptr)
    _findIOP(stack, node->right,key);

  if(!stack.empty()){
    if(stack.top()->key == key){
      stack.pop();
      if(!stack.empty())
        return stack.top();
    }
  }
  return root;
}
*/
/*
template <class K, class V>
typename AVLTree<K,V>::Node*& AVLTree<K,V>::_findIOP(Node*& node, const K& key) {



  if(node->left!=nullptr)
    _findIOP(node->left,key);
  if(node->key == key)
    return stack.top();
  else
    stack.push(node);
  if(node->right!=nullptr)
    _findIOP(node->right,key);

  return nullptr;


}
*/


template <class K, class V>
void AVLTree<K, V>::insert(Node*& node, const K& key, const V& value)
{
    
 //this is not correct
 //you need recursive explicitly here since you need to rebalance each node
 //when we rewind the recursion
/*
  Node*& newNode = _find(root,key);
  newNode = new Node(key,value);
*/
    // your code here

  if(node==nullptr){
    node = new Node(key,value);
  }else{

    if(key<node->key)
      insert(node->left,key,value);
    else
      insert(node->right,key,value);

  }  
  //check balancing when we rewind the recursion
  rebalance(node);

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
      remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
      remove(subtree->right, key);   
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = nullptr;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
           
          Node* tmp = subtree->left;

          //going down from subtree to its iop, which is the right-most node on its left subtree
          while(tmp->right != nullptr)
            tmp = tmp->right;

          swap(subtree,tmp);

          //we are doing this because tmp is a copy to IOP, not a reference
          //actually this is absolutely necessary
          //lets say if now tmp is a reference to the IOP, you may just delete tmp after calling 
          //swap(subtree,tmp), in this way, we avoid going down from subtree to tmp one more time 
          //and we can simply rewind the recursion from subtree
          //but don't forget that remove() will also check the balance of node on each recursion
          //so it will not check the balance of nodes from tmp back to subtree 
          remove(subtree->left, key);
    


        } else {
            /* one-child remove */
            // your code here
/*
          Node* tmp = subtree;
          subtree = subtree->left != NULL ? subtree->left : subtree->right;
          delete tmp;
*/

          if(subtree->left != NULL){
/*
            Node* tmp = subtree;
            subtree = subtree->left;
            delete tmp; 
*/
            Node* temp = subtree->left;
            delete subtree;
            subtree = temp;
          }else{
/*
            Node* tmp = subtree;
            subtree = subtree->right;
            delete tmp; 
*/
            Node* temp = subtree->right;
            delete subtree;
            subtree = temp;
          }
        }
        // your code here
    }

    rebalance(subtree);
}
