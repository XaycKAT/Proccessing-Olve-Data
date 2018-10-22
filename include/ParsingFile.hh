#pragma once
#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<ProcessFile.hh>
using namespace std;

class ParsingFile
{
private:
    static void streamPars (string &str, vector<pair<int,ThreeVector>> &vec);
    static void streamVec (stringstream &sts, ThreeVector &vec);
public:
    ParsingFile();
    static void readPosFile (string fileName,  vector<pair<int,ThreeVector>> &cell,  vector<pair<int,ThreeVector>> &plates);
    static void readSpecFile (string fileName, mapTypeLayer &cell, mapTypeSpec &);

};
