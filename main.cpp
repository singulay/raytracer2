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
#include <mpi.h>

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

int main(int argc,char** argv){
    MPI_Init(NULL,NULL);
    
    int worldSize;
    MPI_Comm_size(MPI_COMM_WORLD,&worldSize);
    
    int worldRank;
    MPI_Comm_rank(MPI_COMM_WORLD,&worldRank);

    Scene s(1,argv+1);
    float pos[3];
    float dir[3];
    pos[0] = 50;
    pos[1] = 50;
    pos[2] = 50;
    dir[0] = -1;
    dir[1] = -1;
    dir[2] = -1;
    float size[2];
    size[0] = 3;
    size[1] = 3;
    int res[2];
    res[0] = 1000;
    res[1] = 1000;
    float tilt = 0;//-M_PI/2.;
    float dist = 1;
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
    MPI_Barrier(MPI_COMM_WORLD);
    
    MPI_Finalize();
    return 0;
}
