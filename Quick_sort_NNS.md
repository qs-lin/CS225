# Quick sort

pseudo code

```c++
quicksort(A,l,r){
  if(l<r){
    pivot = partition(A,l,r);
    quicksort(A,l,pivot-1);
    quicksort(A,pivot+1,r);
  }
}
```

## Partition

For a chosen pivot, move things smaller to its left and things larger to its right.

We can always choose the right most index as our pivot, in this case (A,l,r), we choose A[r].

In order to do this, we need two indices i and j, where 

i: remembering the last element "inserted into" the left section (smaller). 

j: scanner index

That means for any k<=i, A[i] <= A[r] (pivot)

So if A[j] > A[r], do nothing

A[j] <= A[r], we find an element that should be in the left section, so we swap the value A[i+1] and A[j] and increment i by 1.



In this way, we just find the position for the pivot in a totally sorted array: everything on the left is smaller and everything right is bigger. And we call this recursively on both ends until we find the position for all elements. 



# Quick select

Idea is very similar to quick sort. 

For a sorted array, we know the index for kth largest item is n-k.

We pick a pivot randomly (the last element), and do a 

```c++
 pivot = partition(arr,0,size-1)
```

and this will return the index of where the last element should sit at if this is a sorted array. If (n-k) > pivot, that means the item we are looking for is on the right, so we get rid of the left half and recursively apply this partition

```c++
 pivot = partition(arr,pivot+1,size-1)
```

## Complexity = O(n)

T(n) = T(n/2) + (n-1)

so work = n-1 + n/2 -1 + n/4 -1 + ... 

​               = O(n)



# K-D tree

This binary tree is built based on quick sort:

​	key is to find the median in one dimension and put every smaller item on its left and every bigger item on its right. This is exactly using a quick select to find the median (size/2 th largest) and by the time we find it, we've also done all the partition. 



# NNS

Nearest neighbor search: In-order traversal on a k-d tree. We call query point target point and we name our function findnns

We know that if that query point exists in our tree, then it must be the solution with distance = 0. So let's try to find this one first. We search it on the kd binary tree from the root. If q.x > node.x , then we know our target tree should be the right subtree. Let's then call this findnns(node->rightTree). This path ends when we hit a leaf and now we start rewinding the recursion. So whenever we find a better solution when we rewind the recursion, remember to update minDis and solutionPoint(x,y). 



Let's say now we are at a node called subnode when we rewind the recursion. So we've already known the minDis and solutionPoint(x,y) on one of its subtree (we call it a target-tree, remember that we find the target tree by comparing the corresponding dimension , i.e., which layer of tree we are at). Now we find the distance of the subnode itself and figure out whether we should update. And then we go to the other tree (non-target tree) if necessary.  Let's say this subnode is x-dimension. If abs(subnode.x - solutionPoint.x) > minDis, then there is no need to go to this non-target tree. Because for any point P in the non-target tree, abs(p.x-solutionPoint.x)> abs(subnode.x - solutionPoint.x) > mninDis. 

```c++
Dis = findnns(target_subtree);
check_distance(node) {
if sqrt((node.x-solutionPoint.x)^2 + (node.y-solutionPoint.y)^2) < minDis;  
//update
}
if(abs(node.x-solutionPoint.x)<minDis)  //there is a chance that minDis exists in the other subtree
  findnns(non_target_subtree)
```

So the architecture is a In-order traversal. The idea that using kd-tree to look for NNS is it has the chance that we can get rid of one of its two children. 