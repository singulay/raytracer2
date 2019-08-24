#include<vector>
#include<cmath>
#include "camera.h"
#include "util.h"

using namespace std;

Camera::Camera(float* pos,float* dir, float* size, float tilt, float dist, int* res){
    rays = 0;
    update(pos,dir,size,tilt,dist,res);
}

void Camera::update(float* pos,float* dir, float* size, float tilt, float dist, int* res){
    this->pos = pos;
    this->dir = dir;
    this->size = size;
    this->tilt = tilt;
    this->res = res;
    this->dist = dist;
    calculateRays();
}

int* Camera::getRes(){
    return res;
}

float* Camera::getPos(){
    return pos;
}

void Camera::calculateRays(){
    if(rays != 0){
        for(int i = 0;i < res[0];i++){
            for(int j = 0;j < res[1];j++){
                delete[] rays[i][j][0];
                delete[] rays[i][j][1];
            }
            delete[] rays[i];
        }
        delete[] rays;
    }
    rays = new float***[res[0]];
    for(int i = 0;i < res[0];i++){
        rays[i] = new float**[res[1]];
        for(int j = 0;j < res[1];j++){
            rays[i][j] = new float*[2];
            rays[i][j][0] = new float[3];
            rays[i][j][1] = new float[3];
        }
    }
    float** rotMat = util::getRot(dir);
    float** tiltMat = util::getTilt(tilt);
    float** r = util::allocateMatrix();
    util::multMat(rotMat,tiltMat,r);
    
    float* tempVec = new float[3];
    
    for(int i = 0;i < res[0];i++){
        for(int j = 0;j < res[1];j++){
            tempVec[0] = size[0]*((i-res[0]/2.)/res[0]);
            tempVec[1] = size[1]*((j-res[1]/2.)/res[1]);
            tempVec[2] = dist;
            rays[i][j][0][0] = pos[0];
            rays[i][j][0][1] = pos[1];
            rays[i][j][0][2] = pos[2];
            util::multMatVec(r,tempVec,rays[i][j][1]);
        }
    }
    util::freeMatrix(rotMat);
    util::freeMatrix(tiltMat);
    util::freeMatrix(r);
}

float**** Camera::getRays(){
    return rays;
}
