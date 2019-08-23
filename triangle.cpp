#include<vector>
#include "triangle.h"
#include "util.h"

using namespace std;

Triangle::Triangle(float** vs,float** ts,float** ns,char* name){
    this->name = name;
    q = vs[0];
    u = new float[3];
    v = new float[3];
    util::minus(vs[1],q,u);
    util::minus(vs[2],q,v);
    n = new float[3];
    util::cross(u,v,n);
    uv = util::dot(u,v);
    uu = util::dot(u,u);
    vv = util::dot(v,v);
    denominator = uv*uv - uu*vv;
    
}
bool Triangle::findIntersection(float** ray,float* pI){
    //returns 0 if no intersection is found
    float denom = util::dot(n,ray[1]);
    if(denom == 0){
        return false;
    }
    float v0p0[3];
    util::minus(q,ray[0],v0p0);
    float rI = util::dot(n,v0p0)/denom;
    if(rI < 0){
        return false;
    }
    float w[3];
    util::mult(ray[1],rI,pI);
    util::add(pI,ray[0],pI);
    util::minus(pI,q,w);
    float wv = util::dot(w,v);
    float wu = util::dot(w,u);
    float sI = (wv*uv - vv*wu)/denominator;
    float tI = (wu*uv - uu*wv)/denominator;
    if(sI < 0 || tI < 0 || sI+tI > 1){
        return false;
    }
    return true;
}

/*int main(int a, char** b){
    float pos[3];
    float dir[3];
    pos[0] = 1;
    pos[1] = 1;
    pos[2] = 0;
    dir[0] = 1;
    dir[1] = 1;
    dir[2] = 1;
    float pos2[3];
    pos2[0] = 1;
    pos2[1] = -1;
    pos2[2] = 0;
    float** x = new float*[3];
    x[0] = pos;
    x[1] = dir;
    x[2] = pos2;
    Triangle t(x,x,x,"LOL");
    float** rays = new float*[2];
    rays[0] = new float[3];
    rays[0][0] = 5;
    rays[0][1] = 5;
    rays[0][2] = 5;
    rays[1] = new float[3];
    rays[1][0] = -1;
    rays[1][1] = -1;
    rays[1][2] = -1;
    std::cout << t.findIntersection(rays) << std::endl;
    if(t.findIntersection(rays) != 0)
        util::printVector(t.findIntersection(rays));
    return 0;
}*/
