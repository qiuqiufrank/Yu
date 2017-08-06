#include "dpendulum.h"

#include <math.h>
#include "func.h"
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <QList>
#include <QDebug>
//using namespace  std;

Dpendulum::Dpendulum()
{

}

QList <Res> res;
Func func;
double ddtheta1,ddtheta2,ddphi1,ddphi2;
double ar1,ar2,am1,am2;

int fc (double t, const double y[], double f[],
        void *params){
    f[0]=y[4];
    f[1]=y[5];
    f[2]=y[6];
    f[3]=y[7];
    func.getValues(y[0],y[1],y[2],y[3],y[4],y[5],y[6],y[7],ar1,ar2,am1,am2,9.8,f[4],f[5],f[6],f[7]);
    res.append({t,y[0],y[1],y[2],y[3],y[4],y[5],y[6],y[7]});
    return 	GSL_SUCCESS;
}

QList<Res> &Dpendulum::getPoints(double th1, double th2, double ph1, double ph2, double dth1, double dth2, double dph1, double dph2, double r1, double r2, double m1, double m2,double ts)
{

    res.clear();
    ar1=r1,ar2=r2,am1=m1,am2=m2;
    gsl_odeiv2_system sys = {fc,0, 8,0};
    //msadams sk2(slow)
    gsl_odeiv2_driver *d =gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_msadams,1e-6,1e-8, 0.0);
    double t = 0.0;
    double y[8] = { th1, th2,ph1,ph2,dth1,dth2,dph1,dph2 };
    int status = gsl_odeiv2_driver_apply (d, &t, ts, y);
    if (status != GSL_SUCCESS)
    {
        printf ("error, return value=%d\n", status);
    }
    gsl_odeiv2_driver_free (d);
    return res;


}





