#ifndef SCORING_H
#define SCORING_H

#include <math.h>
#include "src/FScoreTable.h"

double SigmoidFS(double x, double s) {
  double y = x * s;
  double f = y*y;
  double v = y/(f+1.);
  v /= s;
  return v;
}

double CDF_FS(double x, double m, double s, double d)
{
 
  double xx = (x-m);
  xx = SigmoidFS(xx, d);
  double r = erfc((xx)/s/1.414213562)/2;
  return r;
}

class ProtAlignScore
{
 public:
  ProtAlignScore() {}

  double FPVal(int len, double ident) {
    if (ident > 1.)
      ident = 1.;
    if (len < 3)
      return 1.;
    double m, s, d;
    if (len > 200) {
      m = (table_m[200] + table_m[201] + table_m[202] + table_m[203])/4.;
      s = (table_s[200] + table_s[201] + table_s[202] + table_s[203])/4.;
      d = (table_d[200] + table_d[201] + table_d[202] + table_d[203])/4.;
    } else {
      m = table_m[len];
      s = table_s[len]; 
      d = table_d[len];
    }  
    double y = CDF_FS(ident, m, s, d);
    return y;
  }
  
};

#endif //SCORING_H


