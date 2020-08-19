/**
 * @file btree.cpp
 * Implementation of a B-tree class which can be used as a generic dictionary
 * (insert-only). Designed to take advantage of caching to be faster than
 * standard balanced binary search trees.
 */

/**
 * Finds the value associated with a given key.
 * @param key The key to look up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const K& key) const
{
    return root == nullptr ? V() : find(root, key);
}

/**
 * Private recursive version of the find function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param key The key we are looking up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const BTreeNode* subroot, const K& key) const
{
    /* TODO Finish this function */

    bool if_find = false;
    size_t first_larger_idx = insertion_idx(subroot->elements, key);
    if(first_larger_idx<subroot->elements.size()){
      if(subroot->elements[first_larger_idx].key==key)
        //return subroot->elements[first_larger_idx].value;
        if_find = true;
    }
    if(!if_find){
      if(subroot->is_leaf)
        return V();
      else
        return find(subroot->children[first_larger_idx], key);
    }else
      return subroot->elements[first_larger_idx].value;

    /* If first_larger_idx is a valid index and the key there is the key we
     * are looking for, we are done. */

    /* Otherwise, we need to figure out which child to explore. For this we
     * can actually just use first_larger_idx directly. E.g.
     * | 1 | 5 | 7 | 8 |
     * Suppose we are looking for 6. first_larger_idx is 2. This means we want to
     * explore the child between 5 and 7. The children vector has a pointer for
     * each of the horizontal bars. The index of the horizontal bar we want is
     * 2, which is conveniently the same as first_larger_idx. If the subroot is
     * a leaf and we didn't find the key in it, then we have failed to find it
     * anywhere in the tree and return the default V.
     */

    //return V();
}

/**
 * Inserts a key and value into the BTree. If the key is already in the
 * tree do nothing.
 * @param key The key to insert.
 * @param value The value to insert.
 */
template <class K, class V>
void BTree<K, V>::insert(const K& key, const V& value)
{
    /* Make the root node if the tree is empty. */
    if (root == nullptr) {
        root = new BTreeNode(true, order);
    }
    insert(root, DataPair(key, value));
    /* Increase height by one by tossing up one element from the old
     * root node. */
    if (root->elements.size() >= order) {
        BTreeNode* new_root = new BTreeNode(false, order);
        new_root->children.push_back(root);
        split_child(new_root, 0);
        root = new_root;
    }
}

/**
 * Splits a child node of a BTreeNode. Called if the child became too
 * large.
 * @param parent The parent whose child we are trying to split.
 * @param child_idx The index of the child in its parent's children
 * vector.
 */
template <class K, class V>
void BTree<K, V>::split_child(BTreeNode* parent, size_t child_idx)
{
    /* Assume we are splitting the 3 6 8 child.
     * We want the following to happen.
     *     | 2 |
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     *
     * Insert a pointer into parent's children which will point to the
     * new right node. The new right node is empty at this point.
     *     | 2 |   |
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     * Insert the mid element from the child into its new position in the
     * parent's elements. At this point the median is still in the child.
     *     | 2 | 6 |
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     * Now we want to copy over the elements (and children) to the right
     * of the child median into the new right node, and make sure the left
     * node only has the elements (and children) to the left of the child
     * median.
     *     | 2 | 6 |
     *    /   /     \
     * | 1 | | 3 | | 8 |
     *
     */

    /* The child we want to split. */
    BTreeNode* child = parent->children[child_idx];
    /* The "left" node is the old child, the right child is a new node. */
    BTreeNode* new_left = child;
    BTreeNode* new_right = new BTreeNode(child->is_leaf, order);

    bool is_child_leaf = child->is_leaf;
    /* E.g.
     * | 3 | 6 | 8 |
     * Mid element is at index (3 - 1) / 2 = 1 .
     * Mid child (bar) is at index 4 / 2 = 2 .
     * E.g.
     * | 2 | 4 |
     * Mid element is at index (2 - 1) / 2 = 0 .
     * Mid child (bar) is at index 2 / 2 = 1 .
     * This definition is to make this BTree act like the visualization
     * at
     * https://www.cs.usfca.edu/~galles/visualization/BTree.html
     */
    size_t mid_elem_idx = (child->elements.size() - 1) / 2;
    size_t mid_child_idx = child->children.size() / 2;

    /* Iterator for where we want to insert the new child. */
    auto child_itr = parent->children.begin() + child_idx + 1;
    /* Iterator for where we want to insert the new element. */
    auto elem_itr = parent->elements.begin() + child_idx;
    /* Iterator for the middle element. */
    auto mid_elem_itr = child->elements.begin() + mid_elem_idx;
    /* Iterator for the middle child. */
    auto mid_child_itr = child->children.begin() + mid_child_idx;

    //insert the mid of child to parent
    parent->elements.insert(elem_itr, child->elements[mid_elem_idx]);
    //insert one pointer after the original child 
    //so this newly added: new_right will point to splitted right half
    //while child is pointing to splitted left half
    parent->children.insert(child_itr, new_right); 

    //now we split child->elements into new left and new right 

    //copy everything after mid to new_right and delete them from left
    for(size_t index=mid_elem_idx+1; index<=order-1; index++){
      child->elements.pop_back();
      new_right->elements.push_back(child->elements[index]);
    }//delete mid from left
    child->elements.pop_back();

 
    //now we split child->children into new left and new right if child is not leaf 
    if(!is_child_leaf){
      for(size_t index=mid_child_idx; index<=order; index++){
        child->children.pop_back();
        new_right->children.push_back(child->children[index]);
      }
    }

    /* TODO Your code goes here! */
}

/**
 * Private recursive version of the insert function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param pair The DataPair to be inserted.
 * Note: Original solution used std::lower_bound, but making the students
 * write an equivalent seemed more instructive.
 */
template <class K, class V>
void BTree<K, V>::insert(BTreeNode* subroot, const DataPair& pair)
{
    /* There are two cases to consider.
     * If the subroot is a leaf node and the key doesn't exist subroot, we
     * should simply insert the pair into subroot.
     * Otherwise (subroot is not a leaf and the key doesn't exist in subroot)
     * we need to figure out which child to insert into and call insert on it.
     * After this call returns we need to check if the child became too large
     * and thus needs to be split to maintain order.
     */

    size_t first_larger_idx = insertion_idx(subroot->elements, pair);
    bool if_find = false;
    if(first_larger_idx<subroot->elements.size()){
      if(subroot->elements[first_larger_idx].key==pair.key)
        if_find = true;
    }

    if(if_find) 
      return;
    else{
      if(subroot->is_leaf){
        auto itPos = subroot->elements.begin()+first_larger_idx;
        subroot->elements.insert(itPos,pair);
        //subroot->elements.insert(first_larger_idx,pair);
      }//end of leaf case
      else{   //goto subtree and split current node when we rewind the recursion later
        insert(subroot->children[first_larger_idx], pair);
        if(subroot->children[first_larger_idx]->elements.size()>=order)
          split_child(subroot, first_larger_idx);
      }//end of internal node case
    }//end of not found 


    /* TODO Your code goes here! */
}
