#ifndef UTIL

#include<cmath>
#include <iostream>
#include <stdlib.h>
#include "triangle.h"

namespace util{

void printVector(float* f){
    std::cout << f[0] << " " << f[1] << " " << f[2] << std::endl;
}

float dot(float* a,float* b){
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

void cross(float* a,float* b,float* c){
    c[0] = a[1]*b[2] - a[2]*b[1];
    c[1] = a[2]*b[0] - a[0]*b[2];
    c[2] = a[0]*b[1] - a[1]*b[0];
}

void minus(float* a,float* b,float* c){
    c[0] = a[0]-b[0];
    c[1] = a[1]-b[1];
    c[2] = a[2]-b[2];
}

void add(float* a,float* b,float* c){
    c[0] = a[0]+b[0];
    c[1] = a[1]+b[1];
    c[2] = a[2]+b[2];
}

void mult(float* a,float lam,float* b){
    b[0] = lam*a[0];
    b[1] = lam*a[1];
    b[2] = lam*a[2];
}

float** allocateMatrix(){
    float** result = new float*[3];
    for(int i = 0;i < 3;i++){
        result[i] = new float[3];
    }
    return result;
}

void freeMatrix(float** mat){
    for(int i = 0;i < 3;i++){
        delete[] mat[i];
    }
}

float** getTilt(float angle){
    float** result = allocateMatrix();
    result[0][0] = cos(angle);
    result[0][1] = -sin(angle);
    result[0][2] = 0;
    result[1][0] = sin(angle);
    result[1][1] = cos(angle);
    result[1][2] = 0;
    result[2][0] = 0;
    result[2][1] = 0;
    result[2][2] = 1;
    return result;
}

float** getRot(float* dir){
    util::mult(dir,1./sqrt(util::dot(dir,dir)),dir); //normalize vector
    float** result = allocateMatrix();
    if((dir[0] == 1 || dir[0] == -1) && dir[1] == dir[2] && dir[1] == 0){ // cross product unuseful
        float m = sqrt(dir[1]*dir[1] + dir[2]*dir[2]);
        if(m == 0){
            m = 1;
        }
        float m2 = sqrt(dir[0]*dir[0]*dir[1]*dir[1] + pow(pow(dir[0],2) + pow(dir[2],2),2) + pow(dir[1],2)*pow(dir[2],2));
        if(m2 == 0){
            m2 = 1;
        }
        result[0][0] = dir[2]/m;
        result[0][1] = -dir[0]*dir[1]/2.;
        result[0][2] = dir[0];
        result[1][0] = 0;
        result[1][1] = (pow(dir[0],2) + pow(dir[2],2))/m;
        result[1][2] = dir[1];
        result[2][0] = -dir[0]/m;
        result[2][1] = -dir[1]*dir[2]/m2;
        result[2][2] = dir[2];
        
    }
    else{
        float m = sqrt(dir[1]*dir[1] + dir[2]*dir[2]);
        if(m == 0){
            m = 1;
        }
        float m2 = sqrt(dir[0]*dir[0]*dir[1]*dir[1] + pow(dir[0],2)*pow(dir[2],2) + pow(pow(dir[1],2) + pow(dir[2],2),2));
        if(m2 == 0){
            m2 = 1;
        }
        result[0][0] = pow(dir[1],2) + pow(dir[2],2)/m2;
        result[0][1] = 0;
        result[0][2] = dir[0];
        result[1][0] = -dir[1]*dir[0]/m2;
        result[1][1] = dir[2]/m2;
        result[1][2] = dir[1];
        result[2][0] = -dir[0]*dir[2]/m2;
        result[2][1] = -dir[1]/m;
        result[2][2] = dir[2];
    }
    return result;
    
}

void multMat(float** A, float** B,float** C){
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            C[i][j] = 0;
            for(int l = 0;l < 3;l++){
                C[i][j] += A[i][l]*B[l][j];
            }
        }
    }
}

void multMatVec(float** A, float* B,float* C){
    for(int i = 0;i < 3;i++){
        C[i] = 0;
        for(int j = 0;j < 3;j++){
            C[i] += A[i][j]*B[j];
        }
    }
}

unsigned int*** allocateRGBImage(int* size){
    unsigned int*** image = new unsigned int**[size[0]];
    for(int i = 0;i < size[0];i++){
        image[i] = new unsigned int*[size[1]];
        for(int j = 0;j < size[1];j++){
            image[i][j] = new unsigned int[3];
        }
    }
    return image;
}

void freeRGBImage(unsigned int*** image,int* size){
    for(int i = 0;i < size[0];i++){
        for(int j = 0;j < size[1];j++){
            delete[] image[i][j];
        }
        delete[] image[i];
    }
    delete[] image;
}

bool compareTriangle(Triangle t1,Triangle t2){
    return t1.getDistToCam() > t2.getDistToCam();
}

}

#define UTIL
#endif
