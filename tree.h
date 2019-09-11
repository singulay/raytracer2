#ifndef TREE

#include<vector>
#include "triangle.h"

class Tree{
    public:
        Tree(vector<Triangle>* t,int depth);
        float** box;
        Tree *left,*right;
        Triangle* tri;
        bool getIntersection(float** ray,float* pI,float* dist,Triangle** returnTri);
    private:
        void calcBoundingBox(vector<Triangle>* t);
        
};

#define TREE
#endif
