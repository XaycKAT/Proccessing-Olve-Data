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
    string filePos="/home/xayc/CERN/data/position.dat";
    string enName = "he_sp";
    string parctileName= enName.substr(0,2);
    string fileSpec="/home/xayc/CERN/data/"+parctileName+'/'+enName+"/spectre_"+enName+'_';
    ProcessFile obj;
    bool index = false; // считывание соседей или расчет (false = расчет не нужен)

    obj.MainProccess(filePos,fileSpec,index,100, enName); // файл позиции, файл спетктра,индекс соседи, кол-во файлов спектра
    cout<<"-----------SUCCESS-----------"<<endl;
    return 0;
}
