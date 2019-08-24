#ifndef CAMERA

class Camera{
    public:
    Camera(float* pos,float* dir, float* size, float tilt, float dist, int* res);
    void update(float* pos,float* dir, float* size, float tilt, float dist, int* res);
    float**** getRays();
    float* getPos();
    int* getRes();
    private:
    float**** rays;
    float *pos,*dir,*size,tilt,dist;
    int *res;
    void calculateRays();
};

#define CAMERA
#endif
