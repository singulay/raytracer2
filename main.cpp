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
//#include <mpi.h>

using namespace std;

int main(int argc,char** argv){
    Scene s(1,argv+1);
    float pos[3];
    float dir[3];
    pos[0] = 0;
    pos[1] = 5;
    pos[2] = -2;
    dir[0] = 0;
    dir[1] = -1;
    dir[2] = +0.3;
    float size[2];
    size[0] = 3;
    size[1] = 3;
    int res[2];
    res[0] = 400;
    res[1] = 400;
    float tilt = -M_PI/2.;
    float dist = 1;
    Camera cam(pos,dir,size,tilt,dist,res);
    s.render(cam);
    return 0;
}
