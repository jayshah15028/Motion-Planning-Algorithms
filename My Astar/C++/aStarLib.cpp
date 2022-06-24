#include<iostream>
#include<eigen3/Eigen/Dense>
#include<tuple>
#include"aStarLib.h"

using namespace std;
using namespace Eigen;

aStarTools::aStarTools(MatrixXf& map): map(map){}

float aStarTools::calculateDistance(Vector2f point1, Vector2f point2){
    float distance;
    distance = sqrt(pow((point1(0)-point2(0)),2) + pow((point1(1)-point2(1)),2));
    return distance;
}

MatrixXf aStarTools::neighbors(Vector2f point){
    MatrixXf successors(1,2);
    int nRows = 0; int nCols = 2;
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if (!(i==j && i==0)){
                if (((point(0)+i)<(map.rows())) && ((point(0)+i)>=0) && ((point(1)+j)<(map.cols())) && ((point(1)+j)>=0)){
                    if (map(point(0)+i,point(1)+j)!=0){
                        nRows+=1;
                        successors.conservativeResize(nRows,nCols);
                        successors(successors.rows()-1,0) = point(0)+i;
                        successors(successors.rows()-1,1) = point(1)+j;
                    }
                }
            }
        }
    }
    return successors;
}

MatrixXf aStarTools::successorDistances(Vector2f point,MatrixXf neighbors,float pathDistance){
    MatrixXf neighborDistances(neighbors.rows(),7);
    for(int i=0;i<neighbors.rows();i++){
        neighborDistances.row(i)(0) = neighbors.row(i)(0);
        neighborDistances.row(i)(1) = neighbors.row(i)(1);
        neighborDistances.row(i)(2) = point(0);
        neighborDistances.row(i)(3) = point(1);
        Vector2f point2 = neighbors.row(i);
        neighborDistances.row(i)(4) = pathDistance + calculateDistance(point,point2);
        neighborDistances.row(i)(5) = calculateDistance(point2,goal);
        neighborDistances.row(i)(6) = neighborDistances.row(i)(4) + neighborDistances.row(i)(5);
    }
    return neighborDistances;
}

tuple<Vector2f,float> aStarTools::minimumDistance(Vector2f point,float pathDistance,MatrixXf neighbors,MatrixXf visited){

    Vector2f node; float nodeDistance;
    int nNeighbors = neighbors.rows();
    float minDistance = numeric_limits<float>::max();
    int index = 0;
    VectorXf distances(nNeighbors);
    bool flag = false;
    for(int i=0; i<nNeighbors;i++){
        if ((map(neighbors.row(i)(0),neighbors.row(i)(1))==3) || (map(neighbors.row(i)(0),neighbors.row(i)(1))==1)){
            Vector2f point2 = neighbors.row(i);
            distances(i) = pathDistance + calculateDistance(point,point2) + calculateDistance(point2,goal);
            if (distances(i)<minDistance){
                index = i;
                minDistance = distances(i);
            }
        }
        if (map(neighbors.row(i)(0),neighbors.row(i)(1))==2){
            Vector2f point2 = neighbors.row(i);
            distances(i) = pathDistance + calculateDistance(point,point2) + calculateDistance(point2,goal);
            if (distances(i)<minDistance){
                index = i;
                minDistance = distances(i);
            }
            for (int j=0;j<visited.rows();j++){
                if (neighbors.row(0)==visited.block(i,0,1,2)){
                    if (pathDistance+calculateDistance(point,point2) < visited.row(i)(4)){
                        visited.row(i)(4) = pathDistance + calculateDistance(point,point2);
                    }
                }
            }
        }
    }
    Vector2f nodePoint = neighbors.row(index);
    node = nodePoint;
    nodeDistance = calculateDistance(point,nodePoint);
    
    return make_tuple(node,nodeDistance);
}