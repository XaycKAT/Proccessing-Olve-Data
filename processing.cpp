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
    string fileSpec="/home/xayc/CERN/data/spectrum.dat";
    ProcessFile obj;

    obj.mainProccess(filePos,fileSpec);
    cout<<"success"<<endl;
    return 0;
}
