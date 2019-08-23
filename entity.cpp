#include<vector>
#include "entity.h"

Entity::Entity(vector<Triangle>* t){
    this->ts = *t;
}

vector<Triangle>* Entity::getTriangles(){
   return &ts;
}
