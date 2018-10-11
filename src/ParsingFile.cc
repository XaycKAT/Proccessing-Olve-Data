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

using namespace std;
void ParsingFile::streamPars(string &currLine, vector<ThreeVector> &vec)
{
    ThreeVector tempvec;
    double tempd;
    char tempc;
    stringstream currLineStream;

    currLineStream<<currLine;
    currLineStream>>tempd;
    tempvec.setN(tempd);

    currLineStream>>tempc;
    currLineStream>>tempd;
    tempvec.setX(tempd);

    currLineStream>>tempc;
    currLineStream>>tempd;
    tempvec.setY(tempd);

    currLineStream>>tempc;
    currLineStream>>tempd;
    tempvec.setZ(tempd);
    vec.push_back(tempvec);
}
void ParsingFile::readPosFile(string fileName, vector<ThreeVector> &posCells, vector<ThreeVector>  &posPlates)
{
    ifstream fileData(fileName);
    if (!fileData.is_open())
    {
        cout << "Position file can not be opened, or it does not exist " << endl;
        exit(EXIT_FAILURE);
    }
    string currLine;
    int temp;
    while (getline(fileData, currLine))
    {
        stringstream currLineStream;

        if(currLine[0]=='#')
        {
            break;
        }
        streamPars(currLine,posCells);
    }
    while (getline(fileData, currLine))
    {
        stringstream currLineStream;
        currLineStream<<currLine;
        streamPars(currLine,posCells);

    }
    if (fileData.bad()) {
        throw runtime_error ("IO error");
    }
}
void ParsingFile::readSpecFile(string fileName,  mapTypeLayer &cellLayersArr, mapTypeLayer &platesGroupArr,mapTypeSpec &specArr)
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
    int event;
    mapTypeIntDouble buffCellMap;
    mapTypeIntDouble buffPlateMap;
    while(getline(fileData,currLine))
    {


        stringstream currLineStream;
        currLineStream<<currLine;
        if(currLine[0]=='#')
        {
            char tempc;
            double tempd;


            if(buffCellMap.size()!=0 || buffPlateMap.size()!=0)
            {
                currLineStream>>tempc;
                currLineStream>>event;

                currLineStream>>tempc;
                currLineStream>>tempd;
                momentVec.setX(tempd);
                currLineStream>>tempc;
                currLineStream>>tempd;
                momentVec.setY(tempd);
                currLineStream>>tempc;
                currLineStream>>tempd;
                momentVec.setZ(tempd);

                currLineStream>>tempc;

                currLineStream>>tempc;
                currLineStream>>tempd;
                posVec.setX(tempd);
                currLineStream>>tempc;
                currLineStream>>tempd;
                posVec.setY(tempd);
                currLineStream>>tempc;
                currLineStream>>tempd;
                posVec.setZ(tempd);

                specArr[event].cellLayersEdep=buffCellMap;
                specArr[event].platesEdep=buffPlateMap;
                specArr[event].momentumVec=momentVec;
                specArr[event].posVec=posVec;
            }


            buffCellMap.clear();
            buffPlateMap.clear();
        }
        else
        {
            stringstream currLineStream;
            currLineStream<<currLine;

            int copyNo;
            double edep;
            currLineStream >> copyNo;
            currLineStream >> edep;
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
}
