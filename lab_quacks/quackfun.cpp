/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
//my first solution. Not a good idea since it involes copy of whole stack 
/*
  if(s.size()==1)
    return s.top();
  else{
    T top = s.top();
    stack<T> s_tmp = s;
    s_tmp.pop();
    return (top + sum(s_tmp));
  }
*/  

  if(s.size()==0)
    return 0;
  T top = s.top();
  s.pop();
  T remain = sum(s);
  s.push(top);
  return top + remain;

    // Your code here
    //return T(); // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{

    // @TODO: Make less optimistic
  //queue<char> copy = input;
  stack<char> s;
  while(!input.empty()){
    char top = input.front();
    if(top=='[')
      s.push(top);
    else if(top==']'){

      if(s.empty())
        return false;
      else
        s.pop();

    }
    input.pop();
  }
  return s.empty(); 
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& orig)
{
    stack<T> s;
    queue<T> q;

    unsigned cnt = 1;
    unsigned round = 0; 
    unsigned total = orig.size();
    while(!orig.empty()){
      unsigned amount = cnt < orig.size() ? cnt : orig.size();
      for(unsigned i=0; i<amount; i++){  
        T top = orig.front();
        orig.pop();
        if(round%2==0)
          q.push(top);
        else
          s.push(top);
      }  
      if(round%2!=0){
        for(unsigned i=0; i<amount; i++){
          q.push(s.top());
          s.pop();
        }
      }
      cnt++;
      round++;
      
    }

    //reset
    while(!q.empty()){
      orig.push(q.front());
      q.pop();
    }

/*
    while(orig.size()<total){
      if(round%2==0){
        unsigned amount = cnt < q.size() ? cnt : q.size();
        for(unsigned i=0; i<amount; i++){        
          T top = q.front();
          q.pop();
          orig.push(top);
        }
      }//end of queue
      else{
        unsigned amount = cnt < s.size() ? cnt : s.size();
        for(unsigned i=0; i<amount; i++){        
          T top = s.top();
          s.pop();
          orig.push(top);
        }
      }//end of stack
      round++;
      cnt++;
    }
*/
}//end of function

}//end of namespace 
