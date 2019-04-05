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
    vector<string> eName = {"100GeV", "1TeV", "10TeV", "100TeV", "sp"};
    vector<double> amountFiles = {40,40,30,300,150};
    string filePos="/home/xayc/CERN/data/position.dat";
    bool index = false; // считывание соседей или расчет (false = расчет не нужен)

    for(unsigned int i = 0; i < 1; i++)
    {
        for(unsigned int k = 0; k < 4; k++)
        {
            cout<<"----Reading "<<pName[i]<<' '<<eName[k]<<endl;
            ProcessFile obj;
            string penName = pName[i] +'_'+ eName[k];
            string fileSpec="/home/xayc/CERN/data/"+pName[i]+'/'+penName+"/spectre_"+penName+'_';
            if ( i == 0 && k == 2)
                obj.MainProccess(filePos,fileSpec,index, 3, penName);
            else
                obj.MainProccess(filePos,fileSpec,index,amountFiles[k], penName);// файл позиции, файл спетктра,индекс соседи, кол-во файлов спектра
        }
    }
//    string fileSpec = "/home/xayc/CERN/data/spectrum.dat";
//    string c = "";
//    obj.MainProccess(filePos,fileSpec,index, 1, c);

    cout<<"-----------END-----------"<<endl;
    return 0;
}
