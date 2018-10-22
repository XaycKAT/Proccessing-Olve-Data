#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ostream>
#include <vector>
#include <cmath>

using namespace std;

class ThreeVector
{
private:


public:
    double x,y,z;
    ThreeVector()
        :x(0.0), y(0.0), z(0.0)
    {}

    ThreeVector(double ax, double ay, double az)
        :x(ax), y(ay), z(az)
    {}


    inline ThreeVector& operator=(const ThreeVector &) noexcept;
    static inline ThreeVector mult(const ThreeVector &p1, const double &multiplicator)
    {
        double x = p1.x * multiplicator;
        double y = p1.y * multiplicator;
        double z = p1.z * multiplicator;
        return ThreeVector(x, y, z);
    }
    static inline double  range(const ThreeVector &p1, const ThreeVector &p2);
    bool getPlateIntersection(const ThreeVector &pp1, const ThreeVector &pp2, const ThreeVector &pp3,
                                 const ThreeVector &lp1, const ThreeVector &lp2);

};
inline double ThreeVector::range(const ThreeVector &p1, const ThreeVector &p2)
{
    return sqrt(pow (p2.x-p1.x,2)+ pow(p2.y-p1.y,2) +pow(p2.z - p1.z, 2));
}

inline ostream & operator<< (ostream &os, const ThreeVector &v)
{
     os << "(" << v.x << "," << v.y  << "," << v.z << ")";
     return os;
}

inline ThreeVector&  ThreeVector::operator= (const ThreeVector &v) noexcept
{
    x=v.x;
    y=v.y;
    z=v.z;
    return *this;
}

inline ThreeVector operator + (const ThreeVector &p1, const ThreeVector &p2)
{
    return ThreeVector(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
}

inline ThreeVector operator - (const ThreeVector &p1, const ThreeVector &p2)
{
    return ThreeVector(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

inline double operator * (const ThreeVector &p1, const ThreeVector &p2)
{
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

inline ThreeVector operator * (const ThreeVector &v1, double t)
{
    return ThreeVector
    {
        t * v1.x,
        t * v1.y,
        t * v1.z,
    };
}

inline ThreeVector operator * (double t, const ThreeVector &v1)
{
    return v1 * t;
}

inline ThreeVector operator & (const ThreeVector &p1, const ThreeVector &p2)
{
    double x = p1.y * p2.z - p2.y * p1.z;
    double y = p1.z * p2.x - p2.z * p1.x;
    double z = p1.x * p2.y - p2.x * p1.y;
    return ThreeVector(x, y, z);
}

inline double abs(const ThreeVector &v)
{
    return std::sqrt(v * v);
}
