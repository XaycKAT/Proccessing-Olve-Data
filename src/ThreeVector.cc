#include "ThreeVector.hh"
#include <cmath>
using namespace std;


bool ThreeVector::getPlateIntersection(const ThreeVector &pp1, const ThreeVector &pp2, const ThreeVector &pp3,
                                         const ThreeVector &lp1, const ThreeVector &lp2)
{
    ThreeVector e1 = pp1-pp2;
    ThreeVector e2 = pp2-pp3;
    ThreeVector n = e1 & e2;
    ThreeVector l = lp2 - lp1;
    ThreeVector p;


    float denom = n * l;
    if (abs(denom) > 1e-6) {
        ThreeVector vecToPlate = pp1 - lp1;
        float t = vecToPlate*n / denom;
        *this=t*l + lp1 ;
        return true;

    }
    else
        return false;
}

