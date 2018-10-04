#pragma once
#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<map>
class ProcessFile
{
private:
    map <int,vector<double>> layersArr;
public:
    ProcessFile(){};
    void processData(vector<ThreeVector> &);

};
