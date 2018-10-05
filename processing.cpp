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
    string fileName="/home/xayc/CERN/root/position.dat";
    vector<ThreeVector> posCells;
    vector<ThreeVector> posPlates;
    ParsingFile::readPosFile(fileName,posCells,posPlates);
    ProcessFile obj;
    obj.sortLayers(posCells);
    return 0;
}
