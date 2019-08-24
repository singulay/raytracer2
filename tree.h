#ifndef TREE

class Tree{
    public:
      Tree(float[2] location, vector<float> space, int depth); // takes list of points, depth
    private:
      float location;
      float median;
      Tree* left;
      Tree* right;

};

#define TREE
#endif
