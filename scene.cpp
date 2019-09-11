#include<vector>
#include "util.h"
#include "camera.cpp"
#include "scene.h"
#include "parser.cpp"

//include <mpi.h>

Scene::Scene(int fc,char** fn){
    for(int i = 0;i < fc;i++){
        objs.push_back(parse(fn[i]));
    }
}

void Scene::render(Camera cam,unsigned int*** image, int wR,int wC){
    float**** rays = cam.getRays();
    int* res = cam.getRes();
    if(image == 0){
        image = util::allocateRGBImage(res);
    }
    
    int wT = int(sqrt(wC));
    while(wC%wT != 0){
        wT++;
    }
    int hT = wC/wT;
    cout << "wT: " << wT << " hT: " << hT << endl;
    int x = wR%wT;
    int y = int(wR/wT);
    
    vector<Triangle> ts;
    float dist = 0;
    //sortTriangles(cam);
    float* intersection = new float[3];
    for(int i = res[0]*(x/((float)wT));i < res[0]*((x+1)/((float)wT));i++){
        //cout << i << endl; 
        
        for(int j = res[1]*(y/((float)wT));j < res[1]*((y+1)/((float)hT));j++){
            float distSq = HUGE_VALF;
            for(int k = 0;k < objs.size();k++){
                bool found = objs[k].findIntersection(rays[i][j],intersection);
                if(found){
                    util::minus(intersection,rays[0][0][0],intersection);
                    float newDistSq = util::dot(intersection,intersection);
                    if(newDistSq < distSq){
                        distSq = newDistSq;
                    }
                }
                /*ts = *(objs[k].getTriangles());
                for(int l = 0;l < ts.size();l++){
                    bool found = ts[l].findIntersection(rays[i][j],intersection);
                    if(found){
                        util::minus(intersection,rays[0][0][0],intersection);
                        float newDist = sqrt(util::dot(intersection,intersection));
                        if(newDist < dist){
                            dist = newDist;
                        }
                        l = ts.size();
                    }
                }*/
            }
            //cout << "WELL" << endl;
            if(distSq == HUGE_VALF){
                image[i][j][0] = 0;
                image[i][j][1] = 0;
                image[i][j][2] = 255;
            }
            else{
                dist = sqrt(distSq);
                image[i][j][0] = 255 - int(255*dist/14.);
                image[i][j][1] = 255 - int(255*dist/14.);
                image[i][j][2] = 255 - int(255*dist/14.);
                //cout << dist << endl;
            }
        }
        //util::loadingBar(i,int(res[0]*(1./((float)wT))),'#','-',"Rendering: ",50);
        //cout << i-res[0]*(x/((float)wT)) << endl;
    }
    delete intersection; 
}

void Scene::sortTriangles(Camera cam){
    for(int k = 0;k < objs.size();k++){
        objs[k].sortWRTDistToCamera(cam);
    }
}
