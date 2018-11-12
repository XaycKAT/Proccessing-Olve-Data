#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<cmath>
#include<ProcessFile.hh>
#include<iostream>
#include<algorithm>
#include<ParsingFile.hh>
#include<omp.h>

#include <TTree.h>
#include <TF1.h>
#include <TApplication.h>
#include "TH2.h"
#include "TCanvas.h"
#include <TGraph2D.h>
using namespace std;

void ProcessFile::SortLayersPos()
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
void ProcessFile::FindNeighborPads()
{
#pragma omp parallel for
    for(int i = 20; i < 94; i++)
    {
        double delta = 0.001;
        auto ret = mapIdPads.equal_range(i);
        for(auto it = ret.first; it!=ret.second; ++it)
        {
            //cout<<it->first<<'\t'<<it->second<<endl;
            auto pos = posPlates.find(it->second.first);
            vector<int> tempv;
            for(auto neig = ret.first; neig!=ret.second; ++neig)
            {
                double range = ThreeVector::range(pos->second,*neig->second.second);
                if( abs(range - 10.) < delta || abs(sqrt(10.*10.+5.*5.)-range) < delta
                           || abs(10.*sqrt(2) - range) < delta)                {
                    tempv.push_back(neig->second.first);
                }
            }
            mapNeighbors.insert(pair<int,vector<int>>(pos->first,tempv));
        }
    }

    //    ofstream file("pos.dat");
    //    file<<"#id"<<endl;
    //    for(auto &it : mapIdPads)
    //    {
    //        file<<it.first<<'\t'<<it.second.first<<'\t'<<*it.second.second<<endl;
    //    }
    //    file<<"#plates"<<endl;
    //    for(auto &it : posPlates)
    //    {
    //        file<<it.first<<'\t'<<it.second<<endl;
    //    }
    //    file.close();


}
void ProcessFile::FindReverseCurr()
{
    for(auto &evt : specArr)
    {
        double mainEdep = 0.;
        double neighEdep = 0.;
        vector<double> revCurr;
        vector<double> charge;
        for(auto &centPad : evt.second.centralPads)
        {
            mainEdep += evt.second.platesEdep.at(centPad.first);
            double edep = 0.;
            for(auto &neig : mapNeighbors.at(centPad.first))
            {
                auto it = evt.second.platesEdep.find(neig);
                if(it != evt.second.platesEdep.end())
                    edep += evt.second.platesEdep.at(neig);
                else
                    continue;
            }
            neighEdep += edep / mapNeighbors.at(centPad.first).size();
            revCurr.push_back(mainEdep - neighEdep);
            charge.push_back((mainEdep - neighEdep)/thresholdValueSilic);
        }
        evt.second.charge = charge;
        evt.second.reversCurrent = revCurr;
    }

}
void ProcessFile::FilterSpec()
{
    int nOverLayers=5;
    vector<int> evtErase;
    for(auto &event : specArr)
    {
        if(event.second.cellLayersEdep.size() == 0)
        {
            evtErase.push_back(event.first);
        }
    }
    cout<<"Before filter cell edep: "<<specArr.size()<<endl;
    for (auto &evt : evtErase)
    {
        auto it=specArr.find(evt);
        specArr.erase(it);
    }
    evtErase.clear();
    cout<<"After: "<<specArr.size()<<endl;
    for(auto &event : specArr)
    {
        int count=0;
        for(auto &layer : event.second.cellLayersEdep)
        {
            if(layer.second >= thresholdValuePlas)
                count++;
            else
                continue;
        }
        if(count < nOverLayers)
        {
            evtErase.push_back(event.first);
        }

    }
    cout<<"Before filter Mips: "<<specArr.size()<<endl;
    for (auto &evt : evtErase)
    {
        auto it=specArr.find(evt);
        specArr.erase(it);
    }
    cout<<"After: "<<specArr.size()<<endl;
    int a[15]={0};
    for (auto &evt : specArr)
    {
        vector<pair<int,double>> ers;
        auto &cPads = evt.second.centralPads;
        if(cPads.size()>4)
        {
            for(int unsigned i = 0; i < cPads.size() - 1; i++)
            {
                double r = ThreeVector::range(cPads[i].second,cPads[i+1].second);
                ers.push_back(pair<int,double>(cPads[i+1].first,r));
            }
            sort( ers.begin( ), ers.end( ), [ ]( const auto& lhs, const auto& rhs )
            {
                return lhs.second > rhs.second;
            });
            int size = cPads.size();
            for(int i=0; i < size - 4; i++)
            {
                auto &it = ers.back();
                for(int unsigned i = 0; i < cPads.size(); i++)
                {
                    if(cPads[i].first == it.first)
                    {
                        auto iter = evt.second.centralPads.begin();
                        evt.second.centralPads.erase(iter + i);
                        break;
                    }
                }
                ers.pop_back();
            }
            vector<ThreeVector> vec;
            for(auto &it : evt.second.centralPads)
            {
                vec.push_back(it.second);
            }
            //RootGraph2D(vec);
        }
        a[cPads.size()]++;

    }
    int f=0;
    for(int i=0;i<15;i++)
    {
        cout<<i<<'\t'<<a[i]<<endl;
        f+=a[i];
    }
    cout<<f<<endl;

}
void ProcessFile::WriteFile(string fileOutName)
{
    ofstream file(fileOutName);

    for(auto &event : specArr)
    {
        file <<'#'<< event.first <<endl;
        for(unsigned int i = 0; i < event.second.reversCurrent.size(); i++)
        {
            file<< event.second.reversCurrent[i]<<"  "<<event.second.charge[i]<<endl;
        }
        file << endl;

        //        file<<"---->Cells"<<endl;
        //        for(auto &layer : event.second.cellLayersEdep)
        //        {
        //            file<< layer.first <<"\t"<< layer.second <<endl;
        //        }
        //        file<<"---->Plates"<<endl;
        //        for(auto &plate : event.second.platesEdep)
        //        {
        //            file<< plate.first<<"\t"<< plate.second<<endl;
        //        }
        //        file<<endl;
    }
    file.close();

}
void ProcessFile::RootProccess()
{
    TH1* Hist =new TH1D("value", "Energy 1 TeV 1000 events", 100, 0, 6e6);
    for(auto &event : specArr)
    {
        double fullEdep;
        for (auto &layer : event.second.cellLayersEdep)
        {
            fullEdep+=layer.second;
        }
        //cout<<fullEdep<<endl;
        Hist->Fill(fullEdep);
    }
    TCanvas c ( "test", "test" );

    Hist->Draw();
    c.SetGridx();
    c.Print ( "/home/xayc/CERN/spec.jpg" );
}
void ProcessFile::RootGraph2D(vector<ThreeVector> vec)
{
    TApplication tapp("Test", 0, nullptr);
    TGraph2D *gr = new TGraph2D();
    //gr->SetPoint(gr->GetN(),vec[0].x,vec[0].y,vec[0].z+rand()%10/10.);

    for(unsigned int i=0; i < vec.size(); i++)
    {
        gr->SetPoint ( gr->GetN(), vec[i].x, vec[i].y, vec[i].z);
        gr->SetMarkerColor(kBlue);
        gr->Draw ();
    }
    tapp.Run();

}
void ProcessFile::MainProccess(string filePos, string fileSpec)
{
    ParsingFile::ReadBinPosFile(filePos,mapIdPads,posCells,posPlates);
    SortLayersPos();
    ParsingFile::ReadBinSpecFile(fileSpec,cellLayersNum,specArr);
    FilterSpec();
    FindNeighborPads();
    int count0=0;
    int count5=0;
    int count3=0;
    int count8=0;
    int count6=0;
    int counts=0;

    for(auto &p : mapNeighbors)
    {
        if(p.second.size() < 4)
            count0++;
        if(p.second.size() == 6)
            count6++;
        if(p.second.size() == 8)
            count8++;
        if(p.second.size() == 3)
            count3++;
        if(p.second.size() == 5)
            count5++;
        if(p.second.size() > 8)
            counts++;
    }
    FindReverseCurr();
    WriteFile("spec.dat");
}

