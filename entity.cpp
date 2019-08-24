#include<vector>
#include<algorithm>
#include "entity.h"
#include "util.h"
#include "camera.h"

using namespace std;

Entity::Entity(vector<Triangle>* t){
    this->ts = *t;
}

vector<Triangle>* Entity::getTriangles(){
   return &ts;
}

void Entity::sortWRTDistToCamera(Camera cam){
    float* camPos = cam.getPos();
    for(int k = 0;k < ts.size();k++){
        ts[k].calcDistToCam(cam);
    }
    sort(ts.begin(),ts.end(),util::compareTriangle);
}
