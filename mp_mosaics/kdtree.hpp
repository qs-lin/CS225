/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
  if(first[curDim] < second[curDim])
    return true;
  else if(first[curDim] == second[curDim])
    return first < second;
  else
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
  double d1 = distance(target, currentBest);
  double d2 = distance(target, potential);

  if(d2<d1)  return true;
  else if(d1==d2)
    return potential < currentBest;
  else 
    return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints) : root(nullptr), size(0)
{
    /**
     * @todo Implement this function!
     */
  
  if(newPoints.size()==0){
    return;
  }
  std::vector<Point<Dim>> vec = newPoints;
  buildTree(vec,0,vec.size()-1,root,0);
  size = vec.size();
}

template <int Dim>
void KDTree<Dim>::buildTree(std::vector<Point<Dim>>& vec, size_t start_index, size_t end_index,
typename KDTree<Dim>::KDTreeNode*& node, size_t currDim){

  if(end_index<start_index) 
    return;
  
  static size_t currLayer = 0;
  //if(node==nullptr) return; 
  size_t median = (start_index+end_index)/2;
  size_t pivot = findMedian(vec,start_index,end_index,median,currDim);
  currDim = (currDim+1)%Dim;
  //std::cout << "dim++ detected" << std::endl;
  //std::cout << currDim << std::endl;
  node = new KDTreeNode(vec[pivot]); 
  if(pivot!=0)  //this is size_t, so -1 is undefined. we simply don't call recursively 
    buildTree(vec,start_index,pivot-1,node->left,currDim); 
  buildTree(vec,pivot+1,end_index,node->right,currDim); 

}

/*
*/
template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */

  copy(other);

}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  clear();
  copy(rhs);

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear();

}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
  return findNNS(query,root,0);
    //return Point<Dim>();
}

template <int Dim>
double KDTree<Dim>::distance(const Point<Dim>& p1, const Point<Dim>& p2 ) const
{
    /**
 *      * @todo Implement this function!
 *           */

  double dis = 0.;
  for(size_t i=0; i<Dim; ++i){
    dis += (p1[i] - p2[i])*(p1[i] - p2[i]);
  }

  return sqrt(dis);

}

template <int Dim>
size_t KDTree<Dim>::partition(std::vector<Point<Dim>>& vec, size_t start_index, size_t end_index, size_t currDim){

  size_t i=start_index;
  size_t j=start_index;
  for(j=start_index; j<end_index; ++j){
    if(smallerDimVal(vec[j],vec[end_index],currDim)){
      std::swap(vec[i],vec[j]);
      ++i;
    }

  }//end of j

  std::swap(vec[i],vec[end_index]);
  return i;
}

template <int Dim>
//Point<Dim> KDTree<Dim>::findMedian(std::vector<Point<Dim>>& vec, size_t start_index, size_t end_index, size_t median, size_t currDim){
size_t KDTree<Dim>::findMedian(std::vector<Point<Dim>>& vec, size_t start_index, size_t end_index, size_t median, size_t currDim){


  // here median is not the index, but ceil(n/2)th smallest;
  // remember the kth largest element index = k-1;
  // the kth smallest element index = n-k;
 
  size_t pivot = partition(vec,start_index,end_index,currDim);
  if(pivot == median) return pivot; 
  else if( pivot > median )
    return findMedian(vec,start_index,pivot-1,median,currDim);
  else
    return findMedian(vec,pivot+1,end_index,median,currDim);

}

template <int Dim>
//Point<Dim> KDTree<Dim>::findMedian(std::vector<Point<Dim>>& vec, size_t start_index, size_t end_index, size_t currDim){
size_t KDTree<Dim>::findMedian(std::vector<Point<Dim>>& vec, size_t start_index, size_t end_index, size_t currDim){
//here we infer index of median from start and endl

  

  //newly noted by Qisen: this is not gonna work
  //I didn't want the recursive calls to modify this median because this is the absolute index in the whole array
  //but if I do this, later when I call findMedian in a lower layer, the median is the value of previous layer. 

  //cant change this in recursive calls 
  const static size_t median = (start_index+end_index)/2; //use flooring 

  size_t pivot = partition(vec,start_index,end_index,currDim);
  //if(pivot == (median-1)) return vec[pivot];
  if(pivot == median) return pivot; 
  else if( pivot > median)
    return findMedian(vec,start_index,pivot-1,currDim);
  else
    return findMedian(vec,pivot+1,end_index,currDim);

}

template <int Dim>
size_t KDTree<Dim>::ceil(size_t a){


  return a%2==0 ? a/2 : (a+1)/2;
}

template <int Dim>
void KDTree<Dim>::clear(){

  if(root!=nullptr)
    _clear(root);
}
  

template <int Dim>
void KDTree<Dim>::_clear(typename KDTree<Dim>::KDTreeNode* node){
  
  if(node->left!=nullptr)
    _clear(node->left);
  if(node->right!=nullptr)
    _clear(node->right);
  delete node;
  node = nullptr;
}

template <int Dim>
void KDTree<Dim>::copy(const KDTree<Dim>& other){
  if(other.root==nullptr)
    return;
  root = _copy(other.root);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::_copy(typename KDTree<Dim>::KDTreeNode* node){

  KDTreeNode* m_node = new KDTreeNode(node->point);

  if(node->left!=nullptr)
    m_node->left = _copy(node->left);  

  if(node->right!=nullptr)
    m_node->right = _copy(node->right);


  return m_node;
}

template <int Dim>
void KDTree<Dim>::debug(){

  root->point.print();

}

template <int Dim>
//Point<Dim>::findNNS(typename KDTree<Dim>::KDTreeNode* node, const Point<Dim>& target, currDim){
Point<Dim>  KDTree<Dim>::findNNS(const Point<Dim>& target, typename KDTree<Dim>::KDTreeNode* node, size_t currDim) const{ 


/*
  //nearest = root->point;
  //initialize with root
  //static Point<Dim> nearest = root->point;
  static Point<Dim> nearest = root->point;
  Point<Dim> result = root->point;
  int direction = 0;  // 0--node 1--left 2--right
  size_t newDim = (currDim+1)%Dim;
  if(smallerDimVal(target,node->point,currDim)){    //smaller
    direction = 1;
    if(node->left!=nullptr)
      result = findNNS(target, node->left, newDim); 
    else
      result = node->point;
  }else{
    if(target==node->point)     //equal case will return false in smallerDimVal    
      result = node->point; //end of euqal
    else{
      direction = 2;
      if(node->right!=nullptr)
        result = findNNS(target, node->right, newDim); 
      else
        result = node->point;
    }//end of larger
  }//end of non-smallerDimVal
  
  if(shouldReplace(target,nearest,result)){
    nearest = result;
    //nearest = node->point;
  }

  //check the node 
  if(shouldReplace(target,nearest,node->point)){
    nearest = node->point;
  }

  //target subtree is left, we still need to check the right one
  if(abs(node->point[currDim] - target[currDim])<= distance(target,nearest)){
    Point<Dim> potential = nearest;
    if(direction == 1){
      if(node->right!=nullptr)
        potential = findNNS(target,node->right,newDim);
    }
    else if(direction == 2){
      if(node->left!=nullptr)
        potential = findNNS(target,node->left,newDim);
    }
    if(shouldReplace(target,nearest,potential)){
      nearest = potential;
    }
  }

  return nearest;
*/


/*
  //will make sure node!=nullptr before calling this function
  Point<Dim> currBest = node->point;
  size_t newDim = (currDim+1)%Dim;
  if(smallerDimVal(target,node->point,currDim){
    if(node->left!=nullptr){
      Point<Dim> potential = findNNS(target,node->left,newDim);
      if(shouldReplace(target,currBest,potential))
        currBest = potential;
    }
  }//end of left section
  else{
    if(currBest==target)
      return currBest;   //the target is in the tree. Just return it.
    else{
      if(node->right!=nullptr){
        Point<Dim> potential = findNNS(target,node->right,newDim);
        if(shouldReplace(target,currBest,potential))
          currBest = potential;
      }
    }//end of right section
  }
*/
  Point<Dim> currBest = node->point;
  int direction = 0;
  size_t newDim = (currDim+1)%Dim;
  if(currBest==target)
    return currBest;  //find the target in the tree and simply return it
  else{  //else we go all the way down to the target tree leaf 
    Point<Dim> potential = currBest;
    if(smallerDimVal(target,node->point,currDim)){
      direction = 1;
      if(node->left!=nullptr)
        potential = findNNS(target,node->left,newDim);
    //end of left section
    }else{
      direction = 2;
      if(node->right!=nullptr)
        potential = findNNS(target,node->right,newDim);
   //end of right section
    }
    if(shouldReplace(target,currBest,potential))
      currBest = potential;
  }

   //there is no need to compare currBest with node->point one more time since currBest is initialized by node->point 
  
  //check the non-target tree.
  //remember use <= rather than < since we need point comparision to break the tie
  if( abs(node->point[currDim]-target[currDim])<= distance(target,currBest) ){
    Point<Dim> potential = currBest;  
    if(direction==1 && node->right!=nullptr)
      potential = findNNS(target,node->right,newDim);
    else if(direction==2 && node->left!=nullptr)
      potential = findNNS(target,node->left,newDim);
    
    if(shouldReplace(target,currBest,potential))
      currBest = potential;
  } 

return currBest;
}

