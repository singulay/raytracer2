#ifndef SCENE

#include<vector>
#include "entity.h"
#include "camera.h"

class Scene{
    public:
    Scene(int fc,char** fn);
    void render(Camera cam,unsigned int*** image,int wR,int wC);
    void sortTriangles(Camera cam);
    private:
    vector<Entity> objs;
};
#define SCENE
#endif
