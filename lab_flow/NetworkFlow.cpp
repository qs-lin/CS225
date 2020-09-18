/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  maxFlow_ = 0;
  std::vector<Vertex> vertices = startingGraph.getVertices();
  for(const auto& v : vertices){
    if(!flow_.vertexExists(v)){
      flow_.insertVertex(v);
      residual_.insertVertex(v);
    }
    for(const auto& w : g_.getAdjacent(v)){
      if(!flow_.vertexExists(w)){
        flow_.insertVertex(w);
        residual_.insertVertex(w);
      }
      if(g_.edgeExists(v,w)){
        //int weight = g_.getEdge(v,w).getWeight();
        int weight = g_.getEdgeWeight(v,w);
        flow_.insertEdge(v,w);
        residual_.insertEdge(v,w);
        residual_.insertEdge(w,v);
        flow_.setEdgeWeight(v,w,0);
        residual_.setEdgeWeight(v,w,weight);
        residual_.setEdgeWeight(w,v,0);
      }
    }
  }


  // YOUR CODE HERE
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

/*
  if (visited.count(source) != 0)
    return false;
*/
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {

  if(path.size()==0) return 0;
  int min = INT_MAX;
  for(size_t i=0;i<path.size()-1;++i){
    int weight = residual_.getEdgeWeight(path[i],path[i+1]);
    if(weight<min) min = weight;
  } 
  // YOUR CODE HERE
  return min;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE

  std::vector<Vertex> path;
  while(findAugmentingPath(source_,sink_,path)){
    int cap = pathCapacity(path);

    for(size_t i=0;i<path.size()-1;++i){
      Vertex start = path[i];
      Vertex end   = path[i+1];
      //in the correct order
      if(flow_.edgeExists(start,end)){
        flow_.setEdgeWeight(start,end,flow_.getEdgeWeight(start,end)+cap);
      }else{
        flow_.setEdgeWeight(end,start,flow_.getEdgeWeight(end,start)-cap);
      }
      residual_.setEdgeWeight(start,end,residual_.getEdgeWeight(start,end)-cap);
      residual_.setEdgeWeight(end,start,residual_.getEdgeWeight(end,start)+cap);
    }
  }

  maxFlow_ = 0;
  for(const auto& w:flow_.getAdjacent(source_)){
    if(flow_.edgeExists(source_,w))
      maxFlow_ += flow_.getEdgeWeight(source_,w);

  }



  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

void NetworkFlow::debug(){

  std::cout << "print residual" << std::endl;
  residual_.print();
  std::cout << "print flow" << std::endl;
  flow_.print();
}

bool NetworkFlow::findPath(Vertex source, Vertex sink, std::vector<Vertex> &path, std::unordered_map<Vertex,bool> &visited){

  visited[source] = true;

  //traversed to sink
  if(source == sink)
    return true;

  for(const auto& w : residual_.getAdjacent(source)){
    if(residual_.getEdgeWeight(source,w)<=0) continue;
    if(visited.find(w)!=visited.end()) continue;    
    //move this to the 1st line
    //visited[w] = true;
    path.push_back(w);
    if(!findPath(w,sink,path,visited)){ 
      path.pop_back();
      //note there is no need to change it back to false;
      //if you change this to false, it means that if you re-visit this point later in other paths
      //but you still cannot start from this point to sink. So remain visited and do not come back
    }else
      return true;
  }

return false;
}

bool NetworkFlow::findPath(Vertex source, Vertex sink, std::vector<Vertex> &path){
  path.clear();
  path.push_back(source);
  std::unordered_map<Vertex,bool> map; 
  return findPath(source,sink,path,map);

}
