#ifndef ENTITY
#include<vector>
#include "triangle.h"

using namespace std;

class Entity{
    public:
    Entity(vector<Triangle>* t);
    vector<Triangle>* getTriangles();
    private:
    vector<Triangle> ts;
};
#define ENTITY
#endif
