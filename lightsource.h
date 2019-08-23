#ifndef LIGHT

class Lightsource{
    public:
    Lightsource(float* pos,float* dir, float* size, float* angle, int* res);
    void update(float* pos,float* dir, float* size, float* angle, int* res);
    float**** getRays();
    int* getRes();
    private:
    float**** rays;
    float *pos,*dir,*size,*angle;
    int *res;
    void calculateRays();
};

#define LIGHT
#endif
