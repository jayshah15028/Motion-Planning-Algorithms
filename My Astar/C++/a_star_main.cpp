#include <iostream>
#include <eigen3/Eigen/Dense>
#include <cstdlib>
#include <random>
#include <tuple>
#include "aStarLib.h"

using namespace std;
using namespace Eigen;

int main(){
    int xRange = 20;  // define x range of the grid
    int yRange = 10;  // define y range of the grid
    MatrixXf map(xRange,yRange);  // initialize map
    // default all points on the grid to 1
    for(int i=0;i<map.rows();i++){
        for(int j=0;j<map.cols();j++){
            map(i,j)=1;
        }
    }
    aStarTools tools(map);
    random_device rd;   //random number generator seed from hardware
    mt19937 gen(time(0)); 
    uniform_int_distribution<> randGenerator(0,(xRange*yRange/2));
    unsigned long nObstacles = randGenerator(gen); // randomly generate number of obstacles 
    uniform_int_distribution<> xRandGenerator(0,xRange-1);
    uniform_int_distribution<> yRandGenerator(0,yRange-1);
    for(unsigned long i=0;i<nObstacles;i++){
        int xIndex = rand()%xRange;
        int yIndex = rand()%yRange;
        map(xIndex,yIndex) = 0;
    }
    int *xIndex = new int;  //allocating memory for temporary variables
    int *yIndex = new int;  //allocating memory for temporary variables
    // define start position
    *xIndex = rand()%xRange;
    *yIndex = rand()%yRange;
    map(*xIndex,*yIndex) = 4;
    Vector2f start(*xIndex,*yIndex);
    tools.start = start;  
    // define goal position
    *xIndex = rand()%xRange;
    *yIndex = rand()%yRange;
    map(*xIndex,*yIndex) = 3;
    Vector2f goal(*xIndex,*yIndex);
    tools.goal = goal; 
    delete xIndex,yIndex;   // deleting temporary variables to save memory
    Vector2f current = start;
    float pathDistance = tools.calculateDistance(start,current);
    MatrixXf path(current.transpose());
    
    MatrixXf neighbors = tools.neighbors(current);
    MatrixXf visited = tools.successorDistances(current,neighbors,pathDistance);
    Vector2f node; float nodeDistance;
    tie(node,nodeDistance) = tools.minimumDistance(current,pathDistance,neighbors,visited);

    pathDistance = pathDistance + nodeDistance;
    path.conservativeResize(path.rows()+1,path.cols());
    path(path.rows()-1,0) = node(0); path(path.rows()-1,1) = node(1);

    MatrixXf visitedTemp;
    current = node;
    
    while(map(current(0),current(1))!=3){
        neighbors = tools.neighbors(current);
        visitedTemp = tools.successorDistances(current,neighbors,pathDistance);
        long nRows = visited.rows() + visitedTemp.rows(); int nCols = visited.cols();
        visited.conservativeResize(nRows,nCols);
        visited.block(visited.rows()-visitedTemp.rows(),0,visitedTemp.rows(),nCols) = visitedTemp;
        tie(node,nodeDistance) = tools.minimumDistance(current,pathDistance,neighbors,visited);
        pathDistance = pathDistance + nodeDistance;
        path.conservativeResize(path.rows()+1,path.cols());
        path(path.rows()-1,0) = node(0); path(path.rows()-1,1) = node(1);
        current = node;        
    }
    cout << "path: " << endl;
    cout << path << endl;
    cout << map << endl;
    return 0;
}