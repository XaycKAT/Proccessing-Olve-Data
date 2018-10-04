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
    vector<ThreeVector> first;
    vector<ThreeVector> second;
    ParsingFile::readPosFile(fileName,first,second);
    ProcessFile obj;
    obj.processData(first);
    return 0;
}
