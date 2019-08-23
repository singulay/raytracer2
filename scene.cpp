#include<vector>
#include "util.h"
#include "camera.cpp"
#include "scene.h"
#include "parser.cpp"

//#include <mpi.h>

Scene::Scene(int fc,char** fn){
    for(int i = 0;i < fc;i++){
        objs.push_back(parse(fn[i]));
    }
}

void Scene::makePhotonMap(Lightsource light){ // create illumination model of scene
    float**** rays = light.getRays();
    // do fancy arithmetics
}

bool Scene::inshadow(float*** point, Lightsource light){

  //more fancy arithmetics
}
void Scene::render(Camera cam){
    /*MPI_Init(NULL,NULL);

    int worldSize;
    MPI_Comm_size(MPI_COMM_WORLD,&worldSize);

    int worldRank;
    MPI_Comm_rank(MPI_COMM_WORLD,&worldRank);*/

    float**** rays = cam.getRays();
    int* res = cam.getRes();
    unsigned int*** image = util::allocateRGBImage(res);

    cout << "Camera is looking from:";
    util::printVector(rays[int(res[0]/2.)][int(res[1]/2.)][0]);

    cout << "Center is looking at: ";
    util::printVector(rays[int(res[0]/2.)][int(res[1]/2.)][1]);


    vector<Triangle> ts;
    float* intersection = new float[3];
    int _p = 0;
    for(int i = 0;i < res[0];i++){ // loop over image;
        for(int j = 0;j < res[1];j++){
            float dist = HUGE_VALF;
            for(int k = 0;k < objs.size();k++){
                ts = *(objs[k].getTriangles());
                for(int l = 0;l < ts.size();l++){
                    bool found = ts[l].findIntersection(rays[i][j],intersection);
                    if(found != 0){
                        util::minus(intersection,rays[0][0][0],intersection);
                        float newDist = sqrt(util::dot(intersection,intersection));
                        if(newDist < dist){
                            dist = newDist;
                        }
                    }
                }
            }
            //cout << "WELL" << endl;
            if(dist == HUGE_VALF){
                image[i][j][0] = 0;
                image[i][j][1] = 0;
                image[i][j][2] = 255;
            }
            else{
                image[i][j][0] = 255 - int(255*dist/14.);
                image[i][j][1] = 255 - int(255*dist/14.);
                image[i][j][2] = 255 - int(255*dist/14.);
                //cout << dist << endl;
            }
            _p += 1;
        }
        //cout << i << endl;
        util::loadingBar(_p, res[0]*res[1]);
    }
    cout << endl;
    ofstream file;
    file.open("test.ppm",ios::trunc);
    file << "P3 " << res[0] << " " << res[1] << " 255 " << endl;
    for(int i = 0;i < res[0];i++){
        for(int j = 0;j < res[1];j++){
            file << image[i][j][0] << " " << image[i][j][1] << " " << image[i][j][2];
            if(j != res[1]-1)
                file << " ";
        }
        file << endl;
    }
    //file << << endl;
    file.flush();
    file.close();
    util::freeRGBImage(image,res);
    delete intersection;


}
