#pragma once
#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<map>
#include<unordered_map>
#include<tuple>

typedef  unordered_map <int,int> mapTypeLayer;
typedef  map<int,double> mapTypeIntDouble;
typedef  map<int,pair<double,ThreeVector>> mapIntPairDoubleVec;
struct EdepData
{
    mapTypeIntDouble cellLayersEdep;
    mapIntPairDoubleVec platesEdep;
    ThreeVector posVec;
    ThreeVector momentumVec;
    ThreeVector posEndVec;
    EdepData(){};
    EdepData(ThreeVector pv, ThreeVector mv,ThreeVector pev, mapTypeIntDouble cellEdep, mapIntPairDoubleVec plateEdep)
    {
        posVec=pv;
        momentumVec=mv;
        cellLayersEdep=cellEdep;
        platesEdep=plateEdep;
        posEndVec=pev;
    };
};


typedef  map <int,EdepData> mapTypeSpec;

class ProcessFile
{
private:
    mapTypeLayer cellLayersNum;
    mapTypeSpec specArr;
    double thresholdValuePlas;
    double thresholdValueSilic;
    vector<pair<int,ThreeVector>> posCells;
    vector<pair<int,ThreeVector>> posPlates;


public:
    ProcessFile(){};
    void sortLayersPos();
    void FindCentralPad(mapTypeSpec &spec,  int event,vector<pair<int,ThreeVector>> &vecplate);
    void mainProccess(string filePos, string fileSpec);

};
