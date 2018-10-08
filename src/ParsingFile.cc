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
void ParsingFile::readPosFile(string fileName, vector<ThreeVector> &posCells, mapTypeLayer &platesGroupArr)
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
            currLineStream<<currLine;
            char tempc;
            currLineStream>>tempc;
            currLineStream>>temp;
            break;
        }
        streamPars(currLine,posCells);
    }
    while (getline(fileData, currLine))
    {
        stringstream currLineStream;
        currLineStream<<currLine;

        if(currLine[0]=='#')
        {
            char tempc;
            currLineStream>>tempc;
            currLineStream>>temp;
        }
        else
        {
            int temp1;
            currLineStream >> temp1;
            platesGroupArr.insert(pair<int,int>(temp1,temp));
        }
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

                specArr[event].cellLayers=buffCellMap;
                specArr[event].platesGroup=buffPlateMap;
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
                it = platesGroupArr.find(copyNo);
                if(it == platesGroupArr.end())
                {
                    cout<<"Parsing spectrum file ERROR"<<endl;
                    exit(EXIT_FAILURE);
                }
                else
                {
                    auto it = buffPlateMap.find(platesGroupArr.at(copyNo));
                    if(it != buffPlateMap.end())
                    {
                        it->second+=edep;
                    }
                    else
                        buffPlateMap.insert(pair<int,double>(platesGroupArr.at(copyNo),edep));
                }
            }
        }
    }
}
