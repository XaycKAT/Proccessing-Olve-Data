#pragma once
#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<ProcessFile.hh>
using namespace std;

class ParsingFile
{
private:
    ThreeVector coorVec;
    static void streamPars (string &str, vector<ThreeVector> &vec);
public:
    ParsingFile();
    static void readPosFile (string fileName, vector<ThreeVector> &cell, mapTypeLayer &plates);
    static void readSpecFile (string fileName, mapTypeLayer &cell, mapTypeLayer &plates,
                              mapTypeSpec &);

};
