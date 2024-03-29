#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <cmath>
#include <functional>
#include "scene.cpp"
//#include "mainwindow.h"
//#include <QApplication>
//#include <mpi.h>

using namespace std;

void imageToFile(char* fname,unsigned int*** image,int* res){
    ofstream file;
    file.open(fname,ios::trunc);
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
}

bool getBoxIntersection(float** box, float** ray){
    float t[6];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 2; j++){
            t[2*i+j] = (box[j][i] - ray[0][i])*ray[2][i];
        }
    }
    float tmin = max(max(min(t[0], t[1]), min(t[2], t[3])), min(t[4], t[5]));
    float tmax = min(min(max(t[0], t[1]), max(t[2], t[3])), max(t[4], t[5]));
    if (tmax < 0) return false;
    if (tmin > tmax) return false;
    return true;
}

int main(int argc,char** argv){
    //  MPI_Init(NULL,NULL);
    
    int worldSize;
    //  MPI_Comm_size(MPI_COMM_WORLD,&worldSize);
    
    int worldRank;
    //  MPI_Comm_rank(MPI_COMM_WORLD,&worldRank);
    
    worldRank = 0;
    worldSize = 1;

    Scene s(argc-1,argv+1);
    float pos[3];
    float dir[3];
    /*pos[0] = 5;
    pos[1] = 5;
    pos[2] = 5;
    dir[0] = -1;
    dir[1] = -1;
    dir[2] = -1;
    float size[2];
    size[0] = 1;
    size[1] = 1;
    int res[2];
    res[0] = 1000;
    res[1] = 1000;
    float tilt = 0;//-M_PI/2.;
    float dist = 1;*/
    pos[0] = 278;
    pos[1] = 273;
    pos[2] = -800;
    dir[0] = 0;
    dir[1] = 0;
    dir[2] = 1;
    float size[2];
    size[0] = 0.025;
    size[1] = 0.025;
    int res[2];
    res[0] = 1000;
    res[1] = 1000;
    float tilt = -M_PI/2.;
    float dist = 0.035;
    Camera cam(pos,dir,size,tilt,dist,res);
    unsigned int*** image;
    //if(worldRank == 0){
    image = util::allocateRGBImage(res);
    //}
    //unsigned int*** image2;
    //MPI_Barrier(MPI_COMM_WORLD);
    //MPI_Scatter(image, 1, MPI_UINT16_T, image2 ,1, MPI_UINT16_T, 0, MPI_COMM_WORLD);
    //MPI_Barrier(MPI_COMM_WORLD);
    //cout << "wR " << worldRank << " " << image2 << endl;
    s.render(cam,image,worldRank,worldSize);
    char fname[300];
    sprintf(fname,"testMT%d.ppm",worldRank);
    imageToFile(fname,image,cam.getRes());
    //  MPI_Barrier(MPI_COMM_WORLD);
    
    //  MPI_Finalize();
    return 0;
}
