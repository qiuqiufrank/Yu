#include "func.h"

Func::Func()
{

}

void Func::getValues(const double th1,const double th2, const double ph1 ,const double ph2,const double dth1,
                     const double dth2,const double dph1,const double dph2,double r1,double r2,
                     double m1,double m2,double g,double &ddtheta1,double &ddtheta2,double &ddphi1,double &ddphi2)
{
     ddtheta1=-((-(pow(dth1,2)*m2*r1*
                   (4*sin(2*th1) - 2*sin(2*(ph1 - ph2 + th1)) -
                     2*sin(2*(-ph1 + ph2 + th1)) +
                     4*sin(ph1 - ph2 - 2*th1 - 2*th2) +
                     4*sin(ph1 - ph2 + 2*th1 - 2*th2) +
                     6*sin(2*(th1 - th2)) + sin(2*(ph1 - ph2 + th1 - th2)) +
                     sin(2*(-ph1 + ph2 + th1 - th2)) +
                     6*sin(2*(th1 + th2)) + sin(2*(ph1 - ph2 + th1 + th2)) +
                     sin(2*(-ph1 + ph2 + th1 + th2)) -
                     4*sin(ph1 - ph2 - 2*th1 + 2*th2) -
                     4*sin(ph1 - ph2 + 2*th1 + 2*th2))) -
                2*(2*g*m2*sin(2*ph1 - 2*ph2 - th1) + 16*g*m1*sin(th1) +
                   12*g*m2*sin(th1) - 2*g*m2*sin(2*ph1 - 2*ph2 + th1) -
                   pow(dph2,2)*m2*r2*sin(ph1 - ph2 - th1 - 3*th2) -
                   2*pow(dph2,2)*m2*r2*sin(th1 - 3*th2) -
                   pow(dph2,2)*m2*r2*sin(ph1 - ph2 + th1 - 3*th2) +
                   2*g*m2*sin(ph1 - ph2 - th1 - 2*th2) +
                   2*g*m2*sin(th1 - 2*th2) +
                   2*g*m2*sin(ph1 - ph2 + th1 - 2*th2) +
                   3*pow(dph2,2)*m2*r2*sin(ph1 - ph2 - th1 - th2) +
                   2*pow(dph2,2)*m2*r2*sin(th1 - th2) +
                   3*pow(dph2,2)*m2*r2*sin(ph1 - ph2 + th1 - th2) +
                   16*pow(dth2,2)*m2*r2*
                    (cos(th2)*sin(th1) - cos(ph1 - ph2)*cos(th1)*sin(th2)) +
                   8*pow(dph1,2)*r1*sin(th1)*
                    (-(cos(th1)*(2*m1 + m2 - m2*cos(2*th2))) +
                      m2*cos(ph1 - ph2)*sin(th1)*sin(2*th2)) -
                   3*pow(dph2,2)*m2*r2*sin(ph1 - ph2 - th1 + th2) +
                   2*pow(dph2,2)*m2*r2*sin(th1 + th2) -
                   3*pow(dph2,2)*m2*r2*sin(ph1 - ph2 + th1 + th2) -
                   2*g*m2*sin(ph1 - ph2 - th1 + 2*th2) +
                   2*g*m2*sin(th1 + 2*th2) -
                   2*g*m2*sin(ph1 - ph2 + th1 + 2*th2) +
                   pow(dph2,2)*m2*r2*sin(ph1 - ph2 - th1 + 3*th2) -
                   2*pow(dph2,2)*m2*r2*sin(th1 + 3*th2) +
                   pow(dph2,2)*m2*r2*sin(ph1 - ph2 + th1 + 3*th2) +
                   g*m2*sin(th1 - 2*(ph1 - ph2 + th2)) +
                   g*m2*sin(th1 + 2*(ph1 - ph2 + th2)) +
                   g*m2*sin(th1 - 2*(-ph1 + ph2 + th2)) +
                   g*m2*sin(th1 + 2*(-ph1 + ph2 + th2))))/
              (r1*(-32*m1 - 20*m2 + 4*m2*cos(2*(ph1 - ph2)) +
                  4*m2*cos(2*th1) - 2*m2*cos(2*(ph1 - ph2 + th1)) -
                  2*m2*cos(2*(-ph1 + ph2 + th1)) -
                  4*m2*cos(ph1 - ph2 - 2*th1 - 2*th2) +
                  4*m2*cos(ph1 - ph2 + 2*th1 - 2*th2) +
                  6*m2*cos(2*(th1 - th2)) +
                  m2*cos(2*(ph1 - ph2 + th1 - th2)) +
                  m2*cos(2*(-ph1 + ph2 + th1 - th2)) + 4*m2*cos(2*th2) -
                  2*m2*cos(2*(ph1 - ph2 + th2)) -
                  2*m2*cos(2*(-ph1 + ph2 + th2)) + 6*m2*cos(2*(th1 + th2)) +
                  m2*cos(2*(ph1 - ph2 + th1 + th2)) +
                  m2*cos(2*(-ph1 + ph2 + th1 + th2)) +
                  4*m2*cos(ph1 - ph2 - 2*th1 + 2*th2) -
                  4*m2*cos(ph1 - ph2 + 2*th1 + 2*th2))));


     ddtheta2=-((32*pow(dth1,2)*(m1 + m2)*r1*
                 (cos(ph1 - ph2)*cos(th2)*sin(th1) - cos(th1)*sin(th2)) +
                8*(4*g*(m1 + m2)*cos(th1)*
                    (cos(ph1 - ph2)*cos(th2)*sin(th1) - cos(th1)*sin(th2)) +
                   4*pow(dph1,2)*(m1 + m2)*r1*pow(sin(th1),2)*
                    (cos(ph1 - ph2)*cos(th2)*sin(th1) - cos(th1)*sin(th2)) +
                   pow(dph2,2)*r2*
                    (-2*m2*cos(ph1)*cos(ph2)*sin(2*th1)*pow(sin(th2),2) -
                      2*m2*sin(ph1)*sin(ph2)*sin(2*th1)*pow(sin(th2),2) +
                      (2*m1 + m2 - m2*cos(2*th1))*sin(2*th2))) +
                pow(dth2,2)*m2*r2*
                 (-4*sin(ph1 - ph2 - 2*th1 - 2*th2) +
                   4*sin(ph1 - ph2 + 2*th1 - 2*th2) + 6*sin(2*(th1 - th2)) +
                   sin(2*(ph1 - ph2 + th1 - th2)) +
                   sin(2*(-ph1 + ph2 + th1 - th2)) - 4*sin(2*th2) +
                   2*sin(2*(ph1 - ph2 + th2)) +
                   2*sin(2*(-ph1 + ph2 + th2)) - 6*sin(2*(th1 + th2)) -
                   sin(2*(ph1 - ph2 + th1 + th2)) -
                   sin(2*(-ph1 + ph2 + th1 + th2)) -
                   4*sin(ph1 - ph2 - 2*th1 + 2*th2) +
                   4*sin(ph1 - ph2 + 2*th1 + 2*th2)))/
              (r2*(-32*m1 - 20*m2 + 4*m2*cos(2*(ph1 - ph2)) +
                  4*m2*cos(2*th1) - 2*m2*cos(2*(ph1 - ph2 + th1)) -
                  2*m2*cos(2*(-ph1 + ph2 + th1)) -
                  4*m2*cos(ph1 - ph2 - 2*th1 - 2*th2) +
                  4*m2*cos(ph1 - ph2 + 2*th1 - 2*th2) +
                  6*m2*cos(2*(th1 - th2)) +
                  m2*cos(2*(ph1 - ph2 + th1 - th2)) +
                  m2*cos(2*(-ph1 + ph2 + th1 - th2)) + 4*m2*cos(2*th2) -
                  2*m2*cos(2*(ph1 - ph2 + th2)) -
                  2*m2*cos(2*(-ph1 + ph2 + th2)) + 6*m2*cos(2*(th1 + th2)) +
                  m2*cos(2*(ph1 - ph2 + th1 + th2)) +
                  m2*cos(2*(-ph1 + ph2 + th1 + th2)) +
                  4*m2*cos(ph1 - ph2 - 2*th1 + 2*th2) -
                  4*m2*cos(ph1 - ph2 + 2*th1 + 2*th2))));

     ddphi1=(2*1/sin(th1)*
             (-(dph1*dth1*r1*cos(th1)*
                  (-32*m1 - 20*m2 + 4*m2*cos(2*(ph1 - ph2)) +
                    4*m2*cos(2*th1) - 2*m2*cos(2*(ph1 - ph2 + th1)) -
                    2*m2*cos(2*(-ph1 + ph2 + th1)) -
                    4*m2*cos(ph1 - ph2 - 2*th1 - 2*th2) +
                    4*m2*cos(ph1 - ph2 + 2*th1 - 2*th2) +
                    6*m2*cos(2*(th1 - th2)) +
                    m2*cos(2*(ph1 - ph2 + th1 - th2)) +
                    m2*cos(2*(-ph1 + ph2 + th1 - th2)) + 4*m2*cos(2*th2) -
                    2*m2*cos(2*(ph1 - ph2 + th2)) -
                    2*m2*cos(2*(-ph1 + ph2 + th2)) +
                    6*m2*cos(2*(th1 + th2)) +
                    m2*cos(2*(ph1 - ph2 + th1 + th2)) +
                    m2*cos(2*(-ph1 + ph2 + th1 + th2)) +
                    4*m2*cos(ph1 - ph2 - 2*th1 + 2*th2) -
                    4*m2*cos(ph1 - ph2 + 2*th1 + 2*th2))) +
               8*pow(dth1,2)*m2*r1*
                (sin(2*(ph1 - ph2))*sin(th1)*pow(sin(th2),2) +
                  cos(th1)*sin(ph1 - ph2)*sin(2*th2)) +
               4*m2*(4*pow(dth2,2)*r2*sin(ph1 - ph2)*sin(th2) +
                  2*sin(ph1 - ph2)*
                   (g*cos(ph1)*cos(ph2)*sin(2*th1)*pow(sin(th2),2) +
                     g*sin(ph1)*sin(ph2)*sin(2*th1)*pow(sin(th2),2) +
                     2*pow(dph2,2)*r2*pow(sin(th2),3) +
                     g*pow(cos(th1),2)*sin(2*th2)) +
                  pow(dph1,2)*r1*sin(th1)*
                   (2*sin(2*(ph1 - ph2))*pow(sin(th1),2)*
                      pow(sin(th2),2) +
                     sin(ph1 - ph2)*sin(2*th1)*sin(2*th2)))))/
           (r1*(-32*m1 - 20*m2 + 4*m2*cos(2*(ph1 - ph2)) +
               4*m2*cos(2*th1) - 2*m2*cos(2*(ph1 - ph2 + th1)) -
               2*m2*cos(2*(-ph1 + ph2 + th1)) -
               4*m2*cos(ph1 - ph2 - 2*th1 - 2*th2) +
               4*m2*cos(ph1 - ph2 + 2*th1 - 2*th2) +
               6*m2*cos(2*(th1 - th2)) +
               m2*cos(2*(ph1 - ph2 + th1 - th2)) +
               m2*cos(2*(-ph1 + ph2 + th1 - th2)) + 4*m2*cos(2*th2) -
               2*m2*cos(2*(ph1 - ph2 + th2)) -
               2*m2*cos(2*(-ph1 + ph2 + th2)) + 6*m2*cos(2*(th1 + th2)) +
               m2*cos(2*(ph1 - ph2 + th1 + th2)) +
               m2*cos(2*(-ph1 + ph2 + th1 + th2)) +
               4*m2*cos(ph1 - ph2 - 2*th1 + 2*th2) -
               4*m2*cos(ph1 - ph2 + 2*th1 + 2*th2)));

     ddphi2=-(1/sin(th2)*
              (4*dph2*dth2*r2*cos(th2)*
                 (-32*m1 - 20*m2 + 4*m2*cos(2*(ph1 - ph2)) +
                   4*m2*cos(2*th1) - 2*m2*cos(2*(ph1 - ph2 + th1)) -
                   2*m2*cos(2*(-ph1 + ph2 + th1)) -
                   4*m2*cos(ph1 - ph2 - 2*th1 - 2*th2) +
                   4*m2*cos(ph1 - ph2 + 2*th1 - 2*th2) +
                   6*m2*cos(2*(th1 - th2)) +
                   m2*cos(2*(ph1 - ph2 + th1 - th2)) +
                   m2*cos(2*(-ph1 + ph2 + th1 - th2)) + 4*m2*cos(2*th2) -
                   2*m2*cos(2*(ph1 - ph2 + th2)) -
                   2*m2*cos(2*(-ph1 + ph2 + th2)) +
                   6*m2*cos(2*(th1 + th2)) +
                   m2*cos(2*(ph1 - ph2 + th1 + th2)) +
                   m2*cos(2*(-ph1 + ph2 + th1 + th2)) +
                   4*m2*cos(ph1 - ph2 - 2*th1 + 2*th2) -
                   4*m2*cos(ph1 - ph2 + 2*th1 + 2*th2)) +
                64*pow(dth1,2)*(m1 + m2)*r1*sin(ph1 - ph2)*sin(th1) +
                64*pow(dth2,2)*m2*r2*sin(ph1 - ph2)*sin(th1)*
                 (cos(th1)*cos(th2) + cos(ph1 - ph2)*sin(th1)*sin(th2)) +
                64*sin(ph1 - ph2)*sin(th1)*
                 (g*(m1 + m2)*cos(th1) +
                   pow(dph1,2)*(m1 + m2)*r1*pow(sin(th1),2) +
                   pow(dph2,2)*m2*r2*pow(sin(th2),2)*
                    (cos(th1)*cos(th2) + cos(ph1 - ph2)*sin(th1)*sin(th2))))
              )/(2.*r2*(-32*m1 - 20*m2 + 4*m2*cos(2*(ph1 - ph2)) +
               4*m2*cos(2*th1) - 2*m2*cos(2*(ph1 - ph2 + th1)) -
               2*m2*cos(2*(-ph1 + ph2 + th1)) -
               4*m2*cos(ph1 - ph2 - 2*th1 - 2*th2) +
               4*m2*cos(ph1 - ph2 + 2*th1 - 2*th2) +
               6*m2*cos(2*(th1 - th2)) +
               m2*cos(2*(ph1 - ph2 + th1 - th2)) +
               m2*cos(2*(-ph1 + ph2 + th1 - th2)) + 4*m2*cos(2*th2) -
               2*m2*cos(2*(ph1 - ph2 + th2)) -
               2*m2*cos(2*(-ph1 + ph2 + th2)) + 6*m2*cos(2*(th1 + th2)) +
               m2*cos(2*(ph1 - ph2 + th1 + th2)) +
               m2*cos(2*(-ph1 + ph2 + th1 + th2)) +
               4*m2*cos(ph1 - ph2 - 2*th1 + 2*th2) -
               4*m2*cos(ph1 - ph2 + 2*th1 + 2*th2)));
     if(isnan(ddtheta1)){
         ddtheta1=0.0;
         cout<<"warning";
     }
     if(isnan(ddtheta2)){
         ddtheta2=0.0;
         cout<<"warning";
     }
     if(isnan(ddphi1)){
         ddphi1=0.0;
         cout<<"warning";
     }
     if(isnan(ddphi2)){
         ddphi2=0.0;
         cout<<"warning";
     }
//     cout<<dth1<<"___"<<dth2<<endl;

}
