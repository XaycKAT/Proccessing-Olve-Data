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

void ParsingFile::StreamPars(string &currLine,  vector<pair<int,ThreeVector>> &vec)
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
void ParsingFile::StreamVec(stringstream &currLineStream, ThreeVector &vec)
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
void ParsingFile::ReadBinVec(ifstream &file, ThreeVector &vec)
{
    float x,y,z;
    file.read((char*)&x,sizeof (x));
    file.read((char*)&y,sizeof (y));
    file.read((char*)&z,sizeof (z));
    vec={x,y,z};
}
void ParsingFile::ReadBinID(ifstream &file, int32_t &an, int32_t &ln, int32_t &num)
{
    file.read((char*)&an,sizeof (an));
    file.read((char*)&ln,sizeof (ln));
    file.read((char*)&num,sizeof (num));
}
void ParsingFile::ReadBinPosFile(string fileName, mapTypeID &mapIdPads, vector<pair<int,ThreeVector>> &posCells, mapIntVec &posPlates)
{
    ifstream filePos(fileName, ifstream::binary);
    if (!filePos.is_open())
    {
        cout << "Position file can not be opened, or it does not exist " << endl;
        exit(EXIT_FAILURE);
    }
    int32_t an = 0;
    int32_t ln, num, copyN;
    int id;
    ThreeVector posVec;
    while (true)
    {

        filePos.read((char*)&copyN, sizeof(copyN));
        ReadBinID(filePos,an,ln,num);
        ReadBinVec(filePos,posVec);
        if(an > 1)
        {
            id=an*10+ln;
            posPlates.insert(pair<int,ThreeVector>(copyN,posVec));
            ThreeVector* vec=&posPlates.at(copyN);
            pair<int,ThreeVector*> tempp(copyN,vec);
            mapIdPads.insert(pair<int,pair<int,ThreeVector*>>(id,tempp));
            break;
        }
        posCells.push_back(pair<int,ThreeVector>(copyN,posVec));
    }
    while(filePos.read((char*)&copyN,sizeof (copyN)))
    {
        ReadBinID(filePos,an,ln,num);
        ReadBinVec(filePos,posVec);
        id=an*10+ln;
        posPlates.insert(pair<int,ThreeVector>(copyN,posVec));
        ThreeVector* vec=&posPlates.at(copyN);
        pair<int,ThreeVector*> tempp(copyN,vec);
        mapIdPads.insert(pair<int,pair<int,ThreeVector*>>(id,tempp));
    }

    if (filePos.bad()) {
        throw runtime_error ("IO error");
    }
    filePos.close();
}
int ParsingFile::ReadBinSpecFile(string fileName, mapTypeLayer &cellLayersArr, mapTypeSpec &specArr, int firstEvt)
{
    ifstream fileSpec(fileName, ifstream::binary);
    if (!fileSpec.is_open())
    {
        cout << "Spectrum file can not be opened, or it does not exist " << endl;
        exit(EXIT_FAILURE);
    }
    //номер, момент, позиция, кол-во выделений
    int32_t evtID=firstEvt, edepCount, copyN;
    int32_t buffEvt;
    float primEnergy;
    ThreeVector posVec, momVec, targetVec;
    vector<pair<int,ThreeVector>> centPads;
    float energyEdep;
    mapTypeEdep buffCellMap;
    mapTypeEdep buffPlateMap;
    while(fileSpec.read((char*)&primEnergy, sizeof(primEnergy)))
    {
        ReadBinVec(fileSpec,momVec);
        ReadBinVec(fileSpec,posVec);
        fileSpec.read((char*)&edepCount, sizeof(edepCount));
        while (edepCount!=0)
        {
            //номер, энергия, вектор.
            edepCount--;
            fileSpec.read((char*)&copyN, sizeof(copyN));
            fileSpec.read((char*)&energyEdep, sizeof(energyEdep));
            ReadBinVec(fileSpec,targetVec);
            if(targetVec.x != 0. && targetVec.y != 0. && targetVec.z != 0.)
            {
                centPads.push_back(pair<int,ThreeVector>(copyN,targetVec));
            }
            auto it = cellLayersArr.find(copyN);
            if (it != cellLayersArr.end())
            {
                auto it = buffCellMap.find(cellLayersArr.at(copyN));
                if(it != buffCellMap.end())
                {
                    it->second+=energyEdep;
                }
                else
                    buffCellMap.insert(pair<int,double>(cellLayersArr.at(copyN),energyEdep));
            }
            else
            {
                buffPlateMap.insert(pair<int,double>(copyN,energyEdep));
            }
        }
        specArr[evtID].cellLayersEdep=buffCellMap;
        specArr[evtID].platesEdep=buffPlateMap;
        specArr[evtID].momentumVec=momVec;
        specArr[evtID].posVec=posVec;
        specArr[evtID].centralPads=centPads;
        specArr[evtID].primEnergy = primEnergy;
        buffCellMap.clear();
        buffPlateMap.clear();
        centPads.clear();
        evtID++;
    }
    return evtID;
}
void ParsingFile::ReadSpecFile(string fileName,  mapTypeLayer &cellLayersArr,mapTypeSpec &specArr)
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
    mapTypeEdep buffCellMap;
    mapTypeEdep buffPlateMap;
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
                buffCellMap.clear();
                buffPlateMap.clear();
            }
            currLineStream>>tempc;
            currLineStream>>event;
            StreamVec(currLineStream,momentVec);

            currLineStream>>tempc;
            StreamVec(currLineStream,posVec);

            currLineStream>>tempc;
            StreamVec(currLineStream,posEndVec);


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
            StreamVec(currLineStream,posSilicVec);
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

                buffPlateMap.insert(pair<int,double>(copyNo,edep));

            }
        }
    }
    if(buffCellMap.size()!=0 || buffPlateMap.size()!=0)
    {
        specArr[event].cellLayersEdep=buffCellMap;
        specArr[event].platesEdep=buffPlateMap;
        specArr[event].momentumVec=momentVec;
        specArr[event].posVec=posVec;
        buffCellMap.clear();
        buffPlateMap.clear();
    }
}
void ParsingFile::ReadNeighborPads(string filename, mapTypeNiegh &mapNeig)
{
    ifstream fileNeighbor(filename);
    if (!fileNeighbor.is_open())
    {
        cout << "Neighbor file can not be opened, or it does not exist " << endl;
        exit(EXIT_FAILURE);
    }
    string currLine;
    while(getline(fileNeighbor,currLine))
    {
        stringstream currStream;
        currStream<< currLine;
        int pad;
        int neig;
        vector<int> neigPads;
        currStream >> pad;
        while ( currStream >> neig)
        {
            neigPads.push_back(neig);
        }
        mapNeig.insert(pair<int,vector<int>>(pad,neigPads));
        neigPads.clear();
    }

}
