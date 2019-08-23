#ifndef SCENE

#include<vector>
#include "entity.h"
#include "camera.h"

class Scene{
    public:
    Scene(int fc,char** fn);
    void render(Camera cam);
    void makePhotonMap(Lightsource light);
    bool inshadow(float*** point, Lightsource light);
    private:
    vector<Entity> objs;
};
#define SCENE
#endif
