#include<ThreeVector.hh>
#include<vector>
#include<string>
#include<ProcessFile.hh>
#include<iostream>
#include<algorithm>

using namespace std;

void ProcessFile::processData(vector<ThreeVector> &vecCells)
{
    sort( vecCells.begin( ), vecCells.end( ), [ ]( const auto& lhs, const auto& rhs )
    {
       return lhs.getY() < rhs.getY();
    });
    double temp=vecCells[0].getY();
    int k=0;
    vector<double> vec;
    for(int i=0; i<vecCells.size();i++)
    {
        if(vecCells[i].getY()!=temp)
            k++;
        layersArr[k].push_back(vecCells[i].getN());
        temp=vecCells[i].getY();
    }
}

