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
    /*float tempPI[3];
    float distVector[3];
    float dist = HUGE_VALF;
    for(int i = 0;i < ts.size();i++){
        cout << ts[i].print() << " aaand : " << ts[i].findIntersection(ray,tempPI) << endl;
        bool intersects = ts[i].findIntersection(ray,tempPI);
        if(intersects){
            util::minus(ray[0],tempPI,distVector);
            float newDist = util::dot(distVector,distVector);
            if(newDist < dist){
                dist = newDist;//dist[0] = 10;//
                pI[0] = tempPI[0];//ray[0][0]+10;//tempPI[0];
                pI[1] = tempPI[1];//ray[0][1];//
                pI[2] = tempPI[2];//ray[0][2];//tempPI[2];
            }
        }
    }
    return dist != HUGE_VALF;*/
    return tree->getIntersection(ray,pI,0);
}


void Entity::sortWRTDistToCamera(Camera cam){
    float* camPos = cam.getPos();
    for(int k = 0;k < ts.size();k++){
        ts[k].calcDistToCam(cam);
    }
    sort(ts.begin(),ts.end(),util::compareTriangle);
}
