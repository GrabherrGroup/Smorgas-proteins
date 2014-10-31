#include <string>
#include "base/CommandLineParser.h"
#include "base/FileParser.h"
#include "src/DNAVector.h"
#include "src/FPTable.h"

int main( int argc, char** argv )
{

  commandArg<string> fileCmmd("-i","input file");
  commandArg<string> oCmmd("-o","output file");
  commandLineParser P(argc,argv);
  P.SetDescription("Trains a table to determine false positive rates for alignments.");
  P.registerArg(fileCmmd);
  P.registerArg(oCmmd);
  
  P.parse();
  
  string fileName = P.GetStringValueFor(fileCmmd);
  string out = P.GetStringValueFor(oCmmd);
  
  FPTable tab;

  //tab.Add(24, 0.33);
  //tab.Compute();
  //tab.Write(out);
  //return 0;
  //comment. ???
  FlatFileParser parser;
  
  parser.Open(fileName);

  while (parser.ParseLine()) {
    if (parser.GetItemCount() < 13)
      continue;
    //cout << parser.Line() << endl;
    int len = parser.AsInt(11) - parser.AsInt(10);
    //cout << len << endl;
    double ident = parser.AsFloat(12);
    if (ident > 1.)
      ident = 1.;
    //cout << "Train " << len << " " << ident << endl;
   
    tab.Add(len, ident);
  }
  cout << "Computing." << endl;
  tab.Compute();
  cout << "Saving." << endl;
  tab.Write(out);
  cout << "All done." << endl;
  return 0;
}
