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
  commandArg<double> cCmmd("-c","cutoff", 1.);
  commandLineParser P(argc,argv);
  P.SetDescription("Tests a table to determine false positive rates for alignments.");
  P.registerArg(fileCmmd);
  P.registerArg(oCmmd);
  P.registerArg(cCmmd);
  
  P.parse();
  
  string fileName = P.GetStringValueFor(fileCmmd);
  string in = P.GetStringValueFor(oCmmd);
  double cutoff = P.GetDoubleValueFor(cCmmd);
 
  FPTable tab;
  tab.Read(in);

  

  FlatFileParser parser;
  
  parser.Open(fileName);

  ProtAlignScore pas;

  svec<string> p_n, f_n;

  while (parser.ParseLine()) {
    if (parser.GetItemCount() < 13)
      continue;
    //cout << parser.Line() << endl;
    int len = parser.AsInt(11) - parser.AsInt(10);
    //cout << len << endl;
    double ident = parser.AsFloat(12);
    double eval = parser.AsFloat(5);
    //double eval = parser.AsFloat(13);
    if (ident > 1.)
      ident = 1.;
    //cout << "Train " << len << " " << ident << endl;
   
    double score = tab.GetScore(len, ident);
    double fvalue = pas.FPVal(len, ident);
    double p_value = 100*GetPValue(ident, len, 0.3);

    //cout << eval << " " << fvalue << endl;

    if (fvalue < cutoff)
      f_n.push_back(parser.AsString(1));
      //cout << parser.Line() << "\t" << score << " " << fvalue << endl;
    if (p_value < cutoff)
      p_n.push_back(parser.AsString(1));
      //cout << parser.Line() << "\t" << score << " " << p_value << endl;

  }

  UniqueSort(f_n);
  UniqueSort(p_n);
  cout << "f-value# " << f_n.isize() << " p-value# " << p_n.isize() << endl;

  return 0;
}
