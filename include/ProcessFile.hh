#pragma once
#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<map>
#include<unordered_map>

typedef  unordered_map <int,int> mapTypeLayer;
typedef  map<int,double> mapTypeIntDouble;

struct EdepData
{
    mapTypeIntDouble cellLayersEdep;
    mapTypeIntDouble platesEdep;
    ThreeVector posVec;
    ThreeVector momentumVec;
    EdepData(){};
    EdepData(ThreeVector pv, ThreeVector mv, mapTypeIntDouble cellEdep, mapTypeIntDouble plateEdep)
    {
        posVec=pv;
        momentumVec=mv;
        cellLayersEdep=cellEdep;
        platesEdep=plateEdep;
    };
};


typedef  map <int,EdepData> mapTypeSpec;

class ProcessFile
{
private:
    mapTypeLayer cellLayersEdep;
    mapTypeLayer platesEdep;

    mapTypeSpec specArr;
    vector<ThreeVector> posCells;
    vector<ThreeVector> posPlates;

public:
    ProcessFile(){};
    void sortLayersPos();

    void rootProcess(string filePos, string fileSpec);

};
