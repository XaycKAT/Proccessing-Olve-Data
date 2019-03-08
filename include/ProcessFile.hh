#pragma once
#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<map>
#include<unordered_map>
#include<tuple>
#include<algorithm>

typedef  unordered_map <int,int> mapTypeLayer;
typedef  map<int,double> mapTypeEdep;
typedef  map<int,pair<double,ThreeVector>> mapIntPairDoubleVec;
typedef  map<int,ThreeVector> mapIntVec;
typedef  multimap<int,pair<int,ThreeVector*>> mapTypeID;
typedef  map<int,vector<int>> mapTypeNiegh;
struct EdepData
{
    mapTypeEdep cellLayersEdep;
    mapTypeEdep platesEdep;
    vector<double> chargeN;
    vector<double> chargewN;
    vector<double> reversCurrent;
    ThreeVector posVec;
    ThreeVector momentumVec;
    vector<pair<int,ThreeVector>> centralPads;
    EdepData(){}
    EdepData(ThreeVector pv, ThreeVector mv,vector<pair<int,ThreeVector>> centPads, mapTypeEdep cellEdep,
             mapTypeEdep plateEdep, vector<double> revCurr, vector<double> chN,vector<double> chwN)
    {
        reversCurrent=revCurr;
        posVec=pv;
        momentumVec=mv;
        cellLayersEdep=cellEdep;
        platesEdep=plateEdep;
        centralPads=centPads;
        chargeN = chN;
        chargewN = chwN;
    }
};
struct PosData
{

    int32_t assemblyNum;
    int32_t layerNum;
    int32_t number;
    ThreeVector posVec;
    PosData(){}
    PosData(int32_t an,int32_t ln,int32_t num, ThreeVector vec)
    {
        assemblyNum=an;
        layerNum=ln;
        number=num;
        posVec=vec;
    }
};

typedef  map <int,EdepData> mapTypeSpec;

class ProcessFile
{
private:
    mapTypeLayer cellLayersNum;
    mapTypeSpec specArr;
    double thresholdValuePlas=5*2*2.5*1.032;
    double thresholdValueSilic=2*0.05*2.33;
    mapTypeID mapIdPads;
    mapTypeNiegh mapNeighbors;
    vector<pair<int,ThreeVector>> posCells;
    mapIntVec posPlates;



public:
    ProcessFile(){}
    ~ProcessFile(){}
    void SortLayersPos();
    void MainProccess(string filePos, string fileSpec, bool, int, string);
    void FilterSpec();
    void WriteFile(string);
    void RootGraph2D(vector<ThreeVector> vec);
    void FindNeighborPads();
    void FindReverseCurr();
    void WriteNeigFile();

};
