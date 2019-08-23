#ifndef TRIANGLE //Sorgt dafür, dass die Datei nur einmal geladen wird
#include<vector>

using namespace std;

class Triangle{
    public:
    Triangle(float** vs,float** ts,float** ns,char* name);
    bool findIntersection(float** ray,float* pI);
    private:
    float *q,*u,*v,*n;
    float uv,uu,vv,denominator;
    char* name;
};
#define TRIANGLE
#endif
