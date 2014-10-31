#ifndef SCORING_H
#define SCORING_H


double Sigmoid(double x, double s) {
  double y = x * s;
  double f = y*y;
  double v = y/(f+1.);
  v /= s;
  return v;
}

double CDF(double x, double m, double s, double d)
{
 
  double xx = (x-m);
  xx = Sigmoid(xx, d);
  double r = erfc((xx)/s/1.414213562)/2;
  return r;
}

class ProtAlignScore
{
 public:
  double FPVal(int len, double ident) {
    if (ident > 1.)
      ident = 1.;
    if (len < 3)
      return 1.;
    
  }
  double x = (double)i/(double)(m_data.isize() - 1);
  double y = CDF(x, m, s, d);
};

#endif //SCORING_H


