#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ostream>
#include <vector>

using namespace std;

class ThreeVector
{
private:
    int n;
    double x,y,z;

public:
    ThreeVector()
        :n(0.0), x(0.0), y(0.0), z(0.0)
    {}

    ThreeVector(int an, double ax, double ay, double az)
        :n(an), x(ax), y(ay), z(az)
    {}

    inline double getX() const { return x; }
    inline double getY() const { return y; }
    inline double getZ() const { return z; }
    inline int getN() const {return n;}

    inline void setX(double ax) { x =  ax; }
    inline void setY(double ay) { y =  ay; }
    inline void setZ(double az) { z =  az; }
    inline void setN(int an) { n =  an; }
    inline ThreeVector& operator=(const ThreeVector &) noexcept;

};
inline ostream & operator<< (ostream &os, const ThreeVector &v)
{
     os << "(" << v.getX() << "," << v.getY() << "," << v.getZ() << ")";
     return os;
}

inline ThreeVector&  ThreeVector::operator= (const ThreeVector &v) noexcept
{
    x=v.x;
    y=v.y;
    z=v.z;
    return *this;
}
