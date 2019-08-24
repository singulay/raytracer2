#ifndef PARSER

#include<vector>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include<string>
#include<iostream>
#include<cstdlib>
#include "triangle.cpp"
#include "entity.cpp"

using namespace std;

void getTokens(string line,vector<string>* tokens,string delimiter){
    int pos = 0;
    string token;
    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);
        if(token.length() != 0){
            tokens->push_back(token);
        }
        line.erase(0, pos + delimiter.length());
    }
    tokens->push_back(line);
}

Entity parse(char* fname){
    cout << "Loading: " << fname << endl;
    vector<float*> vs;
    vector<float*> texes;
    vector<float*> ns;
    vector<Triangle> ts;

    ifstream file(fname);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<string> tokens;
            getTokens(line,&tokens," ");
            if(tokens.size() >= 1){
                if(tokens[0].compare("v") == 0){
                    float* vec = new float[3];
                    vec[0] = atof(tokens[1].c_str());
                    vec[1] = atof(tokens[2].c_str());
                    vec[2] = atof(tokens[3].c_str());
                    vs.push_back(vec);
                }
                if(tokens[0].compare("f") == 0){
                    float* vsT[3];
                    float* texesT[3];
                    float* nsT[3];
                    for(int j = 0;j < 3;j++){
                        vector<string> subtokens;
                        getTokens(tokens[j+1],&subtokens,"/");
                        vsT[j] = vs[atoi(subtokens[0].c_str())-1];
                    }
                    Triangle newT = Triangle(vsT,texesT,nsT,"None");
                    ts.push_back(newT);
                    
                }
            }
            
        }
        file.close();
    }
    cout << "Loaded " << ts.size() << " faces (vertices = " << vs.size() << ")" << endl;
    
    Entity e(&ts);
    return e;
}

#define PARSER
#endif
