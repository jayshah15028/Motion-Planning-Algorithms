#ifndef ASTARLIB
#define ASTARLIB

#include <eigen3/Eigen/Dense>
#include <tuple>
using namespace std;
using namespace Eigen;

class aStarTools{
public:
    MatrixXf& map;
    Vector2f start;
    Vector2f goal;
    float calculateDistance(Vector2f point1, Vector2f point2);
    MatrixXf neighbors(Vector2f point);
    MatrixXf successorDistances(Vector2f point,MatrixXf neighbors,float pathDistance);
    tuple<Vector2f,float> minimumDistance(Vector2f point,float pathDistance,MatrixXf neighbors,MatrixXf visited);
    aStarTools(MatrixXf& map); //constructor

};

#endif