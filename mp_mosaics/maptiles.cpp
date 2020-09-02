/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include "kdtree.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{


    /**
     * @todo Implement this function!
     */

  MosaicCanvas* newFile = new MosaicCanvas(theSource.getRows(),theSource.getColumns());

  //build the kd tree from vector
  std::map<Point<3>,TileImage*> map;
  std::vector<Point<3>> vec;
  for( auto& image : theTiles ){
    LUVAPixel pixel = image.getAverageColor();
    Point<3> point = convertToXYZ(pixel);
    vec.push_back(point);
    map[point] = &image;
  }

  KDTree<3> tree(vec);

  for(int irow=0;irow<theSource.getRows();++irow){
    for(int icol=0;icol<theSource.getColumns();++icol){
      LUVAPixel orig_pixel =  theSource.getRegionColor(irow,icol);
      Point<3> orig_point = convertToXYZ(orig_pixel); 
      Point<3> NNS = tree.findNearestNeighbor(orig_point);
      //TileImage NNS_image = *(map[NNS]);
      newFile->setTile(irow,icol,map[NNS]);
    }
  }

  return newFile; 
}

