#include <string>
#include "base/CommandLineParser.h"
#include "base/FileParser.h"
#include "src/DNAVector.h"
#include "src/FPTable.h"
#include "src/Smorgas/Scoring.h"
#include <math.h>

double Sigma(double p, int N)
{
  return sqrt(p * (1. - p) * (double)N);
}

double GetPValue(double ident,
                 int length,
                 double expect_ident)
{

      
  double p_match = expect_ident;
     
  //cout << "ident=" << ident << " p_match=" << p_match << endl;


  double s = Sigma(p_match, length);

  //cout << "Sigma=" << s << endl; 
      
  double m = p_match * (double)length;

  double x = (double)length * ident;
    
  //cout << "m=" << m << " x=" << x << endl;

  //double cdf = CDF(m, x, s);

  double cdf = erfc((x-m)/s/1.414213562)/2;


  //cout << "cdf=" << cdf << endl;

  double targetSize = 1;

  double expect = cdf * targetSize; // Twice the genome size if we do RC!!
  double p_val = -expm1(-expect);
     
  //cout << "expect=" << expect << " p-val=" << p_val << endl;
  return p_val;
}





int main( int argc, char** argv )
{

  commandArg<string> fileCmmd("-i","input file");
  commandArg<string> oCmmd("-t","table file");
  commandLineParser P(argc,argv);
  P.SetDescription("Fits a trained model to estimate false positive rates for alignments.");
  P.registerArg(fileCmmd);
  P.registerArg(oCmmd);
  
  P.parse();
  
  string fileName = P.GetStringValueFor(fileCmmd);
  string in = P.GetStringValueFor(oCmmd);
 
  FPTable tab;
  tab.Read(in);
  tab.Fit();
  return 0;

}
