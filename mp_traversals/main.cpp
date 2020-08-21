#include <map>
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */


  PNG png;
  png.readFromFile("i.png");

  FloodFilledImage ffi(png);
  Point p1(png.width()/2,png.height()/2);
  DFS dfs(png,p1,0.1);
  HSLAPixel color(0,0,0,1.);
  SolidColorPicker black(color);
  ffi.addFloodFill(dfs,black);
  Animation ani = ffi.animate(1000);



/*
  PNG png;
  png.readFromFile("i.png");

  FloodFilledImage ffi(png);
  Point p1(png.width()/2,png.height()/2);
  DFS dfs(png,p1,0.1);
  HSLAPixel color(0,0,0,1.);
  SolidColorPicker black(color); 
  ffi.addFloodFill(dfs,black);
  ffi.writeToFile();
*/




/*
  std::map<Point,int> map;
  Point p1(0,0);
  Point p2(10,0);

  map[p1] = 3;
  std::cout << map[p1] << std::endl;
  auto search = map.find(p2);
  if(search!=map.end())
    std::cout << "found" << std::endl; 

*/

/*
  std::cout << " DFS begin ------ " << std::endl;

  PNG png;
  Point p3(0,0);
  Point p4(291,43);
  png.readFromFile("myFloodFill.png");
  DFS dfs(png,p3,0.1);
  dfs.test();
  BFS bfs(png,p3,0.1);

  int index=0;

  for(ImageTraversal::Iterator it=dfs.begin(); it!=dfs.end(); ++it){
    index++;
  }
  std::cout << "number of traversals DFS: " << index << std::endl;

  std::cout << " BFS begin ------ " << std::endl;
  index = 0;


  for(ImageTraversal::Iterator it=bfs.begin(); it!=bfs.end() ; ++it){
    index++;
  }


  std::cout << "number of traversals BFS: " << index << std::endl;
  //std::cout << "total pixels: " << png.width() * png.height() << std::endl;
*/

  
 
/*
  int** arr;

  arr = new int*[10];
  for(int i=0; i<10; i++)
    arr[i] = new int[5];

  arr[9][3] = 1;
 std::cout << arr[9][3] << std::endl; 
 std::cout << arr[1][3] << std::endl; 
*/
//  std::cout << "line:  " << __LINE__ << std::endl;
  return 0;
}
