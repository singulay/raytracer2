#include "tree.h"
#include "triangle.h"
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

Tree::Tree(vector<Triangle>* t,int depth){
    int axis = depth%3;
    box = new float*[2];
    for(int i = 0;i < 2;i++){
        box[i] = new float[3];
    }
    calcBoundingBox(t);
    
    tri = 0;
    right = 0;
    left = 0;
    if(t->size() == 1){
        float** vsT = new float*[3];
        vsT[0] = new float[3];
        vsT[1] = new float[3];
        vsT[2] = new float[3];
        for(int i = 0;i < 3;i++){
            for(int j = 0;j < 3;j++){
                vsT[i][j] = t[0][0].vs[i][j];
            }
        }
        tri = new Triangle(vsT,vsT,vsT,"NOEN");
    }
    else if(t->size() > 1){
        sort(t->begin(),t->end(),[&](Triangle t1, Triangle t2) {
            float maxT1 = max(max(t1.vs[0][axis],t1.vs[1][axis]),t1.vs[2][axis]);
            float maxT2 = max(max(t2.vs[0][axis],t2.vs[1][axis]),t2.vs[2][axis]);
            return maxT1 > maxT2;
        });
        int leftLength = int(t->size()/2);
        vector<Triangle> leftList,rightList;
        for(int i = 0;i < leftLength;i++){
            leftList.push_back(t[0][i]);
        }
        for(int i = leftLength;i < t->size();i++){
            rightList.push_back(t[0][i]);
        }
        if(leftList.size() > 0){
            left = new Tree(&leftList,depth+1);
        }
        if(rightList.size() > 0){
            right = new Tree(&rightList,depth+1);
        }
    }
};

bool Tree::getIntersection(float** ray,float* pI,float* dist,Triangle** returnTri){
    //check for AABB intersection
    float t0 = (box[0][0] - ray[0][0])*ray[2][0];
    float t1 = (box[1][0] - ray[0][0])*ray[2][0];
    float t2 = (box[0][1] - ray[0][1])*ray[2][1];
    float t3 = (box[1][1] - ray[0][1])*ray[2][1];
    float t4 = (box[0][2] - ray[0][2])*ray[2][2];
    float t5 = (box[1][2] - ray[0][2])*ray[2][2];
    float tmin = t0;
    float tmax = t1;
    if(t0 > t1){
        tmin = t1;
        tmax = t0;
    }
    if(t2 > t3){
        if(t2 < tmax){
            tmax = t2;
        }
        if(t3 > tmin){
            tmin = t3;
        }
    }
    else{
        if(t3 < tmax){
            tmax = t3;
        }
        if(t2 > tmin){
            tmin = t2;
        }
    }
    if(t4 > t5){
        if(t4 < tmax){
            tmax = t4;
        }
        if(t5 > tmin){
            tmin = t5;
        }
    }
    else{
        if(t5 < tmax){
            tmax = t5;
        }
        if(t4 > tmin){
            tmin = t4;
        }
    }
    if (tmax < 0) return false;
    if (tmin > tmax) return false;
    bool createdDist = false;
    if(dist == 0){
        dist = new float[1];
        *dist = HUGE_VALF;
        createdDist = true;
    }
    bool leftTree = false;
    bool rightTree = false;
    if(left != 0)
        leftTree = left->getIntersection(ray,pI,dist,returnTri);
    if(right != 0)
        rightTree = right->getIntersection(ray,pI,dist,returnTri);
    if(left == 0 && right == 0){ // is leaf
        float tempPI[3];
        float distVector[3];
        bool intersects = tri->findIntersection(ray,tempPI);
        if(intersects){
            util::minus(ray[0],tempPI,distVector);
            float newDist = util::dot(distVector,distVector);
            if(newDist < *dist){
                dist[0] = newDist;
                pI[0] = tempPI[0];
                pI[1] = tempPI[1];
                pI[2] = tempPI[2];
                returnTri[0] = tri;
            }
        }
        return intersects;
    }
    if(createdDist){
        delete[] dist;
    }
    return leftTree || rightTree;
}

void Tree::calcBoundingBox(vector<Triangle>* t){
    util::initTo(box[0],+HUGE_VALF);
    util::initTo(box[1],-HUGE_VALF);
    for(int i = 0;i < t->size();i++){
        for(int k = 0;k < 3;k++){
            box[0][k] = min(box[0][k],min(min(t[0][i].vs[0][k],t[0][i].vs[1][k]),t[0][i].vs[2][k]));
            box[1][k] = max(box[1][k],max(max(t[0][i].vs[0][k],t[0][i].vs[1][k]),t[0][i].vs[2][k]));
        }
    }
}

