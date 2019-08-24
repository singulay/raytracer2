#ifndef ENTITY
#include<vector>
#include "triangle.h"
#include "camera.h"

using namespace std;

class Entity{
    public:
    Entity(vector<Triangle>* t);
    vector<Triangle>* getTriangles();
    void sortWRTDistToCamera(Camera cam);
    private:
    vector<Triangle> ts;
};
#define ENTITY
#endif
