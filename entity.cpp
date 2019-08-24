#include<vector>
#include<algorithm>
#include "entity.h"
#include "util.h"
#include "camera.h"
#include "triangle.h"
#include "tree.cpp"

using namespace std;

Entity::Entity(vector<Triangle>* t){
    this->ts = *t;
    this->tree = new Tree(t,0);
}

vector<Triangle>* Entity::getTriangles(){
   return &ts;
}

bool Entity::findIntersection(float** ray,float* pI){
    return tree->getIntersection(ray,pI);
}

void Entity::sortWRTDistToCamera(Camera cam){
    float* camPos = cam.getPos();
    for(int k = 0;k < ts.size();k++){
        ts[k].calcDistToCam(cam);
    }
    sort(ts.begin(),ts.end(),util::compareTriangle);
}
