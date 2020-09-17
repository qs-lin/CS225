std::vector<int> SquareMaze::solveMaze_(int x,int y){

  std::vector<int> path;
  std::stack<std::pair<int,int>> stack;

  visited[x][y] = true;
  std::pair<int,int> p(x,y);
  stack.push(p);

  while(!stack.empty()){
    std::pair<int,int> top = stack.top();
    stack.pop();
    if(canTravel(x,y,0)){
      if(!visited[x+1][y]){
        std::pair<int,int> p(x+1,y);
        stack.push(p);
        visited[x+1][y] = true;
      }
    }
    if(canTravel(x,y,1)){
      if(!visited[x][y+1]){
        std::pair<int,int> p(x,y+1);
        stack.push(p);
        visited[x][y+1] = true;
      }
    }
  }
  return std::vector<int>();
}
