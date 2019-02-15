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

bool ThreeVector::getLineBelongs(const ThreeVector &linePoint1,const ThreeVector &linePoint2,const ThreeVector &point)
{
    double x= abs((point.x - linePoint1.x)/(linePoint2.x-linePoint1.x));
    double y= abs((point.y - linePoint1.y)/(linePoint2.y-linePoint1.y));
    double z= abs((point.z - linePoint1.z)/(linePoint2.z-linePoint1.z));
    if(abs(x+y-2*z) < 0.001)
        return true;
    else
        return false;
}

double ThreeVector::getAngleTrackPad( ThreeVector &p1, ThreeVector &p2, ThreeVector &p3, ThreeVector &vec)
{
    ThreeVector e1 = p1-p2;
    ThreeVector e2 = p2-p3;
    ThreeVector n = e1 & e2;
    return n*vec/(abs(n)*abs(vec));
}
