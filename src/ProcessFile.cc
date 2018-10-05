#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<ProcessFile.hh>
#include<iostream>
#include<algorithm>
#include<ParsingFile.hh>
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
        //layersArr[k].push_back(vecCells[i].getN());
        layersArr.insert(pair<int,int>(vecCells[i].getN(),k));
        temp=vecCells[i].getY();
    }
}


