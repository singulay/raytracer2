#include "tree.h"
#include "triangle.h"

using namespace std;

Tree::Tree(float** location, vector<float**> space, int depth){ //?
  int axis = depth%3;

  float** location = location;
  // spaceL = space with items LEFT of median
  // spaceR = " " " RIGHT " "
  if (spaceL.size() > 0){
    float** median; // depending on axis
    Tree* left(*median, spaceL, depth+1);
  }
  if (spaceR.size() > 0) Tree* right(*median, spaceR, depth+1);
  for (int i = 0; i <= space.size(); i++){

  }


}

void Tree:addtoTree(){
  ;
}
