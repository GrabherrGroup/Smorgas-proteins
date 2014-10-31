

#ifndef FPTABLE_H
#define FPTABLE_H

#include "base/SVector.h"

class Dist
{
 public:
  Dist() {
    SetSize(200);
  }

  void SetSize(int size) {
    m_data.resize(size, 0.);
  }

  void Set(int i, double v) {
    m_data[i] = v;
  }
  double Get(int i) const {
    return m_data[i];
  }
  int Size() const {return m_data.isize();}
  
  void Add(double ident) {
    //cout << "Adding " << ident << " " << ToInt(ident) << endl;
    m_data[ToInt(ident)] += 1.;
  }
  void Normalize() {
     double s = 0.000000000000001;
    int i;
    for (i=0; i<m_data.isize(); i++)
      s += m_data[i];
    for (i=0; i<m_data.isize(); i++)
      m_data[i] /= s;    
    s = 0.;
    for (i=m_data.isize()-1; i>=0; i--) {
      s += m_data[i];
      m_data[i] = s;
    }

  }
  void Smooth(int n) {
    int i, j;
    for (i=0; i<n; i++) {
      svec<double> tmp;
      //Print();

      tmp = m_data;
      double r = 0.001;
      tmp.resize(m_data.isize(), 0.);
      for (j=1; j<m_data.isize()-1; j++) {
	//cout << "Before: " << tmp[j] << endl;
	tmp[j] = m_data[j] * (1 - r) + m_data[j-1]*r/2 + m_data[j+1]*r/2;
	//cout << "After: " << tmp[j] << endl;
      }
      m_data = tmp;
    }
  }

  double FP(double ident) {
    return m_data[ToInt(ident)];
  } 
  void Print() const {
    for (int i=0; i<m_data.isize(); i++)
      cout << i << " " << m_data[i] << endl;
  }

  void Fit();

 private:
  double Distance(double m, double s, double d, bool bPrint = false);
  int ToInt(double v) const {
    int x = (int)(v*(double)(m_data.isize() - 1));
    if (x >= m_data.isize())
      cout << "ERROR: " << x << " " << v << " " << m_data.isize() << endl; 
    return x;
  }

  svec<double> m_data;
};


class FPTable
{
 public:
  FPTable() {
    m_data.resize(300);
  }

  double GetScore(int len, double ident) { 
    if (ident > 1.)
      ident = 1.;
    int index = len;
    double div = 1.;
    if (len >= m_data.isize()) {
      index = m_data.isize()-1;
      div = (double)len/(double)(m_data.isize()-1);
    }

    double r = m_data[index].FP(ident);
    r /= div;
    return r;
  }

  int Size() const {return m_data.isize();}
  const Dist & Table(int i) const {return m_data[i];}

  void Fit();

  void Read(const string & fileName);
  void Write(const string & fileName);
  
  void Add(int size, double ident);
  void Compute();

 private:
  svec<Dist> m_data;
};







#endif //FPTABLE_H

