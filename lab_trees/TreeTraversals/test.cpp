#include <stack>
#include <iostream>

int main(){

  std::stack<int*> stack;
  stack.push(NULL);
  stack.push(nullptr);
  if(stack.empty()) 
    std::cout << "empty" << std::endl;

  if(stack.top()==NULL)
    std::cout << "equal" << std::endl;
return 0;
}
