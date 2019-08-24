#ifndef ENTITY
#include<vector>
#include "triangle.h"
#include "camera.h"
#include "tree.h"

using namespace std;

class Entity{
    public:
    Entity(vector<Triangle>* t);
    vector<Triangle>* getTriangles();
    void sortWRTDistToCamera(Camera cam);
    bool findIntersection(float** ray,float* pI);
    private:
    vector<Triangle> ts;
    Tree* tree;
};
#define ENTITY
#endif
