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
    string fileName="/home/xayc/CERN/position.dat";
    vector<ThreeVector> posCells;
    mapTypeLayer posPlates;
    ParsingFile::readPosFile(fileName,posCells,posPlates);
    fileName="/home/xayc/CERN/spectrum.dat";
    ProcessFile obj;
    obj.sortLayers(posCells);
    obj.rootProcess(fileName,posPlates);
    cout<<"success"<<endl;
    return 0;
}
