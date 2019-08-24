#ifndef TRIANGLE //Sorgt dafür, dass die Datei nur einmal geladen wird
#include<vector>
#include "camera.h"

using namespace std;

class Triangle{
    public:
    Triangle(float** vs,float** ts,float** ns,char* name);
    bool findIntersection(float** ray,float* pI);
    float** vs;
    float getDistToCam();
    void calcDistToCam(Camera cam);
    private:
    float *q,*u,*v,*n;
    float uv,uu,vv,denominator;
    char* name;
    float distToCam;
};
#define TRIANGLE
#endif
