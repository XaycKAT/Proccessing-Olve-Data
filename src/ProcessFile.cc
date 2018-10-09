#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<ProcessFile.hh>
#include<iostream>
#include<algorithm>
#include<ParsingFile.hh>

#include <TTree.h>
#include <TF1.h>
#include <TApplication.h>
#include "TH2.h"
#include "TCanvas.h"
using namespace std;

void ProcessFile::sortLayers(vector<ThreeVector> &vecCells)
{
    sort( vecCells.begin( ), vecCells.end( ), [ ]( const auto& lhs, const auto& rhs )
    {
        return lhs.getY() < rhs.getY();
    });
    double temp=vecCells[0].getY();
    int k=0;
    for(unsigned int i=0; i<vecCells.size();i++)
    {
        if(vecCells[i].getY()!=temp)
            k++;
        cellLayersArr.insert(pair<int,int>(vecCells[i].getN(),k));
        temp=vecCells[i].getY();
    }
}


void ProcessFile::rootProcess(string fileName,mapTypeLayer &platesGroupArr)
{
    ParsingFile::readSpecFile(fileName,cellLayersArr,platesGroupArr,specArr);

    ofstream file("spec.dat");
    for(auto &layer : specArr)
    {
        file <<'#'<< layer.first <<'\t'<<layer.second.momentumVec<<'\t'<<layer.second.posVec<< endl;
        for(auto &cellLayers : layer.second.cellLayers)
        {
            file<< cellLayers.first <<"\t"<< cellLayers.second <<endl;
        }
        for(auto &plateGroups : layer.second.platesGroup)
        {
            file<< plateGroups.first <<"\t"<< plateGroups.second <<endl;
        }
        file<<endl;
    }

    TApplication tapp("Test", 0, nullptr);
    TH1* Hist =new TH1D("value", "Energy 1 TeV 1000 events", 100, 0, 6e6);
    for(auto &event : specArr)
    {
        double fullEdep;
        for (auto &layer : event.second.cellLayers)
        {
            fullEdep+=layer.second;
        }
        //cout<<fullEdep<<endl;
        Hist->Fill(fullEdep);
    }
    TCanvas c ( "test", "test" );

    Hist->Draw();
    c.SetGridx();
    c.Print ( "/home/xayc/CERN/spec.pdf" );
}
