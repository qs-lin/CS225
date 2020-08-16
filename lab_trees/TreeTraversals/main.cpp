#include <algorithm>
#include <iostream>
#include "InorderTraversal.h"
#include "InorderTraversal2.h"
#include "PreorderTraversal.h"
#include "PostorderTraversal.h"
#include "LevelTraversal.h"
//#include "PreorderTraversal_queue.h"

using namespace std;

int main() {
    // For deterministic behavior, use a fixed seed instead of a random device
    std::random_device r;
    std::mt19937 rng(r());

    BinaryTree<int> myTree;
    for (int i = 1; i <= 10; i++)
        myTree.insertRandom(i, rng);
    myTree.print();


    PreorderTraversal<int> pot(myTree.getRoot());
    cout<<"Preorder Traversal: ";
    for (TreeTraversal<int>::Iterator it = pot.begin(); it != pot.end(); ++it) {
        cout<<(*it)->elem<<" ";
    }
    cout<<endl;

    LevelTraversal<int> level(myTree.getRoot());
    cout<<"LevelTraversal Traversal: ";
    for (TreeTraversal<int>::Iterator it = level.begin(); it != level.end(); ++it) {
        cout<<(*it)->elem<<" ";
    }
    cout<<endl;


    InorderTraversal<int> iot(myTree.getRoot());
    cout<<"Inorder Traversal:  ";
    for (TreeTraversal<int>::Iterator it = iot.begin(); it != iot.end(); ++it) {
        cout<<(*it)->elem<<" ";
    }
    cout<<endl;

    InorderTraversal2<int> iot2(myTree.getRoot());
    cout<<"Inorder Traversal2:  ";
    for (TreeTraversal<int>::Iterator it = iot2.begin(); it != iot2.end(); ++it) {
        cout<<(*it)->elem<<" ";
    }
    cout<<endl;

    PostorderTraversal<int> post(myTree.getRoot());
    cout<<"Postorder Traversal:  "; 
    //post.print();
    int index = 0;
    for (TreeTraversal<int>::Iterator it = post.begin(); it != post.end() ; ++it) {
        cout<<(*it)->elem<<" ";
//        std::cout << "index: " << index << std::endl;
        index++;
    }

    cout<<endl;

  return 0;
}
