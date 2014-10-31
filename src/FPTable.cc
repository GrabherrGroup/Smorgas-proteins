#include "src/FPTable.h"
#include "base/FileParser.h"
#include <math.h>

double Sigmoid(double x, double s) {
  double y = x * s;
  double f = y*y;
  //if (f < 0)
  //f = -f;
  double v = y/(f+1.);
  v /= s;
  return v;
}

double CDF(double x, double m, double s, double d)
{
  //x = 1. - x;

  double xx = (x-m);
  xx = Sigmoid(xx, d);
  //cout << d << " " << x-m << " " << xx << endl;
  //double r = 0.5 * (1. + erf(xx/s/1.414213562));
  //cout << r << " ";
  double r = erfc((xx)/s/1.414213562)/2;
  //cout << r << endl;
  //cout << "x=" << x << " m=" << m << " s=" << s << " cdf=" << r << endl;
  return r;
}

double CDF_tanh(double x, double m, double s, double d)
{
  //double xx = (x-m);
  //xx = Sigmoid(xx, d);
  //cout << d << " " << x-m << " " << xx << endl;
  double r = 0.5 + tanh((x-m)/s)/2;

  //cout << "x=" << x << " m=" << m << " s=" << s << " cdf=" << r << endl;
  return r;
}


void FPTable::Read(const string & fileName)
{
  FlatFileParser parser;
  
  parser.Open(fileName);
  parser.ParseLine();
  int n = parser.AsInt(0);
  m_data.clear();
  m_data.resize(n);
  int k = 0;
  int i = 0;
  while (parser.ParseLine()) {
    if (parser.GetItemCount() == 0)
      continue;
    if (parser.AsString(0) == "len") {
      //cout << k << endl;
      m_data[k].SetSize(parser.AsInt(3));
      k++;
      if (k == n)
	break;
      i = 0;
      continue;
    }
    //cout << i << endl;
    
    m_data[k].Set(i, parser.AsFloat(0));
    i++;
  }
  //cout << "Done." << endl;
}


void FPTable::Write(const string & fileName)
{
  FILE * p = fopen(fileName.c_str(), "w");
  int i, j;
  fprintf(p, "%d\n", m_data.isize());
  for (i=0; i<m_data.isize(); i++) {
    const Dist & d = Table(i);

    fprintf(p, "len %d data % d\n", i, d.Size());
    for (j=0; j<d.Size(); j++) 
      fprintf(p, "%e\n", d.Get(j));
  }
  fclose(p);
}

void FPTable::Add(int size, double ident)
{
  if (size >= m_data.isize())
    size = m_data.isize()-1;
  //cout << size << " " << m_data.isize() << endl;
  m_data[size].Add(ident);
}

void FPTable::Compute()
{
  int n = 0;
  int i, j;
  
  cout << "Computing tables." << endl;
  for (i=0; i<m_data.isize(); i++)
    m_data[i].Normalize();
  return;

  //bool bOK = false;
  for (j=0; j<m_data[0].Size(); j++) {
    cout << "Loop " << j << endl;
    bool bOK = true;
    do {
      bOK = true;
      for (i=4; i<m_data.isize(); i++) {
	double a = m_data[i-1].Get(j)*1.2;
	double b = m_data[i].Get(j);
	//cout << "%: " << j << " t: " << i << " ";
	//cout << "a: " << a << " b: " << b << endl;
	if (a < b) {
	  cout << "Not OK, " << i << " " << j  << " " << a << " " << b << endl;
	  //if (a < b) {
	  //cout << "Comparison error (1)." << endl;
	  //}
	  //if (a > b) {
	  //cout << "Comparison error (2)." << endl;
	  //}
	  bOK = false;
	  //toSmooth = j;
	  break;
	}
      }      
      if (!bOK) {
	double r = 0.001;
	svec<Dist> tmp = m_data;
	//for (j=0; j<m_data[0].Size(); j++) {
	//j = toSmooth;
	for (i=4; i<m_data.isize()-1; i++) {
	  double v = m_data[i].Get(j)*(1.-r) + m_data[i-1].Get(j)*r/2. + m_data[i+1].Get(j)*r/2.;
	  tmp[i].Set(j, v);
	}
	//}
	m_data = tmp;    
      } 
    } while (!bOK);
  }
  for (i=0; i<m_data.isize(); i++)
    m_data[i].Smooth(m_data.isize());
}


void FPTable::Fit()
{
  int i;
  for (i=0; i<m_data.isize(); i++) {
    cout << "Len: " << i << " ";
    m_data[i].Fit();
  }
  //m_data[70].Fit();

}

double Dist::Distance(double m, double s, double d, bool bPrint)
{
  
  int i;
  double dist = 0.;
  for (i=0; i<m_data.isize(); i++) {
    double x = (double)i/(double)(m_data.isize() - 1);
    double y = CDF(x, m, s, d);
    double dd = y - m_data[i];
    dist += dd*dd;
    if (bPrint) {
      cout << m_data[i] << "\t" << y << "\t" << dd*dd << endl;
    }
  }
  return dist;
}


void Dist::Fit()
{
  int i, j, k;


  /*  for (i=0; i<100; i++) {
    double x = (double)i/99.;
    cout << CDF(x, 0.5, 0.1, 1.) << " ";
    cout << CDF(x, 0.5, 0.2, .1) << " ";
    cout << CDF(x, 0.5, 0.3, 2.) << " ";
    cout << CDF(x, 0.5, 0.4, 5.) << endl;;
  }

  exit(0);*/

  double min = 999999999.;
  double best_m = 0.;
  double best_s = 0.;
  double best_d = 0.;

  for (i=0; i<500; i++) {
    for (j=0; j<500; j++) {
      for (k=5; k<=5; k++) {
	double d = (double)k/5;
	double m = (double)i/500.;
	double s = (double)j/1200.;
	double dist = Distance(m, s, d);
	if (dist < min) {
	  min = dist;
	  best_s = s;
	  best_m = m;
	  best_d = d;
	}
      }
    }
  }
  //cout << "Printing: " << endl;
  cout << "m: " << best_m << "\ts: " << best_s << "\td: " << best_d << "\t" << Distance(best_m, best_s, best_d) << endl;
  // Distance(best_m, best_s, best_d, true);


}
