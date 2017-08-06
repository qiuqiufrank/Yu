#ifndef DPENDULUM_H
#define DPENDULUM_H
#include <QList>


struct Res{
    double t;
    double th1;
    double th2;
    double ph1;
    double ph2;
    double dth1;
    double dth2;
    double dph1;
    double dph2;
};

class Dpendulum
{
public:
    Dpendulum();
    QList<Res> & getPoints(double th1, double th2, double ph1, double ph2, double dth1, double dth2, double dph1, double dph2, double r1, double r2, double m1, double m2, double ts);

};

#endif // DPENDULUM_H
