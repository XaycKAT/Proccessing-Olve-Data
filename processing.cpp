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
    vector<string> pName = {"p", "c", "he", "fe"};
    vector<string> eName = {"100GeV", "1TeV", "10TeV", "100TeV","sp"};
    vector<double> fileSize = {40,40,3,300,100};
    string filePos="/home/xayc/CERN/data/position.dat";

    for(unsigned int i = 0; i < pName.size();i++)
    {
        for(unsigned int k = 0; k < eName.size(); k++)
        {
            cout<<"Reading "<<pName[i]<<' '<<eName[k]<<endl;

            string penName = pName[i] +'_'+ eName[k];
            string fileSpec="/home/xayc/CERN/data/"+pName[i]+'/'+penName+"/spectre_"+penName+'_';
            ProcessFile obj;
            bool index = false; // считывание соседей или расчет (false = расчет не нужен)

            obj.MainProccess(filePos,fileSpec,index,fileSize[k], penName); // файл позиции, файл спетктра,индекс соседи, кол-во файлов спектра
        }
    }
    cout<<"-----------END-----------"<<endl;
    return 0;
}
