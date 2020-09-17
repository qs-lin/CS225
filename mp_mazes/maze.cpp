/* Your code here! */

#include "maze.h"

SquareMaze::SquareMaze() : wall(nullptr), forest(nullptr), visited(nullptr),
dist(nullptr),
pred(nullptr)

{
//SquareMaze::SquareMaze() : wall(nullptr) {
  
  //forest = new DisjointSets();
  _width = 0;
  _height = 0;
  soln.clear();
  destination = 0;
}

SquareMaze::~SquareMaze(){
  clear_wall();
  clear_forest();
}

void SquareMaze::clear_wall(){

  for(int i=0;i<_width;++i){
    for(int j=0;j<_height;++j){
      if(wall[i][j]!=nullptr){
        delete[] wall[i][j];
        wall[i][j] = nullptr;
      }  
    }
    if(wall[i]!=nullptr){
      delete[] wall[i];
      wall[i] = nullptr;
    }
    if(visited[i] != nullptr){
      delete[] visited[i];
      visited[i] = nullptr;
    }
    if(dist[i] != nullptr){
      delete[] dist[i];
      dist[i] = nullptr;
    }
    if(pred[i] != nullptr){
      delete[] pred[i];
      pred[i] = nullptr;
    }
  }

  if(wall!=nullptr){
    delete[] wall;
    wall = nullptr;
  }
  if(visited!=nullptr){
    delete[] visited;
    visited = nullptr;
  }
  if(dist!=nullptr){
    delete[] dist;
    dist = nullptr;
  }
  if(pred!=nullptr){
    delete[] pred;
    pred = nullptr;
  }

  _height = 0;
  _width = 0;
}

void SquareMaze::clear_forest(){
  if(forest!=nullptr){
    delete forest;
    forest= nullptr;
  }
}

bool SquareMaze::check_cycle(){

  for(int i=0; i<_width; ++i){
    for(int j=0; j<_height;++j){
      for(int k=0; k<2; ++k){
        if(wall[i][j][k]==false) continue; //pass walls already been removed
        if(i==_width-1 && k==0) continue; //pass perimeters
        if(j==_height-1 && k==1) continue;

        int index = j*_width + i;
        int index2 = k==1 ? index + _width : index + 1;
        if(forest->find(index) == forest->find(index2))
          return false;

      }
    }
  }


  return true;
}

void SquareMaze::makeMaze(int width, int height){

  clear_wall();
  clear_forest();
  //removal_vec.clear();
  //map.clear();
  soln.clear();
  destination = 0; 
  _height = height;
  _width = width;

  int map_index = 0;

  wall = new bool**[width];
  visited = new bool*[width];
  dist = new int*[width];
  pred = new std::pair<int,int>*[width];
    
  for(int i=0; i<width; ++i){
    wall[i] = new bool*[height];
    visited[i] = new bool[height];
    dist[i] = new int[height];
    pred[i] = new std::pair<int,int>[height];
    for(int j=0; j<height;++j){
      wall[i][j] = new bool[2];
      visited[i][j] = false;
      dist[i][j] = 0;
      pred[i][j] = std::make_pair(-1,-1);
      for(int k=0; k<2; ++k){
        wall[i][j][k] = true; 
        //map[map_index] = std::tuple<int,int,int>(i,j,k);
        //removal_vec.push_back(map_index);
        //map_index++;
      }
    }
  }
  //std::cout << "LINE maze: " << __LINE__ << std::endl;

  //we fill in the forset row by row, from left to right
  //so (i,j) will be index j*width+i in the forset.vec
  //move this line to ctor
  forest = new DisjointSets();
  forest->addelements(width*height);
  //std::cout << "LINE maze: " << __LINE__ << std::endl;


  int total = width*height;

  //while(removal_vec.size()>0){

  int index = 0;
  while(forest->size(0)<total){

/*
    int ith = rand()%removal_vec.size();

    auto t = map[removal_vec[ith]];
    int i = std::get<0>(t);
    int j = std::get<1>(t);
    int k = std::get<2>(t);

    
    //std::vector<int>::iterator it = removal_vec.begin();
    //removal_vec.erase(it+ith);
*/

    int i = rand() % _width;
    int j = rand() % _height;
    int k = rand() % 2; 


    if(wallCanRemove(i,j,k)){ 
      setWall(i,j,k,0);    

      int index = j*_width+i;
      int index2 = k==0 ? index+1 : index + _width;
      forest->setunion(index,index2);

    }

/*
    if(i==0 && j==0){
      std::cout << "----------" << std::endl;
      std::cout << "forest(0) size: " << forest->size(0) << std::endl; 
      std::cout << "index: " << index << std::endl;
    }
    index++;
*/
  }//end of canRemove


}

bool SquareMaze::wallCanRemove(int i,int j,int k){

   
  //already been removed
  //if(wall[i][j][k]==false) return false;

  //cannot remoev edge
  if(i==(_width-1) && k==0) return false;;
  if(j==(_height-1) && k==1) return false; 

  int index = j*_width + i;
  int index2 = (k==1) ? index + _width : index + 1;

  //cannot create cycle
  if(forest->find(index) != forest->find(index2))
    return true;

  return false;
}


/*(
bool SquareMaze::canRemove(){

  //search for all remaining walls inside the pool
  //for(size_t ith=0; ith<removal_vec.size(); ++ith){
  //std::cout << "remaining: " << removal_vec.size() << std::endl;
  for(std::vector<int>::iterator it = removal_vec.begin(); it!=removal_vec.end();){ 
    auto t = map[*it];
    int i = std::get<0>(t);
    int j = std::get<1>(t);
    int k = std::get<2>(t);

    if(wallCanRemove(i,j,k))  
      return true;
    else
      it = removal_vec.erase(it); 

      ++it;
    else
    //for those walls that cannot be removed, remove them from the vector
      it = removal_vec.erase(it); 

  }

  return false; 
}
*/

bool SquareMaze::canTravel(int x, int y, int direction) const{

  if(x==0 && direction==2) return false; //can't go left 
  if(x==(_width-1) && direction==0) return false; //can't go right
  if(y==0 && direction==3) return false;  //can't go up
  if(y==(_height-1) && direction==1) return false; //can't go down 


  if(direction==0) 
    return !wall[x][y][0];
  if(direction==1) 
    return !wall[x][y][1];
  if(direction==2) 
    return !wall[x-1][y][0];
  if(direction==3) 
    return !wall[x][y-1][1];


  return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){

  //we will make sure not to call this function on perimeters of the grid
  wall[x][y][dir] = exists;


/*
  if(exists==1) return;
  int index = y*_width+x;
  int index2 = dir==0 ? index+1 : index + _width;
  forest->setunion(index,index2);
*/
}

std::vector<int> SquareMaze::solveMaze(){
  return solveMaze_(0,0);
}

std::vector<int> SquareMaze::solveMaze_(int x,int y){
  DFS(x,y);  
  //int index = 0; //find the largest dist on the bottom
  destination = 0;
  int distance = dist[0][_height-1];
  for(int i=0;i<_width;++i){ 
    if(dist[i][_height-1]>distance){
      distance = dist[i][_height-1];
      destination = i;
    }  
  }

  //std::vector<int> path;
  //std::cout << "index: " << index << std::endl;
  retrieve(soln,destination,_height-1);
  std::reverse(soln.begin(),soln.end());
  return soln; 
/*
  retrieve(path,index,_height-1);
  std::reverse(path.begin(),path.end());
  return path; 
*/
  //return std::vector<int>(); 
}

void SquareMaze::retrieve(std::vector<int>& path, int x, int y){

  if(x==0 && y==0) 
    return;

  std::pair<int,int> p = pred[x][y];
  int i = p.first;
  int j = p.second;

  if(i==x){
    if(y>j) path.push_back(1); //down  
    else path.push_back(3); //up
  }else if(j==y){
    if(x>i) path.push_back(0); //right
    else path.push_back(2);
  }else{
    std::cout << "error in path" << std::endl;
  }
  
  retrieve(path,i,j);
}

//std::vector<int> SquareMaze::solveMaze_(int x,int y){
void SquareMaze::DFS(int x,int y){

  //std::cout << "dfs working: " << std::endl;
  std::stack<std::pair<int,int>> stack;

  visited[x][y] = true;
  std::pair<int,int> p(x,y);
  stack.push(p);

  while(!stack.empty()){
    std::pair<int,int> top = stack.top();
    stack.pop();
    int i = top.first;
    int j = top.second;
    //std::cout << "now we are at: (" << i <<", " << j << ")" << std::endl;
/*
*/
    //check its 4 adjacent neighbours
    for(int dir=0; dir<4; ++dir){
      int newx = 0;
      int newy = 0;
      if(canTravel(i,j,dir)){
        if(dir==0){newx=i+1;newy=j;}
        if(dir==1){newx=i;  newy=j+1;}
        if(dir==2){newx=i-1;newy=j;}
        if(dir==3){newx=i;  newy=j-1;}
        if(visited[newx][newy]) continue;
        std::pair<int,int> p(newx,newy);
        stack.push(p);
        visited[newx][newy] = true;
        dist[newx][newy] = dist[i][j]+1;
        pred[newx][newy] = std::make_pair(i,j);
      }
    }//end of direction
  }//end of stack
}


PNG* SquareMaze::drawMaze() const{
  
  unsigned int png_width  = _width*10+1; 
  unsigned int png_height = _height*10+1; 
  PNG* png = new PNG(png_width,png_height);

  for(unsigned int x=0; x<png_width; ++x){
    if(1<=x && x<=9) continue;
    HSLAPixel& p = png->getPixel(x, 0);
    p.l = 0;
  }
  for(unsigned int y = 0; y < png_height; y++){
    HSLAPixel& p = png->getPixel(0,y);
    p.l = 0;
  }

  for(int i=0;i<_width;++i){
    for(int j=0;j<_height;++j){
      if(wall[i][j][0]){
        for(int k=0;k<=10;++k){
          HSLAPixel& p = png->getPixel((i+1)*10,j*10+k);
          p.l = 0;
        }//end of k  
      }//right wall
      if(wall[i][j][1]){
        for(int k=0;k<=10;++k){
          HSLAPixel& p = png->getPixel(i*10+k, (j+1)*10);
          p.l = 0;
        }//end of k
      }//down wall
    
    }
  }
  return png;
}

PNG* SquareMaze::drawMazeWithSolution(){

  PNG* png = drawMaze();
  if(soln.size()==0)
    solveMaze();

  //std::cout << "dest: " << destination << " _height-1: " << _height << std::endl;
  for(int k=1;k<=9;++k){
    HSLAPixel& p = png->getPixel(destination*10+k, (_height-1+1)*10);
    p.l = 1;
  }//end of k

  int x = 5;
  int y = 5;

  for(size_t i = 0; i < soln.size(); i++){
      if(soln[i] == 0) {
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = png->getPixel(x + k, y);
          p.h = 0;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
        x += 10;
      }
      else if(soln[i] == 1) {
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = png->getPixel(x, y + k);
          p.h = 0;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
        y += 10;
      }
      else if(soln[i] == 2) {
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = png->getPixel(x - k, y);
          p.h = 0;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
        x -= 10;
      }
      else if(soln[i] == 3) {
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = png->getPixel(x, y - k);
          p.h = 0;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
        y -= 10;
      }
  }



  return png;
}



void SquareMaze::debug(){

  std::cout << "print wall" << std::endl;
  for(int i=0;i<_width;++i){
    //for(int j=0;j<_height;++j){
      int j = _height-1;
      std::cout << "visited: " << visited[i][j] << " pred: (" << pred[i][j].first << 
     "," <<  pred[i][j].second << ")" << 
      " dist: " << dist[i][j] << std::endl;
/*
      for(int k=0; k<2; ++k){
        std::cout << wall[i][j][k] << std::endl;;
      } 
*/
   // }
  }

}

void SquareMaze::debug2(){
/*
  if(forest==nullptr)
    forest = new DisjointSets();
  forest->addelements(10);
  std::cout << forest->find(0) << std::endl;
  std::cout << forest->find(1) << std::endl;
*/

  int cnt=0;
  for(int i=0;i<_width;++i){
    for(int j=0;j<_height;++j){
      if(visited[i][j]) cnt++;
    }
  }

  std::cout << "# of visit: " << cnt << std::endl;
}   
