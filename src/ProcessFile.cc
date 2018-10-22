#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<cmath>
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

void ProcessFile::sortLayersPos()
{

    sort( posCells.begin( ), posCells.end( ), [ ]( const auto& lhs, const auto& rhs )
    {
        return lhs.second.y > rhs.second.y;
    });
    double temp=posCells[0].second.y;
    int k=0;
    for(unsigned int i=0; i<posCells.size();i++)
    {
        if(posCells[i].second.y!=temp)
            k++;
        cellLayersNum.insert(pair<int,int>(posCells[i].first,k));
        temp=posCells[i].second.y;
    }
}
void ProcessFile::FindCentralPad(mapTypeSpec &specArr,const int event, vector<pair<int,ThreeVector>> &plateVecPosEdep)
{
    for(auto &numPad : specArr.at(event).platesEdep)
    {
        auto &p = numPad.second.second;
        if(p.x == 0. && p.y == 0. && p.z == 0.)
            continue;
        else
        {
            pair<int,ThreeVector> x(numPad.first,numPad.second.second);
            plateVecPosEdep.push_back(x);
        }

    }
}



void ProcessFile::mainProccess(string filePos, string fileSpec)
{
    ParsingFile::readPosFile(filePos,posCells,posPlates);
    sortLayersPos();
    ParsingFile::readSpecFile(fileSpec,cellLayersNum,specArr);
    int nofMips=0;
    thresholdValuePlas=5*2*25*1.032;
    thresholdValueSilic=2*0.5*2.33;
    ofstream file("/home/xayc/CERN/data/spec.dat");
    vector<int> evtErase;
    for(auto &event : specArr)
    {
        int count=0;
        for(auto &layer : event.second.cellLayersEdep)
        {
            if(layer.second > thresholdValuePlas)
                count++;
            else
                continue;
        }
        if(count < nofMips)
        {
            evtErase.push_back(event.first);
        }

    }
    cout<<"Before filter: "<<specArr.size()<<endl;
    for (auto &evt : evtErase)
    {
        auto it=specArr.find(evt);
        specArr.erase(it);
    }
    cout<<"After: "<<specArr.size()<<endl;
    int k=0,n=0;
    for (auto &evt : specArr)
    {
        vector<pair<int,ThreeVector>> p;
        FindCentralPad(specArr,evt.first,p);
        if(p.size() > 8)
            k++;
        if(p.size() == 8)
            n++;
    }
    cout<<k<<'\t'<<n<<endl;

    for(auto &event : specArr)
    {
        file <<'#'<< event.first <<'\t'<<event.second.momentumVec<<'\t'<<event.second.posVec<< endl;
        file<<"---->Cells"<<endl;
        for(auto &layer : event.second.cellLayersEdep)
        {
            file<< layer.first <<"\t"<< layer.second <<endl;
        }
        file<<"---->Plates"<<endl;
        for(auto &plate : event.second.platesEdep)
        {
            file<< plate.first<<"\t"<< plate.second.first <<'\t'<<plate.second.second<<endl;
        }
        file<<endl;
    }

    //    TApplication tapp("Test", 0, nullptr);
    //    TH1* Hist =new TH1D("value", "Energy 1 TeV 1000 events", 100, 0, 6e6);
    //    for(auto &event : specArr)
    //    {
    //        double fullEdep;
    //        for (auto &layer : event.second.cellLayersEdep)
    //        {
    //            fullEdep+=layer.second;
    //        }
    //        //cout<<fullEdep<<endl;
    //        Hist->Fill(fullEdep);
    //    }
    //    TCanvas c ( "test", "test" );

    //    Hist->Draw();
    //    c.SetGridx();
    //    c.Print ( "/home/xayc/CERN/spec.jpg" );

}
