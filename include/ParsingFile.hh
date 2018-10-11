#pragma once
#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<ProcessFile.hh>
using namespace std;

class ParsingFile
{
private:
    static void streamPars (string &str, vector<ThreeVector> &vec);
public:
    ParsingFile();
    static void readPosFile (string fileName, vector<ThreeVector> &cell, vector<ThreeVector> &plates);
    static void readSpecFile (string fileName, mapTypeLayer &cell, mapTypeLayer &plates,
                              mapTypeSpec &);

};
