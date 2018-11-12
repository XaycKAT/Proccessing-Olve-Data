#pragma once
#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<ProcessFile.hh>
using namespace std;

class ParsingFile
{
private:
    static void StreamPars (string &str, vector<pair<int,ThreeVector>> &vec);
    static void StreamVec (stringstream &sts, ThreeVector &vec);

public:
    ParsingFile();
    ~ParsingFile(){}
    static void ReadBinPosFile (string fileName, mapTypeID &mapId, vector<pair<int,ThreeVector>> &cell, mapIntVec &plates);
    static void ReadBinSpecFile(string filename,  mapTypeLayer &cell, mapTypeSpec &);
    static void ReadBinVec(ifstream &,ThreeVector &vec);
    static void ReadBinID(ifstream &, int32_t &an,int32_t &gn, int32_t &num);

    static void ReadSpecFile (string fileName, mapTypeLayer &cell, mapTypeSpec &);

};
