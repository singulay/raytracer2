#ifndef TRIANGLE //Sorgt dafür, dass die Datei nur einmal geladen wird
#include<vector>
#include "camera.h"
#include<cstring>

using namespace std;

class Triangle{
    public:
    Triangle(float** vs,float** ts,float** ns,char* name);
    bool findIntersection(float** ray,float* pI);
    float vs[3][3];
    float getDistToCam();
    void calcDistToCam(Camera cam);
    string print();
    //float *q,*u,*v,*n;
    float q[3],v[3],u[3],n[3];
    float uv,uu,vv,denominator;
    char* name;
    float distToCam;
    private:
};
#define TRIANGLE
#endif
