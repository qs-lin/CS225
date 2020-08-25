
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return (2*currentIdx+1);
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    if( leftChild(currentIdx) >= _elems.size() )
    //if( leftChild(currentIdx) > _elems.size() )
      return false;
    else 
      return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t leftIndex  = leftChild(currentIdx);
    size_t rightIndex = rightChild(currentIdx);
    if(rightIndex >= _elems.size())
      return leftIndex;
    T left  = _elems[leftIndex];
    T right = _elems[rightIndex];

    if(higherPriority(left, right)){  //true if left<right so left has higher priority
      return  leftIndex;
    }else
      return rightIndex;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.

  if(!hasAChild(currentIdx))  return;
  size_t maxPChild = maxPriorityChild(currentIdx);
  if(higherPriority(_elems[maxPChild], _elems[currentIdx])){
    std::swap(_elems[maxPChild], _elems[currentIdx]);
    heapifyDown(maxPChild);
  }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
  _elems.push_back(T());    

}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm

  _elems.push_back(T());
  for( auto & t : elems )
    _elems.push_back(t);
  //_elems.assign(elems.begin(),elems.end());
  //each leaf is a heap itself, for a complete tree, first non-leaf index is the parent of last elem
  size_t firstNonLeaf = parent(_elems.size()-1);
  for(size_t i=firstNonLeaf; i>=root(); --i){
    heapifyDown(i);
  }

}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if(_elems.size()<=1){
     // _elems.erase(_elems.begin());
      return T(); 
    }
    T ret = _elems[root()];
    //swap with the last elem
    std::swap(_elems[root()], _elems[_elems.size()-1]);
    typename std::vector<T>::iterator it = _elems.begin() + (_elems.size()-1); 
    _elems.erase(it);
    heapifyDown(root());
    return ret;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    if(_elems.size()>1)
      return _elems[root()];
    else
      return T();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
  _elems.push_back(elem);
 heapifyUp(_elems.size()-1);
    // @TODO Add elem to the heap
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update

  _elems[idx] = elem;
  //compare with parent
  if(higherPriority(_elems[idx],_elems[parent(idx)])){
    //std::swap(_elems[idx],_elems[parent(idx)]);
    //heapifyUp(parent(idx));
    heapifyUp(idx);
  }else{
    heapifyDown(idx);
/*
    if(hasAChild(idx)){
      size_t maxPChild = maxPriorityChild(idx);
      if(!higherPriority(_elems[idx],_elems[maxPChild])){  //child has higher priority
        std::swap(_elems[idx],_elems[maxPChild]);
        heapifyDown(_elems[maxPChild]);
      }
    }else
      return;
*/
  }//end of else

}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    if(_elems.size()>1)
      return false;
    else return true;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
