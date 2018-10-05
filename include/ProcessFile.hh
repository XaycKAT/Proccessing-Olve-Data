#pragma once
#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<map>
#include<unordered_map>


struct EdepData
{
    int layerNum;
    double edepLayer;
    EdepData(int num, double en)
    {
        layerNum=num;
        edepLayer=en;
    };
};

typedef  unordered_map <int,int> mapTypeLayer;
typedef  unordered_map <int,vector<EdepData>> mapTypeSpec;

class ProcessFile
{
private:
    mapTypeLayer layersArr;
    mapTypeSpec specArr;
public:
    ProcessFile(){};
    void sortLayers(vector<ThreeVector> &);
    void sortEdep();
    void rootProcess();

};
