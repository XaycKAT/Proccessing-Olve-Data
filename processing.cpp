#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include<ThreeVector.hh>
#include<ParsingFile.hh>
#include<ProcessFile.hh>
using namespace std;
int main()
{
    string filePos="/home/xayc/CERN/data/position.dat";
    string fileSpec="/home/xayc/CERN/data/spectre_30TeV_";
    ProcessFile obj;
    bool index = false; // считывание соседей или расчет
    obj.MainProccess(filePos,fileSpec,index);
    cout<<"success"<<endl;
    return 0;
}
