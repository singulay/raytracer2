#include "tree.h"
#include "triangle.h"
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

Tree::Tree(vector<Triangle>* t){
    /*box = new float*[8];
    for(int i = 0;i < 8;i++){
        box[i] = new float[3];
    }
    calcBoundingBox();
    Tree(t,1);*/
};

Tree::Tree(vector<Triangle>* t,int depth){
    cout << "depth = " <<  depth << endl;
    cout << "T = " << t->size() << endl;
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
        tri = &t[0][0];
    }
    else if(t->size() > 1){
        sort(t->begin(),t->end(),[&](Triangle t1, Triangle t2) {
            float maxT1 = max(max(t1.vs[0][axis],t1.vs[1][axis]),t2.vs[2][axis]);
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
        if(leftList.size() > 0)
            left = new Tree(&leftList,depth+1);
        if(rightList.size() > 0)
            right = new Tree(&rightList,depth+1);
        //rightList.clear();
        //leftList.clear();
    }
    if(depth >= 1){
        //t->clear();
        //delete t;
    }
};

bool Tree::getIntersection(float** ray,float* pI){
    float t[6];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 2; j++){
            t[2*i+j] = (box[j][i] - ray[0][i])*ray[2][i];
        }
    }
    float tmin = max(max(min(t[0], t[1]), min(t[2], t[3])), min(t[4], t[5]));
    float tmax = min(min(max(t[0], t[1]), max(t[2], t[3])), max(t[4], t[5]));
    if (tmax < 0) return false;
    if (tmin > tmax) return false;
    //else
    bool leftTree = false;
    bool rightTree = false;
    if(left != 0)
        leftTree = left->getIntersection(ray,pI);
    if(right != 0)
        rightTree = right->getIntersection(ray,pI);
    if(left == 0 && right == 0){
        return this->tri->findIntersection(ray,pI);
    }
    return leftTree || rightTree;
}

void Tree::calcBoundingBox(vector<Triangle>* t){
    float minC[3];
    util::initTo(minC,+HUGE_VALF);
    float maxC[3];
    util::initTo(maxC,-HUGE_VALF);
    for(int i = 0;i < t->size();i++){
        for(int k = 0;k < 3;k++){
            minC[k] = min(minC[k],min(min(t[0][i].vs[0][k],t[0][i].vs[1][k]),t[0][i].vs[2][k]));
            maxC[k] = max(maxC[k],max(max(t[0][i].vs[0][k],t[0][i].vs[1][k]),t[0][i].vs[2][k]));
        }
    }
    for(int i = 0;i < 3;i++){
        box[0][i] = minC[i];
        box[1][i] = maxC[i];
    }
}

