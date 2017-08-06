#ifndef FUNC_H
#define FUNC_H
#include <iostream>
#include <math.h>
using namespace  std;


class Func
{
public:
    Func();
    void getValues(const double th1, const double th2, const double ph1, const double ph2, const double dth1, const double dth2, const double dph1, const double dph2, double r1, double r2, double m1, double m2, double g, double &ddtheta1, double &ddtheta2, double &ddphi1, double &ddphi2);


};

#endif // FUNC_H
