#pragma once
#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<map>
#include<unordered_map>

typedef  unordered_map <int,int> mapTypeLayer;
typedef  unordered_map<int,double> mapTypeIntDouble;

struct EdepData
{
    mapTypeIntDouble cellLayers;
    mapTypeIntDouble platesGroup;
    ThreeVector posVec;
    ThreeVector momentumVec;
    EdepData(){};
    EdepData(ThreeVector pv, ThreeVector mv, mapTypeIntDouble cellvec, mapTypeIntDouble platevec)
    {
        posVec=pv;
        momentumVec=mv;
        cellLayers=cellvec;
        platesGroup=platevec;
    };
};


typedef  map <int,EdepData> mapTypeSpec;

class ProcessFile
{
private:
    mapTypeLayer cellLayersArr;
    mapTypeSpec specArr;
public:
    ProcessFile(){};
    void sortLayers(vector<ThreeVector> &);
    void rootProcess(string fileName, mapTypeLayer &platesGroupArr);

};
