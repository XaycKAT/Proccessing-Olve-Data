#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<ParsingFile.hh>
#include<ProcessFile.hh>
#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<unordered_map>
#include<tuple>

using namespace std;
void ParsingFile::streamPars(string &currLine,  vector<pair<int,ThreeVector>> &vec)
{
    ThreeVector tempvec;
    double tempd;
    char tempc;
    stringstream currLineStream;

    currLineStream<<currLine;
    currLineStream>>tempd;
    int n=tempd;
    currLineStream>>tempc;
    currLineStream>>tempd;
    tempvec.x=tempd ;

    currLineStream>>tempc;
    currLineStream>>tempd;
    tempvec.y=tempd ;

    currLineStream>>tempc;
    currLineStream>>tempd;
    tempvec.z=tempd ;
    vec.push_back(pair<int,ThreeVector>(n,tempvec));
}
void ParsingFile::streamVec(stringstream &currLineStream, ThreeVector &vec)
{
    double tempd;
    char tempc;

    currLineStream>>tempc;
    currLineStream>>tempd;
    vec.x=tempd;
    currLineStream>>tempc;
    currLineStream>>tempd;
    vec.y=tempd;
    currLineStream>>tempc;
    currLineStream>>tempd;
    vec.z=tempd;
}

void ParsingFile::readPosFile(string fileName,  vector<pair<int,ThreeVector>> &posCells,  vector<pair<int,ThreeVector>>  &posPlates)
{
    ifstream fileData(fileName);
    if (!fileData.is_open())
    {
        cout << "Position file can not be opened, or it does not exist " << endl;
        exit(EXIT_FAILURE);
    }
    string currLine;

    while (getline(fileData, currLine))
    {
        if(currLine[0]=='#')
        {
            break;
        }
        streamPars(currLine,posCells);
    }
    while (getline(fileData, currLine))
    {

        streamPars(currLine,posPlates);

    }
    if (fileData.bad()) {
        throw runtime_error ("IO error");
    }
}
void ParsingFile::readSpecFile(string fileName,  mapTypeLayer &cellLayersArr,mapTypeSpec &specArr)
{
    ifstream fileData(fileName);
    if (!fileData.is_open())
    {
        cout << "Spectrum file can not be opened, or it does not exist " << endl;
        exit(EXIT_FAILURE);
    }
    string currLine;
    ThreeVector posVec;
    ThreeVector momentVec;
    ThreeVector posEndVec;
    int event;
    mapTypeIntDouble buffCellMap;
    mapIntPairDoubleVec buffPlateMap;
    while(getline(fileData,currLine))
    {
        if(currLine[0]=='#')
        {
            char tempc;
            stringstream currLineStream;
            currLineStream<<currLine;
            if(buffCellMap.size()!=0 || buffPlateMap.size()!=0)
            {
                specArr[event].cellLayersEdep=buffCellMap;
                specArr[event].platesEdep=buffPlateMap;
                specArr[event].momentumVec=momentVec;
                specArr[event].posVec=posVec;
                specArr[event].posEndVec=posEndVec;
                buffCellMap.clear();
                buffPlateMap.clear();
            }
            currLineStream>>tempc;
            currLineStream>>event;
            streamVec(currLineStream,momentVec);

            currLineStream>>tempc;
            streamVec(currLineStream,posVec);

            currLineStream>>tempc;
            streamVec(currLineStream,posEndVec);


        }
        else
        {
            stringstream currLineStream;
            currLineStream<<currLine;

            int copyNo;
            double edep;
            ThreeVector posSilicVec;
            pair<double,ThreeVector> p;
            currLineStream >> copyNo;
            currLineStream >> edep;
            streamVec(currLineStream,posSilicVec);
            auto it = cellLayersArr.find(copyNo);
            if (it != cellLayersArr.end())
            {
                auto it = buffCellMap.find(cellLayersArr.at(copyNo));
                if(it != buffCellMap.end())
                {
                    it->second+=edep;
                }
                else
                    buffCellMap.insert(pair<int,double>(cellLayersArr.at(copyNo),edep));
            }
            else
            {
                p.first=edep;
                p.second=posSilicVec;
                buffPlateMap.insert(pair<int,pair<double,ThreeVector>>(copyNo,p));

            }
        }
    }
    if(buffCellMap.size()!=0 || buffPlateMap.size()!=0)
    {
        specArr[event].cellLayersEdep=buffCellMap;
        specArr[event].platesEdep=buffPlateMap;
        specArr[event].momentumVec=momentVec;
        specArr[event].posVec=posVec;
        specArr[event].posEndVec=posEndVec;
        buffCellMap.clear();
        buffPlateMap.clear();
    }
}
